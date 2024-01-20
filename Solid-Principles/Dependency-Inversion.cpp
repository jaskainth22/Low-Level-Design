#include<iostream>

using namespace std;

// abstract
class Mouse {
    public:

    virtual void mouseFun() = 0;
};

//abstract
class KeyBoard {
    public:

    virtual void keyboardFun() = 0;
};

class wiredMouse : Mouse {
    void mouseFun() {

    };
};

class bluetoothMouse : Mouse {
    void mouseFun() {

    };
};

class wiredKeyboard : KeyBoard {
    void keyboardFun() {

    };
};

class bluetoothKeyboard : KeyBoard {
    void keyboardFun() {

    };
};

class Macbook : wiredKeyboard {
    // Here we are limiting ourseleves by extending concrete class
};

class Macbook1 : KeyBoard{
    // here we are extending interface
};

int main() {

}