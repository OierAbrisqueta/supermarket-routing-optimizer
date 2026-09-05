import styles from './ItemSelector.module.css';

export const ItemSelector = ({ items, selectedIds, onChange }) => {
  const toggleItem = (id) => {
    if (selectedIds.includes(id)) {
      onChange(selectedIds.filter(itemId => itemId !== id));
    } else {
      onChange([...selectedIds, id]);
    }
  };

  return (
    <div className={styles.list}>
      {items.map(item => (
        <label key={item.id} className={styles.item}>
          <input
            type="checkbox"
            checked={selectedIds.includes(item.id)}
            onChange={() => toggleItem(item.id)}
          />
          <span className={styles.label}>{item.name}</span>
          <span className={styles.nodeId}>Area {item.node_id}</span>
        </label>
      ))}
    </div>
  );
};
