// //////////////////////////////////////////////////////////////////////
// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
// //////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/stat.h>

#include "baik_word.h"
#include "baik_struct.h"
#include "val_label.h"
#include "baik_lexer.h"

// ///////////////////////////////////
// GTK2
// ///////////////////////////////////
#ifdef USE_GTK2
#include <gtk/gtk.h>
#include <gtk/gtkobject.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#ifdef WINDOWS
#pragma comment(lib, "gtk-win32-2.0.lib")
#pragma comment(lib, "gdk-win32-2.0.lib")
#pragma comment(lib, "gdk_pixbuf-2.0.lib")
#pragma comment(lib, "pango-1.0.lib")
#pragma comment(lib, "cairo.lib")
#pragma comment(lib, "atk-1.0.lib")
#pragma comment(lib, "glib-2.0.lib")
#pragma comment(lib, "gio-2.0.lib")
#pragma comment(lib, "gmodule-2.0.lib")
#pragma comment(lib, "gobject-2.0.lib")
#pragma comment(lib, "gthread-2.0.lib")
#endif

#endif

// ///////////////////////////////////
// GTK3
// ///////////////////////////////////
#ifdef USE_GTK3
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#endif

extern BAIK_LEX lex; 
extern BAIK_ADDR pg; 

VAL_LABEL *pstartVAR, *pendVAR;
VAL_LABEL *glptrVAR;

#ifdef WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#endif

// --------------------------------------------------------------

// ////////////////////////////////////////////
// ValLabel - Generalize function
// ////////////////////////////////////////////

/* --------------------------------------------------------
 TREE Management
-------------------------------------------------------- */

