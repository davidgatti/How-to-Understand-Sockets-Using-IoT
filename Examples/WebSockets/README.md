![WebSockets Movie](https://github.com/davidgatti/IoT-Raw-Sockets-Examples/blob/assets/webSockets.gif)

This directory contains another example of a partial implementation for a standard protocol. In this case we are implementing the WebSocket one. Of course we are not implementing the whole thing, since there are already other developers who have done the hard work. Here, we'll focus only on sending data from our Particle to the browser to prove again that the big word protocol shouldn't be treated as something scary. 

We are also going to attach a potentiometer to our Particle, and send the values from the Particle to the Browser.

# Differences

By now, you should be comfortable with sockets; you open a connection and start sending data. With WebSockets, the situation is bit different. 

- First, make a handshake to let the browser switch in to Socket mode. The purpose of this is to prevent a caching proxy from re-sending a previous WebSocket conversation.
- Once the socket mode is on, you need to send your data with a header to let the browser know how it should interpret the data. 

# First things first: The handshake

To make the browser happy, we need to send back a hashed Key that the browser sends us. To do so, we need to do the following:

- Find the Key from the header (HTTP style header)
- Append a fixed, non-changing GUID to the key
- Hash the new string with SHA1
- Take the SHA1 hash and convert it to base64
- And, finally, send it back

There's lots of fun learning to do here, so please take the time and go over the singKey() function. I added a comment for each line to help you thoroughly understand each step.

# Sending data

From previous articles, you know that sockets are just a way to send a blob of data to another place. The other side needs to know how to interpret this data; as you know, this is called a protocol. And if you are building your own solution, you decide how the protocol should be designed. 

Here, we're sending the data to a browser, so the browser needs a little bit of context to know how to interpret the data that’s receiving, as follows: 

- Indicate whether what we're sending is the final data (yes, in most cases) 
- Set the data type (in this case, UTF-8 data)
- Indicate how much data will be sent (ASCII size if we are sending text)
the actual payload

The method sendData() has the code for this, with detail comets explaining each line of code.

In the example code, you’ll also see that we use the write() and print() methods to talk with the browser. The write() method is used to send binary data as is. Whereas the print() method converts the data to ASCII (maps each integer to the corresponding ASCII character) making it possible for the browser to display our numbers straight on the page.

If you want to learn all of the details about the packet, check the official page for the [WebSocket standard](https://tools.ietf.org/html/rfc6455#section-5.2).

# WebSocket is actually a mix of the UDP and TCP standards

If you haven’t already, visit the Templates section to learn about how UDP and TCP differ. But the gist is the following:

- **UDP** is a packet system; you chop your data in to these small packets and send it over the wire with no idea whether the data got to the other side or not. 
- **TCP**, on the other hand, is a stream protocol. It has a built-in system to make sure the data gets to the other end. The data will be also fragmented by the protocol itself, and you have no control over this.

The WebSocket standard requires that you send data in a packet style, where you have to chop your information, thus having that one “bit” at the beginning of the header that I mentioned above. But then this packed will be sent over the wire in a TCP fashion, ensuring that it will make it to the other end. 

Yes, it is a weird way of doing this, but this is how developers designed it.

This shows that you can mix different approaches in your own protocol, nobody will stand in the way of your taking advantage of things others have created before you.
