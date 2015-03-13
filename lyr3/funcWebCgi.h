// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcPOST_NAMA ( char currentClass[MAX_STRING_LEN] , int is_class_ident)
{
  VAL_LABEL datx;
  int  n=0, i=0, j=0;
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0;                           // array index
  int    pos = 0;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


           getlex();
         /* printf("lex type : %d\n", lex.type);  */

         memset(&datx.str,'\0',sizeof(datx.str));

         if(lex.type == TYPE_NUM) {
           if(web_name[lex.detail.num] != '\0')
             strcpy(datx.str , web_name[lex.detail.num]);
           else 
             strcpy(datx.str , "");
           datx.datatype = 3;
         } else if(lex.type == TYPE_DBL) {
           Error("POST_NAMA: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           Error("POST_NAMA: masukan data salah");
         } else if(lex.type == TYPE_ARRAY) {
            /* printf("akar array\n"); */

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

              //itoa(idx, valdat.array_idx, 10);
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #else
               snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #endif
              #else
              snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
              #endif

              /* printf("akar type %d\n", valdat.datatype); */

              if(idx < 0 || idx > MAX_ARRAY)
                Error("pos_nama: ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 6 && valdat.array_i[idx] != '\0') {
                if(valdat.array_i == '\0')
                  Error("post_nama: ukuran Untaian belum terdefinisi");

                strcpy(datx.str, web_name[ valdat.array_i[idx] ]);
                datx.datatype = 3;
              } else {
                Error("POST_NAMA: masukan data salah");
              }
           }

         } else {
           datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 0) {
             strcpy(datx.str , web_name[datx.val]);
             datx.datatype = 3;
           } else {
             Error("POST_NAMA: masukan data salah");
           }
         }

  return datx;
}


VAL_LABEL funcPOST_NILAI ( char currentClass[MAX_STRING_LEN] , int is_class_ident)
{
  VAL_LABEL datx;
  int  n=0, i=0, j=0;
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0;                           // array index
  int    pos = 0;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex type : %d\n", lex.type);  */

         memset(&datx.str,'\0',sizeof(datx.str));

         if(lex.type == TYPE_NUM) {
           strcpy(datx.str , web_value[lex.detail.num]);
           datx.datatype = 3;
         } else if(lex.type == TYPE_DBL) {
           Error("POST_NILAI: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           Error("POST_NILAI: masukan data salah");
         } else if(lex.type == TYPE_ARRAY) {
            /* printf("akar array\n"); */

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

              //itoa(idx, valdat.array_idx, 10);
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #else
               snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #endif
              #else
              snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
              #endif

              /* printf("akar type %d\n", valdat.datatype); */

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 6 && valdat.array_i[idx] != '\0') {
                if(valdat.array_i == '\0')
                  Error("pos_nilai: ukuran Untaian belum terdefinisi");

                strcpy(datx.str, web_value[ valdat.array_i[idx] ]);
                datx.datatype = 3;
              } else {
                Error("POST_NILAI: masukan data salah");
              }
           }

         } else {
           datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 0) {
             strcpy(datx.str , web_value[datx.val]);
             datx.datatype = 3;
           } else {
             Error("POST_NILAI: masukan data salah");
           }
         }

    return datx;
}


VAL_LABEL funcBASIS64 ( char currentClass[MAX_STRING_LEN] , int is_class_ident)
{
  VAL_LABEL datx;
  int  n=0, i=0, j=0;
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0;                           // array index
  int    pos = 0;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("BASIS64: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("BASIS64: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           base64(lex.detail.string, sizeof(lex.detail.string), datx.str);
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

              //itoa(idx, valdat.array_idx, 10);
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #else
               snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #endif
              #else
              snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
              #endif

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 8 && valdat.array_s != '\0') {
                if(valdat.array_s == '\0')
                  Error("basis64: ukuran Untaian belum terdefinisi");

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
                base64(TmpStrBox.str.mystring, sizeof(TmpStrBox.str.mystring), datx.str);
                datx.datatype = 3;

              } else if (valdat.datatype == 10) {
                base64(valdat.long_str[idx], sizeof(valdat.long_str[idx]), datx.str );
                datx.datatype = 3;

              } else {
                Error("BASIS64: masukan data salah");
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
             base64(valdat.str, sizeof(valdat.str), datx.str );
             datx.datatype = 3;
           } else {
             Error("BASIS64: masukan data salah");
           }
         }

    return datx;
}


VAL_LABEL funcBUKABASIS64 ( char currentClass[MAX_STRING_LEN] , int is_class_ident)
{
  VAL_LABEL datx;
  int  n=0, i=0, j=0;
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0;                           // array index
  int    pos = 0;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("BUKABASIS64: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("BUKABASIS64: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           b64_decode(lex.detail.string, datx.str);
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

              //itoa(idx, valdat.array_idx, 10);
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #else
               snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #endif
              #else
              snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
              #endif

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 8 && valdat.array_s != '\0') {
                if(valdat.array_s == '\0')
                  Error("bukabasis64: ukuran Untaian belum terdefinisi");

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
                b64_decode(TmpStrBox.str.mystring, datx.str);
                datx.datatype = 3;


              } else if (valdat.datatype == 10) {
                b64_decode(valdat.long_str[idx], datx.str );
                datx.datatype = 3;

              } else {
                Error("BUKABASIS64: masukan data salah");
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
             valdat = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 3) {
             b64_decode(valdat.str, datx.str );
             datx.datatype = 3;
           } else {
             Error("BUKABASIS64: masukan data salah");
           }
         }

      return datx;
}
