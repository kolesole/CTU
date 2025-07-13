package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Message;
import cz.cvut.fel.agents.pdv.dsand.Pair;
import cz.cvut.fel.agents.pdv.evaluation.StoreOperationEnums;
import cz.cvut.fel.agents.pdv.raft.RaftProcess;

import java.util.*;
import java.util.function.BiConsumer;

import cz.cvut.fel.agents.pdv.raft.messages.*;

/**
 * Vasim ukolem bude naimplementovat (pravdepodobne nejenom) tuto tridu. Procesy v clusteru pracuji
 * s logy, kde kazdy zanam ma podobu mapy - kazdy zaznam v logu by mel reprezentovat stav
 * distribuovane databaze v danem okamziku.
 *
 * Vasi implementaci budeme testovat v ruznych scenarich (viz evaluation.RaftRun a oficialni
 * zadani). Nasim cilem je, abyste zvladli implementovat jednoduchou distribuovanou key/value
 * databazi s garancemi podle RAFT.
 */
public class ClusterProcess extends RaftProcess<Map<String, String>> {

  enum ProcessState {
    Leader,
    Follower,
    Candidate
  }

  private final List<String> otherProcessesInCluster;

  private ProcessState state;

  private int term;

  private int votedForEpoch;

  private int nominatedForEpoch;

  private int networkDelays;

  private int wakeCount;

  private int leaderMessageTime;

  private int votesReceived;

  private final Log log;

  private String leader;

  private final int majority;

  private int processTimeout;

  private Log waitingRequests;

  private final Database database;

  private int numReceiversLastLogEl;

  private LogElement lastCommittedLogElement;

  private Map<String, Integer> nextIndexes;       // send node with index for each process

  private Random rand;

  public ClusterProcess(String id, Queue<Message> inbox, BiConsumer<String, Message> outbox,
                        List<String> otherProcessesInCluster, int networkDelays) {
    super(id, inbox, outbox);
    this.otherProcessesInCluster = otherProcessesInCluster;
    this.majority = (otherProcessesInCluster.size()) / 2 + 1;

    this.networkDelays = networkDelays;

    this.state = ProcessState.Follower;
    this.leader = null;
    this.leaderMessageTime = 0;
    this.votesReceived = 0;
    this.votedForEpoch = 0;
    this.nominatedForEpoch = 0;

    this.term = 0;
    this.wakeCount = 0;

    this.log = new Log(new ArrayList<LogElement>());
    this.waitingRequests = null;

    database = new Database();
    numReceiversLastLogEl = 0;
    lastCommittedLogElement = null;

    nextIndexes = new HashMap<>();

    rand = new Random();
    updateTimeout();
  }

  public void updateTimeout() {
    processTimeout = rand.nextInt(1, otherProcessesInCluster.size() * 2) * (networkDelays + 2);
  }

  public boolean isLeaderRelevant() {
    return (wakeCount - leaderMessageTime < processTimeout) || (state == ProcessState.Leader);
  }

  @Override
  public Optional<Map<String, String>> getLastSnapshotOfLog() {
    return Optional.of(database.DB);
  }

  @Override
  public String getCurrentLeader() {
    return leader;
  }

