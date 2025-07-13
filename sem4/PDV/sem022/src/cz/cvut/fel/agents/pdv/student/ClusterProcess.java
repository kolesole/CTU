package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Message;
import cz.cvut.fel.agents.pdv.dsand.Pair;
import cz.cvut.fel.agents.pdv.evaluation.StoreOperationEnums;
import cz.cvut.fel.agents.pdv.raft.RaftProcess;
import cz.cvut.fel.agents.pdv.raft.messages.*;

import java.util.*;
import java.util.function.BiConsumer;

public class ClusterProcess extends RaftProcess<Map<String, String>> {
  enum ProcessState {
    Leader,
    Follower,
    Candidate
  }

  // ostatni procesy v clusteru
  private final List<String> otherProcessesInCluster;
  // maximalni spozdeni v siti
  private final int networkDelays;

  private int wakeCount;

  // FOR ALL
  private ProcessState state;
  private int currentTerm;
  private String votedFor;
  private int votedForTerm;
  private Log log;
  private Database database;

  private int commitIndex;
  private int numOfReceivers;
  private int lastApplied;

  private Random rand;

  // FOR LEADER
  private Map<String, Integer> nextIndex;
  private Map<String, Integer> matchIndex;
  private int votedNum;
  private final int majority;

  // OTHERS
  private int electionTimeout;
  private String leader;


  public ClusterProcess(String id, Queue<Message> inbox, BiConsumer<String, Message> outbox,
      List<String> otherProcessesInCluster, int networkDelays) {
    super(id, inbox, outbox);
    this.otherProcessesInCluster = otherProcessesInCluster;
    this.networkDelays = networkDelays;
    wakeCount = 0;

    currentTerm = 0;
    state = ProcessState.Follower;
    currentTerm = 0;
    log = new Log();
    database = new Database();

    rand = new Random();

    nextIndex = new HashMap<>();
    matchIndex = new HashMap<>();
    votedNum = 0;
    majority = (otherProcessesInCluster.size()) / 2 + 1;

    restartTimeout();
    leader = null;
  }

  public void restartTimeout() {
    electionTimeout = (rand.nextInt(otherProcessesInCluster.size() * 2) + 3) + networkDelays;
  }

  public void restartIndexes() {
    int lastLogIndex = log.getLastIndex();
    for (String otherProcess : otherProcessesInCluster) {
      if (otherProcess.equals(getId())) continue;
      nextIndex.put(otherProcess, lastLogIndex + 1);
      matchIndex.put(otherProcess, -1);
    }
  }

  public void tryStartElection() {
    electionTimeout--;

    if (electionTimeout > 0 || state == ProcessState.Leader) return;

    state = ProcessState.Candidate;
    currentTerm++;
    votedFor = getId();
    votedNum = 1;
    leader = null;
    restartTimeout();

    int lastLogIndex = log.getLastIndex();
    int lastLogTerm = log.getTermAtIndex(lastLogIndex);
    for (String otherProcess : otherProcessesInCluster) {
      if (otherProcess.equals(getId())) continue;
      send(otherProcess, new VoteMessage(currentTerm, getId(), lastLogIndex, lastLogTerm));
    }
  }

  public void handleOperation(LogElement logElement) {
    String clientID = logElement.clientID;
    String requestID = logElement.requestID;
    String operation = logElement.operation;
    String key = logElement.key;
    String value = logElement.value;

    switch (operation) {
      case "PUT":
        if (logElement.result == null || state != ProcessState.Leader) {
          database.put(key, value);
          logElement.result = "";
        }

        if (state == ProcessState.Leader) {
          send(clientID, new ServerResponseConfirm(requestID));
        }
        break;
      case "APPEND":
        if (logElement.result == null || state != ProcessState.Leader) {
          database.append(key, value);
          logElement.result = "";
        }

        if (state == ProcessState.Leader) {
          send(clientID, new ServerResponseConfirm(requestID));
        }
        break;
      case "GET":
        if (logElement.result == null) {
          logElement.result = database.get(key);
        }

        if (state == ProcessState.Leader) {
          send(clientID, new ServerResponseWithContent<>(requestID, logElement.result));
        }
        break;
      default:
        break;
    }
  }

  public void trySendAppendEntries() {
    if (!state.equals(ProcessState.Leader)) return;

    for (String otherProcess : otherProcessesInCluster) {
      if (otherProcess.equals(getId())) continue;

      int nextIndx = nextIndex.getOrDefault(otherProcess, 0);
      int prevLogIndex = nextIndx - 1;
      int prevLogTerm = log.getTermAtIndex(prevLogIndex);
      send(otherProcess, new AppendEntries(currentTerm, getId(), prevLogIndex, prevLogTerm, log.getEntriesFrom(nextIndx), commitIndex));
    }
  }

  public void handleClientRequestWhoisLeader(ClientRequestWhoIsLeader crwil) {
    send(crwil.sender, new ServerResponseLeader(crwil.getRequestId(), leader));
  }

  public void handleRequestWithContent(ClientRequestWithContent<StoreOperationEnums, Pair<String, String>> crwc) {
    if (state != ProcessState.Leader) {
      send(crwc.sender, new ServerResponseLeader(crwc.getRequestId(), leader));
      return;
    }

    IOperation op = crwc.getOperation();
    Pair<String, String> content = crwc.getContent();
    LogElement newLogEl = new LogElement(currentTerm, crwc.sender, crwc.getRequestId(),
            op, content.getFirst(), content.getSecond());

    LogElement checkLogEl = log.getLogElById(crwc.getRequestId());
    if (checkLogEl != null) {
      if (checkLogEl.committed) handleOperation(checkLogEl);
    } else {
      log.addLogEl(newLogEl);
    }
  }

