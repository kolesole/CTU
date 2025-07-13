package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Message;

public class AppendEntriesResponse extends Message {
    public int term;
    public boolean success;
    public int matchIndex;

    public AppendEntriesResponse(int term, boolean success, int matchIndex) {
        this.term = term;
        this.success = success;
        this.matchIndex = matchIndex;
    }
}
