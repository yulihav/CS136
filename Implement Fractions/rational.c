#include <assert.h>
#include <stdio.h>
#include "rational.h"
#include "gcd.h"

// See interface for purpose statement and requirements
struct rational R(int n, int d) {
  assert(d != 0);
  // NOTE: we will see later why this is rarely done in C.
  // However, for now we will do this to make your code
  // easier to program and test
  const struct rational r = {n, d};
  return r;
}

// your implementation below:

// see header
struct rational r_simplify(struct rational a) {
  struct rational x;
  int div = gcd(a.num,a.den);
  x.num = a.num/div;
  x.den = a.den/div;
  if (x.den < 0 ) {
    x.den = x.den*(-1);
    x.num = x.num*(-1); }
  return x; }


// see header
struct rational r_add(struct rational a, struct rational b) {
  struct rational x;
  x.num = (a.num*b.den + b.num*a.den);
  x.den = (a.den*b.den);
  return r_simplify(x);
}

// see header
struct rational r_sub(struct rational a, struct rational b) {
  struct rational x;
  x.num = (a.num*b.den - b.num*a.den);
  x.den = (a.den*b.den);
  return r_simplify(x);
}

// see header
struct rational r_mult(struct rational a, struct rational b) {
  struct rational x;
  x.num = (a.num*b.num);
  x.den = (a.den*b.den);
  return r_simplify(x); }

// see header
struct rational r_div(struct rational a, struct rational b){
  struct rational x;
  x.num = (a.num*b.den);
  x.den = (a.den*b.num);
  return r_simplify(x); }

// see header
bool r_equal(struct rational a, struct rational b) {
  struct rational aSimp;
  struct rational bSimp;
  aSimp = r_simplify(a);
  bSimp = r_simplify(b);
  if ((aSimp.num == bSimp.num) && (aSimp.den == bSimp.den)) {
    return 1; }
  else {
    return 0;}
}




