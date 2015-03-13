// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia



#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/stat.h>
#include <math.h>

#include "baik_word.h"
#include "baik_struct.h"
#include "val_label.h"
#include "baik_lexer.h"

extern BAIK_LEX lex;  
extern BAIK_ADDR pg;  

extern BAIK_ADDR tmp_pg;  

// ..............................................................
#define MAX_LOOP_LEN     1024
extern int loop_flag;

extern void InterpreterForInitIncr(void);
extern void InterpreterForIncr( int endPos );

extern int interpretForCondition(char *src, int tmp_pt, int back_pt);
extern int posForStart[MAX_LOOP_LEN];
extern int backForStart[MAX_LOOP_LEN];
extern int posForTemp[MAX_LOOP_LEN];
extern int backForTemp[MAX_LOOP_LEN];
extern int statFor[MAX_LOOP_LEN];

// ..............................................................
extern int forExecDone[MAX_LOOP_LEN];     // 0->notyet , 1->done */
extern int f_deep;                        // loop to check untuk depth */
extern char forInitSource[MAX_LOOP_LEN][MAX_STRING_LEN],
       forConditSource[MAX_LOOP_LEN][MAX_STRING_LEN],
       forPlusSource[MAX_LOOP_LEN][MAX_STRING_LEN];
// ..............................................................


extern void InterpreterSub( int endSub, char subName[MAX_STRING_LEN] );
extern void InterpreterParam( int progType, int endSub, char subName[MAX_STRING_LEN] );

extern void subtituteParam(char tmp_param[MAX_STRING_LEN*2],char get_param[MAX_STRING_LEN], char orig_param[MAX_STRING_LEN]);
extern int checkParamNum(char get_param[MAX_STRING_LEN], char orig_param[MAX_STRING_LEN]);

#define MAX_SUB_DEPTH              64
extern int sub_deep;
extern int isLyrSub;
extern int isTimerSub;
extern int posSub[MAX_SUB_DEPTH]; 

/* array max length            */
#define MAX_ARRAY         99999000

extern VAL_LABEL returnVal;

extern char *tmp_source;

extern char currentClass[MAX_STRING_LEN];   // current Class for Object Oriented

// --------------------------------------
// Stack for Array String
#include "stack_str_struct.h"

extern int renban;
extern STR_ARRY TmpStrBox;
extern STR_ARRY TmpStrBox2;
extern int strarryPos;
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

extern int get_int_array(VAL_LABEL valdat, int idx);
extern void save_int_array(VAL_LABEL valdat, int idx, int val);
// --------------------------------------

extern double get_dbl_array(VAL_LABEL valdat, int idx);
extern void save_dbl_array(VAL_LABEL valdat, int idx, double dbl);
// --------------------------------------

extern VAL_LABEL Compare(void);
extern VAL_LABEL Factor(void);

#ifdef WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#endif

VAL_LABEL expression()
{
  return ( AndOr() );
}


VAL_LABEL AndOr()
{
  VAL_LABEL dat, tmp;

  memset(&dat, '\0', sizeof(dat));
  memset(&tmp, '\0', sizeof(tmp));

  //printf("Inside AndOr : Before NotFunc\n");

  dat.val=0; tmp.val=0;
  dat = NotFunc();

  //printf("Inside AndOr : After NotFunc\n");

  getlex();
  if( lex.type == _EOF )
    Error("AndOr: Program berhenti diluar perkiraan");

  while ( lex.type == _ATAU || lex.type == _DAN ){

    switch( lex.type )
      {
      case _DAN:
        tmp = NotFunc();
	    dat.val = ( dat.val && tmp.val ) ? 1 : 0;
	break;
      case _ATAU:
        tmp = NotFunc();
	    dat.val = ( dat.val || tmp.val ) ? 1 : 0;
	break;
      }

    getlex();
  }

  ungetlex();

  // printf("AndOr val %d\n", dat.val);
  // printf("AndOr str %s\n", dat.str);

  return dat;
}


