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

#define ROUNDS_LIMIT 100
#define SETTLE_TIMEOUT 5000L
#define TRIGGER_PIN1 17
#define ECHO_PIN1    27
#define TRIGGER_PIN2 18
#define ECHO_PIN2    22

static int deadline = 0;
struct timespec fire_duration = {0};

void set_deadline(int unused) {
  deadline = ( 1 == 1 );
}

int waitforpin(int pin, int bit, long timeout) {
  deadline = ( 1 == 0 );
  struct timespec start, now;
  if (clock_gettime (CLOCK_MONOTONIC, &start) == -1) {
    perror ("clock_gettime");
  }
  timer_t timer = set_alarm(timeout, 0, set_deadline);
  while (digitalRead(pin) != bit) {
    if (clock_gettime (CLOCK_MONOTONIC, &now) == -1) {
      perror ("clock_gettime");
    }
    if (deadline == ( 1 == 1)) {
      return -1;
    }
  }
  clear_alarm(timer);
  return ((long)(now.tv_sec - start.tv_sec))*1000000L + ((long)(now.tv_nsec - start.tv_nsec))/1000;
}

int readSensor(int trig, int echo, int rounds) { // rounds should be less than ROUNDS_LIMIT
  int pulsewidth;
  if (rounds <= 0) {
    rounds = 1;
  }
  if (rounds > ROUNDS_LIMIT) {
    rounds = ROUNDS_LIMIT;
  }
  int* elapse = (int*)malloc(rounds*sizeof(int));
  int ret = -1;
  int count = 0;
  int i = 0;
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  while (1) {
REDO:
    digitalWrite(pin, LOW);
    usleep(SETTLE_TIMEOUT);
    digitalWrite(pin, HIGH);
    if (nanosleep(&fire_duration, NULL) == -1) {
      perror("[Re-Fire:] nanosleep");
      goto REDO;
    }
    digitalWrite(pin, LOW);
    if (waitforpin(echo, HIGH, 5000L) != -1) {
      pulsewidth = waitforpin(echo, LOW, 60000L);
      if (pulsewidth > 0) {
        elapse[count] = pulsewidth;
        ++count;
      }
#ifdef DEBUG
      else {
        printf("echo timed out\n");
      }
#endif
    }
#ifdef DEBUG
    else {
      printf("sensor didn't fire\n");
    }
#endif
    ++i;
    if (i > ROUNDS_LIMIT || (i > rounds && count > rounds / 2)) {
      break;
    }
  }
  if (count > 0) {
    ret = median(elapse, count);
  }
  free(elapse);
  return ret;
}

int main (int argc, char const *argv[]) {
  if (wiringPiSetupGpio () == -1) {
    fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }
  fire_duration.tv_nsec = 10000L; // fire duration: 10us
  int cost = readSensor(TRIGGER_PIN1, ECHO_PIN1);
  if (cost > 0) {
    printf("Time: %dus\tDistance: %.1fcm\n", cost, ((double)cost) * 343 / 2 / 10000);
  } else {
    fprintf(stderr, "Failed to fire sona.\n");
  }
  // cost = readSensor(TRIGGER_PIN2, ECHO_PIN2);
  // if (cost > 0) {
  //   printf("Time: %d\tDistance: %.1f\n", cost, ((double)cost) * 343 / 2 / 10000);
  // }
}