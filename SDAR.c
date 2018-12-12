#include "simpletools.h"
#include "abdrive360.h"
#include "ping.h" // Library for operating an ultrasonic distance sensor
#include "mstimer.h" // Milisecond timer library

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int moveForwardInCM(float);
int moveBackwardInCM(float);
int pushObject(float, int);

float cutOff = 45.0;
const int ULTRASONIC_SENSOR_PIN_NO = 8; // Verify with actual breadboard circuit!

float closestMeasurement;
int closestMeasurementDegrees;


/* Performs an ultrasonic echo measurement: returns time-of-flight in microseconds */
int measureEchoTime_mus() {
  int echoTime_mus = ping(ULTRASONIC_SENSOR_PIN_NO); // Out of range: 18427
  
  //print("%d\n", echoTime_mus);
  
  return echoTime_mus;
}
int main() {
  findClosestObject();
  while (closestMeasurement < cutOff) {
    pushObject(closestMeasurement, closestMeasurementDegrees);
    findClosestObject();
  }    
  playPirates();
}

int pushObject(float cm, int degrees){
  print("Pushing object at %d... \n", degrees);
  
  print("turning %d... \n", degrees);
  if(degrees > 180){
    turnDegrees(degrees - 360);
  }
  else
  {
    turnDegrees(degrees);
  }    
  
  print("driving %.2f... \n", cm);
  moveForwardInCM(cm + 5.0);
  
  print("driving back %.2f... \n", cm);
  moveBackwardInCM(cm + 5.0);
  
  closestMeasurement = 100.0;
}  


int turnDegrees(int degrees) {      
  float ticks = degrees * 0.284;
  drive_goto(ticks, ticks * -1);
  pause(50);
}

int moveForwardInCM(float cm) {
  drive_goto(3.2*cm*0.96, 3.2*cm*0.96);
  pause(100);
}

int moveBackwardInCM(float cm)
{
  drive_goto(-3.2*cm*0.96, -3.2*cm*0.96);
  pause(100);
}

/* Performs an ultrasonic echo measurement: returns distance in centimeters */
float measureDistance_cm() {
  const float SPEED_OF_SOUND_M_PER_S = 343; // Assumptions: in air, of 20 degrees Celsius
  const float SPEED_OF_SOUND_CM_PER_MUS = SPEED_OF_SOUND_M_PER_S * 100.0 / 1000000.0;
  
  int echoTime_mus = measureEchoTime_mus();
  
  float objectDistance_cm = (float) echoTime_mus * SPEED_OF_SOUND_CM_PER_MUS;
  
  objectDistance_cm = objectDistance_cm / 2.0; // NB: time-of-flight also includes return!
  
  return objectDistance_cm;
}  

int findClosestObject() {
  int turn = 18;
  int degrees = 0;
  closestMeasurement = cutOff;
  closestMeasurementDegrees = -1;
  print("Finding closest object... \n");
  
  while(degrees < 360)
  {
    float distance = measureDistance_cm();
    print("degrees: %d    distance: %.2f    \n", degrees, distance);
    if(distance < closestMeasurement)
    {
      closestMeasurement = distance;
      closestMeasurementDegrees = degrees;
      print("closestMeasurement: %.2f    closestMeasurementDegrees: %d     \n", closestMeasurement, closestMeasurementDegrees);
    }
    degrees += turn;
    turnDegrees(turn + 0); // 0 -> 1 Y
  }
  
  print("Done finding closest object... \n \n \n \n");
  return degrees;
}

const double songspeed = 0.6; //Change to 2 for a slower version of the song, the bigger the number the slower the song

int notes[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};

int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};

int playPirates() {
  for (int i=0; i < 203; i++){
    int wait = duration[i] * songspeed;
    freqout(4,wait,notes[i]);
    pause(wait);
  }
}

