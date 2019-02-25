// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// 2015/08/08

VAL_LABEL funcSambung ()
{
  VAL_LABEL datx;
  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  int  n=0;

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

        n = 0;
        datx.datatype = 3;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
	         Error("SAMBUNG: masukan data salah");
           } else if(lex.type == TYPE_STR) {
             if(n == 0)
              strcpy(dat_a, lex.detail.string);
             if(n == 1)
              strcpy(dat_b, lex.detail.string);

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

              if(valdat.datatype == 8 && valdat.array_s != '\0') {
                if(valdat.array_s == '\0')
                  Error("sambung: ukuran Untaian belum terdefinisi");

                datx.datatype = 3;


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
  					  printf("nilai untaian kata tidak ditemukan\n");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);

                      if(n == 0)
						  strcpy(dat_a, TmpStrBox.str.mystring);
                      if(n == 1)
						  strcpy(dat_b, TmpStrBox.str.mystring);

					}

				  }

              } else if (valdat.datatype == 10) {

                datx.datatype = 3;

                if(strlen(valdat.long_str[idx]) > 0) {
                  if(n == 0)
                    strcpy(dat_a, valdat.long_str[idx]);
                  if(n == 1)
                    strcpy(dat_b, valdat.long_str[idx]);
                }

              } else {
                strcpy(datx.str, "");
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
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

             } else {

                valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 3) {
               if( strlen(valdat.str) > 0 ) {
                 if(n == 0)
                   strcpy(dat_a, valdat.str);
                 if(n == 1)
                   strcpy(dat_b, valdat.str);
               }
             } 
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=2) {
	     Error("SAMBUNG: masukan data salah");
        } else {
              /*printf("a: %s\n", dat_a);
                printf("b: %s\n", dat_b); */
             strcat(dat_a, dat_b);

             strcpy(datx.str , dat_a);
             datx.datatype = 3;
             /* printf("hasil sambung: %s\n", datx.str); */

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

  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);

  return datx;
}

VAL_LABEL funcGabung ()
{
  VAL_LABEL datx;
  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  int  n=0;

  char   tmp_str[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0;
        strcpy(tmp_str , "");

        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {

             #ifdef WIN32
              #ifndef S_SPLINT_S
              sprintf_s(dat_a, sizeof(dat_a),"%li", lex.detail.num);
              #else
              snprintf(dat_a, sizeof(dat_a),"%li", lex.detail.num);
              #endif
             #else
             snprintf(dat_a, sizeof(dat_a),"%li", lex.detail.num);
             #endif

             strcat(tmp_str, dat_a);
           } else if(lex.type == TYPE_DBL) {

             #ifdef WIN32
              #ifndef S_SPLINT_S
              sprintf_s(dat_a, sizeof(dat_a),"%.2f", lex.detail.dblnum);
              #else
              snprintf(dat_a, sizeof(dat_a),"%.2f", lex.detail.dblnum);
              #endif
             #else
             snprintf(dat_a, sizeof(dat_a),"%.2f", lex.detail.dblnum);
             #endif

             strcat(tmp_str, dat_a);
           } else if(lex.type == TYPE_STR) {

             #ifdef WIN32
              #ifndef S_SPLINT_S
              sprintf_s(dat_a, sizeof(dat_a),"%s", lex.detail.string);
              #else
              snprintf(dat_a, sizeof(dat_a),"%s", lex.detail.string);
              #endif
             #else
             snprintf(dat_a, sizeof(dat_a),"%s", lex.detail.string);
             #endif

             strcat(tmp_str, dat_a);
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

              //printf("get arry type %d\n", valdat.datatype);

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 6) {
                if(valdat.array_i == '\0')
                  Error("GABUNG: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */

                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(dat_a, sizeof(dat_a),"%d", get_int_array(valdat, idx));
                 #else
                 snprintf(dat_a, sizeof(dat_a),"%d", get_int_array(valdat, idx));
                 #endif
                #else
                snprintf(dat_a, sizeof(dat_a),"%d", get_int_array(valdat, idx));
                #endif

                strcat(tmp_str, dat_a);

              } else
              if(valdat.datatype == 7) {
                if(valdat.array_d == '\0')
                  Error("GABUNG: ukuran Untaian belum terdefinisi");

                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(dat_a, sizeof(dat_a),"%.2f", get_dbl_array(valdat, idx));
                 #else
                 snprintf(dat_a, sizeof(dat_a),"%.2f", get_dbl_array(valdat, idx));
                 #endif
                #else
                snprintf(dat_a, sizeof(dat_a),"%.2f", get_dbl_array(valdat, idx));
                #endif

                strcat(tmp_str, dat_a);

              } else
              if(valdat.datatype == 8) {
                if(valdat.array_s == '\0')
                  Error("GABUNG: ukuran Untaian belum terdefinisi");

                get_str_array(valdat, idx, (char *)&dat_a);
                strcat(tmp_str, dat_a);

              } else {
                Error("GABUNG: masukan data salah");
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
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }



             //valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 0) {
               #ifdef WIN32
                #ifndef S_SPLINT_S
                sprintf_s(dat_a, sizeof(dat_a),"%li", valdat.val);
                #else
                snprintf(dat_a, sizeof(dat_a),"%li", valdat.val);
                #endif
               #else
               snprintf(dat_a, sizeof(dat_a),"%li", valdat.val);
               #endif

               strcat(tmp_str, dat_a);
             } else if(valdat.datatype == 1) {
               #ifdef WIN32
                #ifndef S_SPLINT_S
                sprintf_s(dat_a, sizeof(dat_a),"%.2f", valdat.floatdata);
                #else
                snprintf(dat_a, sizeof(dat_a),"%.2f", valdat.floatdata);
                #endif
               #else
               snprintf(dat_a, sizeof(dat_a),"%.2f", valdat.floatdata);
               #endif

               strcat(tmp_str, dat_a);
             } else if(valdat.datatype == 3) {
               #ifdef WIN32
                #ifndef S_SPLINT_S
                sprintf_s(dat_a, sizeof(dat_a),"%s", valdat.str);
                #else
                snprintf(dat_a, sizeof(dat_a),"%s", valdat.str);
                #endif
               #else
               snprintf(dat_a, sizeof(dat_a),"%s", valdat.str);
               #endif

               strcat(tmp_str, dat_a);
             } else {
               Error("GABUNG: masukan data salah");
             }
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        strcpy(datx.str , tmp_str);
        datx.datatype = 3;
        
        /* printf("========="); */


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

  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);

  return datx;
}

