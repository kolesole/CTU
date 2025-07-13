package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Message;

public class VoteMessage extends Message {
    int epoch;
    int lastIndx;

    public VoteMessage(int epoch, int lastIndx) {
        this.epoch = epoch;
        this.lastIndx = lastIndx;
    }
}
