package cz.cvut.fel.agents.pdv.student;

import cz.cvut.fel.agents.pdv.raft.messages.IOperation;

import java.io.Serializable;
import java.util.List;

public class LogElement implements Serializable {
    public final int epoch;
    public final String clientID;
    public final String requestID;
    public final String operation;
    public final String key;
    public final String value;
    public boolean committed;
    public String result;
    public int logIndx;

    public LogElement(int epoch, String clientID, String requestID, IOperation operation, String key, String value) {
        this.epoch = epoch;
        this.clientID = clientID;
        this.requestID = requestID;
        this.operation = operation.toString();
        this.key = key;
        this.value = value;
        this.committed = false;
    }

    @Override
    public boolean equals(Object o) {
        if (!(o instanceof LogElement)) return false;

        return this.requestID.equals(((LogElement) o).requestID);
    }

    @Override
    public int hashCode() {
        return requestID.hashCode();
    }
}
