import styles from './StoreMap.module.css';

export const StoreMap = ({ nodes, edges, optimalPath }) => {
  const minX = Math.min(...nodes.map(n => n.x));
  const maxX = Math.max(...nodes.map(n => n.x));
  const minY = Math.min(...nodes.map(n => n.y));
  const maxY = Math.max(...nodes.map(n => n.y));

  const padding = 40;
  const viewBoxWidth = 400;
  const viewBoxHeight = 400;

  const scaleX = (x) => padding + ((x - minX) / (maxX - minX || 1)) * (viewBoxWidth - 2 * padding);
  const scaleY = (y) => viewBoxHeight - (padding + ((y - minY) / (maxY - minY || 1)) * (viewBoxHeight - 2 * padding));

  const getNodeCoords = (id) => {
    const node = nodes.find(n => n.id === id);
    if (!node) return { x: 0, y: 0 };
    return { x: scaleX(node.x), y: scaleY(node.y) };
  };

  let pathD = '';
  if (optimalPath && optimalPath.length > 0) {
    optimalPath.forEach((nodeId, index) => {
      const { x, y } = getNodeCoords(nodeId);
      if (index === 0) {
        pathD += `M ${x} ${y} `;
      } else {
        pathD += `L ${x} ${y} `;
      }
    });
  }

  return (
    <div className={styles.container}>
      <svg className={styles.svg} viewBox={`0 0 ${viewBoxWidth} ${viewBoxHeight}`}>
        {edges.map((edge, i) => {
          const n1 = getNodeCoords(edge.node1_id);
          const n2 = getNodeCoords(edge.node2_id);
          return (
            <line
              key={i}
              x1={n1.x}
              y1={n1.y}
              x2={n2.x}
              y2={n2.y}
              className={styles.edge}
            />
          );
        })}

        {pathD && (
          <path d={pathD} className={styles.path} />
        )}

        {nodes.map(node => {
          const { x, y } = getNodeCoords(node.id);
          return (
            <g key={node.id}>
              <circle cx={x} cy={y} r="14" className={styles.node} />
              <text x={x} y={y} className={styles.nodeText}>
                {node.id}
              </text>
            </g>
          );
        })}
      </svg>
    </div>
  );
};
