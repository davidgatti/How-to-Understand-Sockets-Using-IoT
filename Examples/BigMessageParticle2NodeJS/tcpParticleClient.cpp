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

    // Create a string so we can use it as our buffer
    unsigned char buf[txtSize];

    // Convert char array pointer in to a nice string
    for(int c=0; c<= txtSize; c++) {

        buf[c] = txt[c];

    }

    // Send our data to the remote server
    client.write(buf, txtSize);

    // Send the separator
    client.print(',');

    Serial.println("Done");

    delay(1000);

}
