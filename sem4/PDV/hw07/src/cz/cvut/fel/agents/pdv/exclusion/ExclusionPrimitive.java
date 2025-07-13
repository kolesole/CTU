package cz.cvut.fel.agents.pdv.exclusion;

import cz.cvut.fel.agents.pdv.clocked.ClockedMessage;
import cz.cvut.fel.agents.pdv.clocked.ClockedProcess;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class ExclusionPrimitive {

    /**
     * Stavy, ve kterych se zamek muze nachazet.
     */
    enum AcquisitionState {
        RELEASED,    // Uvolneny   - Proces, ktery vlastni aktualni instanci ExclusionPrimitive o pristup do kriticke
                     //              sekce nezada

        WANTED,      // Chteny     - Proces, ktery vlastni aktualni instanci ExclusionPrimitive zada o pristup do
                     //              kriticke sekce. Ten mu ale zatim nebyl odsouhlasen ostatnimi procesy.

        HELD         // Vlastneny  - Procesu bylo prideleno pravo pristupovat ke sdilenemu zdroji.
    }

    private ClockedProcess owner;            // Proces, ktery vlastni aktualni instanci ExclusionPrimitive

    private String criticalSectionName;      // Nazev kriticke sekce. POZOR! V aplikaci se muze nachazet vice kritickych
                                             // sekci s ruznymi nazvy!

    private String[] allAccessingProcesses;  // Seznam vsech procesu, ktere mohou chtit pristupovat ke kriticke sekci
                                             // s nazvem 'criticalSectionName' (a tak spolurozhoduji o udelovani pristupu)

    private AcquisitionState state;          // Aktualni stav zamku (vzhledem k procesu 'owner').
                                             // state==HELD znamena, ze proces 'owner' muze vstoupit do kriticke sekce

    private Set<String> acceptedProcesses;

    private Set<String> waitingProcesses;

    private int requestTime;

    // Doplnte pripadne vlastni datove struktury potrebne pro implementaci
    // Ricart-Agrawalova algoritmu pro vzajemne vylouceni

    public ExclusionPrimitive(ClockedProcess owner, String criticalSectionName, String[] allProcesses) {
        this.owner = owner;
        this.criticalSectionName = criticalSectionName;
        this.allAccessingProcesses = allProcesses;

        this.acceptedProcesses = new HashSet<>();
        this.waitingProcesses = new HashSet<>();

        // Na zacatku je zamek uvolneny
        this.state = AcquisitionState.RELEASED;
    }

    /**
     * Metoda pro zpracovani nove prichozi zpravy
     *
     * @param m    prichozi zprava
     * @return 'true', pokud je zprava 'm' relevantni pro aktualni kritickou sekci.
     */
    public boolean accept(ClockedMessage m) {
        owner.increaseTime();
        if (m instanceof RequestMessage) {
            RequestMessage requestMessage = (RequestMessage)m;

            if (!requestMessage.getCriticalSectionName().equals(criticalSectionName)) {
                return false;
            }

            String sender = requestMessage.sender;
            int sentTime = requestMessage.sentOn;

            if (state == AcquisitionState.HELD || (state == AcquisitionState.WANTED
                    && (requestTime < sentTime || (sentTime == requestTime && owner.id.compareTo(sender) < 0)))) {
                waitingProcesses.add(sender);
            } else {
                owner.send(sender, new ReplyMessage(criticalSectionName));
            }

            return true;
        }
        else if (m instanceof ReplyMessage) {
            ReplyMessage replyMessage = (ReplyMessage)m;

            if (!replyMessage.getCriticalSectionName().equals(criticalSectionName)) {
                return false;
            }

            acceptedProcesses.add(replyMessage.sender);
            if (acceptedProcesses.size() == allAccessingProcesses.length - 1) {
                state = AcquisitionState.HELD;
            }

            return true;
        }

        return false;
    }

    public void requestEnter() {
        state = AcquisitionState.WANTED;
        owner.increaseTime();
        requestTime = owner.getTime();
        acceptedProcesses.clear();

        for (String process : allAccessingProcesses) {
            if (!process.equals(owner.id)) {
                owner.send(process, new RequestMessage(criticalSectionName));
            }
        }
    }

    public void exit() {
        state = AcquisitionState.RELEASED;
        owner.increaseTime();
        for (String process : waitingProcesses) {
            owner.send(process, new ReplyMessage(criticalSectionName));
        }

        waitingProcesses.clear();
    }

    public String getName() {
        return criticalSectionName;
    }

    public boolean isHeld() {
        return state == AcquisitionState.HELD;
    }

}
