#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ESC.h>

//  Code is specialized for a certain boat and body of water

double maxX = sqrt(8192 / 3);
double maxY = sqrt(8192);
const double pi = 3.14159265358979323846;
ESC boatESC(3, 1000, 2000, 500);
Servo boatServo;

//  Eqiation of the route the boat will follow; Returns the current Y position of the boat
double curveEQX(double y)
{
  double power = pow(y, 2)/3;
  double radicalConst = (8192 / 3);

  double curveReturn = sqrt(radicalConst - power);
  //printf("x = %f\n", curveReturn);
  return curveReturn;
}

// Declare Microcontroller Pins for Communication && Initiate ESC Speed
void setup()  
{ 

 //declare pin 3 as signal for ESC
  pinMode(3, INPUT);
  //analogWrite(14, HIGH);

  //declare pin 5 as signal for Servo
  pinMode(5, INPUT);
  
  //boatESC.calib();

  //boatESC.stop();

  boatESC.arm();
 
  boatServo.attach(5);
  boatServo.write(95);

  for (int oESC = 1500; oESC <= 1600; oESC += 1) 
      {  // goes from 1000 microseconds to 2000 microseconds
        boatESC.speed(oESC);                               
        delay(30);                                            
      }
  
} 

// Iterate over the Course Equation and change rudder angle as necessary
void loop()  
{       
    
    for (double y = 0; y <= maxY; y+=0.001)
    {
     x = curveEQX(y);
      double rudderAngle = (90) - atan((x / y));
      boatServo.write(rudderAngle);
      
      //printf("Rudder Angle: %f y: %f x: %f\n", rudderAngle, y, x);
      
    }
    for (double y = maxY; y >= 0; y-=0.001)
    {
     x = curveEQX(y);
      double rudderAngle = (90) - atan((x / y));
      boatServo.write(rudderAngle);
      
      //printf("Rudder Angle: %f y: %f x: %f\n", rudderAngle, y, x);
      
    }

}
