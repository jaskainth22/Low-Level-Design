#include<iostream>
#include<cmath>
#include<unordered_map>
#include<vector>

using namespace std;

// ---------------------------------------------------------------------------------------- 

// Classes

class Location {
    private:
    double x;
    double y;

    public:
    Location(double x, double y) : x(x), y(y) {} 

    double getXCoordinate() {
        return this->x;
    }

    double getYCoordinate() {
        return this->y;
    }

    double getDistance(Location* location2) {
        return sqrt( pow(this->x - location2->getXCoordinate(), 2) + pow(this->y - location2->getYCoordinate(), 2) );
    }
};

class Rider {
    private:
    string id;
    string name;

    public:
    Rider(string id, string name) : id(id), name(name) {}

    string getId() {
        return this->id;
    }

    string getName() {
        return this->name;
    }
};

enum TripStatus {
    IN_PROGRESS,
    FINISHED
};  

class Cab;

class Trip {
    private:
    Rider* rider;
    Cab* cab;
    TripStatus status;
    double price;
    Location* startLocation;
    Location* endLocation;

    public:
    Trip(Rider* rider, Cab* cab, double price, Location* start, Location* end) :
    rider(rider), cab(cab), price(price), startLocation(start), endLocation(end), status(TripStatus::IN_PROGRESS) {}

    void endTrip() {
        this->status = TripStatus::FINISHED;
    }

    Rider* getRider() {
        return this->rider;
    }

    Cab* getCab() {
        return this->cab;
    }

    double getTripPrice() {
        return this->price;
    }

    Location* getTripStartLocation() {
        return this->startLocation;
    }

    Location* getTripEndLocation() {
        return this->endLocation;
    }

};

class Cab {
    private:
    string id;
    string name;
    bool isAvailable;
    Location* currentLocation;
    Trip* currentTrip;

    public:

    Cab(string id, string name) : id(id), name(name), isAvailable(true), currentLocation(nullptr), currentTrip(nullptr) {}

    string getId() {
        return this->id;
    }

    string getName() {
        return this->name;
    }

    bool isCabAvailable() {
        return this->isAvailable;
    }

    void setAvailability(bool value) {
        this->isAvailable = value;
    } 

    Location* getLocation() {
        return this->currentLocation;
    }

    void setLocation(Location* location) {
        this->currentLocation = location;
    }

    Trip* getTrip() {
        return this->currentTrip;
    }

    void setTrip(Trip* trip) {
        this->currentTrip = trip;
    }
};

// ---------------------------------------------------------------------------------------- 

// Strategies

class PriceStartegy {
    public:
    
    virtual double findPrice(Location* start, Location* end) = 0;
};

class DefaultPriceStrategy : public PriceStartegy {
    public:

    #define ratePerKm 10;

    double findPrice (Location* start, Location* end) {
        double dist = start->getDistance(end);
        return dist*ratePerKm;
    }
};

class CabMatchingStrategy {
    public:

    virtual Cab* findCab(Rider* rider, vector<Cab*>listCabs, Location* start, Location* end)  = 0;
};

class DefaultCabMatchingStrategy : public CabMatchingStrategy {
    public:

    Cab* findCab(Rider* rider, vector<Cab*> listCabs, Location* start, Location* end) {
        if (listCabs.size() == 0) {
            cout<<"No cab available";
            return nullptr;
        }
        for (int i=0;i<listCabs.size();i++) {
            if (listCabs[i]->isCabAvailable()) {
                return listCabs[i];
            }
        }
        cout<<"No cab available";
        return nullptr;
    }
};  


// ---------------------------------------------------------------------------------------- 

// Managers

class CabsManager {
    public:
    
    unordered_map<string, Cab*> cabs;

    void createCab(Cab* newCab) {
        if (cabs.find(newCab->getId()) != cabs.end()) {
            cout<<"Cab already exists";
            return;
        }
        cabs[newCab->getId()] = newCab;
    }

    Cab* getCab(string id) {
        if (cabs.find(id) == cabs.end()) {
            cout<<"No cab exists with this ID";
            return nullptr;
        }
        return cabs[id];
    }

    void updateCabLocation(string id, Location* newLocation) {
        if (cabs.find(id) == cabs.end()) {
            cout<<"No cab exists with this ID";
            return;
        }
        cabs[id]->setLocation(newLocation);
    }

    void updateCabAvailability(string id, bool newValue) {
        if (cabs.find(id) == cabs.end()) {
            cout<<"No cab exists with this ID";
            return;
        }
        cabs[id]->setAvailability(newValue);
    }

