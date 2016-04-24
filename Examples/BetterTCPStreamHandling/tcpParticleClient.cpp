TCPClient client;

int analogPin = A0;
int port = 1337;
byte server[] = { 192, 168, 0, 72 };

void setup() {

    // Initialize the Serial
    Serial.begin(9600);

    // Connect to the remote server
    if(client.connect(server, port)) {

        Serial.println("Connected");


    } else {

        // if we can't connect, then we display an error.
        Serial.println("error");

    }

}

void loop() {

    // Lets read the value of our potentiometer.
    int val = analogRead(analogPin);

    // set the type of data that we want to send. The Particle documentation have
    // listed all the types.
    client.print(val, BIN);

    // Send the separator
    client.print(',');

    // Display in the terminal what did we send.
    Serial.println(val);

    delay(100);

}
