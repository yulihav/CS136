#include <stdio.h>
#include "intlist.h"
#include "getint.h"

int main(){
  struct intlist * l1 = empty();

  int c = getint();
  while (c != -1){
    addlast(l1,c);
    c = getint();
  }

  printf("length of l1-> %d\n",length(l1));
  /*printf("*********L1**********\n");
  printf("length of l1-> %d\n",length(l1));
   while (!isempty(l1)) {
     printf("%d\n",first(l1));
     dropfirst(l1);
   }
  printf("\n*********L2**********\n");
  printf("length of l2-> %d\n",length(l2));
  while (!isempty(l2)) {
     printf("%d\n",first(l2));
     dropfirst(l2);
   }

  printf("\n*********MERGE**********\n");
  merge(new,l1,l2);
  printf("length of l1-> %d\n",length(l1));
  printf("length of l2-> %d\n",length(l2));
  printf("length of new-> %d\n",length(new));*/
  merge_sort(l1);

  printf("\n*********NEW**********\n");
  printf("length of new-> %d\n",length(l1));
  while (!isempty(l1)) {
    printf("%d\n",first(l1));
    dropfirst(l1);}

  destroylist(l1);

}


