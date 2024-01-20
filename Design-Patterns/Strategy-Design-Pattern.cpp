#include<iostream>

using namespace std;

// Without strategy design pattern

class Vehicle {
    public:
    void drive() {
        cout<<"Normal drive capability"<<endl;
    }
    void display() {
        cout<<"Display"<<endl;
    }
};


// For sports vehicle and offRoad vehicle, we need advanced drive capability, 
// This leads to code duplication in both classes
class sportsVehicle : public Vehicle {
    public:
    void drive() {
        cout<<"Advanced capability"<<endl;
    }
};

class offRoadVehicle : public Vehicle {
    public:
    void drive() {
        cout<<"Advanced capability"<<endl;
    }
};

// Strategy design pattern helps in removing duplicate code through inheritance
// and run time polymorphism. We will create a abstarct class and override the necessary functions in child class.
// on run time, we will decide which function to execute


class vehicleInterface {
    public:
    virtual void drive() = 0;

    void display() {
        cout<<"display";
    }
};

class sportyVehicle : public vehicleInterface {
    public:

    void drive() override {
        cout<<"Sports functionality"<<endl;
    }
};

class suvVehicle : public vehicleInterface {
    public:

    void drive() override {
        cout<<"SUV functionality"<<endl;
    }
};

// here we are using context switching
class vehicleType {
    private:
    vehicleInterface* vi;

    public:

    void chooseVehicleType(vehicleInterface* veh)  {
        vi = veh;
    }

    void callFunction() {
        vi->drive();
    }
};

//another way to do this is via constructor injection
class vehicleType1 {
    private:
    vehicleInterface* vi;

    public:
    // constructor injection
    vehicleType1(vehicleInterface* vehObj) : vi(vehObj) {}

    void callFunction() {
        vi->drive();
    }
};



int main() {
    // vehicleType vTpye;

    // sportyVehicle sv;

    // vTpye.chooseVehicleType(&sv);
    // vTpye.callFunction();

    // suvVehicle suv;
    // vTpye.chooseVehicleType(&suv);
    // vTpye.callFunction(); 


    // using constructor injection1ß
    suvVehicle suv1;
    vehicleType1 vType11(&suv1);
    vType11.callFunction();

    sportyVehicle sv1;
    vehicleType1 vType1(&sv1);
    vType1.callFunction();
}