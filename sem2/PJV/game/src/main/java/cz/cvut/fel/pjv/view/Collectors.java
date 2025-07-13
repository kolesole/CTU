package cz.cvut.fel.pjv.view;

import cz.cvut.fel.pjv.model.Actions;
import cz.cvut.fel.pjv.model.characters.Beast;
import cz.cvut.fel.pjv.model.characters.Knight;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.util.Duration;

import static cz.cvut.fel.pjv.GameApplication.collectorsLogger;

/**Class that is responsible for collecting items.*/
public class Collectors {

    /**Default constructor without parameters.*/
    public Collectors() {

    }

    /**Method that is responsible for collecting an apple with parameters.
     * @param apples array with all (ImageView)apples.
     * @param actions parameter for all possible actions.
     * @param playerImage player image.
     * @param player player in Knight type.
     * @param infoLabel infoLabel in Label type for message to the player.
     * @param quantityOfApple quantityOfApple in type Label for displaying the number of apples in inventory.
     */
    public void collectAnApple(ImageView[] apples, Actions actions, ImageView playerImage, Knight player, Label infoLabel, Label quantityOfApple) {
        for (ImageView apple : apples) {
            if (apple.isVisible() && apple.getBoundsInParent().intersects(playerImage.getBoundsInParent())) {
                collectorsLogger.info("Player trying to collect an apple");
                if (!actions.collectAnApple(player)) {
                    infoLabel.setText("Inventory is full");
                    collectorsLogger.warning("Player was unable to collect an apple!");
                    Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                    timeline.play();
                    break;
                }
                apple.setVisible(false);
                infoLabel.setText("+1 apple");
                collectorsLogger.info("Player managed to collect an apple");
                quantityOfApple.setText(String.valueOf(Integer.parseInt(quantityOfApple.getText()) + 1));
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                timeline.play();
            }
        }
    }

    /**Method that is responsible for collecting a wheat with parameters.
     * @param wheat array with all (ImageView)wheat.
     * @param actions for all possible actions.
     * @param playerImage player image.
     * @param player player in Knight type.
     * @param infoLabel infoLabel in Label type for message to the player.
     * @param quantityOfWheat quantityOfWheat in type Label for displaying the number of wheat in inventory.
     */
    public void collectAWheat(ImageView[] wheat, Actions actions, ImageView playerImage, Knight player, Label infoLabel, Label quantityOfWheat) {
        for (ImageView w : wheat) {
            if (w.isVisible() && w.getBoundsInParent().intersects(playerImage.getBoundsInParent())) {
                collectorsLogger.info("Player trying to collect a wheat");
                if (!actions.collectAWheat(player)) {
                    infoLabel.setText("Inventory is full");
                    collectorsLogger.warning("Player was unable to collect a wheat!");
                    Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                    timeline.play();
                    break;
                }
                w.setVisible(false);
                infoLabel.setText("+wheat");
                collectorsLogger.info("Player managed to collect a wheat");
                quantityOfWheat.setText(String.valueOf(Integer.parseInt(quantityOfWheat.getText()) + 1));
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                timeline.play();
            }
        }
    }

