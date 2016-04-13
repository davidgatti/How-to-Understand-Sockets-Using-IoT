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

        // Inform the browser that evrything is ok
        clientWww.write("HTTP/1.1 200 OK\n\r");

        // Tell the encodign that we are using
        clientWww.write("Content-Type: text/html; charset=ascii\n\r");

        // Separate the header from the body with one empty line
        clientWww.write("\n\r");

        // Our content
        clientWww.write("<html> <head> <title>Particle Server</title> </head> <body> <h1>Hello World</h1> <p>This content is coming from Particle.</p> </body> </html>");

        // Close the connection
        clientWww.stop();

    } else {

        clientWww = serverWww.available();

    }

    // Print out what the client (web broser) sent us.
    while(clientWww.available()) {

        char c = clientWww.read();
        Serial.print(c);

    }

}
