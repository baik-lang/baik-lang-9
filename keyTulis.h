// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// 2014-08-27

extern void writeLog(char msg[MAX_STRING_LEN]);

void keyTulis ()
{
  char ident[MAX_IDENT_LEN];
  int  i=0;

  char   dat_a[MAX_STRING_LEN];
  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&tmp_str, '\0', sizeof(tmp_str));
  
  memset(&ident, '\0', sizeof(ident));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


  // printf("tulis ...renban = %d\n", renban);

      do{
	    getlex();
	    switch( lex.type )
 	      {
	        case TYPE_STR:
              if(lex.detail.string  != NULL && strlen(lex.detail.string) > 0) {
	            printf( "%s", lex.detail.string );
              }
	        break;
	    
            case TYPE_ARRAY:
              // printf("write array\n");

              if(strlen(lex.detail.array_str) > 0) {
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

                     #ifdef WIN32
                      #ifndef S_SPLINT_S
                      sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                      #else
                      snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                      #endif
                     #else
                     snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                     #endif

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

		// get real value of array
		// printf("search array: %s\n", valdat.array_name);
                if(currentClass != NULL && strlen(currentClass) > 0) {
		  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                   #else
                   snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                   #endif
                  #else
                  snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                  #endif

                  valdat2 = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
				} else {
                  valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
				}
                // ltoa(idx, valdat2.array_idx, 10);
		sprintf(valdat2.array_idx, "%li", idx);

		//printf("idx %d\n", idx);
		//printf("max kapasitas %d\n", valdat2.array_max);
		if(valdat2.array_max <= 0) {
                  printf("nil ");  // Untaian nil / terhapus
		} else {
                  if(idx < 0 || idx > (valdat2.array_max-1))
                    Error("ukuran Untaian tidak sesuai kapasitas");
		}

		// printf("get valdat2 type: %d, val %d\n", valdat2.datatype, valdat2.val);
                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

		  if(get_int_array(valdat2, idx) == '\r') {
                    printf("nil");
		  } else {
                    printf("%d", get_int_array(valdat2, idx) );
		  }

                } else if (valdat2.datatype == 7) {
                  if(valdat2.array_d == '\0')
                    Error("ukuran Untaian belum terdefinisi: pecahan");

                  #ifndef S_SPLINT_S

		  if(get_dbl_array(valdat2, idx) == '\r') {
                    printf("nil");
		  } else {
                    printf("%f", get_dbl_array(valdat2, idx) );
		  }

                  #endif

                } else if (valdat2.datatype == 8) {
                  // printf("tulis arry string\n");
                  if(valdat2.array_s == '\0')
                    Error("ukuran Untaian belum terdefinisi: kata");

		  if(!get_str_array(valdat2, idx, (char *)&tmp_str)) {
                    printf("nil %s", tmp_str);
		  } else {
                    printf("%s", tmp_str );
		  }

                } else if (valdat2.datatype == 10) {
                  if(valdat2.long_str != NULL) {
                    printf("%s", valdat2.long_str[idx]);
                  }
                } else {
                  printf("");
                }
                

             }


            break;

	    case TYPE_NUM:
	      printf( "%li", lex.detail.num );
	      break;

	    case TYPE_DBL:
	      printf( "%f", lex.detail.dblnum );
	      break;

	    case TYPE_OBJECT:
			  // printf("tulis obj: %s\n", lex.detail.object_str);
              checkInstanceValidation(lex.detail.object_str);

	    case TYPE_IDENT:
              // printf("tulis ident: %s\n", lex.detail.ident);
              // show params inside memori
              // varstack_printData();

              if(currentClass != NULL && strlen(currentClass) > 0) {

                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                #endif

		        // printf("tulis: construct class var: %s , deep %d\n", class_tmpvar, class_sub_deep);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {
                ungetlex();
                valdat = expression();
              }

              //printf(" get tulis ident datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.str != NULL && strlen(valdat.str) > 0 && valdat.datatype == 3) {
                for(i=0; i < (int)strlen(valdat.str); i++)
                  printf("%c" , valdat.str[i] );

              // -----------------------------------------------------------
              #ifdef USE_GTK2
			  } else if(valdat.GUItype == 16) {
				  // GTK Color
				   printf(" R%d G%d B%d" , valdat.color.red , valdat.color.green, valdat.color.blue);

			  } else if(valdat.str2 != NULL && strlen(valdat.str2) > 0 && valdat.datatype == 41) {
                // special case for getting text from Kertas
				  g_print("%s", valdat.str2);

			  } else if(valdat.datatype == 45 && valdat.isGUI == 1) {
                // special case for getting text from Tabel
				  printf("%s", valdat.str2);

			  } else if(valdat.datatype == 46 && valdat.isGUI == 1) {
                // special case for getting text from Pixbuf
				  //printf("%s", valdat.str2);
				  printf("%s" , valdat.tblcoltype );

			  } else if(valdat.datatype == 50) {
                // special case for getting text from TeksTerpilih
				  printf("%s", valdat.str2);

			  } else if(valdat.GUItype == 15) { // font dialog
				  printf("%s" , valdat.str );

			  } else if(valdat.GUItype == 16) { // color dialog
				  printf("Merah:%d Hijau:%d Biru:%d" , valdat.color.red , valdat.color.green, valdat.color.blue);

			  } else if(valdat.GUItype == 17) { // file dialog
				  printf("nama arsip: %s\n" , valdat.filename );
				  printf("nama map: %s" , valdat.folder );
              #endif
              // -----------------------------------------------------------
              #ifdef USE_GTK3
			  }
			  else if (valdat.GUItype == 16) {
				  // GTK Color
				  printf(" R%d G%d B%d", valdat.color.red, valdat.color.green, valdat.color.blue);

			  }
			  else if (valdat.str2 != NULL && strlen(valdat.str2) > 0 && valdat.datatype == 41) {
				  // special case for getting text from Kertas
				  g_print("%s", valdat.str2);

			  }
			  else if (valdat.datatype == 45 && valdat.isGUI == 1) {
				  // special case for getting text from Tabel
				  printf("%s", valdat.str2);

			  }
			  else if (valdat.datatype == 46 && valdat.isGUI == 1) {
				  // special case for getting text from Pixbuf
				  //printf("%s", valdat.str2);
				  printf("%s", valdat.tblcoltype);

			  }
			  else if (valdat.datatype == 50) {
				  // special case for getting text from TeksTerpilih
				  printf("%s", valdat.str2);

			  }
			  else if (valdat.GUItype == 15) { // font dialog
				  printf("%s", valdat.str);

			  }
			  else if (valdat.GUItype == 16) { // color dialog
				  printf("Merah:%d Hijau:%d Biru:%d", valdat.color.red, valdat.color.green, valdat.color.blue);

			  }
			  else if (valdat.GUItype == 17) { // file dialog
				  printf("nama arsip: %s\n", valdat.filename);
				  printf("nama folder: %s", valdat.folder);
             #endif
			 // -----------------------------------------------------------

              } else if(valdat.datatype == 1) {
                printf("%f" , valdat.floatdata );
              } else if(valdat.datatype == 0) {
                printf("%li" , valdat.val );
              } else if(valdat.datatype == 10) {
                /* printf("Tulis Long Str %d\n", valdat.array_max); */
                if(valdat.long_str != NULL) {
                  for(i=0; i <valdat.array_max ; i++) {

                    if(valdat.long_str[i] != NULL) {
                      memset(dat_a, '\0', sizeof(dat_a));
                      strcpy(dat_a, valdat.long_str[i]);
                      printf("%s\n", dat_a);
                    }

                  }
                }
                /* printf("Tulis Long Str OK\n"); */
              } else if(valdat.datatype == 12) {
                printf("%li" , valdat.val );
              } else if(valdat.datatype < 0) {
                printf("nil ");                
              } else {
                // printf("%d" , valdat.val );
              }


	      break;

	    default:
	      Error("kode perintah TULIS salah");
	    }
	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

	fflush( stdout );

	ungetlex();

  // printf("clearing ... \n");

  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);

  // printf("clearing ... 1 \n");

  if(valdat.filename != NULL)
    valdat.filename = NULL;
  if(valdat.folder != NULL)
    valdat.folder = NULL;
  if(valdat.filedata != NULL)
    valdat.filedata = NULL;
  if(valdat.long_str != NULL)
    valdat.long_str = NULL;

  // printf("clearing ... 2 \n");

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  // printf("clearing ... 3 \n");

  if(tmpdat.filename != NULL)
    tmpdat.filename = NULL;
  if(tmpdat.folder != NULL)
    tmpdat.folder = NULL;
  if(tmpdat.filedata != NULL)
    tmpdat.filedata = NULL;
  if(tmpdat.long_str != NULL)
    tmpdat.long_str = NULL;

  // printf("clearing ... 4 \n");

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

  // printf("clearing ... 5 \n");

  if(valdat2.filename != NULL)
    valdat2.filename = NULL;
  if(valdat2.folder != NULL)
    valdat2.folder = NULL;
  if(valdat2.filedata != NULL)
    valdat2.filedata = NULL;
  if(valdat2.long_str != NULL)
    valdat2.long_str = NULL;

  // printf("clearing ... 6 \n");

  if(valdat2.left != NULL)
    free(valdat2.left);
  if(valdat2.right != NULL)
    free(valdat2.right);
  if(valdat2.pnext != NULL)
    free(valdat2.pnext);

  // printf("clearing ... OK \n");

}

