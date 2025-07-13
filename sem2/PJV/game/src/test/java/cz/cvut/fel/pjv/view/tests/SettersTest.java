package cz.cvut.fel.pjv.view.tests;

import cz.cvut.fel.pjv.model.characters.Knight;
import cz.cvut.fel.pjv.view.Setters;
import javafx.scene.image.ImageView;
import org.junit.jupiter.api.Test;

import java.util.Random;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**Class that tests the Setters.java*/
public class SettersTest {

    /**Test method for method setHp(---//---) from Setters.java without parameters.*/
    @Test
    public void setHpTest() {
        Random random = new Random();
        Setters setters = new Setters();

        Knight player = new Knight(random.nextInt(1, 11), 20);
        ImageView[] hearts = new ImageView[10];
        for (int i = 0; i < 10; i++) {
            hearts[i] = new ImageView();
            hearts[i].setVisible(false);
        }

        setters.setHp(player, hearts);

        for (int i = 0; i < player.getIntHp(); i++) {
            assertTrue(hearts[i].isVisible(), "After the set a HP, the heart image with num < players HP should be visible, but it is invisible");
        }

        for (int i = player.getIntHp(); i < 10; i++) {
            assertTrue(!hearts[i].isVisible(), "After the set a HP, the heart image with num >= players HP should be invisible, but it is visible");
        }
    }

    /**Test method for method setProtection(---//---) from Setters.java without parameters.*/
    @Test
    public void setProtectionTest() {
        Random random = new Random();
        Setters setters = new Setters();

        Knight player = new Knight(10, 20);
        player.changeProtection(random.nextInt(1, 6));

        ImageView[] shields = new ImageView[5];
        for (int i = 0; i < 5; i++) {
            shields[i] = new ImageView();
            shields[i].setVisible(false);
        }

        setters.setProtection(player, shields);

        for (int i = 0; i < player.getIntProtection(); i++) {
            assertTrue(shields[i].isVisible(), "After the set a protection, the shield image with num < players protection should be visible, but it is invisible");
        }

        for (int i = player.getIntProtection(); i < 5; i++) {
            assertTrue(!shields[i].isVisible(), "After the set a protection, the shield image with num >= players protection should be invisible, but it is visible");
        }
    }

    /**Test method for method setThirstLvl(---//---) from Setters.java without parameters.*/
    @Test
    public void setThirstLvlTest() {
        Random random = new Random();
        Setters setters = new Setters();

        Knight player = new Knight(10, random.nextInt(1, 21));
        ImageView[] water = new ImageView[20];
        for (int i = 0; i < 20; i++) {
            water[i] = new ImageView();
            water[i].setVisible(false);
        }

        setters.setThirstLvl(player, water);

        for (int i = 0; i < player.getIntThirstLvl(); i++) {
            assertTrue(water[i].isVisible(), "After the set a thirst level, the water image with num < players thirst level should be visible, but it is invisible");
        }

        for (int i = player.getIntThirstLvl(); i < 20; i++) {
            assertTrue(!water[i].isVisible(), "After the set a thirst level, the shield image with num >= players thirst level should be invisible, but it is visible");
        }
    }



}
