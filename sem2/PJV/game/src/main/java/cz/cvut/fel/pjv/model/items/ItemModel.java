package cz.cvut.fel.pjv.model.items;

/**Template class for all items.*/
public class ItemModel {

    /**quantity in int type.*/
    private int quantity;

    /**Constructor with parameters
     * @param quantity initial value for quantity.
     */
    public ItemModel(int quantity) {
        this.quantity = quantity;
    }

    public int getQuantity() {
        return quantity;
    }

    /**Method for changing quantity with parameters.
     * @param num the number to change quantity.
     */
    public void changeQuantity(int num) {
        quantity += num;
    }
}
