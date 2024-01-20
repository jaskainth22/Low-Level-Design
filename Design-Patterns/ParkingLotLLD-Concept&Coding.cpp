#include<iostream>
#include<vector>

using namespace std;

enum Vehicle_type {
    Empty, Two_Wheeler, Four_Wheeler
};

class Vehicle {
    public:
    int vehicleNo;
    Vehicle_type vehicleType;

    Vehicle(int vNo, Vehicle_type v) : vehicleNo(vNo), vehicleType(v) {};
};

class ParkingSpotInterface {
    public:
    int id;
    bool isEmpty;
    Vehicle vehicle;
    int price;

    ParkingSpotInterface(int id, bool empty, Vehicle vehicle, int price) : id (id), isEmpty(empty), vehicle(vehicle), price(price) {};

    void ParkVehicle(Vehicle_type vehicle) {
        isEmpty = false;
        vehicle = vehicle;
    }

    void RemoveVehicle(Vehicle_type vehicle) {
        isEmpty = true;
        vehicle = Empty;
    }
    
    virtual int priceSpot() = 0; 
};

class TwoWheelerParking : public ParkingSpotInterface {
    public:
    TwoWheelerParking(int id, bool empty, Vehicle vehicle, int price) : ParkingSpotInterface(id,empty,vehicle,price) {};
    
    int priceSpot() {
        return 10;
    }
};

class FourWheelerParking : public ParkingSpotInterface {
    public:
    FourWheelerParking(int id, bool empty, Vehicle vehicle, int price) : ParkingSpotInterface(id,empty,vehicle,price) {};

    int priceSpot() {
        return 20;
    }
};

class ParkingSpotManager {
    public:
    vector<ParkingSpotInterface*> listSpots;
    ParkingStrategy* parkingStrategy;

    ParkingSpotManager(vector<ParkingSpotInterface*>&listSpots, ParkingStrategy* strategy) : listSpots(listSpots), parkingStrategy(strategy) {};

    bool findParkingSpace() {
        parkingStrategy->findSpace();
    }

    bool addParkingSpace() {

    }

    bool removeParkingSpace() {

    }

    bool parkvehicle() {

    }

    bool removeVehicle() {

    }
};

class TwoWheelerParkingSpotManager : public ParkingSpotManager {
    public:
    TwoWheelerParkingSpotManager();
    TwoWheelerParkingSpotManager(vector<ParkingSpotInterface*>&listSpots, ParkingStrategy* parkingStrategy) : ParkingSpotManager(listSpots, parkingStrategy) {};
};

class FourWheelerParkingSpotManager : public ParkingSpotManager {
    public:
    FourWheelerParkingSpotManager();
    FourWheelerParkingSpotManager(vector<ParkingSpotInterface*>&listSpots, ParkingStrategy* parkingStrategy) : ParkingSpotManager(listSpots, parkingStrategy) {};
};

class ParkingStrategy {
    public:
    virtual void findSpace() = 0;
};

class NearToEntrance : public ParkingStrategy {
    public:
    void findSpace() {

    }
};

class NearToEnd : public ParkingStrategy {
    public:
    void findSpace() {

    }
};

class defaultParking : public ParkingStrategy {
    public:
    void findSpace() {

    }
};

class PricingStrategy {
    public:
    virtual int price() = 0;
};

class HourlyPricing : public PricingStrategy {
    public:
    int price() {

    }
};

class MinutePricing : public PricingStrategy {
    public:
    int price() {

    }
};

class CostComputation {
    public:
    PricingStrategy* ps;
    CostComputation(PricingStrategy* ps) : ps(ps) {};

    int price() {
        return ps->price();
    }
};

class TwoWheelerCost : public CostComputation {
    public:
    TwoWheelerCost(HourlyPricing* hp) : CostComputation(hp) {};
};

class FourWheelerCost : public CostComputation {
    public:
    FourWheelerCost(MinutePricing* mp) : CostComputation(mp) {}; 
};


class Ticket {
    public:
    long entryTime;
    Vehicle* vehicle;
    ParkingSpotInterface *spot;

    Ticket(long entry, Vehicle* v, ParkingSpotInterface* sp) : entryTime(entry), vehicle(v), spot(sp) {};
};

class EntraceGate {
    public:
    Vehicle* vehicle;
    ParkingSpotManager* psm;
    EntraceGate(Vehicle* v) : vehicle(v) {};

    void findSpace(Vehicle vehicle) {
        psm->findParkingSpace();
    }

    void BookSpot(Vehicle vehicle) {
        psm->parkvehicle();
    }
    
    void generateTicket() {

    }
};

class ExitGate {
    public:
    Ticket* tk;
    CostComputation* cost;
    ParkingSpotManager* psm;

    ExitGate(Ticket* ticket) : tk(ticket) {
        if (ticket->vehicle->vehicleType == Two_Wheeler) {
            HourlyPricing* hp; // add the logic in Hourly and Minute pricing
            cost = new TwoWheelerCost(hp);
            psm = new TwoWheelerParkingSpotManager();
        }
        else {
            MinutePricing* mp;
            cost = new FourWheelerCost(mp);
            psm = new FourWheelerParkingSpotManager();
        }
    };

    int PriceCal() {
        return cost->price();
    }

    void removeVehilce() {
        psm->removeVehicle();
    }
};

int main() {
    vector<ParkingSpotInterface*>TwoWheelerSpots;
    vector<ParkingSpotInterface*>FourWheelerSpots;
    for (int i=0;i<400;i++) {
        Vehicle v(-1,Two_Wheeler);
        TwoWheelerSpots.push_back(new TwoWheelerParking(i, true, v, 10));
    }
    for (int i=400;i<=999;i++) {
        Vehicle v(-1, Four_Wheeler);
        FourWheelerSpots.push_back(new FourWheelerParking(i, true, v, 20));
    }

    ParkingStrategy* near2Enter = new NearToEntrance();
    TwoWheelerParkingSpotManager twoWheelerManager(TwoWheelerSpots, near2Enter);
    ParkingStrategy* near2End = new NearToEnd();
    FourWheelerParkingSpotManager fourWheelerManager(FourWheelerSpots, near2End);

/** Rest of the code*/


    // Delete all the objects used, free the memory
    for (auto spot : TwoWheelerSpots) {
        delete spot;
    }

    for (auto spot : FourWheelerSpots) {
        delete spot;
    }

    delete near2Enter;
    delete near2End;
}