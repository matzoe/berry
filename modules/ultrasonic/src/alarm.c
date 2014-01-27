#include "alarm.h"
#include <time.h>
#include <signal.h>

timer_t set_alarm(long timeout, long interval, void(*handler)(int)) { // time unit: us
  timer_t timer;
  struct itimerspec nv = {0};
  struct itimerspec ov = {0};
  nv.it_value.tv_nsec = 1000L * timeout;
  nv.it_interval.tv_nsec = 1000L * interval;
  struct sigaction action = {0};
  action.sa_handler = *handler;
  if (sigaction (SIGALRM, &action, NULL) == -1) {
    perror("sigaction");
  }
  if (timer_create(CLOCK_MONOTONIC, NULL, &timer) == -1) {
    perror("timer_create");
  }
  if (timer_settime(timer, 0, &nv, &ov) == -1) {
    perror("timer_settime");
  }
  return timer;
}

void clear_alarm(timer_t timer) {
  if (timer_delete(timer) == -1) {
    perror("timer_delete");
  }
}