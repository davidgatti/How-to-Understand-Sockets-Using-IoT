This code example will teach us something very important when it comes to coding: what happens when our minds go in to over drive, and start to overthink a solution.

The idea was to show how to send lots of data with the wrong assumption, that we'll have to chop our data ourselves. Turns out we don't need to do that, and the solution is just to send everything in one go.

# Story

I created this folder, and called it Big because when I started experimenting with sending more then 1KB of data, I was getting lots of errors. I was basically getting extra random ASCII characters. This made me thing that there is an issue in sending lots of data with the `.print()` function. I decided to split the data in to chunks manually and call `.print()` for each chunk. Check the first [commit](https://github.com/davidgatti/IoT-Raw-Sockets-Examples/blob/e3f3a4055e7dfdb4363621efe0afdb4c28d40deb/Examples/BigMessageParticle2NodeJS/tcpParticleClient.cpp) - lots of code was created.

But this didn’t solve the problem since I was getting the same extra characters. By accident I stumbled upon this [thread](https://community.particle.io/t/electron-tcpclient-write-issue/21819) on the Particle forum which made me realize that there is another method for sending data: `.write()`. I replaced the method and everything worked.

After few hours I came to realize, why not delete all the code that I wrote and just make one call passing all the data and see if it will be handle by the system. Sure enough - it worked. And all the code that I wrote became useless.

# The epiphany

I knew that the TCP is a stream protocol, meaning you can't control how the data will be send. The network card decides when, and how to send data. You can send 10 bytes, and receive on the other end 10 messages, or 2 with 5 bytes each, etc. Meaning chopping your own data won't do any difference.

My confusion came with the `.print()` method, which in the Particle implementation have issues sending lots of data in one go reliably. After discovering the existence of the `.write()` method I assumed that everything works thanks to size management that I put in place. Only later my brain slapped me in the face, and put me back on track.

This is called learning, and deleting code is called adapting :)

# Print vs. Write

The big question is, why `.print()` have such a issue handling lots of data? Right now I have no idea. But the major difference between the two is that: `.write()` can only handle a character array, known also as a buffer, which is nothing more then a chunk of memory used to hold data (in this case ASCII chars).

Where with `.print()` you can pass char, byte, int, long, or strings which will be sent as a sequence, each an ASCII character. This is useful if you need to send different types of data. Check the [Example](https://github.com/davidgatti/IoT-Raw-Sockets-Examples/tree/master/Examples) folder for more examples how to use `.print()`.

- `.print()`: use this method to small send sensor data
- `.write()`: use this method if you need to sends lots of text like a web page
