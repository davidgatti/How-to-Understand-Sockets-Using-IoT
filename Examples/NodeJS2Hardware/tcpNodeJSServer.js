'use strict';

let net = require('net');

const PORT = 1337;
const HOST = '192.168.1.100';

let server = net.createServer(function(socket) {

    console.log("Conected");

    let timer = setInterval(function() {

        sendRandNumber(socket);

    }, 500);

    // Display error message
    socket.on('error', function(err) {

        clearInterval(timer);
        console.error(err);

    });

    // Detect a closed socket
    socket.on('close', function(err) {

        clearInterval(timer);
        console.log("Close");

    });

    // Set the Keep Alive so we can get an ACK from the device. Not sure how it works
    socket.setKeepAlive(true, 1000);

});

// Start listening on a specific port and address
server.listen(PORT, HOST, function() {

	console.log("I'm listening at %s, on port %s", HOST, PORT);

});

// Method to send a random number from 1 to 255 so we can set the brightness
// of the LED over PWM.
function sendRandNumber(socket) {

    // Generate random number
    let rand = Math.floor(Math.random() * 255) + 1;

    // Send random number with a separator character at the end.
    socket.write(rand.toString() + ":");

    // Display wht we sent.
    console.log(rand);

}
