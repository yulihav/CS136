/**
 File: testfib.c
Takes 2 inputs n and f, and produces:
1) the nth fibonacci number on a new line
2) 1 if f is a fibonacci number, and 0 otherwise
*/

#include <stdio.h>
#include "getint.h"
#include "fib.h"

int main(void) {
  printf("%d\n",fib(getint()));
  printf("%d\n",isfib(getint()));
  return 0;}