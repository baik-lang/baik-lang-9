// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// Last Update : 10-10-2015


VAL_LABEL funcArsip ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int  n=0, i=0;
  long  idx=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM || lex.type == TYPE_DBL) {
             Error("FILE: masukan data salah");
           } else if(lex.type == TYPE_STR) {
             if(n == 0) {
               strcpy(dat_a, lex.detail.string);
             } else
             if(n == 1) {
               strcpy(dat_b, lex.detail.string);
             }
           } else if(lex.type == TYPE_ARRAY) {
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

                 /* read data */
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

                 if(idx < 0 || idx > MAX_ARRAY)
                   Error("ukuran Untaian tidak sesuai kapasitas");

                 if(valdat.datatype == 8 && valdat.array_s != '\0') {
                   if(valdat.array_s == '\0')
                     Error("tulis_soket: ukuran Untaian belum terdefinisi");

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

					}

				  }

                   if(n == 0) {
                     strcpy(dat_a, TmpStrBox.str.mystring);
                   } else
                   if(n == 1) {
                     strcpy(dat_b, TmpStrBox.str.mystring);
                   }

                 }

               }

           } else {

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
               valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 3) {          // get from IDENT
               if(n == 0) {
                 strcpy(dat_a, valdat.str);
               } else
               if(n == 1) {
                 strcpy(dat_b, valdat.str);
               }
             }
        	 else if(valdat.GUItype == 17) {     // get from File Dialog
               if(n == 0) {
				 strcpy(dat_a, valdat.filename);
               } 
		     }

           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=2) {
          Error("FILE: masukan data salah");
        } else {
          
          // printf("a: %s\n", dat_a); 
          // printf("b: %s\n", dat_b); 
          

          datx.isFileOpen = 1;
          datx.datatype = 2;                   /* FILE  */

		  strcpy(datx.sub_file, dat_a);        // keep filename (?) - prehab

          if(dat_b[0] == 'b') {                /* baca  */
            // printf("file: baca\n"); 
            datx.filedata = fopen(dat_a, "r");
            datx.isFileOpen = 1;

			// test
			//while (fscanf(datx.filedata, "%c", &x1) ==1) printf("%c", x1);

          } else if(dat_b[0] == 't') {         /* tulis */
            // printf("file: tulis\n"); 
            datx.filedata = fopen(dat_a, "w");
            datx.isFileOpen = 1;
          } else if(dat_b[0] == 's') {         /* sambung */
            // printf("file: sambung\n"); 
            datx.filedata = fopen(dat_a, "a");
            datx.isFileOpen = 1;
          } else {                             /* other */
            Error("FILE: tipe pembukaan file tidak dipahami");
          }

        }
        /*
        printf("file datatype: %d\n", datx.datatype); 
        printf("file open: %d\n", datx.isFileOpen); 
        */


  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

  return datx;
}

// read data from file per line
VAL_LABEL funcBacaArsip ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;
 



  FILE    *tmpfile=NULL;

  char   dat_a[MAX_STRING_LEN * 4]; // 1 line max 1KB

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  datx.val = 0;
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&dat_a, '\0', sizeof(dat_a));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        getlex();
        // printf("BACA ARASIP %s\n", lex.detail.string);

        if(lex.type == TYPE_IDENT) {
        
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
           valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
         } else {
           valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
         }

         // printf("get type %d\n", valdat.datatype);
         if(valdat.datatype == 2) {
           tmpfile = valdat.filedata;
           fgets(dat_a, (int)sizeof(dat_a), tmpfile);

           datx.datatype = 3;
           strcpy(datx.str, dat_a);

           // printf("fgets str %s", dat_a);

           if(dat_a != NULL && strlen(dat_a) > 0) {
             datx.val = 1;
           } else {
             datx.val = 0;
           }

         }
        }

	// printf("val %d\n", datx.val);


  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

  return datx;
}

