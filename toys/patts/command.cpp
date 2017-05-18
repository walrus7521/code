#include <iostream>

// http://www.bogotobogo.com/DesignPatterns/
 
using namespace std;

// abstract command Interface
class Command
{
public:
    virtual void execute() = 0;
};
 
// concrete receiver class
class Light 
{
public:
    void on() {
        cout << "The light is on\n";
    }
    void off() {
        cout << "The light is off\n";
    }
}; 

// concrete receiver command for turning on the light
class LightOnCommand : public Command 
{
public:
    LightOnCommand(Light *light) : mLight(light) {}
    void execute(){
        mLight->on();
    }
private:
    Light *mLight;
};
 
// concrete receiver command for turning off the light
class LightOffCommand : public Command 
{
public:
    LightOffCommand(Light *light) : mLight(light) {}
    void execute(){
        mLight->off();
    }
private:
    Light *mLight;
};

// Invoker 
// Stores the ConcreteCommand object 
class RemoteControl 
{
public:
    void setCommand(Command *cmd) {
        mCmd = cmd;
    }

    void buttonPressed() {
        mCmd->execute();
    } 
private:
    Command *mCmd;
};
 
// The client
int main() 
{
    // Receiver 
    Light *light = new Light;

    // concrete Command objects 
    LightOnCommand *lightOn = new LightOnCommand(light);
    LightOffCommand *lightOff = new LightOffCommand(light);

    // invoker objects
    RemoteControl *control = new RemoteControl;

    // execute
    control->setCommand(lightOn);
    control->buttonPressed();
    control->setCommand(lightOff);
    control->buttonPressed();

    delete light; 
    delete lightOn;
    delete lightOff;
    delete control;

    return 0;
}
