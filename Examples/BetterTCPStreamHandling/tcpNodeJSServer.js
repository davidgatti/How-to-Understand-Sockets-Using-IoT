'use strict';

let net = require('net');

const PORT = 1337;
const HOST = '192.168.1.100';

let server = net.createServer(function(socket) {

    console.log("Connected");

    // Setting the socket Buffer to be in binary instead of the default UTF8
    socket.setEncoding('binary');

    socket.on('data', function(data) {

        // Create temporary array storage where we are going to save all the 1 and 0.
        let tmp = [];

        // Loop thru each character since there is no telling if we get one single message
        // or a bunch combined together.
        for (let c of data) {

            // Only collect the 1 and 0
            if(c != ',') {

                tmp.push(c);

            } else {

                // if we reach a separator character, then we know we have the full
                // value.
                if(tmp.length > 0) {

                    // Combine our array in to a single string
                    let rawInt = tmp.join('');

                    // Since we know we converted ints in to binary from our particle
                    // we can convert them back in to a number.
                    let integerData = parseInt(rawInt, 2);

                    // Print the result
                    console.log('Received: %d', integerData);

                    // clean the temporary storage for the next run.
                    tmp = [];

                }

            }

        } // for

        // If we get a single message, we can display it after we loop over it.
        if(tmp.length > 0) {

            let rawInt = tmp.join('');
            let integerData = parseInt(rawInt, 2);
            console.log('Received: %d', integerData);

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
