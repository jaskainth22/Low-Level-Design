#include<iostream>

using namespace std;

class Button {
    public:
    virtual void fun() = 0;
};

class Panel {
    public:
    virtual void fun() = 0;
};

class winButton : public Button {
    public:
    void fun() {
        cout<<"This is a windows button"<<endl;
    }
};

class macButton : public Button {
    public:
    void fun() {
        cout<<"This is a Mac button"<<endl;
    }
};

class winPanel : public Panel {
    public:
    void fun() {
        cout<<"This is a windows panel"<<endl;
    }
};

class macPanel : public Panel {
    public:
    void fun() {
        cout<<"This is a mac panel"<<endl;
    }
};


class Factory {
    public:
    virtual Button* createButton() = 0;
    virtual Panel* createPanel() = 0;
};

class winFactory : public Factory {
    public:
    Button* createButton() {
        return new winButton();
    }

    Panel* createPanel() {
        return new winPanel();
    } 
};

class macFactory : public Factory {
    public:
    Button* createButton() {
        return new macButton();
    }

    Panel* createPanel() {
        return new macPanel();
    }
};

int main() {
    string osType;
    cout<<"Give the OS type"<<endl;
    osType = "Mac";
    Factory* newFactory;
    if (osType == "Windows") {
        newFactory = new winFactory();
    } else {
        newFactory = new macFactory();
    }
    Button* b = newFactory->createButton();
    Panel* p = newFactory->createPanel();
    b->fun();
    p->fun();
}