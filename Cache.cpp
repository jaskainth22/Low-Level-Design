#include<iostream>
#include<unordered_map>

using namespace std;

class DLL {
    public:
    int key;
    int value;
    DLL* prev;
    DLL* next;

    public:
    DLL(int key, int value) {
        this->key = key;
        this->value = value;
        this->prev = NULL;
        this->next = NULL;
    }
};

class Storage {
    public:
    virtual int size() {
        return 0;
    }

    virtual void add(int key, int value) {}

    virtual int get(int key) {
        return 0;
    }

    virtual void deleteKey(int key) {}
};

class MapDLLStorage : public Storage {
    private:
    unordered_map<int,DLL*>mp;
    DLL* head;
    DLL* tail;

    public:

    MapDLLStorage() {
        this->head = new DLL(-1,-1);
        this->tail = new DLL(-1,-1);
        this->head->next = this->tail;
        this->tail->prev = this->head;
    }

    DLL* getHead() {
        return this->head;
    }

    DLL* getTail() {
        return this->tail;
    }
    
    void add(int key, int value) {
        // always add in beginning
        if (mp.find(key) != mp.end()) {
            // key already exists
            this->deleteKey(key);
            mp.erase(key);
        }
        DLL* node = new DLL(key, value);
        mp[key] = node;
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    int get(int key) {
        if (mp.find(key) == mp.end()) {
            cout<<"Key do not exists"<<endl;
            return -1;
        }
        return mp[key]->value;
    }

    void deleteKey(int key) {
        if (mp.find(key) == mp.end()) {
            cout<<"Key do not exist"<<endl;
            return;
        }
        DLL* x = mp[key];
        DLL* xPrev = x->prev;
        DLL* xNext = x->next;
        xPrev->next = xNext;
        xNext->prev = xPrev;
        delete(x);
        cout<<"Successfully deleted key "<<key<<endl;
    }

    int size() {
        cout<<"Cache size is "<<mp.size()<<endl;
        return mp.size();
    }
};

class EvictionPolicy {
    public:
    virtual void update(int key) {}

    virtual void evict() {}
};

class LRU : public EvictionPolicy {
    private:
    MapDLLStorage* storage;
    public:
    LRU(MapDLLStorage* s) : storage(s) {};

    // put this key in front
    void update (int key) {
        int value = this->storage->get(key);
        this->storage->add(key, value);
        cout<<"Successfully updated value in cache"<<endl;
    }

    void evict() {
        DLL* temp = this->storage->getTail()->prev;
        temp->prev->next = this->storage->getTail(); 
        this->storage->getTail()->prev = temp->prev;
        this->storage->deleteKey(temp->key);
    }

};

class Cache {
    private:
    int capacity;
    Storage* storage;
    EvictionPolicy* ePolicy;

    public:
    Cache(int capacity, Storage* storage, EvictionPolicy* ePolicy) : capacity(capacity), storage(storage), ePolicy(ePolicy) {}

    void setCapacity(int capacity) {
        this->capacity = capacity;
    }

    int getCapacity() {
        return this->capacity;
    }

    int getStorageCurrentCapacity() {
        return this->storage->size();
    }

    void Put (int key, int value) {
        if (getStorageCurrentCapacity() == getCapacity()) {
            cout<<"Cache Capacity is full, evict from cache first"<<endl;
            this->ePolicy->evict();
        }
        this->storage->add(key,value);
        cout<<"Successfully added value in cache"<<endl;
    }

    int Get (int key) {
        this->ePolicy->update(key);
        return this->storage->get(key);
    }

    void Remove(int key) {
        this->storage->deleteKey(key);
    }
};

int main() {
    MapDLLStorage* newStorage = new MapDLLStorage();
    LRU* lruEviction = new LRU(newStorage);
    Cache* c1 = new Cache(2,newStorage,lruEviction);
    c1->Put(1,10);
    c1->Put(2,20);
    c1->Get(2);
    c1->Get(1);
    c1->Put(3,30);
}