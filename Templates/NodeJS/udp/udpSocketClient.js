'use strict';

let dgram = require('dgram');

const PORT = 1337;
const HOST = '192.168.1.58';

let client = dgram.createSocket('udp4');
let message = "I am the client sending you a message.";

// Send data to the client
client.send(message, 0, message.length, PORT, HOST, function(offset, length) {

    console.log("Sent: %s [from %s to %s bytes]", message, offset, length);

});

client.on('message', function(data) {

    console.log('Received: %s [it is %d bytes long]',
        data.toString().replace(/(\n)/gm,""),
        data.length);

    client.close();

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
