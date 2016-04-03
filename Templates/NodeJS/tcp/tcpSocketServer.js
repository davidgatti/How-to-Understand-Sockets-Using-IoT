'use strict';

let net = require('net');

const PORT = 1337;
const HOST = '192.168.1.100';

let server = net.createServer(function(socket) {

	// Send a friendly message
	socket.write("I am the server sending you a message.");

	// If we recive some data, lets display it.
	socket.on('data', function(data) {

		console.log('Received: %s [it is %d bytes long]', data, data.length);

	});

	// Let us know when the transmission is over
	socket.on('end', function() {

		console.log('EOT (End Of Transmission)');

	});

});

// Start listening on a specific port and address
server.listen(PORT, HOST, function() {

	console.log("I'm listening at %s, on port %s", HOST, PORT);

});

// If an error occurs, lets display what went wrong
server.on('error', function(err) {

	throw err;

});
