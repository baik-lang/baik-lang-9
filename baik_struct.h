// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#define MAX_IDENT_LEN   64

#define MAX_STRING_LEN  300

#ifdef WINDOWS
#include <windows.h>
#include <direct.h>

#pragma comment(lib, "libmysql.lib")
#endif

// ///////////////////////////////////
// GD Header
// ///////////////////////////////////
#ifdef USE_GD
#include "gd.h"
#include "gdfontt.h"
#include "gdfonts.h"
#include "gdfontmb.h"
#include "gdfontl.h"
#include "gdfontg.h"
#endif

// ///////////////////////////////////
// MYSQL Header
// ///////////////////////////////////
#ifdef USE_MYSQL
#include <mysql.h>
#endif

// ///////////////////////////////////
// PGSQL Header
// ///////////////////////////////////
#ifdef USE_PGSQL
#include <libpq-fe.h>
#endif

// ///////////////////////////////////
// ORACLE Header
// ///////////////////////////////////
#ifdef USE_OCI
#include <ocilib.h>
#endif

// ///////////////////////////////////
// SQLITE Header
// ///////////////////////////////////
#ifdef USE_SQLITE
#include <sqlite3.h>
#endif

// ///////////////////////////////////
// GTK2
// ///////////////////////////////////
#ifdef USE_GTK2
#include <gtk/gtk.h>
#include <gtk/gtkobject.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#pragma comment(lib, "gtk-win32-2.0.lib")
#pragma comment(lib, "gdk-win32-2.0.lib")
#pragma comment(lib, "gdk_pixbuf-2.0.lib")

#pragma comment(lib, "pango-1.0.lib")
#pragma comment(lib, "cairo.lib")
#pragma comment(lib, "pangocairo-1.0.lib")
#pragma comment(lib, "atk-1.0.lib")
#pragma comment(lib, "glib-2.0.lib")
#pragma comment(lib, "gio-2.0.lib")
#pragma comment(lib, "gmodule-2.0.lib")
#pragma comment(lib, "gobject-2.0.lib")
#pragma comment(lib, "gthread-2.0.lib")
#endif


// ///////////////////////////////////
// GTK3
// ///////////////////////////////////
#ifdef USE_GTK3
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#endif

// ///////////////////////////////////
// PDF Header
// ///////////////////////////////////
#ifdef USE_PDF
#include "hpdf.h"
#endif


// ///////////////////////////////////
// Open SSL
// ///////////////////////////////////
#ifdef USE_SSL
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#endif

// -----------------------------------------------------

typedef struct
{

  int type;                             // type of lex
  char type_word[MAX_STRING_LEN/2];     // string of langword if any

  union{
    long num;                           /* number             */
    double dblnum;                      /* double             */

    char ident[MAX_IDENT_LEN+10];       /* var or label name  */
    char string[MAX_STRING_LEN];        /* string             */
    char symbol;                        /* symbol char        */
    char array_str[MAX_STRING_LEN];     /* array string       */
    char array_name[MAX_STRING_LEN];    /* array name         */
    char array_idx[MAX_STRING_LEN];     /* array index        */

    char object_str[MAX_STRING_LEN];    /* object string       */
    char object_name[MAX_STRING_LEN];   /* object name         */
  }detail;

} BAIK_LEX;


typedef struct
{
  int pt;                   /* current position of parsing */
  int back_pt;              /* last position after parsing */
  char *source;             /* source of parsing in string */
} BAIK_ADDR;

// //////////////////////////////////////////////////////////////////////////////


