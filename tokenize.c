///
/// File:  tokenize.c
/// Description:  TODO: DESC
///
/// @author ljc5423@rit.edu
///


#include "classes.h"
#include "tokenize.h"

#include <stdio.h>
#include <stdlib.h>

void buildTM(FILE* file) {
    // Print File contents
    char *ptr, buf[BUFLEN];

    while((ptr = fgets(buf, BUFLEN, file)) != NULL) {
        if (*ptr == '#') {
            continue;
        }
        printf(ptr);
    }
}

/// TODO: Description
/// @return EXIT_SUCCESS or EXIT_FAILURE on error
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, USAGE_STRING);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    // Check if file exists, error if not
    if (!file) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    buildTM(file);
    fclose(file);

    return EXIT_SUCCESS;
}