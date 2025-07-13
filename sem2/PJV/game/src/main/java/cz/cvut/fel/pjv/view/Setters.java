package cz.cvut.fel.pjv.view;

import cz.cvut.fel.pjv.model.characters.Knight;
import javafx.scene.image.ImageView;

/**Class that is responsible for setting HP/protection and thirst level.*/
public class Setters {

    /**Default constructor without parameters.*/
    public Setters() {

    }

    /**Method that is responsible for setting HP with parameters.
     * @param player player in Knight type.
     * @param hearts array with all (imageView)hearts.
     */
    public void setHp(Knight player, ImageView[] hearts) {
        for (int i = 0; i < player.getIntHp(); i++) {
            hearts[i].setVisible(true);
        }
        for (int i = player.getIntHp(); i < 10; i++) {
            hearts[i].setVisible(false);
        }
    }

    /**Method that is responsible for setting protection with parameters.
     * @param player player in Knight type.
     * @param shields array with all (imageView)shields.
     */
    public void setProtection(Knight player, ImageView[] shields) {
        for (int i = 0; i < player.getIntProtection(); i++) {
            shields[i].setVisible(true);
        }
        for (int i = player.getIntProtection(); i < 5; i++) {
            shields[i].setVisible(false);
        }
    }

    /**Method that is responsible for setting thirst level with parameters.
     * @param player player in Knight type.
     * @param water array with all (imageView)water.
     */
    public void setThirstLvl(Knight player, ImageView[] water) {
        for (int i = 0; i < player.getIntThirstLvl(); i++) {
            water[i].setVisible(true);
        }
        for (int i = player.getIntThirstLvl(); i < 20; i++) {
            water[i].setVisible(false);
        }
    }
}
