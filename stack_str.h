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




STR_ARRY GlbStrBox;

void stackStr_push(struct stackStr_list newlist){
    struct    stackStr_list *ptr_loc;

    ptr_loc = NULL;
    ptr_loc = (struct stackStr_list*)malloc(sizeof(struct stackStr_list));

    if(ptr_loc == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    if ( pendS )
        pendS->pnext = ptr_loc;
    else
        pstartS = ptr_loc;
    pendS = ptr_loc;

    *pendS = newlist;

    pendS->pnext = NULL;
}

void stackStr_addFirst(struct stackStr_list newlist){
    struct stackStr_list *ptr_loc;

    ptr_loc = NULL;
    ptr_loc = (struct stackStr_list*)malloc(sizeof(struct stackStr_list));

    if(ptr_loc == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    *ptr_loc = newlist;

    ptr_loc->pnext = pstartS;

    pstartS = ptr_loc;
}

void stackStr_removeAll(){
    struct stackStr_list *p, *pnext;

    p = NULL;
    pnext = NULL;

    for ( p = pstartS ; p ; p = pnext ){
        pnext = p->pnext;
        free( p );
    }

    pendS = pstartS = NULL;
}

long stackStr_getID(struct stackStr_list data){
    struct stackStr_list *ptr_loc;

    ptr_loc = NULL;

    for ( ptr_loc = pstartS ; ptr_loc ; ptr_loc = ptr_loc->pnext ){
        if ( strncmp(data.array_name, ptr_loc->array_name, strlen(data.array_name)) == 0 )
            return ptr_loc->stackid;
    }

    return -1;
}

int stackStr_getPos(struct stackStr_list data){
    struct stackStr_list *ptr_loc;
    long i = 0;

    ptr_loc = NULL;

    for ( ptr_loc = pstartS ; ptr_loc ; ptr_loc = ptr_loc->pnext ){
        if ( strncmp(data.array_name, ptr_loc->array_name, strlen(data.array_name)) == 0 )
            return i;
        i++;
    }

    return -1;
}

struct stackStr_list stackStr_removeFirst(){
    struct stackStr_list ret;

    memset(&ret, '\0', sizeof(ret));
    ret.stackid = '\0';
    memset(&ret.array_name, '\0', sizeof(ret.array_name));

    if ( pstartS ){

        ret = *pstartS;

        free( pstartS );

        pstartS = ret.pnext;

        if ( !pstartS )
            pendS = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

void stackStr_removeAt(int n){
    struct stackStr_list *ptr_loc, *ppre;

    ptr_loc = NULL; ppre = NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        stackStr_removeFirst();
        return;
    }

    if ( !pstartS )
        return;

    ppre     = pstartS;
    ptr_loc  = pstartS->pnext;
    n--;

    while( ptr_loc ){
        if ( n-- == 0 ){
            ppre->pnext = ptr_loc->pnext;

            free ( ptr_loc );

            return;
        }
        ppre    = ptr_loc;
        ptr_loc = ptr_loc->pnext;
    }
    
}


// ---

void string_push(struct string_list newlist){
    struct    string_list *ptr_loc;

    ptr_loc = NULL;
    ptr_loc = (struct string_list*)malloc(sizeof(struct string_list));

    if(ptr_loc == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    if ( pendstr )
        pendstr->pnext = ptr_loc;
    else
        pstartstr = ptr_loc;
    pendstr = ptr_loc;

    *pendstr = newlist;

    pendstr->pnext = NULL;
}

//
void string_addFirst(struct string_list newlist){
    struct string_list *ptr_loc;

    ptr_loc = NULL;
    ptr_loc = (struct string_list*)malloc(sizeof(struct string_list));

    if(ptr_loc == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    *ptr_loc = newlist;

    ptr_loc->pnext = pstartstr;

    pstartstr = ptr_loc;
}


//
void string_removeAll(){
    struct string_list *p, *pnext;

    p = NULL;
    pnext = NULL;

    for ( p = pstartstr ; p ; p = pnext ){
        pnext = p->pnext;
        free( p );
    }

    pendstr = pstartstr = NULL;
}


//
struct string_list string_removeFirst(){
    struct string_list ret;

    memset(&ret, '\0', sizeof(ret));
    memset(&ret.mystring, '\0', sizeof(ret.mystring));

    if ( pstartstr ){

        ret = *pstartstr;

        free( pstartstr );

        pstartstr = ret.pnext;

        if ( !pstartstr )
            pendstr = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

//
struct string_list string_pop(){
    struct string_list ret;

    memset(&ret, '\0', sizeof(ret));
    memset(&ret.mystring, '\0', sizeof(ret.mystring));

    if ( pendstr ){
        struct string_list *ptr_loc;

        ret = *pendstr;

        for ( ptr_loc = pstartstr ; ptr_loc ; ptr_loc = ptr_loc->pnext ){
            if ( ptr_loc->pnext == pendstr ) {
                ptr_loc->pnext = NULL;
                break;
            }
        }

        free ( pendstr );

        pendstr = ptr_loc;

        if ( !pendstr )
            pstartstr = NULL;

    }
    ret.pnext = NULL;
    return ret;
}

//
struct string_list string_getElement(int n){
    struct string_list *ptr_loc;
    struct string_list ret;

    ptr_loc = NULL;
    memset(&ret, '\0', sizeof(ret));
    memset(&ret.mystring, '\0', sizeof(ret.mystring));

    ret.pnext = NULL;

    if ( n < 0 )
        return ret;

    for ( ptr_loc = pstartstr ; ptr_loc ; ptr_loc = ptr_loc->pnext ){
		if ( n-- == 0 ) {
            // printf("will ret \n");
            return *ptr_loc;
		} 
    }

    return ret;
}

//
void string_removeAt(int n){
    struct string_list *ptr_loc, *ppre;

    ptr_loc=NULL;
    ppre=NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        string_removeFirst();
        return;
    }

    if ( !pstartstr )
        return;

    ppre    = pstartstr;
    ptr_loc = pstartstr->pnext;
    n--;

    while( ptr_loc ){
        if ( n-- == 0 ){
            ppre->pnext = ptr_loc->pnext;

            free ( ptr_loc );

            return;
        }
        ppre    = ptr_loc;
        ptr_loc = ptr_loc->pnext;
    }
    
}

//
void string_setElement(int n, struct string_list newdata){
    struct string_list *ptr_loc;
    struct string_list *pnext;

    ptr_loc = NULL;  pnext = NULL;

    if ( n < 0 )
        return;

    for ( ptr_loc = pstartstr ; ptr_loc ; ptr_loc = ptr_loc->pnext ){
        if ( n-- == 0 ){
            pnext = ptr_loc->pnext;
            *ptr_loc = newdata;
            ptr_loc->pnext = pnext;
            return;
        }
    }
}

//
int string_getCount(){
    struct string_list *ptr_loc;
    long n = 0;

    ptr_loc = NULL;

    if ( pstartstr ){
		for ( ptr_loc = pstartstr ; ptr_loc ; ptr_loc = ptr_loc->pnext ) {
		    // printf("inside getCount ptr : n %d idx %d id %d str %s\n", n, ptr->idx, ptr->stackid, ptr->mystring);
            n++;
		}
    }
    return n;
}


//
int string_isEmpty(){
    return pstartstr ? 0 : 1;
}

//
int string_findData(struct string_list data){
    struct string_list *ptr_loc;
    long i = 0;

    ptr_loc = NULL;

    memset(&data.mystring, '\0', sizeof(data.mystring));
    // printf("Look For data: %d %d \n", data.idx, data.stackid);
    for ( ptr_loc = pstartstr ; ptr_loc ; ptr_loc = ptr_loc->pnext ){
		// printf("inside find ptr : %d %d %s\n", ptr->idx, ptr->stackid, ptr->mystring);
		// printf("---\n");

        if ( 
             data.stackid == ptr_loc->stackid && data.idx == ptr_loc->idx )
            return i;
        i++;
    }

    return -1;
}

int string_getIDX(struct string_list data){
    struct string_list *ptr_loc;

    ptr_loc = NULL;

    for ( ptr_loc = pstartstr ; ptr_loc ; ptr_loc = ptr_loc->pnext ){
        if ( strncmp(data.mystring, ptr_loc->mystring, strlen(data.mystring)) == 0 &&
             data.stackid == ptr_loc->stackid )
            return ptr_loc->idx;
    }

    return -1;
}

void string_printData(void){
    struct string_list *ptr_loc=NULL;
    long i=0;

    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    for ( ptr_loc = pstartstr ; ptr_loc ; ptr_loc = ptr_loc->pnext ){
      if(strlen(ptr_loc->mystring) > 0) {
		 printf("stackid %li var: %s\n", ptr_loc->stackid, ptr_loc->mystring);
      }
      i++;
    }
    printf("|___________________________________|\n");
}

//
struct string_list string_getNext(){
    struct string_list ret;

    memset(&ret, '\0', sizeof(ret));
    memset(&ret.mystring, '\0', sizeof(ret.mystring));
	ret.idx = -1;
	ret.stackid = -1;

    if ( ptrstr != NULL ){
        ret = *ptrstr;
        ptrstr = ptrstr->pnext;
    }
    ret.pnext = NULL;
    return ret;
}

//
void string_setHeadposition(){
    ptrstr = pstartstr;
}

