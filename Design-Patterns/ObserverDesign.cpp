#include<iostream>

using namespace std;

class IObserver {
    public:
    virtual void update() = 0;
};

class IObservable {
    public:
    virtual void addObserver(IObserver* o) = 0;
    virtual void deleteObserver(IObserver* o) = 0;
    virtual void notifyObserver() = 0;

    virtual void stateChange() = 0;
};

class ConcreteObservable : public IObservable {
    private:
    unordered_map<IObserver*, bool>mp;

    public:
    void addObserver(IObserver *o) {
        mp[o] = true;
    }

    void deleteObserver(IObserver *o) {
        mp.erase(o);
    }

    void notifyObserver() {
        for (auto itr=mp.begin();itr!=mp.end();itr++) {
            itr->first->update();
        }
    }

    void stateChange() {
        cout<<"My state is changed!!!!"<<endl;
    }
};

class ConcreteObserver : public IObserver {
    private:
    IObservable* ob;
    public:
    ConcreteObserver(IObservable *o) : ob(o) {
    }

    void update() {
        ob->stateChange();
    }
};

int main() {
    ConcreteObservable publisher;
    ConcreteObserver subscriber1(&publisher);
    ConcreteObserver subscriber2(&publisher);

    publisher.addObserver(&subscriber1);
    publisher.addObserver(&subscriber2);

    publisher.notifyObserver();

    publisher.deleteObserver(&subscriber1);

    cout<<"One subscriber Deleted"<<endl;

    publisher.notifyObserver();

}