package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Pair;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Log {
    private List<LogElement> log;

    public Log () {
        this.log = new ArrayList<LogElement>();
    }

    public int getSize() {
        return log.size();
    }

    public boolean isEmpty() { return getSize() == 0; }

    public LogElement getLastCommitted() {
        for (int i = getSize() - 1; i >= 0; i--) {
            if (log.get(i).committed) return log.get(i);
        }

        return null;
    }

    public LogElement getLogElByIndex(int indx) {
        if (indx < 0 || indx >= log.size()) return null;

        return log.get(indx);
    }

    public LogElement getLogElById(String requestId) {
        for (LogElement el : log) {
            if (el.requestID.equals(requestId)) return el;
        }

        return null;
    }

    public boolean addLogEl(LogElement logElement) {
        if (logElement == null) {
            return false;
        }

        logElement.logIndx = getSize();

        return log.add(logElement);
    }

    public boolean cutLog(int fromIndx, int toIndx) {
        if (fromIndx < 0 || fromIndx >= log.size()
                || toIndx < 0 || toIndx >= log.size()
                || fromIndx > toIndx) return false;

        log.subList(fromIndx, toIndx + 1).clear();
        return true;
    }

    public void commitLogEl(String idLogElement) {
        for (LogElement logEl : log) {
            if (logEl.requestID.equals(idLogElement)) {
                logEl.committed = true;
            }
        }
    }

    public List<LogElement> getEntriesFrom(int index) {
        if (index < 0 || index >= log.size()) {
            return Collections.emptyList();
        }
        return new ArrayList<>(log.subList(index, log.size()));
    }

    public int getTermAtIndex(int index) {
        if (index < 0 || index >= log.size()) {
            return -1;
        }
        return log.get(index).term;
    }

    public LogElement getLastLogEl() {
        if (log.isEmpty()) return null;

        return log.getLast();
    }

    public int getLastIndex() {
        return log.size() - 1;
    }

    public int getLastTerm() {
        if (log.isEmpty()) {
            return -1;
        }
        return log.get(log.size() - 1).term;
    }
}

