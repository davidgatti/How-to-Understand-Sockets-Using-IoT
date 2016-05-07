#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sha1.h"
#include "base64.h"

TCPServer server = TCPServer(80);
TCPClient client;

int handshakeDone = 0;
unsigned long oldTime = millis();
unsigned long interval = 300;
int analogPin = A0;

void setup() {

    // start listening for clients
    server.begin();

    // Make sure your Serial Terminal app is closed before powering your device
    Serial.begin(9600);

    // Show the device ID
    Serial.println(WiFi.localIP());

}

void loop() {

    // While the client is connected
    if (client.connected()) {

        // Run this code only after we went thru the initial hand shake with the browser.
        // If the hand shake happened we know the browser switched to Sockets.
        if(handshakeDone) {

            // calculate the amount of time passed since our last execution
            unsigned long difference = millis() - oldTime;

            // Execute the code only after a specific amount of time passed
            if(difference >= interval) {

                // Send Data
                sendData();

                // Update the time
                oldTime =  millis();
            }

        }

        ///
        /// While there is data to be red.
        ///

        int position = 0;
        char line[100]; // store all the char from the one line.

        // While data is available, read it.
        while(client.available()) {

            char c = client.read();
            line[position++] = c;

            // Look for the new line char which tells us that we reached the end of the line.
            if(c == 13) {

                // Replace new line char with the null termination one.
                line[position] = 0;

                // Reset the position for the next line
                position = 0;

                // Look for the Key
                int result = handshake(line);

                // If the Key was found, we can stop looking so we don't process unnecessary data.
                if (result) {

                    // Set the hand shake to TRUE so we can start sending data over a socket connection
                    handshakeDone = 1;
                    break;

                }

            }

        }

    } else {

        client = server.available();

    }

}

void sendData() {

    // Read analog value from the potentiometer
    int val = analogRead(analogPin);

    // Copy the value, since we are going to change it
    int copyVal = val;

    // Counting how many digits do we have in our int. We do this because the data alone,
    // needs to be sent in ASCII, meaning each digit will sent as a char, thus using
    // sizeof() won't give us the actual size that we are sending. For example 22, as an int
    // takes 4 bytes, but in ASCII it's 2 bytes.
    int intLen = 0;
    while(val != 0) {
        val /= 10; /* same as x=x/10 */
        ++intLen;
    }

    // Sending the header in binary so the browser will knows what it's getting
    client.write((uint8_t) 0x81);   // Txt frame opcode
    client.write(intLen);           // Length of data measured in single ASCII chars

    // Sending the data in ASCII
    client.print(copyVal);

}

int handshake(char line[100]) {

    // This is what we are looking for
    const char phrase[20] = "Sec-WebSocket-Key: ";

    // Look for the phrase with the Key
    char* found = strstr(line, phrase);

    // If something found
    if(found != 0) {

        // Create storage for out output
        unsigned char output64[29];

        // Start processing the Key for the response
        singKey(line, phrase, output64);

        // Send to the browser the signed Key
        client.write("HTTP/1.1 101 WebSocket Protocol Handshake\r\n");
        client.write("Connection: Upgrade\r\n");
        client.write("Upgrade: WebSocket\r\n");
        client.write("Sec-WebSocket-Accept: "); client.write((const char*) output64); client.write("\r\n");

        client.write("\r\n");

        return 1;

    }

    return 0;

}

void singKey(char line[100], const char phrase[20], unsigned char* output64) {

    // Fixed, non changing GUID
    const char guid[37] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

    ///
    /// 1. FIND THE KEY
    ///
    int lineLen = strlen(line);
    int phraseLen = strlen(phrase);
    int guidLen = strlen(guid);
    int whatIsLeft = lineLen - phraseLen;
    int destSize = whatIsLeft + guidLen;
    char dest[destSize];

    // Replacing the enter char with a null termination
    line[lineLen - 1] = 0;

    // Copy just the Key from the whole line.
    strncpy(dest, &line[phraseLen + 1], whatIsLeft);

    ///
    /// 2. Append GUID to the KEY
    ///
    strcat(dest, guid);

    ///
    /// 3. Hash the result using SHA-1
    ///

    unsigned char outputSHA1[22] = "";

    mbedtls_sha1((unsigned char *)dest, destSize-2, outputSHA1);

    outputSHA1[21] = 0;

    ///
    /// 4. Convert the hash in to Base64
    ///

    //number of bytes written
    size_t olen;

    // Convert String to Base64
    mbedtls_base64_encode((unsigned char *)output64, 29, &olen, outputSHA1, 20);

}
