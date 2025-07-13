package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Message;

public class VoteMessage extends Message {
    public int term;
    public String candidateId;
    public int lastLogIndex;
    public int lastLogTerm;

    public VoteMessage(int term, String candidateId, int lastLogIndex, int lastLogTerm) {
        this.term = term;
        this.candidateId = candidateId;
        this.lastLogIndex = lastLogIndex;
        this.lastLogTerm = lastLogTerm;
    }
}
