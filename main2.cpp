#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Product {
    int id;
    string name;
    int quantity;
    double price;
};

// Global inventory list
vector<Product> inventory;

// Function prototypes
void loadFromFile();
void saveToFile();
void addProduct();
void viewProducts();
void searchProduct();
void updateProduct();
void deleteProduct();
void generateReport();
Product parseProduct(const string &line);
string toCSV(const Product &p);

int main() {
    loadFromFile();
    int choice;
    do {
        cout << "\n--- Inventory Management System ---\n";
        cout << "1. Add Product\n2. View Products\n3. Search Product\n4. Update Product\n5. Delete Product\n6. Generate Report\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: generateReport(); break;
            case 0: saveToFile(); cout << "Data saved. Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while(choice != 0);
    return 0;
}

// --- File I/O ---
void loadFromFile() {
    ifstream fin("data.txt");
    string line;
    while (getline(fin, line)) {
        if (!line.empty())
            inventory.push_back(parseProduct(line));
    }
    fin.close();
}

void saveToFile() {
    ofstream fout("data.txt");
    for (const auto &p : inventory) {
        fout << toCSV(p) << endl;
    }
    fout.close();
}

Product parseProduct(const string &line) {
    stringstream ss(line);
    string item;
    Product p;
    getline(ss, item, ','); p.id = stoi(item);
    getline(ss, item, ','); p.name = item;
    getline(ss, item, ','); p.quantity = stoi(item);
    getline(ss, item, ','); p.price = stod(item);
    return p;
}

string toCSV(const Product &p) {
    return to_string(p.id) + "," + p.name + "," + to_string(p.quantity) + "," + to_string(p.price);
}

// --- Core Features ---
void addProduct() {
    Product p;
    cout << "Enter ID: "; cin >> p.id;
    cout << "Enter Name: "; cin.ignore(); getline(cin, p.name);
    cout << "Enter Quantity: "; cin >> p.quantity;
    cout << "Enter Price: "; cin >> p.price;
    inventory.push_back(p);
    cout << "Product added.\n";
}

void viewProducts() {
    cout << "\nID\tName\t\tQty\tPrice\n";
    for (const auto &p : inventory)
        cout << p.id << "\t" << p.name << "\t\t" << p.quantity << "\t" << p.price << "\n";
}

void searchProduct() {
    int id;
    cout << "Enter Product ID to search: ";
    cin >> id;
    auto it = find_if(inventory.begin(), inventory.end(), [id](Product p){ return p.id == id; });
    if (it != inventory.end()) {
        cout << "Found: " << it->name << " | Qty: " << it->quantity << " | Price: " << it->price << "\n";
    } else {
        cout << "Product not found.\n";
    }
}

void updateProduct() {
    int id;
    cout << "Enter Product ID to update: ";
    cin >> id;
    for (auto &p : inventory) {
        if (p.id == id) {
            cout << "New Quantity: "; cin >> p.quantity;
            cout << "New Price: "; cin >> p.price;
            cout << "Updated successfully.\n";
            return;
        }
    }
    cout << "Product not found.\n";
}

void deleteProduct() {
    int id;
    cout << "Enter Product ID to delete: ";
    cin >> id;
    auto it = remove_if(inventory.begin(), inventory.end(), [id](Product p){ return p.id == id; });
    if (it != inventory.end()) {
        inventory.erase(it, inventory.end());
        cout << "Product deleted.\n";
    } else {
        cout << "Product not found.\n";
    }
}

void generateReport() {
    int totalQty = 0;
    double totalValue = 0;
    for (const auto &p : inventory) {
        totalQty += p.quantity;
        totalValue += p.quantity * p.price;
    }
    cout << "\nTotal Products: " << inventory.size();
    cout << "\nTotal Quantity: " << totalQty;
    cout << "\nTotal Inventory Value: ₹" << totalValue << "\n";
}
