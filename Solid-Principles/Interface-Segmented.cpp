#include<iostream>

using namespace std;

// abstarct class
class RestaurantEmployee {
    public:

    virtual void washDishes() = 0;
    virtual void serveCustomers() = 0;
    virtual void cookFood() = 0;
};

class waiter : RestaurantEmployee {
    public:

    // ideally we should not have to implement the functions which are not required in my class
    // so we should bisect our interface further
    void washDishes() override {
        // not my job
    }

    void cookFood() override  {
        // not my job
    }

    void serveCustomers() override {
        cout<<" Serving cusotmers ";
    }
};

class WaiterInterface {
    public:

    virtual void serveCustomers() = 0;
    virtual void takeOrder() = 0; 
};

class ChefInterface {
    public:

    virtual void cookFood() = 0;
    virtual void decideMenu() = 0; 
};

class waiter1 : WaiterInterface {
    public:

    // since waiter interface contains functions only specific to waiters job, we will implement them
    // this is interface segmented principle
    void serveCustomers() {
        // do stuff
    }
    void takeOrder() {
        //do stuff
    }
};


int main() {

}