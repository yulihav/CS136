/**
 [Yuliana Havryshchuk] (20514228)
 CS136 Fall 2015
 Assignment 5, Problem 3
 File: intprioqueue.h
 Module consisting of intprioqueue.h and intprioqueue.c that 
 implements a priority queue with the operations defined below:
**/

#include "intvec.h"

struct intprioqueue {
  struct intvec names;
  struct intvec prios;
};


//new_intpq(): Returns an empty intprioqueue
struct intprioqueue new_intpq();

//intpq_empty(): Returns 1 if q is empty; 0 otherwise.
int intpq_empty(struct intprioqueue q);

//intpq_head(): Returns element of q with the highest priority. 
// If many elements have the highest priority, returns the 
// oldest with the highest priority. 
// q must not be empty.
int intpq_head(struct intprioqueue q);

//intpq_insert():  Insert element e with priority p into q.
void intpq_insert(struct intprioqueue q, int e, int p);

//intpq_delete(): Remove the element of q with the highest priority. 
// If many elements have the highest priority, remove the 
// oldest with the highest priority. 
// q must not be empty.
void intpq_delete(struct intprioqueue q); 

//intpq_destroy(): Destroy intprioqueue q.
void intpq_destroy(struct intprioqueue q);
