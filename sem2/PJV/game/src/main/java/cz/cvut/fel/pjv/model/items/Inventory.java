package cz.cvut.fel.pjv.model.items;

import cz.cvut.fel.pjv.model.items.food.Apple;
import cz.cvut.fel.pjv.model.items.food.Meat;
import cz.cvut.fel.pjv.model.items.food.Water;
import cz.cvut.fel.pjv.model.items.food.Wheat;
import cz.cvut.fel.pjv.model.items.food.dishes.Pie;
import cz.cvut.fel.pjv.model.items.food.dishes.Soup;
import cz.cvut.fel.pjv.model.items.materials.Iron;
import cz.cvut.fel.pjv.model.items.materials.Stone;
import cz.cvut.fel.pjv.model.items.materials.Wood;

/**Class that remembers all selected or crafted materials and objects.*/
public class Inventory {

    /**water in Water type.*/
    public Water water;

    /**iron in Iron type.*/
    public Iron iron;

    /**wheat in wheat type.*/
    public Wheat wheat;

    /**wood in wood type.*/
    public Wood wood;

    /**meat in meat type.*/
    public Meat meat;

    /**apple in apple type.*/
    public Apple apple;

    /**stone in Stone type.*/
    public Stone stone;

    /**pie in Pie type.*/
    public Pie pie;

    /**soup in Soup type.*/
    public Soup soup;

    /**Capacity in int type.*/
    public int capacity;

    /**Constructor with parameters.
     * @param quantityOfWater for initial water.
     * @param quantityOfIron for initial iron.
     * @param quantityOfWheat for initial wheat.
     * @param quantityOfWood for initial wood.
     * @param quantityOfMeat for initial meat.
     * @param quantityOfApple for initial apple.
     * @param quantityOfStone for initial stone.
     * @param capacity for initial capacity.
     */
    public Inventory(int quantityOfWater, int quantityOfIron, int quantityOfWheat, int quantityOfWood,
                     int quantityOfMeat, int quantityOfApple, int quantityOfStone, int capacity) {
        this.water = new Water(quantityOfWater);
        this.iron = new Iron(quantityOfIron);
        this.wheat = new Wheat(quantityOfWheat);
        this.wood = new Wood(quantityOfWood);
        this.meat = new Meat(quantityOfMeat);
        this.apple = new Apple(quantityOfApple);
        this.stone = new Stone(quantityOfStone);
        pie = new Pie(0);
        soup = new Soup(0);
        this.capacity = capacity;
    }

    /**Default constructor without parameters.*/
    public Inventory() {
        this.water = new Water(0);
        this.iron = new Iron(0);
        this.wheat = new Wheat(0);
        this.wood = new Wood(0);
        this.meat = new Meat(0);
        this.apple = new Apple(0);
        this.stone = new Stone(0);
        pie = new Pie(0);
        soup = new Soup(0);
        this.capacity = 15;
    }

    public int getCapacity() {
        return capacity;
    }

    /**Method without parameters.
     * @return the number of all items in inventory*/
    public int quantityOfItems() {
        return water.getQuantity() + iron.getQuantity() + wheat.getQuantity() + wood.getQuantity() + meat.getQuantity()
                + apple.getQuantity() + stone.getQuantity() + pie.getQuantity() + soup.getQuantity();
    }

    /**Method without parameters.
     * @return true if inventory is full.*/
    public boolean isFull() {
        return quantityOfItems() == capacity;
    }

    /**Method without parameters.
     * @return true if inventory is empty.*/
    public boolean isEmpty() {
        return quantityOfItems() == 0;
    }

    /**Method without parameters.
     * @return the number of free places in inventory.*/
    public int freePlaces() { return capacity - quantityOfItems(); }

    /**Method without parameters.
     * @return true if player can craft a pie.*/
    public boolean isPossibleToCraftAPie() { return apple.getQuantity() >= 2 && water.getQuantity() >= 2 && wheat.getQuantity() >= 2; }

    /**Method without parameters.
     * @return true if player can craft a soup.*/
    public boolean isPossibleToCraftASoup() { return water.getQuantity() >= 3 && meat.getQuantity() >= 1; }

    /**Method without parameters.
     * @return true if player can craft a wooden axe.*/
    public boolean isPossibleToCraftAWoodenAxe() { return wood.getQuantity() >= 2; }

    /**Method without parameters.
     * @return true if player can craft a wooden sword.*/
    public boolean isPossibleToCraftAWoodenSword() { return wood.getQuantity() >= 3; }

    /**Method without parameters.
     * @return true if player can craft a wooden shield.*/
    public boolean isPossibleToCraftAWoodenShield() { return wood.getQuantity() >= 4; }

    /**Method without parameters.
     * @return true if player can craft an iron axe.*/
    public boolean isPossibleToCraftAnIronAxe() { return iron.getQuantity() >= 1 && wood.getQuantity() >= 1; }

    /**Method without parameters.
     * @return true if player can craft an iron sword.*/
    public boolean isPossibleToCraftAnIronSword() { return iron.getQuantity() >= 2 && wood.getQuantity() >= 1; }

    /**Method without parameters.
     * @return true if player can craft an iron shield.*/
    public boolean isPossibleToCraftAnIronShield() { return iron.getQuantity() >= 3 && wood.getQuantity() >= 1; }

    /**Method without parameters.
     * @return true if player can craft a stone axe.*/
    public boolean isPossibleToCraftAStoneAxe() { return stone.getQuantity() >= 1 && wood.getQuantity() >= 1; }

    /**Method without parameters.
     * @return true if player can craft a stone sword.*/
    public boolean isPossibleToCraftAStoneSword() { return stone.getQuantity() >= 2 && wood.getQuantity() >= 1; }

    /**Method without parameters.
     * @return true if player can craft a stone shield.*/
    public boolean isPossibleToCraftAStoneShield() { return stone.getQuantity() >= 3 && wood.getQuantity() >= 1; }

    /**Method without parameters.
     * @return String with items that player can craft*/
    public String isPossibleToCraft() {
        String possibleToCraft = "";
        String emptyStr = "";
        if (isPossibleToCraftAPie()) possibleToCraft += "You can make a pie.\n";
        if (isPossibleToCraftASoup()) possibleToCraft += "You can make a soup.\n";
        if (isPossibleToCraftAWoodenAxe()) possibleToCraft += "You can create a wooden axe.\n";
        if (isPossibleToCraftAWoodenSword()) possibleToCraft += "You can craft a wooden sword.\n";
        if (isPossibleToCraftAWoodenShield()) possibleToCraft += "You can craft a wooden shield.\n";
        if (isPossibleToCraftAnIronAxe()) possibleToCraft += "You can craft an iron axe.\n";
        if (isPossibleToCraftAnIronSword()) possibleToCraft += "You can craft an iron sword.\n";
        if (isPossibleToCraftAnIronShield()) possibleToCraft += "You can craft an iron shield.\n";
        if (isPossibleToCraftAStoneAxe()) possibleToCraft += "You can craft a stone axe.\n";
        if (isPossibleToCraftAStoneSword()) possibleToCraft += "You can craft a stone sword.\n";
        if (isPossibleToCraftAStoneShield()) possibleToCraft += "You can craft a stone shield.\n";
        if (possibleToCraft.equals(emptyStr)) possibleToCraft += "Nothing can be crafted.\nCollect more resources.";
        return possibleToCraft;
    }
}

