//
// Created by Taco on 10/04/2017.
//


// Slave only takes in 2 analog sensors and send and analog signal to the master arduino

#include "slave.hpp"

bool slaveSetup()
{
    bool connection = true;
    return connection;
}

int slaveLoop()
{
    int s1 = 1, s2 = 1;
    int slaveSignal;

    s1 = slaveGetAnalogSensor1();
    s2 = slaveGetAnalogSensor2();

    slaveSignal = sendAnalogSignalToMaster(s1, s2);

    return slaveSignal;
}

int slaveGetAnalogSensor1()
{
    int force = 0;

    if(force == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
int slaveGetAnalogSensor2()
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

int sendAnalogSignalToMaster(int s1, int s2)
{
    if(s1 == 0 && s2 == 0){
        return 0;
    }
    else if(s1 == 0 && s2 != 0){
        return 1;
    }
    else if(s1 != 1 && s2 == 0){
        return 2;
    }
    else{
        return 3;
    }
}
