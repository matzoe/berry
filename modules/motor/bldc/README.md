# Variable Speed Brushless DC Motor

[View Original](http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1523)

## Overview
Key characteristics of the Variable Speed Brushless DC Motor: 

- Synchronous, external commutation
- No brush noise, durable, robust 
- Flat speed versus torque characteristics
- Position/Speed Servo

## How it works:
The Brushless DC motor does not operate directly off a DC voltage source. The
Brushless DC motor has a rotor with permanent magnets, a stator with windings
and commutation that is performed electronically. Typically three Hall sensors
are used to detect the rotor position and commutation is performed based on Hall
sensor inputs. The DC Brushless motor is clean, fast and efficient, and creates
no sparks, making it a safer choice in explosive environments. The linear
current/torque relationship results in smoother acceleration. In sensorless
control, back EMF zero crossing is used for commutation. This motor type has
a longer life than Brushed DC motors.

## Typical requirements for Variable Speed Brushless DC Motors:

**Input**:

- Typically torque, speed, position, and/or direction
- Inputs can be analog voltage, potentiometer, switches, or digital
communications

**Control**:

- Basic I/O for firmware bit-bang for 6-step
- 3 phase PWMs for hardware PWM
- Comparators for speed sensing in sensorless control, over-current detection
- Capture/Compare/PWM or input captures for speed sensing

**Feedback**:

- Hall-effect sensors, optical encoder, tachometer, or back-EMF voltage

**Driver**:

- 3 phase Inverter

## Application Notes

- [AN857](http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1824&appnote=en012037) Brushless DC Motor Control Made Easy
- [AN885](http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1824&appnote=en012127) Brushless DC (BLDC) Motor Fundamentals
- [AN894](http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1824&appnote=en012139) Motor Control Sensor Feedback Circuits
- [AN898](http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1824&appnote=en012138) Determining Your MOSFET Driver Needs for Your Motor Drive Application
- [AN899](http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1824&appnote=en012145) Brushless DC Motor Control Using PIC18FXX31
- [AN901](http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1824&appnote=en019525) Using the dsPIC30F for Sensorless BLDC Control
- [AN957](http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1824&appnote=en021551) Sensored BLDC Motor Control Using dsPIC30F2010
- [AN970](http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1824&appnote=en022169) Using the PIC18F2431 for Sensorless BLDC Motor Control
