#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class Item {
    private:
    string name;
    int price;

    public:
    Item(string name, int price) : name(name), price(price) {}

    int getPrice() {
        return this->price;
    } 

    string getName() {
        return this->name;
    }
};

class ItemShelf {
    private:
    Item i;
    int code;
    int quantity;

    public:
    ItemShelf(Item i, int code, int quantity) : i(i), code(code), quantity(quantity) {

    }

    bool isItemSoldOut(int code) {
        if (this->quantity <= 0) {
            cout<<"Item sold out"<<endl;
            return true;
        }
        return false;
    }

    Item getItemAtShelf() {
        return this->i;
    }

    int getItemShelfCode() {
        return this->code;
    }

    void changeQuantity() {
        this->quantity--;
    }

    int getQuantity() {
        return this->quantity;
    }
};

class VendingMachine;

class State {
    private:
    VendingMachine* vm;
    string name;

    public:
    virtual void pressInsertButton() = 0;

    virtual void insertCoins(int coin) = 0;
    
    virtual void selectProductButton() = 0;

    virtual void clickDispenseButton() = 0;

    virtual void dispenseProduct() = 0;

    virtual void chooseProduct() = 0;

    virtual void cancelRefund() = 0;

    virtual void returnChange(int amt) = 0; 

    void setVendingMachine(VendingMachine* v) {
        this->vm = v;
    }

    VendingMachine* getVendingMachine() {
        return this->vm;
    }

    string getName() {
        return this->name;
    }

    void setName(string n) {
        this->name = n;
    }
};


class VendingMachine {
    private:
    unordered_map<int, ItemShelf*> Inventory;
    // vector<ItemShelf*> Inventory;
    State* currState;
    int coinsInserted;
    ItemShelf* currProductChosen;

    public:

    VendingMachine(unordered_map<int, ItemShelf*> inv, State* curr) : Inventory(inv), currState(curr), coinsInserted(0), currProductChosen(nullptr) {}

    void ChangeState(State* newState) {
        State* curr = this->currState;
        delete curr;
        cout<<newState->getName()<<"-"<<this->currState->getName()<<"--";
        this->currState = newState;
        cout<<this->currState->getName()<<endl;
    }

    State* getState() {
        return this->currState;
    }

    void setCoinsInVM(int coin) {
        
        this->coinsInserted = coin;
    }

    int getCoinsInVM() {
        return this->coinsInserted;
    }

    unordered_map<int, ItemShelf*> getInventory() {
        return this->Inventory;
    }

    void setCurrProduct(ItemShelf* i) {
        this->currProductChosen = i;
    }

    ItemShelf* getCurrProduct() {
        return this->currProductChosen;
    }

    void printInventory() {
        for (auto itr=Inventory.begin();itr!=Inventory.end();itr++) {
            ItemShelf* is = itr->second;
            cout<<is->getItemShelfCode()<<" "<<is->getItemAtShelf().getName()<<" "<<is->getItemAtShelf().getPrice()<<" "<<is->getQuantity()<<endl;
        }
    }
};

class Idle : public State {
    void pressInsertButton() override;
    void insertCoins(int coin) {}
    void selectProductButton() {}
    void clickDispenseButton() {}
    void dispenseProduct() {}
    void chooseProduct() {}
    void cancelRefund() {}  
    void returnChange(int amt) {}
};

class HasMoney : public State {
    void pressInsertButton() {}
    void insertCoins(int coin) override;
    void selectProductButton() override;
    void clickDispenseButton() {}
    void dispenseProduct() {}
    void chooseProduct() {}
    void cancelRefund() {} 
    void returnChange(int amt) {}
};

class Dispense : public State {
    void pressInsertButton() {}
    void insertCoins(int coin) {}
    void selectProductButton() {}
    void clickDispenseButton() {}
    void dispenseProduct() override;
    void chooseProduct() {}
    void cancelRefund() {} 
    void returnChange(int amt) {}
};

class SelectionState : public State {
    void pressInsertButton() {}
    void insertCoins(int coin) {}
    void selectProductButton() {}
    void clickDispenseButton() override;
    void dispenseProduct() {}
    void chooseProduct() override;
    void cancelRefund() override;
    void returnChange(int amt) override;
};

void Idle :: pressInsertButton() {
    VendingMachine* vm = this->getVendingMachine();
    HasMoney* hm = new HasMoney;
    hm->setName("HasMoney");
    hm->setVendingMachine(vm);
    vm->ChangeState(hm);
    cout<<vm->getState()->getName()<<endl;
    cout<<"Successfully changed state to HasMoney"<<endl;
}

