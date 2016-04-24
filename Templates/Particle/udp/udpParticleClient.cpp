UDP Udp;

char buffer[39] = "I am the client sending you a message.";

IPAddress remoteIP(192, 168, 1, 100);
int port = 1337;

void setup() {

    // Set the port which to use for contacting us back
    Udp.begin(8888);

    // Send the message to the server
    if (Udp.sendPacket(buffer, 39, remoteIP, port) < 0) {

        Particle.publish("Error");

    }

}

void loop() {

    // First we need to parse before we can check availability.
    Udp.parsePacket();

    // While there is data, we display it.
    while(Udp.available()) {

        // Read first char of data received
        char c = Udp.read();

        // Print all the char one by one.
        Serial.print(c);

    }
}
