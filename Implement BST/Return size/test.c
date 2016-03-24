/**
 File: test.c
Enter a description for this file.
*/
#include "tree.h"
#include <assert.h>
#include <stdio.h>


int main(void) {
  struct inttree *t = create();
  insert(t, 5);
  insert(t, 10);
  insert(t, 0);
  insert(t, 9);
  insert(t, 19);
  insert(t, 8);
  insert(t, 7);
  printf("size - %d\n", size(t));
  printf("height - %d\n", height(t));
  //printf("max - %d\n", size(t));
  destroy(t);

  return 0;}