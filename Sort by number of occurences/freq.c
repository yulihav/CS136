/**
 [Yuliana Havryshchuk] (20514228)
 CS136 Fall 2015
 Assignment 7, Problem 3
 File: freq.c
 ... module description ...
**/

#include "getint.h"
#include "intpq.h"
#include <stdio.h>

int main() {
  // create an array to store counts of each int
  // & another to store their order
  int Counts[100001] = {0};
  int Order[100001]= {0};
  // keep track of how many unique ints have been inputted
  int CtUniq = 0;
  
  // get the next input
  int input = getint();
  
  // POPULATE ARRAYS
  while (input != -1) {
    int Occb4 = 0;
    
    // check if the int has occurred before in the sequence
    // if it has, add one to the count of it, 
    // do not put it in the oreder array (it's already in there)
    for(int m = 0; m < CtUniq; m++) {
      if (Order[m] == input) {
        Occb4++;
      	Counts[m]++; } }
    
    // if not, add it to the array keeping track of order, 
    // increase the count of unique ints
    if (Occb4 == 0) {
      Order[CtUniq] = input; 
      Counts[CtUniq]++;
      CtUniq++; }
  
    // get next int
    input = getint(); }
  
  // transfer from arrays into prioqueues
  struct intprioqueue numspq = new_intpq();
  struct intprioqueue freqspq = new_intpq();
  for (int j = 0; j<=CtUniq; j++) {
    intpq_insert(&numspq, Order[j], Order[j]);
  	intpq_insert(&freqspq, Counts[j], Order[j]);}
  
  // transfer from prioqueues into arrays (will be sorted largest
  // to smallest)
  int Counts2[100001] = {0};
  int Order2[100001]= {0};
  for (int j = 0; j<CtUniq; j++) {
    Order2[j] = intpq_head(numspq);
    Counts2[j] = intpq_head(freqspq);
    intpq_delete(&numspq);
    intpq_delete(&freqspq);}
  intpq_delete(&numspq);
  intpq_delete(&freqspq);
  
  //put back into prioqueues (backwards)
  for (int j = CtUniq; j>=0; j--) {
    intpq_insert(&numspq, Order2[j], Counts2[j]);
  	intpq_insert(&freqspq, Counts2[j], Counts2[j]);}
  
  for (int k = 0; k <CtUniq; k++) {
    printf("%d %d\n", intpq_head(numspq), intpq_head(freqspq)); 
    intpq_delete(&numspq);
    intpq_delete(&freqspq);}
  
  intpq_delete(&numspq);
  intpq_delete(&freqspq);
  intpq_destroy(&numspq);
  intpq_destroy(&freqspq);
}
