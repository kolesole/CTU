package cz.cvut.fel.pjv.view;

import cz.cvut.fel.pjv.model.Actions;
import cz.cvut.fel.pjv.model.characters.Beast;
import cz.cvut.fel.pjv.model.characters.Knight;
import javafx.animation.AnimationTimer;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import javafx.util.Duration;

import static cz.cvut.fel.pjv.GameApplication.gameControllerLogger;

/**Class controller to control the game*/
public class GameController {

    /**main pane in AnchorPane type from FXML file.*/
    @FXML
    private AnchorPane pane;

    /**player image in ImageView type from FXML file.*/
    @FXML
    private ImageView playerImage;

    /**creating a new player in type Knight.*/
    public static Knight player = new Knight(10, 20);

    /**heart images from FXML file that are displayed in the upper right corner of the screen and indicate the players amount of HP.*/
    @FXML
    private ImageView heart1, heart2, heart3, heart4, heart5, heart6, heart7, heart8, heart9, heart10;

    /**shield images from FXML file that is displayed in the upper right corner of the screen and indicate the players amount of protection.*/
    @FXML
    private ImageView shield1, shield2, shield3, shield4, shield5;

    /**water images from FXML file that is displayed in the upper right corner of the screen and indicate the players thirst level.*/
    @FXML
    private ImageView water1, water2, water3, water4, water5, water6, water7, water8, water9, water10,
            water11, water12, water13, water14, water15, water16, water17, water18, water19, water20;

    /**camp fire image from FXML file in the center of the 1-st level.*/
    @FXML
    private ImageView campFireImage;

    /**flag image from FXML file that displays a flag on 1-st level.*/
    @FXML
    private ImageView flagImage;

    /**apple images from FXML file that the player can pick up and replenish the supply.*/
    @FXML
    private ImageView apple1, apple2, apple3, apple4, apple5, apple6,
            apple7, apple8, apple9, apple10, apple11, apple12, apple13;

    /**images from FXML file from which trees are made, which the player can cut down and replenish supplies.*/
    @FXML
    private ImageView treeTop1, treeTrunk1, treeTop2, treeTrunk2, treeTop3, treeTrunk3, treeTop4, treeTrunk4, treeTop5, treeTrunk5,
            treeTop6, treeTrunk6, treeTop7, treeTrunk7, treeTop8, treeTrunk8, treeTop9, treeTrunk9, treeTop10, treeTrunk10, treeTop11, treeTrunk11;

    /**wheat images from FXML file that the player can pick up and replenish the supply.*/
    @FXML
    private ImageView wheat1, wheat2, wheat3, wheat4, wheat5, wheat6, wheat7, wheat8, wheat9,
            wheat10, wheat11, wheat12, wheat13, wheat14, wheat15, wheat16, wheat17, wheat18;

    /**labels that display what player craft, collect etc.*/
    @FXML
    private Label infoLabel, infoCraftsDishesLabel, infoCraftsWeaponsLabel;

    /**labels that display quantities of materials.*/
    @FXML
    private Label quantityOfApple, quantityOfIron, quantityOfMeat, quantityOfPie, quantityOfSoup,
            quantityOfStone, quantityOfWater, quantityOfWheat, quantityOfWood;

    /**images of weapons in the inventory.*/
    @FXML
    private ImageView woodenAxe, woodenSword, woodenShield, ironAxe, ironSword, ironShield, stoneAxe, stoneSword, stoneShield;

    /**images that are removed when opening the 2-nd level.*/
    @FXML
    private ImageView obj1, obj2, obj3;

    /**images that display boars on the 2-nd level*/
    @FXML
    private ImageView boarImage1, boarImage2, boarImage3, boarImage4, boarImage5, boarImage6, boarImage7;

    /**boars from second level in Beast type*/
    private Beast boar1 = new Beast(60, 1), boar2 = new Beast(60, 1),
                  boar3 = new Beast(60, 1), boar4 = new Beast(60, 1),
                  boar5 = new Beast(60, 1), boar6 = new Beast(60, 1),
                  boar7 = new Beast(60, 1);

    /**labels for addition signs used in the crafting tab.*/
    @FXML
    private Label additionSign1, additionSign2, additionSign3, additionSign4, additionSign5,
            additionSign6, additionSign7, additionSign8, additionSign9;

