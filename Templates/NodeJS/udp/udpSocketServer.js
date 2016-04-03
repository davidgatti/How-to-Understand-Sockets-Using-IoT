'use strict';

let dgram = require('dgram');

const PORT = 1337;
const HOST = '192.168.1.100';

let server = dgram.createSocket('udp4');
let message = "I am the server sending you a message.";

server.on('listening', function() {

    let address = server.address();

    console.log("I'm listening at %s, on port %s", address.address, address.port);

});

server.bind(PORT, HOST);

server.on('message', function(data, remote) {

    console.log('Received: %s [it is %d bytes long]',
		data.toString().replace(/(\n)/gm,""),
		data.length);

    // Send a friendly message
    server.send(message, 0, message.length, remote.port, remote.address);

});

server.on('close', function(message, remote) {

    console.log("Connection closed");

});

// When an erro occurse, show it.
server.on('error', function(error) {

	console.error(error);

	// Close the connection after the errors accured.
	server.destroy();

});
