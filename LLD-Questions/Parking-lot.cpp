/*
7. Design a Parking Lot - Single Thread

Write code for low level design of a parking lot with multiple floors.
The parking lot has two kinds of parking spaces: type = 2, for 2 wheeler vehicles and type = 4, for 4 wheeler vehicles.

There are multiple floors in the parking lot. On each floor, vehicles are parked in parking spots arranged in rows and columns.
For simplicity, lets assume that each floor will have same number of rows and each row will have same number of columns.

You can solve this question in either Java or Python
Implement the below methods in Solution class:

init(Helper helper, int [][][] parking)
- helper has methods like, helper.print("") and helper.println("") which you can use for printing logs
- parking[i][j][k] : parking spot on i-th floor, j-th row and k-th column.
- each item in parking array is of the following type.
    4 : 4 wheeler parking spot,
    2 : 2 wheeler parking spot,
    0 : inactive spot, no vehicle can be parked here

park(int vehicleType, String vehicleNumber, String ticketId, int parkingStrategy)
returns spotId
- This function assigns an empty parking spot to vehicle and maps vehicleNumber and ticketId to the assigned spotId
- spotId is floor+"-"+row+"-"+column
e.g. parking[2][0][15] = parking spot at 2nd floor , 0th row and 15th column (0 based index),
its spotId will be: "2-0-15"
- parkingStrategy has two values, 0 and 1

parkingStrategy = 0
- Get the parking spot at lowest index i.e. lowest floor, row and column
e.g. park() is called with vehicleType 4 and we have free 4-wheeler spots at
parking[0][0][0], parking[0][0][1] and parking[1][0][2]
here we will return parking[0][0][0] because its index (floor, row, column) comes before the other two.

parkingStrategy = 1 :
- Get the floor with maximum number of free spots for the given vehicle type.
- If multiple floors have maximum free spots then choose the floor at lowest index from them.
e.g. park() is called with vehicleType 4 and floor[0] has 2 free 4 wheeler parking spots and
floor[1] and floor[3] both have 3 empty 4-wheeler parking spots.
here we will return the free 4-wheeler parking spot at lowest index from floor[1],
because apart from having highest number of free 4-wheeler spots it also comes before floor[3],
which also has 3 empty 4-wheeler parking spots.

removeVehicle(String spotId)
- Unparks or removes vehicle from parking spot.
- returns true if vehicle is removed
- returns false if vehicle not found or any other error


String searchVehicle(String query)
- searches the latest parking details of a vehicle parked in previous park() method calls.
- returns spotId e.g. 2-0-15 or empty string ""
- Query will be either vehicleNumber or ticketId.

int getFreeSpotsCount(int floor, int vehicleType)
- At any point of time get the number of free spots of vehicle type (2 or 4 wheeler).
- 0>= floor < parking.length (parking array from init() method).


Constraints:
- type = 2 for two-wheeler vehicle, type = 4 for 4 wheeler vehicle
- 1<=floors<=5, 1<=rows<=10,000, 1<=columns<=10,000, 1<=rows*columns<=10,000

Input Example
parking = [[
[4, 4, 2, 2],
[2, 4, 2, 0],
[0, 2, 2, 2],
[4, 4, 4, 0]]]
Above input has 1 floor.
It has 4 rows and 4 columns on floor 0.
Total 7 active 2-wheeler vehicles and
6 active 4-wheeler vehicles are there.

e.g park(2, "bh234", "tkt4534", 0)
will return spotId: "0-0-2"
i.e. parking spot from floor 0, row 0 and column 2 is assigned.

- search("bh234") or search("tkt4534")
at this point should return spotId = "0-0-2"
i.e. we can use vehicleNumber: "bh234" or ticketId: "tkt4534" to find the parking spot id where vehicle is parked.

- getFreeSpotsCount(0, 2)
will return 6.

- removeVehicle("0-0-2")
should unpark the parked vehicle and

- getFreeSpotsCount(0, 2)
after unparking, getFreeSpotsCount will now return 7.


*/



#include<iostream>
#include<vector>
#include<unordered_map>
#include<memory>

using namespace std;

// Interface
class ParkingStrategy {
    public:
    virtual vector<int> strategy (int vehicleType, vector<vector<vector<int> > >& parking, unordered_map<int, pair<int,int> >& parkingSpotsAtEachFloor) = 0;
    // vector  -  {floor, row, col}
};

class ParkingStrategy0 : public ParkingStrategy {
    public:
    vector<int> strategy (int vehicleType, vector<vector<vector<int> > >& parking, unordered_map<int, pair<int,int> >& parkingSpotsAtEachFloor) {
        vector<int>res;
        for (int i=0;i<parking.size();i++) {
            for (int j=0;j<parking[i].size();j++) {
                for (int k=0;k<parking[j].size();k++) {
                    if (parking[i][j][k] == vehicleType) {
                        parking[i][j][k] = -1 * parking[i][j][k];
                        // res = {i, j, k};
                        res.push_back(i);res.push_back(j);res.push_back(k);
                        if (vehicleType == 2) {
                            parkingSpotsAtEachFloor[i].first--;
                        } else if (vehicleType == 4) {
                            parkingSpotsAtEachFloor[i].second--;
                        }
                        return res; 
                    }
                }
            }
        }
        return res;
    }
};

