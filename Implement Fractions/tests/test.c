/**
 File: test.c
Enter a description for this file.
*/
assert(r_equal(r_add(R(1,5),R(1,7)), R(12,35))); // 1/5 + 1/7 = 12/35
assert(r_equal(r_mult(R(1,5),R(1,7)), R(1,35))); // 1/5 * 1/7 = 1/35