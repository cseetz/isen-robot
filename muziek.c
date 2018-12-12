#include "simpletools.h"                    
#include "ping.h"                       
#include <time.h>
#include "abdrive360.h"
#include "wavplayer.h"

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

#define melodyPin 9
//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

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

int main()
{
  playWAV();
} 

int playWAV() {
  int DO = 22, CLK = 23, DI = 24, CS = 25;        // SD I/O pins
  sd_mount(DO, CLK, DI, CS);                      // Mount SD card
 
  const char techloop[] = {"Hallo.wav"};       // Set up techloop string
  wav_play(techloop);                             // Pass to wav player
 
  wav_volume(6);                                  // Adjust volume
  pause(3500);                                    // Play for 3.5 s
  wav_volume(4);                                  // Repeat twice more
  pause(2000);
  wav_volume(8);
  pause(3500);
  
  wav_stop();                                      // Stop playing 
}  

int playPirates() {
  for (int i=0; i < 203; i++){
    int wait = duration[i] * songspeed;
    freqout(9,wait,notes[i]);
    pause(wait);
  }
}

int playMario()
{
  int size = sizeof(melody) / sizeof(int);

  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1300 / tempo[thisNote];

    freqout(melodyPin, noteDuration, melody[thisNote]);
    
    int pauseBetweenNotes = noteDuration * 0.40;
  
    pause(pauseBetweenNotes);
  }
}

int musicTest()
{
  int note[] = {1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};
  
  for (int i = 0; i < 8; i++) {
    freqout(9, 500, note[i]);
    pause(68); 
  }
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
  drive_goto(3.25*cm, 3.25*cm);
}

int moveBackwardInCM(int cm)
{
  drive_goto(-3.25*cm, -3.25*cm);
}


int ultraSound()                                    
{
  
  // max sampling rate 100/s 
  // max input = 315, min input = 2 kijk of er ruis is, of iets heel snels
  // max afstands 250cm
  
  clock_t toc;
  clock_t tic = clock();
  int x = 1;
  
  while(1)                                    
  {
    int cmDist = ping_cm(15); // doe een echo op pin 15                
    printf("cmDist = %d - %d\n", cmDist, x);
    
    x = x + 1;
    
    /*if (x >= 1000) {
      toc = clock();
      break; 
    }*/       
  }
  
  printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
}

int senseLight()
{
  // max input = 140000, min input 0
  // max sampling rate 120/s, realistischer 40/s
  
  clock_t toc;
  clock_t tic = clock();
  int x = 1;
    
  while(1)
  {
    high(5); // 3.3V op pin 5
    pause(1); // laadt capacitor op
    int t = rc_time(5, 1); // zet pin 5 op input, en kijk hoe lang het duurt voordat de normale voltage weer terug is 
    printf("t = %d - %d\n", t, x);
    x = x + 1;
    
    if (x >= 2000) {
      toc = clock();
      break; 
    }
  }
  
  printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
}

int buttonPress()
{
  // max input = 1, min input 0
  // max sampling rate 1 per 5ms
  clock_t toc;
  clock_t tic = clock();
  int x = 1;
  while(1)
  {    
    int button = input(3); // input 3, knop ingedrukt of niet
    //int button2 = input(4);
    printf("button = %d - %d\n", button, x);
    x = x + 1;
    //print("button2 = %d\n", button2);
    
    if (x >= 5000) {
      toc = clock();
      break; 
    }      
  }
  
  printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
}

int frequency(char note)
{
  const int numNotes = 8;
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
 
  for (int i = 0; i < numNotes; i++)
  {
    if (names[i] == note)
    {
      return(frequencies[i]);
    }
  }
  return(0);
}

int playWagner() {
  const int songLength = 18;
  char notes[] = "cdfda ag cdfdg gf ";
  int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};
  int tempo = 150;

  for (int i = 0; i < songLength; i++) {
    int duration = beats[i] * tempo;
   
    if (notes[i] == ' ') {
      pause(duration);
    } else {
      freqout(9, duration, frequency(notes[i]));
      pause(duration);
    }
      
    pause(tempo/10);
  }
}