class ParkingStrategy1 : public ParkingStrategy {
    public:
    vector<int> strategy (int vehicleType, vector<vector<vector<int> > >& parking, unordered_map<int, pair<int,int> >& parkingSpotsAtEachFloor) {
        int floor = 0;
        int cnt = 0;
        vector<int>res;
        for (auto itr=parkingSpotsAtEachFloor.begin();itr!=parkingSpotsAtEachFloor.end();itr++) {
            if (vehicleType == 2) {
                if (cnt < itr->second.first) {
                    cnt = itr->second.first;
                    floor = itr->first;
                }
            } else if (vehicleType == 4) {
                if (cnt < itr->second.second) {
                    cnt = itr->second.second;
                    floor = itr->first;
                }
            }
        }
        for (int j=0;j<parking[floor].size();j++) {
            for (int k=0;k<parking[floor][j].size();k++) {
                if (parking[floor][j][k] == vehicleType) {
                    // res = {floor, j, k};
                    res.push_back(floor);res.push_back(j);res.push_back(k);
                    parking[floor][j][k] = -1 * parking[floor][j][k];

                    if (vehicleType == 2) {
                            parkingSpotsAtEachFloor[floor].first--;
                        } else if (vehicleType == 4) {
                            parkingSpotsAtEachFloor[floor].second--;
                        }

                    return res;
                }
            }
        }
        return res;
    }
};

class ParkingStrategyContext {
    unique_ptr<ParkingStrategy> ps;
    public:

    void setStrategy(unique_ptr<ParkingStrategy> strategy) {
        this->ps = move(strategy);
    }

    vector<int> executeStrategy(int vehicleType, vector<vector<vector<int> > >& parking, unordered_map<int, pair<int,int> >& parkingSpotsAtEachFloor) {
        return this->ps->strategy(vehicleType, parking, parkingSpotsAtEachFloor);
    }
};

class ParkingLot {
    int floor;
    unordered_map<int, pair<int,int> >parkingSpotsAtEachFloor;  // floor - {twoWheelerFreeSpots, fourWheelerFreeSpots}
    vector<vector<vector<int> > >parking;
    ParkingStrategyContext psc;
    unordered_map<string, string>mpCarString;
    unordered_map<string, string>mpTicketString;

    public:

    ParkingLot() {}

    void init(vector<vector<vector<int> > >& parking) {
        this->floor = parking.size();
        this->parking = parking;

        // Map available parking at each floor
        for (int i=0;i<parking.size();i++) {
            // i - floor
            for (int j=0;j<parking[i].size();j++) {
                for (int k=0;k<parking[i][j].size();k++) {
                    if (parkingSpotsAtEachFloor.find(i) == parkingSpotsAtEachFloor.end()) {
                        parkingSpotsAtEachFloor[i].first = 0;
                        parkingSpotsAtEachFloor[i].second = 0;
                    }
                    if (parking[i][j][k] == 2)
                        parkingSpotsAtEachFloor[i].first++;
                    else if(parking[i][j][k] == 4)
                        parkingSpotsAtEachFloor[i].second++;
                }
            }
        }
    }

    string park(int vehicleType, string vehicleNumber, string ticketId, int parkingStrategy) {
        if (parkingStrategy == 0) {
            psc.setStrategy(make_unique<ParkingStrategy0>());
            
        } else if (parkingStrategy == 1) {
            psc.setStrategy(make_unique<ParkingStrategy1>());
        }
        vector<int> res = psc.executeStrategy(vehicleType, parking, parkingSpotsAtEachFloor);
        string s = "";
        s += to_string(res[0]);
        s += "-";
        s += to_string(res[1]);
        s += "-";
        s += to_string(res[2]);

        mpCarString[vehicleNumber] = s;
        mpTicketString[ticketId] = s;
        return s;
    }

    void removeVehicle(string spotId) {
        int floor = spotId[0] - '0';
        int row = spotId[2] - '0';
        int col = spotId[4] - '0';
        parking[floor][row][col] = -1 * parking[floor][row][col];
        if (parking[floor][row][col] == 2) {
            parkingSpotsAtEachFloor[floor].first++;
        } else if (parking[floor][row][col] == 4) {
            parkingSpotsAtEachFloor[floor].second++;
        }
    }

    string searchVehicle(string query) {
        if (mpCarString.find(query) != mpCarString.end())
            return mpCarString[query];
        if (mpTicketString.find(query) != mpTicketString.end())
            return mpTicketString[query];
        return "";
    }

    int getFreeSpotsCount(int floor, int vehicleType) {
        if (vehicleType == 2)
            return parkingSpotsAtEachFloor[floor].first;
        return parkingSpotsAtEachFloor[floor].second;
    }
};

int main() {
    vector<vector<vector<int> > > parking(1, vector<vector<int> >(4, vector<int>(4)));

    // Manually set the values
    parking[0] = {
        {4, 4, 2, 2},
        {2, 4, 2, 0},
        {0, 2, 2, 2},
        {4, 4, 4, 0}
    };
    ParkingLot pl;
    pl.init(parking);
    cout<<pl.park(2, "bh234", "tkt4534", 0)<<endl;
    cout<<pl.searchVehicle("bh234")<<endl;
    cout<<pl.searchVehicle("tkt4534")<<endl;
    cout<<pl.getFreeSpotsCount(0, 2)<<endl;
    pl.removeVehicle("0-0-2");
    cout<<pl.getFreeSpotsCount(0, 2)<<endl;
}