    /**image views for various crafting items.*/
    @FXML
    private ImageView craftsApple, craftsCell1, craftsCell2, craftsCell3, craftsCell4,
            craftsCell5, craftsCell6, craftsCell7, craftsCell8, craftsCell9,
            craftsCell10, craftsCell11, craftsCell12, craftsCell13, craftsCell14,
            craftsCell15, craftsCell16, craftsCell17, craftsCell18, craftsCell19,
            craftsCell20, craftsCell21, craftsCell22, craftsCell23, craftsCell24,
            craftsCell25, craftsCell26, craftsCell27, craftsCell28, craftsCell29,
            craftsCell30, craftsCell31, craftsCell32, craftsCell33, craftsCell34,
            craftsCell35, craftsCell36, craftsCell37, craftsCell38, craftsCell39,
            craftsCell40, craftsCell41, craftsCell42, craftsCell43, craftsCell44,
            craftsCell46, craftsCell47, craftsCell48, craftsCell49, craftsCell50,
            craftsCell51, craftsCell52, craftsIron1, craftsIron2, craftsIron3, craftsIronAxe,
            craftsIronShield, craftsIronSword, craftsMeat, craftsPie, craftsSoup,
            craftsStone1, craftsStone2, craftsStone3, craftsStoneAxe, craftsStoneShield,
            craftsStoneSword, craftsWater1, craftsWater2, craftsWheat, craftsWood1,
            craftsWood2, craftsWood3, craftsWood4, craftsWood5, craftsWood6, craftsWood7,
            craftsWood8, craftsWood9, craftsWoodenAxe, craftsWoodenShield, craftsWoodenSword;

    /**labels for equal signs used in the crafting tab.*/
    @FXML
    private Label equalSign1, equalSign2, equalSign3, equalSign4, equalSign5, equalSign6,
            equalSign7, equalSign8, equalSign9, equalSign10, equalSign11;

    /**image views for items that make up part of the inventory.*/
    @FXML
    private ImageView inventory, inventoryApple, inventoryIron, inventoryMeat, inventoryPie,
            inventorySoup, inventoryStone, inventoryWater, inventoryWood, inventoryWheat;

    /**labels for quantities of various crafting items.*/
    @FXML
    private Label quantityOfApple1, quantityOfIron1, quantityOfIron2, quantityOfIron3, quantityOfMeat1,
            quantityOfStone1, quantityOfStone2, quantityOfStone3, quantityOfWater1, quantityOfWater2,
            quantityOfWheat1, quantityOfWood1, quantityOfWood2, quantityOfWood3, quantityOfWood4,
            quantityOfWood5, quantityOfWood6, quantityOfWood7, quantityOfWood8, quantityOfWood9;

    /**images of iron that the player can pick up and replenish the supply.*/
    @FXML
    private ImageView iron1, iron2, iron3, iron4, iron5, iron6, iron7, iron8, iron9, iron10;

     /**labels that appear when a player dies.*/
    @FXML
    private Label gameOverLabel1, gameOverLabel2, gameOverLabel11, gameOverLabel21;

    /**indexes that are created for sprite images.*/
    private static int upImageIndex = 1, downImageIndex = 1, rightImageIndex = 1, leftImageIndex = 1,
            hitImageIndex = 0, campFireIndex = 1, flagIndex = 1;

    /**attributes for interaction between GameController and GameApplication.*/
    public static boolean up = false, right = false, down = false, left = false, playerDirectionIsUp = false,
            playerDirectionIsRight = false, playerDirectionIsDown = false, playerDirectionIsLeft = false, collectAnApple,
            collectAWheat, collectAWater, collectAMeat, isInventoryOpen, hit = false, isRunning = false;

    /**attributes to track what weapons the player has.*/
    public static boolean isWoodenAxe = true, isWoodenSword = false, isWoodenShield = false, isIronAxe = false, isIronSword = false,
            isIronShield = false, isStoneAxe = false, isStoneSword = false, isStoneShield = false;

    /**classes.*/
    private Actions actions = new Actions();
    private Crafts crafts = new Crafts();
    private Consumers consumers = new Consumers();
    private Collectors collectors = new Collectors();
    private Setters setters = new Setters();
    private LevelChanger levelChanger = new LevelChanger();
    private Movement movement;
    private Stage stage;

    private static int iteration = 0;
    private boolean secondLevelRunning = false;

