package cz.cvut.fel.pjv.model.items.weapons;

/**Class extends from CharacterModel class.*/
public class Axe extends WeaponModel {

    /**Damage to material in int type.*/
    private int damageToMaterials;

    /**Constructor with parameters.
     * @param material initial value for material and change damageToMaterials depending on material.
     */
    public Axe(Material material) {
        super(material);
        switch (getMaterial()) {
            case NOTHING:
                damageToMaterials = 0;
            case WOOD:
                damageToMaterials = 1;
                break;
            case IRON:
                damageToMaterials = 5;
                break;
            case STONE:
                damageToMaterials = 10;
                break;
        }
    }

    public int getDamageToMaterials() { return damageToMaterials; }

    /**Method for changing material with parameters.
     * @param newMaterial for change material and initial damageToMaterials depending on newMaterial.
     */
    public void upgradeAxe(Material newMaterial) {
        changeMaterial(newMaterial);
        switch (getMaterial()) {
            case NOTHING:
                damageToMaterials = 0;
            case WOOD:
                damageToMaterials = 1;
                break;
            case IRON:
                damageToMaterials = 5;
                break;
            case STONE:
                damageToMaterials = 10;
                break;
        }
    }
}

