In each folder you will find exactly the same example with minor differences. This way it will be way simpler to explain what’s going on.

The folder names are self explanatory:

- **Binary** means we are converting our data to binary, 
- where the **Char** folder shows how to convert our data into a UTF8 representation (`int 0`, will become `int 30`)

You can read more about types on the home page of the project.

# Protocol description

Each value is separated by a `,`. The example bellow shows the data that will be sent by Particle to the NodeJS app.

`1,10,50,100,150,183,300,322,1000,50`

Where the:

- values: are sent as integers.
- separator: is sent as a character.

This means that in the NodeJS app, we'll compare the separator to a char symbol. If the char is different from the separator, then we’ll save our 1 and 0s in a buffer until we’ll encounter the `,`. When you’ll see the code, you’ll understand what I mean.

# Schematic

- Particle
- Potentiometer (10K in my case)

![raw sockets led](https://raw.githubusercontent.com/davidgatti/IoT-Raw-Sockets-Examples/assets/raw_sockets_potentiometer.png)
