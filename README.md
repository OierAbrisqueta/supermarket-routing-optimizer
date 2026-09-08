# Multi-Store Spatial Routing Optimizer

A software solution to minimize the route a grocery clerk has to complete in order to pack an online delivery. It minimizes distance and therefore costs.

## Overview

The Routing Optimizer runs the TSP solver in C++ (a hybrid Branch and Bound / 2-opt approach). The frontend consists of a visual 2D canvas of a store layout where users can create mock orders and see the optimal route (This frontend is a placeholder and will be replaced later).

## Key Features

- **Multi-Store Scalability:** The relational database design allows mapping products to specific coordinates based on the store id, allowing to handle multiple different stores.
- **High-Performance Routing Engine:** A native C++ graph engine approaches this Traveling Salesperson Problem (TSP) through a hybrid Branch and Bound / 2-opt approach.
- **Concurrent Request Handling:** A custom C++ HTTP server with a multi-threaded Thread Pool architecture is capable of managing multiple routing requests efficiently.
- **Thread-Safe Data Access:** A SQLite database configured with Write-Ahead Logging, allowing concurrent reads and writes without blocking.
- **Visual Path Tracing:** A React frontend displays the store's distribution and the optimal route for a specific request.

## System Architecture

- **API/Network Layer:** Custom C++ HTTP server.
- **Database:** SQLite with WAL configuration.
- **Routing Engine:** Native C++ TSP solver.
- **Build System:** CMake (backend) and Vite (frontend).
- **Frontend (UI):** Functional React components using modern JavaScript, the Fetch API, and standard CSS modules.


## Getting Started

### Prerequisites

- **Backend:** CMake (>= 3.10), C++17 compatible compiler, SQLite3, git and Make.
- **Frontend:** Node.js, npm.

### Running the Backend

```bash
cd backend
mkdir build
cd build
cmake ..
make
cd ../..
./backend/build/server
```

### Running the Frontend

```bash
cd frontend
npm install
npm run dev
```
