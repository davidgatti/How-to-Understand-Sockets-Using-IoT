TCPClient client;

int led = D0;
int port = 1337;
byte server[] = { 192, 168, 1, 100 };

void setup() {

    // Set the pin mode
    pinMode(led, OUTPUT);

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

    char tmp[3];
    int charPosition = 0;

    // While there is data in the buffer, lets read it.
    while(client.available()) {

        char c = client.read();

        // Check if we reached the end of the data
        if(c == ',') {

            // use the accumulated value
            pData(tmp);

            // Reset
            tmp[0];
            charPosition = 0;

        } else {

            // Save char in to the temp array
            tmp[charPosition] = c;

            // Increment the position of the array
            charPosition++;

        }

    }

}

void pData(char* data) {

    // Print out each char that we get
    Serial.printf("%d\n", string2int(data));

    // Set the value to the LED
    analogWrite(led, string2int(data));

}

// Convert an array of characters in to an int
int string2int(const char *s) {

    int res = 0;

    while (*s) {

        res *= 10;
        res += *s - '0';
        *s++

    }

    return res;

}
