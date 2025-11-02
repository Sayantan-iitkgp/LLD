#include <bits/stdc++.h>
using namespace std;

class Singleton{
 private:
     static Singleton* instance;

     Singleton(){
      cout<<"Singleton Object is created"<<endl;
     }

 public:

    static Singleton* get_instance(){
       if(instance==nullptr){instance=new Singleton();}
       return instance;
    }

};

Singleton* Singleton::instance=nullptr;

int main(){
    Singleton* obj1= Singleton::get_instance();
    Singleton* obj2= Singleton::get_instance();

    cout<<(obj1==obj2)<<endl;
  return 0;
}
