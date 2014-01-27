#ifndef  _ALARM_H_
#define _ALARM_H_
#include <time.h> // -lrt

timer_t set_alarm(long timeout, long interval, void(*handler)(int));
void clear_alarm(timer_t timer);

#endif //_ALARM_H_