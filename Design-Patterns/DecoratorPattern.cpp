#include<iostream>

using namespace std;

class Beverage {
    public:
    virtual int cost() = 0;
};

class Decaf : public Beverage {
    public:
    int cost() {
        return 5;
    } 
};

class Espresso : public Beverage {
    public:
    int cost() {
        return 10;
    }  
};

class AddOnDecorator : public Beverage {
    private:
    Beverage* beverage;
    public:
    AddOnDecorator(Beverage* b) : beverage(b) {};

    int cost() {
        return beverage->cost();
    }
};

class CaramelDecorator : public AddOnDecorator {
    public:
    CaramelDecorator(Beverage* b) : AddOnDecorator(b) {};

    int cost() {
        return AddOnDecorator::cost() + 2;
    }
};

class SoyMilkDecorator : public AddOnDecorator {
    public:
    SoyMilkDecorator(Beverage *b) : AddOnDecorator(b) {};

    int cost () {
        return AddOnDecorator::cost() + 3;
    }
};

int main() {
    Decaf d;
    Espresso s;
    CaramelDecorator cd(&d);
    SoyMilkDecorator smd(&s);
    CaramelDecorator cmdWsmd(&smd);

    cout<<d.cost()<<endl;
    cout<<s.cost()<<endl;
    cout<<cd.cost()<<endl;
    cout<<smd.cost()<<endl;
    cout<<cmdWsmd.cost()<<endl;
}