package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Message;

import java.util.*;

public class AppendEntries extends Message {
    public final int term;
    public final String leaderId;
    public final int prevLogIndex;
    public final int prevLogTerm;
    public final List<LogElement> entries;
    public final int leaderCommit;

    public AppendEntries(int term, String leaderId, int prevLogIndex,
                         int prevLogTerm, List<LogElement> entries,
                         int leaderCommit) {
        this.term = term;
        this.leaderId = leaderId;
        this.prevLogIndex = prevLogIndex;
        this.prevLogTerm = prevLogTerm;
        this.entries = new ArrayList<>(entries);
        this.leaderCommit = leaderCommit;
    }

}
