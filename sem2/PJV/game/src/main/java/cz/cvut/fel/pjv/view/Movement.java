package cz.cvut.fel.pjv.view;

import javafx.scene.image.ImageView;

import static cz.cvut.fel.pjv.GameApplication.movementLogger;
import static cz.cvut.fel.pjv.view.GameController.*;

/**Class that is responsible for the players movement,
 * checks if the players coordinates do not coincide with invisible walls.*/
public class Movement {

    /**playerImage in ImageView type.*/
    private ImageView playerImage;

    /**Constructor with parameters.
     * @param playerImage initial image for playerImage.
     */
    public Movement(ImageView playerImage) {
        this.playerImage = playerImage;
    }

    /**Method checks if the players coordinates do not coincide with left invisible walls without parameters.
     * @return true if possible move to left.
     */
    public boolean isPossibleMoveToLeft() {
        if (!left) return false;
        movementLogger.info("Player trying to go left");
        if (
                (playerImage.getLayoutX() < 129 && playerImage.getLayoutY() < 126) ||
                (playerImage.getLayoutX() < 161 && playerImage.getLayoutY() > 118 && playerImage.getLayoutY() < 216) ||
                (playerImage.getLayoutX() < 255 && playerImage.getLayoutY() > 215 && playerImage.getLayoutY() < 426) ||
                (playerImage.getLayoutX() < 255 && playerImage.getLayoutX() > 232 && playerImage.getLayoutY() > 425 && playerImage.getLayoutY() < 463) ||
                (playerImage.getLayoutX() < 188 && playerImage.getLayoutY() > 438 && playerImage.getLayoutY() < 505) ||
                (playerImage.getLayoutX() < 255 && playerImage.getLayoutY() > 493 && playerImage.getLayoutY() < 531 ) ||
                (playerImage.getLayoutX() < 247 && playerImage.getLayoutY() > 531 && playerImage.getLayoutY() < 562) ||
                (playerImage.getLayoutX() < 255 && playerImage.getLayoutY() > 561 && playerImage.getLayoutY() < 600) ||
                (playerImage.getLayoutX() < 193 && playerImage.getLayoutY() > 560) ||
                (playerImage.getLayoutX() < 259 && playerImage.getLayoutX() > 239 && playerImage.getLayoutY() > 621) ||
                (playerImage.getLayoutX() < 292 && playerImage.getLayoutX() > 262 && playerImage.getLayoutY() < 210) ||
                (playerImage.getLayoutX() < 416 && playerImage.getLayoutX() > 368 && playerImage.getLayoutY() > 211 && playerImage.getLayoutY() < 291) ||
                (playerImage.getLayoutX() < 416 && playerImage.getLayoutX() > 355 && playerImage.getLayoutY() > 336 && playerImage.getLayoutY() < 397) ||
                (playerImage.getLayoutX() < 793 && playerImage.getLayoutX() > 747 && playerImage.getLayoutY() > 330) ||
                (playerImage.getLayoutX() < 792 && playerImage.getLayoutX() > 747 && playerImage.getLayoutY() < 262) ||
                (playerImage.getLayoutX() < 879 && playerImage.getLayoutX() > 748 && playerImage.getLayoutY() > 420)
            ) {
            movementLogger.warning("Player has encountered an obstacle!");
            return false;
        }
        movementLogger.info("Player going left");
        return true;
    }

    /**Method checks if the players coordinates do not coincide with right invisible walls with parameters.
     * @param obj1 in ImageView type,
     *             one of the objects that disappears when opening the second level.
     * @param obj2 in ImageView type,
     *             one of the objects that disappears when opening the second level.
     * @param obj3 in ImageView type,
     *             one of the objects that disappears when opening the second level.
     * @return true if possible move to right.
     */
    public boolean isPossibleMoveToRight(ImageView obj1, ImageView obj2, ImageView obj3) {
        if (!right) return false;
        movementLogger.info("Player trying to go right");
        if (!obj1.isVisible() && !obj2.isVisible() && !obj3.isVisible()) {
            if (playerImage.getLayoutX() > 739 && playerImage.getLayoutX() < 800 && playerImage.getLayoutY() > 262 && playerImage.getLayoutY() < 330) {
                movementLogger.info("Player goes right");
                return true;
            }
        }
        if (
                (playerImage.getLayoutX() > 225 && playerImage.getLayoutY() < 19) ||
                (playerImage.getLayoutX() > 261 && playerImage.getLayoutX() < 291 && playerImage.getLayoutY() > 19 && playerImage.getLayoutY() < 293) ||
                (playerImage.getLayoutX() > 230 && playerImage.getLayoutX() < 253 && playerImage.getLayoutY() > 425 && playerImage.getLayoutY() < 463) ||
                (playerImage.getLayoutX() > 236 && playerImage.getLayoutX() < 258 && playerImage.getLayoutY() > 621) ||
                (playerImage.getLayoutX() > 288 && playerImage.getLayoutX() < 382 && playerImage.getLayoutY() > 433) ||
                (playerImage.getLayoutX() > 334 && playerImage.getLayoutX() < 410 && playerImage.getLayoutY() > 335 && playerImage.getLayoutY() < 433) ||
                (playerImage.getLayoutX() > 742 && playerImage.getLayoutX() < 781) ||
                (playerImage.getLayoutX() > 1048 && playerImage.getLayoutY() > 420) ||
                (playerImage.getLayoutX() > 1311)
            ) {
            movementLogger.warning("Player has encountered an obstacle!");
            return false;
        }
        movementLogger.info("Player going right");
        return true;
    }

