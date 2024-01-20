#include<iostream>
#include<vector>

using namespace std;

class cacheNode {
    public:
    string key;
    string value;
    cacheNode* prev;
    cacheNode* next;

    cacheNode(string k, string v) : key(k), value(v) {} 
};

class cacheLevel {
    public:
    int readTime;
    int writeTime;
    int capacity;
    unordered_map<string, cacheNode*>mp;
    cacheNode* head = new cacheNode("","");
    cacheNode* tail = new cacheNode("","");

    cacheLevel(int rT, int wT, int cap) : readTime(rT), writeTime(wT), capacity(cap) {};
};

class cache {
    public:
    int size;
    vector<cacheLevel*> cachelvl;

    cache(int s) : size(s) {}
};

void addNode(cacheLevel* cl, cacheNode* cn) {
    cacheNode* temp = cl->head->next;
    cn->next = temp;
    cn->prev = cl->head;
    cl->head = cn;
    temp->prev = cn;
}

int writeCache(string key, string value, cache* c) {
    int n = c->size;
    vector<cacheLevel*> listCache = c->cachelvl;
    int time = 0;
    for (int i=0;i<n;i++) {
        cacheLevel* cl = listCache[i];
        unordered_map<string, cacheNode*> mp = cl->mp;
        if (mp.find(key) == mp.end()) {
            cacheNode* cn = new cacheNode(key,value);
            mp[key] = cn;
            addNode(cl,cn);
            time += cl->writeTime;
        }
        time += cl->readTime;
    }
    return time;
}

string readcache(string key, cache* c) {
    int n = c->size;
    vector<cacheLevel*> listCache = c->cachelvl;
    int time = 0;
    string res;
    int i;
    for (i=0;i<n;i++) {
        cacheLevel* cl = listCache[i];
        unordered_map<string, cacheNode*> mp = cl->mp;
        if (mp.find(key) != mp.end()) {
            res = mp[key]->value;
            break;
        }
    }
    return res;
}

int main() {
    int sizeOfCache = 5;
    cache* c = new cache(3);
    cacheLevel* cl1 = new cacheLevel(2,2,3);
    cacheLevel* cl2 = new cacheLevel(1,2,2);
    cacheLevel* cl3 = new cacheLevel(2,1,4);
    vector<cacheLevel*> listCacheLevel;
    listCacheLevel.push_back(cl1);
    listCacheLevel.push_back(cl2);
    listCacheLevel.push_back(cl3);
    c->cachelvl = listCacheLevel;
}