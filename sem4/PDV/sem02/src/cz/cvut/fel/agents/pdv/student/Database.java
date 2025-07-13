package cz.cvut.fel.agents.pdv.student;

import java.util.HashMap;

public class Database {
    public HashMap<String, String> DB;
    public Database() {
        DB = new HashMap<>();
    }

    public void put(String key, String value) {
        DB.put(key, value);
    }

    public void append(String key, String value) {
        String old = DB.get(key);
        String newValue = old == null ? value : old + value;

        DB.put(key, newValue);
    }

    public String get(String key) {
        return DB.get(key);
    }
}
