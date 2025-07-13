package cz.cvut.fel.pjv;

import cz.cvut.fel.pjv.view.*;
import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.MouseButton;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.util.Duration;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.logging.Logger;

/**GameApplication class extends Application.*/
public class GameApplication extends Application {
    /**logger for Movement class.*/
    public static final Logger movementLogger = Logger.getLogger(Movement.class.getName());
    /**logger for Collectors class.*/
    public static final Logger collectorsLogger = Logger.getLogger(Collectors.class.getName());
    /**logger for Consumers class.*/
    public static final Logger consumersLogger = Logger.getLogger(Consumers.class.getName());
    /**logger for Crafts class.*/
    public static final Logger craftsLogger = Logger.getLogger(Crafts.class.getName());
    /**logger for gameController class.*/
    public static final Logger gameControllerLogger = Logger.getLogger(GameController.class.getName());
    /**logger for levelChanger class.*/
    public static final Logger levelChangerLogger = Logger.getLogger(LevelChanger.class.getName());
    /**logger for gameApplication class.*/
    public static final Logger gameApplicationLogger = Logger.getLogger(GameApplication.class.getName());
    /**logger for beastThread class.*/
    public static final Logger beastThreadLogger = Logger.getLogger(BeastThread.class.getName());
    /**myLogger in MyLogger type.*/
    private static final MyLogger myLogger = new MyLogger();
    /**gameIsRunning in boolean type.*/
    public static boolean gameIsRunning = false;

    private Timeline timeline;


    /**Method for the 1-st start of the game, which creates loggers without parameters.*/
    @Override
    public void start(Stage stage) throws IOException {
        Files.deleteIfExists(Path.of("Movement.log"));
        Files.deleteIfExists(Path.of("Collectors.log"));
        Files.deleteIfExists(Path.of("Consumers.log"));
        Files.deleteIfExists(Path.of("Crafts.log"));
        Files.deleteIfExists(Path.of("GameController.log"));
        Files.deleteIfExists(Path.of("LevelChanger.log"));
        Files.deleteIfExists(Path.of("GameApplication.log"));
        Files.deleteIfExists(Path.of("BeastThread.log"));
        stage.initStyle(StageStyle.UNDECORATED);
        stage.setTitle("Game");
        showMenu(stage);
    }

    /**Completely the same function as the first start function only without creating logging and with parameters.
     * @param stage main stage in Stage type.
     * @throws IOException method throws IOException.
     */
    public void secondStart(Stage stage) throws IOException {
        stage.initStyle(StageStyle.UNDECORATED);
        stage.setTitle("Game");
        showMenu(stage);
    }

