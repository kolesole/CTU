package cz.cvut.fel.pjv.view;

import cz.cvut.fel.pjv.model.Actions;
import cz.cvut.fel.pjv.model.characters.Knight;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.control.Label;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import javafx.util.Duration;

import static cz.cvut.fel.pjv.GameApplication.consumersLogger;

/**Class that is responsible for consumption of food and water.*/
public class Consumers {

    /**Default constructor without parameters.*/
    public Consumers() {

    }

    /**Method that is responsible for water consumption with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param actions parameter for all possible actions.
     * @param player player in type Knight.
     * @param infoLabel infoLabel in Label type for messages to the player.
     * @param quantityOfWater quantityOfWater in type Label for displaying the number of water in inventory.
     */
    public void drinkWater(MouseEvent event, Actions actions, Knight player, Label infoLabel, Label quantityOfWater) {
        if (event.getButton() == MouseButton.SECONDARY) {
            consumersLogger.info("Player trying to drink water");
            if (!actions.drinkWater(player)) {
                infoLabel.setText("You cant drink water!");
                infoLabel.setTextFill(Color.BLACK);
                consumersLogger.warning("Player was unable to drink water!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoLabel.setText("Inventory"); infoLabel.setTextFill(Color.web("#a96308")); }));
                timeline.play();
                return;
            }
            infoLabel.setText("You quenched your thirst");
            infoLabel.setTextFill(Color.BLACK);
            consumersLogger.info("Player managed to drink water");
            quantityOfWater.setText(String.valueOf(Integer.parseInt(quantityOfWater.getText()) - 1));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoLabel.setText("Inventory"); infoLabel.setTextFill(Color.web("#a96308")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for apple consumption with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param actions parameter for all possible actions.
     * @param player player in type Knight.
     * @param infoLabel infoLabel in Label type for messages to the player.
     * @param quantityOfApple quantityOfApple in type Label for displaying the number of apples in inventory.
     */
    public void eatApple(MouseEvent event, Actions actions, Knight player, Label infoLabel, Label quantityOfApple) {
        if (event.getButton() == MouseButton.SECONDARY) {
            consumersLogger.info("Player trying to eat an apple");
            if (!actions.eatApple(player)) {
                infoLabel.setText("You cant eat an apple!");
                infoLabel.setTextFill(Color.BLACK);
                consumersLogger.warning("Player was unable to eat an apple!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoLabel.setText("Inventory"); infoLabel.setTextFill(Color.web("#a96308")); }));
                timeline.play();
                return;
            }
            infoLabel.setText("You have regained your hp on 1!");
            infoLabel.setTextFill(Color.BLACK);
            consumersLogger.info("Player managed to eat an apple");
            quantityOfApple.setText(String.valueOf(Integer.parseInt(quantityOfApple.getText()) - 1));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoLabel.setText("Inventory"); infoLabel.setTextFill(Color.web("#a96308")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for pie consumption with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param actions parameter for all possible actions.
     * @param player player in type Knight.
     * @param infoLabel infoLabel in Label type for messages to the player.
     * @param quantityOfPie quantityOfPie in type Label for displaying the number of pie in inventory.
     */
    public void eatPie(MouseEvent event, Actions actions, Knight player, Label infoLabel, Label quantityOfPie) {
        if (event.getButton() == MouseButton.SECONDARY) {
            consumersLogger.info("Player trying to eat a pie");
            if (!actions.eatPie(player)) {
                infoLabel.setText("You cant eat a pie!");
                infoLabel.setTextFill(Color.BLACK);
                consumersLogger.warning("Player was unable to eat a pie!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoLabel.setText("Inventory"); infoLabel.setTextFill(Color.web("#a96308")); }));
                timeline.play();
                return;
            }
            infoLabel.setText("You have regained your hp on 3!");
            infoLabel.setTextFill(Color.BLACK);
            consumersLogger.info("Player managed to eat a pie");
            quantityOfPie.setText(String.valueOf(Integer.parseInt(quantityOfPie.getText()) - 1));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoLabel.setText("Inventory"); infoLabel.setTextFill(Color.web("#a96308")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for soup consumption with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param actions parameter for all possible actions.
     * @param player player in type Knight.
     * @param infoLabel infoLabel in Label type for messages to the player.
     * @param quantityOfSoup quantityOfSoup in type Label for displaying the number of soup in inventory.
     */
    public void eatSoup(MouseEvent event, Actions actions, Knight player, Label infoLabel, Label quantityOfSoup) {
        if (event.getButton() == MouseButton.SECONDARY) {
            consumersLogger.info("Player trying to eat a soup");
            if (!actions.eatSoup(player)) {
                infoLabel.setText("You cant eat a soup!");
                infoLabel.setTextFill(Color.BLACK);
                consumersLogger.warning("Player was unable to eat a soup!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoLabel.setText("Inventory"); infoLabel.setTextFill(Color.web("#a96308")); }));
                timeline.play();
                return;
            }
            infoLabel.setText("You have regained your hp on 5!");
            infoLabel.setTextFill(Color.BLACK);
            consumersLogger.info("Player managed to eat a soup");
            quantityOfSoup.setText(String.valueOf(Integer.parseInt(quantityOfSoup.getText()) - 1));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoLabel.setText("Inventory"); infoLabel.setTextFill(Color.web("#a96308")); }));
            timeline.play();
        }
    }
}
