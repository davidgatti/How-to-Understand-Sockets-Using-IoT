'use strict';

let net = require('net');

const PORT = 1337;
const HOST = '192.168.1.100';

let server = net.createServer(function(socket) {

    console.log("Connected");

    socket.on('data', function(data) {

		console.log('Received: %s [it is %d bytes long]', data, data.length);

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
