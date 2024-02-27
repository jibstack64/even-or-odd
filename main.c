/*  even-or-odd
 *  
 *  A silly little program that generates a Python script (hear me out) that
 *  checks if an integer is even or odd.
 *
 *  Here's the catch: it does so using ONLY if and elif statements.
 *  Why? BECAUSE FUNNY!
 *
 *  Now listen, I know that Python *technically* doesn't have any limit on
 *  integer size, but for this project to mean anything I'm going to use
 *  the maximum size of a 2-byte OR 4-byte integer (if you don't like having
 *  a healthy amount of disk space).
 *
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define CHUNK_BUFFER    45
#define USAGE_TEXT      "usage: %s {2 OR 4}\n"
#define TWO_BYTES       '2'
#define FOUR_BYTES      '4'

/* Macros */
#define OUTPUT_FILE() fopen("output.py", "a")
#define WRITE_CHUNK(f, chunk) { \
        do { \
            fputs(chunk, f); \
        } while (0); \
    }
#define VALID_BYTES(x) (x == TWO_BYTES || x == FOUR_BYTES)
#define BYTE_MAX(b) (b == TWO_BYTES ? UINT16_MAX : UINT32_MAX)

int main(int argc, char **argv) {
    if (argc < 2) {
        perror("Insufficient arguments provided\n");
        printf(USAGE_TEXT, argv[0]);
        return 1;
    }

    char bytes = argv[1][0];
    if (!VALID_BYTES(bytes)) {
        perror("Invalid bytes.\n");
        return 1;
    }
     
    FILE *output = OUTPUT_FILE();
    if (output == NULL) {
        perror("WTF! Failed to open file!\n");
        return 1;
    }

    /* The starting chunk of the Python script. */
    char start_chunk[] =    "number=input(\"Number: \")\n"
                            "if number == 0:\n"
                            "   print(\"Zero\")\n";
    WRITE_CHUNK(output, start_chunk);

    /* Bit silly to define this here; the chunk template. */
    char *chunk_template =  "elif number == %d:\n"
                            "   print(\"%s\")\n";

    uint32_t max = BYTE_MAX(bytes);
    for (uint32_t i = 0; i < max; i++) {
        char current[CHUNK_BUFFER];
        sprintf(current, chunk_template, i, i % 2 == 0 ? "Even" : "Odd");
        WRITE_CHUNK(output, current);
    }

    fclose(output);
    
    return 0;
}