  public void becomeLeader() {
    state = ProcessState.Leader;
    leader = getId();
    waitingRequests = new Log(new ArrayList<>());

    numReceiversLastLogEl = 0;
    lastCommittedLogElement = null;
    nextIndexes = new HashMap<>();

    int logSize = log.getSize();

    for (String process : otherProcessesInCluster) {
      if (process.equals(getId())) continue;

      nextIndexes.put(process, logSize - 1);
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

  public void handleVoteMessage(VoteMessage vm) {
    int epoch = log.getLastLogElEpoch();
    int lastIndx = log.getSize() - 1;

    if ((votedForEpoch < vm.epoch) &&
            (vm.epoch > epoch
                    || (vm.epoch == epoch && vm.lastIndx >= lastIndx))) {
      votedForEpoch = vm.epoch;
      send(vm.sender, new ReplyVoteMessage(votedForEpoch));
    }
  }

  public void handleReplyVoteMessage(ReplyVoteMessage rvm) {
    if (rvm.epoch != votedForEpoch) return;

    votesReceived++;
    if (votesReceived > majority) {
      becomeLeader();
    }
  }

  // ???????????????????????????????????
  public void handleAppendEntries(AppendEntries ae) {
    if (ae.epoch >= term) {
      updateTimeout();
      state = ProcessState.Follower;
      term = ae.epoch;
      leader = ae.sender;

      LogElement committedLogEl = ae.committedLogEl;
      LogElement lastLogEl = ae.lastLogEl;
      LogElement newLogEl = ae.newLogEl;

      LogElement confEl = null;
      int nextIndex;

      if (newLogEl != null && newLogEl.logIndx < log.getSize()) {
        log.cutLog(newLogEl.logIndx + 1, log.getSize() - 1);
      }

      LogElement lastEl = log.getLastLogEl();

      if ((newLogEl != null && lastEl != null) && lastEl.equals(newLogEl)) {
        if (lastEl )
      } else {
        log.removeLastLogEl();
      }

      if (newLogEl == null) {
        nextIndex = log.getSize();
      } else {
        if (newLogEl.logIndx < log.getSize() - 1) {
          log.cutLog(newLogEl.logIndx, log.getSize() - 1);
        }
        LogElement curLast = log.getLastLogEl();
        if (curLast != null && curLast.equals(newLogEl)) {
          nextIndex = curLast.logIndx + 1;
          confEl = curLast;
        }
        else if ((lastLogEl == null && curLast == null) || curLast.equals(lastLogEl)) {
          if (curLast != null && !curLast.committed) {
            handleOperation(curLast);
            curLast.committed = true;
          }

          log.addLogEl(newLogEl);
          if (log.isLastElCommitted()) {
            handleOperation(log.getLastLogEl());
          }

          confEl = newLogEl;
          nextIndex = log.getSize()+ 1;
        } else {
          nextIndex = log.getSize() - 2;
        }
      }

      send(ae.sender, new ReplyEntries(term, confEl, nextIndex));
    }
  }

  public void handleRequestWhoIsLeader(ClientRequestWhoIsLeader crwil) {
    send(crwil.sender, new ServerResponseLeader(crwil.getRequestId(), leader));
  }

  public void handleRequestWithContent(ClientRequestWithContent<StoreOperationEnums, Pair<String, String>> crwc) {
    if (state != ProcessState.Leader) {
      send(crwc.sender, new ServerResponseLeader(crwc.getRequestId(), leader));
      return;
    }

    IOperation op = crwc.getOperation();
    Pair<String, String> content = crwc.getContent();
    LogElement newLogEl = new LogElement(term, crwc.sender, crwc.getRequestId(),
            op, content.getFirst(), content.getSecond());

    LogElement lastLogEl = log.getLastLogEl();
    if (log.contains(newLogEl) && (!newLogEl.equals(lastLogEl) || lastLogEl.committed)) {
      // add put append get
      handleOperation(newLogEl);
      return;
    }

    if (waitingRequests.contains(newLogEl)) return;

    if (log.isLastElCommitted() && waitingRequests.isEmpty()) {
      log.addLogEl(newLogEl);
    } else {
      waitingRequests.addLogEl(newLogEl);
    }
  }

  public void trySendAppendEntries() {
    if (state != ProcessState.Leader) return;

    if (log.isLastElCommitted()) {
      LogElement waitingEl = waitingRequests.getFirstLogEl();

      if (waitingEl != null) {
        log.addLogEl(waitingEl);
        waitingRequests.removeFirstLogEl();
      }
    }

    for (String otherProcess : otherProcessesInCluster) {
      if (otherProcess.equals(leader)) continue;

      int nextIndex = nextIndexes.get(otherProcess);

      LogElement lastLogEl = null;
      LogElement newLogEl = null;

      LogElement committedLogEl = lastCommittedLogElement;
      if (nextIndex < log.getSize()) {
        newLogEl = log.getLogEl(nextIndex);
        lastLogEl = log.getLogEl(nextIndex - 1);
      }

      send(otherProcess, new AppendEntries(term, committedLogEl, lastLogEl, newLogEl));
    }
  }

  public void tryNominate() {
    if (!isLeaderRelevant()) {
      updateTimeout();
      if (state != ProcessState.Candidate) {
        state = ProcessState.Candidate;
        term++;
        votesReceived = 1;
        votedForEpoch = term;
      }

      nominatedForEpoch = term;

      for (String otherProcess : otherProcessesInCluster) {
        if (otherProcess.equals(getId())) continue;

        send(otherProcess, new VoteMessage(term, log.getSize() - 1));
      }
    }
  }

  public void handleReplyEntries(ReplyEntries re) {
    if (term > re.epoch) return;

    LogElement confEl = re.confEl;
    LogElement lastLogEl = log.getLastLogEl();
    if (confEl != null && confEl.equals(lastLogEl)) {
      numReceiversLastLogEl++;
      if (!lastLogEl.committed && numReceiversLastLogEl > majority) {
        lastLogEl.committed = true;
        lastCommittedLogElement = lastLogEl;
        handleOperation(lastLogEl);
      }
    }

    nextIndexes.put(re.sender, re.nextIndex);
  }

  @Override
  public void act() {
    wakeCount++;

    while (!inbox.isEmpty()) {
      Message m = inbox.poll();
      if (m instanceof VoteMessage vm) {
        handleVoteMessage(vm);
      }
      else if (m instanceof ReplyVoteMessage rvm) {
        handleReplyVoteMessage(rvm);
      }
      else if (m instanceof AppendEntries ae) {
        handleAppendEntries(ae);
      }
      else if (m instanceof ReplyEntries re) {
        handleReplyEntries(re);
      }
      else if (m instanceof ClientRequestWhoIsLeader crwil) {
        handleRequestWhoIsLeader(crwil);
      }
      else if (m instanceof ClientRequestWithContent) {
        ClientRequestWithContent<StoreOperationEnums, Pair<String, String>> crwc =
                (ClientRequestWithContent<StoreOperationEnums, Pair<String, String>>) m;
        handleRequestWithContent(crwc);
      }
    }

    trySendAppendEntries();
    tryNominate();
  }
}
