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

#define MAX_CLASS_SUB_DEPTH  64
extern class_sub_deep;

extern char currentClass[MAX_STRING_LEN];

extern void varstack_printData(void);

extern void Interpreter( void  );

void InterpreterClassSub( int endSub, char className[MAX_STRING_LEN] )
{
    /* Set Current Class Name Running */
    memset(&currentClass, '\0', sizeof(currentClass));
    strcpy(currentClass, className);

    //class_sub_deep++;
    //if(class_sub_deep > MAX_CLASS_SUB_DEPTH )
    //  Error("Melebihi kapasitas rekursif");

    // printf("=== start interpreterClass ...\n");
    do{

       Interpreter();

    }while( pg.pt <= endSub && strncmp(lex.detail.string , "}", 1) != 0 
            && lex.type != _EOF );

    //}while( pg.pt <= endSub && lex.type != _EOF );

    // class_sub_deep--;
	// printf("interpretClassSub finish , back to deep %d\n", class_sub_deep);

    /* Delete Current Class Name Running */
    memset(&currentClass, '\0', sizeof(currentClass));
}

void InterpreterClassParam( int progType, int endSub, char className[MAX_STRING_LEN] )
{
  int i=0;
  VAL_LABEL valdat, datx;
  char ident[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&datx, '\0', sizeof(datx));
  memset(&ident, '\0', sizeof(ident));

  if(progType == 2 ) {
    /* Do as class function Parameter subtitution Program */

    pg.pt      = 0;
    pg.back_pt = 0;

    /* throw out '{' symbol                   */
    getlex();

    getlex();
    if(strncmp(lex.detail.string , "}", 1) == 0)
      return;

    ungetlex();

    // printf("class func param src: %s\n", pg.source);

    do{
         
      // first ident
      getlex();
      // printf("type %d ident: %s\n", lex.type, lex.detail.string);

      if(lex.type == TYPE_OBJECT) {
        // keep first ident in memory
        memset(&ident, '\0', sizeof(ident));
		sprintf(ident, "%s", lex.detail.string);

        // get equal sym
	    getlex();
	    // printf("ident: %s\n", lex.detail.string);
	    if( lex.type == _EOF )
          Error("interupsi yang tidak diinginkan");

        if( lex.detail.symbol != '=' )    
          Error("ident salah masukan");

        // get value
	    getlex();
		// printf("lex detail ident : %s\n", lex.detail.ident);
        // printf("lex type : %d\n", lex.type);

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

	      valdat = ValLabel( lex.detail.ident, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
          //ungetlex();
          //ungetlex();
          //valdat = Factor();

		  // printf("get value datatype :%d , val : %d \n", valdat.datatype, valdat.val);
          datx = valdat;
		  datx.datatype = valdat.datatype;
        }

		//printf("saving class obj name: %s\n", ident);
	    //printf("saving type ...%d\n", datx.datatype);
	    //printf("saving value ...%d\n", datx.val);
	    //printf("saving dbl ...%f\n", datx.floatdata);
        // save ident
	    ValLabel( ident, class_sub_deep, datx, VAL_FLAG_SEARCH_W );

      }

    }while( lex.type != _EOF && strncmp(lex.detail.string , "}", 1) != 0  );

  } 

}
