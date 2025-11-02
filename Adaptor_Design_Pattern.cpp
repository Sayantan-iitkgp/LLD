#include <bits/stdc++.h>
using namespace std;

// Adaptor Design Pattern

// Abstract Client site interface
class ITarget
{
public:
    virtual void request() = 0;
    virtual ~ITarget() = default;
};

// Adaptee class
class Adaptee
{
public:
    void specificRequest()
    {
        cout << "Specific Request called. It can't be called from client site" << endl;
    }
};

// Adaptor class
class Adaptor : public ITarget
{
private:
    Adaptee *adaptee;

public:
    Adaptor(Adaptee *a) : adaptee(a) {}
    void request() override
    {
        cout << "Request called from client site" << endl;
        cout << "Calling Specific Request of Adaptee class from Adaptor class" << endl;
        adaptee->specificRequest();
    }
};


int main()
{
    Adaptee *adaptee = new Adaptee();
    ITarget *target = new Adaptor(adaptee);
    target->request();
    return 0;
}