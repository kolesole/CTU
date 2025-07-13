package cz.cvut.fel.agents.pdv.swim;

import cz.cvut.fel.agents.pdv.dsand.Message;

public class CheckMessage extends Message {
    private final String processID;

    public CheckMessage(String processID) {
        this.processID = processID;
    }

    public String getProcessID() {
        return processID;
    }
}
