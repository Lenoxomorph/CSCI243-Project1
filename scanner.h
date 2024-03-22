///
/// File:  scanner.h
/// Description:  Header file for the scanner.c source file
///
/// @author ljc5423@rit.edu
///

#ifndef PROJECT1_SCANNER_H
#define PROJECT1_SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "classes.h"


#define BUFLEN 80        ///< the max buffer size of the 'stdin'
#define FILEBUFLEN 256   ///< the max buffer size of the TM file

/// A state machine that can scan and parse tokens in a given text
typedef struct scannerStateMachine {
    int numOfStates;        ///< the total number of states in the matrix
    int startState;        ///< the accepting state of the matrix
    int acceptState;        ///< the accepting state of the matrix
    int state;                    ///< the current state
    char buffer[BUFLEN];                    ///< the buffer of characters in current token
    struct matrix_cell * matrix;  ///< the matrix storing the transitions for the state machine
} scannerStateMachine;

/// A cell in the transition matrix
typedef struct matrix_cell {
    int destState;  ///< the state to which the transition goes
    bool isSave;    ///< if the transition should save the character
} matrix_cell;

/// Takes in a TM file and builds a scanner around it
/// @param file the file to get the TM from
/// @return scannerStateMachine* The pointer to the built scanner
scannerStateMachine *buildScanner(FILE* file);

/// Frees allocated memory for the scanner
/// @param scanner the given scanner
void freeScanner(scannerStateMachine* scanner);

/// Scans for a token using the given scanner
/// @param scanner the scanner to use for the scan
void scanForToken(scannerStateMachine* scanner);

#endif //PROJECT1_SCANNER_H
