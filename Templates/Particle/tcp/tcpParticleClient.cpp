TCPClient client;

int port = 1337;
byte server[] = { 192, 168, 1, 100 };

void setup() {

    Serial.begin(9600);

    // Connect to the remote server
    if(client.connect(server, port)) {

        // Sedn the followign message to the server
        client.print("I am the client sending you a message.");

    } else {

        // if we can't connect, then we display an error.
        Serial.println("error");

    }

}

void loop() {

    // While ther is data in the buffer, lets read it.
    while(client.available()) {

        // Read each singel char
        char c = client.read();

        // Print out each char that we get
        Serial.print(c);

        // When we red the last byte, we can disconect from the server.
        if(client.available() == 1) {

            client.stop();

        }

    }

}
