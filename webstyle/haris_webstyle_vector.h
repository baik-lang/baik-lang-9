// ////////////////////////////////////////////////////
// List Manipulation in C
// Copyright(c) Haris Hasanudin 2005 - 2010
//
// Untuk Bahasa Komputer Versi Bahasa Indonesia
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
// ////////////////////////////////////////////////////

//    void style_addFirst(struct style_list newlist);
//    void style_addLast(struct style_list newlistt);
//    void style_removeAll();
//    struct style_list style_removeLast(); 
//    struct style_list style_removeFirst();
//    struct style_list style_getElement(int n);
//    void style_setElement(int n, struct style_list newdatat);
//    void style_removeAt(int n); 
//    int style_getCount();
//    int style_isEmpty();
//    void style_insertAfter(int n, struct style_list newdata);
//    void style_insertBefore(int n, struct style_list newdata);
//    int style_findData(struct style_list data);
//    struct style_list style_getNext(); 
//    void style_setHeadposition();¡£

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct style_list{
    long   id;
    char   ch;
    char   style_name[64];        // web node name
    char   style_url[514];        // web node address

    char   left_menu_name[64];   // left menu name of web page
    char   left_menu_descr[64];  // left menu description of web page
    char   left_menu_page[64];   // left menu html file of web page

    struct style_list *pnext;
};


void   style_addFirst(struct style_list newlist);
void   style_addLast(struct style_list newlist);
void   style_removeAll();
struct style_list style_removeLast();
struct style_list style_removeFirst();
struct style_list style_getElement(int n);
void   style_setElement(int n, struct style_list newdata);
void   style_removeAt(int n);
int    style_getCount();
int    style_isEmpty();
void   style_insertAfter(int n, struct style_list newdata);
void   style_insertBefore(int n, struct style_list newdata);

int    style_findMenu(struct style_list data);
int    style_findStyle(struct style_list data);

struct style_list style_getNext();
void   style_setHeadposition();


//
struct  style_list *pstartweb, *pendweb;
struct  style_list *ptrweb;




//
void style_addLast(struct style_list newlist){
    struct    style_list *ptrweb=NULL;

    ptrweb = (struct style_list*)malloc(sizeof(struct style_list));

    if ( pendweb )
        pendweb->pnext = ptrweb;
    else
        pstartweb = ptrweb;
    pendweb = ptrweb;

    *pendweb = newlist;

    pendweb->pnext = NULL;
}

//
void style_addFirst(struct style_list newlist){
    struct style_list *ptrweb=NULL;

    ptrweb = (struct style_list*)malloc(sizeof(struct style_list));

    *ptrweb = newlist;

    ptrweb->pnext = pstartweb;

    pstartweb = ptrweb;
}


//
void style_removeAll(){
    struct style_list *p=NULL, *pnext=NULL;

    for ( p = pstartweb ; p ; p = pnext ){
        pnext = p->pnext;
		if(p != NULL) {
          free( p );
		}
    }

    pendweb = pstartweb = NULL;
}


//
struct style_list style_removeFirst(){
    struct style_list ret;

    ret.ch = '\0';

