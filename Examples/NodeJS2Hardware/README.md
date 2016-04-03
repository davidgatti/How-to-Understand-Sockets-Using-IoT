This example will show you how to stream random values from 1 to 255. This values will be then used in the Particle to control the LED connected to the PWM pin (D0).

# Protocol description

Each value is of type int and converted to binary, while being separated by a `,`, and this is an example of the data that will be sent by Particle to the NodeJS app.

`1,10,50,100,150,183,300,322,1000,50`

Where the:

- values: are sent as integers.
- separator: is sent as a character.

This means that on other side, in the NodeJS app, if we want to split the string, we will compare the separator to a char symbol. When you’ll check the code, you’ll see what I mean.

# Schematic

- Particle
- LED
- Resistor

![raw sockets led](https://raw.githubusercontent.com/davidgatti/IoT-Raw-Sockets-Examples/assets/raw_sockets_led.png)
