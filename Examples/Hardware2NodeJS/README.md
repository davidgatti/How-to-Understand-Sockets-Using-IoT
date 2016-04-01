In each folder you will find exactly the same example with minor differences. This way it will be way simpler to understand what’s going on.

The folder names are self explanatory. Binary means we are converting our data to binary, where the Char folder shows that we will convert first our data into a UTF8 representation, meaning int zero, will become 30, and then this data will be converted in to binary. Etc.

You can read more about types on the home page of the project.

# Protocol description

Each voltage value is separated by a `,`.

This is an example of the data that will be sent by NodeJS.

`1,10,50,100,150,183,300,322,1000,50`

# Schematic

![raw sockets led](https://raw.githubusercontent.com/davidgatti/IoT-Raw-Sockets-Examples/assets/raw_sockets_potentiometer.png)
