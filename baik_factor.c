// //////////////////////////////////////////////////////////////////////
// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2016
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
#include <math.h>
#include <limits.h>
#include <errno.h>

#include "baik_word.h"
#include "baik_struct.h"
#include "val_label.h"
#include "baik_lexer.h"

extern BAIK_LEX lex;  
extern BAIK_ADDR pg;  

extern BAIK_ADDR tmp_pg;

#ifdef WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4047)
#pragma warning(disable:4024)

#include <windows.h>
#include <mmsystem.h>
#include "regex.h"
#include <direct.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")

#ifndef S_SPLINT_S
#include "haris_pingbody.h"
#endif

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <fcntl.h>
#include <regex.h>

#include <unistd.h>
#include <sys/param.h>

#include <arpa/inet.h>
#include <sys/select.h>
#include "ux_pingbody.h"

#include <dirent.h>

extern DIR *owndir;

#endif

extern char **dirtp;

#ifndef S_SPLINT_S
#include "multiplatform_struct.h"
# endif

extern char** split(const char *str, const char *delim);
extern void split_free(char **arr);

extern void chop(char* input);

extern char* createTime(void);  /* international version */
extern char* createTime2(void); /* indonesian version    */

extern int dayofweek(int year,int month,int day);
extern char *getDay();          /* international version */
extern char *getDay2();         /* indonesian version    */

extern char *createFilename(void);

extern void InterpreterSub( int endSub, char subName[MAX_STRING_LEN] );
extern void InterpreterParam( int progType, int endSub, char subName[MAX_STRING_LEN] );

extern void subtituteParam(char tmp_param[MAX_STRING_LEN*2],char get_param[MAX_STRING_LEN], char orig_param[MAX_STRING_LEN]);
extern int checkParamNum(char get_param[MAX_STRING_LEN], char orig_param[MAX_STRING_LEN]);

char idx_source[MAX_STRING_LEN];

#define MAX_SUB_DEPTH              64
extern int sub_deep;
extern int isLyrSub;
extern int isTimerSub;
extern int posSub[MAX_SUB_DEPTH]; 

/* array max length            */
#define MAX_ARRAY         99999000

extern VAL_LABEL returnVal;

extern char *tmp_source;
#include "interpretIndexParam.h"

extern char currentClass[MAX_STRING_LEN];   // current Class for Object Oriented

// --------------------------------------
// Stack for Array String
#include "stack_str_struct.h"

extern int renban;
extern long createRenban(int mynum);
extern void save_str_array(VAL_LABEL valdat, long idx, char entryVal[MAX_STRING_LEN]);

static STR_ARRY TmpStrBox;
static STR_ARRY TmpStrBox2;
static int strarryPos;

// --------------------------------------
// Stack for MySQL Array String
// Feb 11, 2016
extern STR_ARRY mysql_TmpStrBox;
extern int      mysql_strarryPos;

extern int      mysql_renban;

extern void save_mysql_str_array(VAL_LABEL valdat, long idx, char entryVal[MAX_STRING_LEN]);
extern int get_mysql_str_array(VAL_LABEL valdat, long idx, char retVal[MAX_STRING_LEN]);
// --------------------------------------
// Stack for Array Int
#include "stack_int_struct.h"

extern INT_ARRY TmpIntBox;
extern INT_ARRY TmpIntBox2;
extern int intarryPos;
// --------------------------------------
// Stack for Array Dbl
#include "stack_dbl_struct.h"

extern DBL_ARRY TmpDblBox;
extern DBL_ARRY TmpDblBox2;
extern int dblarryPos;
// --------------------------------------

extern int get_int_array(VAL_LABEL valdat, long idx);
extern void save_int_array(VAL_LABEL valdat, long idx, int val);
// --------------------------------------

extern double get_dbl_array(VAL_LABEL valdat, long idx);
extern void save_dbl_array(VAL_LABEL valdat, long idx, double dbl);
// --------------------------------------

extern int get_str_array(VAL_LABEL valdat, long idx, char retVal[MAX_STRING_LEN]);
// --------------------------------------

