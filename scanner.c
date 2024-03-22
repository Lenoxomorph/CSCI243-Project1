///
/// File:  scanner.c
/// Description:  Methods for the two data structures, a scanner, and a transition matrix
///
/// @author ljc5423@rit.edu
///

#include <string.h>
#include "scanner.h"

matrix_cell *getCell(matrix_cell *matrix, int stateNum, int charClass) {
    return &matrix[stateNum * NUM_CLASSES + charClass];
}
/// Inserts a given value to a given cell in the given matrix
/// @param matrix A pointer to the matrix to edit
/// @param stateNum The state number of the cell to edit
/// @param charClass The character class of the cell to edit
/// @param destState The State the cell should hold
/// @param isSave The save state of the cell
void insertCell(matrix_cell *matrix, int stateNum, int charClass, int destState, bool isSave) {
    matrix_cell *cell = getCell(matrix, stateNum, charClass);
    cell->destState = destState;
    cell->isSave = isSave;
}

/// Takes in a number of states for a TM and defaults all states to the error state
/// @return matrix_cell* The pointer to the built matrix
matrix_cell *buildMatrix(int numOfStates) {
    matrix_cell *matrix = malloc((numOfStates * NUM_CLASSES) * sizeof(matrix_cell));
    for (int i = 0; i < numOfStates; ++i) {
        for (int j = 0; j < NUM_CLASSES; ++j) {
            insertCell(matrix, i, j, -1, false);
        }
    }
    return matrix;
}

/// Takes in a scanner and prints it's matrix to the terminal
/// @param scanner The scanner to have it's matrix printed
void printMatrix(scannerStateMachine *scanner) {
    printf("Scanning using the following matrix:\n");
    printf("     0    1    2    3    4    5    6    7    8    9   10   11\n");
    for (int i = 0; i < scanner->numOfStates; ++i) {
        printf("%2d", i);
        for (int j = 0; j < NUM_CLASSES; ++j) {
            matrix_cell *cell = getCell(scanner->matrix, i, j);
            printf("  %2d%c", cell->destState, cell->isSave ? 's' : 'd');
        }
        putchar('\n');
    }
}

scannerStateMachine *buildScanner(FILE *file) {
    // Print File contents
    char *ptr, buf[FILEBUFLEN];

    scannerStateMachine *scanner = malloc(sizeof(scannerStateMachine));
    strcpy(scanner->buffer, "");

    int i = 0;
    while ((ptr = fgets(buf, FILEBUFLEN, file)) != NULL) {
        if (*ptr == '#') { // If commented line, skip
            continue;
        }
        // For the first 3 lines, get the numbers and set up the parameters of the state machine
        if (i < 3) {
            // Loop until number is found
            while (*ptr < '0' || *ptr > '9') {
                ptr++;
            }
            int num = strtol(ptr, NULL, 10);
            switch (i) {
                case 0:
                    scanner->numOfStates = num;
                    break;
                case 1:
                    scanner->startState = num;
                    break;
                case 2:
                    scanner->acceptState = num;
                    // Allocates the 2-D transition matrix
                    scanner->matrix = buildMatrix(scanner->numOfStates);
                    break;
            }
            i++;
        } else {
            int stateNum = strtol(ptr, &ptr, 10);
            ptr += 2; // Skips the first two spaces
            while(*ptr) {
                int charClass = strtol(ptr, &ptr, 10);
                ptr++; // Skips '/'
                int destState = strtol(ptr, &ptr, 10);
                bool isSave = *ptr == 115;
                ptr += 2; // Skips the char and the space
                insertCell(scanner->matrix, stateNum, charClass, destState, isSave);
            }
        }
    }
    printMatrix(scanner);
    return scanner;
}

/// Returns the 'Character Class' of the given character
/// @param c the input character
/// @return the integer of the class
int getCharClass(char c) {
    int classNum;
    switch (c) {
        case '\t':
        case ' ': classNum = CC_WS;
            break;
        case '\n': classNum = CC_NL;
            break;
        case 'a' ... 'z':
        case 'A' ... 'Z': classNum = CC_ALPHA;
            break;
        case '0': classNum = CC_ZERO;
            break;
        case '1' ... '7': classNum = CC_OCTAL;
            break;
        case '8' ... '9': classNum = CC_DECIMAL;
            break;
        case '/': classNum = CC_SLASH;
            break;
        case '*': classNum = CC_STAR;
            break;
        case '+':
        case '-':
        case '%': classNum = CC_ARITH;
            break;
        case -1:
        case 26: classNum = CC_EOF;
            break;
        default: classNum = CC_OTHER;
    }
    return classNum;
}

void scanForToken(scannerStateMachine* scanner) {
    scanner->state = scanner->startState;
    while (scanner->state != scanner->acceptState && scanner->state != -1) {
        printf("%d ", scanner->state);
        char tempChar = getchar();
        matrix_cell * cell = getCell(scanner->matrix, scanner->state, getCharClass(tempChar));
        scanner->state = cell->destState;
        if (cell->isSave) {
            strncat(scanner->buffer, &tempChar, 1);
        }
    }
    printf("%d ", scanner->state);
    if (scanner->state == -1) {
        char tempChar = getchar();
        while (getCharClass(tempChar) != CC_WS && getCharClass(tempChar) != CC_NL && getCharClass(tempChar) != CC_EOF) {
            tempChar = getchar();
        }
    }
}

void freeScanner(scannerStateMachine* scanner) {
    free(scanner->matrix);
    free(scanner);
}