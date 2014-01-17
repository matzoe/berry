# LED Clock using Raspberry Pi

[View
Original](http://www.doctormonk.com/2012/08/led-clock-using-raspberry-pi.html)

Tuesday, August 7, 2012


Okay, so if you were going to make a simple LED 4 digit clock, you
probably wouldn't start with a Raspberry Pi.

[![](http://1.bp.blogspot.com/-G4WC7HjvjjI/UCD8qs8a20I/AAAAAAAABC0/JokK1ACuVGs/s1600/clock+web.jpg)](http://1.bp.blogspot.com/-G4WC7HjvjjI/UCD8qs8a20I/AAAAAAAABC0/JokK1ACuVGs/s1600/clock+web.jpg)

But I wanted to test out I2C on the Pi and Adafruit's I2C LED displays
looked like a good bet. I also used a level converter to convert the
Pi's 3.3V I2C to the 5V I2C required by the LED module.

 To recreate what I have done here you will need:
 * Raspberry Pi
 * [Cobbler](http://adafruit.com/products/914)
 * [4-digit 7 segment display and Backpack](https://www.adafruit.com/products/880)
 * [Level Converter](https://www.adafruit.com/products/757)
 * Breadboard
 * Jumper wires

## Hardware
Connect up your Cobbler header as shown below. This is easier without the ribbon cable in place.

[![](http://2.bp.blogspot.com/-gNnUjOHC3aM/UCD_BdyB35I/AAAAAAAABC8/nbA5cyKtgAY/s640/cobbler+web.jpg)](http://2.bp.blogspot.com/-gNnUjOHC3aM/UCD_BdyB35I/AAAAAAAABC8/nbA5cyKtgAY/s1600/cobbler+web.jpg)

If you cannot make out the connections, they are:
 * Cobbler GND to Level Shifter GND to Display GND
 * Cobbler 5V to Level Shifter HV to Display VCC
 * Cobbler 3.3V to Level Shifter LV
 * Cobbler SDA0 to Level Shifter A1 (orange)
 * Cobbler SCL0 to Level Shifter A2 (yellow)
 * Level Shifter B1 to Display SDA (orange)
 * Level Shifter B2 to Display SCL (yellow)


## Software
I had to do the following to get I2C to work, following the instructions here:

```bash
sudo apt-get install python-smbus
sudo apt-get install i2c-tools (usefull but not essential)
sudo modprobe i2c-dev
sudo modprobe i2c-bcm2708
```

To simplify the process of using the display, I have created a Python library modelled on the Adafruit library for Arduino. You can download this from [here](http://code.google.com/p/i2c7segment/downloads/list) and then cd into the extracted folder and do:

```bash
 sudo python setup.py install
```

The clock program is included in the library as `clock_example.py`:

```python
import i2c7segment as display
import time

disp = display.Adafruit7Segment()

while True:
    h = time.localtime().tm_hour
    m = time.localtime().tm_min
    disp.print_int(h * 100 + m)
    disp.draw_colon(True)
    disp.write_display()
    time.sleep(0.5)
    disp.draw_colon(False)
    disp.write_display()
    time.sleep(0.5)
```

For those looking for more information about the library, then just browse through the file `i2c7segment.py`, the methods are documented.

For more information about the display itself, including the segment
mapping can be found at this [useful thread](http://forums.adafruit.com/viewtopic.php?f=47&t=29897).

