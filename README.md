# Pirate Fleet Management System ⚓

An advanced C++ data structures project implementing a dynamic pirate fleet management system using Union-Find, hash tables, linked lists, and amortized complexity optimizations.

Developed as part of the Data Structures course at the Technion.

---

## Overview

This project simulates a large-scale pirate fleet system that supports efficient management of:

- Pirate fleets
- Fleet unions
- Pirate ownership
- Dynamic fleet operations
- Fast search and retrieval
- Rank propagation across merged fleets

The system was designed from scratch without STL containers, focusing on:

- Algorithmic efficiency
- Memory management
- Pointer-based data structures
- Amortized analysis
- Advanced union-find optimizations

---

## Features

### Fleet Management

- Add new fleets
- Unite fleets dynamically
- Track pirate ownership
- Maintain fleet hierarchy
- Handle deleted/merged fleets

### Pirate Management

- Add pirates to fleets
- Manage pirate money
- Rank pirates dynamically
- Query pirate information
- Handle pirate arguments/interactions

### Advanced Data Structure Features

- Dynamic hash tables
- Chained hashing collision handling
- Dynamic resizing (expand/shrink)
- Union-Find with path compression
- Union by size/rank
- Doubly linked lists
- Dynamic arrays
- Recursive rank accumulation

---

## Data Structures Used

### Union-Find (Disjoint Set)

Used for:

- Fleet grouping
- Dynamic fleet unions
- Efficient root finding
- Path compression optimization

### Hash Tables

Two custom dynamic hash tables were implemented:

- Pirate hash table
- Fleet hash table

Features:

- Modulo-based hashing
- Chained collision handling
- Dynamic resizing
- Amortized O(1) operations

### Linked Lists

Custom doubly linked lists used for:

- Collision chains
- Dynamic storage
- Efficient insertion/removal

### Dynamic Arrays

Implemented dynamic array infrastructure supporting:

- Expansion
- Shrinking
- Rehashing
- Efficient memory management

---

## Key Algorithms

### Union by Size

When merging fleets, the smaller fleet is attached to the larger one to maintain efficient tree height.

### Path Compression

The Union-Find structure compresses paths during `find()` operations to optimize future lookups.

### Dynamic Rehashing

Hash tables automatically:

- Expand when load factor grows
- Shrink when utilization decreases
- Rehash all elements efficiently

---

## Complexity Optimizations

The project focuses heavily on amortized complexity analysis and efficient runtime guarantees.

### Average Complexities

| Operation | Complexity |
|---|---|
| Hash Table Search | O(1) amortized |
| Hash Table Insert | O(1) amortized |
| Hash Table Delete | O(1) amortized |
| Union-Find Find | α(n) |
| Union-Find Union | α(n) |
| Linked List Insert | O(n) |
| Linked List Delete | O(n) |

---

## Project Structure

```bash id="w3"
.
├── pirates24b2.cpp
├── pirates24b2.h
├── UnionFind.h
├── fleet.cpp
├── fleet.h
├── pirate.cpp
├── pirate.h
├── LinkedList.h
└──  DynamicArrayWithList.h
