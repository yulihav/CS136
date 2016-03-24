#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include <stdio.h>
#include <limits.h>

/* RUNTIME COMMENT

Runtime is O(height t) because 
- in promote_helper_r, we recurse
down the left path at each step. In worst case, if that's the longest 
path to the top, it's equal to the height of the tree.

- in delete_helper_r, we recurse
down the right path at each step. In worst case, if that's the longest 
path to the top, it's equal to the height of the tree.

Summing these two runtimes together, 2*O(height t), we get O(height t)

*/

/*
// Secret tree node contains key, annotation for height,
// and pointers to roots of left and right subtrees
struct node {
   int key;
   int height;
   struct node *left, *right;
};

// Wrapper struct for ADT
struct inttree {
   struct node *top;
};

// Annotate is called whenever a node is modified
// Update "height" and any other tree annotations
static void annotate(struct node *t){
  assert(t != NULL);
  int subtree_height = 0;
  if (t->left != NULL) subtree_height = t->left->height;
  if (t->right != NULL && t->right->height > subtree_height)
    subtree_height = t->right->height;
  t->height = 1 + subtree_height;
}

// Return height of tree; relies on "height" annotation
int height(struct inttree *t){
  if (t->top == NULL) return 0;
  return t->top->height;
}

// Create an empty tree
struct inttree * create(){
  struct inttree * r = malloc(sizeof(struct inttree));
  r->top = NULL;
  return r;
}

// Private helper to insert e into subtree rooted at t
static struct node * insert_helper(struct node *t, int e){
   if (t == NULL){
      struct node *r = malloc(sizeof(struct node));
      r->key = e;
      r->left = r->right = NULL;
      annotate(r);
      return r;
   }
   if (e < t->key) t->left = insert_helper(t->left, e);
   if (t->key < e) t->right = insert_helper(t->right, e);
   // do not insert if already exists
   annotate(t);
   return t;
}

// Interface function to insert e into t
void insert(struct inttree *t, int e){
   t->top = insert_helper(t->top,e);
}

// Private helper function to add subtree rooted at new
// to subtree rooted at t (used by delete_helper)
static struct node * promote_helper(struct node *t, struct node *new){
   if (t == NULL) return new;
   t->right = promote_helper(t->right, new);
   annotate(t);
   return t;
}

// Private helper function to delete e from subtree rooted at t
static struct node * delete_helper(struct node *t, int e){
   if (t == NULL) return t;  // element not found; don't delete
   if (e < t->key) {
      t->left = delete_helper(t->left, e);
      annotate(t);
      return t;
   }
   if (t->key < e) {
      t->right = delete_helper(t->right, e);
      annotate(t);
      return t;
   }
   // promote left subtree, inserting right subtree into it
   struct node * n = promote_helper(t->left,t->right);
   free(t);
   return n;
}

// Interface function to delete e from t
void delete(struct inttree *t, int e){
   t->top = delete_helper(t->top,e);
}

// Private helper to free elements of subtree rooted at n
static void destroy_helper(struct node *n){
   if (n == NULL) return;
   destroy_helper(n->left);
   destroy_helper(n->right);
   free(n);
}

// Interface function to destroy t
void destroy(struct inttree *t){
   destroy_helper(t->top);
   free(t);
}

#include <stdio.h>
// DO NOT CHANGE print_helper.  Marmoset relies on it.
// Private helper to print subtree t indented d spaces
static void print_helper(struct node *t, int d){
   if (t == NULL) return;
   print_helper(t->right,d+1);
   for (int i=0; i<d;i++) printf(" ");
   printf("%d\n",t->key);
   print_helper(t->left,d+1);
}

// DO NOT CHANGE print.  Marmoset relies on it.
// Interface function to print t sideways
void print(struct inttree *t){
   printf("<<<<right<<<< (height %d)\n",height(t));
   print_helper(t->top,0);
   printf(">>>>left>>>>>\n");
}

/////////////////////////DELETE RIGHT///////////////////////////////////

// Private helper function to add subtree rooted at new
// to subtree rooted at t (used by delete_helper)
static struct node * promote_helper_r(struct node *t, struct node *new){
   if (t == NULL) return new;
   t->left = promote_helper_r(t->left, new);
   annotate(t);
   return t;
}

// Private helper function to delete e from subtree rooted at t
static struct node * delete_helper_r(struct node *t, int e){
   if (t == NULL) return t;  // element not found; don't delete
   
  if (e < t->key) {
      t->right = delete_helper_r(t->right, e);
      annotate(t);
      return t;
   }
   if (t->key < e) {
      t->left = delete_helper_r(t->left, e);
      annotate(t);
      return t;
   }
   // promote left subtree, inserting right subtree into it
   struct node * n = promote_helper_r(t->right,t->left);
   free(t);
   return n;
}

// Interface function to delete e from t
void delete_right(int e,struct inttree *t){
   t->top = delete_helper_r(t->top,e);
}
*/

// Assignment 10

// 0) ---------------------------------------------------

struct inttree {
	struct node * top;
};

struct node {
	int key;
	struct node * left;
	struct node * right;
	int size;
	int height;
	int sum;
	int max;
	int min;
};