#ifdef USE_GTK2
extern GtkWidget *get_gui_array(VAL_LABEL valdat, long idx);
extern GtkWidget *get_eventbox_array(VAL_LABEL valdat, long idx);
extern int get_guitype_array(VAL_LABEL valdat, long idx);
extern void save_gui_array(VAL_LABEL valdat, long idx, GtkWidget *widget, GtkWidget *eventbox, int GUItype);

extern GtkPrintContext   *BAIK_Print_Context;
#endif
// --------------------------------------

#ifdef USE_GTK3
extern GtkWidget *get_gui_array(VAL_LABEL valdat, long idx);
extern GtkWidget *get_eventbox_array(VAL_LABEL valdat, long idx);
extern int get_guitype_array(VAL_LABEL valdat, long idx);
extern void save_gui_array(VAL_LABEL valdat, long idx, GtkWidget *widget, GtkWidget *eventbox, int GUItype);

extern GtkPrintContext   *BAIK_Print_Context;
#endif
// --------------------------------------

extern int class_sub_deep;
extern VAL_LABEL AddSub(void);

/* PI                   */
#define M_PI              3.14159265358979323846

/* ----------------------------------------------------------- */
/* random number */
/* ----------------------------------------------------------- */
static unsigned long seed = 1;

void init_rnd(unsigned long x);
unsigned long irnd(void);
double hhrnd(void);

/* ----------------------------------------------------------- */
/* Math : Statistic                                            */
/* ----------------------------------------------------------- */
double faktorial(int n);
double permutasi(int n, int r);
double kombinasi(int n, int r);
int faktor_gcd(int x, int y);

/* ----------------------------------------------------------- */
/* File Attribute Handle                                       */
/* ----------------------------------------------------------- */

#ifndef _MAX_PATH
#define _MAX_PATH MAX_STRING_LEN
#endif

#ifdef WINDOWS

void win_node_accesstime(char node[_MAX_PATH], char tbuf[30]);
void win_node_modifytime(char node[_MAX_PATH], char tbuf[30]);

void win_node_size(char mypath[_MAX_PATH], char tbuf[30]);
int win_node_isfile(char mypath[_MAX_PATH]);

char** win_dir_content(const char *path);
#else
char *node_accesstime(const char *node); // File last access time
char *node_modifytime(const char *node); // File last modify time
char *node_size(const char *node);       // File size
int  node_isfile(const char *node);      // isFile

char** dir_content(const char *path);
#endif

void   dir_free(char **arr);

char *Mygetcwd (char *buf, size_t size);
void printcwd (void);


extern void keySub (char ident[MAX_IDENT_LEN]);
extern void BaikGarbageCollection(void);


VAL_LABEL get_Minus_Val(void);

// ///////////////////////////////////
// GTK2
// ///////////////////////////////////
#ifdef USE_GTK2
#include <gtk/gtk.h>
#include <gtk/gtkobject.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

extern char* hhstring_add(char orig[], char addstr[]);

extern GdkPixbuf *win_create_pixbuf(const gchar * filename);
extern GtkWidget *png_label_box( GtkWidget *parent, gchar *filename, gchar *label_text );

extern int BAIK_page_nr;
#endif

// ///////////////////////////////////
// GTK3
// ///////////////////////////////////
#ifdef USE_GTK3
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include <glib.h>
#include <glib/gprintf.h>

extern char* hhstring_add(char orig[], char addstr[]);

//extern GdkPixbuf *win_create_pixbuf(const gchar * filename);
extern GtkWidget *png_label_box(GtkWidget *parent, gchar *filename, gchar *label_text);

extern int BAIK_page_nr;
#endif

#ifdef USE_CGI
/* ----------------------------------------------------------- */
/* Web Html CGI POST Handle                                    */
/* ----------------------------------------------------------- */

/* HTML parse             */
#define MAX_WEBINPUT_LEN  4096
#define getenv1(a) ((pdata=getenv(a)) ? pdata : "(NULL)")

int parse_webform(char* s_in,long maxl,char* name[MAX_STRING_LEN],char* value[MAX_STRING_LEN],int *p_nfld);
int decode_webform(char* s,long len);

char *web_inputstring=NULL,
     *web_agent=NULL,
     *web_cLength=NULL,
     *web_name[MAX_WEBINPUT_LEN],
     *web_value[MAX_WEBINPUT_LEN];