VAL_LABEL ValLabel( char *ident, int deep, VAL_LABEL valdat, int flag )
{
 static VAL_LABEL *root=NULL;

 char inner_ident[MAX_IDENT_LEN+10];

 VAL_LABEL tmpdat;

 int  i=0, idx=0;
 char mystr[MAX_STRING_LEN];

 memset(&tmpdat, '\0', sizeof(tmpdat));
 memset(&mystr, '\0', sizeof(mystr));

 memset(&inner_ident, '\0', sizeof(inner_ident));

 if(ident != NULL) {
   if(valdat.scope != '\0' && valdat.scope == 2) {  // obviuosly Global param
     memset(&inner_ident, '\0', sizeof(inner_ident));
     sprintf(inner_ident,"deepGLOB_%s", ident);
     // printf("global inner: %s\n", inner_ident);
   } else {
     memset(&inner_ident, '\0', sizeof(inner_ident));
     sprintf(inner_ident,"deep%d_%s", deep, ident);
     // printf("inner: %s\n", inner_ident);
   }
 } else {
   Error("var pada inti Baik salah");
 }

 tmpdat.datatype = -1;
 tmpdat.val = -1;
 tmpdat.floatdata = 0.0;
 memset(&tmpdat.str, '\0', sizeof(tmpdat.str));

 // printf("inside ValLabel, flag %d\n", flag);

 if( flag == VAL_FLAG_START ){
   // printf("VAL_FLAG_START \n");
   root = NULL;
   root = MakeValLabelTree( inner_ident, valdat );

   if( root == NULL ) {
     tmpdat.val = 1; // TRUE
     return tmpdat;
   } else {
     tmpdat.val = 0; // FALSE
     return tmpdat;
   }
 }

 if( flag == VAL_FLAG_SEARCH_W || flag == VAL_FLAG_SEARCH_R ){
  
   VAL_LABEL *node = NULL;

   //printf("Val_Label:  - - - - - start to SearchValLabelTree: %s, deep %d\n", ident, deep);
   
   if(root == NULL) {
     printf("Val_Label: root NULL! \n");
   }

   node = SearchValLabelTree( root, inner_ident );

   if( node == NULL ){
     // printf("Search GLOBAL param........... \n");
     node = SearchGLBLabelTree( root, inner_ident );
   }

   //printf("Val_Label: SearchValLabelTree finish, type %d\n", node->datatype);

   if( node != NULL ){
     //printf("node is NOT NULL with flag %d\n", flag);

     if( flag == VAL_FLAG_SEARCH_W ) {
       
       // printf("SEARCH_W : write data to Tree\n"); 
       //printf("after SearchValLabelTree %d\n", valdat.datatype);
      

       /* ------------------------------------------------------------------ */
       node->datatype   = valdat.datatype;
	   node->val        = valdat.val;
       node->floatdata  = valdat.floatdata;

       node->filedata   = valdat.filedata;
       node->isFileOpen = valdat.isFileOpen;   /* file open  */

       #ifndef S_SPLINT_S
       node->sock       = valdat.sock;
       #endif

       strcpy(node->str , valdat.str);
	   // printf("write basic vars OK\n");

       strcpy(node->sql_tmp, valdat.sql_tmp);

       strcpy(node->array_str  , valdat.array_str);
       strcpy(node->array_name , valdat.array_name);
       strcpy(node->array_idx  , valdat.array_idx);

       node->array_max  = valdat.array_max;

       node->array_i      = valdat.array_i;
       node->array_d      = valdat.array_d;
       node->array_s      = valdat.array_s;

	   node->array_widget = valdat.array_widget;

       idx = atoi(valdat.array_idx);
       /* printf("write tmpdat: array_idx %d\n", idx); */

       #ifdef USE_GTK2
	   node->str2  = valdat.str2;
       #endif
       #ifdef USE_GTK3
	   node->str2 = valdat.str2;
       #endif

       node->long_str    = valdat.long_str;
       node->isLongStr   = valdat.isLongStr;

       /* printf("Val_Label cpy sub\n"); */

       strcpy(node->sub_name  , valdat.sub_name);
       strcpy(node->sub_param , valdat.sub_param);
       strcpy(node->sub_file , valdat.sub_file);

       /* printf("Val_Label cpy OK\n"); */

       node->sub_pt_start  = valdat.sub_pt_start;
       node->sub_pt_end    = valdat.sub_pt_end;
       node->sub_pt_return = valdat.sub_pt_return;
	   // printf("write sub vars OK\n");

       #ifdef USE_MYSQL
       /* MYSQL */
       node->my_conn       = valdat.my_conn;
       node->my_res        = valdat.my_res;
       node->my_fd         = valdat.my_fd;
       node->my_row        = valdat.my_row;
       node->isMysqlOpen   = valdat.isMysqlOpen;
	   //printf("write mysql vars OK\n");
       #endif

       #ifdef USE_PGSQL
       /* PGSQL */
       node->pg_conn       = valdat.pg_conn;
       node->pg_res        = valdat.pg_res;
       node->isPgdbOpen    = valdat.isPgdbOpen;
	   //printf("write pgsql vars OK\n");
       #endif

       #ifdef USE_OCI
       /* ORACLE */
       node->ora_conn      = valdat.ora_conn;
       node->ora_stmt      = valdat.ora_stmt;
       node->ora_res       = valdat.ora_res;
	   node->isOraOpen     = valdat.isOraOpen;
       #endif

       #ifdef USE_SQLITE
       /* SQLITE */
	   node->sqlite_conn   = valdat.sqlite_conn;
	   node->sqlite_stmt   = valdat.sqlite_stmt;
	   node->isSqliteOpen  = valdat.isSqliteOpen;
	   //printf("write sqlite vars OK\n");
       #endif

       #ifdef USE_GD
       /* GD Graphic */
       node->gdimg         = valdat.gdimg;
       node->gdfont        = valdat.gdfont;
       node->gdpoint       = valdat.gdpoint;
       // printf("write gd vars OK\n");
       #endif

       /* Obj/Class  */
       strcpy(node->benda_name  , valdat.benda_name);
       strcpy(node->benda_param , valdat.benda_param);

       node->benda_pt_start  = valdat.benda_pt_start;
       node->benda_pt_end    = valdat.benda_pt_end;

       node->isClassVar      = valdat.isClassVar;

       node->scope           = valdat.scope;

       node->isClassInit     = valdat.isClassInit;
	   // printf("write OOP vars OK\n");

       #ifdef USE_GTK2
       /* GTK GUI  */
       node->widget           = valdat.widget;
       node->eventbox         = valdat.eventbox;

	   node->font_desc        = valdat.font_desc;
	   node->color            = valdat.color;
	   for(i=0;i<20;i++)
	    node->pixbuf[i]      = valdat.pixbuf[i];
	   node->filename         = valdat.filename;
	   node->folder           = valdat.folder;
	   node->liststore        = valdat.liststore;
	   node->completion       = valdat.completion;

	   node->buffer           = valdat.buffer;
	   node->IterStart        = valdat.IterStart;
	   node->IterEnd          = valdat.IterEnd;
	   node->clipboard        = valdat.clipboard;

	   node->treestore        = valdat.treestore;
	   node->treeiter         = valdat.treeiter;
	   node->treecolumn       = valdat.treecolumn;

	   node->renderer         = valdat.renderer;
       strcpy(node->tblcoltype, valdat.tblcoltype);

       node->isGUI            = valdat.isGUI;
       node->GUItype          = valdat.GUItype;

	   //printf("write node GUI type : %d\n", valdat.GUItype);

	   node->cr_img           = valdat.cr_img;
	   node->cr_surface       = valdat.cr_surface;
	   node->cr_text_ext      = valdat.cr_text_ext;
	   node->cr_pattern       = valdat.cr_pattern;

	   node->pixmap           = valdat.pixmap;

	   node->gtk_print_set    = valdat.gtk_print_set;
	   node->gtk_print_ope    = valdat.gtk_print_ope;
	   node->gtk_print_res    = valdat.gtk_print_res;
	   node->pango_layout     = valdat.pango_layout;
	   // printf("write gtk vars OK\n");
       #endif


       #ifdef USE_GTK3
	   /* GTK GUI  */
	   node->widget = valdat.widget;
	   node->eventbox = valdat.eventbox;

	   node->font_desc = valdat.font_desc;
	   node->color = valdat.color;
	   for (i = 0; i<20; i++)
		   node->pixbuf[i] = valdat.pixbuf[i];
	   node->filename = valdat.filename;
	   node->folder = valdat.folder;
	   node->liststore = valdat.liststore;
	   node->completion = valdat.completion;

	   node->buffer = valdat.buffer;
	   node->IterStart = valdat.IterStart;
	   node->IterEnd = valdat.IterEnd;
	   node->clipboard = valdat.clipboard;

	   node->treestore = valdat.treestore;
	   node->treeiter = valdat.treeiter;
	   node->treecolumn = valdat.treecolumn;

	   node->renderer = valdat.renderer;
	   strcpy(node->tblcoltype, valdat.tblcoltype);

	   node->isGUI = valdat.isGUI;
	   node->GUItype = valdat.GUItype;

	   //printf("write node GUI type : %d\n", valdat.GUItype);

	   node->cr_img = valdat.cr_img;
	   node->cr_surface = valdat.cr_surface;
	   node->cr_text_ext = valdat.cr_text_ext;
	   node->cr_pattern = valdat.cr_pattern;

	   //node->pixmap = valdat.pixmap;

	   node->gtk_print_set = valdat.gtk_print_set;
	   node->gtk_print_ope = valdat.gtk_print_ope;
	   node->gtk_print_res = valdat.gtk_print_res;
	   node->pango_layout = valdat.pango_layout;
	   // printf("write gtk vars OK\n");
       #endif

       #ifdef USE_PDF
	   node->pdf            = valdat.pdf;
	   node->pdf_font       = valdat.pdf_font;
	   node->pdf_page       = valdat.pdf_page;
	   node->pdf_image      = valdat.pdf_image;
       #endif

       #ifdef USE_SSL
	   node->ssl            = valdat.ssl;
	   node->ssl_ctx        = valdat.ssl_ctx;
	   node->ssl_cert       = valdat.ssl_cert;
	   node->ssl_meth       = valdat.ssl_meth;
       #endif

       /* ----------------------------------------------------------- */
       /* prepare for return value */
       /* ----------------------------------------------------------- */
       tmpdat.datatype  = node->datatype;
       tmpdat.val       = node->val;
       tmpdat.floatdata = node->floatdata;

       tmpdat.filedata   = node->filedata;
       tmpdat.isFileOpen = node->isFileOpen;   /* file open  */

       #ifndef S_SPLINT_S
       tmpdat.sock      = node->sock;
       #endif

       strcpy(tmpdat.str , node->str);

	   strcpy(tmpdat.sql_tmp , node->sql_tmp);

       strcpy(tmpdat.array_str , node->array_str);
       strcpy(tmpdat.array_name , node->array_name);
       strcpy(tmpdat.array_idx , node->array_idx);

       tmpdat.array_max = node->array_max;

       tmpdat.array_i      = node->array_i;
       tmpdat.array_d      = node->array_d;
       tmpdat.array_s      = node->array_s;

       tmpdat.array_widget = node->array_widget;

       // printf("OK2\n");

       #ifdef USE_GTK2
       tmpdat.str2  = node->str2;
       #endif

       #ifdef USE_GTK3
	   tmpdat.str2 = node->str2;
       #endif

       tmpdat.long_str   = node->long_str;
       tmpdat.isLongStr  = node->isLongStr;

       /* printf("Val_Label cpy tmp\n"); */

       strcpy(tmpdat.sub_name , node->sub_name);
       strcpy(tmpdat.sub_param , node->sub_param);
       strcpy(tmpdat.sub_file , node->sub_file);

       /* printf("Val_Label tmp OK\n"); */

       tmpdat.sub_pt_start = node->sub_pt_start;
       tmpdat.sub_pt_end = node->sub_pt_end;
       tmpdat.sub_pt_return = node->sub_pt_return;

       #ifdef USE_MYSQL
       /* MYSQL */
       tmpdat.my_conn = node->my_conn;
       tmpdat.my_res  = node->my_res;
       tmpdat.my_fd   = node->my_fd;
       tmpdat.my_row  = node->my_row;
	   tmpdat.isMysqlOpen = node->isMysqlOpen;
       #endif

       #ifdef USE_PGSQL
       /* PGSQL */
       tmpdat.pg_conn = node->pg_conn;
       tmpdat.pg_res  = node->pg_res;
       tmpdat.isPgdbOpen = node->isPgdbOpen;
       #endif

       #ifdef USE_OCI
       /* ORACLE */
       tmpdat.ora_conn = node->ora_conn;
       tmpdat.ora_stmt = node->ora_stmt;
       tmpdat.ora_res  = node->ora_res;
	   tmpdat.isOraOpen = node->isOraOpen;
       #endif

       #ifdef USE_SQLITE
       /* SQLITE */
	   tmpdat.sqlite_conn  = node->sqlite_conn;
	   tmpdat.sqlite_stmt  = node->sqlite_stmt;
	   tmpdat.isSqliteOpen = node->isSqliteOpen;
       #endif

       #ifdef USE_GD
       /* GD Graphic */
       tmpdat.gdimg   = node->gdimg;
       tmpdat.gdfont  = node->gdfont;
       tmpdat.gdpoint = node->gdpoint;
       #endif

       /* Obj/Class */
       strcpy(tmpdat.benda_name , node->benda_name);
       strcpy(tmpdat.benda_param , node->benda_param);

       tmpdat.benda_pt_start = node->benda_pt_start;
       tmpdat.benda_pt_end = node->benda_pt_end;

       tmpdat.isClassVar  = node->isClassVar;

       tmpdat.scope       = node->scope;

       tmpdat.isClassInit = node->isClassInit;

       #ifdef USE_GTK2
       /* GTK GUI  */
       tmpdat.widget      = node->widget;
       tmpdat.eventbox    = node->eventbox;

	   tmpdat.font_desc   = node->font_desc;
	   tmpdat.color       = node->color;
	   for(i=0;i<20;i++)
	     tmpdat.pixbuf[i] = node->pixbuf[i];
	   tmpdat.filename    = node->filename;
	   tmpdat.folder      = node->folder;
	   tmpdat.liststore   = node->liststore;
	   tmpdat.completion  = node->completion;

	   tmpdat.buffer      = node->buffer;
	   tmpdat.IterStart   = node->IterStart;
	   tmpdat.IterEnd     = node->IterEnd;
	   tmpdat.clipboard   = node->clipboard;

	   tmpdat.treestore   = node->treestore;
	   tmpdat.treeiter    = node->treeiter;
	   tmpdat.treecolumn  = node->treecolumn;

	   tmpdat.renderer    = node->renderer;
       strcpy(tmpdat.tblcoltype , node->tblcoltype);

       tmpdat.isGUI       = node->isGUI;
       tmpdat.GUItype     = node->GUItype;

	   tmpdat.cr_img      = node->cr_img;
	   tmpdat.cr_surface  = node->cr_surface;
	   tmpdat.cr_text_ext = node->cr_text_ext;
	   tmpdat.cr_pattern  = node->cr_pattern;

	   tmpdat.pixmap      = node->pixmap;

	   tmpdat.gtk_print_set  = node->gtk_print_set;
	   tmpdat.gtk_print_ope  = node->gtk_print_ope;
	   tmpdat.gtk_print_res  = node->gtk_print_res;
	   tmpdat.pango_layout   = node->pango_layout;
       #endif

       #ifdef USE_GTK3
	   /* GTK GUI  */
	   tmpdat.widget = node->widget;
	   tmpdat.eventbox = node->eventbox;

	   tmpdat.font_desc = node->font_desc;
	   tmpdat.color = node->color;
	   for (i = 0; i<20; i++)
		   tmpdat.pixbuf[i] = node->pixbuf[i];
	   tmpdat.filename = node->filename;
	   tmpdat.folder = node->folder;
	   tmpdat.liststore = node->liststore;
	   tmpdat.completion = node->completion;

	   tmpdat.buffer = node->buffer;
	   tmpdat.IterStart = node->IterStart;
	   tmpdat.IterEnd = node->IterEnd;
	   tmpdat.clipboard = node->clipboard;

	   tmpdat.treestore = node->treestore;
	   tmpdat.treeiter = node->treeiter;
	   tmpdat.treecolumn = node->treecolumn;

	   tmpdat.renderer = node->renderer;
	   strcpy(tmpdat.tblcoltype, node->tblcoltype);

	   tmpdat.isGUI = node->isGUI;
	   tmpdat.GUItype = node->GUItype;

	   tmpdat.cr_img = node->cr_img;
	   tmpdat.cr_surface = node->cr_surface;
	   tmpdat.cr_text_ext = node->cr_text_ext;
	   tmpdat.cr_pattern = node->cr_pattern;

	   //tmpdat.pixmap = node->pixmap;

	   tmpdat.gtk_print_set = node->gtk_print_set;
	   tmpdat.gtk_print_ope = node->gtk_print_ope;
	   tmpdat.gtk_print_res = node->gtk_print_res;
	   tmpdat.pango_layout = node->pango_layout;
       #endif

       #ifdef USE_PDF
	   tmpdat.pdf         = node->pdf;
	   tmpdat.pdf_font    = node->pdf_font;
	   tmpdat.pdf_page    = node->pdf_page;
	   tmpdat.pdf_image   = node->pdf_image;
       #endif

       #ifdef USE_SSL
	   tmpdat.ssl         = node->ssl;
	   tmpdat.ssl_ctx     = node->ssl_ctx;
	   tmpdat.ssl_cert    = node->ssl_cert;
	   tmpdat.ssl_meth    = node->ssl_meth;
       #endif

     } else {
       //printf("SEARCH: read data from Tree\n");
	   //printf("SEARCH: read node type %d \n", node->datatype);

	  if(node->str != '\0' && strlen(node->str) > 0 ) {
         /* for String */
         tmpdat.datatype  = 3; // be careful
         tmpdat.val       = node->val;
         tmpdat.filedata  = NULL;
         strcpy(tmpdat.str , node->str);

         #ifdef USE_GTK2
         /* GTK GUI  */
         tmpdat.widget        = node->widget;
         tmpdat.eventbox      = node->eventbox;

	     tmpdat.font_desc     = node->font_desc;
	     tmpdat.color         = node->color;
	     for(i=0;i<20;i++)
	       tmpdat.pixbuf[i]   = node->pixbuf[i];
	     tmpdat.filename      = node->filename;
	     tmpdat.folder        = node->folder;
	     strcpy(tmpdat.tblcoltype  , node->tblcoltype);

         tmpdat.isGUI         = node->isGUI;
         tmpdat.GUItype       = node->GUItype;

	     if(node->GUItype == 15) {
           tmpdat.datatype  = 42; // font dialog - be careful
	     } else
	     if(node->GUItype == 16) {
           tmpdat.datatype  = 43; // color dialog - be careful
	     } else
	     if(node->GUItype == 17) {
           tmpdat.datatype  = 44; // file dialog - be careful
	     }
         #endif

         #ifdef USE_GTK3
		 /* GTK GUI  */
		 tmpdat.widget = node->widget;
		 tmpdat.eventbox = node->eventbox;

		 tmpdat.font_desc = node->font_desc;
		 tmpdat.color = node->color;
		 for (i = 0; i<20; i++)
			 tmpdat.pixbuf[i] = node->pixbuf[i];
		 tmpdat.filename = node->filename;
		 tmpdat.folder = node->folder;
		 strcpy(tmpdat.tblcoltype, node->tblcoltype);

		 tmpdat.isGUI = node->isGUI;
		 tmpdat.GUItype = node->GUItype;

		 if (node->GUItype == 15) {
			 tmpdat.datatype = 42; // font dialog - be careful
		 }
		 else
		 if (node->GUItype == 16) {
			 tmpdat.datatype = 43; // color dialog - be careful
		 }
		 else
		 if (node->GUItype == 17) {
			 tmpdat.datatype = 44; // file dialog - be careful
		 }
         #endif

       } else {
         /* for NOT String */
		 //printf("search NOT String, val %d \n", node->val);
		 memset(&tmpdat, '\0', sizeof(tmpdat));

         strcpy( tmpdat.ident, node->ident );
         
         strcpy(tmpdat.str , node->str); 

         tmpdat.datatype  = node->datatype;
         tmpdat.floatdata = node->floatdata;
         tmpdat.val       = node->val;

         tmpdat.filedata  = node->filedata;
         tmpdat.isFileOpen= node->isFileOpen;

         #ifndef S_SPLINT_S
         tmpdat.sock      = node->sock;
         #endif

	     strcpy(tmpdat.sql_tmp , node->sql_tmp); 

         // printf("search basic OK\n");
         
         strcpy(tmpdat.array_str , node->array_str);
         strcpy(tmpdat.array_name , node->array_name);
         strcpy(tmpdat.array_idx , node->array_idx);
         /* printf("copy array name ok\n"); */
         tmpdat.array_max = node->array_max;

         tmpdat.array_i      = node->array_i;
         tmpdat.array_d      = node->array_d;
         tmpdat.array_s      = node->array_s;

         tmpdat.array_widget = node->array_widget;

         // printf("search array basic OK: %d\n", node->array_max);

         #ifdef USE_GTK2
		 tmpdat.widget = node->widget;
		 tmpdat.eventbox = node->eventbox;

		 tmpdat.font_desc = node->font_desc;
		 tmpdat.color = node->color;
		 for (i = 0; i<20; i++)
			 tmpdat.pixbuf[i] = node->pixbuf[i];
		 tmpdat.filename = node->filename;
		 tmpdat.folder = node->folder;
		 strcpy(tmpdat.tblcoltype, node->tblcoltype);

		 tmpdat.isGUI = node->isGUI;
		 tmpdat.GUItype = node->GUItype;

		 //printf("get node GUI type : %d\n", tmpdat.GUItype);


		 tmpdat.str2 = node->str2;

		 if (node->GUItype == 15) {
			 tmpdat.datatype = 42; // font dialog - be careful
		 }
		 else
		 if (node->GUItype == 16) {
			 tmpdat.datatype = 43; // color dialog - be careful
		 }
		 else
		 if (node->GUItype == 17) {
			 tmpdat.datatype = 44; // file dialog - be careful
		 }

         #endif

         #ifdef USE_GTK3
		 tmpdat.widget = node->widget;
		 tmpdat.eventbox = node->eventbox;

		 tmpdat.font_desc = node->font_desc;
		 tmpdat.color = node->color;
		 for (i = 0; i<20; i++)
			 tmpdat.pixbuf[i] = node->pixbuf[i];
		 tmpdat.filename = node->filename;
		 tmpdat.folder = node->folder;
		 strcpy(tmpdat.tblcoltype, node->tblcoltype);

		 tmpdat.isGUI = node->isGUI;
		 tmpdat.GUItype = node->GUItype;

		 //printf("get node GUI type : %d\n", tmpdat.GUItype);


		 tmpdat.str2 = node->str2;

		 if (node->GUItype == 15) {
			 tmpdat.datatype = 42; // font dialog - be careful
		 }
		 else
		 if (node->GUItype == 16) {
			 tmpdat.datatype = 43; // color dialog - be careful
		 }
		 else
		 if (node->GUItype == 17) {
			 tmpdat.datatype = 44; // file dialog - be careful
		 }

         #endif

	     tmpdat.long_str   = node->long_str;
         tmpdat.isLongStr  = node->isLongStr;

         // printf("start to get sub\n");

         strcpy(tmpdat.sub_name , node->sub_name);
         strcpy(tmpdat.sub_param , node->sub_param);
         strcpy(tmpdat.sub_file , node->sub_file);

         tmpdat.sub_pt_start  = node->sub_pt_start;
         tmpdat.sub_pt_end    = node->sub_pt_end;
         tmpdat.sub_pt_return = node->sub_pt_return;

         // printf("search get sub OK\n");

         #ifdef USE_MYSQL
         /* MYSQL */
         tmpdat.my_conn     = node->my_conn;
         tmpdat.my_res      = node->my_res;
         tmpdat.my_fd       = node->my_fd;
         tmpdat.my_row      = node->my_row;
         tmpdat.isMysqlOpen = node->isMysqlOpen;
         #endif

         #ifdef USE_PGSQL
         /* PGSQL */
         tmpdat.pg_conn     = node->pg_conn;
         tmpdat.pg_res      = node->pg_res;
	     tmpdat.isPgdbOpen  = node->isPgdbOpen;
         #endif

         #ifdef USE_OCI
         /* ORACLE */
         tmpdat.ora_conn     = node->ora_conn;
         tmpdat.ora_stmt     = node->ora_stmt;          
	     tmpdat.ora_res      = node->ora_res;
	     tmpdat.isOraOpen    = node->isOraOpen;
         #endif

         #ifdef USE_SQLITE
         /* SQLITE */
	     tmpdat.sqlite_conn  = node->sqlite_conn;
	     tmpdat.sqlite_stmt  = node->sqlite_stmt;
	     tmpdat.isSqliteOpen = node->isSqliteOpen;
         #endif

         #ifdef USE_GD
         /* GD Graphic */
         tmpdat.gdimg       = node->gdimg;
         tmpdat.gdfont      = node->gdfont;
         tmpdat.gdpoint     = node->gdpoint;
         #endif
         
         /* Obj/Class  */
         strcpy(tmpdat.benda_name , node->benda_name);
         strcpy(tmpdat.benda_param , node->benda_param);

         tmpdat.benda_pt_start  = node->benda_pt_start;
         tmpdat.benda_pt_end    = node->benda_pt_end;

         tmpdat.isClassVar    = node->isClassVar;

         tmpdat.scope         = node->scope;

         tmpdat.isClassInit   = node->isClassInit;

         #ifdef USE_GTK2
         /* GTK GUI  */
         tmpdat.widget        = node->widget;
         tmpdat.eventbox      = node->eventbox;

	     tmpdat.font_desc     = node->font_desc;
	     tmpdat.color         = node->color;

	     for(i=0;i<20;i++) {
	       tmpdat.pixbuf[i]   = node->pixbuf[i];
	     }

	     tmpdat.filename      = node->filename;
	     tmpdat.folder        = node->folder;
	     tmpdat.liststore     = node->liststore;
	     tmpdat.completion    = node->completion;

	     tmpdat.renderer      = node->renderer;
	     tmpdat.clipboard     = node->clipboard;

	     tmpdat.buffer        = node->buffer;
	     tmpdat.IterStart     = node->IterStart;
	     tmpdat.IterEnd       = node->IterEnd;

	     strcpy(tmpdat.tblcoltype  , node->tblcoltype);

		 tmpdat.treeiter      = node->treeiter;
		 tmpdat.treestore     = node->treestore;
		 tmpdat.treecolumn    = node->treecolumn;

         tmpdat.isGUI         = node->isGUI;
         tmpdat.GUItype       = node->GUItype;

		 //printf("node GUI type : %d\n", tmpdat.GUItype);

		 tmpdat.cr_img        = node->cr_img;
		 tmpdat.cr_surface    = node->cr_surface;
		 tmpdat.cr_text_ext   = node->cr_text_ext;
		 tmpdat.cr_pattern    = node->cr_pattern;

		 tmpdat.pixmap        = node->pixmap;

		 tmpdat.gtk_print_set = node->gtk_print_set;
		 tmpdat.gtk_print_ope = node->gtk_print_ope;
		 tmpdat.gtk_print_res = node->gtk_print_res;
		 tmpdat.pango_layout  = node->pango_layout;
         #endif

         #ifdef USE_GTK3
		 /* GTK GUI  */
		 tmpdat.widget = node->widget;
		 tmpdat.eventbox = node->eventbox;

		 tmpdat.font_desc = node->font_desc;
		 tmpdat.color = node->color;

		 for (i = 0; i<20; i++) {
			 tmpdat.pixbuf[i] = node->pixbuf[i];
		 }

		 tmpdat.filename = node->filename;
		 tmpdat.folder = node->folder;
		 tmpdat.liststore = node->liststore;
		 tmpdat.completion = node->completion;

		 tmpdat.renderer = node->renderer;
		 tmpdat.clipboard = node->clipboard;

		 tmpdat.buffer = node->buffer;
		 tmpdat.IterStart = node->IterStart;
		 tmpdat.IterEnd = node->IterEnd;

		 strcpy(tmpdat.tblcoltype, node->tblcoltype);

		 tmpdat.treeiter = node->treeiter;
		 tmpdat.treestore = node->treestore;
		 tmpdat.treecolumn = node->treecolumn;

		 tmpdat.isGUI = node->isGUI;
		 tmpdat.GUItype = node->GUItype;

		 //printf("node GUI type : %d\n", tmpdat.GUItype);

		 tmpdat.cr_img = node->cr_img;
		 tmpdat.cr_surface = node->cr_surface;
		 tmpdat.cr_text_ext = node->cr_text_ext;
		 tmpdat.cr_pattern = node->cr_pattern;

//		 tmpdat.pixmap = node->pixmap;

		 tmpdat.gtk_print_set = node->gtk_print_set;
		 tmpdat.gtk_print_ope = node->gtk_print_ope;
		 tmpdat.gtk_print_res = node->gtk_print_res;
		 tmpdat.pango_layout = node->pango_layout;
         #endif

         #ifdef USE_PDF
		 tmpdat.pdf           = node->pdf;
		 tmpdat.pdf_font      = node->pdf_font;
		 tmpdat.pdf_page      = node->pdf_page;
		 tmpdat.pdf_image     = node->pdf_image;
         #endif

         #ifdef USE_SSL
		 tmpdat.ssl           = node->ssl;
		 tmpdat.ssl_ctx       = node->ssl_ctx;
		 tmpdat.ssl_cert      = node->ssl_cert;
		 tmpdat.ssl_meth      = node->ssl_meth;
         #endif

       }

     }

     /*
     if(tmpdat.datatype == 6) {
      printf("search tmpdat: array_name %s\n", tmpdat.array_name);
      printf("search tmpdat: datatype %d\n", tmpdat.datatype);
      printf("search tmpdat: array_max %d\n", tmpdat.array_max);
      printf("\n ValLabel: get arr val 0 : %d" , tmpdat.array_i[0]);
      printf("\n ValLabel: get arr val 1 : %d" , tmpdat.array_i[1]);
     }
     printf("\n ValLabel: get str : %s\n" , tmpdat.str);
     */

     // printf("search return tmpdat: datatype %d\n", tmpdat.datatype);

     return tmpdat;

   }else{
	 //printf("search Data is NULL, so make new one : %s\n", inner_ident);
     
     if( flag == VAL_FLAG_SEARCH_W ){
	   valdat.recursive_depth = deep;

       if( MakeAddValLabelTree( root, inner_ident, valdat ) )
         Error("Interpreter salah : MakeAddValLabelTree");
     }
     return valdat;
   }
 }

 if( flag == VAL_FLAG_SEARCH_D ){       // Del a Node
   return tmpdat;
 }

 if( flag == VAL_FLAG_PRINT ){          // Print inside Tree
   printf("---mem awal---------------------------------\n");
   PrintValLabelTree( root );
   printf("---mem akhir--------------------------------\n");
   tmpdat.val = 0; // FALSE
   return tmpdat;
 }

 if( flag == VAL_FLAG_END ){            // Del All Nodes
   DeleteValLabelTree( root );
   tmpdat.val = 0; // FALSE

   return tmpdat;
 }

 tmpdat.val = 1; // TRUE
 return tmpdat;

}


