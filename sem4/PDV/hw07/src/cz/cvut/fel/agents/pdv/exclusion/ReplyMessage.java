package cz.cvut.fel.agents.pdv.exclusion;

import cz.cvut.fel.agents.pdv.clocked.ClockedMessage;

public class ReplyMessage extends ClockedMessage {
    private String criticalSectionName;

    public ReplyMessage(String criticalSectionName) {
        this.criticalSectionName = criticalSectionName;
    }

    public String getCriticalSectionName() {
        return criticalSectionName;
    }
}
