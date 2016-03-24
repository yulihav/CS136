/**
 File: test.c
Enter a description for this file.
*/
#include "tree.h"
#include <assert.h>
#include <stdio.h>


int main(void) {
  
  struct inttree *x = create();
  insert(x,80000);
  insert(x, 7);
  insert(x, 6);
  insert(x, 5);
  insert(x, 4);
  insert(x, 8);
  insert(x, 9);
  insert(x, 10);
  print(x);
  printf("range sum x: %d\n", sumrange(0,10,x));
  
  struct inttree *t = create();
  insert(t, 5);
  insert(t, 6);
  insert(t, 7);
  insert(t, 8);
  insert(t, 2000);
  insert(t, 0);
  insert(t, 9);
  insert(t, -600);
  insert(t, 8);
  insert(t, 900);
  print(t);
  printf("range sum t: %d\n", sumrange(0,10,t));
  
  struct inttree *t2 = create();
  insert(t2, 30);
  insert(t2, 50);
  insert(t2, 25);
  insert(t2, 2000);
  insert(t2, 3000);
  print(t2);
  printf("range sum t2: %d\n", sumrange(28,55,t2));
  assert(sumrange(28, 55, t2) == 80);
  
  struct inttree *t3 = create();
  insert(t3, 30);
  insert(t3, 50);
  insert(t3, 25);
  insert(t3, 28);
  insert(t3, 55);
  assert(sumrange(-28, 5555, t3) == 188);
  
  destroy(x);
  destroy(t);
  destroy(t2);
  destroy(t3);

  return 0;}