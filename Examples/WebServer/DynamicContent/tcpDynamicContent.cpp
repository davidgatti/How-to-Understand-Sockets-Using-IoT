#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "replace.h"

// Loading pages
#include "home.h"
#include "author.h"
#include "more.h"
#include "error.h"

TCPServer serverWww = TCPServer(80);
TCPClient clientWww;

void setup() {

  // start listening for clients
  serverWww.begin();

  // Make sure your Serial Terminal app is closed before powering your device
  Serial.begin(9600);

  // Show what is our IP
  Serial.println(WiFi.localIP());

}

void loop() {

    if (clientWww.connected()) {

        int position = 0;
        int canI = 0;

        // echo all available bytes back to the client
        while (clientWww.available()) {

            char c = clientWww.read();
            char url[200];

            // Detect space
            if(c == 32) {

                canI = !canI;

            }

            // Save only data in between spaces
            if(canI) {

                // Discard spaces
                if(c != 32) {

                    url[position++] = c;

                }

            }

            // Detect end of the line
            if(c == 10) {

                // Null terminate our array
                url[position + 1] = 0;

                response(url);

                // Discard the rest of the header
                clientWww.flush();

            }

        }

    } else {

        // if no client is yet connected, check for a new connection
        clientWww = serverWww.available();

    }

}

void response(char* url) {

    // Get the local IP address
    IPAddress localIP = WiFi.localIP();

    char myIpString[16];
    char serverTime[20];

    // Format the IP in to a char array
    sprintf(myIpString, "%d.%d.%d.%d", localIP[0], localIP[1], localIP[2], localIP[3]);

    // Format our time
    sprintf(serverTime, "%d:%d:%d %d/%d/%d", Time.hour(), Time.minute(), Time.second(), Time.month(), Time.day(), Time.year());

    tuple_t pairs[] = {
        {"ip", myIpString},
        {"time", serverTime},
    };

    // Our output variable has a fixed size because I don't have the time and
    // energy to write another method to calculated the new size that we'll get.
    // Shoot me ;) If your string get shortened, then just increase the size of the array.
    char output[400] = "";

    // default page is the error page
    const char* page = error;

    // Get the length out of our URL and remove the null termination
    int urlLen = strlen(url) - 1;

    // HOME: check only for the length of the URL, since the home page
    // is represented by a forward slash /
    if(urlLen == 1) {

        page = home;

    }

    // MORE: look for the word
    if(memcmp(url, "/more", 5) == 0) {

        page = more;

    }

    // Author: look for the word
    if(memcmp(url, "/author", 6) == 0) {

        page = author;

    }

    // Look for dynamic content
    replace(page, output, pairs);

    // Inform the browser that everything is ok
    clientWww.write("HTTP/1.1 200 OK\n\r");

    // Tell the encoding that we are using
    clientWww.write("Content-Type: text/html; charset=ascii\n\r");

    // Separate the header from the body with one empty line
    clientWww.write("\n\r");

    // Send our content
    clientWww.write(output);

    // Close the connection
    clientWww.stop();

}
