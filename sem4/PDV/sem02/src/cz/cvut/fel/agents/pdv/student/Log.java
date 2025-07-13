package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.dsand.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

public class Log {
    private List<LogElement> log;

    public Log (List<LogElement> log) {
        this.log = log;
    }

    public int getSize() {
        return log.size();
    }

    public LogElement getLogEl(int indx) {
        if (indx < 0 || indx >= log.size()) return null;

        return log.get(indx);
    }

    public LogElement getFirstLogEl() {
        if (getSize() == 0) return null;

        return log.getFirst();
    }

    public LogElement getLastLogEl() {
        if (getSize() == 0) return null;

        return log.getLast();
    }

    public boolean contains(LogElement logEl) {
        return log.contains(logEl);
    }

    public int getLogElEpoch(int indx) {
        if (indx < 0 || indx >= log.size()) return -1;

        return log.get(indx).epoch;
    }

    public int getLastLogElEpoch() {
        if (getSize() == 0) return -1;

        return log.getLast().epoch;
    }

    public boolean addLogEl(LogElement logElement) {
        if (logElement == null) {
            return false;
        }

        logElement.logIndx = getSize();

        return log.add(logElement);
    }

    public void removeLastLogEl() {
        if (log.isEmpty()) return;
        log.removeLast();
    }

    public void removeFirstLogEl() {
        if (log.isEmpty()) return;

        log.removeFirst();
    }

    public boolean cutLog(int fromIndx, int toIndx) {
        if (fromIndx < 0 || fromIndx >= log.size()
                || toIndx < 0 || toIndx >= log.size()
                || fromIndx > toIndx) return false;

        log.subList(fromIndx, toIndx + 1).clear();
        return true;
    }

    public boolean commitLogEl(LogElement committedLogEl) {
        int size = log.size();
        if (size == 0 || committedLogEl == null) return false;

        LogElement last = getLastLogEl();
        if (last.equals(committedLogEl)) {
            if (last.committed) return false;

            last.committed = true;
            return true;
        }

        return false;
    }

    public boolean isLastElCommitted() {
        return getSize() == 0 || getLastLogEl().committed;
    }

    public boolean isEmpty() {
        return getSize() == 0;
    }
}