    /** AnimationTimer that updates the game state in each frame.
     * This timer is responsible for player movement, checking win/lose conditions,
     * changing levels, and other game actions.*/
    AnimationTimer animationTimer = new AnimationTimer() {
        @Override
        public void handle(long l) {
            if (iteration == 0) {
                iteration++;
            }
            if (!gameOverLabel1.isVisible()) {
                if (levelChanger.isSecondLvl && !secondLevelRunning) {
                    secondLevelRunning = true;
                    BeastThread beastThread1 = new BeastThread(boarImage1, boar1, playerImage, player, actions);
                    Thread thread1 = new Thread(beastThread1);

                    BeastThread beastThread2 = new BeastThread(boarImage2, boar2, playerImage, player, actions);
                    Thread thread2 = new Thread(beastThread2);

                    BeastThread beastThread3 = new BeastThread(boarImage3, boar3, playerImage, player, actions);
                    Thread thread3 = new Thread(beastThread3);

                    BeastThread beastThread4 = new BeastThread(boarImage4, boar4, playerImage, player, actions);
                    Thread thread4 = new Thread(beastThread4);

                    BeastThread beastThread5 = new BeastThread(boarImage5, boar5, playerImage, player, actions);
                    Thread thread5 = new Thread(beastThread5);

                    BeastThread beastThread6 = new BeastThread(boarImage6, boar6, playerImage, player, actions);
                    Thread thread6 = new Thread(beastThread6);

                    BeastThread beastThread7 = new BeastThread(boarImage7, boar7, playerImage, player, actions);
                    Thread thread7 = new Thread(beastThread7);

                    thread1.setDaemon(true);
                    thread2.setDaemon(true);
                    thread3.setDaemon(true);
                    thread4.setDaemon(true);
                    thread5.setDaemon(true);
                    thread6.setDaemon(true);
                    thread7.setDaemon(true);
                    thread1.start();
                    thread2.start();
                    thread3.start();
                    thread4.start();
                    thread5.start();
                    thread6.start();
                    thread7.start();
                }
                if (actions.occurrenceOfPlayersDeath(player)) {
                    gameOverLabel1.setVisible(true);
                    gameOverLabel11.setVisible(true);
                    gameOverLabel2.setVisible(true);
                    gameOverLabel21.setVisible(true);
                    gameControllerLogger.warning("Player died");
                }
                movement = new Movement(playerImage);
                if (movement.isPossibleMoveToUp()) {
                    upImageIndex = (upImageIndex + 1) % 81 != 0 ? (upImageIndex + 1) % 81 : 1;
                    playerImage.setImage(new Image("/images/knight/1-st/Walk/Walk_0" + (upImageIndex / 9 != 0 ? upImageIndex / 9 : 1) + ".png"));
                    playerImage.setLayoutY(playerImage.getLayoutY() - 0.2);
                }
                if (movement.isPossibleMoveToDown()) {
                    downImageIndex = (downImageIndex + 1) % 81 != 0 ? (downImageIndex + 1) % 81 : 1;
                    playerImage.setImage(new Image("/images/knight/1-st/Walk/Walk_2" + (downImageIndex / 9 != 0 ? downImageIndex / 9 : 1) + ".png"));
                    playerImage.setLayoutY(playerImage.getLayoutY() + 0.2);
                }
                if (movement.isPossibleMoveToLeft()) {
                    leftImageIndex = (leftImageIndex + 1) % 81 != 0 ? (leftImageIndex + 1) % 81 : 1;
                    playerImage.setImage(new Image("/images/knight/1-st/Walk/Walk_1" + (leftImageIndex / 9 != 0 ? leftImageIndex / 9 : 1) + ".png"));
                    playerImage.setLayoutX(playerImage.getLayoutX() - 0.2);
                }
                if (movement.isPossibleMoveToRight(obj1, obj2, obj3)) {
                    rightImageIndex = (rightImageIndex + 1) % 81 != 0 ? (rightImageIndex + 1) % 81 : 1;
                    playerImage.setImage(new Image("/images/knight/1-st/Walk/Walk_3" + (rightImageIndex / 9 != 0 ? rightImageIndex / 9 : 1) + ".png"));
                    playerImage.setLayoutX(playerImage.getLayoutX() + 0.2);
                }
                if (hit) {
                    if (playerDirectionIsUp) {
                        hitImageIndex++;
                        playerImage.setImage(new Image("/images/knight/1-st/Hit/AxeHit" + ((hitImageIndex % 72) / 12 != 0 ? (hitImageIndex % 72) / 12 : 1) + ".png"));
                        if (hitImageIndex == 72) {
                            hitImageIndex = 1;
                            hit = false;
                        }
                    }
                    if (playerDirectionIsLeft) {
                        hitImageIndex++;
                        playerImage.setImage(new Image("/images/knight/1-st/Hit/AxeHit1" + ((hitImageIndex % 72) / 12 != 0 ? (hitImageIndex % 72) / 12 : 1) + ".png"));
                        if (hitImageIndex == 72) {
                            hitImageIndex = 1;
                            hit = false;
                        }
                    }
                    if (playerDirectionIsDown) {
                        hitImageIndex++;
                        playerImage.setImage(new Image("/images/knight/1-st/Hit/AxeHit2" + ((hitImageIndex % 72) / 12 != 0 ? (hitImageIndex % 72) / 12 : 1) + ".png"));
                        if (hitImageIndex == 72) {
                            hitImageIndex = 1;
                            hit = false;
                        }
                    }
                    if (playerDirectionIsRight) {
                        hitImageIndex++;
                        playerImage.setImage(new Image("/images/knight/1-st/Hit/AxeHit3" + ((hitImageIndex % 72) / 12 != 0 ? (hitImageIndex % 72) / 12 : 1) + ".png"));
                        if (hitImageIndex == 72) {
                            hitImageIndex = 1;
                            hit = false;
                        }
                    }
                    collectAWood();
                    collectAnIron();
                }
                campFireIndex = (campFireIndex + 1) % 98 != 0 ? (campFireIndex + 1) % 98 : 1;
                flagIndex = (flagIndex + 1) % 98 != 0 ? (flagIndex + 1) % 98 : 1;
                campFireImage.setImage(new Image("images/objects/1-st/animation/CampFire_0" + (campFireIndex / 14 != 0 ? campFireIndex / 14 : 1) + ".png"));
                flagImage.setImage(new Image("images/objects/1-st/animation/Flag_0" + (flagIndex / 14 != 0 ? flagIndex / 14 : 1) + ".png"));
                if (collectAnApple) collectAnApple();
                if (collectAWheat) collectAWheat();
                if (collectAWater && !isRunning) collectAWater();
                if (collectAMeat) collectAMeat();
                if (!isInventoryOpen) closeInventory();
                if (isInventoryOpen) openInventory();
                setHp();
                setProtection();
                setThirstLvl();
                if (obj1.isVisible() && obj2.isVisible() && obj3.isVisible() && isWoodenShield && isWoodenSword) {
                    obj1.setVisible(false);
                    obj2.setVisible(false);
                    obj3.setVisible(false);
                }
                changeLevel();
            }
        }
    };

