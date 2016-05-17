/**
 [Yuliana Havryshchuk] (20514228)
 CS136 Fall 2015
 Assignment 5, Problem 2
 File: intqueue.h
 module consisting of intqueue.h and intqueue.c that implements
 a queue with multiple operations, defined below
**/
#include "intvec.h"

struct intqueue {
  struct intvec vector;
};

//new_intq(): Returns an empty intqueue.
struct intqueue new_intq();

//intq_empty(): Returns 1 if q is empty; 0 otherwise.
int intq_empty(struct intqueue q);

//intq_head(): Returns the oldest element of q. 
// q must not be empty.
int intq_head(struct intqueue q);

//intq_insert(): Insert element e into q.
void intq_insert(struct intqueue q, int e);

//intq_delete(): Remove the oldest element of q. 
// q must not be empty.
void intq_delete(struct intqueue q); 

//intq_destroy(): Destroy intqueue q.
void intq_destroy(struct intqueue q);
