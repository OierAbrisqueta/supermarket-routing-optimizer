DELETE FROM Inventory;
DELETE FROM Edge;
DELETE FROM Area;
DELETE FROM Product;
DELETE FROM Store;

INSERT INTO Store (id, name) VALUES (1, 'Test Supermarket');

INSERT INTO Product (id, name) VALUES
                                   (1, 'Apples'),
                                   (2, 'Bananas'),
                                   (3, 'Bread'),
                                   (4, 'Croissants'),
                                   (5, 'Chicken'),
                                   (6, 'Beef'),
                                   (7, 'Pasta'),
                                   (8, 'Rice'),
                                   (9, 'Chips'),
                                   (10, 'Cola'),
                                   (11, 'Pizza'),
                                   (12, 'Ice Cream'),
                                   (13, 'Milk'),
                                   (14, 'Cheese');

-- Front Row (Y = 0)
INSERT INTO Area (id, store_id, x, y) VALUES (1, 1, 0.0, 0.0);   -- Entrance
INSERT INTO Area (id, store_id, x, y) VALUES (2, 1, 4.0, 0.0);   -- Checkout A
INSERT INTO Area (id, store_id, x, y) VALUES (3, 1, 8.0, 0.0);   -- Checkout B
INSERT INTO Area (id, store_id, x, y) VALUES (4, 1, 12.0, 0.0);  -- Exit

-- Middle Row (Y = 4)
INSERT INTO Area (id, store_id, x, y) VALUES (5, 1, 0.0, 4.0);   -- Fruits
INSERT INTO Area (id, store_id, x, y) VALUES (6, 1, 4.0, 4.0);   -- Dry Goods
INSERT INTO Area (id, store_id, x, y) VALUES (7, 1, 8.0, 4.0);   -- Snacks and Beverages
INSERT INTO Area (id, store_id, x, y) VALUES (8, 1, 12.0, 4.0);  -- Frozen Foods

-- Back Row (Y = 8)
INSERT INTO Area (id, store_id, x, y) VALUES (9, 1, 0.0, 8.0);   -- Bakery
INSERT INTO Area (id, store_id, x, y) VALUES (10, 1, 4.0, 8.0);  -- Meat
INSERT INTO Area (id, store_id, x, y) VALUES (11, 1, 8.0, 8.0);  -- Seafood
INSERT INTO Area (id, store_id, x, y) VALUES (12, 1, 12.0, 8.0); -- Dairy

-- Horizontal Front
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 1, 2, 4.0);
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 2, 3, 4.0);
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 3, 4, 4.0);

-- Horizontal Middle
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 5, 6, 4.0);
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 6, 7, 4.0);
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 7, 8, 4.0);

-- Horizontal Back
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 9, 10, 4.0);
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 10, 11, 4.0);
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 11, 12, 4.0);

-- Vertical Aisles
-- Aisle 1
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 1, 5, 4.0);
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 5, 9, 4.0);

-- Aisle 2
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 2, 6, 4.0);
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 6, 10, 4.0);

-- Aisle 3
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 3, 7, 4.0);
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 7, 11, 4.0);

-- Aisle 4
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 4, 8, 4.0);
INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES (1, 8, 12, 4.0);

INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 1, 5); -- Apples
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 2, 5); -- Bananas
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 3, 9); -- Bread
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 4, 9); -- Croissants
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 5, 10); -- Chicken
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 6, 10); -- Beef
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 7, 6); -- Pasta
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 8, 6); -- Rice
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 9, 7); -- Chips
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 10, 7); -- Cola
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 11, 8); -- Pizza
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 12, 8); -- Ice Cream
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 13, 12); -- Milk
INSERT INTO Inventory (store_id, product_id, node_id) VALUES (1, 14, 12); -- Cheese