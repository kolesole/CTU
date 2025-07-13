package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Message;

public class AppendEntries extends Message {
    public int epoch;
    public LogElement committedLogEl;
    public LogElement lastLogEl;
    public LogElement newLogEl;

    public AppendEntries(int epoch, LogElement committedLogEl, LogElement lastLogEl, LogElement newLogEl) {
        this.epoch = epoch;
        this.committedLogEl = committedLogEl;
        this.lastLogEl = lastLogEl;
        this.newLogEl = newLogEl;
    }
}
