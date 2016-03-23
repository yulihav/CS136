// This module provides some simple functions for working with a symbol ADT

// ADT for symbol
struct symbol;

// symeq(a,b) returns 1 if a and b are the same symbol and 0 otherwise
// examples:
//   symeq(sym("a"),sym("a")) returns 1
//   symeq(sym("a"),sym("b")) returns 0
int symeq(struct symbol a, struct symbol b);

// sym(s) returns a symbol which has symbol name s
// examples:
//   sym("a") returns the symbol a
//   sym("foo") returns the symbol foo 
struct symbol sym(char *s);

// getsym() returns a symbol whose symbol name was read from typed input
// effects: reads typed input
// example:
//   given that there is no typed input to be read and then "qwerty"
//   followed by a newline is typed,
//   getsym() returns the symbol qwerty
struct symbol getsym();

// printfsym(s,x) prints the string s to the screen with the placeholder "%s" in
//   s replaced by the symbol name of x
// effects: prints a message to the screen
// requires: the string s contains exactly one instance of the placeholder %s
// example:
//   printfsym("the symbol name is %s\n", sym("foo")) prints
//   "the symbol name is foo" to the screen on one line
void printfsym(char *s, struct symbol x);


////////////////////////////////////////////////////////////////////
////////  KEEP OUT !!!! ////////////////////////////////////////////

#ifndef SYMBOL_INCLUDED
   // implementation-specific type used in the sample implementation
   struct symbol { char x[100]; };
   #define SYMBOL_INCLUDED 1
#endif
