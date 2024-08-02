#include<iostream>
#include<vector>
using namespace std;

class PageClicker {
    private:
    int n;
    vector<int>pages;

    public:
    void init(int totalPage) {
        this->n = totalPage;
        pages.resize(totalPage+1, 0);
    }

    void incrementVisitCount(int pageIndex) {
        this->pages[pageIndex]++;
    }

    int getVisitCount(int pageIndex) {
        return this->pages[pageIndex];
    }
};

int main() {
    PageClicker p;
    p.init(2);

    p.incrementVisitCount(0);
    p.incrementVisitCount(1);
    p.incrementVisitCount(1);
    p.incrementVisitCount(1);
    p.incrementVisitCount(0);

    cout<<p.getVisitCount(0)<<endl;
    cout<<p.getVisitCount(1)<<endl;
}