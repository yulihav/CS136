/**
 File: freq.c
 Reads a sequence of integers between 0 and 1000, inclusive, 
 and prints the one that occurs most frequently. 
 If several numbers occur most frequently, print 
 the one that occurs first in the sequence. 
 If the sequence is empty, print nothing.
**/

#include <stdio.h>
#include <assert.h>
#include "getint.h"
#include "intvec.h"


int main() {
  
  // create vector of inputs
  struct intvec vector = intvec_create();
  struct intvec *ptr_vector = &vector;
  int input = getint();
  assert(input <= 2147483647);
  
  if (input == -1) {
    intvec_destroy(vector);
    return 0;}
  
  else {
    while (input != -1) {
      assert(input <= 2147483647);
      intvec_grow(*ptr_vector, input);
      input = getint();} 
    
    // variables
    int size = intvec_size(vector);
    int Hi = intvec_nth(vector,0);
    int HiCnt = 1;
    int Temp = 0;
    
    //loops
    for (int i = 0; i < size; i++) {
      Temp = intvec_nth(vector,i);
      int TempCnt = 0;
      for (int j = 0; j < size; j++) {
      	if (intvec_nth(vector,j) == Temp) {
        	TempCnt++; }}
      if (TempCnt > HiCnt) {
        Hi = Temp;
        HiCnt = TempCnt;}}
    
    //print highest frequency int
    printf("%d\n",Hi); }
  
  intvec_destroy(vector);
  return 0;
  }