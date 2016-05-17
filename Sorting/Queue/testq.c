/**
 File: testq.c
Tests all the intqueue functions
*/

#include <assert.h>
#include "intqueue.h"
#include <stdio.h>

int main(void) {
  struct intqueue q = new_intq();
  assert(intq_empty(q));
  intq_insert(q,10);
  assert(!intq_empty(q));
  assert(10 == intq_head(q));
  intq_delete(q);
  assert(intq_empty(q));
  intq_destroy(q);
  
  struct intqueue q2 = new_intq();
  intq_insert(q2,20);
  intq_insert(q2,30);
  intq_insert(q2,40);
  assert(!intq_empty(q2));
  assert(20 == intq_head(q2));
  intq_delete(q2);
  assert(!intq_empty(q2));
  assert(30 == intq_head(q2));
  intq_delete(q2);
  assert(!intq_empty(q2));
  assert(40 == intq_head(q2));
  intq_delete(q2);
  assert(intq_empty(q2));
  intq_destroy(q2);
  
  struct intqueue q3 = new_intq();
  assert(intq_empty(q3));
  intq_insert(q3,20);
  assert(20 == intq_head(q3));
  intq_insert(q3,30);
  assert(20 == intq_head(q3));
  intq_insert(q3,40);
  assert(!intq_empty(q3));
  intq_delete(q3);
  assert(!intq_empty(q3));
  intq_insert(q3,20);
  assert(30 == intq_head(q3));
  intq_delete(q3);
  intq_delete(q3);
  intq_delete(q3);
  assert(intq_empty(q3));
  intq_insert(q3,30);
  assert(!intq_empty(q3));
  intq_delete(q3);
  intq_destroy(q3);
  
  struct intqueue q4 = new_intq();
  intq_insert(q4,20);
  intq_insert(q4,30);
  intq_insert(q4,40);
  intq_destroy(q4);
  return 0; }