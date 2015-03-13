// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

char *Mygetcwd (char *buf, size_t size);
void printcwd (void);

#ifdef WINDOWS
char** win_dir_content(const char *path);
#else
char** dir_content(const char *path);
#endif
void dir_free(char **arr);

VAL_LABEL funcAMBIL_DIR ()
{
  VAL_LABEL datx;
  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  int  i=0, j=0;

  char    **get;

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

  get = NULL;

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("AMBIL_DIR: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("AMBIL_DIR: masukan data salah");
         } else if(lex.type == TYPE_STR) {

            get = NULL;
            #ifdef WINDOWS
            get = win_dir_content(lex.detail.string);
            datx.long_str = win_dir_content(lex.detail.string);
            #else
            get = dir_content(lex.detail.string);
            datx.long_str = dir_content(lex.detail.string);
            #endif

            j = 0;
            if(get != NULL) {
              for(i=0; get[i] != NULL; i++) {
                // writeLog(get[i]);
                j++;
              }
              dir_free(get);
            }

            datx.array_max = j;
            datx.isLongStr = 1;
            datx.datatype  = 10;

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
                if(valdat.array_i == '\0')
                  Error("AMBIL_DIR: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				  memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				  strcpy(TmpStrBox.var.array_name, valdat.array_name);
                  renban = valdat.array_s;

				  // printf("TULIS get stackid: %d, idx: %d\n", renban, idx);

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


                get = NULL;
                #ifdef WINDOWS
                get = win_dir_content(TmpStrBox.str.mystring);
                datx.long_str = win_dir_content(TmpStrBox.str.mystring);				
                #else
                get = dir_content(TmpStrBox.str.mystring);
                datx.long_str = dir_content(TmpStrBox.str.mystring);
                #endif

                j = 0;
                if(get != NULL) {
                  for(i=0; get[i] != NULL; i++) {
                    //writeLog(get[i]);
                    j++;
                  }
                  dir_free(get);
                }

                datx.array_max = j;
                datx.isLongStr = 1;
                datx.datatype  = 10;


              } else {
                Error("AMBIL_DIR: masukan data salah");
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
             datx = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 3) {

             get = NULL;
             #ifdef WINDOWS
             get = win_dir_content(datx.str);
             datx.long_str = win_dir_content(datx.str);
             #else
             get = dir_content(datx.str);
             datx.long_str = dir_content(datx.str);
             #endif

             j = 0;
             if(get != NULL) {
               for(i=0; get[i] != NULL; i++) {
                 //writeLog(get[i]);
                 j++;
               }
               dir_free(get);
             }

             datx.array_max = j;
             datx.isLongStr = 1;
             datx.datatype  = 10;

           } else {
             Error("AMBIL_DIR: masukan data salah");
           }
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

  if(get != NULL) {
    for(i=0; get[i] != NULL; i++) {
       j++;
    }
    if (get != NULL) {
      get--;
      free(get[0]);
      free(get);
    }
  }

  return datx;
}


VAL_LABEL funcBUAT_DIR ()
{
  VAL_LABEL datx;

  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("BUAT_DIR: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("BUAT_DIR: masukan data salah");
         } else if(lex.type == TYPE_STR) {

           #ifndef S_SPLINT_S

           #ifdef WINDOWS
           datx.val = mkdir(lex.detail.string);
           #else
           datx.val = mkdir(lex.detail.string, 0755);
           #endif

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
                if(valdat.array_i == '\0')
                  Error("buat_dir: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				  memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				  strcpy(TmpStrBox.var.array_name, valdat.array_name);
                  renban = valdat.array_s;

				  // printf("TULIS get stackid: %d, idx: %d\n", renban, idx);

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

                #ifndef S_SPLINT_S

                #ifdef WINDOWS
		datx.val = mkdir(TmpStrBox.str.mystring);
                #else
                datx.val = mkdir(TmpStrBox.str.mystring, 0755);
                #endif

                #endif

                datx.datatype = 0;
              } else {
                Error("BUAT_DIR: masukan data salah");
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
             datx = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 3) {
             #ifndef S_SPLINT_S

             #ifdef WINDOWS
             datx.val = mkdir(datx.str);
             #else
             datx.val = mkdir(datx.str, 0755);
             #endif

             #endif

             datx.datatype = 0;
           } else {
             Error("BUAT_DIR: masukan data salah");
           }
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


VAL_LABEL funcHAPUS_DIR ()
{
  VAL_LABEL datx;




  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("HAPUS_DIR: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("HAPUS_DIR: masukan data salah");
         } else if(lex.type == TYPE_STR) {

           #ifndef S_SPLINT_S
           datx.val = rmdir(lex.detail.string);
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
                if(valdat.array_i == '\0')
                  Error("buat_dir: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				  memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				  strcpy(TmpStrBox.var.array_name, valdat.array_name);
                  renban = valdat.array_s;

				  // printf("TULIS get stackid: %d, idx: %d\n", renban, idx);

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


                #ifndef S_SPLINT_S
                datx.val = rmdir(TmpStrBox.str.mystring);
                #endif

                datx.datatype = 0;
              } else {
                Error("HAPUS_DIR: masukan data salah");
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
             datx = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 3) {
             #ifndef S_SPLINT_S
             datx.val = rmdir(datx.str);
             #endif

             datx.datatype = 0;
           } else {
             Error("HAPUS_DIR: masukan data salah");
           }
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

VAL_LABEL funcGANTI_DIR ()
{
  VAL_LABEL datx;




  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("GANTI_DIR: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("GANTI_DIR: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           #ifndef S_SPLINT_S
           datx.val = chdir(lex.detail.string);
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
                if(valdat.array_i == '\0')
                  Error("ganti_dir: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				  memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				  strcpy(TmpStrBox.var.array_name, valdat.array_name);
                  renban = valdat.array_s;

				  // printf("TULIS get stackid: %d, idx: %d\n", renban, idx);

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

                #ifndef S_SPLINT_S
		datx.val = chdir(TmpStrBox.str.mystring);
                #endif
                datx.datatype = 0;
              } else {
                Error("GANTI_DIR: masukan data salah");
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
             datx = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 3) {
             #ifndef S_SPLINT_S
             datx.val = chdir(datx.str);
             #endif
             datx.datatype = 0;
           } else {
             Error("GANTI_DIR: masukan data salah");
           }
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

VAL_LABEL funcPOSISI_DIR ()
{
  VAL_LABEL datx;
  char   dat_a[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&dat_a, '\0', sizeof(dat_a));

        if (Mygetcwd (dat_a, sizeof (dat_a) ) == NULL) {
          strcpy(datx.str, "");
        } else {
          strcpy(datx.str, dat_a);
        }
        datx.datatype = 3;

  return datx;
}

char *Mygetcwd (char *buf, size_t size) {
        #ifndef S_SPLINT_S
        char *p = getcwd (buf, size);
        #else
        char *p = NULL;
        #endif

        if (! p) {
              Error ("getcwd");
        }
        return (p);
}


void printcwd (void)
{
        char    path[MAX_STRING_LEN];
        if (Mygetcwd (path, sizeof (path) ) == NULL) {
                exit (EXIT_FAILURE);
        }
        (void) puts (path);
}

#ifdef WINDOWS

#ifndef S_SPLINT_S

char** win_dir_content(const char *path)
{
   char **arr = NULL; 
   int  n   = 0;    
   int  j   = 0;  
   char *buf=NULL;

   HANDLE          hFile;                   // file handle
   WIN32_FIND_DATA fd;                      // WIN32_FIND_DATA structure(finddata)
   char            cddir[ _MAX_PATH ];      // wildcard inside dir
   char            filename[ _MAX_PATH ];   // full path of filename

    buf = (char*)malloc(strlen(path) + 1);
	if (buf == NULL) {
		return NULL;
	}
	strcpy(buf, path);

    strcpy( cddir, path );      // dir name 
    strcat( cddir, "\\*" );     // adding wildcard

    hFile = FindFirstFile( cddir, &fd );

    if( hFile == INVALID_HANDLE_VALUE )
    {
        Error( "Arsip / Direktori tidak ditemukan\n" );
    }

	n = 0;
	dirtp = NULL;
    do
    {
        char **a = (char**)realloc(arr, sizeof(*arr) * (n+3));
        if (a == '\0') {
           free(arr);
           free(buf);    // a must
           return '\0';
        }

		// not include dir and mother-dir 
        if( strcmp( fd.cFileName, ".." ) == 0  
         || strcmp( fd.cFileName, "." ) == 0 )
        {
            continue;
        }
        strcpy( filename, path ); 
        strcat( filename, "\\" ); 
        strcat( filename, fd.cFileName );

        if(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY ){
	      // printf("%s\\\n",fd.cFileName);  // ini Direktori
          dirtp = (char*)malloc(strlen(fd.cFileName) + 1);
          strcpy(dirtp, fd.cFileName);
		  a[++n] = dirtp;
		  arr = a;
		}
        else{
	      // printf("%s\n",fd.cFileName);  // ini File
          dirtp = (char*)malloc(strlen(fd.cFileName) + 1);
          strcpy(dirtp, fd.cFileName);
		  a[++n] = dirtp;
		  arr = a;
        }


    } while( FindNextFile( hFile, &fd ) ); 

	if (arr != '\0') {
		arr[0] = buf;
		arr++;
		arr[n] = '\0';
	} else {
	  free (buf);
	}

    FindClose( hFile ); // 

    return arr;

}

#endif // #ifndef S_SPLINT_S

#else

char** dir_content(const char *path)
{
   struct dirent *dp=NULL;
   
   char **arr='\0';
   int  n   = 0;    
   int  j   = 0;  
   char *buf='\0';

	if (path == '\0') {
           return '\0';
	}

        buf = (char*)malloc(strlen(path) + 1);
        if (buf == '\0') {
           return '\0';
        }
        strcpy(buf, path);

        owndir = NULL;                                                        
        if((owndir=opendir(buf))==NULL){
          perror("salah buka dir");
          exit(-1);
        }

        n = 0;
	for(dp=readdir(owndir);dp!=NULL;dp=readdir(owndir)) {
           char **a = (char**)realloc(arr, sizeof(*arr) * (n+3));
           if (a == '\0') {
             free(arr);
             free(buf);    // a must
             return '\0';
           }

           if(dp->d_name != NULL) {
		a[++n] = dp->d_name;
		arr = a;
           } 
	}

	if (arr != '\0') {
		arr[0] = buf;
		arr++;
		arr[n] = '\0';
	} else {
	  free (buf);
	  closedir(owndir);
	}

	return arr;
}

#endif

void dir_free(char **arr)
{
  if (arr != NULL) {
    arr--;
    free(arr[0]);
    free(arr);
  }
}


