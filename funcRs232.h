// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcTULIS_RS232 ()
{
  VAL_LABEL datx;
  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  int  n=0, i=0;
  int  dat_num=0;
  long  idx=0;

  VAL_LABEL valdat, tmpdat;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             if(n == 2) {
               dat_num = lex.detail.num;
             }
           } else if(lex.type == TYPE_STR || lex.type == TYPE_DBL) {
             if(n == 0) {
               strcpy(dat_a, lex.detail.string);
             } else if(n == 1) {
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
                   idx = atol (valdat.array_idx);
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

                 if(valdat.datatype == 6) {
                   if(valdat.array_i == '\0')
                     Error("tulis_soket: ukuran Untaian belum terdefinisi");
                   if(n == 2) {
                     dat_num = get_int_array(valdat, idx);
                   }

                 } else if(valdat.datatype == 8 && valdat.array_s != '\0') {
                   if(valdat.array_s == '\0')
                     Error("tulis_soket: ukuran Untaian belum terdefinisi");

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
                  strcpy(TmpStrBox.var.array_name, "a");
                  renban = stackStr_getID(TmpStrBox.var);
				  if(renban < 0) {
                    printf("variabel untaian tidak ditemukan\n");
				  } else {
                    TmpStrBox.str.stackid = renban;
                    TmpStrBox.str.idx = idx;

					strarryPos = string_findData(TmpStrBox.str);
					if(strarryPos < 0) {
  					  printf("nilai untaian kata tidak ditemukan\n");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);

                      if(n == 0) {
						  strcpy(dat_a, TmpStrBox.str.mystring);
                      }else if(n == 1) {
						  strcpy(dat_b, TmpStrBox.str.mystring);
                      }

					}

				  }


                 }
               }

           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
               if(n == 2) {
                 if(datx.datatype == 0) {
                   dat_num = datx.val;
                 }
               }
               else if(n == 0) {
                 if(datx.datatype == 3) {
                   strcpy(dat_a, datx.str);
                 }
               }
               else if(n == 1) {
                 if(datx.datatype == 3) {
                   strcpy(dat_b, datx.str);
                 }
               }
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=3) {
	     Error("TULIS_RS232: masukan data salah");
        } else {
             /* printf("a: %s\n", dat_a); */
             /* printf("b: %s\n", dat_b); */

             #ifndef S_SPLINT_S

             #ifdef WINDOWS
              datx.val = writeSerialCom(dat_a, dat_b, dat_num); 
             #else
              // do nothing
             #endif

             #endif

             datx.datatype = 0;

        }

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

  return datx;
}

VAL_LABEL funcBACA_RS232 ()
{
  VAL_LABEL datx;
  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  int  n=0, i=0;
  int  dat_num=0;
  long  idx=0;

  VAL_LABEL valdat, tmpdat;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             if(n == 1) {
               dat_num = lex.detail.num;
             }
           } else if(lex.type == TYPE_STR || lex.type == TYPE_DBL) {
             if(n == 0) {
               strcpy(dat_a, lex.detail.string);
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
                   idx = atol (valdat.array_idx);
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

                 if(valdat.datatype == 6 ) {
                   if(valdat.array_i == '\0')
                     Error("tulis_soket: ukuran Untaian belum terdefinisi");
                   if(n == 1) {
                     dat_num = get_int_array(valdat, idx);
                   }

                  } else if(valdat.datatype == 8 && valdat.array_s != '\0') {
                   if(valdat.array_s == '\0')
                     Error("tulis_soket: ukuran Untaian belum terdefinisi");


                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
                  strcpy(TmpStrBox.var.array_name, valdat.array_name);
                  renban = stackStr_getID(TmpStrBox.var);
				  if(renban < 0) {
                    printf("variabel untaian tidak ditemukan\n");
				  } else {
                    TmpStrBox.str.stackid = renban;
                    TmpStrBox.str.idx = idx;

					strarryPos = string_findData(TmpStrBox.str);
					if(strarryPos < 0) {
  					  printf("nilai untaian kata tidak ditemukan\n");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);
                      if(n == 0) {
						  strcpy(dat_a, TmpStrBox.str.mystring);
                      }
					}

				  }


                 }
               }

           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
               if(n == 1) {
                 if(datx.datatype == 0) {
                   dat_num = datx.val;
                 }
               }
               else if(n == 0) {
                 if(datx.datatype == 3) {
                   strcpy(dat_a, datx.str);
                 }
               }
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=2) {
	     Error("BACA_RS232: masukan data salah");
        } else {
             /* printf("a: %s\n", dat_a); */
             /* printf("b: %s\n", dat_b); */

             #ifndef S_SPLINT_S

             #ifdef WINDOWS
              strcpy( datx.str , readSerialCom(dat_a, dat_num) );
             #else
              // do nothing
             #endif

             #endif

             datx.datatype = 3;

        }

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

  return datx;
}