#include <wiringPi.h>
#include <pcf8591.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

double volts (int value)
{
        return value * 3.3 /255;
}

int main (void)
{
        if (wiringPiSetup() == -1)
                exit (1);
        printf("PCF8591 Setup: %d\n", pcf8591Setup(80, 0x48));

        pinMode (80, INPUT);
        pinMode (81, INPUT);
        pinMode (82, INPUT);

        for(;;)
        {
                printf ("%f      %f      %f\n", volts(analogRead(80)), volts(analogRead(81)), volts(analogRead(82)));
                delay(1000);
        }
        return 0;
}