VAL_LABEL funcApakahArsip ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  long  idx=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         strcpy(datx.str, "");

         if(lex.type == TYPE_NUM) {
           Error("APAKAH_ARSIP: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("APAKAH_ARSIP: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           #ifdef WINDOWS
           datx.val = win_node_isfile(lex.detail.string);
           #else
           datx.val = node_isfile(lex.detail.string);
           #endif
           datx.datatype = 0;

         } else if(lex.type == TYPE_ARRAY) {
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

              /* read data */
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

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 8 && valdat.array_s != '\0') {
                if(valdat.array_s == '\0')
                  Error("APAKAH_ARSIP: ukuran Untaian belum terdefinisi");

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

					}

				  }


                /* printf("%d", valdat.array_i[idx]); */
                #ifdef WINDOWS
                datx.val = win_node_isfile(TmpStrBox.str.mystring);
                #else
                datx.val = node_isfile(TmpStrBox.str.mystring);
                #endif

                datx.datatype = 0;

              } else if (valdat.datatype == 10) {
                #ifdef WINDOWS
                datx.val = win_node_isfile(valdat.long_str[idx]);
                #else
                datx.val = node_isfile(valdat.long_str[idx]);
                #endif
                datx.datatype = 0;

              } else {
                Error("APAKAH_ARSIP: masukan data salah");
              }
           }

         } else {
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
             valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 3) {
             #ifdef WINDOWS
             datx.val = win_node_isfile(valdat.str);
             #else
             datx.val = node_isfile(valdat.str);
             #endif
             datx.datatype = 0;
           } else {
             Error("APAKAH_ARSIP: masukan data salah");
           }
         }
         datx.datatype = 0;


  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

  return datx;
}


VAL_LABEL funcBesarArsip ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;


  long  idx=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("BESAR_ARSIP: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("BESAR_ARSIP: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           #ifdef WINDOWS
           win_node_size(lex.detail.string, (char *)&datx.str);
           #else
           strcpy(datx.str, node_size(lex.detail.string));
           #endif
           datx.datatype = 3;

         } else if(lex.type == TYPE_ARRAY) {
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

              /* read data */
              valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              // itoa(idx, valdat.array_idx, 10);
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
               #else
               snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
               #endif
              #else
              snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
              #endif

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 8 && valdat.array_s != '\0') {
                if(valdat.array_s == '\0')
                  Error("besar_arsip: ukuran Untaian belum terdefinisi");

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

					}

				  }

                /* printf("%d", valdat.array_i[idx]); */
                #ifdef WINDOWS
				  win_node_size( TmpStrBox.str.mystring, (char *)&datx.str );
                #else
				  strcpy(datx.str , node_size( TmpStrBox.str.mystring) );
                #endif


                datx.datatype = 3;

              } else if (valdat.datatype == 10) {
                #ifdef WINDOWS
                win_node_size(valdat.long_str[idx], (char *)&datx.str );
                #else
                strcpy(datx.str , node_size(valdat.long_str[idx]) );
                #endif
                datx.datatype = 3;

              } else {
                Error("BESAR_ARSIP: masukan data salah");
              }
           }

         } else {
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
             valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 3) {
             #ifdef WINDOWS
             win_node_size(valdat.str, (char *)&datx.str );
             #else
             strcpy(datx.str, node_size(valdat.str) );
             #endif
             datx.datatype = 3;
           } else {
             Error("BESAR_ARSIP: masukan data salah");
           }
         }

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

  return datx;
}

VAL_LABEL funcWaktuAksesArsip ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;


  long  idx=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("WAKTU_AKSES_ARSIP: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("WAKTU_AKSES_ARSIP: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           #ifdef WINDOWS
           win_node_accesstime(lex.detail.string, (char *)&datx.str );
           #else
           strcpy(datx.str, node_accesstime(lex.detail.string));
           #endif

           datx.datatype = 3;

         } else if(lex.type == TYPE_ARRAY) {
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

              /* read data */
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


              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");


              if(valdat.datatype == 8 && valdat.array_s != '\0') {
                if(valdat.array_s == '\0')
                  Error("WAKTU_AKSES_ARSIP: ukuran Untaian belum terdefinisi");

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

					}

				  }

                /* printf("%d", valdat.array_i[idx]); */
                #ifdef WINDOWS
                win_node_accesstime(TmpStrBox.str.mystring, (char *)&datx.str );
                #else
                strcpy(datx.str , node_accesstime(TmpStrBox.str.mystring) );
                #endif
                datx.datatype = 3;

              } else if (valdat.datatype == 10) {
                #ifdef WINDOWS
                win_node_accesstime(valdat.long_str[idx], (char *)&datx.str );
                #else
                strcpy(datx.str , node_accesstime(valdat.long_str[idx]) );
                #endif
                datx.datatype = 3;

              } else {
                Error("WAKTU_AKSES_ARSIP: masukan data salah");
              }
           }

         } else {
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
             valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 3) {
             #ifdef WINDOWS
             win_node_accesstime(valdat.str, (char *)&datx.str );
             #else
             strcpy(datx.str, node_accesstime(valdat.str) );
             #endif
             datx.datatype = 3;
           } else {
             Error("WAKTU_AKSES_ARSIP: masukan data salah");
           }
         }


  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

  return datx;
}


