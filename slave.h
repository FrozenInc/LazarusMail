//
// Created by Taco on 10/04/2017.
//

#ifndef LAZARUSMAILALESS_SLAVE_H
#define LAZARUSMAILALESS_SLAVE_H

#include <iostream>

void slaveSetup();
void slaveLoop();

// Slave analog sensors
int slaveGetAnalogSensor1();
int slaveGetAnalogSensor2();

// Slave - master connection

int sendAnalogSignalToMaster();

#endif //LAZARUSMAILALESS_SLAVE_H
