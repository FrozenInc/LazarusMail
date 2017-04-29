// This is the code for the Arduino controlling Lazarus mail
// It has the following parts:
// 3 digital sensors
// 1 analog sensor
// 1 stepper motor with coresponding controller accepting: direction, steps, sleep, reset

// Includes the library we use for the analog sensor
#include "hx711.h"

/*
 * TODO: Create the amount of pins for all the sensors
 */
// All digital sensors
const int topSensor = 2;
int topSensorState;
const int bottomSensor = 3;
int bottomSensorState;
const int openingSensor = 4;
int openingSensorState;

// All analog sensors
// Box sensor
//DOUT = #A1
//SCK = #A0
Hx711 scale(A1, A0);
int boxSensorState;


// Motor pins
const int stepPin = 13;
const int dirPin =  12;
// The number of steps in one full motor rotation
const int stepsInFullRound = 200;

// Is the elevator supposed to move
// 0 = no
// 1 = yes
int shouldGo = 0;

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

void setup() {
  // put your setup code here, to run once:

  // Initializes the pins for the motor
  pinMode(stepPin, OUTPUT);      
  pinMode(dirPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW); 

  // Initializes the pins for the digital sensors
  pinMode(topSensor, INPUT_PULLUP);
  pinMode(bottomSensor, INPUT_PULLUP);
  pinMode(openingSensor, INPUT_PULLUP);
}

// Loop checks all the sensors and decides if the elevator should move and at what direction
void loop() {


  // Results from the digital sensors
  // 0 = no signal
  // 1 = signal
  int topSen = elevatorTopSensor();
  int botSen = elevatorBottomSensor();
  int openSen = openingSensorFunc();

  // Result from the analog sensor
  // 0 = no signal
  // 1024 = max signal
  int boxSen = boxSensor();

  // Checks of the box is full
  // If full set direction to up so that it goes to the top and waits for a person to empty it
  // NOTE: The values needs to be tested to determinate how many kg we can put in
  if (boxSen > 1000)
  {
    dir = 1;
  }

  // Checks if the opening has been open
  if(openSen == 0)
  {
    shouldGo = 0;
    delay(15000);
    // If the opening has been closed after been open the elevator is free to move again
    if(openSen == 1)
    {
      shouldGo = 1;
      dir = 1;
      lastPos = 0;
    }
  }
  // If the elevator is at the top and the box is full it stops
  else if(topSen == 1 && boxSen > 1000)
  {
    shouldGo = 0;
    lastPos = 1;
    dir = 0;
  }
  /*
  // If the elevator is at the top but the box is still not full
  else if(topSen == 1 && boxSen < 1000)
  {
    // Wait 5 seconds to make sure all the mail gets droped
    delay(5000);
    shouldGo = 1;
    lastPos = 1;
    dir = 0;
  }
  */
  // This is supposed to make the elevator move between top and bot, but stop when it reaches it
  if (dir == 1 && lastPos == 0 && shouldGo == 1)
  {
    if (topSen == 1)
    {
      shouldGo = 0;
      dir = 0;
      lastPos = 1;
      delay(15000);
    }
  }
  else if (dir == 0 && lastPos == 1 && shouldGo == 1)
  {
    if (botSen == 0)
    {
      shouldGo = 0;
      dir = 1;
      lastPos = 0;
    }
  }

  // Decided acording to the shouldGo command if the elevator shall move and which direction
  if(shouldGo == 1)
  {
    go = 1;
    stepperMotor();
    delay(100);
    go = 0;
    stepperMotor();
  }
  else
  {
    go = 0;
    stepperMotor();  
  }

  /*
  // Checks if the opening is open and decideds if it should go or not
  // This should only be one funtion that checks if the elevator shall move as otherwise it migth overwrite itself and do bad stuff
  if (openSen == 0)
  {
    go = 0;
    // Waits 15 seconds before trying anything new
    delay(15000);
    // If the opening is closed it knows that somebody has droppen mail so it goes to the box
    // Also needs to know if it's at the bottom
    if (openSen == 1 && botSen == 1)
    {
      go = 1;
      dir = 1;
    }
  }
  // Checks if the box is full and the elevator is at the top
  else if (topSen == 1 && boxSen > 1000)
  {
    go = 0;
  }
  else
  {
    go = 1;
  }

  // Checks what the last position of the elevator was and decided in what direction the elevator shall move
  if (lastPos == 1)
  {
    dir = 0;
  }
  else
  {
    dir = 1;
  }

  // TODO:
  // 1. Stop the elevator at the bottom and top
  // 2. Make the elevator move when at the bot or top after getting/dropping of mail


  // This is supposed to make the elevator move between top and bot, but stop when it reaches it
  if (dir == 1 && lastPos == 0 && go == 1)
  {
    if (topSen == 1)
    {
      go = 0;
      dir = 0;
      lastPos = 1;
      delay(15000);
    }
  }
  else if (dir == 0 && lastPos == 1 && go == 1)
  {
    if (botSen == 0)
    {
      go = 0;
      dir = 1;
      lastPos = 0;
    }
  }


  // Calls the motor control funtion to move the motor 1 step at the right direction
  stepperMotor();
  */
  // Remmebers where the elevator was last (May not be needed)
  /*
  if (topSen == 1)
  {
    lastPos = 1;
  }
  else if (botSen == 1)
  {
    lastPos = 0;
  }
  */

}

// Top elevator sensor
int elevatorTopSensor()
{
  topSensorState = digitalRead(topSensor);
  if (topSensorState = HIGH)
  {
    return 1;
  }
  return 0;
}

// Bottom elevator sensor
int elevatorBottomSensor()
{
  bottomSensorState = digitalRead(bottomSensor);
  if (bottomSensorState = HIGH)
  {
    return 1;
  }
  return 0;
}

// Opening sensor
int openingSensorFunc()
{
  openingSensorState = digitalRead(openingSensor);
  if (openingSensorState = HIGH)
  {
    return 1;
  }
  return 0;
}

// Box weight sensor
int boxSensor()
{
  // Gets the weight that the analog sensor detects and returns it
  boxSensorState = scale.getGram();
  return boxSensorState;
}

// Controlls the step motor
// Runs the motor just 1 step in a specific direction
//void stepperMotor(boolean runForward, double speedRPS, int stepCount)
void stepperMotor()
{
  // Tells the motor what direction it must go
  digitalWrite(dirPin, dir);

  // Moves the motor 1 step
  if(go == 1)
  {
    digitalWrite(stepPin, HIGH);
    delay(1);
    digitalWrite(stepPin, LOW);
  }
  else
  {
    
  }
}