    vector<Cab*> getCabList(Location* fromPoint, double distance) {
        vector<Cab*>res;
        for (auto itr=cabs.begin();itr!=cabs.end();itr++) {
            // cout<<itr->first<<"   ";
            if (itr->second->isCabAvailable()) {
                Location *l = itr->second->getLocation();
                cout<<l->getXCoordinate()<<" "<<l->getYCoordinate()<<endl;
                if (l->getDistance(fromPoint) <= distance ) {
                    res.push_back(itr->second);
                } 
            }
        }
        cout<<"Cabs List Size"<<res.size()<<endl;
        return res;
    }

};

class RidersManager {
    public:
    unordered_map<string, Rider*>riders;

    void createRider(Rider* newRider) {
        if (riders.find(newRider->getId()) != riders.end()) {
            cout<< "Rider alredy exists";
            return;
        }
        riders[newRider->getId()] = newRider;
    }

    Rider* getRider(string id) {
        if (riders.find(id) == riders.end()) {
            cout<<"No riders exists with this ID";
            return nullptr;
        }
        return riders[id];
    }
};


class TripsManager {
    private:
    CabsManager* cabsManager;
    RidersManager* ridersManager;
    CabMatchingStrategy* cabMatchingStrategy;
    PriceStartegy* priceStrategy;

    public:
    unordered_map<string, vector<Trip*>>trips; // rider - Trips
    double MAX_ALLOWED_TRIP_MATCH_DISTANCE = 10.0;

    TripsManager (CabsManager* c, RidersManager* r, CabMatchingStrategy* cs, PriceStartegy* ps) :
    cabsManager(c), ridersManager(r), cabMatchingStrategy(cs), priceStrategy(ps) {}

    void CreateTrip (Rider *rider, Location* start, Location* end) {
        vector<Cab*> closeByCabs = cabsManager->getCabList(start, MAX_ALLOWED_TRIP_MATCH_DISTANCE);

        Cab* cab1 = cabMatchingStrategy->findCab(rider, closeByCabs, start, end);

        cout<<"Name of cab driver selected for this trip"<<cab1->getName()<<endl;

        // Cab* cab1 = cabsManager->cabs["C1"];

        double price = priceStrategy->findPrice(start, end);

        // Dynamically allocate the Trip object
        Trip* trip = new Trip(rider, cab1, price, start, end);
        trips[rider->getId()].push_back(trip);
        cab1->setTrip(trip);
        cab1->setAvailability(false);
        cout << "trip created successfully";
    }

    vector<Trip*> getHistoryOfTripsForRider(string id) {
        return trips[id];
    }

    void endTripp(Cab* cab) {
        if (cab->getTrip() == nullptr) {
            cout<<"Cab is not in use";
        }
        cab->getTrip()->endTrip();
        cab->setTrip(nullptr);
    }

};


// ---------------------------------------------------------------------------------------- 

int main() {

    CabsManager* cabsManager = new CabsManager();
    RidersManager* ridersManager = new RidersManager();
    DefaultCabMatchingStrategy* defaultCabMatchingStrategy = new DefaultCabMatchingStrategy();
    DefaultPriceStrategy* defaultPriceStrategy = new DefaultPriceStrategy();
    TripsManager* tripsManager = new TripsManager(cabsManager, ridersManager, defaultCabMatchingStrategy, defaultPriceStrategy);

    Rider* rider1 = new Rider("R1", "John");
    Rider* rider2 = new Rider("R2", "Alice");

    Cab* cab1 = new Cab("C1", "Toyota");
    Cab* cab2 = new Cab("C2", "Honda");

    cabsManager->createCab(cab1);
    cabsManager->createCab(cab2);

    ridersManager->createRider(rider1);
    ridersManager->createRider(rider2);

    for (auto itr = cabsManager->cabs.begin();itr!= cabsManager->cabs.end();itr++) {
        cout<<itr->first<<" "<<itr->second->getName()<<endl;
    }

    Location* startLocation1 = new Location(0, 0);
    Location* endLocation1 = new Location(5, 5);

    Location* startLocation2 = new Location(3, 3);
    Location* endLocation2 = new Location(6, 6);

    cab1->setLocation(endLocation2);
    cab2->setLocation(startLocation1);

    tripsManager->CreateTrip(rider1, startLocation1, endLocation1);
    tripsManager->CreateTrip(rider2, startLocation2, endLocation2);


    vector<Trip*> tripsForRider1 = tripsManager->getHistoryOfTripsForRider("R1");
    cout << "Trips for Rider1:" << endl;
    for (Trip* trip : tripsForRider1) {
        cout << "Trip Price: " << trip->getTripPrice() << endl;
    }

    Cab* cabForRider1 = tripsForRider1[0]->getCab();
    tripsManager->endTripp(cabForRider1);

}