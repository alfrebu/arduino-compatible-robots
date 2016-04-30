# Introduction #

Robots are becoming a common educational resource. Together with other applied science fields like wearable computing, or music instrument design, robotics provides an alternative door into traditional fields like math and physics, as well as into more contemporary ones like computer science and complex systems.

![http://farm5.static.flickr.com/4140/4771192383_70171970d8.jpg](http://farm5.static.flickr.com/4140/4771192383_70171970d8.jpg)

Part of the relevance of hybrid fields like robotics resides in their mixed nature. One can approach it from the mechanical, electronic, or purely software point of view. Robots can take many forms, it is possible to easily construct narratives around them.

## Oh\_Oh ##

**Oh\_Oh** is the result of an exploration in the possibilities of cheap educational electronics. It is very important to keep the importance of low cost as a fundamental part of the project, since that will influence its design, as well as its accessibility.

We created **Oh\_Oh** after a couple of basic workshops in electronics with Kids at FARO de Oriente in Mexico DF. Very early in the process we realized there was an interest in learning about robotics. The Computer Clubhouse counts with a couple of Lego kits, but not enough for a group of 20 kids.

We realized that Mexico has a couple of companies dedicated to designing, manufacturing and selling small robots. However they were not really complying with the idea of reprogramability and reusability of general electronics, due to a closed firmware and the lack of an IDE to easily reconfigure the robot's behavior.

The important aspect for us was that we could get access to all the parts needed to build a cheap robot on-site. And that we could then easily hook up this robot to Arduino and build from there. So we decided to go on with the idea of making our own robot with as little parts as possible.

### Briefly about FARO de Oriente ###

FARO is an art centre in the area of Iztapalapa, which happens to be one of the most populated municipalities in the world with over 3m inhabitants. At FARO it is possible to get an education in non-academic fields mostly related to arts and crafts. There is also a Computer Clubhouse donated by Intel as part of the Computer Clubhouse Village project initiated by MIT.

Participants in the Computer Clubhouse activities range from 10 to 18 years old. You can read more about the workshops we conducted [here](http://medea.mah.se/2010/06/arduino-intro-for-kids-at-faro/)

## Hardware ##

This robot has been built based on a study ran informally over time. We have been looking at robots for a while. We bought some, tried some, and learnt a lot about how to DIY. **Oh\_Oh** is the result of analyzing a bunch of different designs, and put them together on a single board.

### Asuro - a precendent ###

Back in 2006 Dave Mellis, from Arduino, had a workshop at _Ars Electronica Festival_. Then he used the robot called **Asuro**, created by the [Institute or Robotics and Mechatronics](http://www.dlr.de/rm/en/desktopdefault.aspx/tabid-3848/6062_read-9032/) at the German Aerospace Agency (DLR) and distributed by [Arexxx Engineering](http://www.arexx.com). No matter how much we liked the experience of playing with **Asuro** and how much we liked its name, it was far too complicated to mount. But it had a couple of nice details: the use of an inexpensive ping pong ball as front wheel, and the use of Arduino compatible processors.

**Asuro** was running on an ATmega8. This processor has 3 PWM enabled pins, which is enough to control up to three motors. Robots in the scale we are talking about here, don't require a huge intelligence and the memory space of the mega8 seems more than enough. Again, this is a very relevant issue, since the processors are not equally available around the world. E.g. in Mexico it is really hard to get almost any processors from _Atmel_, the only manufacturer of the mega8, but the ATmega8L, which works up to 8MHz, has an internal oscillator and comes in a the very convenient DIL-28 package.

Something that was making **Asuro** really hard to mount was that it had no integrated gear box. All the wheels and bars that integrated the gear box came unmounted, while it is possible to get those in a single inexpensive plastic molded box nowadays. On top of that, the robot had a lot of different sensors integrated in the first place. From an educational point of view, "too many" can become a problem. There is time when the statement _less is more_ makes a lot of sense, and this is one of them, in order to reduce complexity, but also cost.

### Imori Kits - the guy from Mexico ###

As mentioned earlier, one of the design constrains for this project was that it should be possible to find the pieces for this robot close the location where the workshop takes place. It is the intention that the technology should be available in order to enable the dissemination of the design.

A big part of the on-site research consisted in looking for local distributors of electronics, educational kits ... At some point in the process we identified a company ([Imori Kits](http://imorikits.com)) that was importing geared motors from China and manufacturing its own wheels to be included in robots they sell.

We got interested in one of their designs, a [three wheeled robot](http://imorikits.com/tienda/product_info.php?cPath=48&products_id=294) that seemed to be easy to hack using some sort of socket to adjust a DIL-16 processor to the DIL-28 from the mega8. We got a couple of those in our lab and mounted them, just to get to learn how it was to mount them. This robot didn't offer the possibility of reprogramming it in any way. It came with a pre-burn processor.

In order to control the motors, this design was avoiding the use of transistors, and in a clever move, included the H-bridge L293D that the Arduino community has been including in a lot of designs. This is a way of reducing the amount of space needed to integrate the robot, as well as simplifies it's construction.

On top of that, the **Imori Robot** doesn't have any sensors at all. It can be controlled via a small remote control unit and the robot's processor is ready to decypher the IR communication captured by a 1 Eur IR receiver. This is a huge difference to **Asuro**, which includes a whole lot of sensors on board.

### Design decisions ###

Taking all of the above mentioned aspects into account, the hardware design should include:

  * an ATmega processor, the design should allow using the mega8 pinout to control the motors, which means being careful where to place the PXM enabled pins
  * an H-bridge L293D, to control both speed and direction on the two DC motors that would drive the robot
  * two DC motors with gear boxes, and wheels that could be found in Mexico
  * a ping pong ball as the back wheel
  * there will be no sensors on board, they will be placed on a daughter board situated in front of the robot that we decided to call **nose** in the same way **Arduino** has got **shields**
  * there should be the possibility to mount a _shield for Arduino_ on top of the robot
  * the possibility to be programmed from Arduino's IDE (this affects the Software)
  * a button and some LEDs on board
  * a connection with the third PWM to allow easy connecting a servo
  * powered by 9V batteries


## Software ##

When it comes to software, there are three aspects to take into account:

  * how will the users program the robot, this is part of the user experience
  * which IDE is convenient for our scenario of use, how will the IDE interact with the software needed to command the robot
  * which are the possibilities to expand the system
  * what experiments are interesting for a newcomer in the ages from 10 to 18 years old with no prior experience in electronics or software, what can be engaging and informative at the same time

We don't think it is meaningful to spend a lot of time explaining the design decisions we have made regarding the IDE. We are constructing the system on top of the Arduino platform and there is a lot of information online regarding the advantages of using this IDE versus others. Mostly we like it for being cross-platform, easy to deploy, license free, and easy to integrate with the setup at the Computer Clubhouse at FARO.

Therefore, when it comes to discuss about the software, we have been concentrating in aspects that have to do with the user experience:

  * how will the kids program the robots
  * what experiments are interesting

### How will the kids program the robots ###

Since **Lego** launched their robotics platform, there is a lot of discussions going on about the advantages and disadvantages of using Visual Programming User Interfaces for creating and assigning behaviors to robots. Among the good things of VPUIs we find the lack of syntax errors, the ease of use, and the ease of understanding the system at one glance. Among the bad things, the problem they represent when trying to expand the system, the initial cost in developing the basic structure for it, and the lack of a common paradigm (robotics is a complex field, and Visual Programming is not very developed in terms of portability between systems).

There are some experiences in making possible to visually program Arduino:

  * the EU funded project EduWear created a layer on top of Arduino's IDE that aimed creating code in a similar fashion as **Scratch** does, it is called Amici and can be found (for MAC only) [here](http://dimeb.informatik.uni-bremen.de/eduwear/?p=495)
  * MAX/MSP presented at the conference Sketching in Hardware 2009 a prototype of a patch that can send code to Arduino as mentioned [here](http://www.philvanallen.com/news/sketching-in-hardware-2009/)
  * [ModKit](http://www.modk.it/) is an online platform to program Arduino from a browser, again based on the **Scratch** paradigm
  * a combination of Scratch + Serial Server as explained [here](http://transitlab.org/2010/arduino-in-schools)

Considering the time constrains we have for the first phase of the **Oh\_Oh** project (concept, prototype, first manufacturing run, and test with kids made in less than two months) we have decided that no matter how interesting VPUIs are, we are not going to even consider them. Moving into VP is a latter issue for us.

Therefore, the kids participating in our first test run will have to program the robots via code within the normal Arduino IDE. In order to make this as simple as possible, we have developed a library that covers the basic aspects of the robot's behavior. On top of that we have created a series of examples (see the following paragraph) that make use of this library.

### What experiments are interesting ###

This part of the documentation will be explained in depth at a different page where you will find pictures of each experiment as well as code. We are working on it as for 2010-07-12.

## Documentation ##

You can follow a visual diary of the prototypes at [this gallery](http://www.flickr.com/photos/dcuartielles/sets/72157624318825795/) and some videos at [this channel](http://vimeo.com/album/252666)

# Notes #

Contributors and how they were involved:
  * Xun Yang, Malmö University, Sweden: Master Student in Interaction Design, responsible for software and behavior creation for Oh\_Oh
  * Gianluca Martino, Arduino, Italy: Hardware responsible for Arduino, made the original hardware designs easy to manufacture
  * Tlacotalpan, México: inspired us with her infinite knowledge about how to name our robot
  * Alejandro Jimenez, México: runs the Computer Clubhouse at FARO and hosts the workshops with kids
  * Hugo, México: runs the paper sculpture workshops at FARO and designed the skull-covers for our robots
  * David Cuartielles, Arduino, Malmö University, Sweden: PhD. Candidate in Interaction Design, Oh\_Oh's project initiator, hardware designer and software instigator

Institutions and companies contributing to the project:
  * Centro Cultural de España en México: commissioned the project, special thanks to Eva Gómez for her endless support during the two years it took us to gather the funding
  * FARO de Oriente, México: hosts the Computer Clubhouse
  * Malmö University, Sweden: gave D. Cuartielles and X. Yang a workspace where to prototype the robot
  * Arduino LLC, USA: donated 15 Arduino Duemilanove boards to FARO in order to start the workshops with kids