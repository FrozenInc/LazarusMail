//
// Created by Taco on 10/04/2017.
//

#ifndef LAZARUSMAILALESS_MAIN_H
#define LAZARUSMAILALESS_MAIN_H
#include <iostream>
#include "slave.h"


void masterSetup();
bool masterLoop();

// Get analog master sensors
int masterGetAnalogSensor1();
int masterGetAnalogSensor2();

// Master - slave connection
int getAnalogSignalFromSlave();

// Analog output for the stepper motor
int sendMotorControl();

#endif //LAZARUSMAILALESS_MAIN_H
