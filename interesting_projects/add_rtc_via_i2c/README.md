# How to add a RTC to the Raspberry Pi via I2C

By Drew Fustini, www.element14.com [View Original](http://www.element14.com/community/community/raspberry-pi/blog/2012/07/19/what-time-is-it-adding-a-rtc-to-the-raspberry-pi-via-i2c)
July 18th, 2012

*UPDATE: Adafruit shows how to interace with the DS1307 RTC without a level converter in their [Adding a Real Time Clock to Raspberry Pi](http://learn.adafruit.com/adding-a-real-time-clock-to-raspberry-pi) tutorial*

Yesterday, I described how to access the Raspberry Pi's [serial console](http://www.element14.com/community/community/raspberry-pi/blog/2012/07/18/look-ma-no-display-using-the-raspberry-pi-serial-console) via the GPIO header. Another capability that can accessed from that header is the I2C bus. I2C stands for Inter-Integrated Circuit and is common serial bus for chips to talk to each other. Although not written for the Pi, [Tronixstuff's Arduino and the I2C bus](http://tronixstuff.wordpress.com/2010/10/20/tutorial-arduino-and-the-i2c-bus/) is a good introduction to how the bus works. Here's a short video from NXP that the tutorial highlights:

[Video](https://www.youtube.com/watch?feature=player_embedded&v=BcWixZcZ6JY)

Unlike most computers, the Pi lacks a [real-time clock](http://en.wikipedia.org/wiki/Real-time_clock) (or RTC). This means the Pi doesn't know what time it is when powered on. If connected to a network, then the Pi could retrieve the current time from a time server (referred to as NTP). Another option is to connect an external real-time clock to the Pi via the I2C bus. I already had a [DS1307 Real Time Clock breakout board kit](http://adafruit.com/products/264) from Adafruit:

[![](http://www.adafruit.com/images/medium/ds1307rtc_MED.jpg)](http://www.adafruit.com/images/medium/ds1307rtc_MED.jpg)

However, the DS1307 operates at 5V and requires a logic level converter to safely connect to the Pi's 3.3V I2C pins. Furthermore, since I2C is bi-directional, a logic level converter should be choosen which explicitly states it will work with I2C. I choose [Adafruit's 4-channel I2C-safe Bi-directional Logic Level Converter](https://www.adafruit.com/products/757):

[![](http://www.adafruit.com/images/medium/ID757_MED.jpg)](http://www.adafruit.com/images/medium/ID757_MED.jpg)

From the [eLinux wiki](http://elinux.org/RPi_Low-level_peripherals), the GPIO header pinout show the I2C lines are on GPIO 0 (SDA) and GPIO 1 (SCL):

[![GPIOs.png](http://www.element14.com/community/servlet/JiveServlet/downloadImage/38-8788-115218/GPIOs.png)](http://www.element14.com/community/servlet/JiveServlet/showImage/38-8788-115218/GPIOs.png)

SDA is the Serial Data line, and SCL is the Serial Clock line. Here is a photo of the RTC board connected via the logic level shifter to the Pi:

[![20120714\_034608.jpg](http://www.element14.com/community/servlet/JiveServlet/downloadImage/38-8788-88218/620-465/20120714_034608.jpg)](http://www.element14.com/community/servlet/JiveServlet/showImage/38-8788-88218/20120714_034608.jpg)

*(From Left to Right: Adafruit 4-channel I2C-safe logic level converter, Adafruit DS1307 RTC board, <del>Adafruit 8-channel logic level converter</del> [unused], SparkFun logic level converter board [connected to FTDI cable for serial console])* 


| Raspberry Pi Pin  | Jumper Wire | Logic Level Converter: LV side (3.3V)| Logic Level Converter: HV side (5V) | Jumper Wire | DS1307 RTC |
| ----------------- |:-------:|:-----:|:-----:|:-----:|:-----:|
|3V3 Power|Red|LV|HV|Red|5V\*|
|Ground|Green|GND|GND|Black|GND\*|
|GPIO 0|(SDA)|Yellow|A3|B3|Yellow|SDA|
|GPIO 1|(SCL)|Blue|A4|B4|Blue|SCL|


***NOTE:*** The 5V FTDI cable provides 5V power to the DS1307. The DS1307 "5V" pin is connected to "VCC" on the 5V FTDI cable, and the DS1307 "GND" pin is connected to "GND" on the 5V FTDI cable. Alternatively, the DS1307 could instead be powered by the 5V pin on the Pi's GPIO header.

Here's a close up of the wiring:

[![20120715\_011650.jpg](http://www.element14.com/community/servlet/JiveServlet/downloadImage/38-8788-88219/620-465/20120715_011650.jpg)](http://www.element14.com/community/servlet/JiveServlet/showImage/38-8788-88219/20120715_011650.jpg)

*(From Left to Right: Adafruit 4-channel I2C-safe logic level converter, Adafruit DS1307 RTC board, TMP102 temperature senor [more info in a future post], SparkFun logic level converter board [connected to FTDI cable for serial console])*

I'll now turn my attention to the software side now that the wiring is
done. [bootc.net](http://www.bootc.net/) a terrific resource for I2C on
Pi. First, download the [bootc.net Debian Wheezy
image](http://www.bootc.net/archives/2012/07/01/updated-debian-wheezy-image/)
which includes v3.2 of the Linux kernel and I2C drviers. Boot the Pi
from that image and execute these simple commands from [I2C and the
Raspberry
Pi](http://www.bootc.net/archives/2012/05/19/i2c-and-the-raspberry-pi/)
(as root):

Register the DS1307 RTC chip with the I2C address of 0x68:

```bash
echo ds1307 0x68 > /sys/class/i2c-adapter/i2c-0/new_device
```

View the current date & time stored in the RTC:

```bash
hwclock -r
```

Set the Linux system time to the value in the RTC:

```bash
hwclock -s
```

Here's screenshots of the process:

[![20120714\_034405.jpg](http://www.element14.com/community/servlet/JiveServlet/downloadImage/38-8788-88220/620-464/20120714_034405.jpg)](http://www.element14.com/community/servlet/JiveServlet/showImage/38-8788-88220/20120714_034405.jpg)

[![20120715\_011535.jpg](http://www.element14.com/community/servlet/JiveServlet/downloadImage/38-8788-88221/620-464/20120715_011535.jpg)](http://www.element14.com/community/servlet/JiveServlet/showImage/38-8788-88221/20120715_011535.jpg)

These commands could be added to a startup script so that the Pi retrieves the current date/time from the RTC while booting up.

Finally, the DS3231 is a higher precision I2C RTC than the DS1307. The [ChronoDot](http://www.adafruit.com/products/255) by [Macetech](http://docs.macetech.com/doku.php/chronodot) features this chip. It also has the advantage of being able to operate at 3.3V, so a logic level converter isn't needed.


Cheers,
Drew
[http://twitter.com/pdp7](http://twitter.com/pdp7)
 
