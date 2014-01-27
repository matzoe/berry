#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

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

typedef struct value {
  int data;
  int timestamp;
} value_t;

int main (int argc, char const *argv[]) {
  struct timespec duration;
  duration.tv_sec = 0;
  duration.tv_nsec = 100;
  if (wiringPiSetupGpio () == -1) {
    fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  value_t* buffer = (value_t*)malloc(sizeof(value_t) * BUF_LEN);
  int count, j, k, rnd = 0;
  for (; rnd < ROUNDS; ++rnd) {
    memset(buffer, 0, sizeof(value_t) * BUF_LEN);
    count = 0;
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(1000L);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    while(count<BUF_LEN) {
      buffer[count].data = digitalRead(ECHO_PIN);
      buffer[count].timestamp = micros();
      ++count;
      nanosleep(&duration, NULL);
    }
    j = 0;
    while(buffer[j].data == 0 && j < BUF_LEN) j++;
    k = j;
    while(k < BUF_LEN && buffer[k].data == 1) k++;
    if (j < k && k < BUF_LEN) {
      double cost = (double)(buffer[k].timestamp - buffer[j].timestamp);
      fprintf(stderr, "[%.2d] %d %d    %.fus  %.1fcm\n", rnd, j, k, cost, cost * SPEED_OF_SOUND);
    } else{
      fprintf(stderr, "[%.2d] ----\n", rnd);
    }
  }
  free(buffer);
  return 0;
}

