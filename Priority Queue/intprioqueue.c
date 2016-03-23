/**
 [Yuliana Havryshchuk] (20514228)
 CS136 Fall 2015
 Assignment 5, Problem 3
 File: intprioqueue.c
 Module consisting of intprioqueue.h and intprioqueue.c that 
 implements a priority queue with the operations defined below:
**/
#include "intprioqueue.h"
#include "getint.h"
#include <assert.h>
#include <stdio.h>

struct intprioqueue new_intpq() {
  const struct intprioqueue pq = {intvec_create(), intvec_create()};
  return pq;}

int intpq_empty(struct intprioqueue q) {
  if (intvec_size(q.names) == 0) {
    return 1; }
  else {
    return 0;}
}

int intpq_head(struct intprioqueue q) {
  assert(intvec_size(q.names) != 0);
  
  // FIND HIGHEST PRIO
  // variables
    int size = intvec_size(q.prios);
    int Hi = intvec_nth(q.prios,0);
    int HiPos = 0;
    
    //loop
      for (int j = 0; j < size; j++) {
      	if (intvec_nth(q.prios,j) > Hi) {
          Hi = intvec_nth(q.prios,j);
          HiPos = j; }}
  
  return intvec_nth(q.names,HiPos);
}

void intpq_insert(struct intprioqueue q, int e, int p) {
  intvec_grow(q.names,e);
  intvec_grow(q.prios,p);
}

void intpq_delete(struct intprioqueue q) {
  assert(intvec_size(q.names) != 0);
  
  // FIND HIGHEST PRIO
  // variables
    int size = intvec_size(q.prios);
    int Hi = intvec_nth(q.prios,0);
    int HiPos = 0;
    //loop
      for (int j = 0; j < size; j++) {
      	if (intvec_nth(q.prios,j) > Hi) {
          Hi = intvec_nth(q.prios,j);
          HiPos = j; }}
    
  int OFFnames = 0;
  int OFFprios = 0;
  
  //delete from names
    for (int i = 0;  i < size ; i++) {
      if (i != HiPos) {
    		intvec_set_nth(q.names, i - OFFnames, intvec_nth(q.names,i));}
  		if (i == HiPos) {
        OFFnames++;}}
    	intvec_shrink(q.names);
  
  //delete from prios
  for (int i = 0;  i < size ; i++) {
      if (i != HiPos) {
    		intvec_set_nth(q.prios, i - OFFprios, intvec_nth(q.prios,i));}
  		if (i == HiPos) {
        OFFprios++;}}
    	intvec_shrink(q.prios); 
}

void intpq_destroy(struct intprioqueue q) {
  intvec_destroy(q.names);
  intvec_destroy(q.prios);
}
