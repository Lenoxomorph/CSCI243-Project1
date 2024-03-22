///
/// File:  tokenize.c
/// Description:  Takes in a transition matrix from the terminal, then input text from the standard input and finds
///               the tokens within the text
///
/// @author ljc5423@rit.edu
///

#include <string.h>
#include "tokenize.h"

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

    scannerStateMachine* scanner = buildScanner(file);
    fclose(file);

    while (feof(stdin) == 0) {
        scanForToken(scanner);
        if (scanner->state == -1) {
            printf("rejected\n");
        } else {
            if (scanner->buffer[0] != '\0') {
                printf("recognized '%s'\n", scanner->buffer);
            }
        }
        strcpy(scanner->buffer, "");
    }
    printf("EOF\n");

    freeScanner(scanner);
    return EXIT_SUCCESS;
}