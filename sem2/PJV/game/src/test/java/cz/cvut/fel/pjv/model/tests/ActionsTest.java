package cz.cvut.fel.pjv.model.tests;

import cz.cvut.fel.pjv.model.Actions;
import cz.cvut.fel.pjv.model.characters.Beast;
import cz.cvut.fel.pjv.model.characters.Knight;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;

/*Class that checks the Actions class.*/
public class ActionsTest {

    private final Actions actionsTest = new Actions();

    /**Test method for method doHit(---//---) from Actions.java without parameters.*/
    @Test
    public void doHitTest() {
        Knight knightTest1 = new Knight(10, 20);
        knightTest1.changeProtection(5);
        Knight knightTest2 = new Knight(10, 20);
        knightTest2.changeDamage(1);
        Beast beastTest = new Beast(20, 5);
        actionsTest.doHit(beastTest, knightTest1);
        assertTrue(knightTest1.getIntProtection() == 0, "After a beast hits a knight, the knights protection should be 0, not" + knightTest1.getIntProtection());
        assertTrue(knightTest1.getIntHp() == 10, "After a beast hits a knight, the knights HP should be 10, not" + knightTest1.getIntHp());
        actionsTest.doHit(beastTest, knightTest2);
        assertTrue(knightTest2.getIntProtection() == 0, "After a beast hits a knight, the knights protection should be 0, not" + knightTest2.getIntProtection());
        assertTrue(knightTest2.getIntHp() == 5, "After a beast hits a knight, the knights HP should be 5, not" + knightTest2.getIntHp());
        actionsTest.doHit(knightTest2, beastTest);
        assertTrue(beastTest.getIntHp() == 19, "After a knight hits a beast, the beasts HP should be 19, not" + beastTest.getIntHp());
    }

    /**Test method for method occurrenceOfDeath(---//---) from Actions.java without parameters.*/
    @Test
    public void occurrenceOfDeathTest() {
        Beast beastTest = new Beast(0, 5);
        boolean retTest = actionsTest.occurrenceOfDeath(beastTest);
        assertTrue(retTest, "After the end of all the beasts HP, the function should return true, not " + retTest);
    }

    /**Test method for method occurrenceOfPlayersDeath(---//---) from Actions.java without parameters.*/
    @Test
    public void occurrenceOfPlayersDeathTest() {
        Knight knightTest1 = new Knight(0, 20);
        Knight knightTest2 = new Knight(10, 0);
        boolean retTest1 = actionsTest.occurrenceOfPlayersDeath(knightTest1);
        assertTrue(retTest1, "After the end of all the knights HP, the function should return true, not " + retTest1);
        boolean retTest2 = actionsTest.occurrenceOfPlayersDeath(knightTest2);
        assertTrue(retTest2, "After the end of all the knights thirst points, the function should return true, not " + retTest2);
    }

    /**Test method for method collectAnApple(---//---) from Actions.java without parameters.*/
    @Test
    public void collectAnAppleTest() {
        Knight knightTest = new Knight(10, 20);
        actionsTest.collectAnApple(knightTest);
        assertTrue(knightTest.inventory.apple.getQuantity() == 1, "After the collect an apple, the apple quantity should be 1, not " + knightTest.inventory.apple.getQuantity());
    }

    /**Test method for method collectAMeat(---//---) from Actions.java without parameters.*/
    @Test
    public void collectAMeatTest() {
        Knight knightTest = new Knight(10, 20);
        actionsTest.collectAMeat(knightTest);
        assertTrue(knightTest.inventory.meat.getQuantity() == 1, "After the collect a meat, the meat quantity should be 1, not " + knightTest.inventory.meat.getQuantity());
    }

    /**Test method for method collectAWheat(---//---) from Actions.java without parameters.*/
    @Test
    public void collectAWheat() {
        Knight knightTest = new Knight(10, 20);
        actionsTest.collectAWheat(knightTest);
        assertTrue(knightTest.inventory.wheat.getQuantity() == 1, "After the collect a wheat, the wheat quantity should be 1, not " + knightTest.inventory.wheat.getQuantity());
    }

    /**Test method for method collectAWater(---//---) from Actions.java without parameters.*/
    @Test
    public void collectAWater() {
        Knight knightTest = new Knight(10, 20);
        actionsTest.collectAWater(knightTest);
        assertTrue(knightTest.inventory.water.getQuantity() == 1, "After the collect a water, the water quantity should be 1, not " + knightTest.inventory.water.getQuantity());
    }

