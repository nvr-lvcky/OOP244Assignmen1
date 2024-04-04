#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Product {
protected:
    string name;
    double price;
    int quantity;

public:
    Product(const string& name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    virtual ~Product() {}

    virtual double calculateTotalPrice() const {
        return price * quantity;
    }

    virtual void displayProductInfo() const {
        cout << "Name: " << setw(15) << left << name << " | "
            << "Price: $ " << setw(6) << fixed << setprecision(2) << price << " | "
            << "Quantity: " << quantity;
    }

    const string& getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    double getPrice() const {
        return price;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }
};

class Fruit : public Product {
protected:
    string origin;

public:
    Fruit(const string& name, double price, int quantity, const string& origin)
        : Product(name, price, quantity), origin(origin) {}

    void displayProductInfo() const override {
        Product::displayProductInfo();
        cout << " | Origin: " << origin << endl;
    }
};

class Mangoes : public Fruit {
public:
    Mangoes(const string& name, double price, int quantity, const string& origin)
        : Fruit(name, price, quantity, origin) {}
};

class PakistaniMangoes : public Mangoes {
public:
    PakistaniMangoes(const string& name, double price, int quantity)
        : Mangoes(name, price, quantity, "Pakistan") {}
};

class Chaunsa : public PakistaniMangoes {
public:
    Chaunsa(double price, int quantity)
        : PakistaniMangoes("Chaunsa Mango", price, quantity) {}
};

class Vegetable : public Product {
protected:
    bool organic;

public:
    Vegetable(const string& name, double price, int quantity, bool organic)
        : Product(name, price, quantity), organic(organic) {}

    void displayProductInfo() const override {
        Product::displayProductInfo();
        cout << " | Organic: " << (organic ? "Yes" : "No") << endl;
    }
};

class BakeryItem : public Product {
protected:
    bool glutenFree;

public:
    BakeryItem(const string& name, double price, int quantity, bool glutenFree)
        : Product(name, price, quantity), glutenFree(glutenFree) {}

    void displayProductInfo() const override {
        Product::displayProductInfo();
        cout << " | Gluten-Free: " << (glutenFree ? "Yes" : "No") << endl;
    }
};

class Meat : public Product {
protected:
    bool halal;

public:
    Meat(const string& name, double price, int quantity, bool halal)
        : Product(name, price, quantity), halal(halal) {}

    void displayProductInfo() const override {
        Product::displayProductInfo();
        cout << " | Halal: " << (halal ? "Yes" : "No") << endl;
    }
};

class Inventory {
private:
    vector<Product*> products;

public:
    ~Inventory() {
 
        for (Product* product : products) {
            delete product;
        }
    }

    void addProduct(Product* product) {
        products.push_back(product);
    }

    void updateQuantity(const string& name, int newQuantity) {
        for (Product* product : products) {
            if (product->getName() == name) {
                product->setQuantity(newQuantity);
                return;
            }
        }
        throw invalid_argument("Product not found.");
    }

    void generateInventoryReport() const {
        cout << setw(35) << left << "Product Details" << endl;
        cout << "---------------------------------------------------------" << endl;
        for (const Product* product : products) {
            product->displayProductInfo();
        }
        cout << "---------------------------------------------------------" << endl;
    }

    Product* findProductByName(const string& name) const {
        for (Product* product : products) {
            if (product->getName() == name) {
                return product;
            }
        }
        return nullptr;
    }
};

void printMenu() {
    cout << "Welcome to Grocery Store Inventory Management System" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Update Product Quantity" << endl;
    cout << "3. Generate Inventory Report" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

void main() {
    Inventory inventory;

    int choice;
    do {
        printMenu();
        cin >> choice;
        switch (choice) {
        case 1: {
            string name, origin;
            double price;
            int quantity;
            bool organic, glutenFree, halal;

            int typeChoice;
            cout << "Select product type:" << endl;
            cout << "1. Fruit" << endl;
            cout << "2. Vegetable" << endl;
            cout << "3. Bakery Item" << endl;
            cout << "4. Meat Item" << endl;
            cout << "Enter your choice: ";
            cin >> typeChoice;

            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product price: $";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;

            switch (typeChoice) {
            case 1:
                cout << "Enter country of origin: ";
                cin >> origin;
                inventory.addProduct(new Fruit(name, price, quantity, origin));
                break;
            case 2:
                cout << "Is it organic? (1 for Yes, 0 for No): ";
                cin >> organic;
                inventory.addProduct(new Vegetable(name, price, quantity, organic));
                break;
            case 3:
                cout << "Is it gluten-free? (1 for Yes, 0 for No): ";
                cin >> glutenFree;
                inventory.addProduct(new BakeryItem(name, price, quantity, glutenFree));
                break;
            case 4:
                cout << "Is the meat halal? (1 for Yes, 0 for No): ";
                cin >> halal;
                inventory.addProduct(new Meat(name, price, quantity, halal));
            default:
                cout << "Invalid choice" << endl;
            }
            break;
        }
        case 2: {
            string name;
            int newQuantity;

            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter new quantity: ";
            cin >> newQuantity;

            try {
                inventory.updateQuantity(name, newQuantity);
                cout << "Quantity updated successfully." << endl;
            }
            catch (const invalid_argument& e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }
        case 3:
            inventory.generateInventoryReport();
            break;
        case 4:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 4);

}
