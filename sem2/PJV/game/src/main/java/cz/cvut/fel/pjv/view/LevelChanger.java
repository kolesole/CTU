package cz.cvut.fel.pjv.view;

import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import static cz.cvut.fel.pjv.GameApplication.levelChangerLogger;

/**Class that is responsible for changing levels.*/
public class LevelChanger {

    /**isFirstLvl in boolean type.*/
    public static boolean isFirstLvl = true;
    /**isSecondLvl in boolean type.*/
    public static boolean isSecondLvl = false;
    /**isThirdLvl in boolean type.*/
    public static boolean isThirdLvl = false;

    /**Default constructor without parameters.*/
    public LevelChanger() {

    }

    /**Method that is responsible for changing 1-st level on 2-nd.
     * @param stage main stage in Stage type.
     * @param playerImage player image.
     * @param pane main pane in AnchorPane type.
     * @param obj1 in ImageView type,
     *             one of the objects that disappears when opening the second level.
     * @param obj2 in ImageView type,
     *             one of the objects that disappears when opening the second level.
     * @param obj3 in ImageView type,
     *             one of the objects that disappears when opening the second level.
     * @param hearts array with all (ImageView)hearts.
     * @param shields array with all (ImageView)shields.
     * @param water array with all (ImageView)water.
     * @param labels array with all the labels in type Label that need to be transferred from the first level to the second.
     * @param inventoryItems array with all inventory items in type ImageView that need to be transferred from the first level to the second.
     */
    public void change1stLvlOn2ndLvl(Stage stage, ImageView playerImage, AnchorPane pane, ImageView obj1, ImageView obj2, ImageView obj3, ImageView[] hearts, ImageView[] shields, ImageView[] water, Label[] labels, ImageView[] inventoryItems) {
        if (!obj1.isVisible() && !obj2.isVisible() && !obj3.isVisible() && playerImage.getLayoutX() > 775 && isFirstLvl) {
            for (ImageView heart : hearts) {
                heart.setLayoutX(heart.getLayoutX() + 720);
            }
            for (ImageView shield : shields) {
                shield.setLayoutX(shield.getLayoutX() + 720);
            }
            for (ImageView w : water) {
                w.setLayoutX(w.getLayoutX() + 720);
            }
            for (Label label : labels) {
                label.setLayoutX(label.getLayoutX() + 1150);
            }
            for (ImageView inventoryItem : inventoryItems) {
                inventoryItem.setLayoutX(inventoryItem.getLayoutX() + 1150);
            }
            stage.setWidth(688);
            pane.setLayoutX(pane.getLayoutX() - 800);
            isFirstLvl = false;
            isSecondLvl = true;
            levelChangerLogger.info("Changing level 1-->2");
        }
    }

    /**Method that is responsible for changing 2-nd level on 1-st.
     * @param stage main stage in Stage type.
     * @param playerImage player image.
     * @param pane main pane in AnchorPane type.
     * @param hearts array with all (ImageView)hearts.
     * @param shields array with all (ImageView)shields.
     * @param water array with all (ImageView)water.
     * @param labels array with all the labels in type Label that need to be transferred from the second level to the first.
     * @param inventoryItems array with all inventory items in type ImageView that need to be transferred from the second level to the first.
     */
    public void change2ndLvlOn1stLvl(Stage stage, ImageView playerImage, AnchorPane pane, ImageView[] hearts, ImageView[] shields, ImageView[] water, Label[] labels, ImageView[] inventoryItems) {
        if (playerImage.getLayoutX() < 775 && isSecondLvl) {
            for (ImageView heart : hearts) {
                heart.setLayoutX(heart.getLayoutX() - 720);
            }
            for (ImageView shield : shields) {
                shield.setLayoutX(shield.getLayoutX() - 720);
            }
            for (ImageView w : water) {
                w.setLayoutX(w.getLayoutX() - 720);
            }
            for (Label label : labels) {
                label.setLayoutX(label.getLayoutX() - 1150);
            }
            for (ImageView inventoryItem : inventoryItems) {
                inventoryItem.setLayoutX(inventoryItem.getLayoutX() - 1150);
            }
            stage.setWidth(800);
            pane.setLayoutX(pane.getLayoutX() + 800);
            isFirstLvl = true;
            isSecondLvl = false;
            levelChangerLogger.info("Changing level 2-->1");
        }
    }

    /**Method that is responsible for changing 2-nd level on 3-rd.
     * Note: the method is unfinished and not working.
     */
    public void change2ndLvlOn3rdLvl() {

    }

    /**Method that is responsible for changing 3-rd level on 2-nd.
     * Note: the method is unfinished and not working.
     */
    public void change3rdLvlOn2ndLvl() {

    }
}