#include "simpletools.h" // Standard auxiliary library
#include "ping.h" // Library for operating an ultrasonic distance sensor
#include "mstimer.h" // Milisecond timer library

const int ULTRASONIC_SENSOR_PIN_NO = 15; // Verify with actual breadboard circuit!
const int PIEZO_SPEAKER_PIN_NO = 9; // Verify with actual breadboard circuit!

/* Performs an ultrasonic echo measurement: returns time-of-flight in microseconds */
int measureEchoTime_mus() {
  int echoTime_mus = ping(ULTRASONIC_SENSOR_PIN_NO); // Out of range: 18427
  
  //print("%d\n", echoTime_mus);
  
  return echoTime_mus;
}

/* Performs an ultrasonic echo measurement: returns distance in centimeters */
float measureDistance_cm() {
  const float SPEED_OF_SOUND_M_PER_S = 343; // Assumptions: in air, of 20 degrees Celsius
  const float SPEED_OF_SOUND_CM_PER_MUS = SPEED_OF_SOUND_M_PER_S * 100.0 / 1000000.0;
  
  int echoTime_mus = measureEchoTime_mus();
  
  float objectDistance_cm = (float) echoTime_mus * SPEED_OF_SOUND_CM_PER_MUS;
  
  objectDistance_cm = objectDistance_cm / 2.0; // NB: time-of-flight also includes return!
  
  print("%.2f\n", objectDistance_cm);
  
  return objectDistance_cm;
}  

float distanceToFreq_Hz(float distance_cm)
{
  /**
   * Exponentially map a distance (in CM) to a frequency (Hz).
   **/
  const float RANGE_START_CM = 5.0;
  const float RANGE_END_CM = 65.0;
  const float RANGE_START_HZ = 880.0; // (lower start frequencies were hard to hear!)
  const float CM_PER_OCTAVE = (RANGE_END_CM - RANGE_START_CM) / 3.0;
  
  float returnFreq_Hz = 0.0; // default return value
  float n_octaves = 0.0; 

  if (distance_cm >= RANGE_START_CM && distance_cm <= RANGE_END_CM)  // distance within-range
  {
    n_octaves = (distance_cm - RANGE_START_CM) / CM_PER_OCTAVE;
    returnFreq_Hz = RANGE_START_HZ * pow(2, n_octaves);
  }

  return returnFreq_Hz;
}

int main() {
  const int TARGET_MEASUREMENT_DURATION_MS = 40; // Duration for a sampling rate of 25Hz
  const int N_MEASUREMENTS = 10*25;
  const int WAVE_CHANNEL = 0;
  
  int measurementDuration_ms = -1; // Stores the duration of a single measurement
  float distance_cm = -1.0; // Stores the value of a single measurement
  
  mstime_start(); // Initialize an mstimer.h milisecond timer
  
  for(int i = 0; i < N_MEASUREMENTS; i++){
    mstime_reset();
  
    distance_cm = measureDistance_cm();

    square_wave(PIEZO_SPEAKER_PIN_NO, WAVE_CHANNEL, distanceToFreq_Hz(distance_cm));

    measurementDuration_ms = mstime_get();
    
    //print("%d\n", measurementDuration_ms);
    
    pause(TARGET_MEASUREMENT_DURATION_MS - measurementDuration_ms);
  }
  
  square_wave_stop();
  mstime_stop(); // Frees resourecs associated with the timer
  
  return 0; // Report "No Error"
}  