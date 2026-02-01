# Database Schema Design

## Tables

### Product
- id (Primary Key)
- name
- price
- category

### Stock
- product_id (Foreign Key)
- quantity
- threshold

### Transaction
- id
- product_id
- type (BUY / SELL)
- quantity
- timestamp

### User
- id
- username
- role (ADMIN / STAFF)

## Notes
- SQLite is used for lightweight persistent storage
- Foreign keys maintain data consistency
