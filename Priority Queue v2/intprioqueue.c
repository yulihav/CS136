/**
 [Yuliana Havryshchuk] (20514228)
 CS136 Fall 2015
 Assignment 6, Problem 3
 File: intprioqueue.c
 Implements a priority queue with the operations described below:
**/
#include "intprioqueue.h"
#include <limits.h>
#include <stdio.h>
/*
// see header
struct intprioqueue new_intpq() {
  // creates a struct with the arrays and size initialized to 0
  struct intprioqueue pq = {{0}, {0}, 0};
  return pq;
}

// see header
int intpq_empty(struct intprioqueue q) {
  if (q.size == 0) return 1;
  else return 0;
}

// see header
int intpq_head(struct intprioqueue q) {
  
  // find highest prio and its position
  int HiPrio = q.prios[0];
  int HiPos = 0;
  for (int i = 0 ; i < q.size ; i++) {
    if (q.prios[i] > HiPrio) {
      HiPrio = q.prios[i] ;
      HiPos = i; } }
  
  // return the name at that position 
  return q.names[HiPos];
}

// see header
void intpq_insert(struct intprioqueue * q, int e, int p) {
  // insert an element to the end of the element array
	q->names[q->size] = e;
  // insert a prio to the end of the priority array
  q->prios[q->size] = p;
  // increase the size count by 1
  (q->size)++;
}

// see header
void intpq_delete(struct intprioqueue * q) {

  // find highest priority and its position
  int HiPrio = q->prios[0];
  int HiPos = 0;
  for (int i = 0 ; i < q->size ; i++) {
    if (q->prios[i] > HiPrio) {
      HiPrio = q->prios[i] ;
      HiPos = i; }}
  
  // these are used to help in overwriting the arrays
  int CountNames = 0;
  int CountPrios = 0;
    
  // loop through elements array
  for (int j = 0; j < q->size ; j++) {
    
    // if the element is not in the position we determined to have the 
    // highest prio, rewrite it there
    if (j != HiPos) {
      q->names[j-CountNames] =  q->names[j];}
    
    // otherwise don't rewrite it, but add 1 to countnames so that all other
    // elements are inserted a spot earlier
    else {
      CountNames = 1; } }
  
  // do the same for the list of priorities
  for (int j = 0; j < q->size ; j++) {
    if (j != HiPos) {
      q->prios[j-CountPrios] =  q->prios[j];}
    else {
      CountPrios = 1; } }
  
  // decrease the size count
  q->size--;
}*/



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