void Dispense :: dispenseProduct() {
    VendingMachine* vm = this->getVendingMachine();
    unordered_map<int, ItemShelf*>mp = vm->getInventory();
    mp[vm->getCurrProduct()->getItemShelfCode()]->changeQuantity();
    cout<<"Succesfully dispensed product, please collect, item:"<<vm->getCurrProduct()->getItemAtShelf().getName()<<endl;
    vm->setCurrProduct(nullptr);

    Idle* i = new Idle();
    i->setName("Idle");
    i->setVendingMachine(vm);
    vm->ChangeState(i);
    cout<<"Successfully changed state to Idle"<<endl;
}

void SelectionState :: returnChange(int amt) {
    VendingMachine* vm = this->getVendingMachine();
    vm->setCoinsInVM(0);
    cout<<"Please collect return amount: "<<amt<<endl;
}

void SelectionState :: clickDispenseButton() {
    VendingMachine* vm = this->getVendingMachine();
    Dispense* d = new Dispense();
    d->setName("Dispense");
    d->setVendingMachine(vm);
    vm->ChangeState(d);
    cout<<"Successfully changed state to Dispense"<<endl;
}

void SelectionState :: cancelRefund() {
    VendingMachine* vm = this->getVendingMachine();
    int x = vm->getCoinsInVM();
    if (x != 0) {
        this->returnChange(x);
    } else {
        cout<<"No coins inserted, Cancel succssfull"<<endl;
    }
    Idle* i = new Idle(); 
    i->setName("Idle");
    i->setVendingMachine(vm);
    vm->ChangeState(i);
    cout<<"Successfully changed state to Idle"<<endl;
}

void SelectionState :: chooseProduct() {
    int code;
    cout<<"Please enter code for the product"<<endl;
    cin>>code;
    VendingMachine* vm = this->getVendingMachine();
    unordered_map<int, ItemShelf*>mp = vm->getInventory();

    if (mp.find(code) == mp.end()) {
        cout<<"No product exists with this code, please enter a valid code."<<endl;
        this->cancelRefund();
        return;
    }
    
    // insufficient money
    if (vm->getCoinsInVM() < mp[code]->getItemAtShelf().getPrice()) {
        cout<<"Insufficient money, please enter the required amount of money and try again"<<endl;
        this->cancelRefund();
        return;
    }

    // check stock
    if (mp[code]->isItemSoldOut(code)) {
        this->cancelRefund();
        return;
    }

    vm->setCurrProduct(mp[code]);
    cout<<"Product chosen succesfully"<<endl;

    // check if we need to return change
    if (vm->getCoinsInVM() > mp[code]->getItemAtShelf().getPrice()) {
        this->returnChange(vm->getCoinsInVM() - mp[code]->getItemAtShelf().getPrice());
    }
}

void HasMoney :: insertCoins(int coin) {
    VendingMachine* vm = this->getVendingMachine();
    cout<<this->getVendingMachine()->getState()->getName()<<endl;
    vm->setCoinsInVM(coin);
    cout<<"Successfully added coins in vending machine, Coins added: "<<coin<<endl;
}

void HasMoney :: selectProductButton() {
    VendingMachine* vm = this->getVendingMachine();
    SelectionState* ss = new SelectionState();
    ss->setName("SelectionState");
    ss->setVendingMachine(vm);
    vm->ChangeState(ss);
    cout<<"Successfully changed state to Selection State"<<endl;
}

int main() {
    Item Pepsi("Pepsi", 40);
    Item Coke("Coke", 50);
    Item Lays("Lays", 20);
    Item Mars("Mars", 60);

    ItemShelf PepsiShelf(Pepsi, 101, 5);
    ItemShelf CokeShelf(Coke, 201, 3);
    ItemShelf LaysShelf(Lays, 202, 2);
    ItemShelf MarsShelf(Mars, 102, 1);

    unordered_map<int, ItemShelf*>Inventory;
    Inventory[101] = &PepsiShelf;
    Inventory[201] = &CokeShelf;
    Inventory[202] = &LaysShelf;
    Inventory[102] = &MarsShelf;

    Idle* i = new Idle();
    i->setName("Idle");

    VendingMachine vm(Inventory, i);

    i->setVendingMachine(&vm);

    vm.printInventory();

    State* curr = vm.getState();
    curr->pressInsertButton();

    cout<<vm.getState()->getName()<<endl;

    vm.getState()->insertCoins(40);

    vm.getState()->selectProductButton();
    
    cout<<vm.getState()->getName()<<endl;

    vm.getState()->chooseProduct();

    vm.getState()->clickDispenseButton();

    cout<<vm.getState()->getName()<<endl;

    vm.getState()->dispenseProduct();

}