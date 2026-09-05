import styles from './Card.module.css';

export const Card = ({ title, children, className = '' }) => {
  return (
    <div className={`${styles.card} ${className}`.trim()}>
      {title && <div className={styles.header}>{title}</div>}
      <div className={styles.content}>
        {children}
      </div>
    </div>
  );
};
