// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

int checkFloatBuf( char buf[MAX_STRING_LEN] );

VAL_LABEL funcANGKA_KAH ()
{
  VAL_LABEL datx;


  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  long   idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */
         datx.datatype = 0;

         if(lex.type == TYPE_NUM) {
           datx.val = 0;
         } else if(lex.type == TYPE_DBL) {
           datx.val = 0;
         } else if(lex.type == TYPE_STR) {
            datx.datatype = 0;

            if(strlen(lex.detail.string) != 1)
              datx.val = 0;
            else
              if(isdigit(lex.detail.string[0]))
                datx.val = 1;
              else
                datx.val = 0;

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
                  Error("angka_kah: ukuran Untaian belum terdefinisi");

                datx.datatype = 0;

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
  					  printf("APAKAH ANGKA nilai untaian kata tidak ditemukan\n");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);

					  if(strlen(TmpStrBox.str.mystring) != 1)
                        datx.val = 0;
                      else
					    if(isdigit(TmpStrBox.str.mystring[0]))
                          datx.val = 1;
                        else
                          datx.val = 0;

					}

				  }


              } else {
                datx.val = 0;
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
             valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           /*
           printf("typ %d\n", valdat.datatype);
           printf("typ str %s\n", valdat.str);
           printf("typ val %d\n", valdat.val);
           */

           if(valdat.datatype == 3) {
              datx.datatype = 0;
             if(strlen(valdat.str) != 1)
               datx.val = 0;
             else
               if(isdigit(valdat.str[0]))
                 datx.val = 1;
               else
                 datx.val = 0;

           } else {
              datx.datatype = 0;
              datx.val = 0;
           }
           /*
           printf("typ %d\n", datx.datatype);
           printf("val %d\n", datx.val);
           */
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


VAL_LABEL funcHURUF_KAH ()
{
  VAL_LABEL datx;


  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));


         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */
         datx.datatype = 0;

         if(lex.type == TYPE_NUM) {
           datx.val = 0;
         } else if(lex.type == TYPE_DBL) {
           datx.val = 0;
         } else if(lex.type == TYPE_STR) {
            datx.datatype = 0;

            if(strlen(lex.detail.string) != 1)
              datx.val = 0;
            else
              if(isalpha(lex.detail.string[0]))
                datx.val = 1;
              else
                datx.val = 0;

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
                  Error("huruf_kah: ukuran Untaian belum terdefinisi");

                datx.datatype = 0;

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
						printf("APAKAH_HURUF: nilai untaian kata tidak ditemukan\n");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);

					  if(strlen(TmpStrBox.str.mystring) != 1)
                        datx.val = 0;
                      else
						if(isalpha(TmpStrBox.str.mystring[0]))
                          datx.val = 1;
                        else
                          datx.val = 0;

					}

				  }

              } else {
                datx.val = 0;
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
             valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           /*
           printf("typ %d\n", valdat.datatype);
           printf("typ str %s\n", valdat.str);
           printf("typ val %d\n", valdat.val);
           */

           if(valdat.datatype == 3) {
              datx.datatype = 0;
             if(strlen(valdat.str) != 1)
               datx.val = 0;
             else
               if(isalpha(valdat.str[0]))
                 datx.val = 1;
               else
                 datx.val = 0;

           } else {
              datx.datatype = 0;
              datx.val = 0;
           }
           /*
           printf("typ %d\n", datx.datatype);
           printf("val %d\n", datx.val);
           */
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



VAL_LABEL funcHURUF_NO ()
{
  VAL_LABEL datx;
  int  n=0;

  char   dat_a[MAX_STRING_LEN*2];

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index
  int    pos = 0;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&dat_a, '\0', sizeof(dat_a));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


        n = 0;
        datx.datatype = 3;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */
           pos = -1;

           if(lex.type == TYPE_NUM) {
             if(n == 1)
               pos = lex.detail.num;
           } else if(lex.type == TYPE_STR) {
             if(n == 0)
              strcpy(dat_a, lex.detail.string);

           } else if(lex.type == TYPE_ARRAY) {
             /* printf("get array\n"); */
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

              /* read real data */
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

              if(valdat.datatype == 6 && valdat.array_i != '\0') {
                if(valdat.array_i == '\0')
                  Error("huruf_no: ukuran Untaian belum terdefinisi");

                if(valdat.array_i != '\0') {
                  if(n == 1)
                    pos = get_int_array(valdat, idx) ;
                }
              } 

              if(valdat.datatype == 8 && valdat.array_s != '\0') {

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				  memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

                  strcpy(TmpStrBox.var.array_name, valdat.array_name);
                  renban = valdat.array_s;

				  // printf("HURUF_NO array name: %s\n", valdat.array_name);
				  // printf("HURUF_NO get stackid: %d, idx: %d\n", renban, idx);

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
					}

				  }

              } else {
                strcpy(datx.str, "");
              }

            }


           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );

             if( strlen(valdat.str) > 0 ) {
               if(n == 0)
                 strcpy(dat_a, valdat.str);
             } else if(valdat.datatype == 0) {
               if(n == 1)
                 pos = valdat.val;
             }

           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=2) {
	     Error("HURUF_NO: masukan data salah");
        } else {
              /*printf("a: %s\n", dat_a);
                printf("b: %s\n", dat_b); */
             if((int)strlen(dat_a) < pos)
               Error("nilai posisi huruf salah");

             if(pos < 0)
               Error("nilai posisi huruf salah");

             datx.str[0] = dat_a[pos];
             datx.str[1] = '\0';

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

  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);

  return datx;
}


