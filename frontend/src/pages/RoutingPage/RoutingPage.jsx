import { useState } from 'react';
import styles from './RoutingPage.module.css';
import { Card } from '../../components/Card/Card';
import { Button } from '../../components/Button/Button';
import { ItemSelector } from '../../components/ItemSelector/ItemSelector';
import { StoreMap } from '../../components/StoreMap/StoreMap';

const STORE_NODES = [
  { id: 1, x: 0.0, y: 0.0 },
  { id: 2, x: 0.0, y: 5.0 },
  { id: 3, x: 5.0, y: 5.0 },
  { id: 4, x: 5.0, y: 0.0 },
  { id: 5, x: 2.0, y: 2.0 }
];

const STORE_EDGES = [
  { node1_id: 1, node2_id: 2 },
  { node1_id: 2, node2_id: 3 },
  { node1_id: 3, node2_id: 4 },
  { node1_id: 4, node2_id: 5 },
  { node1_id: 1, node2_id: 4 }
];

const MOCK_PRODUCTS = [
  { id: 101, name: 'Milk', node_id: 2 },
  { id: 102, name: 'Eggs', node_id: 3 },
  { id: 103, name: 'Bread', node_id: 4 },
  { id: 104, name: 'Apples', node_id: 5 },
  { id: 105, name: 'Cereal', node_id: 2 },
];

export const RoutingPage = () => {
  const [selectedProductIds, setSelectedProductIds] = useState([]);
  const [optimalPath, setOptimalPath] = useState([]);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState(null);

  const handleCalculateRoute = async () => {
    if (selectedProductIds.length === 0) {
      setError('Please select at least one item.');
      return;
    }
    
    setLoading(true);
    setError(null);
    setOptimalPath([]);

    try {
      const response = await fetch('/api/route', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          store_id: 1,
          start_node_id: 1,
          end_node_id: 1,
          product_ids: selectedProductIds,
        }),
      });

      const data = await response.json();

      if (!response.ok || data.status === 'error') {
        throw new Error(data.message || 'Failed to calculate route.');
      }

      setOptimalPath(data.optimal_path);
    } catch (err) {
      setError(err.message);
      console.warn("Backend not reachable. Mocking the route.");
      const path = [1, ...new Set(MOCK_PRODUCTS.filter(p => selectedProductIds.includes(p.id)).map(p => p.node_id)), 1];
      setOptimalPath(path);
    } finally {
      setLoading(false);
    }
  };

  const handleReset = () => {
    setSelectedProductIds([]);
    setOptimalPath([]);
    setError(null);
  };

  return (
    <div className="container">
      <header className={styles.header}>
        <h1 className={styles.title}>Store Routing Optimizer</h1>
        <p className={styles.subtitle}>Select items to generate the most efficient picking route.</p>
      </header>

      <div className={styles.layout}>
        <aside className={styles.sidebar}>
          <Card title="Shopping List">
            <ItemSelector
              items={MOCK_PRODUCTS}
              selectedIds={selectedProductIds}
              onChange={setSelectedProductIds}
            />
            
            {error && <div className={styles.error}>{error}</div>}

            <div className={styles.actions}>
              <Button 
                onClick={handleCalculateRoute} 
                disabled={loading || selectedProductIds.length === 0}
              >
                {loading ? 'Calculating...' : 'Generate Route'}
              </Button>
              <Button 
                variant="secondary" 
                onClick={handleReset}
                disabled={loading || (selectedProductIds.length === 0 && optimalPath.length === 0)}
              >
                Reset
              </Button>
            </div>
          </Card>
          
          {optimalPath.length > 0 && (
            <Card title="Route Sequence">
              <ol style={{ paddingLeft: '1.5rem', margin: 0, fontSize: '0.875rem' }}>
                {optimalPath.map((nodeId, idx) => (
                  <li key={`${nodeId}-${idx}`} style={{ marginBottom: '0.25rem' }}>
                    Node {nodeId}
                    {idx === 0 ? ' (Start)' : idx === optimalPath.length - 1 ? ' (End)' : ''}
                  </li>
                ))}
              </ol>
            </Card>
          )}
        </aside>

        <section className={styles.mapSection}>
          <Card title="Store Layout">
            <StoreMap 
              nodes={STORE_NODES} 
              edges={STORE_EDGES} 
              optimalPath={optimalPath} 
            />
          </Card>
        </section>
      </div>
    </div>
  );
};
