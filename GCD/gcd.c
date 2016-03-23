/**
 File: gcd.c
**/
#include <stdio.h>

//see header
int gcd(const int a, const int b) {
  if ((a == b)||(b == 0)) { 
    return a;}
  if (a == 0) { 
    return b;}
  else {
    int r = a % b;
    return gcd(b,r);}
}
 
//see header
int lcm(const int a, const int b) {
  return (a*b / gcd(a,b));
}



