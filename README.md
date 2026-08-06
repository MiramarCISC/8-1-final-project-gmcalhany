# Inventory Management System

## CISC 192 Final Project

This project is a C++ Inventory Management System that allows a user to manage inventory items through a menu-driven program. Each inventory item contains a SKU, name, quantity, and price. The program can add, search, update, remove, display, sort, and save inventory information.

## Features

The program allows the user to:

1. Display all inventory items
2. Add a new inventory item
3. Find an item by SKU
4. Update an item's quantity
5. Remove an item
6. Display inventory sorted by quantity
7. Save an inventory report to a file
8. Exit the program

The program also loads starting inventory data from `data/inventory.txt`.

## Course Concepts Demonstrated

This project incorporates concepts covered throughout CISC 192:

- **Program basics:** variables, constants, arithmetic, input, and output
- **Decisions and loops:** menu processing, validation, and inventory traversal
- **Functions:** separate functions for inventory operations and validation
- **Arrays:** inventory items can be copied into an array for processing
- **Searching:** inventory can be searched by SKU
- **Sorting:** inventory items can be sorted by quantity
- **Strings and structures:** each inventory item stores a SKU, name, quantity, and price
- **Pointers and dynamic memory:** inventory nodes are dynamically allocated
- **Linked lists:** inventory items are maintained using linked nodes
- **File input/output:** starting inventory is loaded from a file and reports can be written to a file
- **Testing:** automated tests verify the major features of the program

## Project Structure

- `include/project.hpp` - declarations for the inventory structures, class, constants, and functions
- `src/project.cpp` - implementation of the Inventory Management System
- `src/main.cpp` - menu-driven user interface
- `tests/test_project.cpp` - automated tests
- `data/inventory.txt` - starting inventory data

## Build and Run

Compile the program:

```bash
make
```

Run the program:

```bash
./main
```

Run the automated tests:

```bash
make test
```

## Example Inventory

The included data file contains example inventory items such as:

- Apples
- Bread
- Cereal

The program calculates the value of each item by multiplying its quantity by its price and can also calculate the total value of the entire inventory.

## Testing

The automated test suite checks:

- Constants and calculations
- Input validation
- Duplicate SKU prevention
- Adding inventory items
- Finding items by SKU
- Updating quantities
- Removing items
- Arrays
- Searching and sorting
- Strings and structures
- Linked-list operations
- Dynamic memory
- File input/output
- Inventory report generation
- Total inventory value calculations

Run the tests with:

```bash
make test
```

A successful test run displays:

```text
All Inventory Management System tests passed!
```

## Author

Garrick McAlhany

CISC 192 Final Project