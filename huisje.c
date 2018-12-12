#include "simpletools.h"
#include "abdrive360.h"

int moveForwardInCM(float);

int main() {
  moveForwardInCM(10.0); // 0 -> 1 Y
  pause(500);
  turnDegrees(-90);
  pause(500);
  moveForwardInCM(10.0); // 1 -> 2 Y
  pause(500);
  turnDegrees(-131); // original -135
  pause(500);
  moveForwardInCM(14.0); // 2 -> 3 N
  pause(500);
  turnDegrees(135);
  pause(500);
  moveForwardInCM(11.0); // 3 -> 4 Y
  pause(500);
  turnDegrees(88);
  pause(500);
  moveForwardInCM(9.5); // 4 -> 5 Y
  pause(500);
  turnDegrees(-135);
  pause(500);
  moveForwardInCM(6.0); // 5 -> 6 N
  pause(500);
  turnDegrees(-84);
  pause(500);
  moveForwardInCM(6.0); // 6 -> 7 N
  pause(500);
  turnDegrees(-89);
  pause(500);
  moveForwardInCM(14.0); // 7 -> 8 N
}

int turnDegrees(int degrees) {          
  float ticks = degrees * 0.284;
  drive_goto(ticks, ticks * -1);
}

int moveForwardInCM(float cm) {
  drive_goto(3.2*cm*0.96, 3.2*cm*0.96);
}