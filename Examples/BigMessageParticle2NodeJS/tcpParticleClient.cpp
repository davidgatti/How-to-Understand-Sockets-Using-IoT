TCPClient client;

int port = 1337;
byte server[] = { 192, 168, 1, 100 };

char* txt = "1. Particle is a prototype-to-production platform for developing an Internet of Things\n2. Particle is a prototype-to-production platform for developing an Internet of Things\n3. Particle is a prototype-to-production platform for developing an Internet of Things\n4. Particle is a prototype-to-production platform for developing an Internet of Things\n5. Particle is a prototype-to-production platform for developing an Internet of Things\n6. Particle is a prototype-to-production platform for developing an Internet of Things\n7. Particle is a prototype-to-production platform for developing an Internet of Things\n8. Particle is a prototype-to-production platform for developing an Internet of Things\n9. Particle is a prototype-to-production platform for developing an Internet of Things\n10. Particle is a prototype-to-production platform for developing an Internet of Things\n11. Particle is a prototype-to-production platform for developing an Internet of Things\n12. Particle is a prototype-to-production platform for developing an Internet of Things.\n13. Particle is a prototype-to-production platform for developing an Internet of Things.\n14. Particle is a prototype-to-production platform for developing an Internet of Things.\n15. Particle is a prototype-to-production platform for developing an Internet of Things.\n16. Particle is a prototype-to-production platform for developing an Internet of Things.\n17. Particle is a prototype-to-production platform for developing an Internet of Things.\n18. Particle is a prototype-to-production platform for developing an Internet of Things.\n19. Particle is a prototype-to-production platform for developing an Internet of Things.\n20. Particle is a prototype-to-production platform for developing an Internet of Things.\n21. Particle is a prototype-to-production platform for developing an Internet of Things.\n22. Particle is a prototype-to-production platform for developing an Internet of Things.\n23. Particle is a prototype-to-production platform for developing an Internet of Things.\n24. Particle is a prototype-to-production platform for developing an Internet of Things.\n25. Particle is a prototype-to-production platform for developing an Internet of Things.\n26. Particle is a prototype-to-production platform for developing an Internet of Things.\n27. Particle is a prototype-to-production platform for developing an Internet of Things.\n28. Particle is a prototype-to-production platform for developing an Internet of Things.\n29. Particle is a prototype-to-production platform for developing an Internet of Things.\n30. Particle is a prototype-to-production platform for developing an Internet of Things.\n31. Particle is a prototype-to-production platform for developing an Internet of Things.\n32. Particle is a prototype-to-production platform for developing an Internet of Things.\n33. Particle is a prototype-to-production platform for developing an Internet of Things.\n34. Particle is a prototype-to-production platform for developing an Internet of Things.\n35. Particle is a prototype-to-production platform for developing an Internet of Things.\n36. Particle is a prototype-to-production platform for developing an Internet of Things.\n37. Particle is a prototype-to-production platform for developing an Internet of Things.\n38. Particle is a prototype-to-production platform for developing an Internet of Things.\n39. Particle is a prototype-to-production platform for developing an Internet of Things.\n40. Particle is a prototype-to-production platform for developing an Internet of Things.\n41. Particle is a prototype-to-production platform for developing an Internet of Things.\n42. Particle is a prototype-to-production platform for developing an Internet of Things.\n43. Particle is a prototype-to-production platform for developing an Internet of Things.\n44. Particle is a prototype-to-production platform for developing an Internet of Things.";

void setup() {

    Serial.begin(9600);

    Serial.println("UP");

    // Connect to the remote server
    if(client.connect(server, port)) {

        Serial.println("Connected");


    } else {

        // if we can't connect, then we display an error.
        Serial.println("error");

    }

}

void loop() {

    int txtSize = strlen(txt);  // Get the size of our data
    int position = 0;           // Set the starting position
    int bufSize = 1024;         // Set our buffer size

    // We are going to chop our data if it is to big
    // so we can put it all together on the other end
    while(txtSize) {

        // Remove the buffer size that we wen thru
        int next = txtSize - bufSize;

        // Check if we are in the last iteration. If so, we have to set
        // the remaining buffer size which might be smaller then our buffer size.
        if(next <= 0) {
            bufSize = txtSize;
        } else {
            txtSize = next;
        }

        // Initialize a char pointer array each time we want to store a fragment of our data.
        // The size of the array needs to be dynamic, because our data chunks might be smaller
        // towards the end.
        char* tmp = (char*) malloc(bufSize);

        // Red a fragment of the data.
        for(int x=0; x < bufSize; x++) {

            tmp[x] = txt[position++];

        }

        // Create a string so we can use it as our buffer
        unsigned char buf[bufSize];

        // Convert char array pointer in to a nice string
        for(int c=0; c<= bufSize; c++) {

            buf[c] = tmp[c];

        }

        // Send our data to the remote server
        client.write(buf, bufSize);

        // Free up memory so we can set our variable again with a different size
        free(tmp);

        // If we are in the last iteration, then we send a END character.
        // Since there is no way of controlling how the data will be sent
        // (in how many peaces), we need a way of telling if we received
        // all of our data.
        if(next <= 0) {

            client.print(',');
            break;

        }

    }

    Serial.println("Done");

    delay(1000);

}
