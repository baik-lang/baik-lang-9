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

INT_ARRY GlbIntBox;

void stackInt_push(struct stackInt_list newlist){
    struct    stackInt_list *ptr2;

    ptr2 = NULL;
    ptr2 = (struct stackInt_list*)malloc(sizeof(struct stackInt_list));

    if(ptr2 == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    if ( pendI )
        pendI->pnext = ptr2;
    else
        pstartI = ptr2;

    pendI = ptr2;

    *pendI = newlist;

    pendI->pnext = NULL;
}

void stackInt_addFirst(struct stackInt_list newlist){
    struct stackInt_list *ptr2;

    ptr2 = NULL;
    ptr2 = (struct stackInt_list*)malloc(sizeof(struct stackInt_list));

    if(ptr2 == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    *ptr2 = newlist;

    ptr2->pnext = pstartI;

    pstartI = ptr2;
    
}

void stackInt_removeAll(){
    struct stackInt_list *p, *pnext;

    p = NULL;
    pnext = NULL;

    for ( p = pstartI ; p ; p = pnext ){
        pnext = p->pnext;
        free( p );
    }

    pendI = pstartI = NULL;
}

long stackInt_getID(struct stackInt_list data){
    struct stackInt_list *ptr2;
    long ret = -1;

    ptr2 = NULL;

    for ( ptr2 = pstartI ; ptr2 ; ptr2 = ptr2->pnext ){
        if ( strncmp(data.array_name, ptr2->array_name, strlen(data.array_name)) == 0 ) {
            ret = ptr2->stackid;
            return (long)ret;
        }
    }

    return ret;
}

int stackInt_getPos(struct stackInt_list data){
    struct stackInt_list *ptr2;
    long i = 0;

    ptr2 = NULL;

    for ( ptr2 = pstartI ; ptr2 ; ptr2 = ptr2->pnext ){
        if ( strncmp(data.array_name, ptr2->array_name, strlen(data.array_name)) == 0 )
            return i;
        i++;
    }

    return -1;
}

struct stackInt_list stackInt_removeFirst(){
    struct stackInt_list ret;

    memset(&ret, '\0', sizeof(ret));
    ret.stackid = '\0';
    memset(&ret.array_name, '\0', sizeof(ret.array_name));

    if ( pstartI ){

        ret = *pstartI;

        free( pstartI );

        pstartI = ret.pnext;

        if ( !pstartI )
            pendI = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

void stackInt_removeAt(int n){
    struct stackInt_list *ptr2, *ppre;

    ptr2 = NULL; ppre = NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        stackInt_removeFirst();
        return;
    }

    if ( !pstartI )
        return;

    ppre = pstartI;
    ptr2  = pstartI->pnext;
    n--;

    while( ptr2 ){
        if ( n-- == 0 ){
            ppre->pnext = ptr2->pnext;

            free ( ptr2 );

            return;
        }
        ppre = ptr2;
        ptr2  = ptr2->pnext;
    }
    
}


// ---

void int_push(struct int_list newlist){
    struct    int_list *ptr2;

    ptr2 = NULL;
    ptr2 = (struct int_list*)malloc(sizeof(struct int_list));

    if(ptr2 == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    if ( pendint )
        pendint->pnext = ptr2;
    else
        pstartint = ptr2;
    pendint = ptr2;

    *pendint = newlist;

    pendint->pnext = NULL;
}

//
void int_addFirst(struct int_list newlist){
    struct int_list *ptr2;

    ptr2 = NULL;
    ptr2 = (struct int_list*)malloc(sizeof(struct int_list));

    if(ptr2 == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    *ptr2 = newlist;

    ptr2->pnext = pstartint;

    pstartint = ptr2;
}


//
void int_removeAll(){
    struct int_list *p, *pnext;

    p = NULL;
    pnext = NULL;

    for ( p = pstartint ; p ; p = pnext ){
        pnext = p->pnext;
        free( p );
    }

    pendint = pstartint = NULL;
}


//
struct int_list int_removeFirst(){
    struct int_list ret;

    memset(&ret, '\0', sizeof(ret));

    if ( pstartint ){

        ret = *pstartint;

        free( pstartint );

        pstartint = ret.pnext;

        if ( !pstartint )
            pendint = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

//
struct int_list int_pop(){
    struct int_list ret;

    memset(&ret, '\0', sizeof(ret));

    if ( pendint ){
        struct int_list *ptr2;

        ret = *pendint;

        for ( ptr2 = pstartint ; ptr2 ; ptr2 = ptr2->pnext ){
            if ( ptr2->pnext == pendint ) {
                ptr2->pnext = NULL;
                break;
            }
        }

        free ( pendint );

        pendint = ptr2;

        if ( !pendint )
            pstartint = NULL;

    }
    ret.pnext = NULL;
    return ret;
}

//
struct int_list int_getElement(int n){
    struct int_list *ptr2;
    struct int_list ret;

    ptr2 = NULL;
    memset(&ret, '\0', sizeof(ret));
    ret.pnext = NULL;

    if ( n < 0 )
        return ret;

    for ( ptr2 = pstartint ; ptr2 ; ptr2 = ptr2->pnext ){
        if ( n-- == 0 )
            return *ptr2;
    }

    return ret;
}

//
void int_removeAt(int n){
    struct int_list *ptr2, *ppre;

    ptr2=NULL;
    ppre=NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        int_removeFirst();
        return;
    }

    if ( !pstartint )
        return;

    ppre = pstartint;
    ptr2  = pstartint->pnext;
    n--;

    while( ptr2 ){
        if ( n-- == 0 ){
            ppre->pnext = ptr2->pnext;

            free ( ptr2 );

            return;
        }
        ppre = ptr2;
        ptr2  = ptr2->pnext;
    }
    
}

//
void int_setElement(int n, struct int_list newdata){
    struct int_list *ptr2;
    struct int_list *pnext;

    ptr2 = NULL;  pnext = NULL;

    if ( n < 0 )
        return;

    for ( ptr2 = pstartint ; ptr2 ; ptr2 = ptr2->pnext ){
        if ( n-- == 0 ){
            pnext = ptr2->pnext;
            *ptr2 = newdata;
            ptr2->pnext = pnext;
            return;
        }
    }
}

//
int int_getCount(){
    struct int_list *ptr2;
    long n = 0;

    ptr2 = NULL;

    if ( pstartint ){
	for ( ptr2 = pstartint ; ptr2 ; ptr2 = ptr2->pnext ) {
          // printf("inside getCount ptr : n %d idx %d id %d str %s\n", n, ptr->idx, ptr->stackid, ptr->mystring);
          n++;
	}
    }
    return n;
}


//
int int_isEmpty(){
    return pstartint ? 0 : 1;
}

//
int int_findData(struct int_list data){
    struct int_list *ptr2;
    long i = 0;

    ptr = NULL;

    //printf("look for data   : %d idx %d %d : %d\n", i, data.idx, data.stackid, data.myint);
    for ( ptr2 = pstartint ; ptr2 ; ptr2 = ptr2->pnext ){
		//printf("inside find ptr : %d idx %d %d : %d\n", i, ptr->idx, ptr->stackid, ptr->myint);
		//printf("look for data   : %d idx %d %d : %d\n", i, data.idx, data.stackid, data.myint);
		// printf("---\n");

        if ( 
             data.stackid == ptr2->stackid && data.idx == ptr2->idx )
            return i;
        i++;
    }

	// clear memory
	memset(&data, '\0', sizeof(data));

    return -1;
}

int int_getIDX(struct int_list data){
    struct int_list *ptr2;

    ptr2 = NULL;

    for ( ptr2 = pstartint ; ptr2 ; ptr2 = ptr2->pnext ){
        if ( data.myint == ptr2->myint &&
             data.stackid == ptr2->stackid )
            return ptr2->idx;
    }

    return -1;
}

//
void int_printData(void){
    struct int_list *ptr2=NULL;
    long i=0;

    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    for ( ptr2 = pstartint ; ptr2 ; ptr2 = ptr2->pnext ){
	  printf("stackid %li var: %li\n", ptr2->stackid, ptr2->myint);
      i++;
    }
    printf("|___________________________________|\n");
}

//
struct int_list int_getNext(){
    struct int_list ret;

    memset(&ret, '\0', sizeof(ret));
	ret.idx = -1;
	ret.stackid = -1;

    if ( ptrint ){
        ret = *ptrint;
        ptrint = ptrint->pnext;
    }
    ret.pnext = NULL;
    return ret;
}

//
void int_setHeadposition(){
    ptrint = pstartint;
}


