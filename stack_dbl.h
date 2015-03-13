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


DBL_ARRY GlbDblBox;


void stackDbl_push(struct stackDbl_list newlist) {
    struct    stackDbl_list *ptr2;

    ptr2 = NULL;
    ptr2 = (struct stackDbl_list*)malloc(sizeof(struct stackDbl_list));

    if(ptr2 == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    if ( pendD )
        pendD->pnext = ptr2;
    else
        pstartD = ptr2;
    pendD = ptr2;

    *pendD = newlist;

    pendD->pnext = NULL;
}

void stackDbl_addFirst(struct stackDbl_list newlist){
    struct stackDbl_list *ptr2;

    ptr2 = NULL;
    ptr2 = (struct stackDbl_list*)malloc(sizeof(struct stackDbl_list));

    if(ptr2 == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    *ptr2 = newlist;

    ptr2->pnext = pstartD;

    pstartD = ptr2;
    
}

void stackDbl_removeAll(){
    struct stackDbl_list *p, *pnext;

    p = NULL;
    pnext = NULL;

    for ( p = pstartD ; p ; p = pnext ){
        pnext = p->pnext;
        free( p );
    }

    pendD = pstartD = NULL;
}


long stackDbl_getID(struct stackDbl_list data){
    struct stackDbl_list *ptr2;

    ptr2 = NULL;

    for ( ptr2 = pstartD ; ptr2 ; ptr2 = ptr2->pnext ){
        if ( strncmp(data.array_name, ptr2->array_name, strlen(data.array_name)) == 0 )
            return ptr2->stackid;
    }

    return -1;
}

int stackDbl_getPos(struct stackDbl_list data){
    struct stackDbl_list *ptr2;
    long i = 0;

    ptr2 = NULL;

    for ( ptr2 = pstartD ; ptr2 ; ptr2 = ptr2->pnext ){
        if ( strncmp(data.array_name, ptr2->array_name, strlen(data.array_name)) == 0 )
            return i;
        i++;
    }

    return -1;
}

struct stackDbl_list stackDbl_removeFirst(){
    struct stackDbl_list ret;

    memset(&ret, '\0', sizeof(ret));
    ret.stackid = '\0';
    memset(&ret.array_name, '\0', sizeof(ret.array_name));

    if ( pstartD ){

        ret = *pstartD;

        free( pstartD );

        pstartD = ret.pnext;

        if ( !pstartD )
            pendD = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

void stackDbl_removeAt(int n){
    struct stackDbl_list *ptr2, *ppre;

    ptr2 = NULL; ppre = NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        stackDbl_removeFirst();
        return;
    }

    if ( !pstartD )
        return;

    ppre = pstartD;
    ptr2  = pstartD->pnext;
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

void dbl_push(struct dbl_list newlist){
    struct    dbl_list *ptr2;

    ptr2 = NULL;
    ptr2 = (struct dbl_list*)malloc(sizeof(struct dbl_list));

    if(ptr2 == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    if ( penddbl )
        penddbl->pnext = ptr2;
    else
        pstartdbl = ptr2;
    penddbl = ptr2;

    *penddbl = newlist;

    penddbl->pnext = NULL;
}

//
void dbl_addFirst(struct dbl_list newlist){
    struct dbl_list *ptr2;

    ptr2 = NULL;
    ptr2 = (struct dbl_list*)malloc(sizeof(struct dbl_list));

    if(ptr2 == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    *ptr2 = newlist;

    ptr2->pnext = pstartdbl;

    pstartdbl = ptr2;
}


//
void dbl_removeAll(){
    struct dbl_list *p, *pnext;

    p = NULL;
    pnext = NULL;

    for ( p = pstartdbl ; p ; p = pnext ){
        pnext = p->pnext;
        free( p );
    }

    penddbl = pstartdbl = NULL;
}


//
struct dbl_list dbl_removeFirst(){
    struct dbl_list ret;

    memset(&ret, '\0', sizeof(ret));

    if ( pstartdbl ){

        ret = *pstartdbl;

        free( pstartdbl );

        pstartdbl = ret.pnext;

        if ( !pstartdbl )
            penddbl = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

//
struct dbl_list dbl_pop(){
    struct dbl_list ret;

    memset(&ret, '\0', sizeof(ret));

    if ( penddbl ){
        struct dbl_list *ptr2;

        ret = *penddbl;

        for ( ptr2 = pstartdbl ; ptr2 ; ptr2 = ptr2->pnext ){
            if ( ptr2->pnext == penddbl ) {
                ptr2->pnext = NULL;
                break;
            }
        }

        free ( penddbl );

        penddbl = ptr2;

        if ( !penddbl )
            pstartdbl = NULL;

    }
    ret.pnext = NULL;
    return ret;
}

//
struct dbl_list dbl_getElement(int n){
    struct dbl_list *ptr2;
    struct dbl_list ret;

    ptr2 = NULL;
    memset(&ret, '\0', sizeof(ret));
    ret.pnext = NULL;

    if ( n < 0 )
        return ret;

    for ( ptr2 = pstartdbl ; ptr2 ; ptr2 = ptr2->pnext ){
        if ( n-- == 0 )
            return *ptr2;
    }

    return ret;
}

//
void dbl_removeAt(int n){
    struct dbl_list *ptr2, *ppre;

    ptr2=NULL;
    ppre=NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        dbl_removeFirst();
        return;
    }

    if ( !pstartdbl )
        return;

    ppre = pstartdbl;
    ptr2 = pstartdbl->pnext;
    n--;

    while( ptr2 ){
        if ( n-- == 0 ){
            ppre->pnext = ptr2->pnext;

            free ( ptr2 );

            return;
        }
        ppre = ptr2;
        ptr2 = ptr2->pnext;
    }
    
}

//
void dbl_setElement(int n, struct dbl_list newdata){
    struct dbl_list *ptr2;
    struct dbl_list *pnext;

    ptr2 = NULL;  pnext = NULL;

    if ( n < 0 )
        return;

    for ( ptr2 = pstartdbl ; ptr2 ; ptr2 = ptr2->pnext ){
        if ( n-- == 0 ){
            pnext = ptr2->pnext;
            *ptr2 = newdata;
            ptr2->pnext = pnext;
            return;
        }
    }
}

//
int dbl_getCount(){
    struct dbl_list *ptr;
    long n = 0;

    ptr = NULL;

    if ( pstartdbl ){
		for ( ptr = pstartdbl ; ptr ; ptr = ptr->pnext ) {
		    // printf("inside getCount ptr : n %d idx %d id %d str %s\n", n, ptr->idx, ptr->stackid, ptr->mystring);
            n++;
		}
    }
    return n;
}


//
int dbl_isEmpty(){
    return pstartdbl ? 0 : 1;
}

//
int dbl_findData(struct dbl_list data){
    struct dbl_list *ptr2;
    long i = 0;

    ptr2 = NULL;

    // printf("look for data: %d %d %f\n", data.idx, data.stackid, data.mydbl);
    for ( ptr2 = pstartdbl ; ptr2 ; ptr2 = ptr2->pnext ){
		// printf("inside find ptr : %d %d %f\n", ptr->idx, ptr->stackid, ptr->mydbl);
		// printf("---\n");

        if ( 
             data.stackid == ptr2->stackid && data.idx == ptr2->idx )
            return i;
        i++;
    }

    return -1;
}

int dbl_getIDX(struct dbl_list data){
    struct dbl_list *ptr2;

    ptr2 = NULL;

    for ( ptr2 = pstartdbl ; ptr2 ; ptr2 = ptr2->pnext ){
        if ( data.mydbl == ptr2->mydbl &&
             data.stackid == ptr2->stackid )
            return ptr2->idx;
    }

    return -1;
}

//
void dbl_printData(void){
    struct dbl_list *ptr2=NULL;
    long i=0;

    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    for ( ptr2 = pstartdbl ; ptr2 ; ptr2 = ptr2->pnext ){
	  printf("stackid %li var: %f\n", ptr2->stackid, ptr2->mydbl);
      i++;
    }
    printf("|___________________________________|\n");
}

//
struct dbl_list dbl_getNext(){
    struct dbl_list ret;

    memset(&ret, '\0', sizeof(ret));
	ret.idx = -1;
	ret.stackid = -1;

    if ( ptrdbl ){
        ret = *ptrdbl;
        ptrdbl = ptrdbl->pnext;
    }
    ret.pnext = NULL;
    return ret;
}

//
void dbl_setHeadposition(){
    ptrdbl = pstartdbl;
}

