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
  printf("max - %d\n", max(t));
  insert(t, 2000);
  printf("max - %d\n", max(t));
  insert(t, 0);
  printf("max - %d\n", max(t));
  insert(t, 9);
  printf("max - %d\n", max(t));
  insert(t, -600);
  printf("max - %d\n", max(t));
  insert(t, 8);
  printf("max - %d\n", max(t));
  insert(t, 900);
  printf("max - %d\n", max(t));
  print(t);
  printf("size - %d\n", size(t));
  printf("height - %d\n", height(t));
  printf("max - %d\n", max(t));
  delete(t,max(t));
  printf("max - %d\n", max(t));
  delete(t,max(t));
  printf("max - %d\n", max(t));
  delete(t,max(t));
  printf("max - %d\n", max(t));
  delete(t,max(t));
  printf("max - %d\n", max(t));
  delete(t,max(t));
  printf("max - %d\n", max(t));
  delete(t,max(t));
  printf("max - %d\n", max(t));
  delete(t,max(t));
  printf("max - %d\n", max(t));
  print(t);
  destroy(t);

  return 0;}