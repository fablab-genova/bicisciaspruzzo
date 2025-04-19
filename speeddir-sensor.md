[<-- back to main readme <--](readme.md)
# Speed and direction sensor

This module is used to measure the speed and direction of the bike. It uses two encoders, one on each wheel, to determine the speed and direction of rotation. The signal of every encoder goes to the esp32 via 2 lines each (A and B). The esp32 uses the A signal to determine the direction of rotation and the B signal to determine the speed. The speed is calculated by measuring the time between two pulses of the A signal. The direction is determined by checking if the A signal is high or low when the B signal goes high.

## Purposes

The purpose of this module is to provide the speed and direction of the vehicle in order to:

- avoid printing while the bike is not moving, is moving backward, is moving too fast or too slow;
- print curved text while the bike is turning;
- print straight text while the bike is going straight;

## Features

The module has the following features:

### mandatory

- 2 encoders (one for each wheel)
- resolution: at least 12 bit
- max speed: at least 60 rpm
- connectivity: CLK, DT, GND, VCC

### nice to have

- resolution: more than 12 bit
- max speed: at least 120 rpm
- connectivity: I2C

## State of the art

At first we gonna try to hack a bike magnetic tachometer so we will just have one pin per wheel and no info about direction

### Existing solutions

No existing solutions were found yet that meet the requirements OR a description of what we found that works

### Products / Components

Put here details on components as if it was a BOM

## Limitations

- The maximum speed of the bike while printing is limited by the speed of the encoders. An example is an encoder with a maximum speed of 60 rpm and a resolution of  xxx gives a maximum speed of yyy m/s on a bike with zzz inches rims

## Schematics

Put here the schematics of the module. It may be a diagram that shows how the module is connected to the other modules and to the system. It may not be a complete schematic of the system, but it should display the main components and their connections.

## Documentation

Fell free to document everything here