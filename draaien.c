#include "simpletools.h"
#include "abdrive360.h"

int main()
{
 
  moveForwardInCM(23);
  pause(500);
  moveBackwardInCM(23);
}

int turnDegrees(int degrees) {
  float ticks = degrees * 0.284;
  drive_goto(ticks, ticks * -1);
}
 
int turnTest()
{
  turnRight();
  turnLeft(); 
}

int turnRight()
{
  drive_goto(26,-25);  
}

int turnLeft()
{
  drive_goto(-25,26); 
}

int moveTest()
{
  moveForwardInCM(10);
  moveBackwardInCM(10);
  
  pause(100);
  
  moveForwardInCM(10);
  moveBackwardInCM(10);
  
  pause(100);
  
  moveForwardInCM(10);
  moveBackwardInCM(10); 
}                            

int moveForwardInCM(int cm)
{
  drive_goto(3.2*cm*0.96, 3.2*cm*0.96);
}

int moveBackwardInCM(int cm)
{
  drive_goto(-3.2*cm*0.96, -3.2*cm*0.96);
}

