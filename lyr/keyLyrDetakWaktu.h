// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyDetak_Waktu ()
{
  int  type_func = 0; // 0: general function , 1: object function
  int  point = 0;
  int  n=0, i=0, j=0;

  int  x = 0;         // time number

  
  char   tmp_str[MAX_STRING_LEN];

  char sub_name[MAX_STRING_LEN],
       sub_param[MAX_STRING_LEN],
       sub_tmpparam[MAX_STRING_LEN];

  char get_param[MAX_STRING_LEN],
       orig_param[MAX_STRING_LEN],
       param_source[MAX_STRING_LEN * 2];

  VAL_LABEL valdat,tmpdat, tmpdat2;
  VAL_LABEL aksidat;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  char   *sub_tmpstring=NULL;
  char   *sub_tmpstring2=NULL;

  char   logMsg[MAX_STRING_LEN];
  char   tmpMsg[MAX_STRING_LEN];

  TimerData *dat=NULL;

  memset(&sub_name, '\0', sizeof(sub_name));
  memset(&sub_param, '\0', sizeof(sub_param));
  memset(&sub_tmpparam, '\0', sizeof(sub_tmpparam));

  memset(&get_param, '\0', sizeof(get_param));
  memset(&orig_param, '\0', sizeof(orig_param));
  memset(&param_source, '\0', sizeof(param_source));

  memset(&aksidat, '\0', sizeof(aksidat));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&logMsg, '\0', sizeof(logMsg));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  sub_tmpstring  = NULL;
  sub_tmpstring2 = NULL;


  // printf("aksi fungsi...\n");

  n = 0;

	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_DBL:
			if(n == 0) {
			  x =  (int)lex.detail.dblnum;
			} 
	      break;   

	    case TYPE_NUM:
			if(n == 0) {
			  x =  lex.detail.num;
			}
	      break;   

	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
               #ifdef WIN32
                #ifndef S_SPLINT_S
                sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #endif
               #else
               snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
               #endif

                //printf("construct class var: %s\n", class_tmpvar);
                aksidat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                aksidat = expression();
              }

              // printf("type %d\n", valdat.datatype);

              if(aksidat.datatype == 40) {
                if(n == 1) {
				  tmpdat.widget   = aksidat.widget;
                  tmpdat.datatype = 40;
				  tmpdat.GUItype  = aksidat.GUItype;
				} 
			  } else
			  if(aksidat.datatype == 0) {
                if(n == 0) {
                  x = aksidat.val;
				}
			  
			  } else
			  if(aksidat.datatype == 1) {
                if(n == 0) {
                  x = (int)aksidat.floatdata;
				}
			  
			  } else {
                if(n == 1) {
                  // null widget - good for detak without gui
				  tmpdat.widget   = NULL;
                  tmpdat.datatype = 40;
				} else {
                  Error("bentuk perintah detak_waktu salah");
				}
			  }

	      break;

	    case TYPE_SYM:
          /* *******************   call function ********************  */
          if( lex.detail.symbol == '&' )  {
            // printf("detak_waktu subroutine\n");

            memset(&sub_name, '\0', sizeof(sub_name));
            memset(&sub_param, '\0', sizeof(sub_param));
            memset(&sub_tmpparam, '\0', sizeof(sub_tmpparam));

            memset(&get_param, '\0', sizeof(get_param));
            memset(&orig_param, '\0', sizeof(orig_param));
            memset(&param_source, '\0', sizeof(param_source));

            getlex();

            if( lex.type == TYPE_OBJECT_FUNC ) {
		      // BENDA Function
			  type_func = 1;

            } // stop if(lex.type == TYPE_OBJECT_FUNC) 

            else if(lex.type == TYPE_IDENT) {
		      // General Function (NOT BENDA)
			  type_func = 0;

              // printf("sub name string: %s\n", lex.detail.string); 

              if(lex.detail.string != NULL && strlen(lex.detail.string) > 0)
                strcpy(sub_name, lex.detail.string);
              else
                strcpy(sub_name, "");

              /* printf("if OK, start to search\n"); */

              valdat.val = -1;
              valdat = ValLabel( sub_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              /* printf("evaluate search result\n"); */
          
              point = valdat.val;
              if( point == -1 ) {
                Error("SUB tidak ditemukan");
              } else {
                //printf("SUB ada\n");
                //printf("SUB start : %d\n",valdat.sub_pt_start);
                //printf("SUB end : %d\n",valdat.sub_pt_end);
              }
              valdat.val = 0;

              // printf("evaluate sub existance OK\n");

              getlex();
              sub_tmpstring = NULL;
		      sub_tmpstring = (char * )malloc(sizeof(char *));
		      if(sub_tmpstring == NULL) {
                Error("memori tidak cukup untuk menjalankan fungsi/sub prosedur");
		      }
		      sub_tmpstring = lex.detail.string;
              // printf("sub ( string: %s\n", sub_tmpstring);

              if( lex.type != TYPE_SYM || strncmp(lex.detail.string , "(", 1) != 0 ) {
                Error("kode SUB salah : tanpa tanda (");
              }

              strcpy(sub_param, "");

              while( sub_tmpstring[0] != ')' && lex.type != _EOF  ) {
                getlex();
                sub_tmpstring2 = NULL;
	  	        sub_tmpstring2 = (char * )malloc(sizeof(char *));
		        sub_tmpstring2 = lex.detail.string;

                if(sub_tmpstring2[0] == ')' )
                  break;

                /*
                if( lex.type != TYPE_IDENT ) {
                  Error("kode SUB salah");
                }
                */

                if(lex.type == TYPE_NUM) {
                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(tmp_str, sizeof(tmp_str),"%li", lex.detail.num);
                   #else
                   snprintf(tmp_str, sizeof(tmp_str),"%li", lex.detail.num);
                   #endif
                  #else
                  snprintf(tmp_str, sizeof(tmp_str),"%li", lex.detail.num);
                  #endif

                  strcat(sub_param, tmp_str);
                }
                else if(lex.type == TYPE_DBL) {
                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(tmp_str, sizeof(tmp_str),"%f", lex.detail.dblnum);
                   #else
                   snprintf(tmp_str, sizeof(tmp_str),"%f", lex.detail.dblnum);
                   #endif
                  #else
                  snprintf(tmp_str, sizeof(tmp_str),"%f", lex.detail.dblnum);
                  #endif

                  strcat(sub_param, tmp_str);
                }
                else if(sub_tmpstring2 != '\0' && strlen(sub_tmpstring2) > 0) {
                  strcat(sub_param, sub_tmpstring2);
                }

                getlex();
                sub_tmpstring2 = NULL;
		        sub_tmpstring2 = (char * )malloc(sizeof(char *));
		        sub_tmpstring2 = lex.detail.string;

                if(sub_tmpstring2[0] == ',') {
                  if(lex.type == TYPE_NUM) {
                    sprintf(tmp_str, "%li", lex.detail.num);
                    strcat(sub_param, tmp_str);
                  }
                  else if(lex.type == TYPE_DBL) {
                    sprintf(tmp_str, "%f", lex.detail.dblnum);
                    strcat(sub_param, tmp_str);
                  }
                  else if(sub_tmpstring2 != '\0' && strlen(sub_tmpstring2) > 0) {
                    strcat(sub_param, sub_tmpstring2);
                  }
                }

              } // end while

              /* Keep Param into temporary vars         */
              strcpy(get_param, sub_param);
              strcpy(orig_param, valdat.sub_param);

              /* check parameter count                  */
              if(checkParamNum(get_param, orig_param) != 0)
                Error("Definisi SUB tidak benar");

              //printf("sub get param: %s\n", sub_param);
              //printf("sub orig param: %s\n", valdat.sub_param);

			  /* Keep Param into temporary vars         */
              strcpy(get_param, sub_param);
              strcpy(orig_param, valdat.sub_param);
              /* printf("keep sub params ok\n"); */

              /* set global params into SUB param vars  */
              subtituteParam((char *)&sub_tmpparam, get_param, orig_param);
              if(sub_tmpparam != '\0' && strlen(sub_tmpparam) > 0)
                strcpy(param_source , sub_tmpparam );
              else
                strcpy(param_source , "" );

		  // keep position
		  posLyrSub = pg.pt;
		  posLyrSubBack = pg.back_pt;

		  // printf("deep %d pos %d \n", lyr_sub_deep, posLyrSub);

		  if(sub_tmpstring != NULL ) {
                // free(sub_tmpstring);
		  }

		  if(sub_tmpstring2 != NULL ) {
                // free(sub_tmpstring2);
		  }

		    } // end if(lex.type == TYPE_IDENT)


		  } // end if (lex.detail.symbol == '&')
		  
		  break; // TYPE_SYM

	    default:
	      Error("bentuk perintah detak_waktu salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');




    if(n != 3) {
      Error("parameter detak_waktu tidak lengkap");
    } else {
	  //printf("detak_waktu x %d\n", x);
	  //printf("win type %d\n", tmpdat.datatype );
	  //printf("Jenis Fungsi %d\n", type_func);

      dat = (TimerData *)malloc(sizeof(TimerData));

	  if(type_func == 1) {
	    // // Do Object Function
		//  printf("aksi : object\n");

		memset(&dat->sub_name,'\0', sizeof(dat->sub_name));
        strcpy(dat->sub_name , sub_name);
		memset(&dat->param_source,'\0', sizeof(dat->param_source));
        strcpy(dat->param_source , param_source);
		memset(&dat->currentClass,'\0', sizeof(dat->currentClass));
        strcpy(dat->currentClass , currentClass);

		dat->posSub     = posLyrSub;
		dat->posSubBack = posLyrSubBack;

		dat->valdat     = valdat;
		dat->tmpdat     = tmpdat;
		dat->widget     = aksidat.widget;

        if(tmpdat.datatype == 40 || tmpdat.datatype == 0) {
            g_timeout_add(x, (GSourceFunc) Do_Detak_Waktu, (gpointer) dat);
		} else {
          Error("parameter pada kode perintah detak_waktu salah");
		}


	  } else if(type_func == 0) {
	    // // Do General Function
		//  printf("aksi : general\n");

		memset(&dat->sub_name,'\0', sizeof(dat->sub_name));
        strcpy(dat->sub_name , sub_name);
		memset(&dat->param_source,'\0', sizeof(dat->param_source));
        strcpy(dat->param_source , param_source);
		memset(&dat->currentClass,'\0', sizeof(dat->currentClass));
        strcpy(dat->currentClass , currentClass);

		dat->posSub     = posLyrSub;
		dat->posSubBack = posLyrSubBack;

		dat->valdat     = valdat;
		dat->tmpdat     = tmpdat;
		dat->widget     = aksidat.widget;

		// printf("aksi, deep %d pos %d \n", lyr_sub_deep, posLyrSub);

        if(tmpdat.datatype == 40 || tmpdat.datatype == 0) {
            //printf("start g_timeout_add..\n");
            g_timeout_add(x, (GSourceFunc) Do_Detak_Waktu, (gpointer) dat);
		} else {
          Error("parameter pada kode perintah detak_waktu salah");
		}


	  } // end (type_func)

    }

	ungetlex();

}

