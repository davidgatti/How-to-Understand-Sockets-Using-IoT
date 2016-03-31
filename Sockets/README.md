In this two folders you'll find the most basic examples that try to show how to get, and send data over a socket connection over TCP and UDP. Where TLS is TCP but with security on top.

The NodeJS folder of course has the code in JavaScript, where the Particle one have code written in C++ specific for Particle.

How can C++ be specific to just one device? Because in this case I'm using classes that are specific for Particle. For example the TCPClient is a implementation of sockets made by Particle. Depending on your device you’ll have to use something else, but still similar in its working.
