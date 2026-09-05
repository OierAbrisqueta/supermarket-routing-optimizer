import { useState } from 'react'

function App() {
  const [routeResult, setRouteResult] = useState(null)
  const [error, setError] = useState(null)

  const calculateRoute = async () => {
    setRouteResult(null)
    setError(null)

    const payload = {
      store_id: 1,
      start_node_id: 1,
      end_node_id: 5,
      product_ids: [101, 102, 103]
    }

    try {
      const response = await fetch('/api/route', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(payload)
      })

      const data = await response.json()

      if (!response.ok || data.status === 'error') {
        throw new Error(data.message || 'Server error')
      }

      setRouteResult(data.optimal_path)
    } catch (err) {
      setError(err.message)
    }
  }

  return (
      <div style={{ padding: '2rem', fontFamily: 'system-ui' }}>
        <h1>Spatial Routing Optimizer</h1>
        <button
            onClick={calculateRoute}
            style={{ padding: '0.5rem 1rem', cursor: 'pointer' }}
        >
          Calculate Optimal Path
        </button>

        {error && <p style={{ color: 'red' }}>Error: {error}</p>}

        {routeResult && (
            <div style={{ marginTop: '1rem', padding: '1rem', background: '#f5f5f5', borderRadius: '8px' }}>
              <h2>Optimal Path (A* / TSP):</h2>
              <p style={{ fontSize: '1.2rem', fontWeight: 'bold' }}>
                {routeResult.join(' → ')}
              </p>
            </div>
        )}
      </div>
  )
}

export default App