VAL_LABEL NotFunc()
{
  VAL_LABEL datx, tmp;

  memset(&datx, '\0', sizeof(datx));
  memset(&tmp, '\0', sizeof(tmp));

  datx.val=0; tmp.val=0;

  //printf("inside NotFunc...\n");

  getlex();
  if( lex.type == _EOF )
    Error("NotFunc: Program berhenti diluar perkiraan");

  if( lex.type != _NOT ){
    // printf("NotFunc 1 val %d\n", tmp.val);

    ungetlex();
    tmp = Compare();

    // printf("NotFunc 2 val %d\n", tmp.val);
    // printf("NotFunc str %s\n", tmp.str);

    return ( tmp );
  }

  //printf("Before Compare NotFunc datx_val %d\n", datx.val);

  tmp = Compare();
  datx.val = ( ( tmp.val != 0 ) ? 0 : 1 );

  //printf("After Compare NotFunc datx_val %d\n" , datx.val);

  if(tmp.left != NULL)
    free(tmp.left);
  if(tmp.right != NULL)
    free(tmp.right);
  if(tmp.pnext != NULL)
    free(tmp.pnext);

  //printf("Return NotFunc datx_val %d\n", datx.val);

  return datx;
}


VAL_LABEL AddSub()
{
  VAL_LABEL datx = MultiDiv();
  VAL_LABEL datz;

  int tmp_ai = 0;      // array int
  double tmp_ad = 0.0; // array dbl

  int tmp_i  = 0;       // int
  int tmp_ai2 = 0;      // array int
  double tmp_d   = 0.0; // dbl
  double tmp_ad2 = 0.0; // array dbl

  char symbol = '\0';

  long idx=0, idx2=0;
  memset(&datz, '\0', sizeof(datz));

  //ap_rputs(" == AddSub getlex() <BR>", web_r);
  getlex();
  symbol = lex.detail.symbol;

  if( lex.type == _EOF ) {

  if(datz.right->filename != NULL)
    free(datz.right->filename);
  if(datz.right->folder != NULL)
    free(datz.right->folder);
  if(datz.right->filedata != NULL)
    free(datz.right->filedata);
  if(datz.right->long_str != NULL)
    free(datz.right->long_str);

  if(datz.left->filename != NULL)
    free(datz.left->filename);
  if(datz.left->folder != NULL)
    free(datz.left->folder);
  if(datz.left->filedata != NULL)
    free(datz.left->filedata);
  if(datz.left->long_str != NULL)
    free(datz.left->long_str);

  if(datz.pnext->filename != NULL)
    free(datz.pnext->filename);
  if(datz.pnext->folder != NULL)
    free(datz.pnext->folder);
  if(datz.pnext->filedata != NULL)
    free(datz.pnext->filedata);
  if(datz.pnext->long_str != NULL)
    free(datz.pnext->long_str);

  if(datz.right->right != NULL)
    free(datz.right->right);
  if(datz.right->left != NULL)
    free(datz.right->left);
  if(datz.right->pnext != NULL)
    free(datz.right->pnext);

  if(datz.left->right != NULL)
    free(datz.left->right);
  if(datz.left->left != NULL)
    free(datz.left->left);
  if(datz.left->pnext != NULL)
    free(datz.left->pnext);

  if(datz.pnext->right != NULL)
    free(datz.pnext->right);
  if(datz.pnext->left != NULL)
    free(datz.pnext->left);
  if(datz.pnext->pnext != NULL)
    free(datz.pnext->pnext);

  if(datz.filename != NULL)
    free(datz.filename);
  if(datz.folder != NULL)
    free(datz.folder);
  if(datz.filedata != NULL)
    free(datz.filedata);

  if(datz.left != NULL)
    free(datz.left);
  if(datz.right != NULL)
    free(datz.right);
  if(datz.pnext != NULL)
    free(datz.pnext);

   return datx;
  }

  if(datx.datatype == 6 || datx.datatype == 7) {
    idx = atoi(datx.array_idx);
    tmp_ai = get_int_array(datx, idx);
    tmp_ad = get_dbl_array(datx, idx);
  }

  
  //ap_rputs(" == AddSub after getlex() <BR>", web_r);

  while( lex.type == TYPE_SYM && 
	 ( lex.detail.symbol == '+' ||
	   lex.detail.symbol == '-' ) ){

    memset(&datz, '\0', sizeof(datz));
    datz = MultiDiv();
    tmp_i = datz.val;
    tmp_d = datz.floatdata;
    if(datz.datatype == 6 || datz.datatype == 7) {
      idx2 = atoi(datz.array_idx);
      tmp_ai2 = get_int_array(datz, idx2);
      tmp_ad2 = get_dbl_array(datz, idx2);
    }

    switch( symbol )
      {
      case '+':
        if(datx.datatype == 0) {

          if(datz.datatype == 0) {
            // ap_rputs(" datx 0 datz 0 <BR>\n", web_r);
            datx.val = datx.val + tmp_i;
            datx.datatype = 0;
          } else if(datz.datatype == 1) {
            // ap_rputs(" datx 0 datz 1 <BR>\n", web_r);
            datx.floatdata = (double)datx.val + tmp_d;
            datx.datatype = 1;
          } else if(datz.datatype == 6) {
            datx.val = datx.val + tmp_ai2;
            datx.datatype = 0;
          } else if(datz.datatype == 7) {
            datx.floatdata = (double)datx.val + tmp_ad2;
            datx.datatype = 1;
          }

        } else
        if(datx.datatype == 1) {

          if(datz.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            datx.floatdata = datx.floatdata + (double)tmp_i;
            datx.datatype = 1;
          } else if(datz.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            datx.floatdata = datx.floatdata + tmp_d;
            datx.datatype = 1;
          } else if(datz.datatype == 6) {
            datx.floatdata = datx.floatdata + (double)tmp_ai2;
            datx.datatype = 1;
          } else if(datz.datatype == 7) {
            datx.floatdata = datx.floatdata + tmp_ad2;
            datx.datatype = 1;
          }

        } else
        if(datx.datatype == 6) {

          if(datz.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            datx.floatdata = (double)tmp_ai + (double)tmp_i;
            datx.datatype = 0;
          } else if(datz.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            datx.floatdata = (double)tmp_ai + tmp_d;
            datx.datatype = 1;
          } else if(datz.datatype == 6) {
            datx.floatdata = (double)tmp_ai + (double)tmp_ai2;
            datx.datatype = 0;
          } else if(datz.datatype == 7) {
            datx.floatdata = (double)tmp_ai + tmp_ad2;
            datx.datatype = 1;
          }

        } else
        if(datx.datatype == 7) {

          if(datz.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            datx.floatdata = tmp_ad + (double)tmp_i;
            datx.datatype = 1;
          } else if(datz.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            datx.floatdata = tmp_ad + tmp_d;
            datx.datatype = 1;
          } else if(datz.datatype == 6) {
            datx.floatdata = tmp_ad + (double)tmp_ai2;
            datx.datatype = 1;
          } else if(datz.datatype == 7) {
            datx.floatdata = tmp_ad + tmp_ad2;
            datx.datatype = 1;
          }

        } else {
          Error("salah dalam penjumlahan");
        }

	break;
	
      case '-':
        if(datx.datatype == 0) {

          if(datz.datatype == 0) {
            // ap_rputs(" datx 0 datz 0 <BR>\n", web_r);
            datx.val = datx.val - tmp_i;
            datx.datatype = 0;
          } else if(datz.datatype == 1) {
            // ap_rputs(" datx 0 datz 1 <BR>\n", web_r);
            datx.floatdata = (double)datx.val - tmp_d;
            datx.datatype = 1;
          } else if(datz.datatype == 6) {
            datx.val = datx.val - tmp_ai2;
            datx.datatype = 0;
          } else if(datz.datatype == 7) {
            datx.floatdata = (double)datx.val - tmp_ad2;
            datx.datatype = 1;
          }

        } else
        if(datx.datatype == 1) {

          if(datz.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            datx.floatdata = datx.floatdata - (double)tmp_i;
            datx.datatype = 1;
          } else if(datz.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            datx.floatdata = datx.floatdata - tmp_d;
            datx.datatype = 1;
          } else if(datz.datatype == 6) {
            datx.floatdata = datx.floatdata - (double)tmp_ai2;
            datx.datatype = 1;
          } else if(datz.datatype == 7) {
            datx.floatdata = datx.floatdata - tmp_ad2;
            datx.datatype = 1;
          }

        } else
        if(datx.datatype == 6) {

          if(datz.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            datx.floatdata = (double)tmp_ai - (double)tmp_i;
            datx.datatype = 0;
          } else if(datz.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            datx.floatdata = (double)tmp_ai - tmp_d;
            datx.datatype = 1;
          } else if(datz.datatype == 6) {
            datx.floatdata = (double)tmp_ai - (double)tmp_ai2;
            datx.datatype = 0;
          } else if(datz.datatype == 7) {
            datx.floatdata = (double)tmp_ai - tmp_ad2;
            datx.datatype = 1;
          }

        } else
        if(datx.datatype == 7) {

          if(datz.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            datx.floatdata = tmp_ad - (double)tmp_i;
            datx.datatype = 1;
          } else if(datz.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            datx.floatdata = tmp_ad - tmp_d;
            datx.datatype = 1;
          } else if(datz.datatype == 6) {
            datx.floatdata = tmp_ad - (double)tmp_ai2;
            datx.datatype = 1;
          } else if(datz.datatype == 7) {
            datx.floatdata = tmp_ad - tmp_ad2;
            datx.datatype = 1;
          }

        } else {
          Error("salah dalam pengurangan");
        }


	break;
      }

    getlex();
    symbol = lex.detail.symbol;
  }

  ungetlex();


  if(datz.filename != NULL)
    free(datz.filename);
  if(datz.folder != NULL)
    free(datz.folder);
  if(datz.filedata != NULL)
    free(datz.filedata);

  if(datz.left != NULL)
    free(datz.left);
  if(datz.right != NULL)
    free(datz.right);
  if(datz.pnext != NULL)
    free(datz.pnext);


  return datx;
}