VAL_LABEL funcKE_ANGKA ()
{
  VAL_LABEL datx;


  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("KE_ANGKA: salah masukan : angka");
         } else if(lex.type == TYPE_DBL) {
           Error("KE_ANGKA: salah masukan : pecahan");
         } else if(lex.type == TYPE_STR) {

            if(strlen(lex.detail.string) > 0) {
              if(checkFloatBuf(lex.detail.string) == 1) {
                datx.floatdata = atof(lex.detail.string);
                datx.datatype = 1;
              } else {
                datx.val = atol(lex.detail.string);
                datx.datatype = 0;
              }

            } else
              datx.val = 0;

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
                  Error("ke_angka: ukuran Untaian belum terdefinisi");

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

					  if(strlen(TmpStrBox.str.mystring) > 0) {
						if(checkFloatBuf(TmpStrBox.str.mystring) == 1) {
						  datx.floatdata = strtodbl(TmpStrBox.str.mystring);
                          datx.datatype = 1;
                        } else {
						  datx.val = atol(TmpStrBox.str.mystring);
                          datx.datatype = 0;
                        }
                      } else
                        datx.val = 0;
  					  }

				  }

              } else {
                datx.val = 0;
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
             valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           /*
           printf("typ %d\n", valdat.datatype);
           printf("typ str %s\n", valdat.str);
           printf("typ val %d\n", valdat.val);
           */

           if(valdat.datatype == 3) {
             if(strlen(valdat.str) > 0) {
               if(checkFloatBuf(valdat.str) == 1) {
                 datx.floatdata = atof(valdat.str);
                 datx.datatype = 1;
               } else {
                 datx.val = atol(valdat.str);
                 datx.datatype = 0;
               }

             } else {
               datx.val = 0;
               datx.datatype = 0;
             }

           } else {
              datx.val = 0;
           }
           /*
           printf("typ %d\n", datx.datatype);
           printf("val %d\n", datx.val);
           */
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


VAL_LABEL funcKE_HURUF ()
{
  VAL_LABEL datx;


  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */
         datx.datatype = 3;

         if(lex.type == TYPE_NUM) {

           #ifdef WIN32
            #ifndef S_SPLINT_S
            sprintf_s(datx.str, sizeof(datx.str),"%li", lex.detail.num);
            #else
            snprintf(datx.str, sizeof(datx.str),"%li", lex.detail.num);
            #endif
           #else
           snprintf(datx.str, sizeof(datx.str),"%li", lex.detail.num);
           #endif

         } else if(lex.type == TYPE_DBL) {

           #ifdef WIN32
            #ifndef S_SPLINT_S
            sprintf_s(datx.str, sizeof(datx.str),"%f", lex.detail.dblnum);
            #else
            snprintf(datx.str, sizeof(datx.str),"%f", lex.detail.dblnum);
            #endif
           #else
           snprintf(datx.str, sizeof(datx.str),"%f", lex.detail.dblnum);
           #endif

         } else if(lex.type == TYPE_STR) {
           Error("KE_HURUF: salah masukan : kata");

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

              if(valdat.datatype == 6 && valdat.array_i != '\0') {
                if(valdat.array_i == '\0')
                  Error("ke_huruf: ukuran Untaian belum terdefinisi");

                datx.datatype = 3;

                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(datx.str, sizeof(datx.str),"%d", get_int_array(valdat, idx));
                 #else
                 snprintf(datx.str, sizeof(datx.str),"%d", get_int_array(valdat, idx));
                 #endif
                #else
                snprintf(datx.str, sizeof(datx.str),"%d", get_int_array(valdat, idx));
                #endif

              } else if(valdat.datatype == 7 && valdat.array_d != '\0') {
                datx.datatype = 3;

                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(datx.str, sizeof(datx.str),"%f", get_dbl_array(valdat, idx));
                 #else
                 snprintf(datx.str, sizeof(datx.str),"%f", get_dbl_array(valdat, idx));
                 #endif
                #else
                snprintf(datx.str, sizeof(datx.str),"%f", get_dbl_array(valdat, idx));
                #endif

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
             valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           datx.datatype = 3;
           /*
           printf("typ %d\n", valdat.datatype);
           printf("typ str %s\n", valdat.str);
           printf("typ val %d\n", valdat.val);
           */

           if(valdat.datatype == 0) {
             if(valdat.val != '\0')

               #ifdef WIN32
                #ifndef S_SPLINT_S
                sprintf_s(datx.str, sizeof(datx.str),"%li", valdat.val);
                #else
                snprintf(datx.str, sizeof(datx.str),"%li", valdat.val);
                #endif
               #else
               snprintf(datx.str, sizeof(datx.str),"%li", valdat.val);
               #endif

             else
               strcpy(datx.str, "");
           } else if(valdat.datatype == 1) {

               #ifdef WIN32
                #ifndef S_SPLINT_S
                sprintf_s(datx.str, sizeof(datx.str),"%f", valdat.floatdata);
                #else
                snprintf(datx.str, sizeof(datx.str),"%f", valdat.floatdata);
                #endif
               #else
               snprintf(datx.str, sizeof(datx.str),"%f", valdat.floatdata);
               #endif

           } else {
             Error("KE_HURUF: salah masukan");
           }
           /*
           printf("typ %d\n", datx.datatype);
           printf("val %d\n", datx.val);
           */
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


int checkFloatBuf( char buf[MAX_STRING_LEN] )
{
  char c;
  int  isFloat = 0;
  int  n = 0;

  do{
    c = buf[n++];

    if(c == '.')
      isFloat = 1;

  }while( !isspace( c ) && c != '\0' );

  return isFloat;
}

