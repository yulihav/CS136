/**
 [Yuliana Havryshchuk] (20514228)
 CS136 Fall 2015
 Assignment 8, Problem 3
 File: strsort.c
 reads a sequence of strings from input, and prints the sequence 
 in ascending lexicographic order, with one element per line.
**/

//O(n log n) running time and consume O(n) space, where n is the length of the input sequence
// details below

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct string {
  char *chars;
  int chars_len;
  int chars_max;
};

struct ArrOfString {
  struct string *chars;
  int chars_len;
  int chars_max;
};

//has O(n log n) runtime according to notes 
void merge(int n, struct string *a) {
   if (n < 2) return;
   int m = n/2;       // mid point
   merge(m,a);
   merge(n-m,a+m);
   
   struct string t[n];
   int i=0;
   int j=0;
   
  while (i<m && j<n-m){
      if (strcmp(a[i].chars,a[m+j].chars)<0) {
         t[i+j] = a[i];
         i++;
      } else {
         t[i+j] = a[m+j];
         j++;
      }
   }
   while (i<m) {
      t[i+j] = a[i];
      i++;
   }
   while (j<n-m) {
      t[i+j] = a[m+j];
      j++;
   }
   for (i=0;i<n;i++) a[i] = t[i];
}


int main() {
  struct string s = {NULL,0,10};
  struct ArrOfString a = {NULL,0,10};
 
  int input = getchar(); //O(1)
  while (input != EOF) {
    // GET ONE SYM
    
    // consumes at most 2*O(n)= O(n) space, at best O(n)
    // because we double the array in size ever time we 
    // reach the limit
    
    // has O(n) runtime where n is the number of inputs since malloc
    // and realloc and getchar() are O(1)
    // and we're calling them n times 
    
    while (!isspace(input)  && input != EOF ) {
        if (s.chars_len == 0) {
          s.chars = malloc(sizeof(char)*s.chars_max);} 
        else if (s.chars_len == s.chars_max) {
          s.chars_max *= 2;
          s.chars=realloc(s.chars,sizeof(char)*(s.chars_max));}
      s.chars[s.chars_len] = input;
      s.chars_len++;
      input = getchar();}
    
    //PUT SYM INTO ARRAY OF SYMS
   if (s.chars_len != 0 ) {
    // has O(n) runtime where n is the number of inputs since malloc
    // and realloc and getchar() are O(1)
    // and we're calling them n times 
     s.chars[s.chars_len] = '\0';
    
      if (a.chars_len == 0) {
        a.chars = malloc(sizeof(struct string)*a.chars_max);} 
      else if (a.chars_len == a.chars_max) {
        a.chars_max *= 2;
        a.chars=realloc(a.chars,sizeof(struct string)*(a.chars_max));}
      a.chars[a.chars_len] = s;
      a.chars_len++;

      s.chars_len=0;
      s.chars_max=10;
      input = getchar();
    }
  else {
    input = getchar();}
  }
  
  merge(a.chars_len,a.chars); // n*O(log n) by definition
  
  //printf is O(1) n times 
  for (int i = 0; i < a.chars_len; i++) {
    for(int j = 0; j < a.chars[i].chars_len; j++) {
      printf("%c",a.chars[i].chars[j]);}
    printf("\n");}
  
  // free is O(1) and we're calling it n times where n is the number of strings
   for(int i = 0; i < a.chars_len; i++)  {
    free(a.chars[i].chars); }
  free(a.chars);

  // slowest runtime is O(n log n)
}
