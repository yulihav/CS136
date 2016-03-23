/**
 File: testq.c
Tests all the intprioqueue functions using negative, positive, and 0
elements and priorities
*/


#include <assert.h>
#include "intprioqueue.h"
#include <stdio.h>

int main(void) {
  
  struct intprioqueue q = new_intpq();
  assert(intpq_empty(q));
  intpq_insert(&q,10,20);
  intpq_insert(&q,30,-5);
  assert(!intpq_empty(q));
  assert(10 == intpq_head(q));
  intpq_delete(&q);
  intpq_delete(&q);
  assert(intpq_empty(q));
  
  struct intprioqueue q0 = new_intpq();
  assert(intpq_empty(q0));
  intpq_insert(&q0,10,1);
  assert(!intpq_empty(q0));
  assert(10 == intpq_head(q0));
  intpq_delete(&q0);
  assert(intpq_empty(q0));
  
  struct intprioqueue q2 = new_intpq();
  intpq_insert(&q2,20,-1);
  intpq_insert(&q2,30,5);
  intpq_insert(&q2,40,6);
  assert(!intpq_empty(q2));
  assert(40 == intpq_head(q2));
  intpq_delete(&q2);
  assert(!intpq_empty(q2));
  assert(30 == intpq_head(q2));
  intpq_delete(&q2);
  assert(!intpq_empty(q2));
  assert(20 == intpq_head(q2));
  intpq_delete(&q2);
  assert(intpq_empty(q2));
  
  struct intprioqueue q3 = new_intpq();
  assert(intpq_empty(q3));
  intpq_insert(&q3,20,5);
  assert(20 == intpq_head(q3));
  intpq_insert(&q3,30,1);
  assert(20 == intpq_head(q3));
  intpq_insert(&q3,40,10);
  assert(!intpq_empty(q3));
  intpq_delete(&q3);
  assert(!intpq_empty(q3));
  intpq_insert(&q3,100,100);
  assert(100 == intpq_head(q3));
  intpq_delete(&q3);
  intpq_delete(&q3);
  intpq_delete(&q3);
  assert(intpq_empty(q3));
  intpq_insert(&q3,30,101);
  assert(!intpq_empty(q3));
  
  struct intprioqueue q4 = new_intpq();
  intpq_insert(&q4,0,5);
  intpq_insert(&q4,0,5);
  intpq_insert(&q4,40,5);
  assert(0 == intpq_head(q4));
  intpq_delete(&q4);
  assert(0 == intpq_head(q4));
  
  struct intprioqueue q5 = new_intpq();
  assert(intpq_empty(q5));
  intpq_insert(&q5,-20,-5);
  intpq_insert(&q5,-30,5);
  intpq_insert(&q5,0,0);
  assert(!intpq_empty(q5));
  assert(-30 == intpq_head(q5));
  intpq_delete(&q5);
  assert(!intpq_empty(q5));
  assert(0 == intpq_head(q5));
  intpq_delete(&q5);
  assert(!intpq_empty(q5));
  assert(-20 == intpq_head(q5));
  intpq_delete(&q5);
  assert(intpq_empty(q5));
  
  struct intprioqueue q6 = new_intpq();
  assert(intpq_empty(q6));
  intpq_insert(&q6,-200000,-500000);
  intpq_insert(&q6,-301234,54321);
  intpq_insert(&q6,0,0);
  assert(!intpq_empty(q6));
  assert(-301234 == intpq_head(q6));
  intpq_delete(&q6);
  assert(!intpq_empty(q6));
  assert(0 == intpq_head(q6));
  intpq_delete(&q6);
  assert(!intpq_empty(q6));
  assert(-200000 == intpq_head(q6));
  intpq_delete(&q6);
  assert(intpq_empty(q6));
  
  return 0; }