VAL_LABEL funcWaktuRubahArsip ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;


  long  idx=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("WAKTU_RUBAH_ARSIP: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("WAKTU_RUBAH_ARSIP: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           #ifdef WINDOWS
           win_node_modifytime(lex.detail.string, (char *)&datx.str);
           #else
           strcpy(datx.str, node_modifytime(lex.detail.string));
           #endif
           datx.datatype = 3;

         } else if(lex.type == TYPE_ARRAY) {
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

              /* read data */
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

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 8 && valdat.array_s != '\0') {
                if(valdat.array_s == '\0')
                  Error("WAKTU_RUBAH_ARSIP: ukuran Untaian belum terdefinisi");

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

					}

				  }

                /* printf("%d", valdat.array_i[idx]); */
                #ifdef WINDOWS
                win_node_modifytime(TmpStrBox.str.mystring, (char *)&datx.str);
                #else
                strcpy(datx.str , node_modifytime(TmpStrBox.str.mystring) );
                #endif

                datx.datatype = 3;

              } else if (valdat.datatype == 10) {
                #ifdef WINDOWS
                win_node_modifytime(valdat.long_str[idx], (char *)&datx.str);
                #else
                strcpy(datx.str , node_modifytime(valdat.long_str[idx]) );
                #endif
                datx.datatype = 3;

              } else {
                Error("WAKTU_RUBAH_ARSIP: masukan data salah");
              }
           }

         } else {
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
             valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 3) {
             #ifdef WINDOWS
             win_node_modifytime(valdat.str, (char *)&datx.str);
             #else
             strcpy(datx.str, node_modifytime(valdat.str) );
             #endif
             datx.datatype = 3;
           } else {
             Error("WAKTU_AKSES_ARSIP: masukan data salah");
           }
         }

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

  return datx;
}


// ////////////////////////////////////////////////////////////////////////////////////////////


#ifdef WINDOWS
#define FuncLoadFile(s,a) CreateFile((LPCTSTR)(s),(GENERIC_READ|GENERIC_WRITE),(FILE_SHARE_READ|FILE_SHARE_WRITE),NULL,OPEN_EXISTING,a,NULL)

#ifndef S_SPLINT_S
BOOL win_accesstime( LPSYSTEMTIME lpDate, LPCTSTR lpFileName ) {

  FILETIME ftDate;
  FILETIME lcDate;
  HANDLE hFile;

  if((hFile = FuncLoadFile(lpFileName,FILE_ATTRIBUTE_NORMAL)) != INVALID_HANDLE_VALUE ){
//  GetFileTime( hFile, &ftDate, NULL, NULL);    // create time
    GetFileTime( hFile, NULL, &ftDate, NULL);    // access time
//  GetFileTime( hFile, NULL, NULL, &ftDate);    // modify time
    FileTimeToLocalFileTime( &ftDate, &lcDate ); // change from UTC to local time
    FileTimeToSystemTime( &lcDate, lpDate );     // change to system style
    CloseHandle( hFile );
    return(TRUE);
  }
  return(FALSE);
}

void win_node_accesstime(char node[_MAX_PATH], char tbuf[30])
{
  SYSTEMTIME   stDate;
  
  if ( win_accesstime(&stDate, node) ){
    // format : hari-bulan-tahun jam:menit:detik
    sprintf(tbuf, "%02d-%02d-%04d ", stDate.wDay, stDate.wMonth, stDate.wYear , stDate.wHour, stDate.wMinute, stDate.wSecond);
  }

}