VAL_LABEL MultiDiv()
{
  VAL_LABEL datx = Factor();
  VAL_LABEL daty = datx;

  int tmp_ai = 0;      // array int
  double tmp_ad = 0.0; // array dbl

  int tmp_i  = 0;       // int
  int tmp_ai2 = 0;      // array int
  double tmp_d   = 0.0; // dbl
  double tmp_ad2 = 0.0; // array dbl

  double dblNol = 0.0;

  char symbol = '\0';

  long idx=0, idx2=0;

  //ap_rputs(" == MultiDiv getlex() <BR>", web_r);
  getlex();
  symbol = lex.detail.symbol;

  if( lex.type == _EOF )
    return datx;

  if(datx.datatype == 6 || datx.datatype == 7) {
    idx = atoi(datx.array_idx);
    tmp_ai = get_int_array(datx, idx);
    tmp_ad = get_dbl_array(datx, idx);
  }

  //ap_rputs(" == MultiDiv after getlex() <BR>", web_r);

  while( lex.type == TYPE_SYM && 
	 ( lex.detail.symbol == '*' ||
	   lex.detail.symbol == '/' ||
	   lex.detail.symbol == '%' ) ){
    
    memset(&datx, 0, sizeof(datx));
    datx = Factor();

    tmp_i = datx.val;
    tmp_d = datx.floatdata;
    if(datx.datatype == 6 || datx.datatype == 7) {
      idx2 = atoi(datx.array_idx);
      tmp_ai2 = get_int_array(datx, idx2);
      tmp_ad2 = get_dbl_array(datx, idx2);
    }

    switch( symbol )
      {
      case '*':
        if(daty.datatype == 0) {

          if(datx.datatype == 0) {
            // ap_rputs(" daty 0 datx 0 <BR>\n", web_r);
            daty.val = daty.val * tmp_i;
            daty.datatype = 0;
          } else if(datx.datatype == 1) {
            // ap_rputs(" daty 0 datx 1 <BR>\n", web_r);
            daty.floatdata = (double)daty.val * tmp_d;
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            daty.val = daty.val * tmp_ai2;
            daty.datatype = 0;
          } else if(datx.datatype == 7) {
            daty.floatdata = (double)daty.val * tmp_ad2;
            daty.datatype = 1;
          }

        } else
        if(daty.datatype == 1) {

          if(datx.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.floatdata = daty.floatdata * (double)tmp_i;
            daty.datatype = 1;
          } else if(datx.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.floatdata = daty.floatdata * tmp_d;
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            daty.floatdata = daty.floatdata * (double)tmp_ai2;
            daty.datatype = 1;
          } else if(datx.datatype == 7) {
            daty.floatdata = datx.floatdata * tmp_ad2;
            daty.datatype = 1;
          }

        } else
        if(daty.datatype == 6) {

          if(datx.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.val = tmp_ai * tmp_i;
            daty.datatype = 0;
          } else if(datx.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.floatdata = (double)tmp_ai * tmp_d;
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            daty.val = tmp_ai * tmp_ai2;
            daty.datatype = 0;
          } else if(datx.datatype == 7) {
            daty.floatdata = (double)tmp_ai * tmp_ad2;
            daty.datatype = 1;
          }

        } else
        if(daty.datatype == 7) {

          if(datx.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.floatdata = tmp_ad * (double)tmp_i;
            daty.datatype = 1;
          } else if(datx.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.floatdata = tmp_ad * tmp_d;
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            daty.floatdata = tmp_ad * (double)tmp_ai2;
            daty.datatype = 1;
          } else if(datx.datatype == 7) {
            daty.floatdata = tmp_ad * tmp_ad2;
            daty.datatype = 1;
          }

        } else {
          Error("salah dalam perkalian");
        }

	break;
	
      case '/':
        if(daty.datatype == 0) {

          if(datx.datatype == 0) {
            if( tmp_i == 0 )
              Error("Dibagi dengan Nol");
            daty.floatdata = (double)daty.val / (double)tmp_i;
            daty.datatype = 1;
          } else if(datx.datatype == 1) {
            if( tmp_d == dblNol )
              Error("Dibagi dengan Nol");
            // ap_rputs(" daty 0 datx 1 <BR>\n", web_r);
            daty.floatdata = (double)daty.val / tmp_d;
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            if( tmp_ai == 0 )
              Error("Dibagi dengan Nol");
            daty.floatdata = (double)daty.val / (double)tmp_ai2;
            daty.datatype = 1;
          } else if(datx.datatype == 7) {
            if( tmp_ad2 == dblNol )
              Error("Dibagi dengan Nol");
            daty.floatdata = (double)daty.val / tmp_ad2;
            daty.datatype = 1;
          }

        } else
        if(daty.datatype == 1) {

          if(datx.datatype == 0) {
            if( tmp_i == 0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.floatdata = daty.floatdata / (double)tmp_i;
            daty.datatype = 1;
          } else if(datx.datatype == 1) {
            if( tmp_d == dblNol )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.floatdata = daty.floatdata / tmp_d;
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            if( tmp_ai2 == 0 )
              Error("Dibagi dengan Nol");
            daty.floatdata = daty.floatdata / (double)tmp_ai2;
            daty.datatype = 1;
          } else if(datx.datatype == 7) {
            if( tmp_ad2 == dblNol )
              Error("Dibagi dengan Nol");
            daty.floatdata = datx.floatdata / tmp_ad2;
            daty.datatype = 1;
          }

        } else
        if(daty.datatype == 6) {

          if(datx.datatype == 0) {
            if( tmp_i == 0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.floatdata = (double)tmp_ai / (double)tmp_i;
            daty.datatype = 1;
          } else if(datx.datatype == 1) {
            if( tmp_d == dblNol )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.floatdata = (double)tmp_ai / tmp_d;
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            if( tmp_ai2 == 0 )
              Error("Dibagi dengan Nol");
            daty.floatdata = (double)tmp_ai / (double)tmp_ai2;
            daty.datatype = 1;
          } else if(datx.datatype == 7) {
            if( tmp_ad2 == dblNol )
              Error("Dibagi dengan Nol");
            daty.floatdata = (double)tmp_ai / tmp_ad2;
            daty.datatype = 1;
          }

        } else
        if(daty.datatype == 7) {

          if(datx.datatype == 0) {
            if( tmp_i == 0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.floatdata = tmp_ad / (double)tmp_i;
            daty.datatype = 1;
          } else if(datx.datatype == 1) {
            if( tmp_d == dblNol )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.floatdata = tmp_ad / tmp_d;
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            if( tmp_ai2 == 0 )
              Error("Dibagi dengan Nol");
            daty.floatdata = tmp_ad / (double)tmp_ai2;
            daty.datatype = 1;
          } else if(datx.datatype == 7) {
            if( tmp_ad2 == dblNol )
              Error("Dibagi dengan Nol");
            daty.floatdata = tmp_ad / tmp_ad2;
            daty.datatype = 1;
          }

        } else {
          Error("salah dalam pembagian");
        }

	break;
	

      case '^':
        if(daty.datatype == 0) {

          if(datx.datatype == 0) {
            // ap_rputs(" daty 0 datx 0 <BR>\n", web_r);
            daty.val = (int)pow((double)daty.val , (double)tmp_i);
            daty.datatype = 0;
          } else if(datx.datatype == 1) {
            // ap_rputs(" daty 0 datx 1 <BR>\n", web_r);
            daty.floatdata = pow((double)daty.val , tmp_d);
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            daty.val = (int)pow((double)daty.val , (double)tmp_ai2);
            daty.datatype = 0;
          } else if(datx.datatype == 7) {
            daty.floatdata = pow((double)daty.val , tmp_ad2);
            daty.datatype = 1;
          }

        } else
        if(daty.datatype == 1) {

          if(datx.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.floatdata = pow(daty.floatdata , (double)tmp_i);
            daty.datatype = 1;
          } else if(datx.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.floatdata = pow(daty.floatdata , tmp_d);
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            daty.floatdata = pow(daty.floatdata , (double)tmp_ai2);
            daty.datatype = 1;
          } else if(datx.datatype == 7) {
            daty.floatdata = pow(datx.floatdata , tmp_ad2);
            daty.datatype = 1;
          }

        } else
        if(daty.datatype == 6) {

          if(datx.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.val = (int)pow((double)tmp_ai , (double)tmp_i);
            daty.datatype = 0;
          } else if(datx.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.floatdata = pow((double)tmp_ai , tmp_d);
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            daty.val = (int)pow((double)tmp_ai , (double)tmp_ai2);
            daty.datatype = 0;
          } else if(datx.datatype == 7) {
            daty.floatdata = pow((double)tmp_ai , tmp_ad2);
            daty.datatype = 1;
          }

        } else
        if(daty.datatype == 7) {

          if(datx.datatype == 0) {
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.floatdata = pow(tmp_ad , (double)tmp_i);
            daty.datatype = 1;
          } else if(datx.datatype == 1) {
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.floatdata = pow(tmp_ad , tmp_d);
            daty.datatype = 1;
          } else if(datx.datatype == 6) {
            daty.floatdata = pow(tmp_ad , (double)tmp_ai2);
            daty.datatype = 1;
          } else if(datx.datatype == 7) {
            daty.floatdata = pow(tmp_ad , tmp_ad2);
            daty.datatype = 1;
          }

        } else {
          Error("salah dalam pemangkatan");
        }

	break;

      case '%':
        if(daty.datatype == 0) {

          if(datx.datatype == 0) {
            if( tmp_i == 0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" daty 0 datx 0 <BR>\n", web_r);
            daty.val = daty.val % tmp_i;
            daty.datatype = 0;
          } else if(datx.datatype == 1) {
            if( tmp_d == 0.0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" daty 0 datx 1 <BR>\n", web_r);
            daty.val = daty.val % abs((int)tmp_d);
            daty.datatype = 0;
          } else if(datx.datatype == 6) {
            if( tmp_ai == 0 )
              Error("Dibagi dengan Nol");
            daty.val = daty.val % tmp_ai2;
            daty.datatype = 0;
          } else if(datx.datatype == 7) {
            if( tmp_ad2 == 0.0 )
              Error("Dibagi dengan Nol");
            daty.val = daty.val % abs((int)tmp_ad2);
            daty.datatype = 0;
          }

        } else
        if(daty.datatype == 1) {

          if(datx.datatype == 0) {
            if( tmp_i == 0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.val = abs((int)daty.floatdata) % tmp_i;
            daty.datatype = 0;
          } else if(datx.datatype == 1) {
            if( tmp_d == 0.0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.val = abs((int)daty.floatdata) % abs((int)tmp_d);
            daty.datatype = 0;
          } else if(datx.datatype == 6) {
            if( tmp_ai2 == 0 )
              Error("Dibagi dengan Nol");
            daty.val = abs((int)daty.floatdata) % tmp_ai2;
            daty.datatype = 0;
          } else if(datx.datatype == 7) {
            if( tmp_ad2 == 0.0 )
              Error("Dibagi dengan Nol");
            daty.val = abs((int)datx.floatdata) % abs((int)tmp_ad2);
            daty.datatype = 1;
          }

        } else
        if(daty.datatype == 6) {

          if(datx.datatype == 0) {
            if( tmp_i == 0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.val = tmp_ai % tmp_i;
            daty.datatype = 0;
          } else if(datx.datatype == 1) {
            if( tmp_d == 0.0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.val = tmp_ai % abs((int)tmp_d);
            daty.datatype = 0;
          } else if(datx.datatype == 6) {
            if( tmp_ai2 == 0 )
              Error("Dibagi dengan Nol");
            daty.val = tmp_ai % tmp_ai2;
            daty.datatype = 0;
          } else if(datx.datatype == 7) {
            if( tmp_ad2 == 0.0 )
              Error("Dibagi dengan Nol");
            daty.val = tmp_ai % abs((int)tmp_ad2);
            daty.datatype = 0;
          }

        } else
        if(daty.datatype == 7) {

          if(datx.datatype == 0) {
            if( tmp_i == 0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 0 <BR>\n", web_r);
            daty.val = abs((int)tmp_ad) % tmp_i;
            daty.datatype = 0;
          } else if(datx.datatype == 1) {
            if( tmp_d == 0.0 )
              Error("Dibagi dengan Nol");
            // ap_rputs(" datx 1 datz 1 <BR>\n", web_r);
            daty.val = abs((int)tmp_ad) % abs((int)tmp_d);
            daty.datatype = 0;
          } else if(datx.datatype == 6) {
            if( tmp_ai2 == 0 )
              Error("Dibagi dengan Nol");
            daty.val = abs((int)tmp_ad) % tmp_ai2;
            daty.datatype = 0;
          } else if(datx.datatype == 7) {
            if( tmp_ad2 == 0.0 )
              Error("Dibagi dengan Nol");
            daty.val = abs((int)tmp_ad) % abs((int)tmp_ad2);
            daty.datatype = 0;
          }

        } else {
          Error("salah dalam operasi modulus");
        }
	break;
      }

    getlex();
    symbol = lex.detail.symbol;

  }

  ungetlex();


  return daty;
}



