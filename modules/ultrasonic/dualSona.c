#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#define TRIGGER_PIN1 17
#define ECHO_PIN1    27
#define TRIGGER_PIN2 18
#define ECHO_PIN2    22
#define TIMEOUT 999 /* any value other than LOW or HIGH */

int waitforpin(int pin, int level, int timeout) {
   struct timeval now, start;
   int done;
   long micros;
   gettimeofday(&start, NULL);
   micros = 0;
   done=0;
   while (!done) {
      gettimeofday(&now, NULL);
      if (now.tv_sec > start.tv_sec) micros = 1000000L; else micros = 0;
      micros = micros + (now.tv_usec - start.tv_usec);
      if (micros > timeout) done=1;
      if (digitalRead(pin) == level) done = 1;
   }
   return micros;
}

double fireSensor(int trig, int echo) {
   int pulsewidth;
   pinMode(trig, OUTPUT);
   pinMode(echo, INPUT);
   int timeElapse = 0;
   int validCount = 0;
   for (int i = 0; i < 10; i++) {
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
            printf("echo at %d micros\n", pulsewidth);
            timeElapse += pulsewidth;
            ++validCount;
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
   }
   if (validCount > 0) {
      return ((double)timeElapse)/validCount;
   }
   return -1.0;
}

int main (int argc, char const *argv[]) {
   if (wiringPiSetupGpio () == -1) {
      fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno)) ;
      return 1 ;
   }
   double cost = fireSensor(TRIGGER_PIN1, ECHO_PIN1);
   if (cost > 0) {
      printf("Time: %.1f\tDistance: %.1f\n", cost, cost*343/2/10000);
   }
   cost = fireSensor(TRIGGER_PIN2, ECHO_PIN2);
   if (cost > 0) {
      printf("Time: %.1f\tDistance: %.1f\n", cost, cost*343/2/10000);
   }
}

