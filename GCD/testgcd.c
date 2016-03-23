/**
 File: testgcd.c
 Takes 4 inputs and: 
1) prints the gcd of the first 2 inputs
2) prints the lcm of the second 2 inputs
*/

#include <stdio.h>
#include "gcd.h"
#include "getint.h"

int main(void) {
  printf("%d\n", gcd(getint(),getint()));
  printf("%d\n", lcm(getint(),getint()));
  return 0;}
