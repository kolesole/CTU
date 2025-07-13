package cz.cvut.fel.pjv.view;

import cz.cvut.fel.pjv.GameApplication;
import cz.cvut.fel.pjv.model.Actions;
import cz.cvut.fel.pjv.model.characters.Beast;
import cz.cvut.fel.pjv.model.characters.Knight;
import javafx.application.Platform;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import static cz.cvut.fel.pjv.GameApplication.beastThreadLogger;

/**Class that represents the behavior of boars implements Runnable.*/
public class BeastThread implements Runnable {

    /**boarImage in ImageView type.*/
    private ImageView boarImage;
    /**boar in Beast type.*/
    private Beast boar;
    /**playerImage in ImageView type.*/
    private ImageView playerImage;
    /**player in Knight type.*/
    private Knight player;
    /**actions in Actions type.*/
    private Actions actions;
    /**running in boolean type.*/
    private boolean running = true;
    /**MOVEMENT_SPEED in double type.*/
    private final double MOVEMENT_SPEED = 0.6;
    /**upImageIndex in int type.*/
    private int upImageIndex = 0;
    /**leftImageIndex in int type.*/
    private int leftImageIndex = 0;
    /**downImageIndex in int type.*/
    private int downImageIndex = 0;
    /**rightImageIndex in int type.*/
    private int rightImageIndex = 0;
    /**hitImageIndex in int type.*/
    private int hitImageIndex = 0;
    /**dieImageIndex in int type.*/
    private int dieImageIndex = 0;
    /**boarDirectionIsUp in boolean type.*/
    private boolean boarDirectionIsUp = false;
    /**boarDirectionIsLeft in boolean type.*/
    private boolean boarDirectionIsLeft = true;
    /**boarDirectionIsDown in boolean type.*/
    private boolean boarDirectionIsDown = false;
    /**boarDirectionIsRight in boolean type.*/
    private boolean boarDirectionIsRight = false;
    /**hit in boolean type.*/
    private boolean hit = false;
    /**die in boolean type.*/
    private boolean die = false;
    /**walkIteration in int type.*/
    private int walkIteration = 0;
    /**hitIteration in int type.*/
    private int hitIteration = 0;
    /**deathIteration in int type.*/
    private int deathIteration = 0;
    /**moveX in double type.*/
    private double moveX;
    /**moveY in double type.*/
    private double moveY;

    /**Constructor with parameters.
     * @param boarImage initial image for boarImage.
     * @param boar initial boar.
     * @param playerImage initial image for playerImage.
     * @param player initial player.
     * @param actions initial actions.
     */
    public BeastThread(ImageView boarImage, Beast boar, ImageView playerImage, Knight player, Actions actions) {
        this.boarImage = boarImage;
        this.playerImage = playerImage;
        this.boar = boar;
        this.player = player;
        this.actions = actions;
    }

