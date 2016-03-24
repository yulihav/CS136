/**
 File: test.c
Enter a description for this file.
*/
#include "tree.h"
#include <assert.h>
#include <stdio.h>


int main(void) {
  struct inttree *t = create();
  insert(t, 20);
  insert(t, 50);
  insert(t, 10);
  /*insert(t, 5);
  insert(t, 80);
  insert(t, 3);
  insert(t, 70);*/
  delete(t,20);
  //delete_right(20,t);
  print(t);
  destroy(t);

  return 0;}