#include<iostream>

using namespace std;

class Marker {
    public:
    string name;
    string color;
    int year;
    int price;

    Marker (string n, string c, int y, int p) : name(n), color(c), year(y), price(p) {
        // cout<<"Called constructor";
    }
};

class invoice1 {
    public:
    Marker marker;
    int quantity;

    invoice1(Marker m, int q) : marker(m), quantity(q) {
        // 
    }

    int calculateTask() {
        int price = marker.price * quantity;
        return price;
    }
};

class InvoiceSaveToDB {
    private:
    invoice1 i;

    public:

    InvoiceSaveToDB(invoice1 x) : i(x) {
        //
    }

    void saveToDB() {
        // save the data to SQL DB;
    }

    // this is a new function, but this does not follow the open-closed principle
    // We should not add new function to already existing classes
    void saveToNoSQLDB() {
        //save data to NoSQL DB
    }
};

// Abstarct class
class InvoiceSaveToDB1 {
    protected:
    invoice1 i1;

    public:
    InvoiceSaveToDB1(invoice1 i) : i1(i) {
        // constructor
        cout<<"This is InvoiceSaveToDB1 constructor"<<endl;
    }

    // pure virtual function
    virtual void saveTODB() const = 0;

    virtual ~InvoiceSaveToDB1() {
        // Virtual destructor
        cout<<"This is InvoiceSaveToDB1 destructor"<<endl;
    }
};

class InvoiceSaveToSQLDB : public InvoiceSaveToDB1 {
    public:
    InvoiceSaveToSQLDB(invoice1 i) : InvoiceSaveToDB1(i) {
        cout<<"This is InvoiceSaveToSQLDB constructor"<<endl;
    }

    void saveTODB() const override {
        cout<<"Saving in SQL DB"<<endl;
    }
};

class InvoiceSaveToNoSQLDB : public InvoiceSaveToDB1 {
    public:
    InvoiceSaveToNoSQLDB(invoice1 i) : InvoiceSaveToDB1(i) {
        cout<<"This is InvoiceSaveToNoSQLDB constructor"<<endl;
    }

    void saveTODB() const override {
        cout<<"Saving in NO SQL DB"<<endl;
    }
};

int main() {
    Marker m1("Cello", "Black", 1999, 50);
    invoice1 i1(m1,10);

    InvoiceSaveToSQLDB isql(i1);
    InvoiceSaveToNoSQLDB inosql(i1); 

    isql.saveTODB();

    inosql.saveTODB();
}