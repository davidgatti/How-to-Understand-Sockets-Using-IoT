TCPClient client;

int analogPin = A0;
int port = 1337;
byte server[] = { 192, 168, 1, 100 };

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

    int val = analogRead(analogPin);

    // No type set and the defautl one is char. Mening in this case our Int will
    // be converted to UTF8
    client.print(val);
    client.print(',');

    Serial.println(val);

    delay(100);

}
