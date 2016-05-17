/**
 [Yuliana Havryshchuk] (20514228)
 CS136 Fall 2015
 Assignment 5, Problem 2
 File: intqueue.c
 module consisting of intqueue.h and intqueue.c that implements
 a queue with multiple operations, defined below
**/

#include "intqueue.h"
#include "getint.h"
#include <assert.h>
#include <stdio.h>

struct intqueue new_intq() {
  const struct intqueue vector = {intvec_create()};
  return vector;}

int intq_empty(struct intqueue q) {
  if (intvec_size(q.vector) == 0) {
    return 1; }
  else {
    return 0;}
}

int intq_head(struct intqueue q) {
  assert(intvec_size(q.vector) != 0);
  return intvec_nth(q.vector,0);
}

void intq_insert(struct intqueue q, int e) {
  intvec_grow(q.vector,e);
}

void intq_destroy(struct intqueue q) {
  intvec_destroy(q.vector);
}

void intq_delete(struct intqueue q) {
  assert(intvec_size(q.vector) != 0);
  int size = intvec_size(q.vector);
  
  for (int i = 0;  i < size-1 ; i++) {
    intvec_set_nth(q.vector, i, intvec_nth(q.vector,i+1));}
    intvec_shrink(q.vector); 
}

/*void intq_delete(struct intqueue q) {
  assert(intvec_size(q.vector) != 0);
  
  struct intqueue q2 = new_intq();
  q = q2;
  intq_destroy(q2);
}*/