VAL_LABEL funcEKSPRESI ()
{
  VAL_LABEL datx;
  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];
  char   tmp_str[MAX_STRING_LEN];

  int  n=0;

  long  idx=0;

  VAL_LABEL valdat, valdat2, tmpdat;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
	          Error("EKSPRESI: masukan data salah");
           } else if(lex.type == TYPE_STR) {
             if(n == 0)
              strcpy(dat_a, lex.detail.string);
             if(n == 1)
              strcpy(dat_b, lex.detail.string);
           } else if(lex.type == TYPE_IDENT) {

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
               datx = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

             // datx = ValLabel( lex.detail.ident, datx, VAL_FLAG_SEARCH_R );
			 if( datx.datatype == 3 && strlen(datx.str) > 0 ) {
               if(n == 0)
                 strcpy(dat_a, datx.str);
               if(n == 1)
                 strcpy(dat_b, datx.str);
             }
           } else if(lex.type == TYPE_ARRAY) {

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
                 sprintf_s(valdat2.array_idx, sizeof(valdat.array_idx),"%li", idx);
                 #else
                 snprintf(valdat2.array_idx, sizeof(valdat.array_idx),"%li", idx);
                 #endif
                #else
                snprintf(valdat2.array_idx, sizeof(valdat.array_idx),"%li", idx);
                #endif


		//printf("idx %d\n", idx);
		//printf("max kapasitas %d\n", valdat2.array_max);
		if(valdat2.array_max <= 0) {
                  printf("nil ");  // Untaian nil / terhapus
		} else {
                  if(idx < 0 || idx > (valdat2.array_max-1))
                    Error("ukuran Untaian tidak sesuai kapasitas");
		}

		if (valdat2.datatype == 8) {
                  // printf("tulis arry string\n");
                  if(valdat2.array_s == '\0')
                    Error("ukuran Untaian belum terdefinisi: kata");

		  if(!get_str_array(valdat2, idx, (char *)&tmp_str)) {
                    if(n == 0)
                      strcpy(dat_a, "");
                    if(n == 1)
                      strcpy(dat_b, "");
				  } else {
                    if(n == 0)
                      strcpy(dat_a, tmp_str);
                    if(n == 1)
                      strcpy(dat_b, tmp_str);
		  }
		}

           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=2) {
	     Error("EKSPRESI: masukan data salah");
        } else {
            /*  printf("a: %s\n", dat_a);
                printf("b: %s\n", dat_b); */

            #ifndef S_SPLINT_S

            #ifdef WINDOWS
             /* printf("match win\n"); */
             if(winRegexBuf(dat_a, dat_b) == 1) {
               datx.val = 1;
             } else {
               datx.val = 0;
             }
            #else
             /* printf("match unix\n"); */
             if(unixRegexBuf(dat_a, dat_b) == 1) {
               datx.val = 1;
             } else {
               datx.val = 0;
             }
            #endif

            #endif

            datx.datatype = 0;
            strcpy(datx.str , "");
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

  return datx;
}


