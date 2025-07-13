package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Message;

public class ReplyEntries extends Message {
    public int epoch;
    public boolean success;
    public int matchIndex;

    public ReplyEntries(int epoch, boolean success, int matchIndex) {
        this.epoch = epoch;
        this.success = success;
        this.matchIndex = matchIndex;
    }
}
