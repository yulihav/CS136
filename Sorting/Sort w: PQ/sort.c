/**
 [Yuliana Havryshchuk] (20514228)
 CS136 Fall 2015
 Assignment 7, Problem 2
 File: sort.c
 Read a sequence of non-negative integers from the input. 
 Prints the integers, one per line, in ascending order
**/

// SEE BOTTOM FOR RUNTIME COMMENT
#include "intpq.h"
#include "getint.h"
#include <stdio.h>
   
void mypqsort2(){
  int count = 0;
  struct intprioqueue mypq = new_intpq();
  struct intprioqueue mypq2 = new_intpq();
  int c = getint();
  
  //int pq_insert has runtime O(log n). Doing it n times makes it
  // n*O(log n) = O(n log n)
  while(c != -1) {
    intpq_insert(&mypq,c,c);
    count++;
    c = getint();
  }
  
  //intpq_insert and delete both have O(log n)
  // performing them n times results in
  // 2 * n * O(nlogn) = O(n log n)
  for (int i = 0; i <count; i++) {
    intpq_insert(&mypq2,intpq_head(mypq),i);
    intpq_delete(&mypq);}
  
  //intpq_head and delete both have O(log n)
  // performing them n times results in
  // 2 * n * O(nlogn) = O(n log n)
  //the runtime of printf is smaller, so it's insignificant
  for (int i = 0; i <count; i++) {
    printf("%d\n",intpq_head(mypq2));
    intpq_delete(&mypq2);}
  
  //intpq_destroy has runtime O(n), but both pqs are empty
  // so O(0) = 0 
  intpq_destroy(&mypq);
  intpq_destroy(&mypq2);
}

int main() {
  mypqsort2();
  return 0;
}

// RUNTIME COMMENT: 
// all operations that contribute significant runtime
// are O(log n). We perform each of them n times (in our loops), 
// we have 3 loops (1 with 1 operation, 2 with 2 operations)
// so, 5*O(n log n ) = O(n log n)
// see above for details
