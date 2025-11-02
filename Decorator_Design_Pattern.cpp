#include <bits/stdc++.h>
using namespace std;

// Base Interface
class Base
{
public:
    virtual void show() = 0;
};

// Concrete Base Class 1
class ConcreteBase1 : public Base
{
public:
    void show()
    {
        cout << "Concrete Class 1 Show Function Called" << endl;
    }
};

// Concrete Base Class 2
class ConcreteBase2 : public Base
{
public:
    void show()
    {
        cout << "Concrete Class 2 Show Function Called" << endl;
    }
};

// Decorator Interface
class Decorator : public Base
{
protected:
    Base *base;

public:
    Decorator(Base *b) : base(b) {}

    void baseShow()
    {
        base->show();
    }
};

// Concrete Decorator 1
class ConcreteDecorator1 : public Decorator
{
public:
    ConcreteDecorator1(Base *b) : Decorator(b) {}

    void show()
    {
        base->show();
        cout << "Concrete Decorator 1 Show Function Called" << endl;
    }
};

// Concrete Decorator 2
class ConcreteDecorator2 : public Decorator
{
public:
    ConcreteDecorator2(Base *b) : Decorator(b) {}

    void show()
    {
        base->show();
        cout << "Concrete Decorator 2 Show Function Called" << endl;
    }
};

int main()
{
    Base *b1 = new ConcreteBase1();
    Base *b2 = new ConcreteBase2();
    Decorator *d1 = new ConcreteDecorator1(b1);
    Decorator *d2 = new ConcreteDecorator2(b2);
    Decorator *d3 = new ConcreteDecorator1(new ConcreteDecorator2(b1));
    Decorator *d4 = new ConcreteDecorator2(new ConcreteDecorator1(b2));

    d1->baseShow();
    cout << endl;
    d1->show();
    cout << endl;
    d2->baseShow();
    cout << endl;
    d2->show();
    cout << endl;

    d3->baseShow();
    cout << endl;
    d3->show();
    cout << endl;
    d4->baseShow();
    cout << endl;
    d4->show();

    return 0;
}