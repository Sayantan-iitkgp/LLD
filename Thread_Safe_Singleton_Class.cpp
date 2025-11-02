#include <bits/stdc++.h>
using namespace std;

//THREAD SAFE DUE TO EARLY EAGAR INITIALIZATION OF SINGLETON CLASS INSTANCE. BUT NOT A VERY GOOD PRACTICAL APPROACH

class Singleton
{

private:
    static Singleton* instance;

    Singleton()
    {
        cout<<"Singleton Instance is created only once"<<endl;
    }

public:

    static Singleton* get_Instance()
    {
        return instance;
    }
};

//IT WILL NOT THROW SYNTAXTICAL ERROR BECAUSE STATIC MEMBERS AND METHODS BELONG TO A CLASS NOT TO A OBJECT. So We can call its private members and methods for representing any static member or static function

Singleton* Singleton::instance = new Singleton();


//THREAD SAFE SINGLETON CONSTRUCTOR WITH DOUBLE LOCKING.
class Singleton_New
{
private:
    static mutex mu;
    static Singleton_New* instance;

    //Private Constructor
    Singleton_New()
    {
        cout<<"Thread Safe Singleton Constructor is called only once"<<endl;
    }

public:

    static Singleton_New* get_instance()
    {
        //Double Locking
        //First Lock  for checking instance and acquiring the lock for most least condition
        if(instance==nullptr)
        {
            unique_lock<mutex> lock(mu);
            //Second lock for checking instance and creating the object if needed
            if(instance==nullptr)
            {
                instance= new Singleton_New();
            }
        }
        return instance;
    }
};

mutex Singleton_New::mu;
Singleton_New* Singleton_New::instance=nullptr;

int main()
{

    Singleton* obj1=Singleton::get_Instance();
    Singleton* obj2=Singleton::get_Instance();

    cout<<(obj1==obj2)<<endl;

    Singleton_New* obj3=Singleton_New::get_instance();
    Singleton_New* obj4=Singleton_New::get_instance();

    cout<<(obj3==obj4)<<endl;
    return 0;
}
