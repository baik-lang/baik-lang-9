

// ////////////////////////////////////////////////////
// List Manipulation in C
// Copyright(c) Haris Hasanudin 2005 - 2010
//
// Untuk Bahasa Komputer Versi Bahasa Indonesia
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
// ////////////////////////////////////////////////////

//    void node_addFirst(struct node_list newlist);
//    void node_addLast(struct node_list newlistt);
//    void node_removeAll();
//    struct node_list node_removeLast(); 
//    struct node_list node_removeFirst();
//    struct node_list node_getElement(int n);
//    void node_setElement(int n, struct node_list newdatat);
//    void node_removeAt(int n); 
//    int node_getCount();
//    int node_isEmpty();
//    void node_insertAfter(int n, struct node_list newdata);
//    void node_insertBefore(int n, struct node_list newdata);
//    int node_findData(struct node_list data);
//    struct node_list node_getNext(); 
//    void node_setHeadposition();¡£

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void   node_addFirst(struct node_list newlist);
void   node_addLast(struct node_list newlist);
void   node_removeAll();
struct node_list node_removeLast();
struct node_list node_removeFirst();
struct node_list node_getElement(int n);
void   node_setElement(int n, struct node_list newdata);
void   node_removeAt(int n);
int    node_getCount();
int    node_isEmpty();
void   node_insertAfter(int n, struct node_list newdata);
void   node_insertBefore(int n, struct node_list newdata);

int    node_findData(struct node_list data);
void   class_findParams(struct node_list data);

struct node_list node_getNext();
void   node_setHeadposition();

void   class_params_init();

//
struct  node_list *pstart, *pend;
struct  node_list *ptr;

struct all_class_params class_params;

