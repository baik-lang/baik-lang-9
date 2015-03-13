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

struct  stackgui_list *pstartGUI, *pendGUI;
struct  stackgui_list *ptrGUI;

struct  gui_list *pstartGUInt, *pendGUInt;
struct  gui_list *ptrGUInt;

GUI_ARRY GlbGuiBox;

void stackGui_push(struct stackgui_list newlist){
    struct    stackgui_list *ptr;

    ptr = NULL;
    ptr = (struct stackgui_list*)malloc(sizeof(struct stackgui_list));

    if(ptr == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    if ( pendGUI )
        pendGUI->pnext = ptr;
    else
        pstartGUI = ptr;
    pendGUI = ptr;

    *pendGUI = newlist;

    pendGUI->pnext = NULL;
}

void stackGui_addFirst(struct stackgui_list newlist){
    struct stackgui_list *ptr;

    ptr = NULL;
    ptr = (struct stackgui_list*)malloc(sizeof(struct stackgui_list));

    if(ptr == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    *ptr = newlist;

    ptr->pnext = pstartGUI;

    pstartGUI = ptr;
    
}

void stackGui_removeAll(){
    struct stackgui_list *p, *pnext;

    p = NULL;
    pnext = NULL;

    for ( p = pstartGUI ; p ; p = pnext ){
        pnext = p->pnext;
        free( p );
    }

    pendGUI = pstartGUI = NULL;
}

long stackGui_getID(struct stackgui_list data){
    struct stackgui_list *ptr;
    long ret = -1.0;

    ptr = NULL;

    for ( ptr = pstartGUI ; ptr ; ptr = ptr->pnext ){
        if ( strncmp(data.array_name, ptr->array_name, strlen(data.array_name)) == 0 ) {
            ret = ptr->stackid;
            return (long)ret;
        }
    }

    return ret;
}

int stackGui_getPos(struct stackgui_list data){
    struct stackgui_list *ptr;
    long i = 0;

    ptr = NULL;

    for ( ptr = pstartGUI ; ptr ; ptr = ptr->pnext ){
        if ( strncmp(data.array_name, ptr->array_name, strlen(data.array_name)) == 0 )
            return i;
        i++;
    }

    return -1;
}

struct stackgui_list stackGui_removeFirst(){
    struct stackgui_list ret;

    memset(&ret, '\0', sizeof(ret));
    ret.stackid = '\0';
    memset(&ret.array_name, '\0', sizeof(ret.array_name));

    if ( pstartGUI ){

        ret = *pstartGUI;

        free( pstartGUI );

        pstartGUI = ret.pnext;

        if ( !pstartGUI )
            pendGUI = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

void stackGui_removeAt(int n){
    struct stackgui_list *ptr, *ppre;

    ptr = NULL; ppre = NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        stackGui_removeFirst();
        return;
    }

    if ( !pstartGUI )
        return;

    ppre = pstartGUI;
    ptr  = pstartGUI->pnext;
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


// ---

void gui_push(struct gui_list newlist){
    struct    gui_list *ptr;

    ptr = NULL;
    ptr = (struct gui_list*)malloc(sizeof(struct gui_list));

    if(ptr == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    if ( pendGUInt )
        pendGUInt->pnext = ptr;
    else
        pstartGUInt = ptr;
    pendGUInt = ptr;

    *pendGUInt = newlist;

    pendGUInt->pnext = NULL;
}

//
void gui_addFirst(struct gui_list newlist){
    struct gui_list *ptr;

    ptr = NULL;
    ptr = (struct gui_list*)malloc(sizeof(struct gui_list));

    if(ptr == NULL) {
      printf("Kesalahan Internal: memori tidak cukup");
    }

    *ptr = newlist;

    ptr->pnext = pstartGUInt;

    pstartGUInt = ptr;
}


//
void gui_removeAll(){
    struct gui_list *p, *pnext;

    p = NULL;
    pnext = NULL;

    for ( p = pstartGUInt ; p ; p = pnext ){
        pnext = p->pnext;
        free( p );
    }

    pendGUInt = pstartGUInt = NULL;
}


//
struct gui_list gui_removeFirst(){
    struct gui_list ret;

    memset(&ret, '\0', sizeof(ret));

    if ( pstartGUInt ){

        ret = *pstartGUInt;

        free( pstartGUInt );

        pstartGUInt = ret.pnext;

        if ( !pstartGUInt )
            pendGUInt = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

//
struct gui_list gui_pop(){
    struct gui_list ret;

    memset(&ret, '\0', sizeof(ret));

    if ( pendGUInt ){
        struct gui_list *ptr;

        ret = *pendGUInt;

        for ( ptr = pstartGUInt ; ptr ; ptr = ptr->pnext ){
            if ( ptr->pnext == pendGUInt ) {
                ptr->pnext = NULL;
                break;
            }
        }

        free ( pendGUInt );

        pendGUInt = ptr;

        if ( !pendGUInt )
            pstartGUInt = NULL;

    }
    ret.pnext = NULL;
    return ret;
}

//
struct gui_list gui_getElement(int n){
    struct gui_list *ptr;
    struct gui_list ret;

    ptr = NULL;
    memset(&ret, '\0', sizeof(ret));
    ret.pnext = NULL;

    if ( n < 0 )
        return ret;

    for ( ptr = pstartGUInt ; ptr ; ptr = ptr->pnext ){
        if ( n-- == 0 )
            return *ptr;
    }

    return ret;
}

//
void gui_removeAt(int n){
    struct gui_list *ptr, *ppre;

    ptr=NULL;
	ppre=NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        gui_removeFirst();
        return;
    }

    if ( !pstartGUInt )
        return;

    ppre = pstartGUInt;
    ptr  = pstartGUInt->pnext;
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
void gui_setElement(int n, struct gui_list newdata){
    struct gui_list *ptr;
    struct gui_list *pnext;

    ptr = NULL;  pnext = NULL;

    if ( n < 0 )
        return;

    for ( ptr = pstartGUInt ; ptr ; ptr = ptr->pnext ){
        if ( n-- == 0 ){
            pnext = ptr->pnext;
            *ptr = newdata;
            ptr->pnext = pnext;
            return;
        }
    }
}

//
int gui_getCount(){
    struct gui_list *ptr;
    long n = 0;

    ptr = NULL;

    if ( pstartGUInt ){
		for ( ptr = pstartGUInt ; ptr ; ptr = ptr->pnext ) {
		    // printf("inside getCount ptr : n %d idx %d id %d str %s\n", n, ptr->idx, ptr->stackid, ptr->mystring);
            n++;
		}
    }
    return n;
}


//
int gui_isEmpty(){
    return pstartGUInt ? 0 : 1;
}

//
int gui_findData(struct gui_list data){
    struct gui_list *ptr;
    long i = 0;

    ptr = NULL;

    //printf("look for data   : %d idx %d %d : %d\n", i, data.idx, data.stackid, data.mywidget);
    for ( ptr = pstartGUInt ; ptr ; ptr = ptr->pnext ){
		//printf("inside find ptr : %d idx %d %d : %d\n", i, ptr->idx, ptr->stackid, ptr->mywidget);
		//printf("look for data   : %d idx %d %d : %d\n", i, data.idx, data.stackid, data.mywidget);
		// printf("---\n");

        if ( 
             data.stackid == ptr->stackid && data.idx == ptr->idx )
            return i;
        i++;
    }

	// clear memory
	memset(&data, '\0', sizeof(data));

    return -1;
}

int gui_getIDX(struct gui_list data){
    struct gui_list *ptr;

    ptr = NULL;

    for ( ptr = pstartGUInt ; ptr ; ptr = ptr->pnext ){
        if ( data.mywidget == ptr->mywidget &&
             data.stackid == ptr->stackid )
            return ptr->idx;
    }

    return -1;
}

//
void gui_printData(void){
    struct gui_list *ptr=NULL;
    long i=0;

    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    for ( ptr = pstartGUInt ; ptr ; ptr = ptr->pnext ){
	  printf("stackid %li var: GUI widget \n", ptr->stackid);
      i++;
    }
    printf("|___________________________________|\n");
}

//
struct gui_list gui_getNext(){
    struct gui_list ret;

    memset(&ret, '\0', sizeof(ret));
	ret.idx = -1;
	ret.stackid = -1;

    if ( ptrGUInt ){
        ret = *ptrGUInt;
        ptrGUInt = ptrGUInt->pnext;
    }
    ret.pnext = NULL;
    return ret;
}

//
void gui_setHeadposition(){
    ptrGUInt = pstartGUInt;
}


