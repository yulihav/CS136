#include <stdio.h>

// append_char(const int acc) returns the int whose decimal representation
//   consists of the digits of acc followed by the next character to be
//   read from typed input
static int append_char(const int acc) {
  const int c = getchar();
  if (c == '0') return append_char(10*acc+0);
  if (c == '1') return append_char(10*acc+1);
  if (c == '2') return append_char(10*acc+2);
  if (c == '3') return append_char(10*acc+3);
  if (c == '4') return append_char(10*acc+4);
  if (c == '5') return append_char(10*acc+5);
  if (c == '6') return append_char(10*acc+6);
  if (c == '7') return append_char(10*acc+7);
  if (c == '8') return append_char(10*acc+8);
  if (c == '9') return append_char(10*acc+9);
  return acc;
}
  
// See interface for purpose statement
int getint(void) {
  const int c = getchar();
  if (c == EOF) return -1;
  if (c == '0') return append_char(0);
  if (c == '1') return append_char(1);
  if (c == '2') return append_char(2);
  if (c == '3') return append_char(3);
  if (c == '4') return append_char(4);
  if (c == '5') return append_char(5);
  if (c == '6') return append_char(6);
  if (c == '7') return append_char(7);
  if (c == '8') return append_char(8);
  if (c == '9') return append_char(9);
  return getint();
}