    /**Method that is responsible for collecting a water with parameters.
     * @param actions for all possible actions.
     * @param playerImage player image.
     * @param player player in Knight type.
     * @param infoLabel infoLabel in Label type for message to the player.
     * @param quantityOfWater quantityOfWater in type Label for displaying the number of water in inventory.
     */
    public void collectAWater(ImageView playerImage, Knight player, Actions actions, Label infoLabel, Label quantityOfWater) {
        if (playerImage.getLayoutX() < 253 && playerImage.getLayoutY() > 529 && playerImage.getLayoutY() < 561) {
            collectorsLogger.info("Player trying to collect a water");
            if (!actions.collectAWater(player)) {
                infoLabel.setText("Inventory is full");
                collectorsLogger.warning("Player was unable to collect a water!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                timeline.play();
                return;
            }
            infoLabel.setText("+1 water");
            collectorsLogger.info("Player managed to collect a water");
            quantityOfWater.setText(String.valueOf(Integer.parseInt(quantityOfWater.getText()) + 1));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
            timeline.play();
        }
    }

    /**Method that is responsible for collecting a wood with parameters.
     * @param treeTops array with all (ImageView)treeTops.
     * @param treeTrunks array with all (ImageView)treeTrunks.
     * @param actions for all possible actions.
     * @param playerImage player image.
     * @param player player in Knight type.
     * @param infoLabel infoLabel in Label type for message to the player.
     * @param quantityOfWood quantityOfWood in type Label for displaying the number of wood in inventory.
     */
    public void collectAWood(ImageView[] treeTops, ImageView[] treeTrunks, Actions actions, ImageView playerImage, Knight player, Label infoLabel, Label quantityOfWood) {
        for (int i = 0; i < treeTops.length; i++) {
            if (treeTops[i].isVisible() && treeTops[i].getBoundsInParent().intersects(playerImage.getBoundsInParent())) {
                collectorsLogger.info("Player trying to collect a wood");
                if (!actions.collectAWood(player)) {
                    infoLabel.setText("Inventory is full");
                    collectorsLogger.warning("Player was unable to collect a wood!");
                    Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                    timeline.play();
                    break;
                }
                treeTops[i].setVisible(false);
                treeTrunks[i].setVisible(false);
                infoLabel.setText("+" + player.getIntDamageToMaterials() + " wood");
                collectorsLogger.info("Player managed to collect a wood");
                quantityOfWood.setText(String.valueOf(Integer.parseInt(quantityOfWood.getText()) + player.getIntDamageToMaterials()));
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                timeline.play();
            }
        }
    }

    /**Method that is responsible for collecting an iron with parameters.
     * @param iron array with all (ImageView)iron.
     * @param actions for all possible actions.
     * @param playerImage player image.
     * @param player player in Knight type.
     * @param infoLabel infoLabel in Label type for message to the player.
     * @param quantityOfIron quantityOfIron in type Label for displaying the number of iron in inventory.
     */
    public void collectAnIron(ImageView[] iron, Actions actions, ImageView playerImage, Knight player, Label infoLabel, Label quantityOfIron) {
        for (int i = 0; i < iron.length; i++) {
            if (iron[i].isVisible() && iron[i].getBoundsInParent().intersects(playerImage.getBoundsInParent())) {
                collectorsLogger.info("Player trying to collect an iron");
                if (!actions.collectAnIron(player)) {
                    infoLabel.setText("Inventory is full");
                    collectorsLogger.warning("Player was unable to collect an iron!");
                    Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                    timeline.play();
                    break;
                }
                iron[i].setVisible(false);
                infoLabel.setText("+" + player.getIntDamageToMaterials() + " iron");
                collectorsLogger.info("Player managed to collect an iron");
                quantityOfIron.setText(String.valueOf(Integer.parseInt(quantityOfIron.getText()) + player.getIntDamageToMaterials()));
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                timeline.play();
            }
        }
    }

    /**Method that is responsible for collecting a meat(if boar is dead) with parameters.
     * @param boarsImages array with all (ImageView)boarsImages/.
     * @param boars array with all (Boar)boars.
     * @param actions for all possible actions.
     * @param playerImage player image.
     * @param player player in Knight type.
     * @param infoLabel infoLabel in Label type for message to the player.
     * @param quantityOfMeat quantityOfMeat in type Label for displaying the number of meat in inventory.
     */
    public void collectAMeat(ImageView[] boarsImages, Beast[] boars, Actions actions, ImageView playerImage, Knight player, Label infoLabel, Label quantityOfMeat) {
        for (int i = 0; i < boars.length; i++) {
            if (boarsImages[i].isVisible() && actions.occurrenceOfDeath(boars[i]) && boarsImages[i].getBoundsInParent().intersects(playerImage.getBoundsInParent())) {
                collectorsLogger.info("Player trying to collect a meat");
                if (!actions.collectAMeat(player)) {
                    infoLabel.setText("Inventory is full");
                    collectorsLogger.warning("Player was unable to collect a meat!");
                    Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                    timeline.play();
                    break;
                }
                boarsImages[i].setVisible(false);
                infoLabel.setText("+" + 1 + " meat");
                collectorsLogger.info("Player managed to collect a meat");
                quantityOfMeat.setText(String.valueOf(Integer.parseInt(quantityOfMeat.getText()) + 1));
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> infoLabel.setText("Inventory")));
                timeline.play();
                boarsImages[i].setVisible(false);
            }
        }
    }
}