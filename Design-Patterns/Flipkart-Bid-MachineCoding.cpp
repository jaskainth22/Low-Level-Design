#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

class Member;

class Event {
    private:
    int eventID;
    string eventName;
    string prizeName;
    // Here we can use a Map as well
    // As our system is write heavy, if we use a map, then each insert operation will be O(logn)
    // with unordered_map insert will be O(1)
    // Deciding winner is only one time operation
    unordered_map<int, vector<Member*>> bidList;

    public:
    Event(int id, string name, string prizeName) : eventID(id), eventName(name), prizeName(prizeName) {}

    int getEventID() {
        return this->eventID;
    }

    string getEventName() {
        return this->eventName;
    }

    string getPrizeName() {
        return this->prizeName;
    }

    void setBidForMember(vector<int>bids, Member* member) {
        for (int i=0;i<bids.size();i++) {
            bidList[bids[i]].push_back(member);
        }
    } 

    unordered_map<int, vector<Member*>> getBidList() {
        return this->bidList;
    }

    Member* getWinner() {
        int lowest = 2147483647;
        for (auto itr=bidList.begin();itr!=bidList.end();itr++) {
            lowest = min(lowest, itr->first);
        }
        return bidList[lowest][0];
    }
    
};

class Member {
    private:
    int memberID;
    int superCoins;
    string memberName;
    vector<Event*> pastEvents;
    Event* currEvent;
    bool isRegistered;
    vector<int> bidsForCurrEvent;

    public:
    Member(int id, int coins, string name) {
        this->memberID = id;
        this->superCoins = coins;
        vector<Event*>v;
        this->pastEvents = v;
        this->currEvent = nullptr;
        this->isRegistered = false;
        vector<int>x;
        this->bidsForCurrEvent = x;
        this->memberName = name;
    }

    void setSuperCoins(int coins) {
        this->superCoins = coins;
    }

    int getSuperCoins() {
        return this->superCoins;
    }

    string getName() {
        return this->memberName;
    }

    void setIsRegistered(bool value) {
        this->isRegistered = value;
    }

    bool getIsRegistered() {
        return this->isRegistered;
    }

    void setCurrEvent(Event* e) {
        this->currEvent = e;
    }

    Event* getCurrEvent() {
        return this->currEvent;
    }

    vector<Event*> getPastEvents() {
        return this->pastEvents;
    }

    void setPastEvents(Event* e) {
        this->pastEvents.push_back(e);
    }

    void setBidsForCurrEvent(vector<int> x) {
        this->bidsForCurrEvent = x;
    }

    vector<int> getBidsForCurrEvent() {
        return this->bidsForCurrEvent;
    }
};

class System {
    private:
    unordered_map<int, Member*>memberList;
    unordered_map<int, Event*>eventList;
    unordered_map<Event*, Member*>pastEventWinners;

    public:

    System()
    {
        unordered_map<int, Member*>m;
        unordered_map<int, Event*>e;
        unordered_map<Event*, Member*>em;
        this->memberList = m;
        this->eventList = e;
        this->pastEventWinners = em;
    }

    void ADD_MEMBER(int id, int coins, string name) {
        Member* m = new Member(id, coins, name);
        memberList[id] = m;
        cout<<m->getName()<<endl;
        cout<<memberList[id]->getName()<<endl;
    }

    void ADD_EVENT(int id, string eventName, string prizeName) {
        Event* e = new Event(id, eventName, prizeName);
        eventList[id] = e;
        cout<<e->getEventName()<<" "<<e->getPrizeName()<<endl;
        cout<<eventList[id]->getEventName()<<" "<<eventList[id]->getPrizeName()<<endl;
    }

    void REGISTER_MEMBER(int memberID, int eventID) {
        Member* currMember = memberList[memberID];
        Event* currEvent = eventList[eventID];
        
        currMember->setIsRegistered(true);
        currMember->setCurrEvent(currEvent);

        cout<<currMember->getName()<<" ";
        if (currMember->getIsRegistered())
            cout<<"registered"<<endl;
        else
            cout<<"not registered"<<endl;
    }

    void SUBMIT_BID(int memberID, int eventID, vector<int> bids) {
        Member* currMember = memberList[memberID];
        Event* currEvent = eventList[eventID];

        if (!currMember->getIsRegistered()) {
            cout<<"Cannot place bid as member is not registered. Member: "<< currMember->getName()<<endl;
            return;
        }

        int getCoins = currMember->getSuperCoins();
        
        int max_bid = 0;
        for (int i=0;i<bids.size();i++) {
            max_bid = max(max_bid, bids[i]);
        }

        if (getCoins < max_bid) {
            cout<<"Cannot place bid as we do not have that much coins"<<endl;
            return;
        }

        currEvent->setBidForMember(bids, currMember);
        currMember->setSuperCoins(getCoins - max_bid);
    }

    void unRegisterMembers() {
        for (auto itr=memberList.begin();itr!=memberList.end();itr++) {
            itr->second->setIsRegistered(false);
        }
    }

    void DECLARE_WINNER(int eventID) {
        Event* currEvent = eventList[eventID];

        Member* winnerMember = currEvent->getWinner();

        cout<<winnerMember->getName()<<endl;


        // Add this event in history
        pastEventWinners[currEvent] = winnerMember;

        // Unregister all the members
        unRegisterMembers();
    }

    void LIST_WINNERS() {
        for (auto itr=pastEventWinners.begin();itr!=pastEventWinners.end();itr++) {
            Event* e = itr->first;
            Member* m = itr->second;
            cout<<e->getEventName()<<" "<<m->getName()<<endl;
        }
    }
};

int main() {
    System s;

    s.ADD_MEMBER(1, 10000, "Akshay");
    s.ADD_MEMBER(2, 5000, "Chris");
    s.ADD_MEMBER(3, 3000, "David");

    s.ADD_EVENT(1, "BBD", "IPHONE 14");

    s.REGISTER_MEMBER(1, 1);
    s.REGISTER_MEMBER(2, 1);
    s.REGISTER_MEMBER(3, 1);

    vector<int>bid1 {100, 200, 300, 400};
    vector<int>bid2 {100, 200, 300, 400, 50};
    vector<int>bid3 {10, 200, 300, 400, 50};

    s.SUBMIT_BID(1, 1, bid1);
    s.SUBMIT_BID(2, 1, bid2);
    s.SUBMIT_BID(3, 1, bid3);
    s.SUBMIT_BID(1, 1, bid3);

    s.DECLARE_WINNER(1);

    s.LIST_WINNERS();

    cout<<"====================================="<<endl;

    s.ADD_EVENT(2, "Diwali Sale", "Macbook Pro");

    s.REGISTER_MEMBER(2, 2);
    s.REGISTER_MEMBER(3, 2);

    s.SUBMIT_BID(1, 2, bid2);
    s.SUBMIT_BID(2, 2, bid3);
    s.SUBMIT_BID(3, 2, bid1);

    s.DECLARE_WINNER(2);

    s.LIST_WINNERS();

}