BOOL win_modifytime( LPSYSTEMTIME lpDate, LPCTSTR lpFileName ) {
  FILETIME ftDate;
  FILETIME lcDate;
  HANDLE hFile;

  if((hFile = FuncLoadFile(lpFileName,FILE_ATTRIBUTE_NORMAL)) != INVALID_HANDLE_VALUE ){
//  GetFileTime( hFile, &ftDate, NULL, NULL);    // create time
//  GetFileTime( hFile, NULL, &ftDate, NULL);    // access time
    GetFileTime( hFile, NULL, NULL, &ftDate);    // modify time
    FileTimeToLocalFileTime( &ftDate, &lcDate ); // change from UTC to local time
    FileTimeToSystemTime( &lcDate, lpDate );     // change to system style
    CloseHandle( hFile );
	return(TRUE);

  }
  return(FALSE);
}

void win_node_modifytime(char node[_MAX_PATH], char tbuf[30])
{
  SYSTEMTIME   stDate;
  
  if ( win_modifytime(&stDate, node) ){
    // format : hari-bulan-tahun jam:menit:detik
    sprintf(tbuf, "%02d-%02d-%04d ", stDate.wDay, stDate.wMonth, stDate.wYear , stDate.wHour, stDate.wMinute, stDate.wSecond);
  }


}

