struct intvec;                   
struct intvec intvec_create();       
void intvec_destroy(struct intvec);  
int intvec_size(struct intvec);  
void intvec_shrink(struct intvec);    
void intvec_grow(struct intvec, int e); 
int intvec_nth(struct intvec, int n);
void intvec_set_nth(struct intvec, int n, int e);

////////////////////////////////////////////////////////////////////
////////  KEEP OUT !!!! ////////////////////////////////////////////

struct intvec{ struct intvec_elems *x; };

