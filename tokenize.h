///
/// File:  tokenize.h
/// Description:  Header file for the tokenize c file
///
/// @author ljc5423@rit.edu
///

#ifndef PROJECT1_TOKENIZE_H
#define PROJECT1_TOKENIZE_H

#include <stdio.h>

#include <stdlib.h>
#include "scanner.h"

#define USAGE_STRING "usage: ./tokenize tmfile\n"

/// Takes in the path to the TM file and prints the TM and tokens to the terminal
/// @return EXIT_SUCCESS or EXIT_FAILURE on error
int main(int argc, char* argv[]);

#endif //PROJECT1_TOKENIZE_H
