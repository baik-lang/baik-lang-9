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


// Stack String
struct string_list{
    long     stackid;           // id to connect with stackStr_list

    int      idx;              // arry contents : pos of array
    char     mystring[300];    // arry contents : string array ['name1','name2','name3', ...]

    struct string_list *pnext;  
};

struct stackStr_list{
    long      stackid;          // id to connect with string_list

    char     array_name[256];  // variable name of array

    struct stackStr_list *pnext; 
};

typedef struct string_array {
  struct string_list str;
  struct stackStr_list  var;
} STR_ARRY;

struct  stackStr_list *pstartS, *pendS;
struct  stackStr_list *ptrS;

struct  string_list *pstartstr, *pendstr;
struct  string_list *ptrstr;

void   stackStr_push(struct stackStr_list newlist);
void   stackStr_addFirst(struct stackStr_list newlist);
long   stackStr_getID(struct stackStr_list data);
void   stackStr_removeAll(void);
int    stackStr_getPos(struct stackStr_list data);
struct stackStr_list stackStr_removeFirst(void);
void   stackStr_removeAt(int n);

void   string_addFirst(struct string_list newlist);
void   string_push(struct string_list newlist);
void   string_removeAll(void);
void   string_removeAt(int n);
struct string_list string_pop(void);
struct string_list string_removeFirst(void);
struct string_list string_getElement(int n);
void   string_setElement(int n, struct string_list newdata);
int    string_getCount(void);
int    string_isEmpty(void);
int    string_findData(struct string_list data);
int    string_getIDX(struct string_list data);
void   string_printData(void);
struct string_list string_getNext(void);
void   string_setHeadposition(void);