    /**Method run Override from Runnable without parameters,
     * calculates the distance of the player,
     * determines when to hit and when the boar dies.
     */
    @Override
    public void run() {
        while (running) {
            Platform.runLater(() -> {
                if (hitIteration == 0) {
                    if (playerImage.getLayoutX() > boarImage.getLayoutX() - 20 && playerImage.getLayoutX() < boarImage.getLayoutX() + 20 &&
                            playerImage.getLayoutY() > boarImage.getLayoutY() - 20 && playerImage.getLayoutY() < boarImage.getLayoutY() + 20) {
                        hit = true;
                    } else {
                        hit = false;
                    }
                    if (!hit) {
                        double playerX = playerImage.getLayoutX();
                        double playerY = playerImage.getLayoutY();
                        double boarX = boarImage.getLayoutX();
                        double boarY = boarImage.getLayoutY();

                        double differenceX = playerX - boarX;
                        double differenceY = playerY - boarY;
                        if (walkIteration == 0) {
                            moveX = 0;
                            moveY = 0;
                            if ((Math.abs(differenceX) >= Math.abs(differenceY) && Math.abs(differenceX) > 1)) {
                                moveX = differenceX > 0 ? MOVEMENT_SPEED : -MOVEMENT_SPEED;
                            } else if (Math.abs(differenceY) > 1) {
                                moveY = differenceY > 0 ? MOVEMENT_SPEED : -MOVEMENT_SPEED;
                            }
                        }
                        if (moveX != 0 || moveY != 0) {
                            updateBoarWalk(moveX, moveY);
                            boarImage.setLayoutX(boarX + moveX);
                            boarImage.setLayoutY(boarY + moveY);
                            walkIteration++;
                            if (playerImage.getLayoutX() > boarImage.getLayoutX() - 20 && playerImage.getLayoutX() < boarImage.getLayoutX() + 20 &&
                                    playerImage.getLayoutY() > boarImage.getLayoutY() - 20 && playerImage.getLayoutY() < boarImage.getLayoutY() + 20) {
                                hit = true;
                                walkIteration = 0;
                            }
                        }
                        if (walkIteration == 50) walkIteration = 0;
                    }
                }
                if (hit && !die) {
                    if (GameController.hit) {
                        beastThreadLogger.info("Player is hitting the boar");
                        actions.doHit(player, boar);
                    }
                    if (actions.occurrenceOfDeath(boar))  die = true;
                    do_hit();
                    hitIteration++;
                }
                if (actions.occurrenceOfPlayersDeath(player) || !GameApplication.gameIsRunning) stop();
                if (die) {
                    occurrenceOfBeastDeath();
                    deathIteration++;
                }
                if (deathIteration == 14) {
                    beastThreadLogger.info("Boar died, thread stopped");
                    stop();
                }
                if (hitIteration == 30) {
                    hitIteration = 0;
                    actions.doHit(boar, player);
                }
            });
            try {
                Thread.sleep(25);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

        }
    }

    /**Method that is responsible for the movement of the boar with parameters.
     * @param moveX if less than 0, the boar move along the x-axis to the left.
     *              if more than 0, the boar move along the x-axis to the right.
     * @param moveY if less than 0, the boar move along the y-axis to the up.
     *              if more than 0, the boar move along the Y-axis to the down.
     */
    private void updateBoarWalk(double moveX, double moveY) {
        if (moveX < 0) {
            leftImageIndex = (leftImageIndex + 1) % 16;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/walk/BoarWalk_1" + (leftImageIndex / 4 + 1) + ".png"));
            beastThreadLogger.info("Boar is going left");
            boarDirectionIsUp = false;
            boarDirectionIsLeft = true;
            boarDirectionIsDown = false;
            boarDirectionIsRight = false;
        }
        else if (moveX > 0) {
            rightImageIndex = (rightImageIndex + 1) % 16;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/walk/BoarWalk_3" + (rightImageIndex / 4 + 1) + ".png"));
            beastThreadLogger.info("Boar is going right");
            boarDirectionIsUp = false;
            boarDirectionIsLeft = false;
            boarDirectionIsDown = false;
            boarDirectionIsRight = true;
        }
        else if (moveY < 0) {
            upImageIndex = (upImageIndex + 1) % 16;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/walk/BoarWalk_0" + (upImageIndex / 4 + 1) + ".png"));
            beastThreadLogger.info("Boar is going up");
            boarDirectionIsUp = true;
            boarDirectionIsLeft = false;
            boarDirectionIsDown = false;
            boarDirectionIsRight = false;
        }
        else if (moveY > 0) {
            downImageIndex = (downImageIndex + 1) % 16;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/walk/BoarWalk_2" + (downImageIndex / 4 + 1) + ".png"));
            beastThreadLogger.info("Boar is going down");
            boarDirectionIsUp = false;
            boarDirectionIsLeft = false;
            boarDirectionIsDown = true;
            boarDirectionIsRight = false;
        }
    }

    /**Method that is responsible for the hit of the boat(called when boars coordinates are equal to players coordinates) without parameters.*/
    private void do_hit() {
        if (boarDirectionIsUp) {
            hitImageIndex = (hitImageIndex + 1) % 36;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/hit/BoarAttack_0" + (hitImageIndex / 6 + 1) + ".png"));
            beastThreadLogger.warning("Boar is doing hit a upward direction");
        }
        else if (boarDirectionIsLeft) {
            hitImageIndex = (hitImageIndex + 1) % 36;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/hit/BoarAttack_1" + (hitImageIndex / 6 + 1) + ".png"));
            beastThreadLogger.warning("Boar is doing hit a leftward direction");
        }
        else if (boarDirectionIsDown) {
            hitImageIndex = (hitImageIndex + 1) % 36;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/hit/BoarAttack_2" + (hitImageIndex / 6 + 1) + ".png"));
            beastThreadLogger.warning("Boar is doing hit a downward direction");
        }
        else if (boarDirectionIsRight) {
            hitImageIndex = (hitImageIndex + 1) % 36;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/hit/BoarAttack_3" + (hitImageIndex / 6 + 1) + ".png"));
            beastThreadLogger.warning("Boar is doing hit a rightward direction");
        }
    }

    /**Method that is responsible for the death of the boar(gradually change images when thw boar dies) without parameters.*/
    private void occurrenceOfBeastDeath() {
        if (boarDirectionIsUp) {
            dieImageIndex = (dieImageIndex + 1) % 16;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/die/BoarDie_0" + (dieImageIndex / 4 + 1) + ".png"));
        }
        else if (boarDirectionIsLeft) {
            dieImageIndex = (dieImageIndex + 1) % 16;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/die/BoarDie_1" + (dieImageIndex / 4 + 1) + ".png"));
        }
        else if (boarDirectionIsDown) {
            dieImageIndex = (dieImageIndex + 1) % 16;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/die/BoarDie_2" + (dieImageIndex / 4 + 1) + ".png"));
        }
        else if (boarDirectionIsRight) {
            dieImageIndex = (dieImageIndex + 1) % 16;
            boarImage.setImage(new Image("/images/enemies/2-nd/boar/die/BoarDie_3" + (dieImageIndex / 4 + 1) + ".png"));
        }
    }

    /**Method that is responsible for stopping the thread without parameters.*/
    public void stop() {
        running = false;
    }
}