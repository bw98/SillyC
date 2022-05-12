#include<iostream>

using std::cout;
using std::cin;
using std::endl;

class Base {
    public:
        Base() {};
        virtual ~Base() {};
        virtual void print(int para=1) {
            cout << "Parent " << para << endl;
        }
        //virtual void print() {
        //    cout << "Parent " << "11111" << endl;
        //}
};

class Derived : public Base {
    public:
        Derived() {};
        ~Derived() {};
        void print(int para=2) override {
            cout << "Child " << para << endl;
        }
        //void print() override {
        //    cout << "Child " << "2222222" << endl;
        //}
};

int main() {
    Base *b = new Derived;
    b->print();
    //delete b;
    Derived *d = new Derived;
    d->print();
    //delete d;
    Base *c = d;
    c->print();
    //delete c;

    return 0;
}

