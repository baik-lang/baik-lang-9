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

struct int_list{
    long     stackid;           // id to connect with stackInt_list

    long     idx;              // arry contents : pos of array
    long     myint;            // arry contents : integer array [int0, int1, int2, ...]

    struct int_list *pnext; 
};

struct stackInt_list{
    long      stackid;          // id to connect with int_list

    char     array_name[256];  // variable name of array

    struct stackInt_list *pnext; 
};

typedef struct int_array {
  struct int_list       val;
  struct stackInt_list  var;
} INT_ARRY;

struct  stackInt_list *pstartI, *pendI;
struct  stackInt_list *ptrI;

struct  int_list *pstartint, *pendint;
struct  int_list *ptrint;

void   stackInt_push(struct stackInt_list newlist);
void   stackInt_addFirst(struct stackInt_list newlist);
long   stackInt_getID(struct stackInt_list data);
int    stackInt_getPos(struct stackInt_list data);
struct stackInt_list stackInt_removeFirst(void);
void   stackInt_removeAt(int n);

void   int_addFirst(struct int_list newlist);
void   int_push(struct int_list newlist);
void   int_removeAll(void);
void   int_removeAt(int n);
struct int_list int_pop(void);
struct int_list int_removeFirst(void);
struct int_list int_getElement(int n);
void   int_setElement(int n, struct int_list newdata);
int    int_getCount(void);
int    int_isEmpty(void);
int    int_findData(struct int_list data);
int    int_getIDX(struct int_list data);
void   int_printData(void);
struct int_list int_getNext(void);
void   int_setHeadposition(void);