int  web_nfield=0;
long web_i,
     web_length,
     WEBMAXLEN   = 4096;

void getPostCgi(void);
char *getPostName(int i);
char *getPostVal(int i);

int base64(char *data,int size,char *into);
int outchar(int *n, char **ptr, char c);
char b64_charconv(char c);
void b64_decode(char *lpszStr, char *lpszResult);

#include "cgi/baik_cgi.h"
#endif

#include "FactorIdent.h"

// /////////////////////////////////////////////////////////////////////////////////
VAL_LABEL Factor()
{
  VAL_LABEL tmpdat;       // for return value
  VAL_LABEL datx, valdat;
  long idx=0;
  char ident[MAX_IDENT_LEN];
  char class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&ident, '\0', sizeof(ident));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&idx_source, '\0', sizeof(idx_source));

  // printf ("  Factor() \n");

  getlex();

  switch( lex.type )
    {
    case TYPE_IDENT:
      //printf(" expression look for ident: %s\n", lex.detail.ident);
      tmpdat = FactorIdent( lex.detail.ident );
      break;
      
    case TYPE_NUM:
      /* printf("Factor NUM\n"); */
      memset(&tmpdat, '\0', sizeof(tmpdat));
      tmpdat.val = lex.detail.num;
      tmpdat.datatype = 0;
      break;

    case TYPE_DBL:
      /* printf("Factor DBL\n"); */
      memset(&tmpdat, '\0', sizeof(tmpdat));
      if(lex.detail.dblnum != '\0')
        tmpdat.floatdata = lex.detail.dblnum;
      else
        tmpdat.floatdata = 0.0;
      tmpdat.datatype = 1;
      break;

    case TYPE_STR:
      memset(&tmpdat, '\0', sizeof(tmpdat));
      strcpy(tmpdat.str, lex.detail.string);
      tmpdat.datatype = 3;
      break;

    case TYPE_ARRAY:
        //printf("Factor ARRAY\n"); 

        strcpy(tmpdat.array_str, lex.detail.array_str);

        getArrayName(lex.detail.array_str, (char *)&tmpdat.array_name);
        getArrayIdx(lex.detail.array_str, (char *)&tmpdat.array_idx);

        if(strlen(lex.detail.array_str) > 0) {
          strcpy(valdat.array_str, lex.detail.array_str);
          getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
          getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

           if(currentClass != NULL && strlen(currentClass) > 0) {
              sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_name);
              //printf("construct class var: %s\n", class_tmpvar);
              memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));
              strcpy(valdat.array_name, class_tmpvar);
           }

           // printf("factor ARRAY name: %s\n", valdat.array_name);

	      // printf("factor array_idx: %s\n", valdat.array_idx);

          if(isdigit(valdat.array_idx[0])) {
            /* printf("show digit\n"); */
            idx = atol (valdat.array_idx);
          } else {
            /* printf("show NOT digit\n"); */
            /* Read index param */

            // datx = ValLabel( valdat.array_idx, sub_deep, datx, VAL_FLAG_SEARCH_R );
			 memset(&idx_source, '\0', sizeof(idx_source));
			 strcpy(idx_source, "{ ");
			 strcat(idx_source, valdat.array_idx);
			 strcat(idx_source, " }");
			  
			 datx = interpretIndexParam(idx_source, pg.pt, pg.back_pt, currentClass);

            if(datx.datatype==0)
              idx = datx.val;
            else if(datx.datatype==1)
		      idx = (int)abs(datx.floatdata);
            else
              Error("Untaian salah masukan");
          }

          /* Read Data */
          valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
          sprintf(valdat.array_idx, "%li", idx);
          // ltoa(idx, valdat.array_idx, 10);

          if(idx < 0 || idx > MAX_ARRAY)
            Error("ukuran Untaian tidak sesuai kapasitas");

		  // printf("get array type %d\n", valdat.datatype); 

          if(valdat.datatype == 6) {
            tmpdat.val = get_int_array(valdat, idx);
            tmpdat.datatype = 0;
          }
          else
          if(valdat.datatype == 7) {
            tmpdat.floatdata = get_dbl_array(valdat, idx);
            tmpdat.datatype  = 1;
          }
          else
          if(valdat.datatype == 8) {
		    // Array String
            memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
			memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

			strcpy(TmpStrBox.var.array_name, valdat.array_name);
            renban = valdat.array_s;

		    if(renban < 0) {
              printf("variabel untaian tidak ditemukan\n");
			} else {
              TmpStrBox.str.stackid = renban;
              TmpStrBox.str.idx = idx;

			  strarryPos = string_findData(TmpStrBox.str);
			  if(strarryPos < 0) {
  			    // printf("\n! nilai untaian kata tidak ditemukan");
			  } else {
                TmpStrBox.str = string_getElement(strarryPos);
 			    strcpy(tmpdat.str , TmpStrBox.str.mystring);
			  }

			}

			tmpdat.datatype = 3;

		  }

          #ifdef USE_GTK2
          else
          if(valdat.datatype == 60) {
		    // printf("got factor GUI array \n");
			tmpdat.widget   = get_gui_array(valdat, idx);
			tmpdat.GUItype  = get_guitype_array(valdat, idx);
			tmpdat.eventbox = get_eventbox_array(valdat, idx);
            tmpdat.datatype = 40;
          }
          #endif

          else
          if(valdat.datatype == 10) {
            strcpy(tmpdat.str , valdat.long_str[idx]);
            tmpdat.datatype = 3;

          } else {
            /* printf("JUST substitution\n"); */
            tmpdat = valdat;
          }

        }

      break;
      
    case TYPE_OBJECT:
        
        // printf("\nFactor get OBJECT\n");
        // printf(" Factor lex str : %s\n", lex.detail.object_str);
        
        checkInstanceValidation(lex.detail.object_str);

        /* read data */
		memset(&valdat, '\0', sizeof(valdat));
		valdat.datatype = -1;
		valdat.val = -1;
        valdat = ValLabel( lex.detail.object_str, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
        
        // printf(" Factor get datatype %d\n", valdat.datatype);
        // printf(" Factor get val %d\n", valdat.val);
        // printf(" Factor get benda_param : %s\n", valdat.benda_param);
        // printf(" Factor get isClassVar : %d\n", valdat.isClassVar);
        

        strcpy(tmpdat.benda_param, valdat.benda_param);
		tmpdat.isClassVar = valdat.isClassVar;

        if(valdat.datatype == 0) {
          tmpdat.val = valdat.val;
          tmpdat.datatype = 0;
        }
        else
        if(valdat.datatype == 1) {
          tmpdat.floatdata = valdat.floatdata;
          tmpdat.datatype  = 1;
        }
        else
        if(valdat.datatype == 3) {
          strcpy(tmpdat.str , valdat.str);
          tmpdat.datatype = 3;
        }
        else
        if(valdat.datatype == 6) {
			datx.val = get_int_array(valdat, idx);
            tmpdat.datatype = 0;
        }
        else
        if(valdat.datatype == 7) {
            datx.floatdata = get_dbl_array(valdat, idx);
            tmpdat.datatype  = 1;
        }
        else
        if(valdat.datatype == 8) {
            memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
			memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

			strcpy(TmpStrBox.var.array_name, valdat.array_name);
            renban = valdat.array_s;

	        if(renban < 0) {
              printf("variabel untaian tidak ditemukan\n");
			} else {
              TmpStrBox.str.stackid = renban;
              TmpStrBox.str.idx = idx;

			  strarryPos = string_findData(TmpStrBox.str);
			  if(strarryPos < 0) {
  			    // printf("\n! nilai untaian kata tidak ditemukan");
			  } else {
                TmpStrBox.str = string_getElement(strarryPos);
 			    strcpy(tmpdat.str , TmpStrBox.str.mystring);
			  }
			}

            tmpdat.datatype = 3;
        }
        else
        if(valdat.datatype == 10) {
            strcpy(tmpdat.str , valdat.long_str[idx]);
            tmpdat.datatype = 3;

        } else {
            /* printf("JUST substitution\n"); */
            tmpdat = valdat;
        }

      break;

    case TYPE_SYM:
      if( lex.detail.symbol == '(' ){

	    tmpdat = expression();

	    getlex();
	    if ( lex.detail.symbol != ')' )
	      Error("tidak ada tanda penutup ')'");
      }
	  else
      /* ******************* minus number ********************  */
      if( lex.detail.symbol == '-' )  {
        // printf("minus number\n"); 

        getlex();

        if(lex.type == TYPE_NUM) {

          lex.detail.num = 0 - lex.detail.num;

          datx.val      = lex.detail.num;
          datx.datatype = 0;

        } else if(lex.type == TYPE_DBL) {

          lex.detail.dblnum =  0.0 - lex.detail.dblnum;

          datx.floatdata = lex.detail.dblnum;
          datx.datatype  = 1;

        } else {
          Error("Salah bentuk bilangan negatif");
        }

      } 
	  //else
      /* *******************   call function ********************  */
      //if( lex.detail.symbol == '&' )  {
      //  /* printf("subroutine\n");                                 */
	  //    strcpy( ident, "");
	  //	  // sub routine
      //     keySub(ident);
	  //}
      break;
      
    default:
      Error("Label/Variabel: Salah tata kalimat");
    }


  // printf("return factor type %d\n", tmpdat.datatype); 

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  if(datx.left != NULL)
    free(datx.left);
  if(datx.right != NULL)
    free(datx.right);
  if(datx.pnext != NULL)
    free(datx.pnext);

  return tmpdat;
}


