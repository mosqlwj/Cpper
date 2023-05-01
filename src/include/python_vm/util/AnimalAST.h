#include <iostream>

using namespace std;

class Dog;
class Cat;
class Visitor {
public:
    // void visit()
    virtual void visit(Dog* dog);
    virtual void visit(Cat* cat);
};

class Animal {
public:
    virtual void accept(Visitor* v) {
        cout << "emm.." << endl;
    }
};

class Dog : public Animal {
public:
    virtual void accept(Visitor* v) {
        v->visit(this);
    }
};

class Cat : public Animal {
public:
    virtual void accept(Visitor* v) {
        v->visit(this);
    }
};

class Speaker : public Visitor {

public:
    void visit(Dog* dog) override {
        cout << "wang.." << endl;
    }

    void visit(Cat* cat) override {
        cout << "miao.." << endl;
    }
};



class Feeding : public Visitor {

public:
   void visit(Dog* dog) override {
        cout << "bone.." << endl;
    }

    void visit(Cat* cat) override {
        cout << "fish.." << endl;
    }
};
