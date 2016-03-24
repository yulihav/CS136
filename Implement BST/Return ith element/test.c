/**
 File: test.c
Enter a description for this file.
*/
#include "tree.h"
#include <assert.h>
#include <stdio.h>


int main(void) {
  /*struct inttree *t = create();
  insert(t, 5);
  insert(t, 2000);
  insert(t, 0);
  insert(t, 9);
  insert(t, -600);
  insert(t, 8);
  insert(t, 900);
  printf("size - %d\n", size(t));
  printf("height - %d\n", height(t));
  printf("max - %d\n", max(t));
 // printf("min - %d\n", min(t));
  printf("sum - %d\n", sumrange(-100,100,t));*/
  struct inttree *t = create();
  insert(t, 50);
  insert(t, 35);
  insert(t, 100);
  insert(t, 60);
  insert(t, 15);
  insert(t, 7);
  print(t);
  printf("%d\n", ith(0, t));
  assert(ith(0, t) == 7);
  assert(ith(1, t) == 15);
  assert(ith(2, t) == 35);
  assert(ith(3, t) == 50);
  assert(ith(4, t) == 60);
  assert(ith(5, t) == 100);
  
  destroy(t);

  return 0;}