VAL_LABEL *MakeValLabelTree( char *inner_ident, VAL_LABEL valdat )
{
 VAL_LABEL *node;

 int i=0;

 node = NULL;

 //printf("malloc of MakeNode start...\n");
 //printf("make datatype %d\n", valdat.datatype);
 //printf("make val %d\n", valdat.val);
 //printf("make ident %s\n", inner_ident);
 
 node = (VAL_LABEL *)malloc(sizeof(VAL_LABEL));
 // printf("malloc of MakeNode done\n");

 if(node == NULL) {
   Error("malloc : memori tidak cukup\n");
 }

 node->val = 0;
 strcpy( node->ident, inner_ident ); // use special inner name (with depth)

 node->datatype = valdat.datatype;

 /* printf("make datatype OK %d\n", valdat.datatype); */
 
 node->recursive_depth = valdat.recursive_depth;  

 node->val = valdat.val;                 /* int        */
 node->floatdata = valdat.floatdata;     /* double     */

 node->filedata   = valdat.filedata;     /* file       */
 node->isFileOpen = valdat.isFileOpen;   /* file open  */

 #ifndef S_SPLINT_S
 node->sock       = valdat.sock;
 #endif

 memset(&node->str, '\0', sizeof(node->str));
 strcpy(node->str, valdat.str);                        /* string     */

 memset(&node->sql_tmp, '\0', sizeof(node->sql_tmp));
 strcpy(node->sql_tmp, valdat.sql_tmp);                /* sql tmp     */

 strcpy(node->array_str, valdat.array_str);
 strcpy(node->array_name, valdat.array_name);
 strcpy(node->array_idx, valdat.array_idx);

 node->array_max = valdat.array_max;

 node->array_i      = valdat.array_i;
 node->array_d      = valdat.array_d;
 node->array_s      = valdat.array_s;

 node->array_widget = valdat.array_widget;

 /* printf("make tree: array_max %d\n", valdat.array_max);         */
 /* printf("make tree: lex type %d\n", lex.type);                  */
 /* printf("make tree: array string OK\n", valdat.array_max); */

 #ifdef USE_GTK2
 // printf("make str2 in node\n");
 node->str2        = NULL;
 //node->str2      = (char *)malloc(sizeof(valdat.str2));
 // Dont Do malloc
 node->str2      = valdat.str2;
 // printf("make str2 ok\n");
 #endif

#ifdef USE_GTK3
 // printf("make str2 in node\n");
 node->str2 = NULL;
 //node->str2      = (char *)malloc(sizeof(valdat.str2));
 // Dont Do malloc
 node->str2 = valdat.str2;
 // printf("make str2 ok\n");
#endif
 
 node->long_str      = valdat.long_str;
 node->isLongStr     = valdat.isLongStr;

 strcpy(node->sub_name, valdat.sub_name);
 strcpy(node->sub_param, valdat.sub_param);
 strcpy(node->sub_file, valdat.sub_file);

 node->sub_pt_start  = valdat.sub_pt_start;
 node->sub_pt_end    = valdat.sub_pt_end;
 node->sub_pt_return = valdat.sub_pt_return;

 /*
 if(valdat.datatype != '\0')
   printf("inside node: datatype %d\n", node->datatype);
 
 printf("MakeValLabelTree: get f : %f\n" , node->floatdata);
 
 if(valdat.datatype == 6) {
  printf("inside node: ident %s\n", node->ident);
  printf("inside valdat: array_name %s\n", valdat.array_name);
  printf("inside valdat: datatype %d\n", valdat.datatype);
  printf("inside valdat: array_max %d\n", node->array_max);
  printf("inside valdat: array 0 %d\n", node->array_i[0]);
 }
 */

#ifdef USE_MYSQL
 /* MYSQL */
 node->my_conn      = NULL;
 node->my_res       = NULL;
 node->my_fd        = NULL;

 node->my_conn      = valdat.my_conn;
 node->my_res       = valdat.my_res;
 node->my_fd        = valdat.my_fd;
 node->my_row       = valdat.my_row;
 node->isMysqlOpen  = valdat.isMysqlOpen;
#endif


#ifdef USE_PGSQL
 /* PGSQL */
 node->pg_conn      = NULL;
 node->pg_res       = NULL;

 node->pg_conn      = valdat.pg_conn;
 node->pg_res       = valdat.pg_res;
 node->isPgdbOpen   = valdat.isPgdbOpen;
#endif

#ifdef USE_OCI
 /* ORACLE */
 node->ora_conn      = NULL;
 node->ora_stmt      = NULL;
 node->ora_res       = NULL;

 node->ora_conn      = valdat.ora_conn;
 node->ora_stmt      = valdat.ora_stmt;
 node->ora_res       = valdat.ora_res;
 node->isOraOpen     = valdat.isOraOpen;
#endif

#ifdef USE_SQLITE
 /* SQLITE */
 node->sqlite_conn  = NULL;
 node->sqlite_stmt  = NULL;

 node->sqlite_conn  = valdat.sqlite_conn;
 node->sqlite_stmt  = valdat.sqlite_stmt;
 node->isSqliteOpen = valdat.isSqliteOpen;
#endif

#ifdef USE_GD
 /* GD Graphic Library */
 node->gdimg      = NULL;
 node->gdfont     = NULL;

 node->gdimg      = valdat.gdimg;        /* gd img      */
 node->gdfont     = valdat.gdfont;       /* gd font     */
 node->gdpoint    = valdat.gdpoint;      /* gd point    */
#endif

 /* Objec/Class Handle */
 strcpy(node->benda_name, valdat.benda_name);
 strcpy(node->benda_param, valdat.benda_param);

 node->benda_pt_start  = valdat.benda_pt_start;
 node->benda_pt_end    = valdat.benda_pt_end;

 node->isClassVar      = valdat.isClassVar;

 node->scope           = valdat.scope;
 
 node->isClassInit     = valdat.isClassInit;

 #ifdef USE_GTK2
 /* GTK GUI Handle */
 node->widget           = NULL;
 node->eventbox         = NULL;

 node->widget           = valdat.widget;
 node->eventbox         = valdat.eventbox;
 node->font_desc        = valdat.font_desc;
 node->color            = valdat.color;

 for(i=0;i<20;i++) {
   node->pixbuf[i]      = NULL;
   node->pixbuf[i]      = valdat.pixbuf[i];
 }

 node->filename         = NULL;
 if(valdat.datatype == 44 ) {
   node->filename       = (char *)malloc(sizeof(valdat.filename));
   node->filename       = valdat.filename;
 }
 node->folder           = NULL;
 if(valdat.datatype == 44 ) {
   node->folder         = (char *)malloc(sizeof(valdat.folder));
   node->folder         = valdat.folder;
 }
 node->liststore        = valdat.liststore;
 node->completion       = valdat.completion;

 node->buffer           = valdat.buffer;
 node->IterStart        = valdat.IterStart;
 node->IterEnd          = valdat.IterEnd;
 node->clipboard        = valdat.clipboard;

 node->renderer         = valdat.renderer;

 node->treestore        = valdat.treestore;
 node->treeiter         = valdat.treeiter;
 node->treecolumn       = valdat.treecolumn;

 memset(&node->tblcoltype, '\0', sizeof(node->tblcoltype));
 strcpy(node->tblcoltype, valdat.tblcoltype);

 node->isGUI            = valdat.isGUI;
 node->GUItype          = valdat.GUItype;

 // printf("save node GUI type : %d\n", valdat.GUItype);

 node->cr_img           = valdat.cr_img;
 node->cr_surface       = valdat.cr_surface;
 node->cr_text_ext      = valdat.cr_text_ext;
 node->cr_pattern       = valdat.cr_pattern;

 node->pixmap           = valdat.pixmap;

 node->gtk_print_set    = valdat.gtk_print_set;
 node->gtk_print_ope    = valdat.gtk_print_ope;
 node->gtk_print_res    = valdat.gtk_print_res;
 node->pango_layout     = valdat.pango_layout;
 #endif

#ifdef USE_GTK3
 /* GTK GUI Handle */
 node->widget = NULL;
 node->eventbox = NULL;

 node->widget = valdat.widget;
 node->eventbox = valdat.eventbox;
 node->font_desc = valdat.font_desc;
 node->color = valdat.color;

 for (i = 0; i<20; i++) {
	 node->pixbuf[i] = NULL;
	 node->pixbuf[i] = valdat.pixbuf[i];
 }

 node->filename = NULL;
 if (valdat.datatype == 44) {
	 node->filename = (char *)malloc(sizeof(valdat.filename));
	 node->filename = valdat.filename;
 }
 node->folder = NULL;
 if (valdat.datatype == 44) {
	 node->folder = (char *)malloc(sizeof(valdat.folder));
	 node->folder = valdat.folder;
 }
 node->liststore = valdat.liststore;
 node->completion = valdat.completion;

 node->buffer = valdat.buffer;
 node->IterStart = valdat.IterStart;
 node->IterEnd = valdat.IterEnd;
 node->clipboard = valdat.clipboard;

 node->renderer = valdat.renderer;

 node->treestore = valdat.treestore;
 node->treeiter = valdat.treeiter;
 node->treecolumn = valdat.treecolumn;

 memset(&node->tblcoltype, '\0', sizeof(node->tblcoltype));
 strcpy(node->tblcoltype, valdat.tblcoltype);

 node->isGUI = valdat.isGUI;
 node->GUItype = valdat.GUItype;

 // printf("save node GUI type : %d\n", valdat.GUItype);

 node->cr_img = valdat.cr_img;
 node->cr_surface = valdat.cr_surface;
 node->cr_text_ext = valdat.cr_text_ext;
 node->cr_pattern = valdat.cr_pattern;

 //node->pixmap = valdat.pixmap;

 node->gtk_print_set = valdat.gtk_print_set;
 node->gtk_print_ope = valdat.gtk_print_ope;
 node->gtk_print_res = valdat.gtk_print_res;
 node->pango_layout = valdat.pango_layout;
#endif

 #ifdef USE_PDF
 node->pdf              = valdat.pdf;
 node->pdf_font         = valdat.pdf_font;
 node->pdf_page         = valdat.pdf_page;
 node->pdf_image        = valdat.pdf_image;
 #endif

 #ifdef USE_SSL
 node->ssl              = valdat.ssl;
 node->ssl_ctx          = valdat.ssl_ctx;
 node->ssl_cert         = valdat.ssl_cert;
 node->ssl_meth         = valdat.ssl_meth;
 #endif


 /* Tree */
 node->left  = NULL;
 node->right = NULL;

 return node;

}

