#include <iostream>

using namespace std;

class InterfaceStrategy {
    public:
    virtual int execute(int a,int b) = 0;
};

class ConcreteStrategyAdd : public InterfaceStrategy {
    public:
    int execute(int a, int b) {
        return a + b;
    } 
};

class ConcreteStrategySubtract : public InterfaceStrategy {
    public:
    int execute(int a, int b) {
        return a - b;
    } 
};

class ConcreteStrategyMultiply : public InterfaceStrategy {
    public:
    int execute(int a, int b) {
        return a * b;
    } 
};

class Context {
    InterfaceStrategy *strategy;

    public:
    void setStrategy (InterfaceStrategy *ptr) {
        strategy = ptr;
    }

    int executeStrategy(int a, int b) {
        return strategy->execute(a,b);
    }

};

int main() {
    Context c1;
    ConcreteStrategyAdd ca;
    ConcreteStrategySubtract cb;
    ConcreteStrategyMultiply cm;
    c1.setStrategy(&ca);
    cout<<c1.executeStrategy(20,10)<<endl;
    c1.setStrategy(&cb);
    cout<<c1.executeStrategy(20,10)<<endl;
    c1.setStrategy(&cm);
    cout<<c1.executeStrategy(20,10)<<endl;
}