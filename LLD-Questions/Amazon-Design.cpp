/**
 * Basic Class structure for Amazon
*/

#include<iostream>

using namespace std;

/*Data Types Begin*/
struct Address {
    string street;
    string city;
    string pincode;
    string state;
    string country;
};

enum OrderStatus {
    Recieved,
    Pending,
    Completed,
    Cancelled
};

enum AccountStatus {
    Active,
    Blocked,
    Banned,
    Compromised
};

enum ShipmentStatus {
    Pending,
    Shipped,
    Delievered,
    Hold
};

enum PaymentStatus {
    Pending,
    Unpaid,
    Completed,
    Failed,
    Declined,
    Cancelled
};

/*Data Types End*/

class Item {
    int quantity;
    int price;
    public:
    bool updateQuantity();
};

class OrderLog {
    int orderNo;
    int creationDate;
    OrderStatus status;
};

class Order {
    vector<OrderLog> logs; // multiple logs for creation, shipped, delievered
    int orderNo;
    int orderDate;
    OrderStatus status;

    public:
    bool sendForShipment();
    bool doPayment();
    bool addOrderLog(OrderLog log);
};

class ShoppingCart {
    vector<Item> items;
    public:
    bool addItem(Item item);
    bool removeItem(Item item);
    bool updateItemQuantity(Item item, int quantity);
    bool checkout();
    vector<Item> getItems();
};






// Abstract class
class Customer {
    ShoppingCart cart;
    Order order;
    public:
    virtual ShoppingCart getShoppingCart() = 0;
    virtual bool addItemToCart(Item item) = 0;
    virtual bool removeItemFromCart(Item item) = 0;
};

class Account {
    string username;
    string password;
    string name;
    AccountStatus status;
    Address ShippingAdderess;
};

class Member : Customer {
    Account account;
    public:
    bool placeOrder();
};

class Admin {
    Account account;
    public:
    bool blockUser();
    bool AddNewProductCategory();
    bool UpdateProductCategory();
};

class Guest : Customer {
    public:
    bool registerAccount();
};

class ProductCategory {
    string name;
    string description;
};

class ProductReview {
    int rating;
    string review;
    Member reviewer;    
};

class Product {
    int id;
    string name;
    string description;
    int price;
    int availableCount;
    ProductCategory category; // Aggregation
    ProductReview review;       // Composition

    public:
    bool getAvailableCount();
    bool getReview();
};


class Product {

};


class Notification {
    int id;
    int createdDate;
    string content

    public:
    virtual bool sendNotification() = 0;
};

class SMSNotification : Notification {

};

class EmailNotification : Notification {

};

class ShipmentLog {
    int shipmentId;
    int creationDate;
    ShipmentStatus status;
};

class Shipment {
    int shipmentDate;
    int shipmentId;
    ShipmentStatus status;
    vector<ShipmentLog> logs;
    int estimatedArrival;
    string shopmentMethod;
};



int main() {

}