    /**Test method for method collectAWood(---//---) from Actions.java without parameters.*/
    @Test
    public void collectAWoodTest() {
        Knight knightTest = new Knight(10, 20);
        actionsTest.collectAWood(knightTest);
        assertTrue(knightTest.inventory.wood.getQuantity() == knightTest.getIntDamageToMaterials(), "After the collect a wood, the wood quantity should be " + knightTest.getIntDamageToMaterials() + ", not " + knightTest.inventory.wood.getQuantity());
    }

    /**Test method for method collectAnIron(---//---) from Actions.java*/
    @Test
    public void collectAnIronTest() {
        Knight knightTest = new Knight(10, 20);
        actionsTest.collectAnIron(knightTest);
        assertTrue(knightTest.inventory.iron.getQuantity() == knightTest.getIntDamageToMaterials(), "After the collect an iron, the iron quantity should be " + knightTest.getIntDamageToMaterials() + ", not " + knightTest.inventory.iron.getQuantity());
    }

    /**Test method for method collectAStone(---//---) from Actions.java without parameters.*/
    @Test
    public void collectAStoneTest() {
        Knight knightTest = new Knight(10, 20);
        actionsTest.collectAStone(knightTest);
        assertTrue(knightTest.inventory.stone.getQuantity() == knightTest.getIntDamageToMaterials(), "After the collect a stone, the stone quantity should be " + knightTest.getIntDamageToMaterials() + ", not " + knightTest.inventory.stone.getQuantity());
    }

    /**Test method for method drinkWater(---//---) from Actions.java without parameters.*/
    @Test
    public void drinkWaterTest() {
        Knight knightTest = new Knight(10, 10);
        knightTest.changeThirstLvl(-1);
        knightTest.inventory.water.changeQuantity(+1);
        actionsTest.drinkWater(knightTest);
        assertTrue(knightTest.getIntThirstLvl() == 10, "After the drink water, the players thirst level should be 10, not " + knightTest.getIntThirstLvl());
    }

    /**Test method for method eatApple(---//---) from Actions.java without parameters.*/
    @Test
    public void eatAppleTest() {
        Knight knightTest = new Knight(10, 10);
        knightTest.changeHp(-1);
        knightTest.inventory.apple.changeQuantity(+1);
        actionsTest.eatApple(knightTest);
        assertTrue(knightTest.getIntHp() == 10, "After the eat apple, the players HP should be 10, not " + knightTest.getIntHp());
    }

    /**Test method for method eatPie(---//---) from Actions.java without parameters.*/
    @Test
    public void eatPieTest() {
        Knight knightTest = new Knight(10, 10);
        knightTest.changeHp(-5);
        knightTest.inventory.pie.changeQuantity(+1);
        actionsTest.eatPie(knightTest);
        assertTrue(knightTest.getIntHp() == 8, "After the eat pie, the players Hp should be 8, not " + knightTest.getIntHp());
    }

    /**Test method for method eatSoup(---//---) from Actions.java without parameters.*/
    @Test
    public void eatSoupTest() {
        Knight knightTest = new Knight(10, 10);
        knightTest.changeHp(-6);
        knightTest.inventory.soup.changeQuantity(+1);
        actionsTest.eatSoup(knightTest);
        assertTrue(knightTest.getIntHp() == 9, "After the eat soup, the players Hp should be 9, not " + knightTest.getIntHp());
    }

    /**Test method for method craftAPie(---//---) from Actions.java without parameters.*/
    @Test
    public void craftAPieTest() {
        Knight knightTest = new Knight(10, 20);
        knightTest.inventory.apple.changeQuantity(+2);
        knightTest.inventory.water.changeQuantity(+2);
        knightTest.inventory.wheat.changeQuantity(+2);
        actionsTest.craftAPie(knightTest);
        assertTrue(knightTest.inventory.pie.getQuantity() == 1, "After the craft a pie, the pies quantity should be 1, not " + knightTest.inventory.pie.getQuantity());
    }

    /**Test method for method craftASoup(---//---) from Actions.java without parameters.*/
    @Test
    public void craftASoupTest() {
        Knight knightTest = new Knight(10, 20);
        knightTest.inventory.water.changeQuantity(+3);
        knightTest.inventory.meat.changeQuantity(+1);
        actionsTest.craftASoup(knightTest);
        assertTrue(knightTest.inventory.soup.getQuantity() == 1, "After the craft a soup, the soup quantity should be 1, not " + knightTest.inventory.soup.getQuantity());
    }