void keyTulisRinci ()
{
  char ident[MAX_IDENT_LEN];
  int  i=0;

  char   dat_a[MAX_STRING_LEN];
  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&tmp_str, '\0', sizeof(tmp_str));
  
  memset(&ident, '\0', sizeof(ident));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


      do{
	    getlex();
	    switch( lex.type )
 	      {
	        case TYPE_STR:
              if(lex.detail.string  != NULL && strlen(lex.detail.string) > 0) {
	            printf( "%s", lex.detail.string );
              }
	        break;
	    
            case TYPE_ARRAY:
              // printf("write array\n");

              if(strlen(lex.detail.array_str) > 0) {
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

                     #ifdef WIN32
                      #ifndef S_SPLINT_S
                      sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                      #else
                      snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                      #endif
                     #else
                     snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                     #endif

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

		// get real value of array
		// printf("search array: %s\n", valdat.array_name);
                if(currentClass != NULL && strlen(currentClass) > 0) {
		  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                   #else
                   snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                   #endif
                  #else
                  snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                  #endif

                  valdat2 = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
		} else {
                  valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
		}

                // ltoa(idx, valdat2.array_idx, 10);
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx);
                 #else
                 snprintf(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx);
                 #endif
                #else
                snprintf(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx);
                #endif

		//printf("idx %d\n", idx);
		//printf("max kapasitas %d\n", valdat2.array_max);

		if(valdat2.array_max <= 0) {
                  printf("nil ");  // Untaian nil / terhapus
		} else {
                  if(idx < 0 || idx > (valdat2.array_max-1))
                    Error("ukuran Untaian tidak sesuai kapasitas");
                }

		// printf("get valdat2 type: %d, val %d\n", valdat2.datatype, valdat2.val);

                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  #ifndef S_SPLINT_S

		  if(get_int_array(valdat2, idx) == '\r') {
                    printf("nil");
		  } else {
                    printf("%d", get_int_array(valdat2, idx) );
		  }

                  #endif

                } else if (valdat2.datatype == 7) {
                  if(valdat2.array_d == '\0')
                    Error("ukuran Untaian belum terdefinisi: pecahan");

                  #ifndef S_SPLINT_S

		  if(get_dbl_array(valdat2, idx) == '\r') {
                    printf("nil");
		  } else {
                    printf("%.18f", get_dbl_array(valdat2, idx) );
		  }

                  #endif

                } else if (valdat2.datatype == 8) {
                  // printf("tulis arry string\n");

                  #ifndef S_SPLINT_S

                  if(valdat2.array_s == '\0')
                    Error("ukuran Untaian belum terdefinisi: kata");

                  #endif

		  if(!get_str_array(valdat2, idx, (char *)&tmp_str)) {
                    printf("nil %s", tmp_str);
		  } else {
                    printf("%s", tmp_str );
		  }

                } else if (valdat2.datatype == 10) {
                  if(valdat2.long_str != NULL) {
                    printf("%s", valdat2.long_str[idx]);
                  }
                } else {
                  printf("");
                }
                

             }


            break;

	    case TYPE_NUM:
	      printf( "%li", lex.detail.num );
	      break;

	    case TYPE_DBL:
	      printf( "%.18f", lex.detail.dblnum );
	      break;

	    case TYPE_OBJECT:
              // printf("tulis obj: %s\n", lex.detail.object_str);
              checkInstanceValidation(lex.detail.object_str);

	    case TYPE_IDENT:
	      // printf("tulis ident: %s\n", lex.detail.ident);
	      // show params inside memori
	      // varstack_printData();

              if(currentClass != NULL && strlen(currentClass) > 0) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                  #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                #endif

		// printf("tulis: construct class var: %s , deep %d\n", class_tmpvar, class_sub_deep);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {
                // ungetlex();
                // valdat = expression();
                valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              // printf(" ident datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.str != NULL && strlen(valdat.str) > 0 && valdat.datatype == 3) {
                for(i=0; i < (int)strlen(valdat.str); i++)
                  printf("%c" , valdat.str[i] );
              } else if(valdat.datatype == 1) {
                printf("%.18f" , valdat.floatdata );
              } else if(valdat.datatype == 0) {
                printf("%li" , valdat.val );
              } else if(valdat.datatype == 10) {
                /* printf("Tulis Long Str %d\n", valdat.array_max); */
                if(valdat.long_str != NULL) {
                  for(i=0; i <valdat.array_max ; i++) {
                    if(valdat.long_str[i] != NULL) {

                      memset(dat_a, '\0', sizeof(dat_a));
                      strcpy(dat_a, valdat.long_str[i]);
                      printf("%s\n", dat_a);

                    }
                  }
                }
                /* printf("Tulis Long Str OK\n"); */
              } else if(valdat.datatype < 0) {
                printf("nil ");
              } else {
                // printf("%d" , valdat.val );
              }


	      break;

	    default:
	      Error("kode perintah TULIS_RINCI salah");
	    }
	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

	fflush( stdout );

	ungetlex();

  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);


  if(valdat.filename != NULL)
    free(valdat.filename);
  if(valdat.folder != NULL)
    free(valdat.folder);
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

  if(valdat2.filename != NULL)
    free(valdat2.filename);
  if(valdat2.folder != NULL)
    free(valdat2.folder);
  if(valdat2.filedata != NULL)
    free(valdat2.filedata);
  if(valdat2.long_str != NULL)
    free(valdat2.long_str);

  if(valdat2.left != NULL)
    free(valdat2.left);
  if(valdat2.right != NULL)
    free(valdat2.right);
  if(valdat2.pnext != NULL)
    free(valdat2.pnext);

}

