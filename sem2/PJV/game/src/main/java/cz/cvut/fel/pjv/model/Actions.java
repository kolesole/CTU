package cz.cvut.fel.pjv.model;

import cz.cvut.fel.pjv.model.characters.CharacterModel;
import cz.cvut.fel.pjv.model.characters.Knight;
import cz.cvut.fel.pjv.model.items.weapons.Material;

/**Class with all possible actions in the game.*/
public class Actions {

    /**Default constructor without parameters.*/
    public Actions() {

    }

    /**Method for reducing the HP of a player or mob with parameters.
     * @param o1 object that hit.
     * @param o2 objects that take a hit.
     */
    public void doHit(CharacterModel o1, CharacterModel o2) {
        if (o2.getClass() == Knight.class) {
            int o1Damage = o1.getIntDamage();
            int temp = ((Knight)o2).getIntProtection() - o1.getIntDamage();
            if (temp <= 0) {
                ((Knight)o2).changeProtection(0);
                o2.changeHp(temp);
            } else {
                ((Knight)o2).changeProtection(temp);
            }
        } else {
            o2.changeHp(-(o1.getIntDamage()));
        }
    }

    /**Method to determine if any of the characters are dead with parameters.
     * @param o object about which it is necessary to determine whether it is dead.
     * @return true if objects HP less than 1.
     */
    public boolean occurrenceOfDeath(CharacterModel o) {
        return o.getIntHp() <= 0;
    }

    /**Method to determine if player is dead with parameters.
     * @param knight object about which it is necessary to determine whether it is dead.
     * @return true if knights HP or knights thirst level less than 1.
     */
    public boolean occurrenceOfPlayersDeath(Knight knight) {
        return knight.getIntHp() <= 0 || knight.getIntThirstLvl() <= 0;
    }

    /**Method to collect an apple with parameters.
     * @param knight player who wants to pick up an apple.
     * @return true if possible to pick up an apple(inventory is not full).
     */
    public boolean collectAnApple(Knight knight) {
        if (knight.inventory.isFull()) return false;
        knight.inventory.apple.changeQuantity(+1);
        return true;
    }

    /**Method to collect a meat with parameters.
     * @param knight player who wants to pick up a meat.
     * @return true if possible to pick up a meat(inventory is not full).
     */
    public boolean collectAMeat(Knight knight) {
        if (knight.inventory.isFull()) return false;
        knight.inventory.meat.changeQuantity(+1);
        return true;
    }

    /**Method to collect a wheat with parameters.
     * @param knight player who wants to pick up a wheat.
     * @return true if possible to pick up a wheat(inventory is not full).
     */
    public boolean collectAWheat(Knight knight) {
        if (knight.inventory.isFull()) return false;
        knight.inventory.wheat.changeQuantity(+1);
        return true;
    }

    /**Method to collect a water with parameters.
     * @param knight player who wants to pick up a water.
     * @return true if possible to pick up a water(inventory is not full).
     */
    public boolean collectAWater(Knight knight) {
        if (knight.inventory.isFull()) return false;
        knight.inventory.water.changeQuantity(+1);
        return true;
    }

    /**Method to collect a wood with parameters.
     * @param knight player who wants to pick up a wood.
     * @return true if possible to pick up a wood(inventory is not full).
     */
    public boolean collectAWood(Knight knight) {
        if (knight.inventory.isFull()) return false;
        knight.inventory.wood.changeQuantity(Math.min(knight.getIntDamageToMaterials(), knight.inventory.freePlaces()));
        return true;
    }

    /**Method to collect an iron with parameters.
     * @param knight player who wants to pick up an iron.
     * @return true if possible to pick up an iron(inventory is not full).
     */
    public boolean collectAnIron(Knight knight) {
        if (knight.inventory.isFull()) return false;
        knight.inventory.iron.changeQuantity(Math.min(knight.getIntDamageToMaterials(), knight.inventory.freePlaces()));
        return true;
    }

    /**Method to collect a stone with parameters.
     * @param knight player who wants to pick up a stone.
     * @return true if possible to pick up a stone(inventory is not full).
     */
    public boolean collectAStone(Knight knight) {
        if (knight.inventory.isFull()) return false;
        knight.inventory.stone.changeQuantity(Math.min(knight.getIntDamageToMaterials(), knight.inventory.freePlaces()));
        return true;
    }

    /**Method to quench thirst with parameters.
     * @param knight player who wants to quench thirst.
     * @return true if possible to drink water(water quantity > 0 and knights thirst level is not max).
     */
    public boolean drinkWater(Knight knight) {
        if (knight.inventory.water.getQuantity() == 0 || knight.getIntThirstLvl() == 20) return false;
        knight.changeThirstLvl(+1);
        knight.inventory.water.changeQuantity(-1);
        return true;
    }

    /**Method to increase HP using an apple with parameters.
     * @param knight player who wants to increase HP.
     * @return true if possible to eat an apple(apple quantity > 0 and knights hp is not max).
     */
    public boolean eatApple(Knight knight) {
        if (knight.inventory.apple.getQuantity() == 0 || knight.getIntHp() == 10) return false;
        knight.changeHp(+1);
        knight.inventory.apple.changeQuantity(-1);
        return true;
    }

    /**Method to increase HP using a pie with parameters.
     * @param knight player who wants to increase HP.
     * @return true if possible to eat a pie(pie quantity > 0 and knights hp is not max).
     */
    public boolean eatPie(Knight knight) {
        if (knight.inventory.pie.getQuantity() == 0 || knight.getIntHp() == 10) return false;
        knight.changeHp(+3);
        knight.inventory.pie.changeQuantity(-1);
        return true;
    }

