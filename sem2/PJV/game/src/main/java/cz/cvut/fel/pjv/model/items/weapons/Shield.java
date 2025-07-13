package cz.cvut.fel.pjv.model.items.weapons;

/**Class extends from CharacterModel class.*/
public class Shield extends WeaponModel {

    /**Protection in int type.*/
    private int protection;

    /**Constructor with parameters.
     * @param material initial value for material and initial protection depending on material.
     */
    public Shield(Material material) {
        super(material);
        switch (getMaterial()) {
            case NOTHING:
                protection = 0;
            case WOOD:
                protection = 1;
                break;
            case IRON:
                protection = 3;
                break;
            case STONE:
                protection = 5;
                break;
        }
    }

    public int getProtection() { return protection; }

    /**Method for changing material with parameters.
     * @param newMaterial for change material and change protection depending on newMaterial.
     */
    public void upgradeShield(Material newMaterial) {
        changeMaterial(newMaterial);
        switch (getMaterial()) {
            case NOTHING:
                protection = 0;
            case WOOD:
                protection = 1;
                break;
            case IRON:
                protection = 3;
                break;
            case STONE:
                protection = 5;
                break;
        }
    }
}

