#include<iostream>

using namespace std;

//  Product
class Animal {
    public:
    virtual void speak() = 0;
};

//concrete product
class Dog : public Animal {
    public:
    void speak() {
        cout<<"Whoof"<<endl;
    }
};

//concrete product
class Cat : public Animal {
    public:
    void speak() {
        cout<<"Meaow"<<endl;
    }
};

class AnimalFactory {
    public:
    virtual Animal* createAnimal() = 0;
};

class DogFactory : public AnimalFactory {
    public:
    Animal* createAnimal() {
        return new Dog();
    }
};

class CatFactory : public AnimalFactory {
    public:
    Animal* createAnimal() {
        return new Cat();
    }
};


int main() {
    DogFactory df;
    CatFactory cf;
    Animal* d1 = df.createAnimal();
    Animal* c1 = cf.createAnimal();
    d1->speak();
    c1->speak();

    delete d1;
    delete c1;
}