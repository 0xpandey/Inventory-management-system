# System Architecture

## Architecture Overview
This project follows a layered architecture pattern to ensure separation of concerns, scalability, and maintainability.

## Layers
1. Presentation Layer (Console UI)
2. Service Layer (Business Logic)
3. Repository Layer (Data Access)
4. Database Layer (SQLite)

## Why This Architecture?
- Makes the system easier to extend
- Allows independent testing of logic
- Mirrors real-world software design practices

## High-Level Flow
User Input → UI Layer → Service Layer → Repository → SQLite Database
