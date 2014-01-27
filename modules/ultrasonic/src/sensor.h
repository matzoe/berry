#ifndef _SENSOR_H_
#define _SENSOR_H_
// not thread-safe
#include <wiringPi.h> // -lwiringPi
#include "alarm.h"

#define SENSOR_OPENED(sensor) (sensor->status == 1)
#define SETTLE_TIMEOUT 5000L // 5ms
#define FIRE_DURATION 10 // 10us
typedef struct sensor {
  int pin_trig;
  int pin_echo;
  int status;
} sensor_t;

/*
  -1        -> sensor not ready
  0         -> time out
  positive  -> normal value
*/
inline int read_sensor(sensor_t* sensor, long timeout) {
  if (SENSOR_OPENED(sensor)) {
    digitalWrite(sensor->pin_trig, LOW);
    delayMicroseconds(SETTLE_TIMEOUT);
    digitalWrite(sensor->pin_trig, HIGH);
    delayMicroseconds(FIRE_DURATION);
    // timer_t deadline = set_alarm(timeout, 0, );
    digitalWrite(sensor->pin_trig, LOW);
    unsigned int start = micros();
    unsigned int now;
    while(digitalRead(sensor->pin_echo) != HIGH) start = micros();
    while(digitalRead(sensor->pin_echo) != LOW) now = micros();
    int ret = (int)(now - start);
    if (ret < 0) {
      return 0;
    }
    return ret;
  }
  return -1;
}

// inline int read_sensor_n(sensor_t* sensor, int);

inline int open_sensor(sensor_t* sensor) {
  if (!SENSOR_OPENED(sensor)) {
    pinMode(sensor->pin_trig, OUTPUT);
    pinMode(sensor->pin_echo, INPUT);
    sensor->status = 1;
  }
}

inline int close_sensor(sensor_t* sensor) {
  if (SENSOR_OPENED(sensor)) {
    //
    sensor->status = 0;
  }
}

#endif // _SENSOR_H_