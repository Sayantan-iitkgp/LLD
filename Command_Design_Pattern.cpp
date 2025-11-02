#include <bits/stdc++.h>
using namespace std;

// Command Design Pattern

// Light
class Light
{
public:
    void on()
    {
        cout << "Light is ON" << endl;
    }
    void off()
    {
        cout << "Light is OFF" << endl;
    }
};

// Fan
class Fan
{
public:
    void start()
    {
        cout << "Fan is STARTED" << endl;
    }
    void stop()
    {
        cout << "Fan is STOPPED" << endl;
    }
};

// Command Interface
class ICommand
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~ICommand() {}
};

// Concrete Command
class Light_Command : public ICommand
{
private:
    Light *light;

public:
    Light_Command(Light *l) : light(l) {}
    void execute() override
    {
        light->on();
    }
    void undo() override
    {
        light->off();
    }
};

class Fan_Command : public ICommand
{
private:
    Fan *fan;

public:
    Fan_Command(Fan *f) : fan(f) {}
    void execute() override
    {
        fan->start();
    }
    void undo() override
    {
        fan->stop();
    }
};

// Remote Control
class RemoteControl
{
private:
    vector<ICommand *> commands;
    vector<bool> commandStates; // true for executed, false for undone
public:
    void setCommand(ICommand *command)
    {
        commands.push_back(command);
        commandStates.push_back(false); // Initially not executed
    }

    void pressButton(int index)
    {
        if (index < 0 || index >= commands.size())
        {
            cout << "Invalid Command Index" << endl;
            return;
        }

        if (!commandStates[index])
        {
            commands[index]->execute();
            commandStates[index] = true;
        }
        else
        {
            commands[index]->undo();
            commandStates[index] = false;
        }
    }
};

int main()
{
    Light *light = new Light();
    Fan *fan = new Fan();
    ICommand *cmd1 = new Light_Command(light);
    ICommand *cmd2 = new Fan_Command(fan);

    RemoteControl remote;
    remote.setCommand(cmd1);
    remote.setCommand(cmd2);
    remote.pressButton(0); // Light ON
    remote.pressButton(1); // Fan STARTED
    remote.pressButton(0); // Light OFF
    remote.pressButton(0); // Light ON
    remote.pressButton(1); // Fan STOPPED
    remote.pressButton(1); // Fan STARTED
    remote.pressButton(1); // Fan STOPPED
    remote.pressButton(2); // Invalid Command Index
    remote.pressButton(0); // Light OFF

    return 0;
}