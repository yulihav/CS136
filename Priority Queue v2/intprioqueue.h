/**
 [Yuliana Havryshchuk] (20514228)
 CS136 Fall 2015
 Assignment 6, Problem 3
 File: intprioqueue.h
 Implements a priority queue with the operations described below:
**/

struct intprioqueue {
	int ints[1000];
	int prios[1000];
	int size;
	int hiprio;
};


//new_intpq(): Returns an empty intprioqueue
struct intprioqueue new_intpq();

//intpq_empty(): Returns 1 if q is empty; 0 otherwise.
int intpq_empty(struct intprioqueue q);

//intpq_head(): Returns element of q with the highest priority.
int intpq_head(struct intprioqueue q);

//intpq_insert(): Insert element e with priority p into q
void intpq_insert(struct intprioqueue * q, int e, int p);

//intpq_delete(): Remove the element of q with the highest priority.
void intpq_delete(struct intprioqueue * q); 

