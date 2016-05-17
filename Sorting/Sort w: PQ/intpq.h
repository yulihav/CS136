/**
 File: intpq.h
 This module contains functions for working with a priority queue which contains
   integers
**/

// Priority queue ADT
struct intprioqueue;

// new_intpq() returns a new empty intprioqueue
// time: O(1)
struct intprioqueue new_intpq();

// intpq_empty(q) returns 1 if q is empty and 0 otherwise
// requires: q has been previously created but not destroyed
// time: O(1)
int intpq_empty(struct intprioqueue q);

// intpq_head(q) returns element with the highest priority in q (and the oldest
//   element with the highest priority if there are many)
// requires: q has been previously created but not destroyed; q is not empty
// time: O(log n) where n is the number of elements in q
int intpq_head(struct intprioqueue q);

// intpq_insert(q, e, p) inserts the element e into *q with priority p
// requires: *q has been previously created but not destroyed
// effects: contents of *q are updated
// time: O(log n) where n is the number of elements in q
void intpq_insert(struct intprioqueue * q, int e, int prio);

// intpq_delete(q) removes the element with the highest priority in *q (and the
//   oldest element with the highest priority if there are many)
// requires: *q has been previously created but not destroyed; *q is not empty
// effects: contents of *q are updated
// time: O(log n) where n is the number of elements in *q
void intpq_delete(struct intprioqueue * q);

// intpq_destroy(q) destroys the priority queue q; every intprioqueue created
//   must eventually be destroyed
// requires: q has been previously created but not destroyed
// effects: q can no longer be used
// time: O(n) where n is the number of elements in q
void intpq_destroy(struct intprioqueue * q);

///////////////////////////////
/////  Keep Out!
///////////////////////////////

// implementation-specific type used in the sample implementation
struct intprioqueue {
  struct node * x;
};
