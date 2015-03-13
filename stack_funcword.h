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


struct  funcword_list *pstartword, *pendword;
struct  funcword_list *ptrword;

void funcword_push(struct funcword_list newlist){
    struct    funcword_list *ptr;

    ptr = NULL;
    ptr = (struct funcword_list*)malloc(sizeof(struct funcword_list));

    if(ptr == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    if ( pendword )
        pendword->pnext = ptr;
    else
        pstartword = ptr;
    pendword = ptr;

    *pendword = newlist;

    pendword->pnext = NULL;
}

//
void funcword_addFirst(struct funcword_list newlist){
    struct funcword_list *ptr;

    ptr = NULL;
    ptr = (struct funcword_list*)malloc(sizeof(struct funcword_list));

    if(ptr == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    *ptr = newlist;

    ptr->pnext = pstartword;

    pstartword = ptr;
}


//
void funcword_removeAll(){
    struct funcword_list *p, *pnext;

    p = NULL;
    pnext = NULL;

    for ( p = pstartword ; p ; p = pnext ){
        pnext = p->pnext;
        free( p );
    }

    pendword = pstartword = NULL;
}


//
struct funcword_list funcword_removeFirst(){
    struct funcword_list ret;

    memset(&ret, '\0', sizeof(ret));
    memset(&ret.funcname, '\0', sizeof(ret.funcname));

    if ( pstartword ){

        ret = *pstartword;

        free( pstartword );

        pstartword = ret.pnext;

        if ( !pstartword )
            pendword = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

//
struct funcword_list funcword_pop(){
    struct funcword_list ret;

    memset(&ret, '\0', sizeof(ret));
    memset(&ret.funcname, '\0', sizeof(ret.funcname));

    if ( pendword ){
        struct funcword_list *ptr;

        ret = *pendword;

        for ( ptr = pstartword ; ptr ; ptr = ptr->pnext ){
            if ( ptr->pnext == pendword ) {
                ptr->pnext = NULL;
                break;
            }
        }

        free ( pendword );

        pendword = ptr;

        if ( !pendword )
            pstartword = NULL;

    }
    ret.pnext = NULL;
    return ret;
}

//
struct funcword_list funcword_getElement(int n){
    struct funcword_list *ptr;
    struct funcword_list ret;

    ptr = NULL;
    memset(&ret, '\0', sizeof(ret));
    memset(&ret.funcname, '\0', sizeof(ret.funcname));

    ret.pnext = NULL;

    if ( n < 0 )
        return ret;

    for ( ptr = pstartword ; ptr ; ptr = ptr->pnext ){
		if ( n-- == 0 ) {
            // printf("will ret \n");
            return *ptr;
		} 
    }

    return ret;
}

//
void funcword_removeAt(int n){
    struct funcword_list *ptr, *ppre;

    ptr=NULL;
	ppre=NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        funcword_removeFirst();
        return;
    }

    if ( !pstartword )
        return;

    ppre = pstartword;
    ptr  = pstartword->pnext;
    n--;

    while( ptr ){
        if ( n-- == 0 ){
            ppre->pnext = ptr->pnext;

            free ( ptr );

            return;
        }
        ppre = ptr;
        ptr  = ptr->pnext;
    }
    
}

//
void funcword_setElement(int n, struct funcword_list newdata){
    struct funcword_list *ptr;
    struct funcword_list *pnext;

    ptr = NULL;  pnext = NULL;

    if ( n < 0 )
        return;

    for ( ptr = pstartword ; ptr ; ptr = ptr->pnext ){
        if ( n-- == 0 ){
            pnext = ptr->pnext;
            *ptr = newdata;
            ptr->pnext = pnext;
            return;
        }
    }
}

//
int funcword_getCount(){
    struct funcword_list *ptr;
    long n = 0;

    ptr = NULL;

    if ( pstartword ){
		for ( ptr = pstartword ; ptr ; ptr = ptr->pnext ) {
		    // printf("inside getCount ptr : n %d idx %d id %d str %s\n", n, ptr->idx, ptr->enumid, ptr->keyword);
            n++;
		}
    }
    return n;
}


//
int funcword_isEmpty(){
    return pstartword ? 0 : 1;
}

//
int funcword_findPos(struct funcword_list data){
    struct funcword_list *ptr;
    int i = 0;

    ptr = NULL;

	memset(&data.funcname, '\0', sizeof(data.funcname));
	// printf("Look For data: %s \n", data.funcname);
    for ( ptr = pstartword ; ptr ; ptr = ptr->pnext ){
        if ( strncmp(data.funcname, ptr->funcname, strlen(data.funcname)) == 0 &&
			strlen(data.funcname) == strlen(ptr->funcname)		
			)
            return i;
        i++;
    }

    return -1;
}

int funcword_getEnum(struct funcword_list data){
    struct funcword_list *ptr;

    ptr = NULL;

    for ( ptr = pstartword ; ptr ; ptr = ptr->pnext ){
		// printf("enumid %d var: %s len %d \n", ptr->enumid, ptr->funcname, strlen(ptr->funcname));
        if ( strncmp(data.funcname, ptr->funcname, strlen(data.funcname)) == 0 &&
			strlen(data.funcname) == strlen(ptr->funcname)
			)
            return ptr->enumid;
    }

    return -1;
}

void funcword_printData(void){
    struct funcword_list *ptr=NULL;
    int i=0;

    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    for ( ptr = pstartword ; ptr ; ptr = ptr->pnext ){
      if(strlen(ptr->funcname) > 0) {
		  printf("enum %d : %s : %s\n", ptr->enumid, ptr->funcname, ptr->alias);
      }
      i++;
    }
    printf("|___________________________________|\n");
}

//
struct funcword_list funcword_getNext(){
    struct funcword_list ret;

    memset(&ret, '\0', sizeof(ret));
    memset(&ret.funcname, '\0', sizeof(ret.funcname));
	ret.enumid = -1;

    if ( ptrword ){
        ret = *ptrword;
        ptrword = ptrword->pnext;
    }
    ret.pnext = NULL;
    return ret;
}

//
void funcword_setHeadposition(){
    ptrword = pstartword;
}

