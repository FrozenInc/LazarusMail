
// Master takes in 2 analog sensors and analog signal from the slave arduino
// Sends out digital signal to the stepper motor
//
// Master calculates everything, while the slave only sends information to master

#include "main.hpp"

// Only for simulating the arduino
int main() {

    // Checks if the loop should continue to run
    bool run = true;
    int slaveSignal = 1;

    // Runs first time setup
    masterSetup();
    slaveSetup();

    // Runs the loop
    while(run){
        slaveSignal = slaveLoop();
        run = masterLoop();
    }
    return 0;
}


void masterSetup()
{

}

bool masterLoop()
{
    bool run = false;

    return run;
}

int masterGetAnalogSensor1()
{
    return 0;
}
int masterGetAnalogSensor2()
{
    return 0;
}

int getAnalogSignalFromSlave()
{
    return 0;
}

int sendMotorControl()
{
    return 0;
}
