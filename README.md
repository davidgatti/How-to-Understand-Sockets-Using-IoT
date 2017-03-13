![IoT Raw Sockets](https://raw.githubusercontent.com/davidgatti/IoT-Raw-Sockets-Examples/assets/iotrawsockets.jpg)

# The idea

I’m [David Gatti](https://twitter.com/dawidgatti), and my goal with this repository is to demystify Sockets. I’ll try to explain them in the simplest possible way.

In these examples, I’m going to use [NodeJS](https://nodejs.org/en/) and [Particle](https://www.particle.io) (any version will do) to show how hardware can talk with NodeJS, and vice versa. But make no mistake, this doesn’t mean the tools that I choose are the only way to go about this. This is what I personally know.

But any embedded device with network connectivity will work similarly, and any language with sockets support will also do.

The Repo Structure

- **Sockets folder**: Here you can find the simplest form of sockets examples. Files in this folder should help you understand how to use TCP, UDP, and TLS (NodeJS only for now). These are basically templates.
- Examples folder: Here you will find specific examples that provide more of a working solution for a specific problem.
    - **NodeJS2Hardware**: Using NodeJS to control an LED.
    - **Hardware2NodeJS**: Read values from an analog PIN, and stream the data to NodeJS. This example also explains how to send data as chars or binary.
    - **BetterTCPStreamHandling**: NodeJS buffers the received data until the END character is detected.
    - WebServer:
       - **StaticPage**: Learn how to turn your Particle into a web server.
       - **DynamicPages**: Learn how to turn your Particle into a web server with multiple pages.
       - **DynamicContent**: Learn how to turn your Particle in to a web server with dynamic content.

# The End Goal

I believe there is a large measure of mystery around network sockets. Many people have made them sound scary, and my goal is to prove that they aren’t that mysterious or complicated. I hope that in the end you are going to think about sockets as a simpler solution to a problem.

Especially in embedded systems, where every byte counts.

# What are Sockets

Sockets are the foundation for all network connectivity. Every connected device uses sockets. On top of sockets, you'll have protocols, which are nothing other than rules that specify how data should be sent or processed after it's received. The popular HTTP protocol is an example of this. Knowing this, you can mimic any device with any language that has Socket support. How? By sending bytes that adhere to specific protocols (rules). These rules are freely available online.

You could make an app that pretends to be a:

- Network printer
- DNS server
- FTP server
- SMTP server

Why do people believe Sockets are complicated?

Probably because people tend to use words that convey complexity, like:

- I’m **crafting** packets.
- It is the **lowest** software layer.
- I just sent the **right amount** of bytes.
- I’m **implementing** this protocol.

Just by reading these few points you might think, This is not for me. But Sockets are actually very straightforward. For example, to get a response from a web server, you just need to send the following text:

`GET/HTTP/1.1`

This is it. The server will take this text, parse it, and understand that you are making a:

- **GET request**: You want something from the server.
- **/**: is the root address of the site. Another example would be to write `/contact` to get the contact page.
- **HTTP/1.1**: Tells the server which HTTP version you can understand.

There isn’t much more to it. A printer will understand another header, similarly a DNS server will need something specific to its protocol (rules).

Hard to believe? Use a telnet app to connect to your favorite site using this command (only an insecure connection will be supported through port 80).

- telnet `SITE 80`
- Type `GET / HTTP/1.1`
- Press enter twice, and you’ll get the page.

For a secure connection, you can use openssl as follows:

- `Openssl s_client -connect google.com:443`
- Admire all the security that is going on.
- `GET / HTTP/1.1`
- Press enter twice. You’ll get the page.

Another example would be to send an email by connecting straight to a SMTP server. Most current SMTP servers are secured by passwords and use encryption, which makes it hard to quickly test this. But if you had access to a plain SMTP server, you could just type the following:

- `telnet example.com smtp`
- and type
- `HELO client.example.com`
- `MAIL from: <sender@example.com>`
- `RCPT to: <recipient@example.com>`
- `DATA`
- `From: sender@example.com`
- `To: recipient@example.com`
- `Subject: Test message`
- *empty space*
- This is my awesome message
- . *just a single dot to tell the server that we finished our message*
- `QUIT`

As you can see, this isn't 🚀🔬.

# How to Make Your Own Rules (Protocol)

Now that we have a better understanding of protocols, you’ll need to design a common structure for communication. Let's say you want to send the temperature of your house to your NodeJS server. Your stream of bytes could look like this:

`45,40.1,50,90,100,102.5`

The comma acts as the separator for each measurement. You can choose any character you want, but, just so you know, the comma will make your data compatible with the CSV (Comma Separated Values) format. Anyway, on the other end, you need some code that will check for the separator, and when that happens - you have your value.

As you can see from this example, there is no header or optional data. You decide what goes in your protocol.

Based on the example above, you could add humidity to your protocol, like this:

`45:80,40:85,32.1:82,50:89`

Again, the comma separates your data, while the colon differentiates your data set. Remember, protocols need good documentation, so other developers can make sense of them.

# Types - be aware of how you send your data.

Computers work in 1s and 0s, and this is a fact. There is no way for the example to distinguish a compiled application from regular data. Everything is stored as a series of bits. Meaning that even the data that is sent over the Internet is in 1s and 0s.

You are probably asking, then why should I care about types. Because depending on your type, your binary data will be different. For example: an integer of `1` will be `00000001`, where a char of `1v in UTF8 is `31`HEX, which will become `00110001`.

This means that, at the other end of the connection, you need to know what you're getting. Let's say you want to make a simple comparison.

    if(data == 1) {
        true
    }

If you converted your data as if it were an integer, but you sent it as a char, then you'll compare int 49 to int 1. But if you know that you're sending a character, you can compare it with the right type:

    if(data == '1') {
        true
    }

Now char 1 is actually 49, and the comparison will work. In the Hardware2NodeJS example folder, you'll find simple code that explains the difference in practice.

# Which one: TCP or UDP?

On the Internet, the two most popular protocols for sending data are TCP and UDP. You'll see that people add /IP at the end of the name. IP stands for (Internet Protocol), and, in short, you can think of it as the Internet's address system. This means that you can use TCP or UDP not only on the Internet, because TCP and UDP are the way the data is packaged, what address system you'll use is up to you.

TCP and UDP are protocols, and by now you should know that this word means rules, and these two protocols are nothing more than rules explaining how to package data. The other end understands the same rules, and can unpack the received information, and vice versa.

# Difference

- **TCP**: A stream of data that always arrives at the other end, no matter what. The rules say, if some data is lost during the transmission, resend it. This way you get high fidelity, "slower" speeds, and more data over all.
- **UDP**: Sends data as a standalone packet, because once the data is sent, there is no way to tell if it reached its destination. The rules here are: I'll send it, but I won't guarantee that you'll receive it. With this protocol you get faster speeds, because you're not wasting time resending lost data. Also, you're not sending information needed to determine whether anything was lost back to the source.

# Use cases

Most of the Internet uses TCP, because we want the assurance that what we send will be received in its entirety on the other end. For example, if you send a document, you don't want letters or words to be missing. With many formats, if parts are missing from the header, which tells the system how to understand the file, the system will inform you that the file is corrupted, and can't be read.

Of course, there are formats that are more resilient and don't need 100 percent of the data. Some movies, images, and music formats, for example, can have some content missing, and we just live with that. An image or movie might have some weird artifacts; music might have some blips and noises.

# When should I use UDP?

This protocol is very useful when sending data from hardware products. Lets say we are collecting sensor data from many devices, using a cellular modem, and we have to pay for each byte we send. In this case we should consider the following: Is it worth it to pay more for the higher fidelity we'd have with TCP? Or is it better to accept the loss of some measurements, but pay less for our data transfer?

Normally, I would default toward TCP, but if you have a good case against using it, UDP is your next best option.

# To sum it all up

I hope this repository helped you get a better understanding of what sockets are. If something was unclear, hit me up on [Twitter](https://twitter.com/dawidgatti), and I’ll try to fix any points in the project that are unclear.

# Thank you

I want to thank all of the good people who helped me with this project, including:

- [Tomasz Wątorowski](http://mightydevices.com): For helping me understand C even better.
- [Kenneth Lim](https://github.com/kennethlimcp): For helping me proof the content.

# My other projects

- [Simpe.li](https://simpe.li): which is a simple API for generating PDFs out of beautiful templates.
- [IoT Water Flow Meter](https://www.hackster.io/davidgatti/iot-water-flow-meter-4595ff?ref=user&ref_id=6416&offset=0): Measure the water consumption in your house with a Particle and water flow sensors.
- [IoT Garage Opener](https://www.hackster.io/davidgatti/garage-opener-591175?ref=user&ref_id=6416&offset=1): A non destructive basic garage opener
- [dgCam for Android](https://github.com/davidgatti/dgCam): Custom camera for Android created for testing, playing and learning.
