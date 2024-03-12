///
/// File:  classes.h
/// Description:  Defines names for character classes used in the
///               CSCI-243 scanner project.
///
/// @author csci243@cs.rit.edu
///

#ifndef CLASSES_H_
#define CLASSES_H_

   // whitespace characters:  space, tab
#define	CC_WS	   	0

   // newline character
#define	CC_NL	   	1

   // alphabetic (A-Z, a-z) and underscore
#define	CC_ALPHA   	2

   // digit character 0
#define	CC_ZERO    	3

   // octal/decimal digit characters 1-7
#define	CC_OCTAL  	4

   // decimal digit characters 8, 9
#define	CC_DECIMAL 	5

   // division operator
#define	CC_SLASH	6

   // multiplicative operator
#define	CC_STAR 	7

   // other arithmetic operators: +, -, %
#define	CC_ARITH 	8

   // any other ASCII character
#define	CC_OTHER   	9

   // EOF on input
#define	CC_EOF  	10

   // any non-ASCII character
#define	CC_ERROR   	11

   // number of character classes
#define	NUM_CLASSES	12

#endif
