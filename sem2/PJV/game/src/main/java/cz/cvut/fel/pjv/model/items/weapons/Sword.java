package cz.cvut.fel.pjv.model.items.weapons;

/**Class extends from CharacterModel class.*/
public class Sword extends WeaponModel {

    /**Damage to characters in int type.*/
    private int damageToCharacters;

    /**Constructor with parameters.
     * @param material initial value for material and initial damageToCharacters depending on material.
     */
    public Sword(Material material) {
        super(material);
        switch (getMaterial()) {
            case NOTHING:
                damageToCharacters = 0;
            case WOOD:
                damageToCharacters = 2;
                break;
            case IRON:
                damageToCharacters = 6;
                break;
            case STONE:
                damageToCharacters = 10;
                break;
        }
    }

    public int getDamageToCharacters() { return damageToCharacters; }

    /**Method for changing material with parameters.
     * @param newMaterial for change material and change damageToCharacters depending on newMaterial.
     */
    public void upgradeSword(Material newMaterial) {
        changeMaterial(newMaterial);
        switch (getMaterial()) {
            case NOTHING:
                damageToCharacters = 0;
            case WOOD:
                damageToCharacters = 2;
                break;
            case IRON:
                damageToCharacters = 6;
                break;
            case STONE:
                damageToCharacters = 10;
                break;
        }
    }
}

