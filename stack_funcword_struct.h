// ////////////////////////////////////////////////////
// List Manipulation in C
// Copyright(c) Haris Hasanudin 2005 2010
//
// Untuk Bahasa Komputer Versi Bahasa Indonesia
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
// ////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// Stack funcword //////////////////////////////////////////////////////

struct funcword_list{
    int     enumid;            // id for enum

    char     funcname[64];     // lang funcname ['func1','func2','func3', ...]
    char     alias[64];        // alias for funcname

	VAL_LABEL retVal;          // return val

    struct funcword_list *pnext;  
};


void   funcword_addFirst(struct funcword_list newlist);
void   funcword_push(struct funcword_list newlist);
void   funcword_removeAll(void);
void   funcword_removeAt(int n);
struct funcword_list funcword_pop(void);
struct funcword_list funcword_removeFirst(void);
struct funcword_list funcword_getElement(int n);
void   funcword_setElement(int n, struct funcword_list newdata);
int    funcword_getCount(void);
int    funcword_isEmpty(void);
int    funcword_findPos(struct funcword_list data);
int    funcword_getEnum(struct funcword_list data);
void   funcword_printData(void);
struct funcword_list funcword_getNext(void);
void   funcword_setHeadposition(void);

