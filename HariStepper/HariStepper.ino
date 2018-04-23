#include <Stepper.h>

// Here to set the stepper motor rotation is how many steps
#define STEPS 100

// attached toSet the step number and pin of the stepper motor
Stepper stepper(STEPS, 8, 9, 10, 11);

// Define variables used to store historical readings
int previous = 0;

void setup()
{
  // Set the motor at a speed of 90 steps per minute
  stepper.setSpeed(90);
}

void loop()
{
//  int val = analogRead(0); // Get sensor readings
//  stepper.step(val - previous);// Move the number of steps for the current readings    less historical readings
//  previous = val;// Save historical readings 
stepper.step(1000);
delay(1000);
stepper.step(-1000);
delay(1000);
  }

