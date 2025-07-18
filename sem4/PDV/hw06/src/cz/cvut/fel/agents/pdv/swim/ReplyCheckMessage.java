package cz.cvut.fel.agents.pdv.swim;

import cz.cvut.fel.agents.pdv.dsand.Message;

public class ReplyCheckMessage extends Message {
    private final String processID;

    public ReplyCheckMessage(String processID) {
        this.processID = processID;
    }

    public String getProcessID() {
        return processID;
    }
}