  public void handleVoteMessage(VoteMessage vm) {
    if (vm.term <= currentTerm || log.getLastTerm() > vm.term ||
            (log.getLastTerm() == vm.lastLogTerm && log.getLastIndex() > vm.lastLogIndex)) {
      send(vm.candidateId, new VoteMessageResponse(currentTerm, false));
      return;
    }

    state = ProcessState.Follower;
    currentTerm = vm.term;
    votedFor = vm.candidateId;
    send(votedFor, new VoteMessageResponse(currentTerm, true));
  }

  public void handleVoteMessageResponse(VoteMessageResponse vmr) {
    if (vmr.term != currentTerm || !vmr.voteGranted || state.equals(ProcessState.Leader)) return;

    votedNum++;
    if (votedNum >= majority) {
      state = ProcessState.Leader;
      leader = getId();
      restartIndexes();
    }
  }

  public void rewriteLog(int startIndex, List<LogElement> entries) {
    if (startIndex < log.getSize()) {
      log.cutLog(startIndex, log.getSize() - 1);
    }

    for (LogElement entry : entries) {
      log.addLogEl(entry);
      if (entry.committed) {
        handleOperation(entry);
      }
    }
  }

  public void handleAppendEntries(AppendEntries ae) {
    if (ae.term < currentTerm) {
      send(ae.leaderId, new AppendEntriesResponse(currentTerm, false, -1));
      return;
    }
    state = ProcessState.Follower;
    currentTerm = ae.term;
    leader = ae.leaderId;
    restartTimeout();

    if (ae.prevLogIndex >= 0) {
      LogElement prev = log.getLogElByIndex(ae.prevLogIndex);
      if (prev == null || prev.term != ae.prevLogTerm) {
        send(leader, new AppendEntriesResponse(currentTerm, false, -1));
        return;
      }
    }

    rewriteLog(ae.prevLogIndex + 1, ae.entries);

    if (ae.leaderCommit > commitIndex) {
      commitIndex = Math.min(ae.leaderCommit, log.getLastIndex());
      for (int i = lastApplied + 1; i <= commitIndex; i++) {
        LogElement entry = log.getLogElByIndex(i);
        if (entry != null && !entry.committed) {
          entry.committed = true;
          handleOperation(entry);
        }
      }
      lastApplied = commitIndex;
    }
    send(leader, new AppendEntriesResponse(currentTerm, true, log.getLastIndex()));
  }

  public void handleAppendEntriesResponse(AppendEntriesResponse aer) {
    if (aer.term != currentTerm || state != ProcessState.Leader) return;
    if (aer.success) {
      matchIndex.put(aer.sender, aer.matchIndex);
      nextIndex.put(aer.sender, aer.matchIndex + 1);
      tryCommitEntries();
//      int count = 0;
//      for (int val : matchIndex.values()) {
//        count += val >= aer.matchIndex ? 1 : 0;
//      }
//      if (count >= majority) {
//        handleOperation(log.getLogElByIndex(aer.matchIndex - 1));
//        log.getLogElByIndex(aer.matchIndex - 1).committed = true;
//      }
    } else {
      int nextIndx = nextIndex.getOrDefault(aer.sender, 1);
      if (nextIndx > 1) {
        nextIndex.put(aer.sender, nextIndx - 1);
      }
    }
  }

  public void tryCommitEntries() {
    List<Integer> lst = new ArrayList<>(matchIndex.values());
    lst.add(log.getLastIndex());
    Collections.sort(lst);
    int comm = lst.get(lst.size() - majority);
    if (comm > commitIndex && log.getTermAtIndex(comm) == currentTerm) {
      commitIndex = comm;
      for (int i = lastApplied + 1; i <= commitIndex; i++) {
        LogElement entry = log.getLogElByIndex(i);
        if (entry != null && !entry.committed) {
          entry.committed = true;
          handleOperation(entry);
        }
      }
      lastApplied = commitIndex;
    }
  }


  @Override
  public Optional<Map<String, String>> getLastSnapshotOfLog() {
    return Optional.of(database.DB);
  }

  @Override
  public String getCurrentLeader() { return leader; }

  @Override
  public void act() {
    wakeCount++;
    tryStartElection();

    while (!inbox.isEmpty()) {
      Message m = inbox.poll();
      if (m instanceof ClientRequestWhoIsLeader crwil) {
        handleClientRequestWhoisLeader(crwil);
      }
      else if (m instanceof ClientRequestWithContent) {
        ClientRequestWithContent<StoreOperationEnums, Pair<String, String>> crwc =
                (ClientRequestWithContent<StoreOperationEnums, Pair<String, String>>) m;
        handleRequestWithContent(crwc);
      }
      else if (m instanceof VoteMessage vm) {
        handleVoteMessage(vm);
      }
      else if (m instanceof VoteMessageResponse vmr) {
        handleVoteMessageResponse(vmr);
      }
      else if (m instanceof AppendEntries ae) {
        handleAppendEntries(ae);
      }
      else if (m instanceof AppendEntriesResponse aer) {
        handleAppendEntriesResponse(aer);
      }
    }
    trySendAppendEntries();
  }
}