VAL_LABEL get_Minus_Val() {
  VAL_LABEL datx,             // ret value
	    valdat, tmpdat;
  int idx=0;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  getlex();

  switch( lex.type )
  {
	 case TYPE_NUM:
	  datx.val =  0 - lex.detail.num;                         // minus
	  datx.datatype = 0;
     break; 

	 case TYPE_DBL:
	  datx.floatdata =  0.0 - lex.detail.dblnum;             // minus
	  datx.datatype = 1;
     break; 

	 case TYPE_OBJECT:
       checkObjectValidation(lex.detail.object_str);
	 case TYPE_IDENT:
 	   if(currentClass != NULL && strlen(currentClass) > 0) {
         sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
         //printf("construct class var: %s\n", class_tmpvar);
         valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
       } else {
         valdat = ValLabel( lex.detail.string, sub_deep, valdat, VAL_FLAG_SEARCH_R );
       }

       if(valdat.datatype == 0) {
		 datx.val =  0 - valdat.val;                      // minus
	     datx.datatype = 0;
	   } else 
       if(valdat.datatype == 1) {
		 datx.floatdata =  0.0 - valdat.floatdata;        // minus
	     datx.datatype = 1;
	   } else {
         Error("salah bilangan minus");
	   }
     break; 

     case TYPE_ARRAY:
       if(strlen(lex.detail.array_str) > 0) {
         strcpy(valdat.array_str, lex.detail.array_str);
         getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
         getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

         if(isdigit(valdat.array_idx[0])) {
           /* printf("show digit\n"); */
           idx = atol (valdat.array_idx);
         } else {
           /* printf("show NOT digit\n"); */
           /* Read index param */
            tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
            if(tmpdat.datatype==0)
              idx = tmpdat.val;
            else
               Error("Untaian salah masukan");
         }

         valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
         sprintf(valdat.array_idx, "%d", idx);

         if(idx < 0 || idx > (valdat.array_max-1))
            Error("ukuran Untaian tidak sesuai kapasitas");

         if(valdat.datatype == 6) {
            datx.val = 0 - get_int_array(valdat, idx);           // minus
            datx.datatype = 0;
		 } else
         if(valdat.datatype == 7) {
			datx.floatdata = 0.0 - get_dbl_array(valdat, idx);   // minus
            datx.datatype = 1;
		 } else {
            Error("salah bilangan minus");
		 }

	   }
     break;

	 default:
	   Error("salah bentuk bilangan minus");

  }

  // printf("get minus type %d , val %d \n", datx.datatype, datx.val);


  if(valdat.filedata != NULL)
    free(valdat.filedata);
  if(valdat.long_str != NULL)
    free(valdat.long_str);

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  if(tmpdat.filename != NULL)
    free(tmpdat.filename);
  if(tmpdat.folder != NULL)
    free(tmpdat.folder);
  if(tmpdat.filedata != NULL)
    free(tmpdat.filedata);
  if(tmpdat.long_str != NULL)
    free(tmpdat.long_str);

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

  return datx;

}