void AddValLabelTree( VAL_LABEL *t, VAL_LABEL *n )
{
 int judge = strcmp( t->ident, n->ident );

 if( judge > 0 ){
   if( t->left != NULL )
     AddValLabelTree( t->left, n );
   else
     t->left = n;
 }
 else
 if( judge < 0 ){
   if( t->right != NULL )
     AddValLabelTree( t->right, n );
   else
     t->right = n;
 }
}


int MakeAddValLabelTree( VAL_LABEL *t, char *inner_ident, VAL_LABEL valdat )
{
 VAL_LABEL *node = NULL;
 if( (node = MakeValLabelTree( inner_ident, valdat )) == NULL )
   return 1;

 // node has special ident name with depth

 AddValLabelTree( t, node );
 return 0;
}


VAL_LABEL *SearchValLabelTree( VAL_LABEL *t, char *inner_ident )
{
 int judge;

 // printf("SearchValLabelTree : t-ident %s <-> ident %s \n", t->ident, inner_ident);
 judge = strcmp( t->ident, inner_ident );
 // printf("   SearchValLabelTree judge: %d\n", judge);

 if( judge == 0) {
   // printf(" FOUND t type %d, val %d\n", t->datatype, t->val);
   return t;
 } 

 if( judge > 0 && t->left != NULL )
     return ( SearchValLabelTree( t->left, inner_ident ) );

 else
 if( judge < 0 && t->right != NULL )
     return ( SearchValLabelTree( t->right, inner_ident ) );


 return NULL;
}


