#include <stdlib.h>
#include <assert.h>
#include "tree.h"

/*// Secret tree node contains key, annotation for height,
// and pointers to roots of left and right subtrees
struct node {
  int key;
  int height;
  int size;
  int max;
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
  int subtree_size = 0;
  int subtree_max = 0;
  if (t->left != NULL) {
    subtree_height = t->left->height;
    subtree_size += t->left->size;
    subtree_max = t->left->max; }
  if (t->right != NULL) {
    subtree_size += t->right->size;
    if (t->right->height>subtree_height) {
      subtree_height = t->right->height; 
    }
    if (t->right->max>subtree_max) {
      subtree_max = t->right->max; 
    }   
  }
  t->height = 1 + subtree_height;
  t->size = 1 + subtree_size;
  t->max = subtree_max;
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
// DO NOT CHANGE print_helper. Marmoset relies on it.
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


int size(struct inttree *t){
  if (t->top == NULL) return 0;
  return t->top->size;
}*/



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

	if (t->left != NULL){ 
		size_temp += t->left->size;
		sum_temp += t->left->sum;
		height_temp = t->left->height + 1;
		if (t->left->max > max_temp) {
			max_temp = t->left->max;
		}
		max_temp = t->left->max;
	}
	if (t->right != NULL){ 
		size_temp += t->right->size;
		sum_temp += t->right->sum;
		if (t->right->height > height_temp) {
			height_temp = t->right->height + 1;
		}
		if (t->right->max > max_temp) {
			max_temp = t->right->max;
		}
	}
	t->size = size_temp;
	t->sum = sum_temp;
	t->height = height_temp;
	t->max = max_temp;
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

// 0) ---------------------------------------------------
int size(struct inttree *t){
  if (t->top == NULL) return 0;
	else return t->top->size;
}

