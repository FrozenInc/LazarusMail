// This is the code for the Arduino controlling Lazarus mail
// It has the following parts:
// 4 digital sensors
// 1 analog sensor
// 1 stepper motor with coresponding controller accepting: direction, steps, sleep, reset

#include "hx711.h"

// Determinates what the max weight in the box is
//#define MAX_WEIGHT 1000
#define MAX_WEIGHT 200

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

// CLK = speed, analog signal
// CW = direction, digital signal
// Motor pins
const int stepPin = 10;
const int dirPin =  11;

// Should the elevator go at any direction
// 0 = no
// 1 = yes
int go = 0;
  
// What direction should the elevator go to 
// 0 = up
// 1 = down
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
  lastPos = 1;
  if (digitalRead(topSensor) == HIGH)
  {
    return LOW;
  }
  return HIGH;
}


// Middle elevator sensor
int elevatorMiddleSensor()
{
  passedMid = 1;
  if (digitalRead(middleSensor) == HIGH)
  {
    return LOW;
  }
  return HIGH;
}

// Bottom elevator sensor
int elevatorBottomSensor()
{
  lastPos = 0;
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
  analogWrite(stepPin, 1000);
}

void stopMotor()
{
  analogWrite(stepPin, 0);
}

// Changes the direction of the motor
// Return the new direction so that we can use the function
int setDirection(int newDirection)
{
  if(newDirection == 1){
    newDirection = 0;
  }
  else{
    newDirection = 1;
  }
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
int setGo(int newGo)
{
  // Stops the motor if the code decides that the newGo is 0
  if(newGo == 0){
    stopMotor();
  }
  return newGo;
}

void setup() {
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
  // Result from the analog sensor
  //boxSensorState = boxSensor();
  boxSensorState = 0;
  // Sets direction to bottom when LAzarus Mail is started so that it calibrates itself when it reaches the bottom sensor
  dir = setDirection(0);
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
  

  // If the elevator is at the bottom check if the mail drop has been opened and decides if it should move or not
  // Dont move
  if(bottomSensorState == HIGH && go == 0 && openingSensorState == HIGH){
    lastPos = setLastPos(0);
    destination = setDestination(0);
    dir = setDirection(0);
    passedMid = setPassedMid(0);
    go = setGo(0);
    //Serial.println("1");
  }
  // Dont move
  else if(bottomSensorState == HIGH && go == 0 && openingSensorState == LOW){
    lastPos = setLastPos(0);
    destination = setDestination(2);
    dir = setDirection(1);
    passedMid = setPassedMid(0);
    go = setGo(0);
    delay(5000);
    // Check is the mail drop has been closed and then move
    openingSensorState = openingSensorFunc();
    if(bottomSensorState == HIGH && openingSensorState == HIGH){
      delay(5000);
      lastPos = setLastPos(0);
      destination = setDestination(2);
      dir = setDirection(1);
      passedMid = setPassedMid(0);
      go = setGo(1);
    }
    // If the mail drop is still open dont move
    else{
      lastPos = setLastPos(0);
      destination = setDestination(0);
      dir = setDirection(0);
      passedMid = setPassedMid(0);
      go = setGo(0);
    }
  }
  // IF the destination is to the bottom, stop when it reaches is
  else if(bottomSensorState == HIGH && go == 1 && openingSensorState == HIGH && destination == 0){
    lastPos = setLastPos(0);
    destination = setDestination(0);
    dir = setDirection(0);
    passedMid = setPassedMid(0);
    go = setGo(0);
  }

  // Mid sensor, just moving by
  else if(middleSensorState == HIGH && destination != 1){
    passedMid = setPassedMid(1);
    go = setGo(1);
  }

  // Mid sensor, stopping at it
  else if(middleSensorState == HIGH && destination == 1){
    passedMid = setPassedMid(1);
    dir = setDirection(0);
    go = setGo(0);
    boxSensorState = boxSensor();
    if(boxSensorState < MAX_WEIGHT){
      passedMid = setPassedMid(0);
      dir = setDirection(0);
      destination = setDestination(0);
      go = setGo(1);
    }
  }
  
  // Top sensor
  // Stops at top sensor and then moves to a new location
  else if(topSensorState == HIGH && destination == 2){
    
    go = setGo(0);
    passedMid = setPassedMid(0);
    dir = setDirection(0);
    boxSensorState = boxSensor();
    delay(5000);
    lastPos = setLastPos(1);    
    
    // Checks if the box is full or not and decides a destination
    if(boxSensorState > MAX_WEIGHT){
      destination = setDestination(1);
      go = setGo(1);
    }
    else{
      destination = setDestination(0);
      go = setGo(1);
    }
  }
  else if(topSensorState == HIGH && openingSensorState == LOW){
      go = setGo(0);
      destination = setDestination(2);
    }

  // Checks if the opening is open and stops the motor
  // This needs to exist as otherwise every single if/else if needs to check too
  if(openingSensorState == LOW){
    go = setGo(0);
  }
  else if(openingSensorState == HIGH && bottomSensorState == LOW && middleSensorState == LOW && topSensorState == LOW){
    go = setGo(1);
  }

  // Decides if the motor shall move or not
  // Only place that starts the motor as otherwise we risk that it doesnt stop at a correct position
  if(go == 0){
    stopMotor();
  }
  else{
    startMotor();
  }
}

