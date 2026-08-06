#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>

const int MAX_INVENTORY_ITEMS = 100;
const int MIN_QUANTITY = 0;
const double MIN_PRICE = 0.0;

// Represents one inventory record.
struct InventoryItem {
    std::string sku;
    std::string name;
    int quantity;
    double price;
};

// Represents one dynamically allocated node in the inventory linked list.
class InventoryNode {
public:
    InventoryItem item;
    InventoryNode* next;

    InventoryNode(const InventoryItem& inventoryItem);
};

// Manages inventory records using a linked list.
class InventoryManager {
private:
    InventoryNode* head;
    int itemCount;

public:
    InventoryManager();

    InventoryManager(const InventoryManager& other) = delete;
    InventoryManager& operator=(const InventoryManager& other) = delete;

    ~InventoryManager();

    bool addItem(
        const std::string& sku,
        const std::string& name,
        int quantity,
        double price
    );

    InventoryNode* findItem(const std::string& sku);
    const InventoryNode* findItem(const std::string& sku) const;

    bool updateQuantity(const std::string& sku, int newQuantity);
    bool removeItem(const std::string& sku);

    int getItemCount() const;
    bool isEmpty() const;

    double calculateItemValue(const InventoryItem& item) const;
    double calculateTotalValue() const;

    int copyItemsToArray(
        InventoryItem items[],
        int maxItems
    ) const;

    static void sortItemsByQuantity(
        InventoryItem items[],
        int count
    );

    static int searchArrayBySku(
        const InventoryItem items[],
        int count,
        const std::string& sku
    );

    bool loadFromFile(const std::string& filename);
    bool saveReportToFile(const std::string& filename) const;

    void displayInventory() const;
    void clear();

    static bool isValidSku(const std::string& sku);
    static bool isValidName(const std::string& name);
    static bool isValidQuantity(int quantity);
    static bool isValidPrice(double price);
};

bool isValidMenuChoice(int choice);
void printMenu();

#endif