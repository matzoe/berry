#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "sonar.h"

/*
  http://en.wikipedia.org/wiki/Speed_of_sound
  "In dry air at 20 °C (68 °F), the speed of sound is 343.2 metres per second (1,126 ft/s)."

  speed of sound in air: 343m/s
  [1us     -> 0.017cm]
  [5us     -> 0.085cm]
  [10us    -> 0.172cm] (* the chosen granularity)
  [100us   -> 1.715cm]
  [1000us  -> 17.15cm]
  [10000us -> 171.5cm]
  [20000us -> 343.0cm]
*/

#define TRIGGER_PIN 17
#define ECHO_PIN    27
#define BUF_LEN (1024*2)
#define SPEED_OF_SOUND 343 / 2 / 10000
#define ROUNDS 14

int main (int argc, char const *argv[]) {
  if (wiringPiSetupGpio () == -1) {
    fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }
  sonar_t sonar = {0};
  sonar.pin_trig = TRIGGER_PIN;
  sonar.pin_echo = ECHO_PIN;
  value_t* buffer = (value_t*)malloc(sizeof(value_t) * BUF_LEN);
  open_sonar(&sonar);
  int rnd, cost = 0;
  for (rnd = 0; rnd < ROUNDS; ++rnd) {
    cost = read_sonar_buf(&sonar, buffer, BUF_LEN);
    if (cost > 0) {
      fprintf(stderr, "[%.2d] %dus %.1fcm\n", rnd, cost, (double)(cost) * SPEED_OF_SOUND);
    } else{
      fprintf(stderr, "[%.2d] ----\n", rnd);
    }
  }
  for (rnd = 0; rnd < ROUNDS; ++rnd) {
    cost = read_sonar(&sonar);
    if (cost > 0) {
      fprintf(stderr, "[%.2d] %dus %.1fcm\n", rnd, cost, (double)(cost) * SPEED_OF_SOUND);
    } else{
      fprintf(stderr, "[%.2d] ----\n", rnd);
    }
  }
  free(buffer);
  close_sonar(&sonar);
  return 0;
}

