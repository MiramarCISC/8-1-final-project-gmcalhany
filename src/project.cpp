#include "project.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// InventoryNode
InventoryNode::InventoryNode(const InventoryItem& inventoryItem) {
    item = inventoryItem;
    next = nullptr;
}

// InventoryManager
InventoryManager::InventoryManager() {
    head = nullptr;
    itemCount = 0;
}

InventoryManager::~InventoryManager() {
    clear();
}

bool InventoryManager::isValidSku(const string& sku) {
    return !sku.empty();
}

bool InventoryManager::isValidName(const string& name) {
    return !name.empty();
}

bool InventoryManager::isValidQuantity(int quantity) {
    return quantity >= MIN_QUANTITY;
}

bool InventoryManager::isValidPrice(double price) {
    return price >= MIN_PRICE;
}

bool InventoryManager::addItem(
    const string& sku,
    const string& name,
    int quantity,
    double price
) {
    if (!isValidSku(sku) ||
        !isValidName(name) ||
        !isValidQuantity(quantity) ||
        !isValidPrice(price)) {
        return false;
    }

    if (itemCount >= MAX_INVENTORY_ITEMS) {
        return false;
    }

    if (findItem(sku) != nullptr) {
        return false;
    }

    InventoryItem newItem;
    newItem.sku = sku;
    newItem.name = name;
    newItem.quantity = quantity;
    newItem.price = price;

    InventoryNode* newNode = new InventoryNode(newItem);

    if (head == nullptr) {
        head = newNode;
    } else {
        InventoryNode* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }

    itemCount++;
    return true;
}

InventoryNode* InventoryManager::findItem(const string& sku) {
    InventoryNode* current = head;

    while (current != nullptr) {
        if (current->item.sku == sku) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

const InventoryNode* InventoryManager::findItem(const string& sku) const {
    const InventoryNode* current = head;

    while (current != nullptr) {
        if (current->item.sku == sku) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

bool InventoryManager::updateQuantity(
    const string& sku,
    int newQuantity
) {
    if (!isValidQuantity(newQuantity)) {
        return false;
    }

    InventoryNode* item = findItem(sku);

    if (item == nullptr) {
        return false;
    }

    item->item.quantity = newQuantity;
    return true;
}

bool InventoryManager::removeItem(const string& sku) {
    InventoryNode* current = head;
    InventoryNode* previous = nullptr;

    while (current != nullptr) {
        if (current->item.sku == sku) {
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }

            delete current;
            itemCount--;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

int InventoryManager::getItemCount() const {
    return itemCount;
}

bool InventoryManager::isEmpty() const {
    return head == nullptr;
}

double InventoryManager::calculateItemValue(
    const InventoryItem& item
) const {
    return item.quantity * item.price;
}

double InventoryManager::calculateTotalValue() const {
    double total = 0.0;

    const InventoryNode* current = head;

    while (current != nullptr) {
        total += calculateItemValue(current->item);
        current = current->next;
    }

    return total;
}

int InventoryManager::copyItemsToArray(
    InventoryItem items[],
    int maxItems
) const {
    if (items == nullptr || maxItems <= 0) {
        return 0;
    }

    int count = 0;
    const InventoryNode* current = head;

    while (current != nullptr && count < maxItems) {
        items[count] = current->item;
        count++;
        current = current->next;
    }

    return count;
}

void InventoryManager::sortItemsByQuantity(
    InventoryItem items[],
    int count
) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (items[j].quantity > items[j + 1].quantity) {
                InventoryItem temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

int InventoryManager::searchArrayBySku(
    const InventoryItem items[],
    int count,
    const string& sku
) {
    for (int i = 0; i < count; i++) {
        if (items[i].sku == sku) {
            return i;
        }
    }

    return -1;
}

bool InventoryManager::loadFromFile(const string& filename) {
    ifstream input(filename);

    if (!input.is_open()) {
        return false;
    }

    string sku;
    string name;
    int quantity;
    double price;

    while (input >> sku >> name >> quantity >> price) {
        addItem(sku, name, quantity, price);
    }

    input.close();
    return true;
}

bool InventoryManager::saveReportToFile(
    const string& filename
) const {
    ofstream output(filename);

    if (!output.is_open()) {
        return false;
    }

    output << fixed << setprecision(2);
    output << "INVENTORY REPORT" << endl;
    output << "================" << endl;

    const InventoryNode* current = head;

    while (current != nullptr) {
        output << current->item.sku << " "
               << current->item.name << " "
               << current->item.quantity << " "
               << current->item.price << " "
               << calculateItemValue(current->item)
               << endl;

        current = current->next;
    }

    output << "================" << endl;
    output << "Total Inventory Value: $"
           << calculateTotalValue() << endl;

    output.close();
    return true;
}

void InventoryManager::displayInventory() const {
    if (head == nullptr) {
        cout << "Inventory is empty." << endl;
        return;
    }

    cout << fixed << setprecision(2);

    cout << left
         << setw(12) << "SKU"
         << setw(22) << "Name"
         << setw(12) << "Quantity"
         << setw(12) << "Price"
         << setw(12) << "Value"
         << endl;

    cout << "--------------------------------------------------------------"
         << endl;

    const InventoryNode* current = head;

    while (current != nullptr) {
        cout << left
             << setw(12) << current->item.sku
             << setw(22) << current->item.name
             << setw(12) << current->item.quantity
             << "$" << setw(11) << current->item.price
             << "$" << setw(11)
             << calculateItemValue(current->item)
             << endl;

        current = current->next;
    }

    cout << endl;
    cout << "Total inventory value: $"
         << calculateTotalValue() << endl;
}

void InventoryManager::clear() {
    InventoryNode* current = head;

    while (current != nullptr) {
        InventoryNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    itemCount = 0;
}

bool isValidMenuChoice(int choice) {
    return choice >= 1 && choice <= 8;
}

void printMenu() {
    cout << endl;
    cout << "Inventory Management System" << endl;
    cout << "1. Display inventory" << endl;
    cout << "2. Add inventory item" << endl;
    cout << "3. Find item by SKU" << endl;
    cout << "4. Update item quantity" << endl;
    cout << "5. Remove item" << endl;
    cout << "6. Display inventory sorted by quantity" << endl;
    cout << "7. Save inventory report" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter choice: ";
}