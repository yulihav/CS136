#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "intlist.h"
//comments at bottom

struct intlist {
  struct node *f;
  struct node *b;
  int length;
};

struct node {
  int car;
  struct node *cdr;
};

void addfirst(int e, struct intlist *l){
  struct node * r = malloc(sizeof(struct node));
  r->car = e;
  r->cdr = l->f;
  l->f = r;
  if (l->f == NULL) {
    l->b = r;}
  l->length++;
}

struct intlist * empty(){
  struct intlist * r = malloc(sizeof(struct intlist));
  r->f = NULL;
  r->b = NULL;
  r->length = 0;
  return r;

}

int isempty(struct intlist * l){
  return l->f == NULL;
}

int first(struct intlist * l){
  assert (!isempty(l));
  return l->f->car;
}

void dropfirst(struct intlist * l){
  assert(!isempty(l));
  struct node *t = l->f;
  l->f = l->f->cdr;
  l->length--;
  free(t);
}

void destroylist(struct intlist *l){
  while (!isempty(l)) dropfirst(l);
  free(l);
}

int length(struct intlist * x) {
  return x->length; 
}

int last(struct intlist * x){
  assert (!isempty(x));
  return x->b->car;
}

void addlast(struct intlist * x, int e) {
  struct node *r = malloc(sizeof(struct node)); 
  r->car = e;
  r->cdr = NULL;
  if (x->f == NULL) { // empty list
    x->f = r;
    x->b = r;
  } else {
    x->b->cdr = r;
    x->b = r;
  }
  x->length++;
}


// move the the first floor(length(x)/2) elements from x into a
// leave the remaining elements in x
// running time: O(length(x))
// space: O(1)
// effects: Modifies x and a
void split(struct intlist *x, struct intlist *a){
  if (x->length == 0) {return;}
  else {
    int half = x->length/2;
    for (int i = 0; i < half; i++) {
      addlast(a,first(x));
      dropfirst(x);}
  }
}

void merge(struct intlist *x, struct intlist *a, struct intlist *b){
  int n = a->length + b->length;


  if ((a->f == NULL)&&(b->f == NULL)) {
    return;}
  for (int j = 0; j < n-1; j++) { 
    if(b->f == NULL || a->f == NULL) {break;}
    else if(first(a) < first(b)) {
      addlast(x,first(a));
      dropfirst(a);} 
    else {
      addlast(x,first(b));
      dropfirst(b);}}
  if(b->f == NULL){ 
    while(a->f != NULL) {
      addlast(x,first(a));
      dropfirst(a);}}
  else {
    while(b->f != NULL) {
      addlast(x,first(b));
      dropfirst(b);}}
}

/*// sorts x into ascending order
// running time: O(n log n) where n is the length of x.
// heap space: O(1)
// stack space: O(log n)
// effects: Modifies x
*/

// see header file.
void merge_sort (struct intlist *x) {
  assert(x->length >= 0);
  //int half = x->length;

  // Base Case
  if (x->length <= 1) {
    return;
    // Recursive Case
  } else {
    struct intlist * temp = empty();
    struct intlist * new = empty();
    // Divide the array in two.
    split(x,temp);

    // Sort the two halves.
    merge_sort(x);
    merge_sort(temp);
    merge(new,x,temp);
    
    //move all the elemets back into x.
    int len = new->length;
    for (int i = 0; i < len; i++) {
      addlast(x,first(new));
      dropfirst(new);}

    // Free the temperary arrays.
    destroylist(temp);
    destroylist(new);
  }
}

/*
running time: O(n log n) 

Merge-sort performs two operations - diving and merging

Dividing: the n-element list gets divided into halves until we have n
single element lists.
Doing this takes log n steps in base 2. -- O(log n)

Merging: the number of steps to accomplish this task grows 
proportionally to n (since we broke our list down into n lists).
So the runtime of this process is linear with n steps — O(n). 

This process happens at every step of the dividing part.

Combining the two, we get n*logn = O(n log n)

space: O(1) because the expression does not grow. 
Every time we make a new list, we delete it
Every time we add from one list, we remove from another
We never create additional space without removing space from somewhere else
*/