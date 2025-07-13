package cz.cvut.fel.agents.pdv.swim;

import cz.cvut.fel.agents.pdv.dsand.Message;
import cz.cvut.fel.agents.pdv.dsand.Pair;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Random;
import java.util.stream.Collectors;

public class ActStrategy {

    private final int maxDelayForMessages;     // max delay
    private final List<String> otherProcesses; // list of processes

    private Map<String, Integer> pingedProcesses;      // processes which were pinged by this process
    private Map<String, Pair<String, Integer>> checkedProcesses;    // processes which were asked for check
    private List<String> deadProcesses;                // list of dead processes

    private Random randomGen;            // random generator
    private int wakeCount = 0;           // current tick
    private String id = "";              // id

    public ActStrategy(int maxDelayForMessages, List<String> otherProcesses,
                       int timeToDetectKilledProcess, int upperBoundOnMessages) {
        this.maxDelayForMessages = maxDelayForMessages;
        this.otherProcesses = otherProcesses;
        this.pingedProcesses = new HashMap<>();
        this.checkedProcesses = new HashMap<>();
        this.deadProcesses = new ArrayList<>();
        this.randomGen = new Random();
    }

    // Method generates List of K alive processes
    private List<String> getRandomProcesses(int K) {
        List<String> aliveProcesses = otherProcesses.stream()
                .filter(p -> !deadProcesses.contains(p))
                .collect(Collectors.toList());
        List<String> ret = new ArrayList<>();
        K = Math.min(K, aliveProcesses.size());
        for (int i = 0; i < K; i++) {
            while (true) {
                String randomProcess = aliveProcesses.get(randomGen.nextInt(aliveProcesses.size()));
                if (!ret.contains(randomProcess)) {
                    ret.add(randomProcess);
                    break;
                }
            }
        }
        return ret;
    }

    // act method
    public List<Pair<String, Message>> act(Queue<Message> inbox, String disseminationProcess) {
        List<Pair<String, Message>> outbox = new ArrayList<>();

        while (!inbox.isEmpty()) {
            Message m = inbox.poll();

            // setting current id
            if (id.equals("")) {
                id = m.recipient;
                otherProcesses.remove(id);
            }

            // receiving a new dead process
            if (m instanceof DeadProcessMessage) {
                String deadProcess = ((DeadProcessMessage) m).getProcessID();
                deadProcesses.add(deadProcess);
                // otherProcesses.remove(deadProcess);

                pingedProcesses.remove(deadProcess);
                checkedProcesses.remove(deadProcess);
            }

            // ping message reply
            else if (m instanceof PingMessage) {
                String sender = m.sender;

                pingedProcesses.remove(sender);
                checkedProcesses.remove(sender);

                if (deadProcesses.contains(sender)) continue;

                outbox.add(new Pair<>(sender, new ReplyPingMessage()));
            }
            // receiving reply to a ping message
            else if (m instanceof ReplyPingMessage) {
                String sender = m.sender;

                pingedProcesses.remove(sender);

                if (deadProcesses.contains(sender)) continue;

                if (checkedProcesses.containsKey(sender)) {
                    Pair<String, Integer> pair = checkedProcesses.get(sender);
                    if (!deadProcesses.contains(pair.getFirst())) {
                        outbox.add(new Pair<>(pair.getFirst(), new ReplyCheckMessage(sender)));
                    }
                    checkedProcesses.remove(sender);
                }
            }
            // receiving a check message
            else if (m instanceof CheckMessage) {
                String sender = m.sender;
                String processToCheck = ((CheckMessage) m).getProcessID();

                if (deadProcesses.contains(sender)
                        || deadProcesses.contains(processToCheck)) continue;

                checkedProcesses.put(processToCheck, new Pair<>(sender, wakeCount));
                outbox.add(new Pair<>(processToCheck, new PingMessage()));
            }
            // receiving reply to a check message
            else if (m instanceof ReplyCheckMessage) {
                String checkedProcess = ((ReplyCheckMessage) m).getProcessID();

                pingedProcesses.remove(checkedProcess);
                checkedProcesses.remove(checkedProcess);
            }
        }

        // checking pinged processes
        Map<String, Integer> pingedProcessesCopy = new HashMap<>(pingedProcesses);
        for (String process : pingedProcessesCopy.keySet()) {
            if (deadProcesses.contains(process)) {
                pingedProcesses.remove(process);
                checkedProcesses.remove(process);
                continue;
            }

            int sendTime = pingedProcesses.get(process);
            if (wakeCount - sendTime > 7 * maxDelayForMessages) {
                pingedProcesses.remove(process);
                checkedProcesses.remove(process);
                outbox.add(new Pair<>(disseminationProcess, new PFDMessage(process)));
            }
            else if (wakeCount - sendTime == 3 * maxDelayForMessages) {
                List<String> randomProcesses = getRandomProcesses(7);
                for (String randomProcess : randomProcesses) {
                    outbox.add(new Pair<>(randomProcess, new CheckMessage(process)));
                }
            }
        }

        //checking checked processes
        Map<String, Pair<String, Integer>> checkedProcessesCopy = new HashMap<>(checkedProcesses);
        for (String process : checkedProcessesCopy.keySet()) {
            if (deadProcesses.contains(process)) {
                checkedProcesses.remove(process);
                pingedProcesses.remove(process);
                continue;
            }

            Pair<String, Integer> pair = checkedProcesses.get(process);

            if (deadProcesses.contains(pair.getFirst())) {
                checkedProcesses.remove(process);
                pingedProcesses.remove(process);
                continue;
            }

            int sendTime = checkedProcesses.get(process).getSecond();
            if (wakeCount - sendTime > 7 * maxDelayForMessages) {
                checkedProcesses.remove(process);
                pingedProcesses.remove(process);
            }
        }

        // sending a ping message to a random process
        if (wakeCount % 2 == 1) {
            String randomProcess = getRandomProcesses(1).get(0);
            outbox.add(new Pair<>(randomProcess, new PingMessage()));
            pingedProcesses.put(randomProcess, wakeCount);
        }

        wakeCount++;

        return outbox;
    }

}