void win_node_size(char mypath[_MAX_PATH], char tbuf[30])
{
  HANDLE hFile;

  DWORD  fsize,hiwd;

  hFile = CreateFile(mypath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
  if (hFile==INVALID_HANDLE_VALUE) {
    Error("arsip salah");
  }
  fsize= GetFileSize(hFile,&hiwd);

  sprintf(tbuf,"%d",fsize);

}

int win_node_isfile(char mypath[_MAX_PATH])
{
  int ret=0;

  WIN32_FIND_DATA fd;
  HANDLE          hFile;

  hFile = FindFirstFile( mypath, &fd );

  if( hFile == INVALID_HANDLE_VALUE ) {
     ret = 0;
  } else {
	 ret = 1;
  }

  return ret;
}

#endif // #ifndef S_SPLINT_S

#else

#include <dirent.h>

char *node_accesstime(const char *node)
{
  struct stat statb;
  struct dirent *dentp;
  DIR *dp=NULL;
  char buf[MAX_STRING_LEN+2];
  char tbuf[30];
  char *ret=NULL;

  memset(&tbuf,'\0',sizeof(tbuf));
  if (stat(node, &statb) == -1) {
	fprintf(stderr, "Status Arsip Salah : %s \n", node);
	if (errno == EBADF)
		fprintf(stderr, " struktur file tidak baik ,");
	if (errno == ENOENT)
		fprintf(stderr, " komponen/arsipnya tidak ada ,");
	if (errno == ENOTDIR)
		fprintf(stderr, " komponen/arsip path bukan direktori ,");
	if (errno == EACCES)
		fprintf(stderr, " tak ada izin pengaksesan ,");
	if (errno == ENOMEM)
		fprintf(stderr, " melebihi kapasitas memory ,");
	if (errno == ENAMETOOLONG)
		fprintf(stderr, " Nama file terlalu panjang ,");
        Error(" Arsip Salah");
        exit(1);
  } else {
        if (S_ISREG(statb.st_mode) ) {
          // format : hari-bulan-tahun jam:menit:detik
          strftime(tbuf,30,"%d-%m-%Y %H:%M:%S",localtime(&statb.st_atime));
        } else if(S_ISDIR(statb.st_mode) ) {
          strftime(tbuf,30,"%d-%m-%Y %H:%M:%S",localtime(&statb.st_atime));
        } else {
          strcpy(tbuf,"");
        }
        ret = tbuf;
  }
  node = NULL;
  return ret;
}

char *node_modifytime(const char *node)
{
  struct stat statb;
  struct dirent *dentp;
  DIR *dp=NULL;
  char buf[MAX_STRING_LEN+2];
  char tbuf[30];
  char *ret=NULL;

  memset(&tbuf,'\0',sizeof(tbuf));
  if (stat(node, &statb) == -1) {
	fprintf(stderr, "Status Arsip Salah : %s \n", node);
	if (errno == EBADF)
		fprintf(stderr, " struktur file tidak baik ,");
	if (errno == ENOENT)
		fprintf(stderr, " komponen/arsipnya tidak ada ,");
	if (errno == ENOTDIR)
		fprintf(stderr, " komponen/arsip path bukan direktori ,");
	if (errno == EACCES)
		fprintf(stderr, " tak ada izin pengaksesan ,");
	if (errno == ENOMEM)
		fprintf(stderr, " melebihi kapasitas memory ,");
	if (errno == ENAMETOOLONG)
		fprintf(stderr, " Nama file terlalu panjang ,");
        Error(" Arsip Salah");
        exit(1);
  } else {
        if (S_ISREG(statb.st_mode) ) {
          // format : hari-bulan-tahun jam:menit:detik
          strftime(tbuf,30,"%d-%m-%Y %H:%M:%S",localtime(&statb.st_mtime));
        } else if(S_ISDIR(statb.st_mode) ) {
          strftime(tbuf,30,"%d-%m-%Y %H:%M:%S",localtime(&statb.st_mtime));
        } else {
          strcpy(tbuf,"");
        }
        ret = tbuf;
  }
  node = NULL;
  return ret;
}

char *node_size(const char *node)
{
  struct stat statb;
  struct dirent *dentp;
  DIR *dp=NULL;
  char buf[MAX_STRING_LEN+2];
  char tbuf[30];
  char *ret=NULL;

  memset(&tbuf,'\0',sizeof(tbuf));
  if (stat(node, &statb) == -1) {
	fprintf(stderr, "Status Arsip Salah : %s \n", node);
	if (errno == EBADF)
		fprintf(stderr, " struktur file tidak baik ,");
	if (errno == ENOENT)
		fprintf(stderr, " komponen/arsipnya tidak ada ,");
	if (errno == ENOTDIR)
		fprintf(stderr, " komponen/arsip path bukan direktori ,");
	if (errno == EACCES)
		fprintf(stderr, " tak ada izin pengaksesan ,");
	if (errno == ENOMEM)
		fprintf(stderr, " melebihi kapasitas memory ,");
	if (errno == ENAMETOOLONG)
		fprintf(stderr, " Nama file terlalu panjang ,");
        Error(" Arsip Salah");
        exit(1);
  } else {
        if (S_ISREG(statb.st_mode) ) {
          sprintf(tbuf,"%ld", statb.st_size);
        } else if(S_ISDIR(statb.st_mode) ) {
          sprintf(tbuf,"%ld", statb.st_size);
        } else {
          strcpy(tbuf,"0");
        }
        ret = tbuf;
  }
  node = NULL;
  return ret;
}

int node_isfile(const char *node)
{
  struct stat statb;
  struct dirent *dentp=NULL;
  DIR *dp=NULL;
  char buf[MAX_STRING_LEN+2];
  int ret=0;

  if (stat(node, &statb) == -1) {
	fprintf(stderr, "Status Arsip Salah : %s \n", node);
	if (errno == EBADF)
		fprintf(stderr, " struktur file tidak baik ,");
	if (errno == ENOENT)
		fprintf(stderr, " komponen/arsipnya tidak ada ,");
	if (errno == ENOTDIR)
		fprintf(stderr, " komponen/arsip path bukan direktori ,");
	if (errno == EACCES)
		fprintf(stderr, " tak ada izin pengaksesan ,");
	if (errno == ENOMEM)
		fprintf(stderr, " melebihi kapasitas memory ,");
	if (errno == ENAMETOOLONG)
		fprintf(stderr, " Nama file terlalu panjang ,");
        Error(" Arsip Salah");
        exit(1);
  } else {
        if (S_ISREG(statb.st_mode) ) {
          ret = 1;
        } else {
          ret = 0;
        }
  }
  node = NULL;
  return ret;
}

#endif

// //////////////////////////////////////////////////////////////////////


