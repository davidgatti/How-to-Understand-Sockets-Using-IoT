![DynamicContentParticle](https://raw.githubusercontent.com/davidgatti/IoT-Raw-Sockets-Examples/assets/dynamicContent.png)

This example is the next step from the [Dynamic Page](https://github.com/davidgatti/IoT-Raw-Sockets-Examples/tree/master/Examples/WebServer/DynamicPages) example. This time we not only dynamically load pages based on the URL. We also change the HTML content on the fly with custom data. Here we add the time/date, and the IP address of Particle. In addition to that in the header of the home page I added one line that tells the browser to refresh the page every second, which will update the time on each refresh.

# Use case

The `replace()` method is very powerful, because it can replace any tag with your data. The only limit will be the amount of memory in your device. But until you have enough space, you can use this example to build your web server, and show stats from your various sensors.

# The inefficiency of the code.

The inefficiency of the code in this example is on purpose to make the code easier to understand. For example,

- on each request we get the IP of Particle even dough it never changes, and the code could be easily moved in the `setup()` method.
- The `output` variable have a fixed size of 400 bytes. In production hardware that would be unacceptable. But to know the end size of the replaced content I would have to add a new method to the project which would gives back the size of the new variable. This would  take to much time, and would make the whole idea of simple example pointless.
- The `replace()` could be shorter. Sadly once I finished working on it I realizes that i'd could have used the `strchr()` method from the `string.h` library. I didn't improve the code, because perfection is the enemy of release. I think it is better to release something that works, and later on work on efficiency if necessary.

# What this project is not

The idea of this repository is to teach about sockets and protocols by showing that this two technologies are easier to understand then you might think. This example is not a full fledged web server. It supports just a tiny fragment of the HTTP protocol. If you would like to have a full web server, check out the [Webduino](https://github.com/sirleech/Webduino)] project.