    /**Method that opens the menu scene with parameters.
     * @param stage main stage in Stage type.
     * @throws IOException method throws IOException.
     */
    private void showMenu(Stage stage) throws IOException {
        ImageView backgroundImageView = new ImageView(getClass().getResource("/images/menu/menuBackground.png").toExternalForm());
        backgroundImageView.setFitWidth(1000);
        backgroundImageView.setFitHeight(1000);
        backgroundImageView.setPreserveRatio(true);

        Button playButton = new Button("PLAY");
        Button exitButton = new Button("EXIT");

        playButton.getStyleClass().add("button");
        exitButton.getStyleClass().add("button");

        VBox controlLayout = new VBox(10);
        controlLayout.setAlignment(Pos.CENTER);
        controlLayout.getChildren().addAll(playButton, exitButton);

        CheckBox loggingCheckBox = new CheckBox("Enable Logging");

        AnchorPane root = new AnchorPane();
        root.getChildren().addAll(backgroundImageView, controlLayout, loggingCheckBox);

        AnchorPane.setTopAnchor(controlLayout, 200.0);
        AnchorPane.setLeftAnchor(controlLayout, 400.0);

        AnchorPane.setBottomAnchor(loggingCheckBox, 10.0);
        AnchorPane.setRightAnchor(loggingCheckBox, 10.0);

        Scene mainMenuScene = new Scene(root, 1000, 560);
        mainMenuScene.getStylesheets().add(getClass().getResource("styles.css").toExternalForm());

        playButton.setOnAction(e -> {
            try {
                if (loggingCheckBox.isSelected()) {
                    myLogger.enableLogging(movementLogger, "Movement.log");
                    myLogger.enableLogging(collectorsLogger, "Collectors.log");
                    myLogger.enableLogging(consumersLogger, "Consumers.log");
                    myLogger.enableLogging(craftsLogger, "Crafts.log");
                    myLogger.enableLogging(gameControllerLogger, "GameController.log");
                    myLogger.enableLogging(levelChangerLogger, "LevelChanger.log");
                    myLogger.enableLogging(gameApplicationLogger, "GameApplication.log");
                    myLogger.enableLogging(beastThreadLogger, "BeastThread.log");
                } else {
                    myLogger.disableLogging(movementLogger);
                    myLogger.disableLogging(collectorsLogger);
                    myLogger.disableLogging(consumersLogger);
                    myLogger.disableLogging(craftsLogger);
                    myLogger.disableLogging(gameControllerLogger);
                    myLogger.disableLogging(levelChangerLogger);
                    myLogger.disableLogging(gameApplicationLogger);
                    myLogger.disableLogging(beastThreadLogger);
                }
                gameIsRunning = true;
                gameApplicationLogger.info("Start game");
                showGame(stage);
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        exitButton.setOnAction(e -> {
            gameApplicationLogger.info("Exit the game");
            stage.close();
        });

        stage.setScene(mainMenuScene);
        stage.show();
    }

    /**Method that opens the game scene with parameters.
     * @param stage main stage in Stage type.
     * @throws IOException method throws IOException.
     */
    private void showGame(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(GameApplication.class.getResource("game-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 800, 687);
        stage.setScene(scene);
        GameController controller = fxmlLoader.getController();
        controller.setStage(stage);
        scene.setOnKeyPressed(event -> {
            if (event.getCode() == KeyCode.W) {
                GameController.up = true;
                GameController.playerDirectionIsUp = true;
                GameController.playerDirectionIsRight = false;
                GameController.playerDirectionIsDown = false;
                GameController.playerDirectionIsLeft = false;
                gameApplicationLogger.info("Player pressed W");
            }
            if (event.getCode() == KeyCode.D) {
                GameController.right = true;
                GameController.playerDirectionIsUp = false;
                GameController.playerDirectionIsRight = true;
                GameController.playerDirectionIsDown = false;
                GameController.playerDirectionIsLeft = false;
                gameApplicationLogger.info("Player pressed D");
            }
            if (event.getCode() == KeyCode.S) {
                GameController.down = true;
                GameController.playerDirectionIsUp = false;
                GameController.playerDirectionIsRight = false;
                GameController.playerDirectionIsDown = true;
                GameController.playerDirectionIsLeft = false;
                gameApplicationLogger.info("Player pressed S");
            }
            if (event.getCode() == KeyCode.A) {
                GameController.left = true;
                GameController.playerDirectionIsUp = false;
                GameController.playerDirectionIsRight = false;
                GameController.playerDirectionIsDown = false;
                GameController.playerDirectionIsLeft = true;
                gameApplicationLogger.info("Player pressed A");

            }
            if (event.getCode() == KeyCode.E) {
                GameController.collectAnApple = true;
                GameController.collectAWheat = true;
                GameController.collectAWater = true;
                GameController.collectAMeat = true;
                gameApplicationLogger.info("Player pressed E");
            }
            if (event.getCode() == KeyCode.R) {
                GameController.isInventoryOpen = !GameController.isInventoryOpen;
                if (GameController.isInventoryOpen) {
                    gameControllerLogger.info("Inventory opened");
                } else {
                    gameControllerLogger.info("Inventory closed");
                }
                gameApplicationLogger.info("Player pressed R");
            }
            if (event.getCode() == KeyCode.ESCAPE) {
                try {
                    gameApplicationLogger.info("Return to menu");
                    gameApplicationLogger.info("Player pressed ESCAPE");
                    timeline.stop();
                    controller.stopAnimationTimer();
                    stage.close();
                    gameIsRunning = false;
                    secondStart(new Stage());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
        });

        scene.setOnMouseClicked(mouseEvent -> {
            if (mouseEvent.getButton() == MouseButton.PRIMARY) {
                GameController.hit = true;
                gameApplicationLogger.info("Player pressed LMB");
            }
        });

        scene.setOnKeyReleased(event -> {
            if (event.getCode() == KeyCode.W) {
                GameController.up = false;
                gameApplicationLogger.info("Player released W");
            }
            if (event.getCode() == KeyCode.D) {
                GameController.right = false;
                gameApplicationLogger.info("Player released D");
            }
            if (event.getCode() == KeyCode.S) {
                GameController.down = false;
                gameApplicationLogger.info("Player released S");
            }
            if (event.getCode() == KeyCode.A) {
                GameController.left = false;
                gameApplicationLogger.info("Player released A");
            }
            if (event.getCode() == KeyCode.E) {
                GameController.collectAnApple = false;
                GameController.collectAWheat = false;
                GameController.collectAWater = false;
                GameController.collectAMeat = false;
                gameApplicationLogger.info("Player released E");
            }
        });

        scene.setOnMouseReleased(mouseEvent -> {
            if (mouseEvent.getButton() == MouseButton.PRIMARY) {
                GameController.hit = false;
                gameApplicationLogger.info("Player released LBM");
            }
        });

        timeline = new Timeline(
                new KeyFrame(Duration.seconds(30), event -> {GameController.player.changeThirstLvl(-1); gameApplicationLogger.info("PLayer has lost one point of thirst level");})
        );
        timeline.setCycleCount(Animation.INDEFINITE);
        timeline.play();
        stage.show();
    }

    /**Main method.*/
    public static void main(String[] args) {
        launch();
    }
}