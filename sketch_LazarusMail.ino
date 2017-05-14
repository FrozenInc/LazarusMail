// This is the code for the Arduino controlling Lazarus mail
// It has the following parts:
// 3 digital sensors
// 1 analog sensor
// 1 stepper motor with coresponding controller accepting: direction, steps, sleep, reset

#include "hx711.h"

/*
 * TODO: Create the amount of pins for all the sensors
 */
// All digital sensors
const int topSensor = 2;
int topSensorState;

const int bottomSensor = 4;
int bottomSensorState;

const int middleSensor = 6;
int middleSensorState;

const int openingSensor = 8;
int openingSensorState;

// All analog sensors
// Box sensor
//DOUT = #A1
//SCK = #A0
Hx711 scale(A1, A0);
int boxSensorState;


// Motor pins
const int stepPin = 10;
const int dirPin =  11;
// The number of steps in one full motor rotation
//const int stepsInFullRound = 200;

// Should the elevator go at any direction
// 0 = no
// 1 = yes
int go = 0;
  
// What direction should the elevator go to 
// 0 = down
// 1 = up
int dir = 0;

// Saves the last positon of the elevator(top or bot)
// 0 = bot
// 1 = top
int lastPos = 0;

// Where is the elevator supposed to go
// 0 = bot
// 1 = mid
// 2 = top
int destination = 0;

// Has the elevator passed mid?
// 0 = no
// 1 = yes
int passedMid = 0;

// Top elevator sensor
int elevatorTopSensor()
{
  if (digitalRead(topSensor) == HIGH)
  {
    return LOW;
  }
  return HIGH;
}


// Middle elevator sensor
int elevatorMiddleSensor()
{
  if (digitalRead(middleSensor) == HIGH)
  {
    return LOW;
  }
  return HIGH;
}

// Bottom elevator sensor
int elevatorBottomSensor()
{
  if (digitalRead(bottomSensor) == HIGH)
  {
    return LOW;
  }
  return HIGH;
}

// Opening sensor
int openingSensorFunc()
{
  if (digitalRead(openingSensor) == HIGH)
  {
    return LOW;
  }
  return HIGH;
}

// Box weight sensor
int boxSensor()
{
  // Gets the weight that the analog sensor detects and returns it
  return scale.getGram();
}

// Starts or stops the motor
// This only turns 1 step, so you need to call it every loop if you want it to continue spinning
void startMotor()
{
  analogWrite(stepPin, 500);
}

void stopMotor()
{
  analogWrite(stepPin, 0);
}

// Changes the direction of the motor
// Return the new direction so that we can use the function
int setDirection(int newDirection)
{
  digitalWrite(dirPin, newDirection);
  return newDirection;
}

// Useless shit, but makes reading the code easier
int setLastPos(int newLastPos)
{
  return newLastPos;
}

int setDestination(int newDestination)
{
  return newDestination;
}

int setPassedMid(int newPassedMid)
{
  return newPassedMid;
}

void setup() {
  // put your setup code here, to run once:

  // Initializes the pins for the motor
  pinMode(stepPin, OUTPUT);      
  pinMode(dirPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW); 

  // Initializes the pins for the digital sensors
  pinMode(topSensor, INPUT_PULLUP);
  pinMode(middleSensor, INPUT_PULLUP);
  pinMode(bottomSensor, INPUT_PULLUP);  
  pinMode(openingSensor, INPUT_PULLUP);
}

// Loop checks all the sensors and decides if the elevator should move and at what direction
void loop() {


  // Results from the digital sensors
  // 0 = no signal
  // 1 = signal
  topSensorState = elevatorTopSensor();
  middleSensorState = elevatorMiddleSensor();
  bottomSensorState = elevatorBottomSensor();
  openingSensorState = openingSensorFunc();

  // Result from the analog sensor
  boxSensorState = boxSensor();

  

}



