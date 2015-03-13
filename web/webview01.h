// //////////////////////////////////////////////////////////////////////
// Web MVC View Parser - BAIK
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


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


#define MAX_STRING_LEN  300


enum
{
  _MVCEND,          //00
  _MVCLABEL,        //01

  _MVC_TULIS,       //02
  _MVC_UNTUK,       //03  
  _MVC_ULANG,       //04    
  _MVC_LAGI,        //05      
  
  _MVC_START,       //06
  _MVC_STOP,        //07

  _MVC_AND,         //08 
  _MVC_OR,          //09
  _MVC_NOT,         //10

  _MVC_EOF,         //11
  
  _MVC_UNTAI,       //12  

  TYPE_MVC_NUM,     //13
  TYPE_MVC_DBL,     //14
  TYPE_MVC_IDENT,   //15 
  TYPE_MVC_STR,     //16
  TYPE_MVC_SYM,     //17
  TYPE_MVC_ARRAY,   //18

  TYPE_MVC_HTMLTAG, //19

  MVC_VAL_FLAG_START,     
  MVC_VAL_FLAG_SEARCH_R,  
  MVC_VAL_FLAG_SEARCH_W,  
  MVC_VAL_FLAG_END
};


typedef struct
{
  int type;

  union{
    long num;                     
    double dblnum;

    char ident[MAX_IDENT_LEN];   
    char string[MAX_STRING_LEN];
    char symbol;              
    
    char array_str[MAX_STRING_LEN];     /* array string       */
    char array_name[MAX_STRING_LEN];    /* array name         */
    char array_idx[MAX_STRING_LEN];     /* array index        */    
    
  }detail;

} MVC_LEX_T;

typedef struct
{
  int pt;      
  int back_pt;  
  char *source;  
} MVC_S_ADDR;


typedef struct _MVC_val_label
{
  struct _MVC_val_label *left;  
  struct _MVC_val_label *right;

  char ident[MAX_IDENT_LEN]; 
  int data;                 

} MVC_VAL_LABEL;

typedef struct
{

  MVC_LEX_T mvc_lex; 
  MVC_S_ADDR mvc_pg;  
  char c;

  int  datatype;                       // data type of var

  long   val;                          // value: int or expression bool
  double floatdata;                    // valee: dbl
  char   str[MAX_STRING_LEN];          // value: str

  long   array_i;                      /* stackid for array: int               */
  long   array_d;                      /* stackid for array: double            */
  long   array_s;                      /* stackid for array: string            */

  long   array_widget;                 /* stackid for array: string            */

  char   array_str[MAX_STRING_LEN],    /* parsed array string all              */
         array_name[MAX_STRING_LEN/2], /* array name                           */
         array_idx[MAX_STRING_LEN/2];  /* array index                          */
  long   array_max;                    /* array member max                     */

  char   **long_str;                   /* pointer string                       */
  int    isLongStr;                    /* 1 or 0  && datatype = 10             */

} MVCPARSING;

