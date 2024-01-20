#include<iostream>

using namespace std;

// Abstarct class
class Bike {
    virtual void turnOnEngine() = 0;
    virtual void accelerate() = 0;
};

class MotorCycle : public Bike {
    public:
    bool isEngineOn = false;
    int speed = 0;
    void turnOnEngine() override {
        isEngineOn = true;
    }
    void accelerate() override {
        speed++;
    }
};

class Bicycle : public Bike {
    public:
    bool isEngineOn = false;
    int speed = 0;

    // This is now limiting the capabilities of parent class - Wrong
    void turnOnEngine() override {
        throw runtime_error("Not possible");
    }
    void accelerate() override {
        speed++;
    }
};

// to avoid this, its best to segregate/truncate Bike class further

class Bike1 {
    virtual void accelerate() = 0;
};

class hasMotor : Bike1 {
    virtual void turnOnEngine() = 0;
};

class MotorCycle1 : hasMotor {
    // capabilities of both Bike1 and hasMotot
};

class Bicycle1 : Bike1 {
    // only capabilities of Bike1
};


int main() {
    Bicycle b;
    b.turnOnEngine();
// 
    MotorCycle b1;
    b1.turnOnEngine();
}