void keyTulisLog ()
{

  char ident[MAX_IDENT_LEN];

  char logMsg[MAX_STRING_LEN * 2],
       tmpMsg[MAX_STRING_LEN * 2];

  int  i=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  VAL_LABEL valdat, valdat2, tmpdat, valdat0;
  
  int    idx=0;                           // array index

  char   get_name[MAX_STRING_LEN];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&valdat0, '\0', sizeof(valdat0));

  memset(&get_name, '\0', sizeof(get_name));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  
  memset(&ident, '\0', sizeof(ident));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));
  memset(&logMsg, '\0', sizeof(logMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:

              if(lex.detail.string  != '\0' && strlen(lex.detail.string) > 0) {
                strcat(logMsg, lex.detail.string );
              } else {
                strcat(logMsg, "");
              }

	      break;


            case TYPE_ARRAY:
              /* printf("write array\n"); */

              if(strlen(lex.detail.array_str) > 0) {
                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(currentClass != NULL && strlen(currentClass) > 0) {
                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                   #else
                   snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                   #endif
                  #else
                  snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                  #endif

                  //printf("construct class var: %s\n", class_tmpvar);
                  memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));
                  strcpy(valdat.array_name, class_tmpvar);
                  // printf("tulis ARRAY name: %s\n", valdat.array_name);

                  if(!isdigit(valdat.array_idx[0])) {
                    memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                    #ifdef WIN32
                     #ifndef S_SPLINT_S
                     sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                     #else
                     snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                     #endif
                    #else
                    snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                    #endif

                    //printf("construct class var: %s\n", class_tmpvar);
                    memset(&valdat.array_idx[0], '\0', sizeof(valdat.array_idx));
                    strcpy(valdat.array_idx, class_tmpvar);
                  }
                }

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

                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
                 #else
                 snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
                 #endif
                #else
                snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
                #endif

                /*
                printf("log show arr datatype %d\n", valdat.datatype);
                
                printf("log show arr ALL : %s\n", valdat.array_str);
                printf("log show arr name : %s\n", valdat.array_name);
                printf("log show arr idx : %s\n", valdat.array_idx);
                printf("log show arr max : %d\n", valdat.array_max);
                */

                if(idx < 0 || idx > (valdat.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

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

                } else {
                  strcpy(tmpMsg, "Nil");
                }
              }
	          strcat(logMsg, tmpMsg);

              break;
	    
	    case TYPE_OBJECT:
              checkInstanceValidation(lex.detail.object_str);
	    case TYPE_IDENT:
	    case TYPE_NUM:

              //printf("curr class : %s\n", currentClass);
              //printf("datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(currentClass != NULL && strlen(currentClass) > 0) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                #endif
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.str != NULL && strlen(valdat.str) > 0 && valdat.datatype == 3 && valdat.isGUI != 1) {
                strcpy(tmpMsg, valdat.str );

              // -----------------------------------------------------------
              #ifdef USE_GTK2
		  } else if(valdat.GUItype == 16) {
		  // GTK Color
                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(tmpMsg, sizeof(tmpMsg),"Merah:%d Hijau:%d Biru:%d" , valdat.color.red , valdat.color.green, valdat.color.blue);
                   #else
                   snprintf(tmpMsg, sizeof(tmpMsg),"Merah:%d Hijau:%d Biru:%d" , valdat.color.red , valdat.color.green, valdat.color.blue);
                   #endif
                  #else
                  snprintf(tmpMsg, sizeof(tmpMsg),"Merah:%d Hijau:%d Biru:%d" , valdat.color.red , valdat.color.green, valdat.color.blue);
                  #endif

		  } else if(valdat.str2 != NULL && strlen(valdat.str2) > 0 && valdat.datatype == 41) {
                // special case for getting text from Kertas
	           strcpy(tmpMsg, valdat.str2 );

		  } else if(valdat.datatype == 45 && valdat.isGUI == 1) {
                // special case for getting text from Tabel
		  strcpy(tmpMsg, valdat.str2 );

		  } else if(valdat.datatype == 46 && valdat.isGUI == 1) {
                // special case for getting text from Pixbuf
                    strcpy(tmpMsg, valdat.tblcoltype );

		  } else if(valdat.datatype == 50) {
                // special case for getting text from TeksTerpilih
		    strcpy(tmpMsg, valdat.str2 );

		  } else if(valdat.GUItype == 15) { // font dialog
	            strcpy(tmpMsg, valdat.str );

		  } else if(valdat.GUItype == 17) { // file dialog
	            strcpy(tmpMsg, valdat.filename );
              #endif
              // -----------------------------------------------------------
             #ifdef USE_GTK3
		  }
		  else if (valdat.GUItype == 16) {
			  // GTK Color
          #ifdef WIN32
          #ifndef S_SPLINT_S
			  sprintf_s(tmpMsg, sizeof(tmpMsg), "Merah:%d Hijau:%d Biru:%d", valdat.color.red, valdat.color.green, valdat.color.blue);
          #else
			  snprintf(tmpMsg, sizeof(tmpMsg), "Merah:%d Hijau:%d Biru:%d", valdat.color.red, valdat.color.green, valdat.color.blue);
          #endif
          #else
			  snprintf(tmpMsg, sizeof(tmpMsg), "Merah:%d Hijau:%d Biru:%d", valdat.color.red, valdat.color.green, valdat.color.blue);
          #endif

		  }
		  else if (valdat.str2 != NULL && strlen(valdat.str2) > 0 && valdat.datatype == 41) {
			  // special case for getting text from Kertas
			  strcpy(tmpMsg, valdat.str2);

		  }
		  else if (valdat.datatype == 45 && valdat.isGUI == 1) {
			  // special case for getting text from Tabel
			  strcpy(tmpMsg, valdat.str2);

		  }
		  else if (valdat.datatype == 46 && valdat.isGUI == 1) {
			  // special case for getting text from Pixbuf
			  strcpy(tmpMsg, valdat.tblcoltype);

		  }
		  else if (valdat.datatype == 50) {
			  // special case for getting text from TeksTerpilih
			  strcpy(tmpMsg, valdat.str2);

		  }
		  else if (valdat.GUItype == 15) { // font dialog
			  strcpy(tmpMsg, valdat.str);

		  }
		  else if (valdat.GUItype == 17) { // file dialog
			  strcpy(tmpMsg, valdat.filename);
         #endif

              } else if(valdat.datatype == 1) {

                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(tmpMsg, sizeof(tmpMsg),"%f" , valdat.floatdata );
                 #else
                 snprintf(tmpMsg, sizeof(tmpMsg),"%f" , valdat.floatdata );
                 #endif
                #else
                snprintf(tmpMsg, sizeof(tmpMsg),"%f" , valdat.floatdata );
                #endif

              } else if(valdat.datatype == 0) {
                sprintf(tmpMsg, "%li" , valdat.val );

                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(tmpMsg, sizeof(tmpMsg),"%li" , valdat.val );
                 #else
                 snprintf(tmpMsg, sizeof(tmpMsg),"%li" , valdat.val );
                 #endif
                #else
                snprintf(tmpMsg, sizeof(tmpMsg),"%li" , valdat.val );
                #endif

              } else if(valdat.datatype == 10) {
                /* printf("Tulis Long Str %d\n", valdat.array_max); */
                if(valdat.long_str != NULL) {
                  for(i=0; i <valdat.array_max ; i++) {
                    if(valdat.long_str[i] != NULL) {

                      memset(dat_a, '\0', sizeof(dat_a));
                      strcpy(dat_a, valdat.long_str[i]);
                      strcpy(tmpMsg, dat_a);

                    }
                  }
                }
                /* printf("Tulis Long Str OK\n"); */

              } else {
                #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(tmpMsg, sizeof(tmpMsg),"%li", valdat.val );
                   #else
                   snprintf(tmpMsg, sizeof(tmpMsg),"%li", valdat.val );
                   #endif
                #else
                  snprintf(tmpMsg, sizeof(tmpMsg),"%li", valdat.val );
                #endif
              }
	      strcat(logMsg, tmpMsg);

	      break;

	    default:
	      Error("kode perintah TULISLOG salah");
	    }

	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

    // printf("log : %s\n", logMsg);
    writeLog(logMsg);
    // printf("log write OK \n");

    ungetlex();

}



