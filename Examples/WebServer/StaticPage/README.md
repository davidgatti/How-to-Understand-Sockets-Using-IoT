If you ever wonder how routers and other network devices have their own built in "web server" wonder no more. This example will explain how this works.

By now you should know that sockets are not scary, and protocols are just rules. Knowing this, serving a web page (some text) to a browser is nothing more then listening on port 80 with a socket, and when a client connects to our Particle, we just send back a stream of text.

The code in this folder will show you that the only thing you have to do, is to "build" a header (don't confuse the word build with something hard), which is nothing more then specific lines of text, telling the browser what to expect, how to interpret the message, and the message (body) itself.

**One important thing to remember**: the header is separated by the "body" with an empty line.