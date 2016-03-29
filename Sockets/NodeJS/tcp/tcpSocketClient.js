'use strict';

let net = require('net');

const PORT = 1337;
const HOST = '192.168.1.58';

let client = new net.Socket();

client.connect(PORT, HOST, function() {

	// Send a friendly message
	client.write("I am the client sending you a message.");

});

client.on('data', function(data) {

	console.log('Received: %s [it is %d bytes long]', data, data.length);

	// Close the connection after recivign the message
	client.destroy();

});

// Informa when the socket connection is beeing closed.
client.on('close', function() {

	console.log('Connection closed');

});

// When an erro occurse, show it.
client.on('error', function(error) {

	console.error(error);

	// Close the connection after the errors accured.
	client.destroy();

});
