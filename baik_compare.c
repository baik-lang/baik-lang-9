// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// 2015/06/09 memleak fixed

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/stat.h>
#include <math.h>

#ifdef WINDOWS
#include <windows.h>
#include <direct.h>
#endif

#include "baik_word.h"
#include "baik_struct.h"
#include "val_label.h"
#include "baik_lexer.h"

BAIK_LEX lex;  
BAIK_ADDR pg;  

BAIK_ADDR tmp_pg;  

extern char currentClass[MAX_STRING_LEN];   // current Class for Object Oriented

// --------------------------------------
// Stack for Array String
#include "stack_str_struct.h"

extern int renban;
extern STR_ARRY TmpStrBox;
extern STR_ARRY TmpStrBox2;
extern int strarryPos;
// --------------------------------------

extern int get_int_array(VAL_LABEL valdat, long idx);
extern void save_int_array(VAL_LABEL valdat, long idx, int val);
// --------------------------------------

extern double get_dbl_array(VAL_LABEL valdat, long idx);
extern void save_dbl_array(VAL_LABEL valdat, long idx, double dbl);
// --------------------------------------

extern VAL_LABEL AddSub(void);

#ifdef WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#endif


VAL_LABEL Compare()
{
  VAL_LABEL datx, daty;
  VAL_LABEL datx2, tmp;

  char symbol='\0';
  int idx=0, idx2=0;

// Do NOT use memset here ! caused memory leaks
//  memset(&datx, '\0', sizeof(datx));
//  memset(&daty, '\0', sizeof(daty));
//  memset(&datx2, '\0', sizeof(datx2));
//  memset(&tmp, '\0', sizeof(tmp));

  datx = AddSub();
  // printf("Addsub type %d\n", datx.datatype);

  daty = datx;

  getlex();
  if( lex.type == _EOF )
    Error("Compare: Program berhenti diluar perkiraan");

  if( ( lex.type != TYPE_SYM ) || 
      ( lex.detail.symbol != '=' &&
        lex.detail.symbol != '<' &&
        lex.detail.symbol != '>' ) ){
    ungetlex();



    return daty;
  }

  symbol = lex.detail.symbol;

  getlex();


  if( lex.type == _EOF )
    Error("Compare: Program berhenti diluar perkiraan");

  switch( symbol )
    {
    case '=':
      if( lex.type == TYPE_SYM ){
	    switch( lex.detail.symbol )
	  {

	  case '=':
            // printf("perbandingan , type %d\n", datx.datatype);
            if(datx.datatype == 0) {
              /*
              perbandingan : integer
              return : integer
              */
              daty.val = ( datx.val == AddSub().val ) ? 1 : 0;
            } else if(datx.datatype == 1) {
              daty.val = ( datx.floatdata == AddSub().floatdata ) ? 1 : 0;
            } else if(datx.datatype == 3) {
              // printf("perbandingan string \n");
              tmp = AddSub();
              if( !strcmp(datx.str, tmp.str) ) {
                daty.val = 1;
              } else { 
                daty.val = 0;
              }   
            } else if(datx.datatype == 6) {
              /* array int */
              idx = atoi(datx.array_idx);
              /* printf("d %d\n", get_int_array(datx, idx)); */
              datx2 = AddSub();

              if(datx2.datatype == 0) {
                daty.val = ( get_int_array(datx, idx) == datx2.val ) ? 1 : 0;
              } else if(datx2.datatype == 6) {
                idx2 = atoi(datx2.array_idx);
                /* printf("d2 %d\n", get_int_array(datx2, idx2)); */
                daty.val = ( get_int_array(datx, idx) == get_int_array(datx2, idx2) ) ? 1 : 0;
              }
            } else if(datx.datatype == 7) {
              /* array dbl */
              idx = atoi(datx.array_idx);
              /* printf("d %d\n", get_int_array(datx, idx)); */
              datx2 = AddSub();
              if(datx2.datatype == 1) {
                daty.val = ( get_dbl_array(datx, idx) == datx2.floatdata ) ? 1 : 0;
              } else if(datx2.datatype == 7) {
                idx2 = atoi(datx2.array_idx);
                daty.val = ( get_dbl_array(datx, idx) == get_dbl_array(datx2, idx2) ) ? 1 : 0;
              }
            } else if(datx.datatype == 8) {
              /* array string */
              // printf("perbandingan array string \n");
              idx = atoi(datx.array_idx);
              /*printf("s %s\n", datx.array_s[idx]); */
              datx2 = AddSub();
              // printf("datx2 s %s %d\n", datx2.str, datx2.datatype);
              if(datx2.datatype == 0 || datx2.datatype == 3) {

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));

                  strcpy(TmpStrBox.var.array_name, datx.array_name);
				  renban = datx.array_s;
				  if(renban < 0) {
                    printf("! variabel untaian tidak ditemukan\n");
				  } else {
                    TmpStrBox.str.stackid = renban;
                    TmpStrBox.str.idx = idx;

					strarryPos = string_findData(TmpStrBox.str);
					if(strarryPos < 0) {
  					  printf("! nilai untaian kata tidak ditemukan\n");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);
					  printf("get datx str %s\n", TmpStrBox.str.mystring);
					  printf("get datx2 str %s\n", datx2.str);
					  daty.val = (!strcmp(TmpStrBox.str.mystring, datx2.str) ) ? 1 : 0;

					}

				  }

				  //daty.val = ( datx.array_s == datx2.str) ) ? 1 : 0;
              } else if(datx2.datatype == 8) {
                idx2 = atoi(datx2.array_idx);
				daty.val = ( datx.array_s == datx2.array_s ) ? 1 : 0;
              }
            }

	    break;
	  default:
	    Error("setelah '=', ada simbol lain selain '=' ");
	  }
      }
      /* '=' */
      else{
	ungetlex();
	return ( AddSub() );
      }
      break;
      
    case '>':
      if( lex.type == TYPE_SYM ){
	switch( lex.detail.symbol )
	  {
	    /* '>=' */
	  case '=':
            if(datx.datatype == 0) {
              daty.val = ( datx.val >= AddSub().val ) ? 1 : 0;
            } else  if(datx.datatype == 1) {
              daty.val = ( datx.floatdata >= AddSub().floatdata ) ? 1 : 0;
            } else if(datx.datatype == 6) {
              /* array int */
              idx = atoi(datx.array_idx);
              /* printf("d %d\n", get_int_array(datx, idx)); */
              datx2 = AddSub();
              if(datx2.datatype == 0) {
                daty.val = ( get_int_array(datx, idx) >= datx2.val ) ? 1 : 0;
              } else if(datx2.datatype == 6) {
                idx2 = atoi(datx2.array_idx);
                /* printf("d2 %d\n", get_int_array(datx2, idx2)); */
                daty.val = ( get_int_array(datx, idx) >= get_int_array(datx2, idx2) ) ? 1 : 0;
              }
            } else if(datx.datatype == 7) {
              /* array dbl */
              idx = atoi(datx.array_idx);
              /* printf("d %d\n", get_int_array(datx, idx)); */
              datx2 = AddSub();
              if(datx2.datatype == 1) {
                daty.val = ( get_dbl_array(datx, idx) >= datx2.floatdata ) ? 1 : 0;
              } else if(datx2.datatype == 7) {
                idx2 = atoi(datx2.array_idx);
                daty.val = ( get_dbl_array(datx, idx) >= get_dbl_array(datx2, idx2) ) ? 1 : 0;
              }
            }

	    break;
	  default:
	    Error("setelah '>', ada simbol lain selain '=' ");
	  }
      }
      /* '>' */
      else{
	ungetlex();
        if(datx.datatype == 0) {
          daty.val = ( datx.val > AddSub().val ) ? 1 : 0;
        } else  if(datx.datatype == 1) {
          daty.val = ( datx.floatdata > AddSub().floatdata ) ? 1 : 0;
        } else if(datx.datatype == 6) {
          /* array int */
          idx = atoi(datx.array_idx);
          /* printf("d %d\n", get_int_array(datx, idx)); */
          datx2 = AddSub();
          if(datx2.datatype == 0) {

            daty.val = ((int)get_int_array(datx, idx) > datx2.val ) ? 1 : 0;

          } else if(datx2.datatype == 6) {
            idx2 = atoi(datx2.array_idx);
            /* printf("d2 %d\n", get_int_array(datx2, idx2)); */
            daty.val = ( get_int_array(datx, idx) > get_int_array(datx2, idx2) ) ? 1 : 0;
          }
        } else if(datx.datatype == 7) {
          /* array dbl */
          idx = atoi(datx.array_idx);
          /* printf("d %d\n", get_int_array(datx, idx)); */
          datx2 = AddSub();
          if(datx2.datatype == 1) {
            daty.val = ( get_dbl_array(datx, idx) > datx2.floatdata ) ? 1 : 0;
          } else if(datx2.datatype == 7) {
            idx2 = atoi(datx2.array_idx);
            daty.val = ( get_dbl_array(datx, idx) > get_dbl_array(datx2, idx2) ) ? 1 : 0;
          }
        }
      }
      break;
      
    case '<':
      if( lex.type == TYPE_SYM ){
	switch( lex.detail.symbol )
	  {
	    /* '<>' */
	  case '>':
            if(datx.datatype == 0) {
              daty.val = ( datx.val != AddSub().val ) ? 1 : 0;
            } else  if(datx.datatype == 1) {
              daty.val = ( datx.floatdata != AddSub().floatdata ) ? 1 : 0;
            } else  if(datx.datatype == 3) {
              tmp = AddSub();
              daty.val = ( strcmp(datx.str, tmp.str) ) ? 1 : 0;
            } else  if(datx.datatype == 42) {
              #ifdef USE_GTK2
              tmp = AddSub();
              //printf("compare font dialog\n");
			  daty.val = ( strcmp(datx.str, tmp.str) ) ? 1 : 0;
              #endif
              #ifdef USE_GTK3
			  tmp = AddSub();
			  //printf("compare font dialog\n");
			  daty.val = ( strcmp(datx.str, tmp.str) ) ? 1 : 0;
              #endif
            } else  if(datx.datatype == 43) {
              #ifdef USE_GTK2
              tmp = AddSub();
              //printf("compare color dialog\n");
			  daty.val = ( strcmp(datx.str, tmp.str) ) ? 1 : 0;
              #endif
              #ifdef USE_GTK3
			  tmp = AddSub();
			  //printf("compare color dialog\n");
			  daty.val = ( strcmp(datx.str, tmp.str) ) ? 1 : 0;
              #endif
            } else  if(datx.datatype == 44) {
              #ifdef USE_GTK2
              tmp = AddSub();
              //printf("compare file dialog\n");
              daty.val = ( strcmp(datx.filename, tmp.str) ) ? 1 : 0;
              #endif
              #ifdef USE_GTK3
			  tmp = AddSub();
			  //printf("compare file dialog\n");
			  daty.val = (strcmp(datx.filename, tmp.str)) ? 1 : 0;
              #endif
            } else if(datx.datatype == 6) {
              /* array int */
              idx = atoi(datx.array_idx);
              /* printf("d %d\n", get_int_array(datx, idx)); */
              datx2 = AddSub();
              if(datx2.datatype == 0) {
                daty.val = ( get_int_array(datx, idx) != datx2.val ) ? 1 : 0;
              } else if(datx2.datatype == 6) {
                idx2 = atoi(datx2.array_idx);
                /* printf("d2 %d\n", get_int_array(datx2, idx2)); */
                daty.val = ( get_int_array(datx, idx) != get_int_array(datx2, idx2) ) ? 1 : 0;
              }
            } else if(datx.datatype == 7) {
              /* array dbl */
              idx = atoi(datx.array_idx);
              /* printf("d %d\n", get_int_array(datx, idx)); */
              datx2 = AddSub();
              if(datx2.datatype == 1) {
                daty.val = ( get_dbl_array(datx, idx) != datx2.floatdata ) ? 1 : 0;
              } else if(datx2.datatype == 7) {
                idx2 = atoi(datx2.array_idx);
                daty.val = ( get_dbl_array(datx, idx) != get_dbl_array(datx2, idx2) ) ? 1 : 0;
              }
            } else if(datx.datatype == 8) {
              /* array string */
              idx = atoi(datx.array_idx);
              /*printf("s %s\n", datx.array_s[idx]); */
              datx2 = AddSub();
              /* printf("s %s %d\n", datx2.str, datx2.datatype); */
              if(datx2.datatype == 0 || datx2.datatype == 3) {

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
                  strcpy(TmpStrBox.var.array_name, datx.array_name);
				  renban = datx.array_s;
				  if(renban < 0) {
                    printf("> variabel untaian tidak ditemukan\n");
				  } else {
                    TmpStrBox.str.stackid = renban;
                    TmpStrBox.str.idx = idx;

					strarryPos = string_findData(TmpStrBox.str);
					if(strarryPos < 0) {
  					  printf("> nilai untaian kata tidak ditemukan\n");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);
					  daty.val = ( !strcmp(TmpStrBox.str.mystring, datx2.str) ) ? 1 : 0;

					}

				  }

				  // daty.val = ( strcmp(datx.array_s[idx].str, datx2.str) ) ? 1 : 0;
              } else if(datx2.datatype == 8) {

               idx2 = atoi(datx2.array_idx);

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
                  strcpy(TmpStrBox.var.array_name, datx.array_name);
				  renban = datx.array_s;
				  if(renban < 0) {
                    printf(">2 variabel untaian tidak ditemukan\n");
				  } else {
                    TmpStrBox.str.stackid = renban;
                    TmpStrBox.str.idx = idx;

					strarryPos = string_findData(TmpStrBox.str);
					if(strarryPos < 0) {
  					  printf(">2 nilai untaian kata tidak ditemukan\n");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);
					}

				  }


                  memset(&TmpStrBox2.var.array_name, '\0', sizeof(TmpStrBox2.var.array_name));
                  strcpy(TmpStrBox2.var.array_name, datx2.array_name);
				  renban = datx2.array_s;
				  if(renban < 0) {
                    printf(">3 variabel untaian tidak ditemukan\n");
				  } else {
                    TmpStrBox2.str.stackid = renban;
                    TmpStrBox2.str.idx = idx2;

					strarryPos = string_findData(TmpStrBox2.str);
					if(strarryPos < 0) {
  					  printf(">3 nilai untaian kata tidak ditemukan\n");
					} else {
                      TmpStrBox2.str = string_getElement(strarryPos);

					  daty.val = ( !strcmp(TmpStrBox.str.mystring, TmpStrBox2.str.mystring) ) ? 1 : 0;

					}

				  }

				// daty.val = ( strcmp(datx.array_s[idx].str, datx2.array_s[idx2].str) ) ? 1 : 0;

              }
            }
	    break;
	    /* '<=' */
	  case '=':
            if(datx.datatype == 0) {
              daty.val = ( datx.val <= AddSub().val ) ? 1 : 0;
            } else  if(datx.datatype == 1) {
              daty.val = ( datx.floatdata <= AddSub().floatdata ) ? 1 : 0;
            } else if(datx.datatype == 6) {
              /* array int */
              idx = atoi(datx.array_idx);
              /* printf("d %d\n", get_int_array(datx, idx)); */
              datx2 = AddSub();
              if(datx2.datatype == 0) {
                daty.val = ( get_int_array(datx, idx) <= datx2.val ) ? 1 : 0;
              } else if(datx2.datatype == 6) {
                idx2 = atoi(datx2.array_idx);
                /* printf("d2 %d\n", get_int_array(datx2, idx2)); */
                daty.val = ( get_int_array(datx, idx) <= get_int_array(datx2, idx2) ) ? 1 : 0;
              }
            } else if(datx.datatype == 7) {
              /* array dbl */
              idx = atoi(datx.array_idx);
              /* printf("d %d\n", get_int_array(datx, idx)); */
              datx2 = AddSub();
              if(datx2.datatype == 1) {
                daty.val = ( get_dbl_array(datx, idx) <= datx2.floatdata ) ? 1 : 0;
              } else if(datx2.datatype == 7) {
                idx2 = atoi(datx2.array_idx);
                daty.val = ( get_dbl_array(datx, idx) <= get_dbl_array(datx2, idx2) ) ? 1 : 0;
              }
            }

	    break;
	  default:
	    Error("setelah '<', ada simbol lain selain '>' atau '=' ");
	  }
      }
      else{
	    ungetlex();
        if(datx.datatype == 0) {
          daty.val = ( datx.val < AddSub().val ) ? 1 : 0;
        } else  if(datx.datatype == 1) {
          daty.val = ( datx.floatdata < AddSub().floatdata ) ? 1 : 0;
        } else if(datx.datatype == 6) {
          /* array int */
          idx = atoi(datx.array_idx);
          /* printf("d %d\n", get_int_array(datx, idx)); */
          datx2 = AddSub();
          if(datx2.datatype == 0) {
            daty.val = ( get_int_array(datx, idx) < datx2.val ) ? 1 : 0;
          } else if(datx2.datatype == 6) {
            idx2 = atoi(datx2.array_idx);
            /* printf("d2 %d\n", get_int_array(datx2, idx2)); */
            daty.val = ( get_int_array(datx, idx) < get_int_array(datx2, idx2) ) ? 1 : 0;
          }
        } else if(datx.datatype == 7) {
          /* array dbl */
          idx = atoi(datx.array_idx);
          /* printf("d %d\n", get_int_array(datx, idx)); */
          datx2 = AddSub();
          if(datx2.datatype == 1) {
            daty.val = ( get_dbl_array(datx, idx) < datx2.floatdata ) ? 1 : 0;
          } else if(datx2.datatype == 7) {
            idx2 = atoi(datx2.array_idx);
            daty.val = ( get_dbl_array(datx, idx) < get_dbl_array(datx2, idx2) ) ? 1 : 0;
          }
        }


      }
      break;
      
    default:
	  Error("Internal Compare: Salah tata kalimat");
    }

  return daty;
}
