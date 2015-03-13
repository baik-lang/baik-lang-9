// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyTulisarsip ()
{

  int  n=0;

  char logMsg[MAX_STRING_LEN * 2],
       tmpMsg[MAX_STRING_LEN * 2];

  VAL_LABEL valdat, valdat2, tmpdat, valdat0;
  
  long    idx=0;                           // array index
  FILE   *tmpfile=NULL;
 
  int    isFileOpen=0;


  char   get_name[MAX_STRING_LEN];


  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];


  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&valdat0, '\0', sizeof(valdat0));

  memset(&get_name, '\0', sizeof(get_name));
  
  memset(&tmpMsg, '\0', sizeof(tmpMsg));
  memset(&logMsg, '\0', sizeof(logMsg));;

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  memset(tmpMsg, '\0', sizeof(tmpMsg));
  memset(logMsg, '\0', sizeof(logMsg));

  strcpy(logMsg, "");

  n = 0;

	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_NUM:
              if(n >= 1) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(tmpMsg, sizeof(tmpMsg),"%li" , lex.detail.num );
                 #else
                 snprintf(tmpMsg, sizeof(tmpMsg),"%li" , lex.detail.num );
                 #endif
                #else
                snprintf(tmpMsg, sizeof(tmpMsg),"%li" , lex.detail.num );
                #endif
                strcat(logMsg, tmpMsg);
              } 

	      break;

	    case TYPE_DBL:
              if(n >= 1) {
                sprintf(tmpMsg, "%f", lex.detail.dblnum );
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(tmpMsg, sizeof(tmpMsg),"%f", lex.detail.dblnum );
                 #else
                 snprintf(tmpMsg, sizeof(tmpMsg),"%f", lex.detail.dblnum );
                 #endif
                #else
                snprintf(tmpMsg, sizeof(tmpMsg),"%f", lex.detail.dblnum );
                #endif
                strcat(logMsg, tmpMsg);
              } 

	      break;

	    case TYPE_STR:
              if(n >= 1) {
                strcpy(tmpMsg, lex.detail.string );
                strcat(logMsg, tmpMsg);
              } 

	      break;
	    
	    case TYPE_IDENT:
              //printf(" DEBUG: TULIS_ARSIP\n");
	          ungetlex();
              valdat = expression();

              if(valdat.datatype == 0) {
               if(n >= 1) {
                 #ifdef WIN32
                  #ifndef S_SPLINT_S
                  sprintf_s(tmpMsg, sizeof(tmpMsg),"%li" , valdat.val );
                  #else
                  snprintf(tmpMsg, sizeof(tmpMsg),"%li" , valdat.val );
                  #endif
                 #else
                 snprintf(tmpMsg, sizeof(tmpMsg),"%li" , valdat.val );
                 #endif
               }
              } else
              if(valdat.datatype == 1) {
               if(n >= 1) {
                 #ifdef WIN32
                  #ifndef S_SPLINT_S
                  sprintf_s(tmpMsg, sizeof(tmpMsg),"%f", valdat.floatdata);
                  #else
                  snprintf(tmpMsg, sizeof(tmpMsg),"%f", valdat.floatdata);
                  #endif
                 #else
                 snprintf(tmpMsg, sizeof(tmpMsg),"%f", valdat.floatdata);
                 #endif
               }
              } else
              if(valdat.datatype == 2) {
               if(n == 0) {
                 tmpfile    = valdat.filedata;
                 isFileOpen = valdat.isFileOpen;
               }
              } else
              if(valdat.datatype == 3) {
               if(n >= 1) {
                 strcpy(tmpMsg, valdat.str);
               }
              }
              strcat(logMsg, tmpMsg);

	      break;

            case TYPE_ARRAY:
              /* printf("write array\n"); */

              if(strlen(lex.detail.array_str) > 0) {
                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atoi (valdat.array_idx);
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

                //ltoa(idx, valdat.array_idx, 10);
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
                 #else
                 snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
                 #endif
                #else
                snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
                #endif

                if(idx < 0 || idx > (valdat.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(n >= 1) {
                  if(valdat.datatype == 6 && valdat.array_i != '\0') {
                    if(valdat.array_i == '\0')
                      Error("ukuran Untaian belum terdefinisi");

                    #ifdef WIN32
                     #ifndef S_SPLINT_S
                     sprintf_s(tmpMsg, sizeof(tmpMsg),"%d", get_int_array(valdat, idx));
                     #else
                     snprintf(tmpMsg, sizeof(tmpMsg),"%d", get_int_array(valdat, idx));
                     #endif
                    #else
                    snprintf(tmpMsg, sizeof(tmpMsg),"%d", get_int_array(valdat, idx));
                    #endif

                  } else if (valdat.datatype == 7 && valdat.array_d != '\0') {
                    if(valdat.array_d == '\0')
                      Error("ukuran Untaian belum terdefinisi");

                    #ifdef WIN32
                     #ifndef S_SPLINT_S
                     sprintf_s(tmpMsg, sizeof(tmpMsg),"%f" , get_dbl_array(valdat, idx) );
                     #else
                     snprintf(tmpMsg, sizeof(tmpMsg),"%f" , get_dbl_array(valdat, idx) );
                     #endif
                    #else
                    snprintf(tmpMsg, sizeof(tmpMsg),"%f" , get_dbl_array(valdat, idx) );
                    #endif

                  } else if (valdat.datatype == 8 && valdat.array_s != '\0') {
                    if(valdat.array_s == '\0')
                      Error("ukuran Untaian belum terdefinisi");

                    get_str_array(valdat, idx, (char *)&tmpMsg);

                  } else if (valdat.datatype == 10) {
                    strcpy(tmpMsg, valdat.long_str[idx]);

                  } else {
                    strcpy(tmpMsg, "Nil");
                  }

                  strcat(logMsg, tmpMsg);
                }

              }

              break;

	    default:
	      Error("bentuk perintah TULIS_ARSIP salah");
	    }

          n++;

	  getlex();


	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        /*
        printf("tmpMsg : %s", tmpMsg);
        printf("isOpen : %d\n", isFileOpen);
        */
        if(isFileOpen == 1) {
          fprintf(tmpfile, "%s", logMsg);
          fflush( tmpfile );
        }

	ungetlex();
}


