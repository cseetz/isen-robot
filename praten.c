#include "simpletools.h"
#include "wavplayer.h"

int main() {
  int DO = 22, CLK = 23, DI = 24, CS = 25; // SD I/O pins
  sd_mount(DO, CLK, DI, CS); // Mount SD card
 
  const char hallo[] = {"hallo.wav"}; // Set up hallo string
  const char banaan[] = {"banaan.wav"}; // Set up banaan string
    
  wav_volume(10); // Volume to max
  wav_play(hallo); // Pass to wav player
  
  while (wav_playing()) {
   print("Playing!"); 
  }
  
  wav_play(banaan); // Pass to wav player
  
  while (wav_playing()) {
   print("Playing!"); 
  }
  
  wav_stop(); // Stop playing 
}