    /**Method checks if the players coordinates do not coincide with up invisible walls without parameters.
     * @return true if possible move to up.
     */
    public boolean isPossibleMoveToUp() {
        if (!up) return false;
        movementLogger.info("Player trying to go up");
        if (
                (playerImage.getLayoutX() > 226 && playerImage.getLayoutY() < 20) ||
                (playerImage.getLayoutX() < 234 && playerImage.getLayoutX() > 178 && playerImage.getLayoutY() < 450 && playerImage.getLayoutY() > 214) ||
                (playerImage.getLayoutX() < 254 && playerImage.getLayoutX() > 232 && playerImage.getLayoutY() < 472 && playerImage.getLayoutY() > 443) ||
                (playerImage.getLayoutX() < 254 && playerImage.getLayoutY() > 493 && playerImage.getLayoutY() < 532) ||
                (playerImage.getLayoutX() < 254 && playerImage.getLayoutY() > 562 && playerImage.getLayoutY() < 601) ||
                (playerImage.getLayoutX() < 415 && playerImage.getLayoutX() > 263 && playerImage.getLayoutY() < 294 && playerImage.getLayoutY() > 239) ||
                (playerImage.getLayoutX() > 747 && playerImage.getLayoutX() < 791 && playerImage.getLayoutY() < 263) ||
                (playerImage.getLayoutX() > 781 && playerImage.getLayoutY() < 157)
            ) {
            movementLogger.warning("Player has encountered an obstacle!");
            return false;
        }
        movementLogger.info("Player going up");
        return true;
    }

    /**Method checks if the players coordinates do not coincide with down invisible walls without parameters.
     * @return true if possible move to down.
     */
    public boolean isPossibleMoveToDown() {
        if (!down) return false;
        movementLogger.info("Player trying to go down");
        if (
                (playerImage.getLayoutX() < 160 && playerImage.getLayoutY() > 116) ||
                (playerImage.getLayoutX() < 254 && playerImage.getLayoutY() > 213 && playerImage.getLayoutY() < 426) ||
                (playerImage.getLayoutX() < 254 && playerImage.getLayoutY() > 492 && playerImage.getLayoutY() < 531) ||
                (playerImage.getLayoutX() < 254 && playerImage.getLayoutY() > 561 && playerImage.getLayoutY() < 594) ||
                (playerImage.getLayoutY() > 641 && playerImage.getLayoutX() < 331) ||
                (playerImage.getLayoutX() < 258 && playerImage.getLayoutX() > 238 && playerImage.getLayoutY() > 620) ||
                (playerImage.getLayoutX() > 290 && playerImage.getLayoutX() < 336 && playerImage.getLayoutY() > 430) ||
                (playerImage.getLayoutX() > 338 && playerImage.getLayoutX() < 415 && playerImage.getLayoutY() > 334 && playerImage.getLayoutY() < 433) ||
                (playerImage.getLayoutX() > 414 && playerImage.getLayoutX() < 779 && playerImage.getLayoutY() > 372) ||
                (playerImage.getLayoutX() > 290 && playerImage.getLayoutX() < 415 && playerImage.getLayoutY() > 209 && playerImage.getLayoutY() < 269) ||
                (playerImage.getLayoutX() > 747 && playerImage.getLayoutX() < 792 && playerImage.getLayoutY() > 329) ||
                (playerImage.getLayoutX() > 782 && playerImage.getLayoutX() < 878 && playerImage.getLayoutY() > 419) ||
                (playerImage.getLayoutX() > 1049 && playerImage.getLayoutY() > 419)
            ) {
            movementLogger.warning("Player has encountered an obstacle!");
            return false;
        }
        movementLogger.info("Player going down");
        return true;
    }
}