    /**Method through which the stage is transmitted from the GameApplication with parameters.
     * @param stage in Stage type from GameApplication.
     */
    public void setStage(Stage stage) {
        this.stage = stage;
    }

    /**Method to stop animation timer without parameters.*/
    public void stopAnimationTimer() {
        gameControllerLogger.info("Animation timer stopped");
        player = new Knight(10, 20);
        isWoodenAxe = true;
        isWoodenSword = false;
        isWoodenShield = false;
        isIronAxe = false;
        isIronSword = false;
        isIronShield = false;
        isStoneAxe = false;
        isStoneSword = false;
        isStoneShield = false;
        obj1.setVisible(true);
        obj2.setVisible(true);
        obj3.setVisible(true);
        isInventoryOpen = false;
        if (secondLevelRunning) {
            secondLevelRunning = false;
        }
        levelChanger.isFirstLvl = true;
        levelChanger.isSecondLvl = false;
        levelChanger.isThirdLvl = false;
        animationTimer.stop();
    }

    /**Method that is responsible for opening inventory without parameters.*/
    private void openInventory() {
        Label[] labels = {infoLabel, infoCraftsWeaponsLabel, infoCraftsDishesLabel, quantityOfPie, quantityOfIron, quantityOfWheat, quantityOfMeat, quantityOfWood, quantityOfSoup, quantityOfApple, quantityOfStone, quantityOfWater, quantityOfApple1, quantityOfIron1, quantityOfIron2, quantityOfIron3, quantityOfMeat1, quantityOfStone1,
                quantityOfStone2, quantityOfStone3, quantityOfWater1, quantityOfWater2, quantityOfWheat1, quantityOfWood1,
                quantityOfWood2, quantityOfWood3, quantityOfWood4, quantityOfWood5, quantityOfWood6, quantityOfWood7, quantityOfWood8,
                quantityOfWood9, additionSign1, additionSign2, additionSign3, additionSign4, additionSign5, additionSign6,
                additionSign7, additionSign8, additionSign9, equalSign1, equalSign10, equalSign11, equalSign2, equalSign3, equalSign4,
                equalSign5, equalSign6, equalSign7, equalSign8, equalSign9};
        ImageView[] inventoryItems = {craftsApple, craftsCell1, craftsCell10, craftsCell11, craftsCell12, craftsCell13, craftsCell14,
                craftsCell15, craftsCell16, craftsCell17, craftsCell18, craftsCell19, craftsCell2, craftsCell20, craftsCell21,
                craftsCell22, craftsCell23, craftsCell24, craftsCell25, craftsCell26, craftsCell27, craftsCell28, craftsCell29,
                craftsCell3, craftsCell30, craftsCell31, craftsCell32, craftsCell33, craftsCell34, craftsCell35, craftsCell36,
                craftsCell37, craftsCell38, craftsCell39, craftsCell4, craftsCell40, craftsCell41, craftsCell42, craftsCell43,
                craftsCell44, craftsCell46, craftsCell47, craftsCell48, craftsCell49, craftsCell5, craftsCell50, craftsCell51, craftsCell52,
                craftsCell6, craftsCell7, craftsCell8, craftsCell9, craftsIron1, craftsIron2, craftsIron3, craftsIronAxe,
                craftsIronShield, craftsIronSword, craftsMeat, craftsPie, craftsSoup, craftsStone1, craftsStone2, craftsStone3,
                craftsStoneAxe, craftsStoneShield, craftsStoneSword, craftsWater1, craftsWater2, craftsWheat, craftsWood1,
                craftsWood2, craftsWood3, craftsWood4, craftsWood5, craftsWood6, craftsWood7, craftsWood8, craftsWood9, craftsWoodenAxe,
                craftsWoodenShield, craftsWoodenSword, inventory, inventoryApple, inventoryIron, inventoryMeat, inventoryPie,
                inventorySoup, inventoryStone, inventoryWater, inventoryWood, inventoryWheat};
        if (isWoodenAxe) woodenAxe.setVisible(true);
        if (isWoodenSword) woodenSword.setVisible(true);
        if (isWoodenShield) woodenShield.setVisible(true);
        if (isIronAxe) ironAxe.setVisible(true);
        if (isIronSword) ironSword.setVisible(true);
        if (isIronShield) ironShield.setVisible(true);
        if (isStoneAxe) stoneAxe.setVisible(true);
        if (isStoneSword) stoneSword.setVisible(true);
        if (isStoneShield) stoneShield.setVisible(true);

        for (Label label : labels) label.setVisible(true);
        for (ImageView inventoryItem : inventoryItems) inventoryItem.setVisible(true);
    }

