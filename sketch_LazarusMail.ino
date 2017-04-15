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
  // put your main code here, to run repeatedly:

}

// Top elevator sensor
int elevatorTopSensor()
{
  topSensorState = digitalRead(topSensor);
  if (topSensorState = HIGH)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// Bottom elevator sensor
int elevatorBottomSensor()
{
  bottomSensorState = digitalRead(bottomSensor);
  if (bottomSensorState = HIGH)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// Opening sensor
int openingSensorFunc()
{
  openingSensorState = digitalRead(openingSensor);
  if (openingSensorState = HIGH)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// Box weight/fill sensor
int boxSensor()
{
  
}

// Controlls the step motor
int stepperMotor(boolean runForward, double speedRPS, int stepCount)
{

}

