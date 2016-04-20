![IoT Raw Sockets](https://raw.githubusercontent.com/davidgatti/IoT-Raw-Sockets-Examples/assets/iotrawsockets.jpg)

# The Why

I’m [David Gatti](https://twitter.com/dawidgatti), and my goal with this repository is to demystify Sockets. I’ll try to explain them in the simplest possible way that I can come up with.

In this examples I’m going to use [NodeJS](https://nodejs.org/en/), and [Particle](https://www.particle.io) (any version will do) to show how hardware can talk with NodeJS, and vice versa. But make no mistake, this doesn’t mean the tools that I choose are the only way to go about this. This is what I personally know.

But any embedded device with network connectivity will work similarly, and any language with sockets support will also do.

# The Repo Structure

- **Sockets folder**: here you can find the simplest form of sockets examples. Files in this folder should make you understand how to use TCP, UDP, and TLS sockets. This are basically templates.
- **Examples folder**: here you will find more specific examples that are more of a working solution that solves a specific problem.
   - **NodeJS2Hardware**: using NodeJS to control a LED
   - **Hardware2NodeJS**: read values from an analog PIN, and stream the data to NodeJS. This examples also explains how to send data as chars or binary.
   - **BetterTCPStreamHandling**: NodeJS buffers the received data until the END character is detected.
   - **WebServer**:
      - **StaticPage**: Learn how to turn your Particle in to a web server.
      - **DunamicPages**: Learn how to turn your Particle in to a web server with multiple pages.

# The End Goal

I believe there is a lot of mystery around network sockets. Many people made them sound scary, and my goal is to prove that they aren’t that mysterious, nor complicated. I hope that in the end you are going to think about socket as a simpler solution to your problem.

Especially in embedded systems where every byte counts.

# What are Sockets

Sockets are the foundation for all the network connectivity. Every connected device uses Sockets. On top of Sockets you have protocols, which are nothing else other than rules. Rules that specify how data should be sent or processed after receiving it. For example: the popular HTTP protocol.

Knowing this, you can mimic any device with any language that has Socket support. How? By sending bytes that adhere specific protocols (rules). This rules are are freely available on-line.

You could make an app that pretends to be a:

- Network printer
- DNS server
- FTP server
- SMTP server

# Why do you believe Sockets are Complicated?

Probably because people tend to use words that convey complexity, like:

- I’m **crafting** packets
- It is the **lowest** software layer
- I just send the right amount of **bytes**
- I’m **implementing** this **protocol**

Just by reading this few points you might think - this is not for me. But Sockets are actually very straight forward. For example, to get a repose from a web server, you have to just send the following text.

`GET / HTTP/1.1`

This is it. The server will take this text, parse it, and understand that you are making a:

- **GET request**: you want something form the server
- **/**: is the root address of the site. Another example would be to write `/contact` to get the contact page.
- **HTTP/1.1**: tells the server which version of the HTTP you can understand.

There isn’t much more to it. A printer will understand another header, similarly a DNS server will need something specific to its protocol (rules).

Hard to believe? Use a telnet app an connect to your favorite site using this command (only insecure connection will be supported through port 80)

- `telnet SITE 80`
- and type
- `GET / HTTP/1.1`
- then press enter twice. You’ll get the page.

For secure connection you can use `openssl` in the following way:

- openssl s_client -connect google.com:443
- *admire all the security that is going on*
- `GET / HTTP/1.1`
- then press enter twice. You’ll get the page.

Another example would be to send an email by connecting straight to a SMTP server. Nowadays most SMTP servers are secured by passwords, and use encryption which makes it hard to quickly test this. But if you had access to a plain SMTP server you could just type the following:

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

As you can see this isn't 🚀🔬.

# How to Make Your Own Rules (protocol)

Now that we have a better understanding of protocals. You’ll need to design a common structure for communicating. Lets say you want to send to your NodeJS server the temperature of your house. Your stream of bytes could look like this:

`45,40.1,50,90,100,102.5`

Where the `,` is the separator for each measurement. You can choose any character you want, but just so you know, the `,` will make your data compatible with the CSV (Comma Separated Values) format. Anyway, on the other end, you need some code that will check for the separator, and when that happens - you have your value.

As you can see from this example, there is no header, or optional data. You decide what goes in your protocol.

Based on this example above you could add humidity to your protocol like this.

`45:80,40:85,32.1:82,50:89`

In this case again, the `,` separates your set of data, where the `:` differentiate your data set. Remember, protocols need good documentation so other developers can make sense of them.

# Types - be aware how you send your data.

Computers work in 1 and 0s, and this is a fact. There is no way for example to distinguish a compiled application from regular data. Everything is stored as a series of bits. Meaning even the data that is sent over the internet is in 1 and 0s.

You are probably asking, then why should I care about types. Because depending on your type, your binary data will be different. For example: an integer of 1 will be `00000001`, where a char of 1 in UTF8 is 31, which will become `00011111`.

This means that at the other end of the connection, you need to know what are you getting. Lets say you want to make a simple comparison.

```
if(data == 1) {
    true
}
```

If you convert your data as if it was an integer but you sent it as a char, then you'll compare int 31 to int 1. But if you know that you are sending a character then you can compare it with the right type:

```
if(data == '1') {
    true
}
```

Now char 1 is actually 31 and the comparison will work. In the [Hardware2NodeJS example](https://github.com/davidgatti/IoT-Raw-Sockets-Examples/tree/master/Examples/Hardware2NodeJS) folder you'll find simple code that explains in practice the difference.

# Which one: TCP or UDP?

On the internet the two most popular protocols for sending data are TCP and UDP. You'll see that people write /IP at the end of the name. IP stands for (Internet Protocol), and in short, you can think of it as the address system of the internet. Meaning you can use TCP or UDP not only on the internet. TCP and UDP are the way the data is packaged, what address system you'll use is up to you.

Since TCP and UDP are protocols, by now you should know that this word means rules, and this two protocols are nothing more than rules explaining how to package data, so the other end which also understands the same rules, can unpack the received information and vice versa.

### Difference

- **TCP**: is a stream of data which will always arrive at the other end no matter what. Because the rules say, if some data will be lost during the transmission, resend it. This way you get high fidelity, "slower" speeds, and more data over all.
- **UDP**: sends data as a standalone packet, because once the data is sent, there is no way to tell if it reached its destination. The rules here are: I'll send it, but I won't guarantee that you'll receive it. With this protocol you get faster speeds because you are not waisting time resending lost data, and also you are not sending back to the source the information needed to know if something was lost.

### Use cases

Most of the internet uses TCP because we want the assurance that what we send will be revived on the other end. For example, if you send a document, you don't want letters or words to be missing. Many formats if they'll have missing parts of the header, which tells the system how to understand the file, the system will inform you that the file is corrupted, and can't be read.

Of course there are formats that are more resilient and don't need 100% of the data. Some movies, images, and music formats for example can have parts of its content missing, and you'll live with that. In the case of an image or movie, you'll have some weird artifacts. While in the case of music you'll have some blips and noises.

### When should I use UDP?

This protocol is very useful when sending data from hardware products. Lets say we are collecting sensor data from many devices, and we use a cellular modem where we have to pay for each byte we send. In this case we should consider the following: is it worth it to pay more for higher fidelity with TCP. Or can we accept some lost measurement but pay less for our data transfer?

Normally I would default towards TCP, but if you have a good case against it, UDP will be your best next option.

# To sum it all up

I hope this repository helped you better understand what sockets are. If something was unclear, hit me up on [Twitter](https://twitter.com/dawidgatti), I’ll try to fix the unclear part of this project.

# My other projects

- [Simpe.li](https://simpe.li): which is a simple API for generating PDFs out of beautiful templates.
- [IoT Water Flow Meter](https://www.hackster.io/davidgatti/iot-water-flow-meter-4595ff?ref=user&ref_id=6416&offset=0): Measure the water consumption in your house with a Particle and water flow sensors.
- [IoT Garage Opener](https://www.hackster.io/davidgatti/garage-opener-591175?ref=user&ref_id=6416&offset=1): A non destructive basic garage opener
- [dgCam for Android](https://github.com/davidgatti/dgCam): Custom camera for Android created for testing, playing and learning.