    /**Method that is responsible for closing inventory without parameters.*/
    private void closeInventory() {
        Label[] labels = {infoLabel, infoCraftsWeaponsLabel, infoCraftsDishesLabel, quantityOfPie, quantityOfIron, quantityOfWheat, quantityOfMeat, quantityOfWood, quantityOfSoup, quantityOfApple, quantityOfStone, quantityOfWater, quantityOfApple1, quantityOfIron1, quantityOfIron2, quantityOfIron3, quantityOfMeat1, quantityOfStone1,
                quantityOfStone2, quantityOfStone3, quantityOfWater1, quantityOfWater2, quantityOfWheat1, quantityOfWood1,
                quantityOfWood2, quantityOfWood3, quantityOfWood4, quantityOfWood5, quantityOfWood6, quantityOfWood7, quantityOfWood8,
                quantityOfWood9, additionSign1, additionSign2, additionSign3, additionSign4, additionSign5, additionSign6,
                additionSign7, additionSign8, additionSign9, equalSign1, equalSign10, equalSign11, equalSign2, equalSign3, equalSign4,
                equalSign5, equalSign6, equalSign7, equalSign8, equalSign9};
        ImageView[] inventoryItems = {craftsApple, craftsCell1, craftsCell10, craftsCell11, craftsCell12, craftsCell13, craftsCell14,
                craftsCell15, craftsCell16, craftsCell17, craftsCell18, craftsCell19, craftsCell2, craftsCell20, craftsCell21,
                craftsCell22, craftsCell23, craftsCell24, craftsCell25, craftsCell26, craftsCell27, craftsCell28, craftsCell29,
                craftsCell3, craftsCell30, craftsCell31, craftsCell32, craftsCell33, craftsCell34, craftsCell35, craftsCell36,
                craftsCell37, craftsCell38, craftsCell39, craftsCell4, craftsCell40, craftsCell41, craftsCell42, craftsCell43,
                craftsCell44, craftsCell46, craftsCell47, craftsCell48, craftsCell49, craftsCell5, craftsCell50, craftsCell51, craftsCell52,
                craftsCell6, craftsCell7, craftsCell8, craftsCell9, craftsIron1, craftsIron2, craftsIron3, craftsIronAxe,
                craftsIronShield, craftsIronSword, craftsMeat, craftsPie, craftsSoup, craftsStone1, craftsStone2, craftsStone3,
                craftsStoneAxe, craftsStoneShield, craftsStoneSword, craftsWater1, craftsWater2, craftsWheat, craftsWood1,
                craftsWood2, craftsWood3, craftsWood4, craftsWood5, craftsWood6, craftsWood7, craftsWood8, craftsWood9, craftsWoodenAxe,
                craftsWoodenShield, craftsWoodenSword, inventory, inventoryApple, inventoryIron, inventoryMeat, inventoryPie,
                inventorySoup, inventoryStone, inventoryWater, inventoryWood, inventoryWheat, woodenAxe, woodenShield, woodenSword,
                ironAxe, ironShield, ironSword, stoneAxe, stoneShield, stoneSword};
        for (Label label : labels) label.setVisible(false);
        for (ImageView inventoryItem : inventoryItems) inventoryItem.setVisible(false);
    }

