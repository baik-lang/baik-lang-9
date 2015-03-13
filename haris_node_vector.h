
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


void class_params_init() {
  int max = 128;
  int i=0;

  // printf("initialize ...\n");
  memset(&class_params, '\0', sizeof(class_params));

  // printf("create string array\n");
  for(i=0; i<max; i++) {
    strcpy(class_params.name[i], "");
  }

}

// ////////////////////////////////////////////////////
void node_addLast(struct node_list newlist){
    struct    node_list *ptr;

    ptr = NULL;
    ptr = (struct node_list*)malloc(sizeof(struct node_list));

    if(ptr == NULL) {
      printf("memori tidak cukup! \n");
    }

    if ( pend )
        pend->pnext = ptr;
    else
        pstart = ptr;
    pend = ptr;

    *pend = newlist;

    pend->pnext = NULL;
}

//
void node_addFirst(struct node_list newlist){
    struct node_list *ptr;

    ptr = NULL;
    ptr = (struct node_list*)malloc(sizeof(struct node_list));

    if(ptr == NULL) {
      printf("memori tidak cukup! \n");
    }

    *ptr = newlist;

    ptr->pnext = pstart;

    pstart = ptr;
}


//
void node_removeAll(){
    struct node_list *p, *pnext;

    for ( p = pstart ; p ; p = pnext ){
        pnext = p->pnext;
        free( p );
    }

    pend = pstart = NULL;
}


//
struct node_list node_removeFirst(){
    struct node_list ret;

    memset(&ret, '\0', sizeof(ret));
    ret.ch = '\0';

    if ( pstart ){

        ret = *pstart;

        free( pstart );

        pstart = ret.pnext;

        if ( !pstart )
            pend = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

//
struct node_list node_removeLast(){
    struct node_list ret;

    ret.ch = '\0';

    if ( pend ){
        struct node_list *ptr;

        ret = *pend;

        for ( ptr = pstart ; ptr ; ptr = ptr->pnext ){
            if ( ptr->pnext == pend )
                ptr->pnext = NULL;
        }

        free ( pend );

        pend = ptr;

        if ( !pend )
            pstart = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

//
struct node_list node_getElement(int n){
    struct node_list *ptr;
    struct node_list ret;

    ptr = NULL;
    memset(&ret, '\0', sizeof(ret));
    ret.ch    = '\0';
    ret.pnext = NULL;

    if ( n < 0 )
        return ret;

    for ( ptr = pstart ; ptr ; ptr = ptr->pnext ){
        if ( n-- == 0 )
            return *ptr;
    }

    return ret;
}

//
void node_setElement(int n, struct node_list newdata){
    struct node_list *ptr;
    struct node_list *pnext;

    ptr = NULL;
    pnext = NULL;

    if ( n < 0 )
        return;

    for ( ptr = pstart ; ptr ; ptr = ptr->pnext ){
        if ( n-- == 0 ){
            pnext = ptr->pnext;
            *ptr = newdata;
            ptr->pnext = pnext;
            return;
        }
    }
}

//
void node_removeAt(int n){
    struct node_list *ptr, *ppre;

    ptr =  NULL;
    ppre = NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        node_removeFirst();
        return;
    }

    if ( !pstart )
        return;

    ppre = pstart;
    ptr  = pstart->pnext;
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
int node_getCount(){
    struct node_list *ptr;
    int n = 0;

    ptr = NULL;

    if ( pstart ){
        for ( ptr = pstart ; ptr ; ptr = ptr->pnext )
            n++;
    }
    return n;
}


//
int node_isEmpty(){
    return pstart ? 0 : 1;
}

//
void node_insertAfter(int n, struct node_list newdata){
    struct node_list *ptr, *pnew;

    ptr = NULL;
    pnew = NULL;

    if ( n < 0 )
        return;

    for ( ptr = pstart ; ptr ; ptr = ptr->pnext ){
        if ( n-- == 0 ){
            pnew = (struct node_list*)malloc(sizeof(struct node_list));

            *pnew = newdata;

            pnew->pnext = ptr->pnext;
            ptr->pnext = pnew;

            return;
        }
    }
}

//
void node_insertBefore(int n, struct node_list newdata){
    struct node_list *ptr, *pnew;

    ptr = NULL;
    pnew = NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        node_addFirst( newdata );
        return;
    }

    for ( ptr = pstart ; ptr ; ptr = ptr->pnext ){
        if ( --n == 0 ){
            pnew = (struct node_list*)malloc(sizeof(struct node_list));

            *pnew = newdata;

            pnew->pnext = ptr->pnext;
            ptr->pnext = pnew;

            return;
        }
    }
}


//
int node_findData(struct node_list data){
    struct node_list *ptr;
    int i = 0;

    ptr = NULL;
    /*
    printf("search LIST class name : %s\n", data.class_name);
    printf("search LIST param name : %s\n", data.param_name);
    */

    for ( ptr = pstart ; ptr ; ptr = ptr->pnext ){

        if ( strncmp(data.class_name, ptr->class_name, strlen(data.class_name)) == 0 ) {
           /*
           printf("search LIST param name : %s len %d\n", data.param_name, strlen(data.param_name));
           printf("inside LIST param name : %s len %d\n", ptr->param_name, strlen(ptr->param_name));
           */

           if(data.member_type == 1) { // as param
             if ( ! strcmp(data.param_name, ptr->param_name) && strlen(ptr->param_name) > 0) {
               return i;
             }
           } else
           if(data.member_type == 2) { // as function

             if ( ! strcmp(data.function_name, ptr->function_name) ) {
               return i;
             }
           }
        }
        i++;
    }

    return -1;
}


//
void class_findParams(struct node_list data){
    struct node_list *ptr;
    int i = 0;
    int num = 0;

    ptr = NULL;

    /*
    printf("search LIST class name : %s\n", data.class_name);
    printf("search LIST param name : %s\n", data.param_name);
    */

    for ( ptr = pstart ; ptr ; ptr = ptr->pnext ){

        if ( strncmp(data.class_name, ptr->class_name, strlen(data.class_name)) == 0 ) {
           
           if(strlen(ptr->param_name) > 0) {
             // printf("%d LIST param name : %s len %d\n", num, ptr->param_name, strlen(ptr->param_name));
             class_params.pos[num] = i;
             strcpy(class_params.name[num] , ptr->param_name);
             num++;
           }

        }
        i++;
    }

    class_params.total = num;
    // printf("tot params %d\n", num);
}

//
struct node_list node_getNext(){
    struct node_list ret;

    memset(&ret, '\0', sizeof(ret));
    ret.ch = '\0';

    if ( ptr ){
        ret = *ptr;
        ptr = ptr->pnext;
    }
    ret.pnext = NULL;
    return ret;
}

//
void node_setHeadposition(){
    ptr = pstart;
}

