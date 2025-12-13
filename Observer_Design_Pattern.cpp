#include <bits/stdc++.h>
using namespace std;

// Observer Interface
class IObserver
{
public:
    virtual void update() = 0;
    virtual ~IObserver() {} // Virtual Destructor
};

// Observable Interface
class IObservable
{
protected:
    unordered_set<IObserver *> observers;

public:
    virtual void addObserver(class IObserver *observer) = 0;
    virtual void removeObserver(class IObserver *observer) = 0;
    virtual void notifyObservers() = 0;
    virtual void uploadContent(string Content_Title) = 0;
    virtual ~IObservable() {} // Virtual Destructor
};

// Concrete Observable Class
class Channel : public IObservable
{
private:
    string channelName;
    string latestVideo;

public:
    Channel(const string name) : channelName(name) {}

    void addObserver(IObserver *observer) override
    {
        observers.insert(observer);
    }

    void removeObserver(IObserver *observer) override
    {
        cout << "Removing observer from channel " << channelName << endl;
        observers.erase(observer);
    }

    void notifyObservers() override
    {
        for (auto observer : observers)
        {
            observer->update();
        }
    }

    void uploadContent(string Content_Title) override
    {
        latestVideo = Content_Title;
        cout << "Channel " << channelName << " uploaded a new video: " << latestVideo << endl;
        notifyObservers();
    }

    ~Channel()
    {
        cout << "Channel " << channelName << " is deleted" << endl;
        observers.clear();
    }
};

// Concrete Observer Class
class Subscriber : public IObserver
{
private:
    string subscriberName;
    IObservable *channel;

public:
    Subscriber(const string name, IObservable *ch) : subscriberName(name), channel(ch)
    {
        channel->addObserver(this);
    }

    void update() override
    {
        cout << "Subscriber " << subscriberName << " notified of new video!" << endl;
    }

    ~Subscriber()
    {
        cout << "Subscriber " << subscriberName << " is deleted" << endl;
        channel->removeObserver(this);
    }
};

int main()
{
    IObservable *techChannel = new Channel("TechReviews");
    IObserver *alice = new Subscriber("Alice", techChannel);
    IObserver *bob = new Subscriber("Bob", techChannel);
    techChannel->uploadContent("Top 10 C++17 Features");
    techChannel->removeObserver(bob);
    techChannel->uploadContent("Understanding Observer Pattern");
    delete alice;
    delete techChannel;
    return 0;
}