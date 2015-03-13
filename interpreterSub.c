// //////////////////////////////////////////////////////////////////////
// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
// //////////////////////////////////////////////////////////////////////

// Last 2014/5/6
// Fix InterpreterLyrParam

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

#ifdef WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#endif

extern BAIK_LEX lex;  
extern BAIK_ADDR pg;  

#define MAX_SUB_DEPTH  64

extern int sub_deep;
extern int isLyrSub;
extern int isTimerSub;
extern int class_sub_deep;

extern char currentSub[MAX_STRING_LEN];
extern char currentClass[MAX_STRING_LEN];

extern VAL_LABEL expression( void  );

// --------------------------------------

#ifdef USE_GTK2
extern GtkWidget *get_gui_array(VAL_LABEL valdat, long idx);
extern GtkWidget *get_eventbox_array(VAL_LABEL valdat, long idx);
extern int get_guitype_array(VAL_LABEL valdat, long idx);
extern void save_gui_array(VAL_LABEL valdat, long idx, GtkWidget *widget, GtkWidget *eventbox, int GUItype);
#endif
// --------------------------------------

void InterpreterSub( int endSub, char subName[MAX_STRING_LEN] )
{
  /* Do as Function Program */
    memset(&currentSub, '\0', sizeof(currentSub));
    strcpy(currentSub, subName);

    sub_deep++;
    if(sub_deep > MAX_SUB_DEPTH )
      Error("Melebihi kapasitas rekursif");

    //printf("start interpreterSub ...\n");
    do{

       Interpreter();

    }while( pg.pt <= endSub && strncmp(lex.detail.string , "}", 1) != 0 
            && lex.type != _EOF );

    sub_deep--;
    //printf("interpretSub finish , back to deep %d\n", sub_deep);
    memset(&currentSub, '\0', sizeof(currentSub));
}


void InterpreterLyrSub( int endSub, char subName[MAX_STRING_LEN] )
{
  /* Do as Function Program */

    //sub_deep++;
    //if(sub_deep > MAX_SUB_DEPTH )
    //  Error("Melebihi kapasitas rekursif");

    isLyrSub = 1;

	// printf("start interpreterLyrSub ...\n");
    do{

       Interpreter();

    }while( pg.pt <= endSub && strncmp(lex.detail.string , "}", 1) != 0 
            && lex.type != _EOF );

    isLyrSub = 0;

    //sub_deep--;

}

int InterpreterTimerSub( int endSub, char subName[MAX_STRING_LEN] )
{
    int ret = 1; // TRUE

    if(sub_deep > MAX_SUB_DEPTH )
      Error("Melebihi kapasitas rekursif");

    isTimerSub = 1;

	// printf("start interpreterLyrSub ...\n");
    do{

       Interpreter();

       if(lex.type == _STOP_DETAK) {
          ret = 0; // FALSE
	      break;
       }

    }while( pg.pt <= endSub && strncmp(lex.detail.string , "}", 1) != 0 
            && lex.type != _EOF );

    isTimerSub = 0;

	return ret;
}

