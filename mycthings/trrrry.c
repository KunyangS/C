#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// define constants and variable
#define MAX_IDENTIFIERS 50

// main function
int main(int argc, char *argv[]) {
    // check if only one file is provided
    if (argc != 2) {
        fprintf (stderr, "Usage:%s <file.ml>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    // make sure file is ml file
    const char *extension = strrchr(filename, '.');
    if (extension == NULL || strcmp(extension, ".ml") !=0) {
        printf ("ERROR: The file must have a '.ml'extension.\n");
        return 1;
    }

    // open .ml file in read mode
    FILE *file = fopen(filename, "r");
    // check if the file was successfully opened
    if (!file)
    {   printf("ERROR: cannot open file '%s", error code: %d\n, argv[1], err);
        return 1;
    }
    // make sure the file isn't empty
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size == 0) {
        printf("The file '%s' is empty.\n", filename);
    }   else {
        printf ("The file '%s' is not empty and is %ld bytes long.\n", filename, size);
    }

    // close the file
    fclse (file);
    return 0;
}