// Variable Stack
typedef struct varstack_list{
  struct varstack_list *pnext;        // next pointer of List

  struct varstack_list *left;         // Tree Left
  struct varstack_list *right;        // Tree Right

  char ident[MAX_IDENT_LEN];          // ident of variable
  int  recursive_depth;               // deep in recursive function
  int  thread_id;                     // thread_id
  int  datatype;                      // data type of var

  long   val;                         // value: int or expression bool
  double floatdata;                   // valee: dbl
  char   str[MAX_STRING_LEN];         // value: str

  // ------------------------------------------------------------------------
  long   array_i;                   /* stackid for array: int               */
  long   array_d;                   /* stackid for array: double            */
  long   array_s;                   /* stackid for array: string            */

  long   array_widget;              /* stackid for array: string            */

  char   array_str[MAX_STRING_LEN], /* parsed array string all              */
         array_name[MAX_STRING_LEN/2],/* array name                           */
         array_idx[MAX_STRING_LEN/2]; /* array index                          */
  long   array_max;                 /* array member max                     */
  // ------------------------------------------------------------------------
  char   **long_str;                /* pointer string                       */
  int    isLongStr;                 /* 1 or 0  && datatype = 10             */
  // ------------------------------------------------------------------------
  char   sub_name[MAX_STRING_LEN/2],  /* function name                        */
         sub_param[MAX_STRING_LEN],   /* function                             */
         sub_file[MAX_STRING_LEN];    /* function include file                */

  int    sub_pt_start;              /* function start pos                   */
  int    sub_pt_end;                /* function stop pos       @           */
  int    sub_pt_return;             /* function return pos                  */
  
  // ------------------------------------------------------------------------
  FILE   *filedata;                 /* file                                 */
  int    isFileOpen;                /* file open stat                       */
  // ------------------------------------------------------------------------

  #ifndef S_SPLINT_S
    #ifdef WINDOWS
  SOCKET sock;
    #else
  int    sock;                      /* Socket in Unix/Linux                 */
    #endif
  #endif

  // ------------------------------------------------------------------------
  #ifdef USE_GD
  gdImagePtr gdimg;                 /* GD image                             */
  gdFontPtr  gdfont;                /* GD font                              */
  gdPoint    gdpoint;               /* GD point                             */
  #endif
  // ------------------------------------------------------------------------
  #ifdef USE_MYSQL
  MYSQL       *my_conn;             /* MYSQL_KONEKSI                        */
  MYSQL_RES   *my_res;              /* MYSQL_HASIL                          */
  MYSQL_FIELD *my_fd;               /* MYSQL_NAMAKOLOM                      */
  MYSQL_ROW   my_row;               /* MYSQL_DATABARIS                      */
  #endif
  int         isMysqlOpen;          /* mysql open stat                      */
  // ------------------------------------------------------------------------
  #ifdef USE_PGSQL
  PGconn      *pg_conn;             /* PGDB_KONEKSI                         */
  PGresult    *pg_res;              /* PGDB_HASIL                           */
  #endif
  int         isPgdbOpen;           /* PGDB open stat                       */
  // ------------------------------------------------------------------------
  #ifdef USE_OCI
  OCI_Connection *ora_conn;         /* ORADB_KONEKSI                        */
  OCI_Statement  *ora_stmt;         /* ORADB_STMT                           */
  OCI_Resultset  *ora_res;          /* ORADB_HASIL                          */
  #endif
  int            isOraOpen;         /* ORADB open stat                      */
  // ------------------------------------------------------------------------
  #ifdef USE_SQLITE
  sqlite3       *sqlite_conn;       /* SQLITE_KONEKSI                       */
  sqlite3_stmt  *sqlite_stmt;       /* SQLITE_STMT                          */
  #endif
  int         isSqliteOpen;         /* SQLITE open stat                     */
  // ------------------------------------------------------------------------
  char   sql_tmp[MAX_STRING_LEN * 2];
  // ------------------------------------------------------------------------

  char benda_name[MAX_STRING_LEN/2];  /* obj/class name                     */
  char benda_param[MAX_STRING_LEN*2]; /* obj/class params                   */

  int    benda_pt_start;              /* obj/class start pos                */
  int    benda_pt_end;                /* obj/class stop pos                 */
  int    isClassVar;                  /* 1 if variable of class             */
  int    isClassInit;                 /* class awalan , 1:init OK           */
  // ------------------------------------------------------------------------

  int    scope;                       /* param scope : local 1 /global 2    */

  // ------------------------------------------------------------------------

  #ifdef USE_GTK2
  GtkWidget            *widget;       /* any GUI component                  */
  GtkWidget            *eventbox;     /* eventbox for parent                */

  PangoFontDescription *font_desc;    /* font selected from Dialog          */

  GdkColor             color;         /* GUI Color                          */
  GdkPixbuf            *pixbuf[20];   /* GUI picture array                  */
  GtkListStore         *liststore;
  GtkEntryCompletion   *completion;
  GtkTextBuffer        *buffer;
  GtkTextIter          IterStart,
	                   IterEnd;

  GtkTreeStore         *treestore;
  GtkTreeIter          treeiter;
  GtkTreeViewColumn    *treecolumn;

  GtkClipboard         *clipboard;
  GtkCellRenderer      *renderer;

  char   tblcoltype[MAX_STRING_LEN];  /* table type                         */
  char   *str2;                       /* malloc string pointer              */

  cairo_surface_t      *cr_surface;
  cairo_t              *cr_img;
  cairo_text_extents_t cr_text_ext;
  cairo_pattern_t      *cr_pattern;

  GdkPixmap            *pixmap;

  // GTK Print (Need GTK 2.10 or above)
  GtkPrintSettings        *gtk_print_set;
  GtkPrintOperation       *gtk_print_ope;
  GtkPrintOperationResult gtk_print_res;
  PangoLayout             *pango_layout;
  #endif

  #ifdef USE_GTK3
  GtkWidget            *widget;       /* any GUI component                  */
  GtkWidget            *eventbox;     /* eventbox for parent                */

  PangoFontDescription *font_desc;    /* font selected from Dialog          */

  //GdkColor          color;         /* GUI Color                          */
  GdkRGBA             color;         /* GUI Color GTK3 Style               */

  GdkPixbuf            *pixbuf[20];   /* GUI picture array                  */
  GtkListStore         *liststore;
  GtkEntryCompletion   *completion;
  GtkTextBuffer        *buffer;
  GtkTextIter          IterStart,
	                   IterEnd;

  GtkTreeStore         *treestore;
  GtkTreeIter          treeiter;
  GtkTreeViewColumn    *treecolumn;

  GtkClipboard         *clipboard;
  GtkCellRenderer      *renderer;

  char   tblcoltype[MAX_STRING_LEN];  /* table type                         */
  char   *str2;                       /* malloc string pointer              */

  cairo_surface_t      *cr_surface;
  cairo_t              *cr_img;
  cairo_text_extents_t cr_text_ext;
  cairo_pattern_t      *cr_pattern;

  // GTK Print 
  GtkPrintSettings        *gtk_print_set;
  GtkPrintOperation       *gtk_print_ope;
  GtkPrintOperationResult gtk_print_res;
  PangoLayout             *pango_layout;
  #endif

  char   *filename;                   /* string pointer                     */
  char   *folder;                     /* string pointer                     */
  int     isGUI;                      /* is GUI component or not            */
  int     GUItype;                    /* type of GUI component              */

  // ------------------------------------------------------------------------

  #ifdef USE_PDF
  HPDF_Doc  pdf;
  HPDF_Page pdf_page;
  HPDF_Font pdf_font;
  HPDF_Image pdf_image;
  #endif

  #ifdef USE_SSL
  SSL*       ssl;
  SSL_CTX*   ssl_ctx;
  X509*      ssl_cert;
  SSL_METHOD *ssl_meth;
  #endif
  // ------------------------------------------------------------------------


} VAL_LABEL;