    /**Method to increase HP using a soup with parameters.
     * @param knight player who wants to increase HP.
     * @return true if possible to eat a soup(soup quantity > 0 and knights hp is not max).
     */
    public boolean eatSoup(Knight knight) {
        if (knight.inventory.soup.getQuantity() == 0 || knight.getIntHp() == 10) return false;
        knight.changeHp(+5);
        knight.inventory.pie.changeQuantity(-1);
        return true;
    }

    /**Method for crafting a pie.
     * @param knight who wants to craft a pie.
     * @return true if possible to craft a pie(water quantity, apple quantity, pie quantity >= 2 and inventory is not full).
     */
    public boolean craftAPie(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftAPie())) return false;
        knight.inventory.apple.changeQuantity(-2);
        knight.inventory.water.changeQuantity(-2);
        knight.inventory.wheat.changeQuantity(-2);
        knight.inventory.pie.changeQuantity(+1);
        return true;
    }

    /**Method for crafting a soup.
     * @param knight who wants to craft a soup.
     * @return true if possible to craft a soup(water quantity >= 3, meat quantity >= 1 and inventory is not full).
     */
    public boolean craftASoup(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftASoup())) return false;
        knight.inventory.water.changeQuantity(-3);
        knight.inventory.meat.changeQuantity(-1);
        knight.inventory.soup.changeQuantity(+1);
        return true;
    }

    /**Method for crafting a wooden axe.
     * @param knight who wants to craft a wooden axe.
     * @return true if possible to craft a wooden axe(wood quantity >= 2 and wooden axe is not already crafted).
     */
    public boolean craftAWoodenAxe(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftAWoodenAxe())) return false;
        knight.inventory.wood.changeQuantity(-2);
        knight.upgradeAxe(Material.WOOD);
        return true;
    }

    /**Method for crafting a wooden sword.
     * @param knight who wants to craft a wooden sword.
     * @return true if possible to craft a wooden sword(wood quantity >= 3 and wooden sword is not already crafted).
     */
    public boolean craftAWoodenSword(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftAWoodenSword())) return false;
        knight.inventory.wood.changeQuantity(-3);
        knight.upgradeSword(Material.WOOD);
        return true;
    }

    /**Method for crafting a wooden shield.
     * @param knight who wants to craft a wooden shield.
     * @return true if possible to craft a wooden shield(wood quantity >= 4 and wooden shield is not already crafted).
     */
    public boolean craftAWoodenShield(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftAWoodenShield())) return false;
        knight.inventory.wood.changeQuantity(-4);
        knight.upgradeShield(Material.WOOD);
        return true;
    }

    /**Method for crafting an iron axe.
     * @param knight who wants to craft an iron axe.
     * @return true if possible to craft an iron axe(wood quantity, iron quantity >= 1 and iron axe is not already crafted).
     */
    public boolean craftAnIronAxe(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftAnIronAxe())) return false;
        knight.inventory.wood.changeQuantity(-1);
        knight.inventory.iron.changeQuantity(-1);
        knight.upgradeAxe(Material.IRON);
        return true;
    }

    /**Method for crafting an iron sword.
     * @param knight who wants to craft an iron sword.
     * @return true if possible to craft an iron sword(wood quantity >= 1, iron quantity >= 2 and iron sword is not already crafted).
     */
    public boolean craftAnIronSword(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftAnIronSword())) return false;
        knight.inventory.wood.changeQuantity(-1);
        knight.inventory.iron.changeQuantity(-2);
        knight.upgradeSword(Material.IRON);
        return true;
    }

    /**Method for crafting an iron shield.
     * @param knight who wants to craft an iron shield.
     * @return true if possible to craft an iron shield(wood quantity >= 1, iron quantity >= 3 and iron shield is not already crafted).
     */
    public boolean craftAnIronShield(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftAnIronShield())) return false;
        knight.inventory.wood.changeQuantity(-1);
        knight.inventory.iron.changeQuantity(-3);
        knight.upgradeShield(Material.IRON);
        return true;
    }

    /**Method for crafting a stone axe.
     * @param knight who wants to craft a stone axe.
     * @return true if possible to craft a stone axe(wood quantity, stone quantity >= 1 and stone axe is not already crafted).
     */
    public boolean craftAStoneAxe(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftAStoneAxe())) return false;
        knight.inventory.wood.changeQuantity(-1);
        knight.inventory.stone.changeQuantity(-1);
        knight.upgradeAxe(Material.STONE);
        return true;
    }

    /**Method for crafting a stone sword.
     * @param knight who wants to craft a stone sword.
     * @return true if possible to craft a stone sword(wood quantity >= 1, stone quantity >= 2 and stone sword is not already crafted).
     */
    public boolean craftAStoneSword(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftAStoneSword())) return false;
        knight.inventory.wood.changeQuantity(-1);
        knight.inventory.stone.changeQuantity(-2);
        knight.upgradeSword(Material.STONE);
        return true;
    }

    /**Method for crafting a stone shield.
     * @param knight who wants to craft a stone shield.
     * @return true if possible to craft a stone shield(wood quantity >= 1, stone quantity >= 3 and stone shield is not already crafted).
     */
    public boolean craftAStoneShield(Knight knight) {
        if (!(knight.inventory.isPossibleToCraftAStoneShield())) return false;
        knight.inventory.wood.changeQuantity(-1);
        knight.inventory.stone.changeQuantity(-3);
        knight.upgradeShield(Material.STONE);
        return true;
    }
}