void InterpreterParam( int progType, int endSub, char subName[MAX_STRING_LEN] )
{
  int i=0;
  VAL_LABEL valdat, datx;
  char ident[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&datx, '\0', sizeof(datx));
  memset(&ident, '\0', sizeof(ident));

  // printf("InterpreterParam...\n");

  if(progType == 2 ) {
    /* Do as function Parameter subtitution Program */

    pg.pt      = 0;
    pg.back_pt = 0;

    /* throw out '{' symbol                   */
    getlex();

    getlex();
    if(strncmp(lex.detail.string , "}", 1) == 0)
      return;

    ungetlex();

    // printf("param src: %s\n", pg.source);

    do{
         
      // first ident
      getlex();
      // printf("type %d ident: %s\n", lex.type, lex.detail.string);

      if(lex.type == TYPE_IDENT) {
        // keep first ident in memory
        memset(&ident, '\0', sizeof(ident));
	    strcpy(ident, lex.detail.ident);

        // get equal sym
	    getlex();
        // printf("ident: %s\n", lex.detail.string);
	    if( lex.type == _EOF )
          Error("interupsi yang tidak diinginkan");

        if( lex.detail.symbol != '=' )    
          Error("ident salah masukan");

        // get value
	    getlex();
	    if(lex.type == TYPE_NUM) {
		  datx.val = lex.detail.num;
		  datx.datatype = 0;
	    } else if(lex.type == TYPE_DBL) {
		  datx.floatdata = lex.detail.dblnum;
		  datx.datatype = 1;
        } else if(lex.type == TYPE_STR) {
                if(lex.detail.string != '\0' && strlen(lex.detail.string) > 0) {
                  strcpy(datx.str , lex.detail.string);
	        } else {
                  strcpy(datx.str , "");
	        }
		    datx.datatype = 3;
	    } else if(lex.type == TYPE_IDENT) {
		  // printf("ident val : %s\n", lex.detail.ident);
	      // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
          ungetlex();
          ungetlex();
          valdat = expression();

		  // printf("get datatype :%d , val : %d \n", valdat.datatype, valdat.val);
          datx = valdat;
		  datx.datatype = valdat.datatype;
        }

	    // printf("saving ident ...%s\n", ident);
	    // printf("saving type ...%d\n", datx.datatype);
	    //printf("saving value ...%d\n", datx.val);
	    //printf("saving dbl ...%f\n", datx.floatdata);
        // save ident
	    ValLabel( ident, sub_deep + 1, datx, VAL_FLAG_SEARCH_W );

      }


    }while( lex.type != _EOF && strncmp(lex.detail.string , "}", 1) != 0  );

  } 

}

