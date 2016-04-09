This example will show you how to stream random values from 1 to 255. This values will be then used in the Particle to control the LED connected to the PWM pin (D0).

# Protocol description

Each value is separated by a `,`. The example bellow shows the data that will be sent by NodeJS to the Particle.

`1,10,50,100,150,183,300,322,1000,50`

The Particle code will be saving the data in a buffer and change the LED brightness only after detecting the separator.

# Schematic

- Particle
- LED
- Resistor

![raw sockets led](https://raw.githubusercontent.com/davidgatti/IoT-Raw-Sockets-Examples/assets/raw_sockets_led.png)
