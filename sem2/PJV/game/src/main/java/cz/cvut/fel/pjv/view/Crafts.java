package cz.cvut.fel.pjv.view;

import cz.cvut.fel.pjv.model.Actions;
import cz.cvut.fel.pjv.model.characters.Knight;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import javafx.util.Duration;

import static cz.cvut.fel.pjv.GameApplication.craftsLogger;

/**Class that is responsible for crafting items.*/
public class Crafts {

    /**Default constructor without parameters.*/
    public Crafts() {

    }

    /**Method that is responsible for crafting a pie with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsDishesLabel infoCraftDishesLabel in Label type for craft dishes messages to the player.
     * @param quantityOfPie quantityOfPie in type Label for displaying the number of pie in inventory.
     * @param quantityOfApple quantityOfApple in type Label for displaying the number of apple in inventory.
     * @param quantityOfWheat quantityOfWheat in type Label for displaying the number of wheat in inventory.
     * @param quantityOfWater quantityOfWater in type Label for displaying the number of water in inventory.
     */
    public void craftAPie(MouseEvent event, Knight player, Actions actions, Label infoCraftsDishesLabel, Label quantityOfPie, Label quantityOfApple, Label quantityOfWheat, Label quantityOfWater) {
        craftsLogger.info("Player trying to craft a pie");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (!actions.craftAPie(player)) {
                infoCraftsDishesLabel.setText("You cant craft a pie!");
                infoCraftsDishesLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a pie!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsDishesLabel.setText("Crafts(Dishes)"); infoCraftsDishesLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsDishesLabel.setText("You crafted a pie!");
            infoCraftsDishesLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft a pie");
            quantityOfPie.setText(String.valueOf(Integer.parseInt(quantityOfPie.getText()) + 1));
            quantityOfApple.setText(String.valueOf(Integer.parseInt(quantityOfApple.getText()) - 2));
            quantityOfWheat.setText(String.valueOf(Integer.parseInt(quantityOfWheat.getText()) - 2));
            quantityOfWater.setText(String.valueOf(Integer.parseInt(quantityOfWater.getText()) - 2));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsDishesLabel.setText("Crafts(Dishes)"); infoCraftsDishesLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for crafting a soup with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsDishesLabel infoCraftDishesLabel in Label type for craft dishes messages to the player.
     * @param quantityOfSoup quantityOfSoup in type Label for displaying the number of soup in inventory.
     * @param quantityOfWater quantityOfWater in type Label for displaying the number of water in inventory.
     * @param quantityOfMeat quantityOfMeat in type Label for displaying the number of meat in inventory.
     */
    public void craftASoup(MouseEvent event, Knight player, Actions actions, Label infoCraftsDishesLabel, Label quantityOfSoup, Label quantityOfWater, Label quantityOfMeat) {
        craftsLogger.info("Player trying to craft a soup");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (!actions.craftASoup(player)) {
                infoCraftsDishesLabel.setText("You cant craft a soup!");
                infoCraftsDishesLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a soup!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsDishesLabel.setText("Crafts(Dishes)"); infoCraftsDishesLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsDishesLabel.setText("You crafted a soup!");
            infoCraftsDishesLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft a soup");
            quantityOfSoup.setText(String.valueOf(Integer.parseInt(quantityOfSoup.getText()) + 1));
            quantityOfWater.setText(String.valueOf(Integer.parseInt(quantityOfWater.getText()) - 3));
            quantityOfMeat.setText(String.valueOf(Integer.parseInt(quantityOfMeat.getText()) - 1));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsDishesLabel.setText("Crafts(Dishes)"); infoCraftsDishesLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for crafting a wooden axe with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsWeaponsLabel infoCraftWeaponsLabel in Label type for craft weapons messages to the player.
     * @param woodenAxe woodenAxe in type ImageView for displaying the wooden axe image.
     * @param quantityOfWood quantityOfWood in type Label for displaying the number of wood in inventory.
     */
    public void craftAWoodenAxe(MouseEvent event, Knight player, Actions actions, Label infoCraftsWeaponsLabel, ImageView woodenAxe, Label quantityOfWood) {
        craftsLogger.info("Player trying to craft a wooden axe");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (GameController.isWoodenAxe) {
                infoCraftsWeaponsLabel.setText("You already have a wooden axe");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a wooden axe, because already have!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            if (!actions.craftAWoodenAxe(player)) {
                infoCraftsWeaponsLabel.setText("You cant craft a wooden axe");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a wooden axe!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsWeaponsLabel.setText("You crafted a wooden axe!");
            infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft a wooden axe");
            woodenAxe.setVisible(true);
            GameController.isWoodenAxe = true;
            quantityOfWood.setText(String.valueOf(Integer.parseInt(quantityOfWood.getText()) - 2));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for crafting a wooden sword with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsWeaponsLabel infoCraftWeaponsLabel in Label type for craft weapons messages to the player.
     * @param woodenSword woodenSword in type ImageView for displaying the sword axe image.
     * @param quantityOfWood quantityOfWood in type Label for displaying the number of wood in inventory.
     */
    public void craftAWoodenSword(MouseEvent event, Knight player, Actions actions, Label infoCraftsWeaponsLabel, ImageView woodenSword, Label quantityOfWood) {
        craftsLogger.info("Player trying to craft a wooden sword");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (GameController.isWoodenSword) {
                infoCraftsWeaponsLabel.setText("You already have a wooden sword!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a wooden sword, because already have!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            if (!actions.craftAWoodenSword(player)) {
                infoCraftsWeaponsLabel.setText("You cant craft a wooden sword!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a wooden sword!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsWeaponsLabel.setText("You crafted a wooden sword!");
            infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft a wooden sword");
            woodenSword.setVisible(true);
            GameController.isWoodenSword = true;
            quantityOfWood.setText(String.valueOf(Integer.parseInt(quantityOfWood.getText()) - 3));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for crafting a wooden shield with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsWeaponsLabel infoCraftWeaponsLabel in Label type for craft weapons messages to the player.
     * @param woodenShield woodenShield in type ImageView for displaying the wooden shield image.
     * @param quantityOfWood quantityOfWood in type Label for displaying the number of wood in inventory.
     */
    public void craftAWoodenShield(MouseEvent event, Knight player, Actions actions, Label infoCraftsWeaponsLabel, ImageView woodenShield, Label quantityOfWood) {
        craftsLogger.info("Player trying to craft a wooden shield");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (GameController.isWoodenShield) {
                infoCraftsWeaponsLabel.setText("You already have a wooden shield!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a wooden shield, because already have!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            if (!actions.craftAWoodenShield(player)) {
                infoCraftsWeaponsLabel.setText("You cant craft a wooden shield!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a wooden shield!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsWeaponsLabel.setText("You crafted a wooden shield!");
            infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft a wooden shield");
            woodenShield.setVisible(true);
            GameController.isWoodenShield = true;
            quantityOfWood.setText(String.valueOf(Integer.parseInt(quantityOfWood.getText()) - 4));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for crafting an iron axe with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsWeaponsLabel infoCraftWeaponsLabel in Label type for craft weapons messages to the player.
     * @param quantityOfIron quantityOfIron in type Label for displaying the number of iron in inventory.
     * @param quantityOfWood quantityOfWood in type Label for displaying the number of wood in inventory.
     * @param ironAxe ironAxe in type ImageView for displaying the iron axe image.
     * @param woodenAxe woodenAxe in type ImageView for displaying the wooden axe image.
     */
    public void craftAnIronAxe(MouseEvent event, Knight player, Actions actions, Label infoCraftsWeaponsLabel, Label quantityOfWood, Label quantityOfIron, ImageView ironAxe, ImageView woodenAxe) {
        craftsLogger.info("Player trying to craft an iron axe");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (GameController.isIronAxe) {
                infoCraftsWeaponsLabel.setText("You already have an iron axe!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft an iron axe, because already have!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            if (!actions.craftAnIronAxe(player)) {
                infoCraftsWeaponsLabel.setText("You cant craft an iron axe!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft an iron axe!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsWeaponsLabel.setText("You crafted an iron axe!");
            infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft an iron axe");
            ironAxe.setVisible(true);
            GameController.isIronAxe = true;
            woodenAxe.setVisible(false);
            GameController.isWoodenAxe = false;
            quantityOfWood.setText(String.valueOf(Integer.parseInt(quantityOfWood.getText()) - 1));
            quantityOfIron.setText(String.valueOf(Integer.parseInt(quantityOfIron.getText()) - 1));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for crafting an iron sword with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsWeaponsLabel infoCraftWeaponsLabel in Label type for craft weapons messages to the player.
     * @param quantityOfIron quantityOfIron in type Label for displaying the number of iron in inventory.
     * @param quantityOfWood quantityOfWood in type Label for displaying the number of wood in inventory.
     * @param ironSword ironSword in type ImageView for displaying the iron sword image.
     * @param woodenSword woodenSword in type ImageView for displaying the wooden sword image.
     */
    public void craftAnIronSword(MouseEvent event, Knight player, Actions actions, Label infoCraftsWeaponsLabel, Label quantityOfWood, Label quantityOfIron, ImageView ironSword, ImageView woodenSword) {
        craftsLogger.info("Player trying to craft an iron sword");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (GameController.isIronSword) {
                infoCraftsWeaponsLabel.setText("You already have an iron sword!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft an iron sword, because already have!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            if (!actions.craftAnIronSword(player)) {
                infoCraftsWeaponsLabel.setText("You cant craft an iron sword!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft an iron sword!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsWeaponsLabel.setText("You crafted an iron sword!");
            infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft an iron sword");
            ironSword.setVisible(true);
            GameController.isIronSword = true;
            woodenSword.setVisible(false);
            GameController.isWoodenSword = false;
            quantityOfWood.setText(String.valueOf(Integer.parseInt(quantityOfWood.getText()) - 1));
            quantityOfIron.setText(String.valueOf(Integer.parseInt(quantityOfIron.getText()) - 2));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for crafting an iron shield with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsWeaponsLabel infoCraftWeaponsLabel in Label type for craft weapons messages to the player.
     * @param quantityOfIron quantityOfIron in type Label for displaying the number of iron in inventory.
     * @param quantityOfWood quantityOfWood in type Label for displaying the number of wood in inventory.
     * @param ironShield ironShield in type ImageView for displaying the iron shield image.
     * @param woodenShield woodenShield in type ImageView for displaying the wooden shield image.
     */
    public void craftAnIronShield(MouseEvent event, Knight player, Actions actions, Label infoCraftsWeaponsLabel, Label quantityOfWood, Label quantityOfIron, ImageView ironShield, ImageView woodenShield) {
        craftsLogger.info("Player trying to craft an iron shield");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (GameController.isIronShield) {
                infoCraftsWeaponsLabel.setText("You already have an iron shield!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft an iron shield, because already have!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            if (!actions.craftAnIronShield(player)) {
                infoCraftsWeaponsLabel.setText("You cant craft an iron shield!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft an iron shield!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsWeaponsLabel.setText("You crafted an iron shield!");
            infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft an iron shield");
            ironShield.setVisible(true);
            GameController.isIronShield = true;
            woodenShield.setVisible(false);
            GameController.isWoodenShield = false;
            quantityOfWood.setText(String.valueOf(Integer.parseInt(quantityOfWood.getText()) - 1));
            quantityOfIron.setText(String.valueOf(Integer.parseInt(quantityOfIron.getText()) - 3));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }

    }

    /**Method that is responsible for crafting a stone axe with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsWeaponsLabel infoCraftWeaponsLabel in Label type for craft weapons messages to the player.
     * @param quantityOfStone quantityOfStone in type Label for displaying the number of stone in inventory.
     * @param quantityOfWood quantityOfWood in type Label for displaying the number of wood in inventory.
     * @param stoneAxe stoneAxe in type ImageView for displaying the stone axe image.
     * @param ironAxe ironAxe in type ImageView for displaying the iron axe image.
     */
    public void craftAStoneAxe(MouseEvent event, Knight player, Actions actions, Label infoCraftsWeaponsLabel, Label quantityOfWood, Label quantityOfStone, ImageView stoneAxe, ImageView ironAxe) {
        craftsLogger.info("Player trying to craft a stone axe");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (GameController.isStoneShield) {
                infoCraftsWeaponsLabel.setText("You already have a stone axe!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a stone axe, because already have!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            if (!actions.craftAStoneAxe(player)) {
                infoCraftsWeaponsLabel.setText("You cant craft a stone axe!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a stone axe!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsWeaponsLabel.setText("You crafted a stone axe!");
            infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft a stone axe");
            stoneAxe.setVisible(true);
            GameController.isStoneAxe = true;
            ironAxe.setVisible(false);
            GameController.isIronAxe = false;
            quantityOfWood.setText(String.valueOf(Integer.parseInt(quantityOfWood.getText()) - 1));
            quantityOfStone.setText(String.valueOf(Integer.parseInt(quantityOfStone.getText()) - 1));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for crafting a stone sword with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsWeaponsLabel infoCraftWeaponsLabel in Label type for craft weapons messages to the player.
     * @param quantityOfStone quantityOfStone in type Label for displaying the number of stone in inventory.
     * @param quantityOfWood quantityOfWood in type Label for displaying the number of wood in inventory.
     * @param stoneSword stoneSword in type ImageView for displaying the stone sword image.
     * @param ironSword ironSword in type ImageView for displaying the iron sword image.
     */
    public void craftAStoneSword(MouseEvent event, Knight player, Actions actions, Label infoCraftsWeaponsLabel, Label quantityOfWood, Label quantityOfStone, ImageView stoneSword, ImageView ironSword) {
        craftsLogger.info("Player trying to craft a stone sword");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (GameController.isStoneSword) {
                infoCraftsWeaponsLabel.setText("You already have a stone sword!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a stone sword, because already have!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            if (!actions.craftAStoneSword(player)) {
                infoCraftsWeaponsLabel.setText("You cant craft a stone sword!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a stone sword!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsWeaponsLabel.setText("You crafted a stone sword!");
            infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft a stone sword");
            stoneSword.setVisible(true);
            GameController.isStoneSword = true;
            ironSword.setVisible(false);
            GameController.isIronSword = false;
            quantityOfWood.setText(String.valueOf(Integer.parseInt(quantityOfWood.getText()) - 1));
            quantityOfStone.setText(String.valueOf(Integer.parseInt(quantityOfStone.getText()) - 2));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }
    }

    /**Method that is responsible for crafting a stone shield with parameters.
     * @param event parameter for checking which mouse button is pressed.
     * @param player player in type Knight.
     * @param actions parameter for all possible actions.
     * @param infoCraftsWeaponsLabel infoCraftWeaponsLabel in Label type for craft weapons messages to the player.
     * @param quantityOfStone quantityOfStone in type Label for displaying the number of stone in inventory.
     * @param quantityOfWood quantityOfWood in type Label for displaying the number of wood in inventory.
     * @param stoneShield stoneShield in type ImageView for displaying the stone shield image.
     * @param ironShield ironShield in type ImageView for displaying the iron shield image.
     */
    public void craftAStoneShield(MouseEvent event, Knight player, Actions actions, Label infoCraftsWeaponsLabel, Label quantityOfWood, Label quantityOfStone, ImageView stoneShield, ImageView ironShield) {
        craftsLogger.info("Player trying to craft a stone shield");
        if (event.getButton() == MouseButton.SECONDARY) {
            if (GameController.isStoneShield) {
                infoCraftsWeaponsLabel.setText("You already have a stone shield!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a stone shield, because already have!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            if (!actions.craftAStoneShield(player)) {
                infoCraftsWeaponsLabel.setText("You cant craft a stone shield!");
                infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
                craftsLogger.warning("Player was unable to craft a stone shield!");
                Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
                timeline.play();
                return;
            }
            infoCraftsWeaponsLabel.setText("You crafted a stone shield!");
            infoCraftsWeaponsLabel.setTextFill(Color.BLACK);
            craftsLogger.info("Player managed to craft a stone shield");
            stoneShield.setVisible(true);
            GameController.isStoneShield = true;
            ironShield.setVisible(false);
            GameController.isIronShield = false;
            quantityOfWood.setText(String.valueOf(Integer.parseInt(quantityOfWood.getText()) - 1));
            quantityOfStone.setText(String.valueOf(Integer.parseInt(quantityOfStone.getText()) - 3));
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), e -> { infoCraftsWeaponsLabel.setText("Crafts(Weapons)"); infoCraftsWeaponsLabel.setTextFill(Color.web("#864800")); }));
            timeline.play();
        }
    }
}