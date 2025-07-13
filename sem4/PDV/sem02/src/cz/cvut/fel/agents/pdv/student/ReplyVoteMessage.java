package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Message;

public class ReplyVoteMessage extends Message {
    public int epoch;

    public ReplyVoteMessage(int epoch) {
        this.epoch = epoch;
    }
}
