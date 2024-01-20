/** My own code*/
#include<iostream>

using namespace std;

enum Vehicle_Type {
    Compact, Regular, Large
};

class Reservations {
    private:
    Garage* garage;
    Spots* spot;
    int startTime;
    int endTime;
    bool paid;
    int reservation_id;

    public:
    Reservations (Garage* g, Spots* s, int start, int end, bool paid) : garage(g), spot(s), startTime(start), endTime(end), paid(paid) {};

    pair<int,int> reserve(Garage* garage, int startTime, int endTime) {

    }

    bool payment (int reservation_id) {

    }

    bool cancel (int resevation_id) {

    }

};

class Garage {
    private:
    int zipcode;
    int rate_compact;
    int rate_regular;
    int rate_large;

    public:
    Garage (int zip, int rate_c, int rate_r, int rate_l) : zipcode(zip), rate_compact(rate_c), rate_regular(rate_r), rate_large(rate_l) {};
};

class Spots {
    private:
    Garage* garage;
    Vehicle_Type vehicle;
    bool status;

    public:
    Spots (Garage *garage, Vehicle_Type vehicle, bool status) : garage(garage), vehicle(vehicle),status(status) {};

    int freeSpots (Garage *garage, Vehicle_Type vehicle, int time) {

    }

    bool allocateSpot(Garage* garage, Vehicle_Type, int time) {

    }
};

int main() {

}