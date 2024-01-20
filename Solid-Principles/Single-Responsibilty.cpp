#include<iostream>

using namespace std;

class Marker {
    public:
    string name;
    string color;
    int year;
    int price;

    Marker (string n, string c, int y, int p) : name(n), color(c), year(y), price(p) {
        cout<<"Called constructor";
    }
};
// This class does not follow single responsibilty model
// As this class has multiple responsibiltites
// split this class into multiple classes having only single responsibilty
class invoice {
    private:
    Marker marker;
    int quantity;

    public:

    invoice(Marker m, int q) : marker(m), quantity(q) {
        // 
    }

    int calculateTask() {
        int price = marker.price * quantity;
        return price;
    }

    void printInvoice () {
        // print the invoice;
    }

    void saveToDB() {
        // save the data to DB;
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
        // save the data to DB;
    }
};

class InvoicePrint {
    private:
    invoice1 inv;

    public:

    InvoicePrint(invoice1 x) : inv(x) {
        //
    }

    void printInvoice() {
        cout<<inv.quantity<<endl;

        cout<<"Lets print maker details"<< " ";
        cout<<inv.marker.name<<" "<<inv.marker.color<<" "<<inv.marker.price<<" "<<inv.marker.year;
    }
};

int main() {
    Marker m1("Cello", "Black", 1999, 50);
    invoice1 i1(m1,10);
    InvoicePrint iprint(i1);
    // int res = i1.calculateTask();
    // cout<<res;
    iprint.printInvoice();
}