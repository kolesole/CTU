package cz.cvut.fel.pjv.model.characters;

/**Template class for all characters.*/
public class CharacterModel {

    /**HP in String type.*/
    private String strHp;
    /**HP in int type.*/
    private int intHp;
    /**Damage in String type.*/
    private String strDamage;
    /**Damage in int type.*/
    private int intDamage;

    /**Constructor with parameters.
     * @param intHp initial value for intHp.
     * @param intDamage initial value for intDamage.
     */
    public CharacterModel(int intHp, int intDamage) {
        this.intHp = intHp;
        this.strHp = "_".repeat(intHp);
        this.intDamage = intDamage;
        this.strDamage = "-".repeat(intDamage);
    }

    public String getStrHp() {
        return strHp;
    }

    public int getIntHp() {
        return intHp;
    }

    public String getStrDamage() {
        return strDamage;
    }

    public int getIntDamage() {
        return intDamage;
    }

    /**method for changing HP with parameters.
     * @param num the number to change intHp.
     */
    public void changeHp(int num) {
        intHp = Math.max((intHp + num), 0);
        strHp = "_".repeat(intHp);
    }

    /**method for changing damage with parameters.
     * @param damage the number to change intDamage.
     */
    public void changeDamage(int damage) {
        intDamage = damage;
        strDamage = "-".repeat(intDamage);
    }
}
