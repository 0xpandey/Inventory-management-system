# 📦 Database Schema

The **Inventory Management System** uses an **SQLite** database with three core tables to manage products, stock levels, and inventory transactions.

---

## 🗂 Tables Overview

### 🛒 `products`

Stores basic product details.

| Column       | Type     | Constraints / Description |
|--------------|----------|---------------------------|
| `id`         | INTEGER  | Primary Key, Auto Increment |
| `name`       | TEXT     | NOT NULL |
| `category`   | TEXT     | Optional |
| `price`      | REAL     | NOT NULL |
| `created_at` | TEXT     | Default: `CURRENT_TIMESTAMP` |
| `is_active`  | INTEGER  | Default: `1` |

---

### 📦 `stock`

Tracks available quantity for each product.

| Column        | Type     | Constraints / Description |
|---------------|----------|---------------------------|
| `product_id`  | INTEGER  | Primary Key, Foreign Key → `products.id` |
| `quantity`    | INTEGER  | NOT NULL, ≥ 0 |
| `threshold`   | INTEGER  | Default: `5` |
| `updated_at`  | TEXT     | Default: `CURRENT_TIMESTAMP` |

---

### 🔁 `inventory_transactions`

Records all buy and sell operations.

| Column        | Type     | Constraints / Description |
|---------------|----------|---------------------------|
| `id`          | INTEGER  | Primary Key, Auto Increment |
| `product_id`  | INTEGER  | Foreign Key → `products.id` |
| `type`        | TEXT     | `BUY` or `SELL` |
| `quantity`    | INTEGER  | NOT NULL |
| `unit_price`  | REAL     | NOT NULL |
| `timestamp`   | TEXT     | Default: `CURRENT_TIMESTAMP` |

---

## 🔗 Relationships

- **One Product → One Stock record**
- **One Product → Many Inventory Transactions**

This structure ensures accurate tracking of inventory levels and complete transaction history.
