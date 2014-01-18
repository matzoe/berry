# (Howto) Walz a Hard Drive Spindle Motor

[View Original](http://letsmakerobots.com/node/2898)

By [rik](http://letsmakerobots.com/node/1836 "rik") @ November 10, 2008

an example of a driver for a brushless DC motor without microcontroller

Time to build: 1 hour

Cost to build: $9

-   Control method: [open loop](http://letsmakerobots.com/taxonomy/term/1790), [no
    feedback](http://letsmakerobots.com/taxonomy/term/1791)
-   CPU: [none](http://letsmakerobots.com/taxonomy/term/17)
-   Power source: [4x AA NiMH](http://letsmakerobots.com/taxonomy/term/1351)
-   Sensors / input devices: [none](http://letsmakerobots.com/taxonomy/term/164)
-   Target environment: [ex hard drives](http://letsmakerobots.com/taxonomy/term/1792)

[![](http://letsmakerobots.com/files/imagecache/robot_fullpage_header/field_primary_image/hdd_close.jpg)](/files/field_primary_image/hdd_close.jpg?)

 

|Attachment|Size|
|----------|----|
|[3pulses_l293d_big.gif](http://letsmakerobots.com/files/3pulses_l293d_big.gif)|24.92 KB|
|[3phase_pulsegenl293d.sch](http://letsmakerobots.com/files/3phase_pulsegenl293d.sch)|92.71 KB|



This is a continuation of my [blog](http://letsmakerobots.com/node/2876) on the same subject.
Please continue your commenting here.

 

* * * * *

 

I am the proud owner of a stack of scavenged hard drives. I hoped to
find really fast, torqueless motors inside. But instead I found myself a
project for my [new found 555 knowledge](http://letsmakerobots.com/node/2861).

The logic chip
[74164](http://en.wikipedia.org/wiki/List_of_7400_series_integrated_circuits)
is a "Serial In Parallel Out bit shift register"
([datasheet](http://www.datasheetcatalog.org/datasheets/270/387544_DS.pdf "pdf")).
S1 acts as a reset button. S2 is the little white wire in the video that
"boots" the sequence. Once one serial pulse makes it into the 74164, the
system will maintain the sequence. When the pulse reaches the third
output (red), diode D1 feeds it back to the first (green).

 

![](http://letsmakerobots.com/files/userpics/u1069/3phase_pulsegen_500mono_0.png)

 

The motor driver is the well known [L293D](http://letsmakerobots.com/taxonomy/term/127). The
circuit with the driver is much simpler:

![](http://letsmakerobots.com/files/userpics/u1069/3pulses_l293d.png)

The EN/able pins apparently do not need pulling down to work. The three
diodes D2, D3, D4 only serve to cut a tiny 0.7 V off the voltage. That
keeps the current maintainable for the driver chip (rated at max. 1.0 A
continues duty). I tried lowering the motor's voltage supply, but the
driver would not separate the two supplies very well, when I did. It
works OK when V-motor is higher than V-logic. Not the other way around.

The video lasts as long as 10 minutes. Oh, and you'd better take your
sea sickness medicine! The video compression kills any details, so here
is a closeup of the experiment as demonstrated.

![](http://letsmakerobots.com/files/userpics/u1069/hdd_vid_setup.jpg)

![](http://letsmakerobots.com/files/userpics/u1069/hdd_bread_close.jpg)

## Avenues of improvement

It has been suggested (by [oddbot](http://letsmakerobots.com/node/2876#comment-10123) and
[robologist](http://letsmakerobots.com/node/2876#comment-10137)) that the shape of these
square/block wave can be improved upon. Advantages include higher
rotational speeds or power efficiency.

![](http://letsmakerobots.com/files/userpics/u1069/3pulses_diagrams.jpg)

Also the control method can be improved a lot. Removing the need for a
manual boot up and automatic ramping up of the speed.

Furthermore a decent feedback mechanism could make the driver much more
intelligent. Two main alternatives remain to be inestigated: *external
feedback* (e.g. hall effect or optical sensing) telling a processor
about the state of the entire system, or *internal feedback* (e.g.
voltage detecting on any of the motor's coils when it is not being
fired) which in turn could help the exact firing of the next (round of)
pulses. That could even help gradually ramping up (or down) the speed.

## Practical issues

Finding the right leads. In this picture, I soldered in the wires shown.
I also chose the colour coding to be like the international colour
convention of traffic lights. Nothing to do with reggae or rasta.

![](http://letsmakerobots.com/files/userpics/u1069/hdd_wiring.jpg)

Just as in a stepper motor, measure the resistance through the coils. In
the above diagram any coil from a coloured wire to the "black center"
would be a very low resistance: somewhere between 0.5 and 1.5 Ohm. You
need a reasonably good multimeter (M-thingey) in order to get an
accurate measurement. And some patience.

The resistance through any connection from a colour to a colour would be
about twice as much.

## The bottom line

You're probably better off using a microcontroller after all!

* * * * *
