'use strict';

let tls = require('tls');
let fs = require('fs');

const PORT = 1337;
const HOST = '127.0.0.1'

let options = {
	key: fs.readFileSync('private-key.pem'),
	cert: fs.readFileSync('public-cert.pem')
};

let server = tls.createServer(options, function(socket) {

	// Send a friendly message
	socket.write("I am the server sending you a message.");

	// Print the data that we recived
	socket.on('data', function(data) {

		console.log('Received: %s [it is %d bytes long]',
			data.toString().replace(/(\n)/gm,""),
			data.length);

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

// When an erro occurse, show it.
server.on('error', function(error) {

	console.error(error);

	// Close the connection after the errors accured.
	server.destroy();

});
