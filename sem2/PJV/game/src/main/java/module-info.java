module cz.cvut.fel.pjv {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.logging;

    opens cz.cvut.fel.pjv to javafx.fxml;
    exports cz.cvut.fel.pjv;
    exports cz.cvut.fel.pjv.model;
    exports cz.cvut.fel.pjv.model.characters;
    exports cz.cvut.fel.pjv.model.items;
    exports cz.cvut.fel.pjv.model.items.food;
    exports cz.cvut.fel.pjv.model.items.food.dishes;
    exports cz.cvut.fel.pjv.model.items.materials;
    exports cz.cvut.fel.pjv.view;
    opens cz.cvut.fel.pjv.view to javafx.fxml;
}