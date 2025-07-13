package cz.cvut.fel.pjv.model.characters;

import cz.cvut.fel.pjv.model.items.Inventory;
import cz.cvut.fel.pjv.model.items.weapons.Axe;
import cz.cvut.fel.pjv.model.items.weapons.Material;
import cz.cvut.fel.pjv.model.items.weapons.Shield;
import cz.cvut.fel.pjv.model.items.weapons.Sword;

/**Class that is created directly for the player
 * extends from CharacterModel class.*/
public class Knight extends CharacterModel {

    /**Thirst level in String type.*/
    private String strThirstLvl;
    
    /**Thirst level in int type.*/
    private int intThirstLvl;

    /**Damage to material in String type.*/
    private String strDamageToMaterials;

    /**Damage to material in int type.*/
    private int intDamageToMaterials;

    /**Protection in String type.*/
    private String strProtection;

    /**Protection in int type.*/
    private int intProtection;

    /**axe in Axe type.*/
    private Axe axe;

    /**sword in Sword type.*/
    private Sword sword;

    /**shield in Shield type.*/
    private Shield shield;

    /**inventory in inventory type.*/
    public Inventory inventory;

    /**Constructor with parameters
     * @param intHp initial value for intHp.
     * @param intThirstLvl initial value for intThirstLvl.
     */
    public Knight(int intHp, int intThirstLvl) {
        super(intHp, 0);
        sword = new Sword(Material.NOTHING);
        shield = new Shield(Material.NOTHING);
        axe = new Axe(Material.WOOD);
        this.intThirstLvl = intThirstLvl;
        this.strThirstLvl = ".".repeat(intThirstLvl);
        this.intDamageToMaterials = 1;
        this.strDamageToMaterials = "*".repeat(intDamageToMaterials);
        this.intProtection = 0;
        this.strProtection = "|".repeat(intProtection);
        inventory = new Inventory();
    }

    public String getStrThirstLvl() {
        return strThirstLvl;
    }

    public int getIntThirstLvl() {
        return intThirstLvl;
    }

    public String getStrDamageToMaterials() {
        return strDamageToMaterials;
    }

    public int getIntDamageToMaterials() {
        return intDamageToMaterials;
    }

    public String getStrProtection() {
        return strProtection;
    }

    public int getIntProtection() {
        return intProtection;
    }

    /**Method for changing thirst level with parameters.
     * @param num the number to change intThirstLvl.
     */
    public void changeThirstLvl(int num) {
        intThirstLvl += num;
        strThirstLvl = ".".repeat(intThirstLvl);
    }

    /**Method for changing damage to materials with parameters.
     * @param damageToMaterials the number to change intDamageToMaterials.
     */
    private void changeDamageToMaterials(int damageToMaterials) {
        intDamageToMaterials = damageToMaterials;
        strDamageToMaterials = "*".repeat(intDamageToMaterials);
    }

    /**Method for changing protection with parameters.
     * @param protection the number to change intProtection.
     */
    public void changeProtection(int protection) {
        intProtection = protection;
        strProtection = "|".repeat(intProtection);
    }

    /**Method that calls the same method from a class Axe + changes the damage to materials with parameters.
     * @param material designed to easily change weapons states.
     */
    public void upgradeAxe(Material material) {
        axe.upgradeAxe(material);
        changeDamageToMaterials(axe.getDamageToMaterials());
    }

    /**Method that calls the same method from a class Sword + changes the damage to characters with parameters.
     * @param material designed to easily change weapons states.
     */
    public void upgradeSword(Material material) {
        sword.upgradeSword(material);
        changeDamage(sword.getDamageToCharacters());
    }

    /**Method that calls the same method from a class Shield + changes the protection with parameters.
     * @param material designed to easily change weapons states.
     */
    public void upgradeShield(Material material) {
        shield.upgradeShield(material);
        changeProtection(shield.getProtection());
    }
}
