package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Message;

public class VoteMessageResponse extends Message {
    public int term;
    public boolean voteGranted;

    public VoteMessageResponse(int term, boolean voteGranted) {
        this.term = term;
        this.voteGranted = voteGranted;
    }
}