struct inttree * create() {
	struct inttree * it = malloc(sizeof(struct inttree));
	it->top = NULL;
	return it;
}

void annotate(struct node *t) {
	int size_temp = 1;
	int sum_temp = t->key;
	int height_temp = 0;
	int max_temp = t->key;
	int min_temp = t->key;

	if (t->left != NULL){ 
		size_temp += t->left->size;
		sum_temp += t->left->sum;
		height_temp = t->left->height;
		if (t->left->max > max_temp) {
			max_temp = t->left->max;
		}
		if (t->left->min < min_temp) {
			min_temp = t->left->min;
		}
	}
	if (t->right != NULL){ 
		size_temp += t->right->size;
		sum_temp += t->right->sum;
		if (t->right->height > height_temp) {
			height_temp = t->right->height;
		}
		if (t->right->max > max_temp) {
			max_temp = t->right->max;
		}
		if (t->right->min < min_temp) {
			min_temp = t->right->min;
		}
	}
	t->size = size_temp;
	t->sum = sum_temp;
	t->height = height_temp+1;
	t->max = max_temp;
	t->min = min_temp;
}


struct node * insert_help(struct node *n, int e) {
	//if reached an empty node
	if (n == NULL) {
		struct node * new = malloc(sizeof(struct node));
		new->key = e;
		new->left = NULL;
		new->right = NULL;
		annotate(new);
		return new;
	}
  //if already in the tree
	else if (n->key == e) return n;
  
	else if (e < n->key) {
		n->left = insert_help(n->left,e);
	}
	else if (e > n->key) {
		n->right = insert_help(n->right,e);
	}
	annotate(n);
	return n;
}

void insert(struct inttree *t, int e) {
	t->top = insert_help(t->top,e);
}

void destroy_help(struct node *n) {
	if (n==NULL) return;
	destroy_help(n->left);
	destroy_help(n->right);
	free(n);
}

void destroy(struct inttree *t){ 
	destroy_help(t->top);
	free(t);
}



struct node * promote_l(struct node *t, struct node *new){
	if (t == NULL) return new;
	t->right = promote_l(t->right, new);
 	annotate(t);
 	return t;
}

struct node * delete_help(struct node *t, int e){
	if (t == NULL) return t;

	else if (e < t->key) {
		t->left = delete_help(t->left,e);
		annotate(t);
		return t;
	}
	else if (e > t->key) {
		t->right = delete_help(t->right,e);
		annotate(t);
		return t;
	}

	struct node *new = promote_l(t->left,t->right);
	free(t);
	return new;
	
}

void delete(struct inttree *t, int e){
  t->top = delete_help(t->top,e);
}

int height(struct inttree *t){
  if (t->top == NULL) return 0;
	else return t->top->height;
}


static void print_helper(struct node *t, int d){
  if (t == NULL) return;
  print_helper(t->right,d+1);
  for (int i=0; i<d;i++) printf(" ");
  printf("%d\n",t->key);
  print_helper(t->left,d+1);
}

// DO NOT CHANGE print.  Marmoset relies on it.
// Interface function to print t sideways
void print(struct inttree *t){
  printf("<<<<right<<<< (height %d)\n",height(t));
  print_helper(t->top,0);
  printf(">>>>left>>>>>\n");
}

// 0) ---------------------------------------------------
int size(struct inttree *t){
  if (t->top == NULL) return 0;
	else return t->top->size;
}



// 1) ---------------------------------------------------
int max(struct inttree *t){
	if (t->top == NULL) return INT_MIN;
	else return t->top->max;
}

// 2) ---------------------------------------------------

int sum_helper(int a, int b, struct node *n) {
	if (n == NULL) return 0;

	int sum = 0;
  
	//if none are in the range
	if (n->max < a || n->min > b) return 0;

	//if all are in the range
	else if ((n->max <= b) && (n->min >=a)) return n->sum;

	//if some are in the range
	else {
    if((n->key >= a) && (n->key <= b)) {
      sum += n->key;
    }
		sum += sum_helper(a,b,n->left);
		sum += sum_helper(a,b,n->right);
		return sum;
	}
}

//Return the sum of the elements in t that are between a and b, inclusive
int sumrange(int a, int b, struct inttree *t) {
	if (t==NULL) return 0;
	else return sum_helper(a,b,t->top);
}






// 4) ---------------------------------------------------

//Deletes the element e from t, by promoting the right subtree
// of the subtree rooted at e, and inserting the left subtree into it.
//The provided delete functions promotes the left subtree
// void delete_right(int e, struct inttree *t);
struct node * promote_r(struct node *right, struct node *left){
	if (right == NULL) return left;
	right->left = promote_r(right->left,left);
 	annotate(right);
 	return right;
}

struct node * delete_help_r(struct node *t, int e){

	// element not found; don't delete
	if (t == NULL) return t;

	else if (e < t->key) {
		t->left = delete_help(t->left,e);
		annotate(t);
		return t;
	}
	else if (e > t->key) {
		t->right = delete_help(t->right,e);
		annotate(t);
		return t;
	}

	struct node *new = promote_r(t->right,t->left);
	free(t);
	return new;
	
}
void delete_right(int e,struct inttree *t){
  t->top = delete_help_r(t->top,e);
}







