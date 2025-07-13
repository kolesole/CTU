package cz.cvut.fel.pjv.view.tests;

import cz.cvut.fel.pjv.model.Actions;
import cz.cvut.fel.pjv.model.characters.Beast;
import cz.cvut.fel.pjv.model.characters.Knight;
import cz.cvut.fel.pjv.view.Collectors;
import javafx.application.Platform;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.util.Random;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**Class that tests the Collectors class.*/
public class CollectorsTest {

    @BeforeAll
    public static void setUpClass() {
        Platform.startup(() -> {

        });
    }

    /**1-st test method for method collectAnApple(---//---) from Collectors.java
     * checks the state of the variables after the usual picking up an apple without parameters.*/
    @Test
    public void collectAnAppleTest1() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        ImageView appleImage = new ImageView();
        appleImage.setVisible(true);
        appleImage.setLayoutX(random.nextDouble(0, 100));
        appleImage.setLayoutY(random.nextDouble(0, 100));

        Label infoLabel = new Label("");
        Label quantityOfApple = new Label("0");

        ImageView[] apples = {appleImage};

        playerImage.setVisible(true);
        playerImage.setLayoutX(appleImage.getLayoutX());
        playerImage.setLayoutY(appleImage.getLayoutY());

        collectors.collectAnApple(apples, actions, playerImage, player, infoLabel, quantityOfApple);

