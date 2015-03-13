// ////////////////////////////////////////////////////
// List Manipulation in C
// Copyright(c) Haris Hasanudin 2005 2015
// Untuk Bahasa Komputer Versi Bahasa Indonesia
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
// ////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct dbl_list{
    long     stackid;           // id to connect with stackDbl_list

    int      idx;              // arry contents : pos of array
    double   mydbl;            // arry contents : double array [dbl0, dbl1, dbl2, ...]

    struct dbl_list *pnext;  
};

struct stackDbl_list{
    long      stackid;          // id to connect with dbl_list

    char     array_name[256];  // variable name of array

    struct stackDbl_list *pnext; 
};

struct  stackDbl_list *pstartD, *pendD;
struct  stackDbl_list *ptrD;

struct  dbl_list *pstartdbl, *penddbl;
struct  dbl_list *ptrdbl;


typedef struct dbl_array {
  struct dbl_list dbl;
  struct stackDbl_list  var;
} DBL_ARRY;

void   stackDbl_push(struct stackDbl_list newlist);
void   stackDbl_addFirst(struct stackDbl_list newlist);
long   stackDbl_getID(struct stackDbl_list data);
void   stackDbl_removeAll(void);
int    stackDbl_getPos(struct stackDbl_list data);
struct stackDbl_list stackDbl_removeFirst(void);
void   stackDbl_removeAt(int n);

void   dbl_addFirst(struct dbl_list newlist);
void   dbl_push(struct dbl_list newlist);
void   dbl_removeAll(void);
void   dbl_removeAt(int n);
struct dbl_list dbl_pop(void);
struct dbl_list dbl_removeFirst(void);
struct dbl_list dbl_getElement(int n);
void   dbl_setElement(int n, struct dbl_list newdata);
int    dbl_getCount(void);
int    dbl_isEmpty(void);
int    dbl_findData(struct dbl_list data);
int    dbl_getIDX(struct dbl_list data);
void   dbl_printData(void);
struct dbl_list dbl_getNext(void);
void   dbl_setHeadposition(void);