    if ( pstartweb ){

        ret = *pstartweb;

        free( pstartweb );

        pstartweb = ret.pnext;

        if ( !pstartweb )
            pendweb = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

//
struct style_list style_removeLast(){
    struct style_list ret;

    ret.ch = '\0';

    if ( pendweb ){
        struct style_list *ptrweb;

        ret = *pendweb;

        for ( ptrweb = pstartweb ; ptrweb ; ptrweb = ptrweb->pnext ){
            if ( ptrweb->pnext == pendweb )
                ptrweb->pnext = NULL;
        }

        free ( pendweb );

        pendweb = ptrweb;

        if ( !pendweb )
            pstartweb = NULL;
    }
    ret.pnext = NULL;
    return ret;
}

//
struct style_list style_getElement(int n){
    struct style_list *ptrweb=NULL;
    struct style_list ret;

    ret.ch    = '\0';
    ret.pnext = NULL;

    if ( n < 0 )
        return ret;

    for ( ptrweb = pstartweb ; ptrweb ; ptrweb = ptrweb->pnext ){
        if ( n-- == 0 )
            return *ptrweb;
    }

    return ret;
}

//
void style_setElement(int n, struct style_list newdata){
    struct style_list *ptrweb=NULL;
    struct style_list *pnext=NULL;

    if ( n < 0 )
        return;

    for ( ptrweb = pstartweb ; ptrweb ; ptrweb = ptrweb->pnext ){
        if ( n-- == 0 ){
            pnext = ptrweb->pnext;
            *ptrweb = newdata;
            ptrweb->pnext = pnext;
            return;
        }
    }
}

//
void style_removeAt(int n){
    struct style_list *ptrweb=NULL, *ppre=NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        style_removeFirst();
        return;
    }

    if ( !pstartweb )
        return;

    ppre = pstartweb;
    ptrweb  = pstartweb->pnext;
    n--;

    while( ptrweb ){
        if ( n-- == 0 ){
            ppre->pnext = ptrweb->pnext;

            free ( ptrweb );

            return;
        }
        ppre = ptrweb;
        ptrweb  = ptrweb->pnext;
    }
    
}


//
int style_getCount(){
    struct style_list *ptrweb=NULL;
    int n = 0;

    if ( pstartweb ){
        for ( ptrweb = pstartweb ; ptrweb ; ptrweb = ptrweb->pnext )
            n++;
    }
    return n;
}


//
int style_isEmpty(){
    return pstartweb ? 0 : 1;
}

//
void style_insertAfter(int n, struct style_list newdata){
    struct style_list *ptrweb=NULL, *pnew=NULL;

    if ( n < 0 )
        return;

    for ( ptrweb = pstartweb ; ptrweb ; ptrweb = ptrweb->pnext ){
        if ( n-- == 0 ){
            pnew = (struct style_list*)malloc(sizeof(struct style_list));

            *pnew = newdata;

            pnew->pnext = ptrweb->pnext;
            ptrweb->pnext = pnew;

            return;
        }
    }
}

//
void style_insertBefore(int n, struct style_list newdata){
    struct style_list *ptrweb=NULL, *pnew=NULL;

    if ( n < 0 )
        return;

    if ( n == 0 ){
        style_addFirst( newdata );
        return;
    }

    for ( ptrweb = pstartweb ; ptrweb ; ptrweb = ptrweb->pnext ){
        if ( --n == 0 ){
            pnew = (struct style_list*)malloc(sizeof(struct style_list));

            *pnew = newdata;

            pnew->pnext = ptrweb->pnext;
            ptrweb->pnext = pnew;

            return;
        }
    }
}


//
int style_findMenu(struct style_list data){
    struct style_list *ptrweb;
    int i = 0;

    for ( ptrweb = pstartweb ; ptrweb ; ptrweb = ptrweb->pnext ){
        if ( strncmp(data.left_menu_name, ptrweb->left_menu_name, strlen(data.left_menu_name)) == 0 ) {
           return i;
        }
        i++;
    }

    return -1;
}


//
int style_findStyle(struct style_list data){
    struct style_list *ptrweb;
    int i = 0;

    for ( ptrweb = pstartweb ; ptrweb ; ptrweb = ptrweb->pnext ){
        if ( strncmp(data.style_name, ptrweb->style_name, strlen(data.style_name)) == 0 ) {
           return i;
        }
        i++;
    }

    return -1;
}

//
struct style_list style_getNext(){
    struct style_list ret;

    ret.ch = '\0';