        assertTrue(!appleImage.isVisible(), "After the collect an apple, the apple image should be invisible, but it is visible");
        assertEquals(1, player.inventory.apple.getQuantity(), "After the collect an apple, the quantity of apples should be 1, not " + player.inventory.apple.getQuantity());
        assertEquals(1, Integer.parseInt(quantityOfApple.getText()), "After the collect an apple, the quantity of apples on label in inventory should be 1, not " + Integer.parseInt(quantityOfApple.getText()));
    }

    /**2-nd test method for method collectAnApple(---//---) from Collectors.java
     * checks the state of the variables after trying to pick up an apple that is invisible without parameters.*/
    @Test
    public void collectAnAppleTest2() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        ImageView appleImage = new ImageView();
        appleImage.setVisible(false);
        appleImage.setLayoutX(random.nextDouble(0, 100));
        appleImage.setLayoutY(random.nextDouble(0, 100));

        Label infoLabel = new Label("");
        Label quantityOfApple = new Label("0");

        ImageView[] apples = {appleImage};

        playerImage.setVisible(true);
        playerImage.setLayoutX(appleImage.getLayoutX());
        playerImage.setLayoutY(appleImage.getLayoutY());

        collectors.collectAnApple(apples, actions, playerImage, player, infoLabel, quantityOfApple);

        assertEquals(0, player.inventory.apple.getQuantity(), "After trying the collect an apple with invisible image, the quantity of apples should be unchanged(0), not " + player.inventory.apple.getQuantity());
        assertEquals(0, Integer.parseInt(quantityOfApple.getText()), "After the collect an apple with invisible image, the quantity of apples on label in inventory should be unchanged(0), not " + Integer.parseInt(quantityOfApple.getText()));
    }

    /**1-st test method for method collectAWheat(---//---) from Collectors.java
     * checks the state of the variables after the usual picking up a wheat without parameters.*/
    @Test
    public void collectAWheatTest1() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        ImageView wheatImage = new ImageView();
        wheatImage.setVisible(true);
        wheatImage.setLayoutX(random.nextDouble(0, 100));
        wheatImage.setLayoutY(random.nextDouble(0, 100));

        Label infoLabel = new Label("");
        Label quantityOfWheat = new Label("0");

        ImageView[] wheatImages = {wheatImage};

        playerImage.setVisible(true);
        playerImage.setLayoutX(wheatImage.getLayoutX());
        playerImage.setLayoutY(wheatImage.getLayoutY());

        collectors.collectAWheat(wheatImages, actions, playerImage, player, infoLabel, quantityOfWheat);

        assertTrue(!wheatImage.isVisible(), "After the collect a wheat, the wheat image should be invisible, but it is visible");
        assertEquals(1, player.inventory.wheat.getQuantity(), "After the collect a wheat, the quantity of wheat should be 1, not " + player.inventory.wheat.getQuantity());
        assertEquals(1, Integer.parseInt(quantityOfWheat.getText()), "After the collect a wheat, the quantity of wheat on label in inventory should be 1, not " + Integer.parseInt(quantityOfWheat.getText()));
    }

    /**2-nd test method for method collectAWheat(---//---) from Collectors.java
     * checks the state of the variables after trying to pick up a wheat that is invisible without parameters.*/
    @Test
    public void collectAWheatTest2() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        ImageView wheatImage = new ImageView();
        wheatImage.setVisible(false);
        wheatImage.setLayoutX(random.nextDouble(0, 100));
        wheatImage.setLayoutY(random.nextDouble(0, 100));

        Label infoLabel = new Label("");
        Label quantityOfWheat = new Label("0");

        ImageView[] wheatImages = {wheatImage};

        playerImage.setVisible(true);
        playerImage.setLayoutX(wheatImage.getLayoutX());
        playerImage.setLayoutY(wheatImage.getLayoutY());

        collectors.collectAWheat(wheatImages, actions, playerImage, player, infoLabel, quantityOfWheat);

        assertEquals(0, player.inventory.wheat.getQuantity(), "After trying the collect a wheat with invisible image, the quantity of wheat should be unchanged(0), not " + player.inventory.wheat.getQuantity());
        assertEquals(0, Integer.parseInt(quantityOfWheat.getText()), "After the collect a wheat with invisible image, the quantity of wheat on label in inventory should be unchanged(0), not " + Integer.parseInt(quantityOfWheat.getText()));
    }

    /**Test method for method collectAWater(---//---) from Collectors.java
     * checks the state of the variables after the usual collecting a water without parameters.*/
    @Test
    public void collectAWaterTest() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        Label infoLabel = new Label("");
        Label quantityOfWater = new Label("0");

        playerImage.setVisible(true);
        playerImage.setLayoutX(252);
        playerImage.setLayoutY(535);

        collectors.collectAWater(playerImage, player, actions, infoLabel, quantityOfWater);

        assertEquals(1, player.inventory.water.getQuantity(), "After the collect a water, the quantity of water should be 1, not " + player.inventory.water.getQuantity());
        assertEquals(1, Integer.parseInt(quantityOfWater.getText()), "After the collect a water, the quantity of water on label in inventory should be 1, not " + Integer.parseInt(quantityOfWater.getText()));
    }

    /**1-st test method for method collectAWood(---//---) from Collectors.java
     * checks the state of the variables after the usual collecting a wood without parameters.*/
    @Test
    public void collectAWoodTest1() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        ImageView treeTopImage = new ImageView();
        treeTopImage.setVisible(true);
        treeTopImage.setLayoutX(random.nextDouble(0, 100));
        treeTopImage.setLayoutY(random.nextDouble(0, 100));

        ImageView treeTrunkImage = new ImageView();
        treeTrunkImage.setVisible(true);
        treeTrunkImage.setLayoutX(treeTopImage.getLayoutX());
        treeTrunkImage.setLayoutY(treeTopImage.getLayoutY());

        Label infoLabel = new Label("");
        Label quantityOfWood = new Label("0");

        ImageView[] treeTops = {treeTopImage};
        ImageView[] treeTrunks = {treeTrunkImage};

        playerImage.setVisible(true);
        playerImage.setLayoutX(treeTopImage.getLayoutX());
        playerImage.setLayoutY(treeTopImage.getLayoutY());

        collectors.collectAWood(treeTops, treeTrunks, actions, playerImage, player, infoLabel, quantityOfWood);

        assertTrue(!treeTopImage.isVisible() && !treeTrunkImage.isVisible(), "After the collect a wood, the tree image should be invisible, but it is visible");
        assertEquals(player.inventory.wood.getQuantity(), player.getIntDamageToMaterials(), "After the collect a wood, the quantity of wood should be " + player.getIntDamageToMaterials() + ", not " + player.inventory.wood.getQuantity());
        assertEquals(Integer.parseInt(quantityOfWood.getText()), player.getIntDamageToMaterials(), "After the collect a wood, the quantity of wood on label in inventory should be" + player.getIntDamageToMaterials() + ", not " + Integer.parseInt(quantityOfWood.getText()));
    }

    /**2-nd test method for method collectAWood(---//---) from Collectors.java
     * checks the state of the variables after trying to collect a wood that is invisible without parameters.*/
    @Test
    public void collectAWoodTest2() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        ImageView treeTopImage = new ImageView();
        treeTopImage.setVisible(false);
        treeTopImage.setLayoutX(random.nextDouble(0, 100));
        treeTopImage.setLayoutY(random.nextDouble(0, 100));

        ImageView treeTrunkImage = new ImageView();
        treeTrunkImage.setVisible(false);
        treeTrunkImage.setLayoutX(treeTopImage.getLayoutX());
        treeTrunkImage.setLayoutY(treeTopImage.getLayoutY());

        Label infoLabel = new Label("");
        Label quantityOfWood = new Label("0");

        ImageView[] treeTops = {treeTopImage};
        ImageView[] treeTrunks = {treeTrunkImage};

        playerImage.setVisible(true);
        playerImage.setLayoutX(treeTopImage.getLayoutX());
        playerImage.setLayoutY(treeTopImage.getLayoutY());

        collectors.collectAWood(treeTops, treeTrunks, actions, playerImage, player, infoLabel, quantityOfWood);

        assertEquals(player.inventory.wood.getQuantity(), 0, "After the collect a wood and image is invisible, the quantity of wood should be unchanged(0), not " + player.inventory.wood.getQuantity());
        assertEquals(Integer.parseInt(quantityOfWood.getText()), 0, "After the collect a wood and image is invisible, the quantity of wood on label in inventory should be unchanged(0), not " + Integer.parseInt(quantityOfWood.getText()));
    }

    /**1-st test method for method collectAnIron(---//---) from Collectors.java
     * checks the state of the variables after the usual collecting an iron without parameters.*/
    @Test
    public void collectAnIronTest1() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        ImageView ironImage = new ImageView();
        ironImage.setVisible(true);
        ironImage.setLayoutX(random.nextDouble(0, 100));
        ironImage.setLayoutY(random.nextDouble(0, 100));


        Label infoLabel = new Label("");
        Label quantityOfIron = new Label("0");

        ImageView[] ironImages = {ironImage};

        playerImage.setVisible(true);
        playerImage.setLayoutX(ironImage.getLayoutX());
        playerImage.setLayoutY(ironImage.getLayoutY());

        collectors.collectAnIron(ironImages, actions, playerImage, player, infoLabel, quantityOfIron);

        assertTrue(!ironImage.isVisible(), "After the collect an iron, the iron image should be invisible, but it is visible");
        assertEquals(player.inventory.iron.getQuantity(), player.getIntDamageToMaterials(), "After the collect an iron, the quantity of iron should be " + player.getIntDamageToMaterials() + ",not " + player.inventory.iron.getQuantity());
        assertEquals(Integer.parseInt(quantityOfIron.getText()), player.getIntDamageToMaterials(), "After the collect an iron, the quantity of iron on label in inventory should be" + player.getIntDamageToMaterials() + ",not " + Integer.parseInt(quantityOfIron.getText()));
    }

    /**2-nd test method for method collectAnIron(---//---) from Collectors.java
     * checks the state of the variables after trying to collect an iron that is invisible without parameters.*/
    @Test
    public void collectAnIronTest2() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        ImageView ironImage = new ImageView();
        ironImage.setVisible(false);
        ironImage.setLayoutX(random.nextDouble(0, 100));
        ironImage.setLayoutY(random.nextDouble(0, 100));


        Label infoLabel = new Label("");
        Label quantityOfIron = new Label("0");

        ImageView[] ironImages = {ironImage};

        playerImage.setVisible(true);
        playerImage.setLayoutX(ironImage.getLayoutX());
        playerImage.setLayoutY(ironImage.getLayoutY());

        collectors.collectAnIron(ironImages, actions, playerImage, player, infoLabel, quantityOfIron);

        assertEquals(player.inventory.iron.getQuantity(), 0, "After the collect an iron and image is invisible, the quantity of iron should be unchanged(0), not " + player.inventory.iron.getQuantity());
        assertEquals(Integer.parseInt(quantityOfIron.getText()), 0, "After the collect an iron and image is invisible, the quantity of iron on label in inventory should be unchanged(0), not " + Integer.parseInt(quantityOfIron.getText()));
    }

    /**1-st test method for method collectAMeat(---//---) from Collectors.java
     * checks the state of the variables after the usual picking up a meat, when the boar is dead without parameters.*/
    @Test
    public void collectAMeatTest1() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        ImageView boarImage = new ImageView();
        boarImage.setVisible(true);
        boarImage.setLayoutX(random.nextDouble(0, 100));
        boarImage.setLayoutY(random.nextDouble(0, 100));

        Beast boar = new Beast(0, 10);

        Label infoLabel = new Label("");
        Label quantityOfMeat = new Label("0");

        ImageView[] boarsImages = {boarImage};
        Beast[] boars = {boar};

        playerImage.setVisible(true);
        playerImage.setLayoutX(boarImage.getLayoutX());
        playerImage.setLayoutY(boarImage.getLayoutY());

        collectors.collectAMeat(boarsImages, boars, actions, playerImage, player, infoLabel, quantityOfMeat);

        assertTrue(!boarImage.isVisible(), "After the collect a meat, the boar image should be invisible, but it is visible");
        assertEquals(1, player.inventory.meat.getQuantity(), "After the collect a meat, the quantity of meat should be 1, not " + player.inventory.meat.getQuantity());
        assertEquals(1, Integer.parseInt(quantityOfMeat.getText()), "After the collect a meat, the quantity of meat on label in inventory should be 1, not " + Integer.parseInt(quantityOfMeat.getText()));
    }

    /**2-nd test method for method collectAMeat(---//---) from Collectors.java
     * checks the state of the variables after trying to collect a meat, when boar is not dead without parameters.*/
    @Test
    public void collectAMeatTest2() {
        Collectors collectors = new Collectors();
        Actions actions = new Actions();
        Random random = new Random();

        ImageView playerImage = new ImageView();
        Knight player = new Knight(10, 20);

        ImageView boarImage = new ImageView();
        boarImage.setVisible(true);
        boarImage.setLayoutX(random.nextDouble(0, 100));
        boarImage.setLayoutY(random.nextDouble(0, 100));

        Beast boar = new Beast(10, 10);

        Label infoLabel = new Label("");
        Label quantityOfMeat = new Label("0");

        ImageView[] boarsImages = {boarImage};
        Beast[] boars = {boar};

        playerImage.setVisible(true);
        playerImage.setLayoutX(boarImage.getLayoutX());
        playerImage.setLayoutY(boarImage.getLayoutY());

        collectors.collectAMeat(boarsImages, boars, actions, playerImage, player, infoLabel, quantityOfMeat);

        assertEquals(0, player.inventory.meat.getQuantity(), "After trying the collect a meat when boar is not dead, the quantity of meat should be unchanged(0), not " + player.inventory.meat.getQuantity());
        assertEquals(0, Integer.parseInt(quantityOfMeat.getText()), "After the collect a meat when boar is not dead, the quantity of meat on label in inventory should be unchanged(0), not " + Integer.parseInt(quantityOfMeat.getText()));
    }
}

