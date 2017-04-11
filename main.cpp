
// Master takes in 2 analog sensors and analog signal from the slave arduino
// Sends out digital signal to the stepper motor
//
// Master calculates everything, while the slave only sends information to master

#include "main.hpp"

// Only for simulating the arduino
int main() {

    // Checks if there is a connection between master and slave
    bool connection = false;

    // Checks if the loop should continue to run
    bool run = true;
    int slaveSignal = 1;

    // Runs first time setup
    while(!connection) {
        connection = masterSetup();
    }
    //slaveSetup();

    // Runs the loop
    while(run){
        slaveSignal = getAnalogSignalFromSlave();
        if(slaveSignal == 0) {
            run = masterLoop();
        }
        else{
            //ADD MORE STUFF HERE
        }
    }
    return 0;
}


bool masterSetup()
{
    return slaveSetup();
}

bool masterLoop()
{
    bool run = false;

    return run;
}

int masterGetAnalogSensor1()
{
    int force = 0;

    if(force == 0) {
        return 1;
    }
    else {
        return 0;
    }
    return 0;
}
int masterGetAnalogSensor2()
{

    int force = 0;

    if(force == 0) {
        return 1;
    }
    else {
        return 0;
    }
    return 0;

}

int getAnalogSignalFromSlave()
{
    return slaveLoop();
}

int sendMotorControl()
{
    return 0;
}
