PRAGMA foreign_keys = ON;

-- Store Table
CREATE TABLE IF NOT EXISTS Stores (id INTEGER PRIMARY KEY, name TEXT NOT NULL);

-- Product table
CREATE TABLE IF NOT EXISTS Product (id INTEGER PRIMARY KEY, name TEXT NOT NULL);

-- Node/Area table
CREATE TABLE IF NOT EXISTS Area (id INTEGER PRIMARY KEY, store_id INTEGER,
                                        x REAL, y REAL, FOREIGN KEY(store_id) REFERENCES Stores(id));

-- Edge table
CREATE TABLE IF NOT EXISTS Edge (id INTEGER PRIMARY KEY, store_id INTEGER,
                                        node1_id INTEGER, node2_id INTEGER, weight REAL,
                                        FOREIGN KEY(store_id) REFERENCES Stores(id), FOREIGN KEY(node1_id) REFERENCES Area(id),
                                        FOREIGN KEY(node2_id) REFERENCES Area(id));

-- Inventory table
CREATE TABLE IF NOT EXISTS Inventory (store_id INTEGER, product_id INTEGER, node_id INTEGER,
                                      PRIMARY KEY (store_id, product_id), FOREIGN KEY(store_id) REFERENCES Stores(id),
                                      FOREIGN KEY(product_id) REFERENCES Product(id), FOREIGN KEY(node_id) REFERENCES Area(id));