    if ( ptrweb ){
        ret = *ptrweb;
        ptrweb = ptrweb->pnext;
    }
    ret.pnext = NULL;
    return ret;
}

//
void style_setHeadposition(){
    ptrweb = pstartweb;
}


void createWebStyle(char *filepath, char *clr) {
  char filename[514];
  char color[16];
  char warna[16];
  FILE *fp=NULL;
  struct stat statb;
  int isThere = 0;

  memset(&filename,'\0',sizeof(filename));
  memset(&color,'\0',sizeof(color));
  memset(&warna,'\0',sizeof(warna));

  sprintf(filename,"%s/baikstyle.css", filepath);
  sprintf(warna,"%s", clr);

  if(!strcmp(warna, "biru") || !strcmp(warna, "BIRU"))
     strcpy(color, "blue");
  if(!strcmp(warna, "biru muda") || !strcmp(warna, "BIRU MUDA"))
     strcpy(color, "lightblue");
  if(!strcmp(warna, "hijau") || !strcmp(warna, "HIJAU"))
     strcpy(color, "green");
  if(!strcmp(warna, "hijau muda") || !strcmp(warna, "HIJAU MUDA"))
     strcpy(color, "lightgreen");
  if(!strcmp(warna, "merah") || !strcmp(warna, "MERAH"))
     strcpy(color, "red");
  if(!strcmp(warna, "merah muda") || !strcmp(warna, "MERAH MUDA"))
     strcpy(color, "pink");
  if(!strcmp(warna, "kuning") || !strcmp(warna, "KUNING"))
     strcpy(color, "yellow");
  if(!strcmp(warna, "jingga") || !strcmp(warna, "JINGGA"))
     strcpy(color, "orange");
  if(!strcmp(warna, "kuning emas") || !strcmp(warna, "KUNING EMAS"))
     strcpy(color, "gold");
  if(!strcmp(warna, "merah jambu") || !strcmp(warna, "MERAH JAMBU"))
     strcpy(color, "pink");
  if(!strcmp(warna, "ungu") || !strcmp(warna, "UNGU"))
     strcpy(color, "purple");
  if(!strcmp(warna, "kelabu") || !strcmp(warna, "KELABU"))
     strcpy(color, "gray");
  if(!strcmp(warna, "") )
     strcpy(color, "lightblue");


  if (stat(filename, &statb) == -1) {
    isThere = 0;
  } else {
    isThere = 1;
  }

  if(isThere == 1) {
    // file already exist , so skip
    // printf("skip style \n");
    return;
  } else {

    fp = fopen(filename, "w");
    if(fp == '\0') {
      printf("Salah: Tidak bisa tulis ke Baik Web Style File\n");
    }

    fprintf(fp, ".menu a, \n");
    fprintf(fp, ".title h1, \n");
    fprintf(fp, ".con div {  \n");
    fprintf(fp, "         color:blue   \n");
    fprintf(fp, "          }  \n");
    fprintf(fp, "body,  \n");
    fprintf(fp, ".con h2 {  \n");
    fprintf(fp, " background-color:%s;  \n", color);
    fprintf(fp, "          }  \n");
    fprintf(fp, ".title h1       {   \n");
    fprintf(fp, "        border-bottom-color:%s;   \n", color);
    fprintf(fp, "        }   \n");
    fprintf(fp, ".sub    {   \n");
    fprintf(fp, "        border-left-color:#74ced1;   \n");
    fprintf(fp, "        }   \n");

    fprintf(fp, ".menu div.jp,   \n");
    fprintf(fp, ".title div,   \n");
    fprintf(fp, ".title p,   \n");
    fprintf(fp, ".con p  { \n");
    fprintf(fp, "        color:#888888   \n");
    fprintf(fp, "        }   \n");
    fprintf(fp, ".sub    {   \n");
    fprintf(fp, "        color:#555555   \n");
    fprintf(fp, "        }   \n");
    fprintf(fp, ".menu a:hover,   \n");
    fprintf(fp, ".con h2 {   \n");
    fprintf(fp, "        color:brown   \n");
    fprintf(fp, "        }  \n");

    fprintf(fp, ".main,   \n");
    fprintf(fp, ".menu div.jp,   \n");
    fprintf(fp, ".menu a {   \n");
    fprintf(fp, "        background-color:white;   \n");
    fprintf(fp, "        }   \n");
    fprintf(fp, ".menu a:hover  {  \n");
    fprintf(fp, "        background-color:#666666;   \n");
    fprintf(fp, "        }   \n");
    fprintf(fp, ".menu   {   \n");
    fprintf(fp, "        position:absolute;   \n");
    fprintf(fp, "        left:20px;   \n");
    fprintf(fp, "        top:20px   \n");
    fprintf(fp, "        }   \n");
    fprintf(fp, ".main   {   \n");
    fprintf(fp, "        position:absolute;   \n");
    fprintf(fp, "        left:202px;   \n");
    fprintf(fp, "        top:20px;   \n");
    fprintf(fp, "        width:630px;   \n");
    fprintf(fp, "        padding:20px   \n");
    fprintf(fp, "        }  \n \n");

    fprintf(fp, "/* MENU */  \n");
    fprintf(fp, ".menu div       {   \n");
    fprintf(fp, "        }   \n");
    fprintf(fp, ".menu div.jp    {   \n");
    fprintf(fp, "        width:152px;   \n");
    fprintf(fp, "        padding:1px 0px 2px 8px;   \n");
    fprintf(fp, "        font-size:9px;   \n");
    fprintf(fp, "        margin-top:1px;   \n");
    fprintf(fp, "        margin-bottom:10px;   \n");
    fprintf(fp, "        }   \n");

    fprintf(fp, ".menu a {   \n");
    fprintf(fp, "        display:block;   \n");
    fprintf(fp, "        width:152px;   \n");
    fprintf(fp, "        padding:3px 0px 0px 8px;   \n");
    fprintf(fp, "        text-decoration:none;   \n");
    fprintf(fp, "        font-family:Arial, Helvetica, sans-serif;   \n");
    fprintf(fp, "        font-size:18px;   \n");
    fprintf(fp, "        font-weight:bold;   \n");
    fprintf(fp, "        }   \n");

    fprintf(fp, ".sub    {   \n");
    fprintf(fp, "        width:152px;   \n");
    fprintf(fp, "        margin-top:30px;   \n");
    fprintf(fp, "        border-left:solid 8px;   \n");
    fprintf(fp, "        padding-left:6px;   \n");
    fprintf(fp, "        line-height:12px;   \n");
    fprintf(fp, "        font-size:9px;   \n");
    fprintf(fp, "        font-weight:bold;   \n");
    fprintf(fp, "        }  \n \n");

    fprintf(fp, "/* TITLE */   \n");
    fprintf(fp, ".title h1       {   \n");
    fprintf(fp, "        margin-top:0px;   \n");
    fprintf(fp, "        margin-bottom:8px;   \n");
    fprintf(fp, "        padding-bottom:3px;   \n");
    fprintf(fp, "        border-bottom:solid 2px;   \n");
    fprintf(fp, "        font-family:Arial, Helvetica, sans-serif;   \n");
    fprintf(fp, "        font-size:28px;   \n");
    fprintf(fp, "        }  \n \n");

    fprintf(fp, ".title div      {   \n");
    fprintf(fp, "        float:left;   \n");
    fprintf(fp, "        font-size:16px;   \n");
    fprintf(fp, "        font-weight:bold;   \n");
    fprintf(fp, "        }  \n \n");

    fprintf(fp, ".title p        {   \n");
    fprintf(fp, "        float:right;   \n");
    fprintf(fp, "        margin-top:0px;   \n");
    fprintf(fp, "        margin-bottom:20px;   \n");
    fprintf(fp, "        font-size:12px;   \n");
    fprintf(fp, "        }  \n \n");

    fprintf(fp, "/* CONTENTS */   \n");
    fprintf(fp, ".con    {   \n");
    fprintf(fp, "        margin-bottom:30px;   \n");
    fprintf(fp, "        clear:both   \n");
    fprintf(fp, "        }   \n");
    fprintf(fp, ".con h2 {   \n");
    fprintf(fp, "        padding:3px;   \n");
    fprintf(fp, "        margin-bottom:10px;   \n");
    fprintf(fp, "        font-size:14px;   \n");
    fprintf(fp, "        }   \n");
    fprintf(fp, ".con div {   \n");
    fprintf(fp, "        font-size:16px;   \n");
    fprintf(fp, "        }   \n");
    fprintf(fp, ".con p  {   \n");
    fprintf(fp, "        margin-top:-1.5em;   \n");
    fprintf(fp, "        margin-left:1.5em;   \n");
    fprintf(fp, "        text-align:justify;   \n");
    fprintf(fp, "        text-justify:distribute;   \n");
    fprintf(fp, "        line-height:120%%;   \n");
    fprintf(fp, "        font-size:12px;   \n");
    fprintf(fp, "        }  \n \n");

    fclose(fp);

    fp = NULL;

  }
}

