package cz.cvut.fel.agents.pdv.bfs;

import cz.cvut.fel.agents.pdv.demo.DummyMessage;
import cz.cvut.fel.agents.pdv.dsand.DSProcess;
import cz.cvut.fel.agents.pdv.dsand.Message;

import java.util.List;
import java.util.Queue;
import java.util.function.BiConsumer;

public class BFSProcess extends DSProcess {

    /**
     * Seznam nasledniku uzlu spravovaneho aktualnim procesem
     */
    private List<String> neighbors;

    /**
     * Je uzel spravovany aktualnim procesem 'root' prohledavani?
     */
    private boolean isRoot;

    /**
     * Je uzel spravovany aktualnim procesem cilovym uzlem?
     */
    private boolean isGoal;


    /**
     * Identifikator predchazejiciho procesu ('uzlu' na nejkratsi ceste)
     */
    private String predecessor = null;

    public BFSProcess(String id, Queue<Message> inbox, BiConsumer<String, Message> outbox,
                      List<String> neighbors, boolean isRoot, boolean isGoal) {
        super(id, inbox, outbox);
        this.neighbors = neighbors;
        this.isRoot = isRoot;
        this.isGoal = isGoal;

        // Pro jednoduchost nastavime predchazeji proces korene na koren samotny.
        // if(isRoot) predecessor = id;
    }

    @Override
    public void act() {
        /*
            Doplnte algoritmus, ktery bude vykonavat kazdy proces

            1) Zpracujte prichozi zpravy v 'inbox'
            2) Vytvorte tridy pro posilane zpravy
            3) Doplnte logiku reakce na zpravu a odeslani novych zprav
         */

        if (isRoot && predecessor == null) {
            predecessor = id;
            for (String neighbor : neighbors) {
                send(neighbor, new BfsMessage());
            }
        }

        while (!inbox.isEmpty()) {
            Message m = inbox.poll();

            if (m instanceof BfsMessage) {
                if (predecessor == null) {
                    predecessor = m.sender;
                    for (String neighbor : neighbors) {
                        send(neighbor, new BfsMessage());
                    }
                    if (isGoal) {
                        System.out.println("Goal reached");
                        // terminateAll();
                        send(predecessor, new PMessage(id));
                        return;
                    }
                    for (String neighbor : neighbors) {
                        if (!neighbor.equals(m.sender)) {
                            send(neighbor, new BfsMessage());
                        }
                    }
                }
            }
            else if (m instanceof PMessage) {
                PMessage path = (PMessage) m;

                if (isRoot){
                    System.out.println("Path: " + id + ", " + path.getPath());
                    terminateAll();
                } else {
                    send(predecessor, new PMessage(id + ", " + path.getPath()));
                }
            }
        }
    }

    @Override
    public boolean isTerminated() {
        return false;
    }
}
