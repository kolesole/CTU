package cz.cvut.fel.pjv.model.items.weapons;

/**Template class for all weapons.*/
public class WeaponModel {

    /**material in Material type.*/
    private Material material;

    /**Constructor with parameters.
     * @param material initial value for material.
     */
    public WeaponModel(Material material) {
        this.material = material;
    }

    public Material getMaterial() { return material; }

    /**Method for changing weapon material.
     * @param newMaterial designed to easily change weapons states.
     */
    public void changeMaterial(Material newMaterial) { material = newMaterial; }
}
