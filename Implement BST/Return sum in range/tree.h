/* Binary Search Tree interface for use in CS136 Fall 2015
   Author:  Gordon V. Cormack
   Description:
      "struct inttree" is an abstract data type that maintains 
      a binary search tree with distinct int elements.
*/

struct inttree; // definition is secret

struct inttree * create(); /* return a new, empty BST;
                              O(1) time */
void insert(struct inttree *t, int e); /* add element e to t;
                               do nothing if e already in t;
                               O(height(t)) time */
void delete(struct inttree *t, int e); /* delete e from t;
                               do nothing if e not in t;
                               O(height(t)) time */
void destroy(struct inttree *t); /*destroy t; O(n) time */
void print(struct inttree *t); /* print t sideways; O(n) time */
int height(struct inttree *t); /* height of t; O(1) time */

/* The following functions must be implemented for assignment
   10.
   */

/* A10p0 -- return the number of elements in t, O(1) time */
int size(struct inttree *t);

/* A10p1 -- return the maximum element in t, O(1) time */
int max(struct inttree *t);
int min(struct inttree *t);

/* A10p2 -- return the sum of the elements in t that 
   are between a and b, inclusive.  O(height(t)) time */
int sumrange(int a, int b, struct inttree *t);

//helper for testing
int allsum(struct inttree *t);

