struct intlist;

struct intlist * empty();   // returns an empty list
void addfirst(int e, struct intlist * l);  // add e as first element to l
int isempty(struct intlist * l); // returns 0 if l empty; 1 otherwise
int first(struct intlist * l); // return first element of l; l must not be empty
void dropfirst(struct intlist * l); // remove first element of l; l must not be empty
void destroylist(struct intlist * l); // destroy l
int length(struct intlist * x); // returns the number of elements in x 
int last(struct intlist * x);   // returns the last element of x; must not be empty
void addlast(struct intlist * x, int e); // adds e as the last element of x

// move the the first floor(length(x)/2) elements from x into a
// leave the remaining elements in x
// running time: O(length(x))
// space: O(1)
// effects: Modifies x and a
void split(struct intlist *x, struct intlist *a);

// require that a and b be in ascending order
// move all elements from a and b to x, in ascending order
// destroy a and b
// running time: O(length(a)+length(b))
// space: O(1)
// effects: Modifies x
void merge(struct intlist *x, struct intlist *a, struct intlist *b);

// sorts x into ascending order
// running time: O(n log n) where n is the length of x.
// heap space: O(1)
// stack space: O(log n)
// effects: Modifies x
void merge_sort(struct intlist *x); 
