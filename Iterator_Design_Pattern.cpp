#include<bits/stdc++.h>
using namespace std;
#define ll int
#define pb push_back

//ITERATOR DESIGN PATTERN

//For creating concrete classes in this desigh pattern always create Iterable class first and then create the Iterator class. This is because the Iterator class will be using the Iterable class as a reference to access the data structure and perform the required operations on it.

//Generic Iterator Template class
template <typename T>
class Iterator
{
public:
    virtual bool has_next()=0;
    virtual T next()=0;
};

//Generic Iterable Template Class
template <typename T>
class Iterable
{
public:
    virtual Iterator<T>* get_iterator()=0;
};

//Vector data extends Generic Iterable class
class vector_data:public Iterable<int>
{
private:
    vector<int> v;

public:
    vector_data(vector<int>& a)
    {
        this->v=a;
    }

    const int get_size()
    {
        return v.size();
    }

    int get_val(ll index)
    {
        return v[index];
    }

    Iterator<int>* get_iterator() override;
};


//Vector_Iterator extends Generic Iterator class
class vector_iterator:public Iterator<int>
{
private:
    int curr;
    vector_data* vd;

public:
    vector_iterator(vector_data* vd)
    {
        this->curr=0;
        this->vd= vd;
    }

    bool has_next() override
    {
        return (curr < (vd->get_size()));
    }

    int next() override
    {
        if(!has_next())
        {
            return -1;
        }
        return vd->get_val(curr++);
    }
};


//Declaring the get_iterator method outside the class
Iterator<int>* vector_data :: get_iterator()
{
    return new vector_iterator(this);
}


//Link_List Iterable extends Generic Iterable class

class Linked_List:public Iterable<int>
{
private:
    int val;
    Linked_List* next_ptr;

public:
    Linked_List(ll val)
    {
        this->val= val;
        this->next_ptr =nullptr;
    }

    ll get_val()
    {
        return val;
    }

    Linked_List* next()
    {
        return next_ptr;
    }

    void set_next(Linked_List* ptr)
    {
        this->next_ptr=ptr;
    }

    Iterator<int>* get_iterator() override;
};


//Linked List Iterator extends Generic Iterator class

class Linked_List_Iterator:public Iterator<int>
{
private:
    Linked_List* ptr;

public:
    Linked_List_Iterator(Linked_List* ptr)
    {
        this->ptr= ptr;
    }

    bool has_next() override
    {
        return ptr!=nullptr;
    }

    int next() override
    {
        ll x=ptr->get_val();
        ptr=ptr->next();
        return x;
    }
};


//Declaring the get_iterator method outside the class
Iterator<int>* Linked_List:: get_iterator()
{
    return new Linked_List_Iterator(this);
}

//Binary_Tree Iterable Class
class Binary_Tree:public Iterable<int>
{
private:
    int val;
    Binary_Tree* left;
    Binary_Tree* right;

public:
    Binary_Tree(int val)
    {
        this->val=val;
        this->left=nullptr;
        this->right= nullptr;
    }

    int get_val()
    {
        return val;
    }

    Binary_Tree* get_left()
    {
        return left;
    }

    Binary_Tree* get_right()
    {
        return right;
    }

    void set_left(Binary_Tree* ptr)
    {
        this->left=ptr;
    }

    void set_right(Binary_Tree* ptr)
    {
        this->right=ptr;
    }

    Iterator<int>* get_iterator() override;
} ;

//Binary_Tree Iterator
class BT_Iterator:public Iterator<int>
{
private:
    stack<Binary_Tree*> q;

public:
    BT_Iterator(Binary_Tree* t)
    {
        while(t!=nullptr)
        {
            q.push(t);
            t=t->get_left();
        }
    }

    bool has_next() override
    {
        return (!q.empty());
    }

    //In-Order Traversal in Iterative approach using stack
    int next() override
    {
        Binary_Tree* t=q.top();
        q.pop();
        ll x= t->get_val();
        t= t->get_right();

        if(t!=nullptr)
        {
            while(t!=nullptr)
            {
                q.push(t);
                t=t->get_left();
            }
        }

        return x;
    }

} ;

Iterator<int>* Binary_Tree::get_iterator()
{
    return new BT_Iterator(this);
}


int main()
{

    vector<ll> v= {1,2,3,4,5};

    Iterable<int>* vdata= new vector_data(v);

    Iterator<int>* vdata_iterator= vdata->get_iterator();

    while(vdata_iterator->has_next())
    {
        cout<<vdata_iterator->next()<<" ";
    }
    cout<<endl;

    Linked_List* head=new Linked_List(v[0]);
    Linked_List* temp=head;

    for(ll i=1; i<v.size(); i++)
    {
        temp->set_next(new Linked_List(v[i]));
        temp= temp->next();
    }

    Iterator<int>* LL_iterator= head->get_iterator();

    while(LL_iterator->has_next())
    {
        cout<<LL_iterator->next()<<" ";
    }
    cout<<endl;


    Binary_Tree* root=new Binary_Tree(v[0]);
    auto t=root;
    /*for(ll i=1; i<v.size(); i++)
    {
        if(i%2)
        {
            t->set_left(new Binary_Tree(v[i]));
            t=t->get_left();
        }
        else
        {
            t->set_right(new Binary_Tree(v[i]));
            t=t->get_right();
        }
    }*/

    t->set_left(new Binary_Tree(v[1]));
    t->set_right(new Binary_Tree(v[2]));
    t=t->get_left();
    t->set_left(new Binary_Tree(v[3]));
    t->set_right(new Binary_Tree(v[4]));


    Iterator<int>* bt_iterator=root->get_iterator();

    while(bt_iterator->has_next())
    {
        cout<<bt_iterator->next()<<" ";
    }
    cout<<endl;



    return 0;
}

