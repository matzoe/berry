#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#define ROUNDS 42
#define ROUNDS_LIMIT 100
#define TRIGGER_PIN1 17
#define ECHO_PIN1    27
#define TRIGGER_PIN2 18
#define ECHO_PIN2    22
#define TIMEOUT 999 /* any value other than LOW or HIGH */

int partition(int *a, int p, int r);
int random_partition(int *a, int p, int r);
int random_select(int *a, int p, int r, int i);

int waitforpin(int pin, int level, int timeout) {
  struct timeval now, start;
  int done;
  long micros;
  gettimeofday(&start, NULL);
  micros = 0;
  done = 0;
  while (!done) {
    gettimeofday(&now, NULL);
    if (now.tv_sec > start.tv_sec) {
      micros = 1000000L;
    }
    else {
      micros = 0;
    }
    micros = micros + (now.tv_usec - start.tv_usec);
    if (micros > timeout) {
      done = 1;
    }
    if (digitalRead(pin) == level) {
      done = 1;
    }
  }
  return micros;
}

int readSensor(int trig, int echo) {
  int pulsewidth;
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  int elapse[ROUNDS];
  int count = 0;
  int i = 0;
  while (1) {
    /* trigger reading */
    digitalWrite(trig, HIGH);
    waitforpin(echo, TIMEOUT, 10); /* wait 10 microseconds */
    digitalWrite(trig, LOW);

    /* wait for reading to start */
    waitforpin(echo, HIGH, 5000); /* 5 ms timeout */

    if (digitalRead(echo)  == HIGH) {
      pulsewidth = waitforpin(echo, LOW, 60000L); /* 60 ms timeout */

      if (digitalRead(echo) == LOW) {
        /* valid reading code */
        // printf("echo at %d micros\n", pulsewidth);
        elapse[count] = pulsewidth;
        ++count;
      }
      else {
        /* no object detected code */
        printf("echo timed out\n");
      }
    }
    else {
      /* sensor not firing code */
      printf("sensor didn't fire\n");
    }
    ++i;
    if (i > ROUNDS_LIMIT || (i > ROUNDS && count > ROUNDS / 2)) {
      break;
    }
  }
  if (count > 0) {
    return random_select(elapse, 0, count, (count + 1) / 2);
  }
  return -1;
}

int main (int argc, char const *argv[]) {
  if (wiringPiSetupGpio () == -1) {
    fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }
  int cost = readSensor(TRIGGER_PIN1, ECHO_PIN1);
  if (cost > 0) {
    printf("Time: %dus\tDistance: %.1fcm\n", cost, ((double)cost) * 343 / 2 / 10000);
  }
  // cost = readSensor(TRIGGER_PIN2, ECHO_PIN2);
  // if (cost > 0) {
  //   printf("Time: %d\tDistance: %.1f\n", cost, ((double)cost) * 343 / 2 / 10000);
  // }
}

int partition(int *a, int p, int r) {
  int x = a[r], t;
  int i = p - 1, j;
  for (j = p; j < r; j++) {
    if (a[j] <= x) {
      i++;
      t = a[i];
      a[i] = a[j];
      a[j] = t;
    }
  }
  t = a[i + 1];
  a[i + 1] = a[r];
  a[r] = t;
  return i + 1;
}

int random_partition(int *a, int p, int r) {
  int i = p + (int)((r - p + 1) * rand() / (RAND_MAX + 1.0));
  // exhange a[r] <-> a[i]
  int t = a[i];
  a[i] = a[r];
  a[r] = t;
  return partition(a, p, r);
}

int random_select(int *a, int p, int r, int i) {
  if (p == r) {
    return a[p];
  }
  int q = random_partition(a, p, r);
  int k = q - p + 1;
  if (i == k) {
    return a[q];
  }
  else if (i < k) {
    return random_select(a, p, q - 1, i);
  }
  else {
    return random_select(a, q + 1, r, i - k);
  }
}

