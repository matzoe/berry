#ifndef _SONAR_H_
#define _SONAR_H_
// not thread-safe
#include <wiringPi.h> // -lwiringPi
#include <string.h>
#include "alarm.h"

#define SONAR_OPENED(sonar) (sonar->status == 1)
#define SETTLE_TIMEOUT 5000L // 5ms
#define FIRE_DURATION 10 // 10us
// #define BUF_LEN (1024*2)

typedef struct sonar {
  int pin_trig;
  int pin_echo;
  int status;
} sonar_t;

typedef struct value {
  int data;
  unsigned int timestamp;
} value_t;

/*
  -1        -> sonar not ready
  0         -> time out (not used now)
  positive  -> normal value
*/
inline int read_sonar(sonar_t* sonar/*, long timeout*/) {
  if (SONAR_OPENED(sonar)) {
    digitalWrite(sonar->pin_trig, LOW);
    delayMicroseconds(SETTLE_TIMEOUT);
    digitalWrite(sonar->pin_trig, HIGH);
    delayMicroseconds(FIRE_DURATION);
    digitalWrite(sonar->pin_trig, LOW);
    unsigned int start = micros();
    unsigned int now;
    while(digitalRead(sonar->pin_echo) != HIGH) start = micros();
    while(digitalRead(sonar->pin_echo) != LOW) now = micros();
    return (int)(now - start);
  }
  return -1;
}

inline int read_sonar_buf(sonar_t* sonar, value_t* buffer, int size) {
  if (SONAR_OPENED(sonar)) {
    struct timespec duration;
    memset(&duration, 0, sizeof(duration));
    duration.tv_nsec = 100;
    memset(buffer, 0, sizeof(value_t) * size);
    int count = 0;
    digitalWrite(sonar->pin_trig, LOW);
    delayMicroseconds(SETTLE_TIMEOUT);
    digitalWrite(sonar->pin_trig, HIGH);
    delayMicroseconds(FIRE_DURATION);
    digitalWrite(sonar->pin_trig, LOW);
    while(count < size) {
      buffer[count].data = digitalRead(sonar->pin_echo);
      buffer[count].timestamp = micros();
      ++count;
      nanosleep(&duration, NULL);
    }
    int j = 0;
    while(buffer[j].data == 0 && j < size) j++;
    int k = j;
    while(k < size && buffer[k].data == 1) k++;
    if (j < k && k < size) {
      return (int)(buffer[k].timestamp - buffer[j].timestamp);
    }
    return -1;
  }
}

inline int open_sonar(sonar_t* sonar) {
  if (!SONAR_OPENED(sonar)) {
    pinMode(sonar->pin_trig, OUTPUT);
    pinMode(sonar->pin_echo, INPUT);
    sonar->status = 1;
  }
  return 0;
}

inline int close_sonar(sonar_t* sonar) {
  if (SONAR_OPENED(sonar)) {
    pinMode(sonar->pin_trig, INPUT);
    pinMode(sonar->pin_echo, INPUT);
    sonar->status = 0;
  }
  return 0;
}

#endif // _SONAR_H_
