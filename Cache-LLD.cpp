#include<iostream>
#include<unordered_map>
#include<list>

using namespace std;

/** This approach is not correct at all. Just see the schema structure for reference
 * For Correct approach check LRU cache question in leetcode
*/
/***
 * We are following single responsibilty model
 * /
/** Everything related to eviction policy is in this class*/
class EvictionPolicy {
    unordered_map<string, DLL*> mapper;

    public:
    DLL* head;
    DLL* tail;
    EvictionPolicy() {
        head = new DLL();
        tail = new DLL();
        head->next = tail;
        tail->prev = head;
    }

    void keyAccessed(string key) {
        detachNode(mapper[key]);
        addNodeAtEnd(mapper[key]);
    }

    void evictKey() {
        head = head->next;
    }

    void detachNode(DLL *node) {
        DLL* prevN = node->prev;
        DLL* nextN = node->next;
        prevN->next = nextN;
        nextN->prev = prevN;
    }

    void addNodeAtEnd(DLL *node) {
        DLL* lastN = this->tail->prev;
        lastN->next = node;
        node->prev = lastN;
        node->next = tail;
        tail->prev = node;
    }
};


class DLL {
    public:
    string key;
    DLL* prev;
    DLL* next;

    public:
    DLL() {
    }
};


/** Everything related to storage is in this class*/
class Storage {
    int capacity;

    public:
    unordered_map<string,string>storage;

    Storage(int c) : capacity(c) {}

    void add(string key, string value) {
        if (storage.size() == capacity) {
            cout<<"Capacity is full"<<endl;
            cout<<"Removing Least recently used key"<<endl;
        } else {
            storage[key] = value;
        }
    }

    void remove(string key) {
        if (storage.find(key) == storage.end()) {
            return;
        }
        storage.erase(key);
    }

    string get(string key) {
        if (storage.find(key) == storage.end())
            return;
        return storage[key];
    }

};

class cache {
    EvictionPolicy evictionPolicy;
    Storage storage;

    public:
    cache(EvictionPolicy ep, Storage s) : evictionPolicy(ep), storage(s) {};

    void put(string key, string value) {
        this->storage.add(key,value);
        this->evictionPolicy.keyAccessed(key);
    }

    string get(string key) {
        string value = this->storage.get(key);
        this->evictionPolicy.keyAccessed(key);
        return value; 
    }
};

int main() {

}