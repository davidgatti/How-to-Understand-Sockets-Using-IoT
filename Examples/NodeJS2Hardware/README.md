This example will show you how to stream random values from 1 to 255. This values will be then used in the Particle to control the LED connected to the PWM pin (D0).

# Protocol description

A full set of bytes is separated by a `:`, and the set can contain max 3 characters.

This is an example of the data that will be sent by NodeJS.

`23:54:67:255:1:72`

# Schematic

![raw sockets led](https://raw.githubusercontent.com/davidgatti/IoT-Raw-Sockets-Examples/assets/raw_sockets_led.png)
