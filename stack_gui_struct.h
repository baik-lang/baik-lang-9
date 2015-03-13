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

struct gui_list{
    long     stackid;           // id to connect with stackgui_list

    long     idx;              // arry contents : pos of array
	
	GtkWidget *mywidget;       // arry contents : GUIwidget array [widget0, widget1, widget2, ...]
    GtkWidget *eventbox;  
	int       GUItype;

    struct gui_list *pnext; 
};

struct stackgui_list{
    long      stackid;          // id to connect with gui_list

    char     array_name[256];  // variable name of array

    struct stackgui_list *pnext; 
};

typedef struct gui_array {
  struct gui_list       val;
  struct stackgui_list  var;
} GUI_ARRY;

void   stackGui_push(struct stackgui_list newlist);
void   stackGui_addFirst(struct stackgui_list newlist);
long   stackGui_getID(struct stackgui_list data);
int    stackGui_getPos(struct stackgui_list data);
struct stackgui_list stackGui_removeFirst(void);
void   stackGui_removeAt(int n);

void   gui_addFirst(struct gui_list newlist);
void   gui_push(struct gui_list newlist);
void   gui_removeAll(void);
void   gui_removeAt(int n);
struct gui_list gui_pop(void);
struct gui_list gui_removeFirst(void);
struct gui_list gui_getElement(int n);
void   gui_setElement(int n, struct gui_list newdata);
int    gui_getCount(void);
int    gui_isEmpty(void);
int    gui_findData(struct gui_list data);
int    gui_getIDX(struct gui_list data);
void   gui_printData(void);
struct gui_list gui_getNext(void);
void   gui_setHeadposition(void);

