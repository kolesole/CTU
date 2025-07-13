package cz.cvut.fel.pjv;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

/**Class with additions to the regular logger class.*/
public class MyLogger {

    /**fileHandler in FileHandler type*/
    private static FileHandler fileHandler;

    /**Default constructor without parameters.*/
    public MyLogger() {
    }

    /**Method to enable a logging and creat a file for write with parameters.
     * @param logger in type Logger for create writing to file from this logger.
     * @param fileName in type String for writing logger messages.
     * @throws IOException method throws IOException.
     * */
    public void enableLogging(Logger logger, String fileName) throws IOException {
        if (!Files.exists(Path.of(fileName)) || logger == null) {
            Files.deleteIfExists(Path.of(fileName));
            try {
                fileHandler = new FileHandler(fileName, true);
                fileHandler.setFormatter(new SimpleFormatter());
                logger.addHandler(fileHandler);
            } catch (IOException e) {
                logger.log(Level.SEVERE, "Failed to set up logger", e);
            }
        }
        logger.setLevel(Level.ALL);
    }

    /**Method to disable a logging with parameters.
     * @param logger in type Logger to be deleted.
     */
    public void disableLogging(Logger logger) {
        logger.setLevel(Level.OFF);
    }
}