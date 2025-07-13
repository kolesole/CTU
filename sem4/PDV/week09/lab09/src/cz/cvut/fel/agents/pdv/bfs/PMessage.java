package cz.cvut.fel.agents.pdv.bfs;

import cz.cvut.fel.agents.pdv.dsand.Message;

public class PMessage extends Message {
    String path;

    public PMessage(String path) {
        this.path = path;
    }

    String getPath() {
        return path;
    }
}