    /**Method that is responsible for collection an apple without parameters.*/
    private void collectAnApple() {
        ImageView[] apples = {apple1, apple2, apple3, apple4, apple5, apple6, apple7, apple8, apple9, apple10, apple11, apple12, apple13};
        collectors.collectAnApple(apples, actions, playerImage, player, infoLabel, quantityOfApple);
    }

    /**Method that is responsible for collecting a wheat without parameters.*/
    private void collectAWheat() {
        ImageView[] wheat = {wheat1, wheat2, wheat3, wheat4, wheat5, wheat6, wheat7, wheat8, wheat9, wheat10, wheat11, wheat12, wheat13, wheat14, wheat15, wheat16, wheat17, wheat18};
        collectors.collectAWheat(wheat, actions, playerImage, player, infoLabel, quantityOfWheat);
    }

    /**Method that is responsible for collecting a water without parameters.*/
    private void collectAWater() {
        isRunning = true;
        collectors.collectAWater(playerImage, player, actions, infoLabel, quantityOfWater);
        Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> isRunning = false));
        timeline.play();
    }

    /**Method that is responsible for collecting a meat*/
    private void collectAMeat() {
        ImageView[] boarsImages = {boarImage1, boarImage2, boarImage3, boarImage4};
        Beast[] boars = {boar1, boar2, boar3, boar4};
        collectors.collectAMeat(boarsImages, boars, actions, playerImage, player, infoLabel, quantityOfMeat);
    }
    /**Method that is responsible for collecting a wood without parameters.*/
    private void collectAWood() {
        ImageView[] treeTops = {treeTop1, treeTop2, treeTop3, treeTop4, treeTop5, treeTop6, treeTop7, treeTop8, treeTop9, treeTop10, treeTop11};
        ImageView[] treeTrunks = {treeTrunk1, treeTrunk2, treeTrunk3, treeTrunk4, treeTrunk5, treeTrunk6, treeTrunk7, treeTrunk8, treeTrunk9, treeTrunk10, treeTrunk11};
        collectors.collectAWood(treeTops, treeTrunks, actions, playerImage, player, infoLabel, quantityOfWood);
    }

    /**Method that is responsible for collecting an iron without parameters.*/
    private void collectAnIron() {
        ImageView[] iron = {iron1, iron2, iron3, iron4, iron5, iron6, iron7, iron8, iron9, iron10};
        collectors.collectAnIron(iron, actions, playerImage, player, infoLabel, quantityOfIron);
    }

    /**Method that is responsible for setting HP without parameters.*/
    private void setHp() {
        ImageView[] hearts = {heart1, heart2, heart3, heart4, heart5, heart6, heart7, heart8, heart9, heart10};
        setters.setHp(player, hearts);
    }

    /**Method that is responsible for setting protection without parameters.*/
    private void setProtection() {
        ImageView[] shields = {shield1, shield2, shield3, shield4, shield5};
        setters.setProtection(player, shields);
    }
    /**Method that is responsible for setting thirst level without parameters.*/
    private void setThirstLvl() {
        ImageView[] water = {water1, water2, water3, water4, water5, water6, water7, water8, water9, water10,
                water11, water12, water13, water14, water15, water16, water17, water18, water19, water20};
        setters.setThirstLvl(player, water);
    }

    /**Method that is responsible for changing levels without parameters.*/
    private void changeLevel() {
        Label[] labels = {infoLabel, infoCraftsWeaponsLabel, infoCraftsDishesLabel, quantityOfPie, quantityOfIron, quantityOfWheat, quantityOfMeat, quantityOfWood, quantityOfSoup, quantityOfApple, quantityOfStone, quantityOfWater, quantityOfApple1, quantityOfIron1, quantityOfIron2, quantityOfIron3, quantityOfMeat1, quantityOfStone1,
                quantityOfStone2, quantityOfStone3, quantityOfWater1, quantityOfWater2, quantityOfWheat1, quantityOfWood1,
                quantityOfWood2, quantityOfWood3, quantityOfWood4, quantityOfWood5, quantityOfWood6, quantityOfWood7, quantityOfWood8,
                quantityOfWood9, additionSign1, additionSign2, additionSign3, additionSign4, additionSign5, additionSign6,
                additionSign7, additionSign8, additionSign9, equalSign1, equalSign10, equalSign11, equalSign2, equalSign3, equalSign4,
                equalSign5, equalSign6, equalSign7, equalSign8, equalSign9};
        ImageView[] inventoryItems = {craftsApple, craftsCell1, craftsCell10, craftsCell11, craftsCell12, craftsCell13, craftsCell14,
                craftsCell15, craftsCell16, craftsCell17, craftsCell18, craftsCell19, craftsCell2, craftsCell20, craftsCell21,
                craftsCell22, craftsCell23, craftsCell24, craftsCell25, craftsCell26, craftsCell27, craftsCell28, craftsCell29,
                craftsCell3, craftsCell30, craftsCell31, craftsCell32, craftsCell33, craftsCell34, craftsCell35, craftsCell36,
                craftsCell37, craftsCell38, craftsCell39, craftsCell4, craftsCell40, craftsCell41, craftsCell42, craftsCell43,
                craftsCell44, craftsCell46, craftsCell47, craftsCell48, craftsCell49, craftsCell5, craftsCell50, craftsCell51, craftsCell52,
                craftsCell6, craftsCell7, craftsCell8, craftsCell9, craftsIron1, craftsIron2, craftsIron3, craftsIronAxe,
                craftsIronShield, craftsIronSword, craftsMeat, craftsPie, craftsSoup, craftsStone1, craftsStone2, craftsStone3,
                craftsStoneAxe, craftsStoneShield, craftsStoneSword, craftsWater1, craftsWater2, craftsWheat, craftsWood1,
                craftsWood2, craftsWood3, craftsWood4, craftsWood5, craftsWood6, craftsWood7, craftsWood8, craftsWood9, craftsWoodenAxe,
                craftsWoodenShield, craftsWoodenSword, inventory, inventoryApple, inventoryIron, inventoryMeat, inventoryPie,
                inventorySoup, inventoryStone, inventoryWater, inventoryWood, inventoryWheat, woodenAxe, woodenShield, woodenSword,
                ironAxe, ironShield, ironSword, stoneAxe, stoneShield, stoneSword};
        ImageView[] hearts = {heart1, heart2, heart3, heart4, heart5, heart6, heart7, heart8, heart9, heart10};
        ImageView[] shields = {shield1, shield2, shield3, shield4, shield5};
        ImageView[] water = {water1, water2, water3, water4, water5, water6, water7, water8, water9, water10,
                water11, water12, water13, water14, water15, water16, water17, water18, water19, water20};
        levelChanger.change1stLvlOn2ndLvl(stage, playerImage, pane, obj1, obj2, obj3, hearts, shields, water, labels, inventoryItems);
        levelChanger.change2ndLvlOn1stLvl(stage, playerImage, pane, hearts, shields, water, labels, inventoryItems);
    }

    /**Method that is responsible for water consumption without parameters.*/
    @FXML
    void drinkWater(MouseEvent event) {
        consumers.drinkWater(event, actions, player, infoLabel, quantityOfWater);
    }

    /**Method that is responsible for apple consumption without parameters.*/
    @FXML
    void eatApple(MouseEvent event) {
        consumers.eatApple(event, actions, player, infoLabel, quantityOfApple);
    }

    /**Method that is responsible for pie consumption without parameters.*/
    @FXML
    void eatPie(MouseEvent event) {
        consumers.eatPie(event, actions, player, infoLabel, quantityOfPie);
    }

    /**Method that is responsible for soup consumption without parameters.*/
    @FXML
    void eatSoup(MouseEvent event) {
        consumers.eatSoup(event, actions, player, infoLabel, quantityOfSoup);
    }

    /**Method that is responsible for crafting a pie without parameters.*/
    @FXML
    void craftAPie(MouseEvent event) {
        crafts.craftAPie(event, player, actions, infoCraftsDishesLabel, quantityOfPie, quantityOfApple, quantityOfWheat, quantityOfWater);
    }

    /**Method that is responsible for crafting a soup without parameters.*/
    @FXML
    void craftASoup(MouseEvent event) {
        crafts.craftASoup(event, player, actions, infoCraftsDishesLabel, quantityOfSoup, quantityOfWater, quantityOfMeat);
    }

    /**Method that is responsible for crafting a wooden axe without parameters.*/
    @FXML
    void craftAWoodenAxe(MouseEvent event) {
        crafts.craftAWoodenAxe(event, player, actions, infoCraftsWeaponsLabel, woodenAxe, quantityOfWood);
    }

    /**Method that is responsible for crafting a wooden sword without parameters.*/
    @FXML
    void craftAWoodenSword(MouseEvent event) {
        crafts.craftAWoodenSword(event, player, actions, infoCraftsWeaponsLabel, woodenSword, quantityOfWood);
    }

    /**Method that is responsible for crafting a wooden shield without parameters.*/
    @FXML
    void craftAWoodenShield(MouseEvent event) {
        crafts.craftAWoodenShield(event, player, actions, infoCraftsWeaponsLabel, woodenShield, quantityOfWood);
    }

    /**Method that is responsible for crafting an iron axe without parameters.*/
    @FXML
    void craftAnIronAxe(MouseEvent event) {
        crafts.craftAnIronAxe(event, player, actions, infoCraftsWeaponsLabel, quantityOfWood, quantityOfIron, ironAxe, woodenAxe);
    }

    /**Method that is responsible for crafting an iron sword without parameters.*/
    @FXML
    void craftAnIronSword(MouseEvent event) {
        crafts.craftAnIronSword(event, player, actions, infoCraftsWeaponsLabel, quantityOfWood, quantityOfIron, ironSword, woodenSword);
    }

    /**Method that is responsible for crafting an iron shield without parameters.*/
    @FXML
    void craftAnIronShield(MouseEvent event) {
        crafts.craftAnIronShield(event, player, actions, infoCraftsWeaponsLabel, quantityOfWood, quantityOfIron, ironShield, woodenShield);
    }

    /**Method that is responsible for crafting a stone axe without parameters.*/
    @FXML
    void craftAStoneAxe(MouseEvent event) {
        crafts.craftAStoneAxe(event, player, actions, infoCraftsWeaponsLabel, quantityOfWood, quantityOfStone, stoneAxe, ironAxe);
    }

    /**Method that is responsible for crafting a stone sword without parameters.*/
    @FXML
    void craftAStoneSword(MouseEvent event) {
        crafts.craftAStoneSword(event, player, actions, infoCraftsWeaponsLabel, quantityOfWood, quantityOfStone, stoneSword, ironSword);
    }

    /**Method that is responsible for crafting a stone shield without parameters.*/
    @FXML
    void craftAStoneShield(MouseEvent event) {
        crafts.craftAStoneShield(event, player, actions, infoCraftsWeaponsLabel, quantityOfWood, quantityOfStone, stoneShield, ironShield);
    }

    /**Method that is responsible for initializing the animationTimer without parameters.*/
    @FXML
    void initialize() {
        gameControllerLogger.info("Animation timer started");
        animationTimer.start();
    }

}
