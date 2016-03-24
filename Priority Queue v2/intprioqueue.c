/**
 File: intprioqueue.c
 Implements a priority queue with the operations described below:
**/
#include "intprioqueue.h"
#include <limits.h>
#include <stdio.h>

// Returns an empty intprioqueue
struct intprioqueue new_intpq() {
	struct intprioqueue pq = {{0},{0},0,INT_MIN};
  return pq;
}

//Returns 1 if q is empty; 0 otherwise.
int intpq_empty(struct intprioqueue q){
	return (q.size ==0);
}

// Returns element of q with the highest priority. 
// If many elements have the highest priority, returns the oldest with the highest priority. 
// q must not be empty. 
int intpq_head(struct intprioqueue q) {
	for (int i = 0; i < q.size ; i++) {
		if (q.prios[i]==q.hiprio) {
			return q.ints[i];
		}
	}
  return 0;
}


// Insert element e with priority p into q. 
//Requires that m < n + 1000, where m is the total number of times intq_insert has been called, 
// and n is the number of times times intq_delete has been called, with q as a parameter.
void intpq_insert(struct intprioqueue * q, int e, int p){
	q->ints[q->size]=e;
	q->prios[q->size]=p;
	(q->size)++;
	if (p > q->hiprio){
		q->hiprio = p;
	}
}


// Remove the element of q with the highest priority. 
// If many elements have the highest priority, remove the oldest with the highest priority. 
// q must not be empty.
void intpq_delete(struct intprioqueue * q) {
	int i = 0;

	while (q->prios[i] != q->hiprio) {
		i++;
	}
	for(int j = i; j < q->size -1; j++) {
		q->prios[j] = q->prios[j+1];
		q->ints[j] = q->ints[j+1];
	}
	(q->size)--;

	int HI = INT_MIN;
	for (int k = 0; k < q->size; k++) {
		if(q->prios[k] > HI){
			HI = q->prios[k];
		}
	}
	q->hiprio = HI;
}















