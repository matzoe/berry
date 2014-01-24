# HY-SRF05 Ultrasonic Distance Measurement sensor module.

## References

- [Raspberry Pi and monitoring sump pump water level](http://khekker.blogspot.com/2013/03/raspberry-pi-and-monitoring-sump-pump.html)
- [Ultra cheap ultrasonics with the HY-SRF05](http://rasathus.blogspot.co.uk/2012/09/ultra-cheap-ultrasonics-with-hy-srf05.html)
- [Ultra cheap ultrasonics with the HY-SRF05, Part 2.](http://rasathus.blogspot.co.uk/2012/09/ultra-cheap-ultrasonics-with-hy-srf05_27.html)


## Data Sheet

- [http://www.robotstorehk.com/sensors/doc/srf05tech.pdf](http://www.robotstorehk.com/sensors/doc/srf05tech.pdf)
- [http://www.fgcvme.co.uk/MUSRF05%20Data%20Sheet.pdf](http://www.fgcvme.co.uk/MUSRF05%20Data%20Sheet.pdf)

## Specifications

5-Pin, One each for VCC, Trigger, Echo, Out and Ground.

1. Voltage : DC5V 
2. Static current : less than 2mA 
3. Detection distance: 2cm-450cm 
4. High precision: up to 0.3c

## Notes

1. the module performance is stable, measure the distance accurately:
Can and SRF05, SRF02 ultrasonic distance measuring module and other comparable. Module precision, blind spots  (2cm) super close, stable ranging success of this product to market under the strong!

2. Main technical parameters:

    1. Voltage : DC5V
    2. Static current : less than 2mA
    3. level output: high-5V
    4. level output: the end of 0V
    5. Sensor angle: not more than 15 degrees
    6. Detection distance: 2cm-450cm
    7. High precision: up to 0.3cm

3. Connection: VCC, trig (control side), echo (receiving end), GND
 
4. Usage:
        10US a control population of more than a high-fat, you can wait to receive high output port. A timer can be opened with the output timing, when the port goes low when the timer value can be read this when the time for this distance, only calculate the distance. This constant cycle of measurement, you can reach the value of the mobile measurement ~ ~

5. Module works:

    1. The IO trigger location, the high signal to at least 10us;
    2. the module automatically sends eight 40khz square wave, automatically detects whether a signal return;
    3. a signal back, through the IO of a high output, high duration is Ultrasonic time from launch to return.
      Test distance = (time * High speed of sound (340M / S)) / 2;
 