void InterpreterLyrParam( int progType, int endSub, char subName[MAX_STRING_LEN] )
{
  int i=0;
  VAL_LABEL valdat, valdat2, datx, tmpdat, tmpdat2;
  char ident[MAX_STRING_LEN];
  char  class_tmpvar[MAX_STRING_LEN];  

  long idx=0;                           // array index
  int tmp_deep = 0;
  int isReSearch = 0;

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&datx, '\0', sizeof(datx));
  memset(&ident, '\0', sizeof(ident));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  if(progType == 2 ) {
    /* Do as function Parameter subtitution Program */

	//  printf("++++++++++++++ InterpreterLyrParam... sub_deep %d, isLyrSub %d\n", sub_deep, isLyrSub);

    pg.pt      = 0;
    pg.back_pt = 0;

    /* throw out '{' symbol                   */
    getlex();

    getlex();
    if(strncmp(lex.detail.string , "}", 1) == 0)
      return;

    ungetlex();

    //printf("param src: %s\n", pg.source);

	tmp_deep = sub_deep;

    do{
         
      // sub inside Lyr Function
	  // printf("inside lyr func loop : sub_deep %d, tmp_deep %d, isLyrSub %d\n", sub_deep, tmp_deep, isLyrSub);

	  sub_deep = 1;

      // first ident
      getlex();
      // printf("==== type %d ident: %s\n", lex.type, lex.detail.string);

      if(lex.type == TYPE_IDENT) {
        // keep first ident in memory
        memset(&ident, '\0', sizeof(ident));
  	    strcpy(ident, lex.detail.ident);

		//printf("==== ident: %s\n", ident);

        // get equal sym
	    getlex();
        // printf("ident: %s\n", lex.detail.string);
	    if( lex.type == _EOF )
          Error("interupsi yang tidak diinginkan");

        if( lex.detail.symbol != '=' )    
          Error("ident salah masukan");

		// ///////////////////////
        // get value
		// ///////////////////////
	    getlex();

	if(lex.type == TYPE_NUM) {
	  datx.val = lex.detail.num;
	  datx.datatype = 0;
	} else if(lex.type == TYPE_DBL) {
	  datx.floatdata = lex.detail.dblnum;
	  datx.datatype = 1;
        } else if(lex.type == TYPE_STR) {
          if(lex.detail.string != '\0' && strlen(lex.detail.string) > 0) {
             strcpy(datx.str , lex.detail.string);
          } else {
             strcpy(datx.str , "");
          }
          datx.datatype = 3;
	} else if(lex.type == TYPE_IDENT) {
	  //printf("====> ident val : %s\n", lex.detail.ident);
	  //printf("Param current class: %s\n", currentClass);

          //ungetlex();
          //ungetlex();
          //valdat = expression();

          memset(&valdat, '\0', sizeof(valdat));
		  memset(&tmpdat2, '\0', sizeof(tmpdat2));
		  tmpdat2.datatype = 40;   //GTK widget

		  //printf("ident %s, sub deep %d\n", lex.detail.ident, sub_deep);

          if(currentClass != NULL && strlen(currentClass) > 0) {
            sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
	        //printf("tulis: construct class var: %s , deep %d\n", class_tmpvar, class_sub_deep);
			//printf("start Class ValLabel ...\n");
			valdat = ValLabel(class_tmpvar, class_sub_deep, tmpdat2, VAL_FLAG_SEARCH_R);
          } else {
			//printf("start ValLabel ...\n");
	        valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat2, VAL_FLAG_SEARCH_R );
	      }

	      // printf("Get datatype :%d , GUI type : %d \n", valdat.datatype, valdat.GUItype);

		  if (valdat.GUItype == 0) {
			  // printf("Get 0 data ... Try to seach on sub_deep 0 ...\n");

			  isReSearch = 1;

			  sub_deep = 0;
			  tmp_deep = sub_deep;

			  if (currentClass != NULL && strlen(currentClass) > 0) {
				  sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
				  //printf("tulis: construct class var: %s , deep %d\n", class_tmpvar, class_sub_deep);
				  //printf("start Class ValLabel ...\n");
				  valdat = ValLabel(class_tmpvar, class_sub_deep, tmpdat2, VAL_FLAG_SEARCH_R);
			  }
			  else {
				  //printf("start ValLabel ...\n");
				  valdat = ValLabel(lex.detail.ident, sub_deep, tmpdat2, VAL_FLAG_SEARCH_R);
			  }
		  }

          datx = valdat;
	      datx.datatype = valdat.datatype;

	} else if(lex.type == TYPE_ARRAY) {
	  // printf("subtitute array .... \n");

              if(strlen(lex.detail.array_str) > 0) {
                // printf("start...\n");

                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atol (valdat.array_idx);
                } else {
		   // printf("show NOT digit : %s\n", valdat.array_idx);
                   /* Read index param */

                   if(currentClass != NULL && strlen(currentClass) > 0) {
                     sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_idx);
                     tmpdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
		   } else {
                     tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
		     // printf("get idx type: %d, val %d\n", tmpdat.datatype, tmpdat.val);
	           }

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

                // printf("name %s , idx %d\n", valdat.array_name, idx);

		        // get real value of array
		        // printf("search array: %s\n", valdat.array_name);
                if(currentClass != NULL && strlen(currentClass) > 0) {
		  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_name);
                  valdat2 = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
		} else {
                  valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
		}
		
                // ltoa(idx, valdat2.array_idx, 10);
		        sprintf(valdat2.array_idx, "%li", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

		        //printf("get valdat2 type: %d, renban %d\n", valdat2.datatype, valdat2.array_widget);
                //printf("valdat2 array name %s \n", valdat2.array_name);
                //printf("valdat2 array_idx %d \n", idx);

                if(valdat2.datatype == 60) {  // Array GUI 
                  #ifdef USE_GTK2
                  datx.widget   = get_gui_array(valdat2, idx);
		  datx.eventbox = get_eventbox_array(valdat2, idx);
		  datx.GUItype  = get_guitype_array(valdat2, idx);
		  
		  //printf("interpretLyrParam : get GUI array, GUItype %d\n", datx.GUItype);
                  #endif
                } else {
                  Error("salah jenis untaian");
                }
                
              } else {
                // printf("NOT start...\n");              
              }

              datx.datatype = 40;
	    }

	    //printf("InterpreterLyrParam : Saving ident ...%s\n", ident);
	    //printf("saving type ...%d\n", datx.datatype);
	    //printf("saving value ...%d\n", datx.val);
	    //printf("saving dbl ...%f\n", datx.floatdata);
        // save ident

        if(currentClass != NULL && strlen(currentClass) > 0) {
	      memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
          sprintf(class_tmpvar, "%s->%s", currentClass, ident);
	      //printf("saving class var: %s %s\n", class_tmpvar);

		  ValLabel(class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_W);
	    } else {
		  ValLabel(ident, sub_deep, datx, VAL_FLAG_SEARCH_W);
	    }

      }


	}while( lex.type != _EOF && strncmp(lex.detail.string , "}", 1) != 0  );

	// printf("after read loop : sub_deep %d, tmp_deep %d, isLyrSub %d\n", sub_deep, tmp_deep, isLyrSub);

	if (isReSearch) {
		sub_deep = tmp_deep;
	}
  } 

}
