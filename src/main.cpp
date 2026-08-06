#include "project.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void clearInputLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    InventoryManager inventory;
    int choice = 0;

    cout << "CISC 192 Final Project: Inventory Management System"
         << endl;

    if (inventory.loadFromFile("data/inventory.txt")) {
        cout << "Starting inventory loaded from data/inventory.txt."
             << endl;
    } else {
        cout << "No starting inventory file was loaded." << endl;
    }

    do {
        printMenu();

        if (!(cin >> choice)) {
            cin.clear();
            clearInputLine();
            cout << "Invalid input. Please enter a number from 1 to 8."
                 << endl;
            continue;
        }

        clearInputLine();

        if (!isValidMenuChoice(choice)) {
            cout << "Invalid choice. Please enter a number from 1 to 8."
                 << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                inventory.displayInventory();
                break;
            }

            case 2: {
                string sku;
                string name;
                int quantity;
                double price;

                cout << "Enter SKU: ";
                getline(cin, sku);

                cout << "Enter item name: ";
                getline(cin, name);

                cout << "Enter quantity: ";
                if (!(cin >> quantity)) {
                    cin.clear();
                    clearInputLine();
                    cout << "Invalid quantity." << endl;
                    break;
                }

                cout << "Enter price: ";
                if (!(cin >> price)) {
                    cin.clear();
                    clearInputLine();
                    cout << "Invalid price." << endl;
                    break;
                }

                clearInputLine();

                if (inventory.addItem(sku, name, quantity, price)) {
                    cout << "Item added successfully." << endl;
                } else {
                    cout << "Item could not be added. Check the values "
                         << "and make sure the SKU is unique." << endl;
                }

                break;
            }

            case 3: {
                string sku;

                cout << "Enter SKU to find: ";
                getline(cin, sku);

                const InventoryNode* found = inventory.findItem(sku);

                if (found == nullptr) {
                    cout << "Item not found." << endl;
                } else {
                    cout << fixed << setprecision(2);
                    cout << "SKU: " << found->item.sku << endl;
                    cout << "Name: " << found->item.name << endl;
                    cout << "Quantity: " << found->item.quantity << endl;
                    cout << "Price: $" << found->item.price << endl;
                    cout << "Value: $"
                         << inventory.calculateItemValue(found->item)
                         << endl;
                }

                break;
            }

            case 4: {
                string sku;
                int newQuantity;

                cout << "Enter SKU to update: ";
                getline(cin, sku);

                cout << "Enter new quantity: ";
                if (!(cin >> newQuantity)) {
                    cin.clear();
                    clearInputLine();
                    cout << "Invalid quantity." << endl;
                    break;
                }

                clearInputLine();

                if (inventory.updateQuantity(sku, newQuantity)) {
                    cout << "Quantity updated successfully." << endl;
                } else {
                    cout << "Item was not found or the quantity was invalid."
                         << endl;
                }

                break;
            }

            case 5: {
                string sku;

                cout << "Enter SKU to remove: ";
                getline(cin, sku);

                if (inventory.removeItem(sku)) {
                    cout << "Item removed successfully." << endl;
                } else {
                    cout << "Item not found." << endl;
                }

                break;
            }

            case 6: {
                InventoryItem items[MAX_INVENTORY_ITEMS];

                int count = inventory.copyItemsToArray(
                    items,
                    MAX_INVENTORY_ITEMS
                );

                InventoryManager::sortItemsByQuantity(items, count);

                if (count == 0) {
                    cout << "Inventory is empty." << endl;
                    break;
                }

                cout << fixed << setprecision(2);
                cout << left
                     << setw(12) << "SKU"
                     << setw(22) << "Name"
                     << setw(12) << "Quantity"
                     << setw(12) << "Price"
                     << endl;

                cout << "--------------------------------------------------"
                     << endl;

                for (int i = 0; i < count; i++) {
                    cout << left
                         << setw(12) << items[i].sku
                         << setw(22) << items[i].name
                         << setw(12) << items[i].quantity
                         << "$" << items[i].price
                         << endl;
                }

                break;
            }

            case 7: {
                string filename;

                cout << "Enter report filename "
                     << "(example: data/inventory_report.txt): ";
                getline(cin, filename);

                if (inventory.saveReportToFile(filename)) {
                    cout << "Inventory report saved successfully."
                         << endl;
                } else {
                    cout << "The inventory report could not be saved."
                         << endl;
                }

                break;
            }

            case 8: {
                cout << "Exiting Inventory Management System." << endl;
                break;
            }
        }
    } while (choice != 8);

    return 0;
}