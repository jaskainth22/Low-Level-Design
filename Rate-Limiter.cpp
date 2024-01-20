#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

class RateLimiter {
    private:
    int maxNoOfRequestsPerMin;
    int remainingRequests;

    public:
    RateLimiter(int cnt) : maxNoOfRequestsPerMin(cnt), remainingRequests(cnt) {};

    bool isRequestAllowed() {
        if (remainingRequests > 0) {
            remainingRequests--;
            return true;
        }
        return false;
    }

    void addRequest() {
        remainingRequests = maxNoOfRequestsPerMin;
    }
};

void API () {
    cout<<"API called"<<endl;
}

int main() {
    RateLimiter rl(30);

    for (int i=1;i<=100;i++) {

        // add 1 sec delay
        this_thread::sleep_for(chrono::seconds(1));

        // add more requests after 1min
        if (i%60 == 0) {    
            rl.addRequest();
        }

        if (rl.isRequestAllowed()) {
            API();
        } else {
            cout<<"API limit reached"<<endl;
        }
    }
    
}