// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2012
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyAksi_SiapPrint ()
{
  int  type_func = 0; // 0: general function , 1: object function
  int  point = 0;
  int  n=0, i=0, j=0;

  long idx=0;                           // array index
  int  tmp_deep=0;


  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];
  char   dat_c[MAX_STRING_LEN];
  char   dat_d[MAX_STRING_LEN];
  
  char   tmp_str[MAX_STRING_LEN];

  char sub_name[MAX_STRING_LEN],
       sub_param[MAX_STRING_LEN],
       sub_tmpparam[MAX_STRING_LEN];

  char get_param[MAX_STRING_LEN],
       orig_param[MAX_STRING_LEN],
       param_source[MAX_STRING_LEN * 2];

  VAL_LABEL valdat,valdat2,tmpdat, tmpdat2;
  VAL_LABEL aksidat;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  char   *sub_tmpstring=NULL;
  char   *sub_tmpstring2=NULL;

  char   logMsg[MAX_STRING_LEN];
  char   tmpMsg[MAX_STRING_LEN];


  AksiPrintData *dat=NULL;
  // GtkPrintOperationResult res;


  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  memset(&dat_c, '\0', sizeof(dat_c));
  memset(&dat_d, '\0', sizeof(dat_d));

  memset(&sub_name, '\0', sizeof(sub_name));
  memset(&sub_param, '\0', sizeof(sub_param));
  memset(&sub_tmpparam, '\0', sizeof(sub_tmpparam));

  memset(&get_param, '\0', sizeof(get_param));
  memset(&orig_param, '\0', sizeof(orig_param));
  memset(&param_source, '\0', sizeof(param_source));

  memset(&aksidat, '\0', sizeof(aksidat));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&logMsg, '\0', sizeof(logMsg));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  sub_tmpstring  = NULL;
  sub_tmpstring2 = NULL;


  // printf("aksi siap cetak...\n");

  n = 0;
  tmp_deep = sub_deep;

	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  // printf("getlex type : %d\n", lex.type);

	  switch( lex.type )
	    {
   
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

			  if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                aksidat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                aksidat = expression();
              }

              // printf("n %d , aksidat type %d\n", n, aksidat.datatype);

              if(aksidat.datatype == 40) { // Widget (not used)
                if(n == 0) {
				  tmpdat.widget   = valdat.widget;
                  tmpdat.datatype = 40;
				  tmpdat.GUItype  = valdat.GUItype;
				} 
			  } else if(aksidat.datatype == 90) { // Print Ope
                if(n == 0) {
				  // printf("get print_ope \n");
				  tmpdat2.gtk_print_ope   = aksidat.gtk_print_ope;
                  tmpdat2.datatype = 90;
				  tmpdat2.GUItype  = aksidat.GUItype;
				} 
			  } else {
                Error("bentuk perintah aksi_siap_cetak salah");
			  }

	      break;


	    case TYPE_SYM:
          /* *******************   call function ********************  */
          if( lex.detail.symbol == '&' )  {
            // printf("Aksi_Fungsi subroutine, deep %d\n", sub_deep);

            memset(&sub_name, '\0', sizeof(sub_name));
            memset(&sub_param, '\0', sizeof(sub_param));
            memset(&sub_tmpparam, '\0', sizeof(sub_tmpparam));

            memset(&get_param, '\0', sizeof(get_param));
            memset(&orig_param, '\0', sizeof(orig_param));
            memset(&param_source, '\0', sizeof(param_source));

            getlex();
			// printf("& getlex lex type: %d\n", lex.type);

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
			    // check if sub inside sub ...
				if(sub_deep > 0) {
				  tmp_deep = sub_deep;
				  sub_deep = 0;
                  memset(&valdat, '\0', sizeof(valdat));
                  valdat.val = -1;
                  valdat = ValLabel( sub_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

				  if( valdat.val == -1 ) {
                    Error("SUB tidak ditemukan");
				  }
				}
              } else {
                
				//printf("SUB ada : %s\n", sub_name);
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
				// printf("lex type: %d\n", lex.type);

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
                  sprintf(tmp_str, "%li", lex.detail.num);
                  strcat(sub_param, tmp_str);
                }
                else if(lex.type == TYPE_DBL) {
                  sprintf(tmp_str, "%f", lex.detail.dblnum);
                  strcat(sub_param, tmp_str);
				}
                else if(lex.type == TYPE_ARRAY) {
			      sprintf(tmp_str, "%s", lex.detail.array_str);
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
                  else if(lex.type == TYPE_ARRAY) {
			        sprintf(tmp_str, "%s", lex.detail.array_str);
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

              // printf(" sub get param: %s\n", sub_param);
              // printf(" sub orig param: %s\n", valdat.sub_param);

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

              // printf("subtitute param: %s\n", sub_tmpparam);

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
	      Error("bentuk perintah aksi_siap_cetak salah");
	    }

        n++;

	    getlex(); // pass comma

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

    sub_deep = tmp_deep;

	// printf("num param : %d , deep : %d \n", n, sub_deep);

    if(n != 2) {
      Error("parameter aksi_siap_cetak tidak lengkap");
    } else {
	  // printf("Aksi_Siap_Cetak tmpdat type %d GUItype %d\n", tmpdat.datatype, tmpdat.GUItype);
	  // printf("tmpdat2 type %d\n", tmpdat2.datatype);
	  // printf("Jenis Fungsi %d\n", type_func);

      dat = (AksiPrintData *)malloc(sizeof(AksiPrintData));

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

		strcpy(dat->dat_a  , dat_a);
		strcpy(dat->dat_b  , dat_b);
		strcpy(dat->dat_c  , dat_c);

        if(tmpdat2.datatype == 90) {
		    // printf("* call Do_AksiSiapPrint.......\n");

			// printf("aksi sub_name: %s\n", dat->sub_name);
			// printf("aksi param_source: %s\n", dat->param_source);
			// printf("aksi currentClass: %s\n", dat->currentClass);
 	        // printf("aksi posSub: %d\n", dat->posSub);
	        // printf("aksi posSubBack: %d\n", dat->posSubBack);

		  // call begin_print
          g_signal_connect (tmpdat2.gtk_print_ope, "begin_print", G_CALLBACK (Do_AksiSiapPrint), (gpointer)dat );


		} else {
          Error("parameter pada kode perintah aksi_siap_cetak salah 1");
		}


	  } else if(type_func == 0) {
	    // Do General Function
		// printf("aksi : general, datatype %d\n", tmpdat2.datatype);

		memset(&dat->sub_name,'\0', sizeof(dat->sub_name));
        strcpy(dat->sub_name , sub_name);
		memset(&dat->param_source,'\0', sizeof(dat->param_source));
        strcpy(dat->param_source , param_source);
		memset(&dat->currentClass,'\0', sizeof(dat->currentClass));
        strcpy(dat->currentClass , currentClass);

		dat->posSub     = posLyrSub;
		dat->posSubBack = posLyrSubBack;
		dat->valdat     = valdat;

		// printf("aksi_fungsi, deep %d pos %d \n", lyr_sub_deep, posLyrSub);

        if(tmpdat2.datatype == 90) {
		    // printf("* call Do_AksiSiapPrint.......\n");

			// printf("aksi sub_name: %s\n", dat->sub_name);
			// printf("aksi param_source: %s\n", dat->param_source);
			// printf("aksi currentClass: %s\n", dat->currentClass);
 	        // printf("aksi posSub: %d\n", dat->posSub);
	        // printf("aksi posSubBack: %d\n", dat->posSubBack);

		  // call begin_print
          g_signal_connect (tmpdat2.gtk_print_ope, "begin_print", G_CALLBACK (Do_AksiSiapPrint), (gpointer)dat );

		} else {
          Error("parameter pada kode perintah aksi_siap_cetak salah 0");
		}


	  } // end (type_func)

    }

	ungetlex();

}


