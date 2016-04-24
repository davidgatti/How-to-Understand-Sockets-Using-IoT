'use strict';

let net = require('net');

const PORT = 1337;
const HOST = '192.168.1.100';

let server = net.createServer(function(socket) {

    console.log("Connected");

    // Setting the socket Buffer to be in binary instead of the default UTF8
    socket.setEncoding('binary');

    socket.on('data', function(data) {

        // Skipping the separation char
        if(data != ',') {

            // Converting binary data back to an integer, since we know that the
            // data that we are sending is in binary.
            let integerData = parseInt(data, 2);

            console.log('Received: %s [it is %d bytes long]', integerData, data.length);

        }

	});

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

});

// Start listening on a specific port and address
server.listen(PORT, HOST, function() {

	console.log("I'm listening at %s, on port %s", HOST, PORT);

});

// Save data
function savaData(socket) {



}
