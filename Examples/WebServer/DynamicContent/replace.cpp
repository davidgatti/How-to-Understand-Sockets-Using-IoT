#include <string.h>
#include "replace.h"

void replace(const char* input, char* output, tuple_t* data) {


    // By default we can loop thru the char array.
    int loopThruData = 1;

    // We need two different numbers because we are going to move thru our arrays
    // at different rate. Since the data that we are going to append have
    // different length from the data that we are replacing.
    int i = 0;
    int x = 0;

    while(loopThruData) {

        // Save each char in to a new variable
        output[i] = input[x];

        // When we detect the first issue, we start replacing
        if(input[x] == '{') {

            // remove the '{' char from the variable
            output[i] = 0;

            char phraseToFind[10] = ""; // get some memory for ourselves
            int loopThruPhrase = 1; // by default we can loop
            int j = 0; // new counter for the phrase that we are looking for
            x++; // move our pointer by one so we skip the opening {.

            // Until we don't encounter the closing brakes we keep going
            while(loopThruPhrase) {

                char c = input[x+j];

                phraseToFind[j] = c;

                // End of segment
                if (c == '}') {

                    // remove the { char from the variable
                    phraseToFind[j] = 0;

                    char* replacement;

                    for(int z = 0; z < 2; z++) {

                        // Look for the matching phrase to replace
                        if(memcmp(phraseToFind, data[z].in, strlen(data[z].in)) == 0) {

                            replacement = data[z].out;

                        } // :: if()

                    }

                    // Append the content phrase
                    strcat(output, replacement);

                    i = strlen(output)-1;
                    x = x + j;

                    // Exit the loop.
                    loopThruPhrase = !loopThruPhrase;

                } // :: if()

                j++;

            }// :: while()

        } // :: if(content[x] == '{')

        i++;
        x++;

        // Exit the loop once we reach the end of the char array.
        if(input[x] == 0) {

            loopThruData = !loopThruData;

        } // :: if()

    } // :: while()

}
