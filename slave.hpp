//
// Created by Taco on 10/04/2017.
//

#ifndef LAZARUSMAILALESS_SLAVE_HPP
#define LAZARUSMAILALESS_SLAVE_HPP
#include <iostream>

bool slaveSetup();
int slaveLoop();

// Slave analog sensors
int slaveGetAnalogSensor1();
int slaveGetAnalogSensor2();

// Slave - master connection

int sendAnalogSignalToMaster(int s1, int s2);
#endif //LAZARUSMAILALESS_SLAVE_HPP
