INSERT INTO Store (id, name) VALUES (1, 'SuperMart');

INSERT INTO Product (id, name) VALUES (1, 'Milk');
INSERT INTO Product (id, name) VALUES (2, 'Bread');
INSERT INTO Product (id, name) VALUES (3, 'Apples');

INSERT INTO Area (id, store_id, x, y) VALUES
                                          (1, 1, 0.0, 0.0),
                                          (2, 1, 0.0, 5.0),
                                          (3, 1, 5.0, 5.0),
                                          (4, 1, 5.0, 0.0),
                                          (5, 1, 2.0, 2.0);


INSERT INTO Edge (store_id, node1_id, node2_id, weight) VALUES
                                                            (1, 1, 2, 5.0),
                                                            (1, 2, 3, 5.0),
                                                            (1, 3, 4, 5.0),
                                                            (1, 4, 5, 5.0),
                                                            (1, 1, 4, 5.0);


INSERT INTO Inventory (store_id, product_id, node_id) VALUES
                                                          (1, 1, 3),
                                                          (1, 2, 2),
                                                          (1, 3, 5);