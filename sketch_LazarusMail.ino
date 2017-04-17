// This is the code for the Arduino controlling Lazarus mail
// It has the following parts:
// 3 digital sensors
// 1 analog sensor
// 1 stepper motor with coresponding controller accepting: direction, steps, sleep, reset

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
const int boxSensor1 = A0;
const int boxSensor2 = A1;
int boxSensorState;


// Motor pins
const int stepPin = 13;
const int dirPin =  12;
// The number of steps in one full motor rotation
const int stepsInFullRound = 200;


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
  // If full set direction to up
  if (boxSen > 1000)
  {
    dir = 1;
  }

  // Remmebers where the elevator was last
  if (topSen == 1)
  {
    lastPos = 1;
  }
  else if (botSen == 1)
  {
    lastPos = 0;
  }

  // Checks if the opening is open and decideds if it should go or not
  // This should only be one funtion that checks if the elevator shall move as otherwise it migth overwrite itself and do bad stuff
  if (openSen == 0)
  {
    go = 0;
    // Waits 15 seconds before trying anything new
    delay(15000);
    // If the opening is closed it knows that somebody has droppen mail so it goes to the box
    if (openSen == 1)
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

// Box weight/fill sensor
int boxSensor()
{
  return 0;
}

// Controlls the step motor
int stepperMotor(boolean runForward, double speedRPS, int stepCount)
{

}