struct node_list{
    long   nodeid;
    char   ch;

    char   *nodeType;

    char   class_name[128];      // class name
    char   param_name[128];      // param name

    char   param_operation[512]; // param operation syntax,  e.g. a=1

    char   function_name[128];   // function name

    int    member_type;          // 1:param , 2:function

    int    scope;                // 1:Local / Global

    struct node_list *pnext;
};

struct all_class_params {
    char name[MAX_STRING_LEN][128];  // param name
    int  pos[128];                   // param pos
    int  total;                  // total num of params
};



  /* type of variableF 
        0->int, 1->double, 
        2->File, 3->String, 
        4->SocketTCP, 5->SocketUDP, 
        6->Array int, 7->Array double, 8->Array String,
        9->function, 10->pointer str,
        11->mysql_con, 12->mysql_res, 13->mysql_fd, 14->mysql_row
        20->gdImagePtr, 21->gdPoint, 22->gdFont
        30->Class Definition,31->Class Instance,32->Class function
        33->Array object                                           

		40->GTK widget

		41->KertasText
		42->FontFromDialog   // font_desc
		43->ColorFromDialog 
		44->FilenameFromDialog 
		45->Data Baris Tabel - including string and pixbuf
		46->Single Pixbuf data
		47->Kantong Teks = gtk_list_store - String List
		48->GtkEntryCompletion 
		50->GtkTextBuffer
		51->Clipboard  
		52->Kantong Angka  = gtk_list_store - Int List
		53->Kantong Gambar = gtk_list_store - Pixbuf List
		54->Kantong Teks, Angka, Gambar = gtk_list_store - String+Int+Pixbuf List
		
		55->GtkTreeIter
		56->GtkTreeStore
		57->GtkCellRenderer
		58->GtkTreeViewColumn

		60->Array GTK widget

        61->pgdb_con, 62->pgdb_res, 63->pgdb_fd, 64->pgdb_row
		70->PDF, 71->pdf_page, 72->pdf_font, 73->pdf_image
		80->cairo_img, 81->cairo_surface, 82->cairo_pattern
		83->pixmap, 84->cairo_text_extents_t

		90->print_ope, 91->pango_layout
		100->teks per baris (long_string)
  */



  // 0 Layar - window
  // 1 Alas Tetap - fixed container
  // 2 Alas Tegak - vbox container
  // 3 Tombol - Button
  // 4 Label 
  // 5 Input - masukan
  // 6 Combo Text - pilihan
  // 7 Tombol Radio
  // 8 Group Tombol Radio
  // 9 Menu Separator
  // 10 IsiMenu - MenuItem
  // 11 Expander - perinci
  // 12 Kertas - Text Area 
  // 13 SpinButton - TombolPutar
  // 14 Check Button
  // 15 data dr Font SelectionDialog (font)
  // 16 data dr Color SelectionDialog (warna)
  // 17 data dr File Dialog (filename)
  // 18 IsiMenuCek - CheckMenuItem
  // 19 Statusbar

  // 21 scrolled window

  // 21 Tabel 
  // 22 Citra - GtkImage

  // 6 MnuBar
  // 7 Menu

  // 23 Buku (Notebook)
  // 24 TreeView(Model_Ranting)
