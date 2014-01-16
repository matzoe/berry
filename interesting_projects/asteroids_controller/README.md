# Asteroids Controller with Raspberry Pi
By Bio, timbartlett.net [View Original](http://timbartlett.net/asteroids-pi)
August 15th, 2013

The 1979 arcade version of Atari Asteroids is a beautiful thing.

A white triangle battles lethal polygons on the glowing phosphors of a vector display. The two-note pulse of the music is syncopated by the "pew pew pew" of your effort to stay alive. The controls are as minimal as the graphics, and yet the game itself is complex, never the same twice.

I am a fan.

Years ago, I [wired up parts from a scrapped Asteroids machine](http://timbartlett.net/asteroids-controller-backstory/) to control a computer via USB. It's a beast. So when I had access to the resources at NYU's ITP Camp, I decided to learn some new tools and make a refined desktop version. This one is designed for a tiny Raspberry Pi computer running an arcade machine emulator (MAME), so all you need to provide is power in and audio/video out.

[![Asteroids
Pi](http://timbartlett.net/wp-content/uploads/2013/08/AsteroidsPi_beauty.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/AsteroidsPi_beauty.jpg)

I've included links to design files throughout this page - be sure to open the PDFs in a program that can handle layers. Or, here's a zipped folder with all the files in one place:

[DesktopAsteroidsPlans.zip](http://timbartlett.net/downloads/DesktopAsteroidsPlans.zip)

### The Design

First up, I made vector artwork of the Atari Asteroids control panel by tracing a photo in Illustrator. (I'd actually done this a few years ago for a different project).

[![measuring](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/05_measurement.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/05_measurement.jpg)

[![Asteroids Control
Art](http://timbartlett.net/wp-content/uploads/2013/asteroids/06_AsteroidsControlArt.png)](http://timbartlett.net/wp-content/uploads/2013/asteroids/06_AsteroidsControlArt.png)

[asteroids\_controls.pdf](http://timbartlett.net/downloads/asteroids_controls.pdf) (editable PDF)

[asteroids\_controls\_cs3.ai](http://timbartlett.net/downloads/asteroids_controls_cs3.ai.zip) (Illustrator file)

I decided how small the face could be and still have a comfortable layout, and how tall the controller needed to be to house all the components. From there I sketched up the basic design, and started fabrication with the frame.

### The Frame

The acrylic faceplate wraps around 3/4" plywood end caps, which are connected with two 1.5" x .5" plywood rails.

The end pieces have 3/8" grooves for the acrylic and rails. The CNC machine (robot miller) carved these first, before making a deeper pass to cut the outer shape.

[CNC\_asteroids\_sides.pdf](http://timbartlett.net/downloads/CNC_asteroids_sides.pdf)

[![CNC1](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/11_CNC1.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/11_CNC1.jpg)

[![CNC2](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/12_CNC2.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/12_CNC2.jpg)

[![CNC3](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/13_CNC3.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/13_CNC3.jpg)

That done, it needed some good old cabinet art. I made a black and white vector image from the original arcade marquee, and etched that with the laser cutter in raster mode.

[asteroidsmarquee\_BW\_vectors.svg](http://timbartlett.net/downloads/asteroidsmarquee-BW-vectors.svg)

[LASER\_asteroids\_sideart.pdf](http://timbartlett.net/downloads/LASER_asteroids_sideart.pdf)

[Image link: marquee
art](https://picasaweb.google.com/lh/photo/4Jlo-NlGg3uRbFXfCC0krg)
 [Image link: screen bezel
art](http://www.mikesarcade.com/arcade/artwork/asteroids_bezel.pdf)

![marquee](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/14_asteroidsmarquee.jpg)
 [![sides
etched](http://timbartlett.net/wp-content/uploads/2013/08/15_sidesetched.jpg)](http://timbartlett.net/wp-content/uploads/2013/08/15_sidesetched.jpg)

Finally, I carved out the rails with a table-mounted router. Nothing computer-driven here, but I did make a diagram. The slots are for removable acrylic shelves.

[![SHOP\_asteroids\_rails](http://timbartlett.net/wp-content/uploads/2013/asteroids/17_SHOP_asteroids_rails.png)](http://timbartlett.net/downloads/SHOP_asteroids_rails.pdf)

### The Faceplate

I used 1/4" clear acrylic for the faceplate to show off the components. The control panel file has layers for raster etching (the artwork) and vector cutting (edges and button holes) with a laser cutter. The plans are flopped so the art is etched on the inside.

There are also 3 shelves that slide into the grooves in the wood. The smaller ones have mounting holes for a breakout board and terminal.

[LASER\_asteroids\_faceplate.pdf](http://timbartlett.net/downloads/LASER_asteroids_faceplate.pdf)

[LASER\_asteroids\_shelves.pdf](http://timbartlett.net/downloads/LASER_asteroids_shelves.pdf)

[![LASER\_asteroids\_faceplate](http://timbartlett.net/wp-content/uploads/2013/asteroids/07_LASER_asteroids_faceplate.png)](http://timbartlett.net/wp-content/uploads/2013/asteroids/07_LASER_asteroids_faceplate.png)

[![cut acrylic](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/08_cutacrylic.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/08_cutacrylic.jpg)

ITP has a large strip heater for bending acrylic. I heated up the laser-cut piece along one seam, holding it just above the heater. I flipped it over every minute or so to heat it evenly and prevent warping or blistering.

[![bending acrylic](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/09_bendingacrylic.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/09_bendingacrylic.jpg)

Eventually it was soft enough to flex slowly. I put the shorter edge on the table, and holding the sheet evenly, pressed it forward. Holding a piece of wood along the seam helped start the crease straight. I had to re-heat the fold throughout the process, using the heater on the outside and a heat gun along the inside.

I matched the folds to the curve of the plywood end pieces. There was eyeballing involved. It's not perfect but it's secure, shiny, and strong.

[![bent acrylic](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/10_bentacrylic.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/10_bentacrylic.jpg)

[![assembled1](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/16_assembled1.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/16_assembled1.jpg)

### Assembly and Wiring

I finished the wood with Briwax and glued it all together. The faceplate's curved shape is enough to hold it in place, but it's still easy to remove by lifting up on the front edge.

I wired up the buttons with quick disconnects and it looked like this:

[![final](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/18_final.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/18_final.jpg)

[![21\_final](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/21_final.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/21_final.jpg)

The buttons are from an original Asteroids arcade machine, so they're the old leaf switch type. You can't get much simpler: a spring-loaded plunger presses two pieces of metal together. This was standard in arcade games until the mid-1980s, when they were replaced with micro-switches. The leaf switch is easier for rapid-fire and finesse. The micro-switch is more compact and goes "click."

[![24\_final](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/24_final.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/24_final.jpg)

I scrounged my old buttons at [Vintage Arcade Superstore](http://www.vintagearcade.net/) in Glendale, California. The leaf switch buttons were meant for a thin metal plate, and just barely fit around the 1/4" acrylic. A major supplier of new parts is [Suzo-Happ](http://na.suzohapp.com/gaming_products/pushbuttons/).

I also got two original cone-shaped Atari start buttons. They're supposed to blink when you insert a coin, but the old parts box I went through didn't have any with working lights.

A micro-switch inside a hole on the front signals that a coin's been inserted.

[![25\_final](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/25_final.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/25_final.jpg)

I wired the buttons to a small [Perma-Proto Raspberry Pi Breadboard](http://www.adafruit.com/products/1171) from Adafruit (details below), which was mounted to the acrylic shelf with 1/4" standoffs. I also ran wires to a terminal on the other end, in case I ever want to attach the buttons to something other than a Raspberry Pi.

[![19\_final](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/19_final.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/19_final.jpg)

[![20\_final](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/20_final.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/20_final.jpg)

When it's all put together, the Raspberry Pi computer sits on the large center shelf, with access for video, audio, and power cables running out the back.

[![26\_final](http://timbartlett.net/wp-content/uploads/2013/asteroids/500/26_final.jpg)](http://timbartlett.net/wp-content/uploads/2013/asteroids/full/26_final.jpg)

### Raspberry Pi

The [Raspberry Pi](http://www.raspberrypi.org/) is a tiny, inexpensive ($30 or $40, depending on the model), project-friendly Linux computer that came out in early 2013.

Adafruit has an [excellent tutorial on setting up a Raspberry Pi to play classic arcade games](http://learn.adafruit.com/retro-gaming-with-raspberry-pi/overview), written by Phillip Burgess. It leads you through setting up a RasPi from scratch, installing a MAME (Multi Arcade Machine Emulator), and getting arcade buttons to work.

I modified the button wiring plan to suit the Asteroids controls. The buttons are wired to the RasPi like this:

*Raspberry Pi pin, Asteroids function*

	 #17, Hyper-Space
	 MOSI (GPIO 10), Thrust
	 MISO (GPIO 9), Right
	 #23, Fire
	 #24, insert coin
	 #25 (GPIO 25), Left
	 #4 (GPIO 4), Two Players
	 CE1 (GPIO 7), One Player
	 GND, ground rail

And I changed the appropriate lines of the "retrogame" utility code to
this:

```c
struct {
        int pin;
        int key;
} io[] = {
//        Input    Output (from /usr/include/linux/input.h)

        {  17,      KEY_SPACE     },
        {  10,      KEY_LEFTALT     },
        {  9,      KEY_RIGHT     },
        {  23,      KEY_LEFTCTRL     },
        {  24,      KEY_5     },
        {  25,      KEY_LEFT     },
        {  4,      KEY_2     },
        {  7,      KEY_1     }
};
```

Instructions for doing this are in the tutorial.

At some point I might add two more internal switches to trigger KEY\_ESC and KEY\_ENTER, to quit and shutdown (using an alias/shortcut) with just the controller.

I had a bit of trouble getting the MAME ROM (game file) to work. In the end, I had to unzip the Asteroids Rev. 2 folder, change the file extensions so the names matched the missing file names that the MAME asked for, re-compress the folder, and put that zipped file into the roms folder on the RasPi. The MAME complains that two of the files are funky, but it seems to run fine.

Finally, once everything was working, I set the RasPi to boot directly into Mame4All when it's turned on. [Instructions are here](http://www.raspberrypi.org/phpBB3/viewtopic.php?f=78&t=41472). Since everything is stored on a cheap SD card, I have one dedicated to Asteroids.

### Hello World, Goodbye Asteroid

It works!

I mainly built this to learn some new tools. Maybe next I'll learn Python and write a new game for five buttons, or maybe I'll use it to run live visuals.

As for now, it's time to break out a projector and throw a rooftop Asteroids party.

For more Asteroids love, check out [AtariAsteroids.net](http://www.atariasteroids.net). (I run the site. Like I said, I'm a fan).

