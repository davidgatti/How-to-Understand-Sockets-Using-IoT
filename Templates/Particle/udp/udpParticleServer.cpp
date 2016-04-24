UDP Udp;

void setup() {

    Udp.begin(1337);

    // Print your device IP Address via serial
    Serial.begin(9600);
    Serial.println(WiFi.localIP());

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

    // Set the destination
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

    // Send the message
    Udp.write("I am the server sending you a message.");

    // Close the socket
    Udp.endPacket();

}
