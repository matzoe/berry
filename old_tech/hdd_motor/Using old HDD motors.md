# Using old HDD motors

[View Original](http://home.clear.net.nz/pages/joecolquitt/0hdd.html)

 Hard drives have high-speed low-profile motors that can be re-used.
More often than not it's the logic board that fails in a hard drive and
the motors are OK

 This is a simple program for a PIC16F84 that changes the bit pattern
for switching the FET coil drivers. The most important part of this
program is the table of values stored in the EEPROM, because this
pattern sets the phase relationships between the FETs and consequently
the voltage waveforms that the coils see. The oscillator speed of the
PIC is not important in this particular program as the changes are being
instigated by an external clock. 

 The motor needs to be started at a low speed (less than about 6
revs/second) and slowly accelerated to the final required speed. You can
hear this acceleration as a rising whine in a working drive in a PC when
it powers up after being shut down. If the final speed is always to be
the same then a routine could be written in the micro that slowly
decreases the interruption of a timer loop to accelerate the motor from
low power-up speed to final speed. 

 Hard drives with this motor usually run at 3000rpm (50 revs/second)
when working in a PC, but the speed can be set anywhere from a few
revs/sec up to about 55 rps, at which point the motor will not be able
to keep up with the driving wave and stop. At 12V the torque is not too
bad, and the bolt holes that are used to attach the platters can be used
to fix a pulley or gear wheel for a step-down motion drive. Other uses
could be spinning a propellor clock, fan, or sensor. At 5V supply the
motor will still spin at the same speed as it would at 12V (because it's
being driven by a frequency) but has very low torque. It will not
self-start at 5V. Current consumptions are: 

	12V 10rps (600rpm) 200mA
	12V 50rps (3000rpm) 110mA
	5V 10rps (600rpm) 40mA
	5V 50rps (3000rpm) 20mA
 
 The motor should be mounted on a heatsinking chassis to help keep it
cool if run for extended periods. The FETs (rated at 0.7A to 1.1A) will
normally run cool

 **Download [HDD motor
driver](http://home.clear.net.nz/pages/joecolquitt/hddmotor.zip)**


* * * * *

 ![](http://home.clear.net.nz/pages/joecolquitt/hddmotor.jpg)
 Typical HDD motor (Shinano Tokki Corp or Sankyo from a Conner CP3010)


```asm
;hddmotor.asm - driver for 3-coil HDD motor
;13/12/2000

;Look for external clock on a3 and change FET-driving bit pattern

clock equ porta.3 ;i/p clock

;EEPROM bit patterns

ee1 dbee 24h ;100 100
ee2 dbee 36h ;110 110
ee3 dbee 12h ;010 010
ee4 dbee 1bh ;011 011
ee5 dbee 09h ;001 001
ee6 dbee 2dh ;101 101

index rb ;RAM byte for counter

setup

movlw 08h
tris porta
movlw 00h
tris portb
movlw 80h
option
clrf index
movlw 24h
movwf portb

clocklo ;main loop

btfss clock ;wait for ext clock to go high
goto clocklo

change ;

movf index,w ;get next bit pattern from EE
movwf eeadr
call readee
movwf portb

incf index,f
movlw 06 ;loop for 6 EE locations
xorwf index,w
btfss zero
goto clockhi
clrf index

clockhi ;

btfsc clock  ;wait for clock low
goto clockhi
goto clocklo ;next clock, next pattern

readee ;get next pattern

bsf rp0
bsf rd
bcf rp0
movf eedata,w
return
```


![](http://home.clear.net.nz/pages/joecolquitt/hdddrive.gif)
![](http://home.clear.net.nz/pages/joecolquitt/hddfetdrives.gif)


## Other useful bits in hard drives

![](http://home.clear.net.nz/pages/joecolquitt/hddparts.jpg)

 One of the things disks can be used for is making wind chimes. Below is
a picture of some in my stash recovered from various drives. From top to
bottom in the pile are 65mm, 95mm and 130mm disks. Under that is a
picture of the two types of finishes. On the left is the older red
copper and on the right is the newer bronze, which can be anything from
light smokey brown to almost black. Both are very smooth and reflective.
The bronze ones tend to be thinner and so have a better ring, whereas
the red copper ones have more of a clungy bell sound. The best way to
hang either is to have minimal contact by forming a wire "V" for the
disk to sit in. The "V" has a flat at the bottom of it at least as wide
as the thickness of the disk. Doing this allows the disk to vibrate
freely, more so for a disk that's suspended close to the centre hole.
Either 4, 5 or 6 disks can be hung from threads or wires (shown here
using some enamelled wire scavenged from an old TV choke) and allowed to
swing into each other, or the disks can be hit by a centre clanger. Or
both if you want a lot of noise (personally I like my peace and quiet
and generally make them only for people who don't live near me !!) 


![](http://home.clear.net.nz/pages/joecolquitt/platters.jpg)
