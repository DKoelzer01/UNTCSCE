#ifndef MAJOR1_H
#define MAJOR1_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // include limits.h for ~INT_MAX checking in clz.c
#include <stdbool.h> // for bool types that are used within drawMenu()

bool drawMenu(int *x, unsigned int *value); // prototype for drawMenu function

void countLeadingZeros(int x);         // prototype asd
void endian(int input);                // prototype for the endian function of type void that printf's the desired output for endian swapping
int endian2(int input);                // extra prototype for endian2 just in case wanted output was to return an integer
void rotateRight(unsigned int, int y); // prototype for rotateRight function
void parity(unsigned int x);           //prototype for parity function

#endif
