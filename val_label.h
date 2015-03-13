
// Stack Prototype
void   varstack_addFirst(struct varstack_list newlist);
void   varstack_push(struct varstack_list newlist);
void   varstack_removeAll(void);
struct varstack_list varstack_pop(void);
struct varstack_list varstack_removeFirst(void);
struct varstack_list varstack_getElement(int n);
void   varstack_setElement(int n, struct varstack_list newdata);
void   varstack_removeAt(int n);
long   varstack_getCount(void);
int    varstack_isEmpty(void);
long   varstack_findData(struct varstack_list data);
struct varstack_list varstack_getNext(void);
void   varstack_setHeadposition(void);
void   varstack_printData(void);

VAL_LABEL *MakeValLabelTree( char *ident, VAL_LABEL valdat );
void AddValLabelTree( VAL_LABEL *t, VAL_LABEL *n );
int MakeAddValLabelTree( VAL_LABEL *t, char *ident, VAL_LABEL valdat );
VAL_LABEL *SearchValLabelTree( VAL_LABEL *t, char *ident );
VAL_LABEL *SearchGLBLabelTree( VAL_LABEL *t, char *ident );
void DeleteValLabelTree( VAL_LABEL *t );
void PrintValLabelTree( VAL_LABEL *t );

VAL_LABEL ValLabel( char *ident, int deep, VAL_LABEL valdat, int flag );