    /**Test method for method craftAWoodenSword(---//---) from Actions.java without parameters.*/
    @Test
    public void craftAWoodenSwordTest() {
        Knight knightTest = new Knight(10, 20);
        knightTest.inventory.wood.changeQuantity(+3);
        actionsTest.craftAWoodenSword(knightTest);
        assertTrue(knightTest.getIntDamage() == 2, "After the craft a wooden sword, the knights damage should be 2, not " + knightTest.getIntDamage());
    }

    /**Test method for method craftAWoodenShield(---//---) from Actions.java without parameters.*/
    @Test
    public void craftAWoodenShieldTest() {
        Knight knightTest = new Knight(10, 20);
        knightTest.inventory.wood.changeQuantity(+4);
        actionsTest.craftAWoodenShield(knightTest);
        assertTrue(knightTest.getIntProtection() == 1, "After the craft a wooden shield, the knights protection should be 1, not " + knightTest.getIntProtection());
    }

    /**Test method for method craftAnIronAxe(---//---) from Actions.java without parameters.*/
    @Test
    public void craftAnIronAxeTest() {
        Knight knightTest = new Knight(10, 20);
        knightTest.inventory.wood.changeQuantity(+1);
        knightTest.inventory.iron.changeQuantity(+1);
        actionsTest.craftAnIronAxe(knightTest);
        assertTrue(knightTest.getIntDamageToMaterials() == 5, "After the craft an iron axe, the knights damage to materials should be 5, not " + knightTest.getIntDamageToMaterials());
    }

    /**Test method for method craftAnIronSword(---//---) from Actions.java without parameters.*/
    @Test
    public void craftAnIronSwordTest() {
        Knight knightTest = new Knight(10, 20);
        knightTest.inventory.wood.changeQuantity(+1);
        knightTest.inventory.iron.changeQuantity(+2);
        actionsTest.craftAnIronSword(knightTest);
        assertTrue(knightTest.getIntDamage() == 6, "After the craft an iron sword, the knights damage should be 6, not " + knightTest.getIntDamage());
    }

    /**Test method for method craftAnIronShield(---//---) from Actions.java without parameters.*/
    @Test
    public void craftAnIronShieldTest() {
        Knight knightTest = new Knight(10, 20);
        knightTest.inventory.wood.changeQuantity(+1);
        knightTest.inventory.iron.changeQuantity(+3);
        actionsTest.craftAnIronShield(knightTest);
        assertTrue(knightTest.getIntProtection() == 3, "After the craft an iron shield, the knights protection should be 3, not " + knightTest.getIntProtection());
    }

    /**Test method for method craftAStoneAxe(---//---) from Actions.java without parameters.*/
    @Test
    public void craftAStoneAxeTest() {
        Knight knightTest = new Knight(10, 20);
        knightTest.inventory.wood.changeQuantity(+1);
        knightTest.inventory.stone.changeQuantity(+1);
        actionsTest.craftAStoneAxe(knightTest);
        assertTrue(knightTest.getIntDamageToMaterials() == 10, "After the craft a stone axe, the knights damage to materials should be 10, not " + knightTest.getIntDamageToMaterials());
    }

    /**Test method for method craftAStoneSword(---//---) from Actions.java without parameters.*/
    @Test
    public void craftAStoneSwordTest() {
        Knight knightTest = new Knight(10, 20);
        knightTest.inventory.wood.changeQuantity(+1);
        knightTest.inventory.stone.changeQuantity(+2);
        actionsTest.craftAStoneSword(knightTest);
        assertTrue(knightTest.getIntDamage() == 10, "After the craft a stone sword, the knights damage should be 10, not " + knightTest.getIntDamage());
    }

    /**Test method for method craftAStoneShield(---//---) from Actions.java without parameters.*/
    @Test
    public void craftAStoneShieldTest() {
        Knight knightTest = new Knight(10, 20);
        knightTest.inventory.wood.changeQuantity(+1);
        knightTest.inventory.stone.changeQuantity(+3);
        actionsTest.craftAStoneShield(knightTest);
        assertTrue(knightTest.getIntProtection() == 5, "After the craft a stone shield, the knights protection should be 5, not " + knightTest.getIntProtection());
    }
}
