#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ---------------- MenuItem ----------------
class MenuItem {
public:
    string itemName;
    float price;
    string category;

    MenuItem() {
        itemName = "";
        price = 0;
        category = "";
    }

    MenuItem(const string& name, float p, const string& cat) {
        itemName = name;
        price = p;
        category = cat;
    }

    void display() const {
        cout << itemName << " | " << category << " | $" << price << endl;
    }
};

// ---------------- Customer ----------------
class Customer {
public:
    string name;
    string phone;

    Customer() {
        name = "";
        phone = "";
    }

    Customer(const string& n, const string& ph) {
        name = n;
        phone = ph;
    }

    void displayInfo() const {
        cout << "Customer: " << name << ", Phone: " << phone << endl;
    }
};

// ---------------- Payment ----------------
class Payment {
public:
    string type;
    float amount;

    Payment() {
        type = "";
        amount = 0;
    }

    Payment(const string& t, float a) {
        type = t;
        amount = a;
    }

    void process() const {
        cout << "Payment of $" << amount << " via " << type << endl;
    }
};

// ---------------- Order ----------------
class Order {
public:
    Customer customer;
    vector<MenuItem> items;
    float total;
    Payment payment;

    Order() {
        total = 0;
    }

    void addItem(const MenuItem& item) {
        items.push_back(item);
        total += item.price;
    }

    void setCustomer(const Customer& c) {
        customer = c;
    }

    void setPayment(const Payment& p) {
        payment = p;
    }

    void displaySummary() const {
        cout << "\n--- Order Summary ---\n";
        customer.displayInfo();
        cout << "Items:\n";
        for (size_t i = 0; i < items.size(); i++) {
            items[i].display();
        }
        float tax = total * 0.16f;
        float service = total * 0.10f;
        float finalTotal = total + tax + service;
        cout << "Subtotal: $" << total << endl;
        cout << "Tax: $" << tax << endl;
        cout << "Service: $" << service << endl;
        cout << "Total: $" << finalTotal << endl;
        payment.process();
    }
};

// ---------------- Restaurant ----------------
class Restaurant {
public:
    string name;
    vector<MenuItem> menu;
    vector<Order> orders;

    Restaurant(const string& n) {
        name = n;
    }

    void addMenuItem(const MenuItem& item) {
        menu.push_back(item);
    }

    void showMenu() const {
        cout << "\n--- Menu of " << name << " ---\n";
        for (size_t i = 0; i < menu.size(); i++) {
            menu[i].display();
        }
    }

    void addOrder(const Order& order) {
        orders.push_back(order);
    }

    void showOrders() const {
        cout << "\n=== All Orders ===\n";
        for (size_t i = 0; i < orders.size(); i++) {
            orders[i].displaySummary();
        }
    }
};

// ---------------- main ----------------
int main() {
    Restaurant r("Tasty Foods");

    int choice;
    do {
        cout << "\n1. Add Menu Item\n2. Show Menu\n3. Create Order\n4. Show Orders\n0. Exit\nChoice: ";
        cin >> choice;
        cin.ignore(); 

        if (choice == 1) {
            string name, category;
            float price;
            cout << "Enter item name: ";
            getline(cin, name);
            cout << "Enter category: ";
            getline(cin, category);
            cout << "Enter price: ";
            cin >> price;
            cin.ignore();
            r.addMenuItem(MenuItem(name, price, category));
        }
        else if (choice == 2) {
            r.showMenu();
        }
        else if (choice == 3) {
            Order o;
            string custName, custPhone;
            cout << "Enter customer name: ";
            getline(cin, custName);
            cout << "Enter customer phone: ";
            getline(cin, custPhone);
            o.setCustomer(Customer(custName, custPhone));

            int numItems;
            cout << "Enter number of items: ";
            cin >> numItems;
            cin.ignore();

            for (int i = 0; i < numItems; i++) {
                string itemName;
                cout << "Enter item name from menu: ";
                getline(cin, itemName);
                
                bool found = false;
                for (size_t j = 0; j < r.menu.size(); j++) {
                    if (r.menu[j].itemName == itemName) {
                        o.addItem(r.menu[j]);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Item not found!\n";
                }
            }

            string payType;
            cout << "Enter payment type (Cash/Card): ";
            getline(cin, payType);

            float subtotal = o.total;
            float totalAmount = subtotal + subtotal * 0.16f + subtotal * 0.10f;
            o.setPayment(Payment(payType, totalAmount));

            r.addOrder(o);
        }
        else if (choice == 4) {
            r.showOrders();
        }

    } while (choice != 0);

    cout << "Exiting program.\n";
    return 0;
}