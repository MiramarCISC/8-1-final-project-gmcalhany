#include "project.hpp"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool approximatelyEqual(double first, double second) {
    return fabs(first - second) < 0.001;
}

// Week 1: Program basics, variables, constants, arithmetic, and output values.
void testWeek1ProgramBasics() {
    InventoryManager inventory;

    InventoryItem item;
    item.sku = "A100";
    item.name = "Wrench";
    item.quantity = 4;
    item.price = 12.50;

    assert(MAX_INVENTORY_ITEMS == 100);
    assert(MIN_QUANTITY == 0);
    assert(approximatelyEqual(MIN_PRICE, 0.0));
    assert(approximatelyEqual(inventory.calculateItemValue(item), 50.0));
}

// Week 2: Decisions and loops through validation and duplicate checking.
void testWeek2DecisionsAndLoops() {
    InventoryManager inventory;

    assert(inventory.addItem("B200", "Hammer", 5, 18.00));
    assert(!inventory.addItem("B200", "Duplicate", 2, 5.00));
    assert(!inventory.addItem("", "MissingSku", 2, 5.00));
    assert(!inventory.addItem("B201", "", 2, 5.00));
    assert(!inventory.addItem("B202", "InvalidQuantity", -1, 5.00));
    assert(!inventory.addItem("B203", "InvalidPrice", 2, -5.00));
    assert(inventory.getItemCount() == 1);
}

// Week 3: Functions and program design.
void testWeek3FunctionsAndDesign() {
    InventoryManager inventory;

    assert(inventory.addItem("C300", "Drill", 3, 40.00));
    assert(inventory.updateQuantity("C300", 8));
    assert(!inventory.updateQuantity("UNKNOWN", 8));
    assert(!inventory.updateQuantity("C300", -1));

    const InventoryNode* found = inventory.findItem("C300");
    assert(found != nullptr);
    assert(found->item.quantity == 8);
    assert(approximatelyEqual(inventory.calculateTotalValue(), 320.0));
}

// Week 4: Arrays, searching, and sorting.
void testWeek4ArraysSearchingAndSorting() {
    InventoryManager inventory;

    assert(inventory.addItem("D100", "Pliers", 12, 8.00));
    assert(inventory.addItem("D200", "Saw", 3, 22.00));
    assert(inventory.addItem("D300", "Level", 7, 14.00));

    InventoryItem items[MAX_INVENTORY_ITEMS];
    int count = inventory.copyItemsToArray(items, MAX_INVENTORY_ITEMS);

    assert(count == 3);
    assert(InventoryManager::searchArrayBySku(items, count, "D200") == 1);
    assert(InventoryManager::searchArrayBySku(items, count, "NONE") == -1);

    InventoryManager::sortItemsByQuantity(items, count);

    assert(items[0].quantity == 3);
    assert(items[1].quantity == 7);
    assert(items[2].quantity == 12);
}

// Week 5: Strings and structures.
void testWeek5StringsAndStructures() {
    InventoryManager inventory;

    InventoryItem item;
    item.sku = "E500";
    item.name = "SocketSet";
    item.quantity = 2;
    item.price = 35.75;

    assert(InventoryManager::isValidSku(item.sku));
    assert(InventoryManager::isValidName(item.name));
    assert(InventoryManager::isValidQuantity(item.quantity));
    assert(InventoryManager::isValidPrice(item.price));

    assert(inventory.addItem(
        item.sku,
        item.name,
        item.quantity,
        item.price
    ));

    const InventoryNode* found = inventory.findItem("E500");
    assert(found != nullptr);
    assert(found->item.sku == "E500");
    assert(found->item.name == "SocketSet");
}

// Week 6: Pointers, dynamic memory, and linked lists.
void testWeek6PointersDynamicMemoryAndLinkedLists() {
    InventoryManager inventory;

    assert(inventory.isEmpty());
    assert(inventory.addItem("F100", "Bolt", 20, 0.50));
    assert(inventory.addItem("F200", "Nut", 30, 0.25));
    assert(inventory.addItem("F300", "Washer", 40, 0.10));

    InventoryNode* node = inventory.findItem("F200");
    assert(node != nullptr);
    assert(node->item.name == "Nut");

    assert(inventory.removeItem("F200"));
    assert(inventory.findItem("F200") == nullptr);
    assert(inventory.getItemCount() == 2);
    assert(!inventory.removeItem("UNKNOWN"));

    inventory.clear();
    assert(inventory.isEmpty());
    assert(inventory.getItemCount() == 0);
}

// Week 7: File input/output and integration.
void testWeek7FileIOAndIntegration() {
    const string inputFile = "tests/resources/inventory_test_input.txt";
    const string reportFile = "tests/resources/inventory_test_report.txt";

    {
        ofstream output(inputFile);
        assert(output.is_open());

        output << "G100 Screwdriver 5 9.50\n";
        output << "G200 Toolbox 2 45.00\n";
        output << "G300 TapeMeasure 4 12.25\n";
    }

    InventoryManager inventory;

    assert(inventory.loadFromFile(inputFile));
    assert(inventory.getItemCount() == 3);
    assert(inventory.findItem("G200") != nullptr);
    assert(approximatelyEqual(inventory.calculateTotalValue(), 186.50));

    assert(inventory.saveReportToFile(reportFile));

    ifstream report(reportFile);
    assert(report.is_open());

    string contents;
    string line;

    while (getline(report, line)) {
        contents += line + "\n";
    }

    assert(contents.find("INVENTORY REPORT") != string::npos);
    assert(contents.find("G100") != string::npos);
    assert(contents.find("G200") != string::npos);
    assert(contents.find("G300") != string::npos);
    assert(contents.find("186.50") != string::npos);

    report.close();

    remove(inputFile.c_str());
    remove(reportFile.c_str());
}

int main() {
    testWeek1ProgramBasics();
    testWeek2DecisionsAndLoops();
    testWeek3FunctionsAndDesign();
    testWeek4ArraysSearchingAndSorting();
    testWeek5StringsAndStructures();
    testWeek6PointersDynamicMemoryAndLinkedLists();
    testWeek7FileIOAndIntegration();

    cout << "All Inventory Management System tests passed!" << endl;

    return 0;
}