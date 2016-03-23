/**
 File: testq.c
Tests all the intprioqueue functions
*/


#include <assert.h>
#include "intprioqueue.h"
#include <stdio.h>

int main(void) {
  struct intprioqueue q = new_intpq();
  assert(intpq_empty(q));
  intpq_insert(q,10,20);
  intpq_insert(q,30,5);
  assert(!intpq_empty(q));
  assert(10 == intpq_head(q));
  intpq_delete(q);
  intpq_delete(q);
  assert(intpq_empty(q));
  intpq_destroy(q);
  
  struct intprioqueue q0 = new_intpq();
  assert(intpq_empty(q0));
  intpq_insert(q0,10,1);
  assert(!intpq_empty(q0));
  assert(10 == intpq_head(q0));
  intpq_delete(q0);
  assert(intpq_empty(q0));
  intpq_destroy(q0);
  
  struct intprioqueue q2 = new_intpq();
  intpq_insert(q2,20,1);
  intpq_insert(q2,30,2);
  intpq_insert(q2,40,3);
  assert(!intpq_empty(q2));
  assert(40 == intpq_head(q2));
  intpq_delete(q2);
  assert(!intpq_empty(q2));
  assert(30 == intpq_head(q2));
  intpq_delete(q2);
  assert(!intpq_empty(q2));
  assert(20 == intpq_head(q2));
  intpq_delete(q2);
  assert(intpq_empty(q2));
  intpq_destroy(q2);
  
  struct intprioqueue q3 = new_intpq();
  assert(intpq_empty(q3));
  intpq_insert(q3,20,5);
  assert(20 == intpq_head(q3));
  intpq_insert(q3,30,1);
  assert(20 == intpq_head(q3));
  intpq_insert(q3,40,10);
  assert(!intpq_empty(q3));
  intpq_delete(q3);
  assert(!intpq_empty(q3));
  intpq_insert(q3,100,100);
  assert(100 == intpq_head(q3));
  intpq_delete(q3);
  intpq_delete(q3);
  intpq_delete(q3);
  assert(intpq_empty(q3));
  intpq_insert(q3,30,101);
  assert(!intpq_empty(q3));
  intpq_delete(q3);
  intpq_destroy(q3);
  
  struct intprioqueue q4 = new_intpq();
  intpq_insert(q4,20,5);
  intpq_insert(q4,30,5);
  intpq_insert(q4,40,5);
  assert(20 == intpq_head(q4));
  intpq_delete(q4);
  assert(30 == intpq_head(q4));
  intpq_destroy(q4);
  return 0; }