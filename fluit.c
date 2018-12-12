#include "simpletools.h"
#include "abdrive360.h"

const int steps = 50;

int main()
{
  wave(1500, 4000, 250);
  pause(300);
  wave(3200, 1600, 600);
  
  pause(2500);
  
  wave(1500, 4000, 350);
  pause(100);
  wave(3000, 3600, 200);
  
  pause(300);
  
  wave(1700, 4200, 350);
  pause(100);
  wave(3200, 3800, 200);
}

int wave(int start, int stop, int duration)
{
  if(start < stop)
  {
    waveUp(start, stop, duration);
  }
  else if (start > stop)
  {
    waveDown(start, stop, duration);
  }
  else
  {
    freqout(9, duration, start);
  }        
}

int waveUp(int startFrequency, int stopFrequency, int duration)
{
  
  float numberOfNotes = (stopFrequency - startFrequency) / steps;
  float durationPerNote = duration / numberOfNotes;
  
  printf("num: %.2f - dur: %.2f \n", numberOfNotes, durationPerNote);
  
  for(int i=startFrequency; i<=stopFrequency; i+=steps)
  {
    freqout(9, durationPerNote, i);
  }
}

int waveDown(int startFrequency, int stopFrequency, int duration)
{
  
  float numberOfNotes = abs(stopFrequency - startFrequency) / steps;
  float durationPerNote = duration / numberOfNotes;
  printf("num: %.2f - dur: %.2f \n", numberOfNotes, durationPerNote);
  
  for(int i=startFrequency; i>=stopFrequency; i-=steps)
  {
    
    freqout(9, durationPerNote, i);
  }
}  