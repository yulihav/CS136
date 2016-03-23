/**
 File: lounge.c
A program to simulate the host of a nightclub. Customers wishing to be seated give the host a gratuity (i.e., a tip), 
and whenever a table becomes open, the host seats the customer who has given the highest gratuity 
(and has not yet been seated). If more than one customer has given the same gratuity, 
the one that has been waiting longest is seated first.
*/
#include <stdio.h>
#include "symbol.h"
#include "getint.h"
#include "pq.h"


struct priority_queue line; // = pq_create();

// lounge() has no output, but prints things according
// to the question description

int lounge(void) {
  
  struct symbol input = getsym();
  if (symeq(input,sym("arrive"))) {
    pq_insert(line, getsym(), getint());
    return lounge(); }
  if (symeq(input,sym("table"))) {
    if (pq_is_empty(line)) {
      printf("nobody to seat\n");
      return lounge(); }
    else { 
      printfsym("seat %s\n", pq_top(line));
      pq_delete_top(line);
      return lounge(); } }
  if (symeq(input,sym("close"))) {
    printf("lounge closed\n");
    pq_destroy(line);
    return 0; }
  else {
    return 0; }
}

int main() {
  line = pq_create(); 
  lounge();
  return 0; 
}