// This module implements a priority queue in which each element
// is a symbol (defined in symbol.h) with an int priority

// defines the symbol type used by the pq functions
#include "symbol.h"


// ADT for mutable priority queue
struct priority_queue;

// pq_create() returns a new, empty priority queue
struct priority_queue pq_create();

// pq_destroy(priority_queue) destroys given priority_queue
//   (all priority queues must be destroyed before the program exits)
// effects: mutates priority_queue
void pq_destroy(struct priority_queue);

// pq_is_empty(priority_queue) returns 1 if priority_queue is empty
//   and 0 otherwise
int pq_is_empty(struct priority_queue);

// pq_top(priority_queue) returns the symbol at the top of priority_queue
// requires: priority_queue is not empty
struct symbol pq_top(struct priority_queue);

// pq_delete_top(priority_queue) removes the top element of priority_queue
// requires: priority_queue is not empty
// effects: mutates priority_queue
void pq_delete_top(struct priority_queue);

// pq_insert(priority_queue, elem, prio) inserts elem with priority prio into
//   given priority_queue
// effects: mutates priority_queue
void pq_insert(struct priority_queue, struct symbol elem, int prio);


////////////////////////////////////////////////////////////////////
////////  KEEP OUT !!!! ////////////////////////////////////////////

// implementation-specific types used in the sample implementation
struct pq_elems;
struct priority_queue{ struct pq_elems *x; };
