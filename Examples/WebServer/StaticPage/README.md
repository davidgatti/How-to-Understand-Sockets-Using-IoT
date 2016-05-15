If you've ever wondered how routers and other network devices have their own built in "web servers", wonder no more. This example will explain how this works.

By now you should know that sockets are not scary, and protocols are just rules. Knowing this, serving a web page (some text) to a browser involves nothing more than listening on port 80 with a socket, and when a client connects to our Particle, we just send back a stream of text.

The code in this folder will show you that the only thing you have to do is to "build" a header (don't confuse the word build with something hard), which is nothing more than specific lines of text that tell the browser what to expect and how to interpret the message.

**One important thing to remember**: The header is separated from the "body" with an empty line.
