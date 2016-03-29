TCPServer server = TCPServer(1337);
TCPClient client;

void setup() {

  // start listening for clients
  server.begin();

  // Make sure your Serial Terminal app is closed before powering your device
  Serial.begin(9600);

  Serial.println(WiFi.localIP());

}

void loop() {

    if (client.connected()) {

        client.write("I am the server sending you a message.");

        while(client.available()) {

            char c = client.read();
            Serial.print(c);

        }

    } else {

        client = server.available();

    }

}