VAL_LABEL *SearchGLBLabelTree( VAL_LABEL *t, char *inner_ident )
{
 int judge2;
 int i=0, j=0;
 char ch = '\0';
 char globIdent[MAX_STRING_LEN+10];
 char pureIdent[MAX_STRING_LEN+10];

 memset(&globIdent, '\0', sizeof(globIdent));
 memset(&pureIdent, '\0', sizeof(pureIdent));

 i=0;
 do {
   ch = inner_ident[i];
   i++;
 } while(ch != '_' && ch != '\0');

 j=0;
 do {
   pureIdent[j] = inner_ident[i];
   i++;   j++;
 } while (inner_ident[i] != '\0');
 pureIdent[j] = '\0';

 sprintf(globIdent, "deepGLOB_%s", pureIdent);

 // printf("SearchValLabelTree pure: %s\n", pureIdent);

 // printf("SearchValLabelTree : t-ident %s val %d <-> ident %s \n", t->ident, t->val, globIdent);
 judge2 = strcmp( t->ident, globIdent ) ;
 // printf("   SearchValLabelTree judge2: %d\n", judge2);

 if( judge2 == 0) {
   // printf(" FOUND t type %d, val %d\n", t->datatype, t->val);
   return t;
 } 

 if( judge2 > 0 && t->left != NULL )
     return ( SearchValLabelTree( t->left, globIdent) );

 else
 if( judge2 < 0 && t->right != NULL )
     return ( SearchValLabelTree( t->right, globIdent) );


 return NULL;
}

void PrintValLabelTree(VAL_LABEL *p)
{
    static int  depth = 0;

    if(p->right != NULL){
        ++depth;
        PrintValLabelTree(p->right);
        --depth;
    }

	if(p->datatype == 0)
      printf("%s  %li\n", p->ident, p->val);
	else if (p->datatype == 1)
	  printf("%s  %f\n", p->ident, p->floatdata);
	else if (p->datatype == 3)
      printf("%s  %s\n", p->ident, p->str);
	else if (p->datatype == 9)
      printf("%s  nama-fungsi\n", p->ident);
	else if (p->datatype == 40)
      printf("%s  komponen-layar\n", p->ident);
	else
	  printf("%s  type:%d\n", p->ident, p->datatype);

    if(p->left != NULL){
        ++depth;
        PrintValLabelTree(p->left);
        --depth;
    }
}

void DeleteValLabelTree( VAL_LABEL *t )
{
 // printf("clear all vars...\n");

 if( t->left != NULL )
   DeleteValLabelTree( t->left );

 if( t->right != NULL )
   DeleteValLabelTree( t->right );

 if(t != NULL ) {
   free(t);
 }

}


