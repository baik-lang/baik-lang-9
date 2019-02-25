// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void getLingkup(const char *param, char retVal[MAX_STRING_LEN]);

void setLingkup(const char *param, char nilai[MAX_STRING_LEN]);

int getFromConf(char *filename, char symbol[MAX_STRING_LEN], char result[MAX_STRING_LEN*2]);


VAL_LABEL funcSetLingkup()
{
	VAL_LABEL datx;
	char   dat_a[MAX_STRING_LEN];
	char   dat_b[MAX_STRING_LEN];
	char   val[MAX_STRING_LEN * 2];

	int  n = 0;

	VAL_LABEL valdat;

	// var list for class params
	char    class_tmpvar[MAX_STRING_LEN];

	memset(&datx, '\0', sizeof(datx));
	memset(&dat_a, '\0', sizeof(dat_a));
	memset(&dat_b, '\0', sizeof(dat_b));

	memset(&val, '\0', sizeof(val));

	memset(&valdat, '\0', sizeof(valdat));

	memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

	n = 0;
	do {
		getlex();
		/* printf("%d %s\n",n, lex.detail.string); */

		if (lex.type == TYPE_NUM) {
			Error("SET_LINGKUP: masukan data salah");
		}
		else if (lex.type == TYPE_STR) {
			if (n == 0)
              #ifdef WIN32
                #ifndef S_SPLINT_S
				sprintf_s(dat_a, sizeof(dat_a), "%s", lex.detail.string);
                #else
				snprintf(dat_a, sizeof(dat_a), "%s", lex.detail.string);
                #endif
              #else
				snprintf(dat_a, sizeof(dat_a), "%s", lex.detail.string);
              #endif

			if (n == 1)
              #ifdef WIN32
                #ifndef S_SPLINT_S
				sprintf_s(dat_b, sizeof(dat_b), "%s", lex.detail.string);
                #else
				snprintf(dat_b, sizeof(dat_b), "%s", lex.detail.string);
                #endif
              #else
				snprintf(dat_b, sizeof(dat_b), "%s", lex.detail.string);
              #endif

		}
		else {
			datx = ValLabel(lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R);
			if (strlen(datx.str) > 0) {
				if (n == 0)
                  #ifdef WIN32
                    #ifndef S_SPLINT_S
					sprintf_s(dat_a, sizeof(dat_a), "%s", datx.str);
                    #else
					snprintf(dat_a, sizeof(dat_a), "%s", datx.str);
                    #endif
                  #else
					snprintf(dat_a, sizeof(dat_a), "%s", datx.str);
                  #endif

				if (n == 1)
                  #ifdef WIN32
                    #ifndef S_SPLINT_S
					sprintf_s(dat_b, sizeof(dat_b), "%s", datx.str);
                    #else
					snprintf(dat_b, sizeof(dat_b), "%s", datx.str);
                    #endif
                  #else
					snprintf(dat_b, sizeof(dat_b), "%s", datx.str);
                  #endif
			}
		}

		n++;

		getlex();

	} while (lex.type == TYPE_SYM && lex.detail.symbol == ',');

	ungetlex();

	if (n != 2) {
		Error("SET_LINGKUP: masukan data salah");
	}
	else {
		//printf("a: %s\n", dat_a);
		//printf("b: %s\n", dat_b); 

		setLingkup(dat_a, dat_b);

		datx.val = 0;
		datx.datatype = 0;
	}


	if (valdat.filename != NULL)
		free(valdat.filename);
	if (valdat.folder != NULL)
		free(valdat.folder);
	if (valdat.filedata != NULL)
		free(valdat.filedata);
	if (valdat.long_str != NULL)
		free(valdat.long_str);

	if (valdat.left != NULL)
		free(valdat.left);
	if (valdat.right != NULL)
		free(valdat.right);
	if (valdat.pnext != NULL)
		free(valdat.pnext);

	return datx;
}


VAL_LABEL funcLingkup ()
{
  VAL_LABEL datx;

  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

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
           Error("LINGKUP: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("LINGKUP: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           getLingkup(lex.detail.string, (char *)&datx.str );
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
                  Error("lingkup: ukuran Untaian belum terdefinisi");


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
			  getLingkup(TmpStrBox.str.mystring, (char *)&datx.str );
			}
		  }

                /* printf("%d", valdat.array_i[idx]); */
                // strcpy(datx.str , getLingkup(valdat.array_s[idx].str) );
                datx.datatype = 3;

              } else if (valdat.datatype == 10) {
                 getLingkup(valdat.long_str[idx], (char *)&datx.str );
                datx.datatype = 3;

              } else {
                Error("LINGKUP: masukan data salah");
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
             getLingkup(datx.str, (char *)&datx.str );
             datx.datatype = 3;
           } else {
             Error("LINGKUP: masukan data salah");
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

  return datx;

}


VAL_LABEL funcKONFIGURASI()
{
  VAL_LABEL datx;
  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];
  char   val[MAX_STRING_LEN*2];

  int  n=0;

  VAL_LABEL valdat;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  
  memset(&val, '\0', sizeof(val));  

  memset(&valdat, '\0', sizeof(valdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
	          Error("KONFIGURASI: masukan data salah");
           } else if(lex.type == TYPE_STR) {
             if(n == 0)
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(dat_a, sizeof(dat_a),"%s", lex.detail.string);
               #else
               snprintf(dat_a, sizeof(dat_a),"%s", lex.detail.string);
               #endif
              #else
              snprintf(dat_a, sizeof(dat_a),"%s", lex.detail.string);
              #endif

             if(n == 1)
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(dat_b, sizeof(dat_b),"%s", lex.detail.string);
               #else
               snprintf(dat_b, sizeof(dat_b),"%s", lex.detail.string);
               #endif
              #else
              snprintf(dat_b, sizeof(dat_b),"%s", lex.detail.string);
              #endif

           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             if( strlen(datx.str) > 0 ) {
               if(n == 0)
                 #ifdef WIN32
                  #ifndef S_SPLINT_S
                  sprintf_s(dat_a, sizeof(dat_a),"%s", datx.str);
                  #else
                  snprintf(dat_a, sizeof(dat_a),"%s", datx.str);
                  #endif
                 #else
                 snprintf(dat_a, sizeof(dat_a),"%s", datx.str);
                 #endif

               if(n == 1)
                 #ifdef WIN32
                  #ifndef S_SPLINT_S
                  sprintf_s(dat_b, sizeof(dat_b),"%s", datx.str);
                  #else
                  snprintf(dat_b, sizeof(dat_b),"%s", datx.str);
                  #endif
                 #else
                 snprintf(dat_b, sizeof(dat_b),"%s", datx.str);
                 #endif
             }
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        if(n!=2) {
             Error("KONFIGURASI: masukan data salah");
        } else {
              //printf("a: %s\n", dat_a);
              //printf("b: %s\n", dat_b); 
              getFromConf(dat_a, dat_b, (char *)&val);
              strcpy(datx.str, val);

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

    return datx;
}

/* ************************************************* */
/* Environment Handle                                */
/* ************************************************* */

void getLingkup(const char *param, char retVal[MAX_STRING_LEN]) {
  char *ret=NULL;

  ret = (char*)getenv(param);

  if(ret != NULL && strlen(ret) > 0)
    strcpy(retVal, ret);
  else
    strcpy(retVal, "");

}

void setLingkup(const char *param, char nilai[MAX_STRING_LEN]) {
  char setnilai[MAX_STRING_LEN*2];

  memset(&setnilai,'\0', sizeof(setnilai));

  strcpy(setnilai, param);
  strcat(setnilai, "=");
  strcat(setnilai, nilai);

  // printf("setnilai : %s\n", setnilai);

  #ifndef S_SPLINT_S
  putenv(setnilai);
  #endif
}


int getFromConf(char *filename, char symbol[MAX_STRING_LEN], char result[MAX_STRING_LEN*2]) {
   FILE *configF=NULL;
   char buf[2048];
   char head;
   char *delim = " \n";

   int  i=0;
   char **get;

   char param[MAX_STRING_LEN];
   char value[MAX_STRING_LEN];
   char *val;

   get = NULL;
   val = NULL;

   configF = fopen(filename,"r");
   if(configF == NULL) {
     Error("gagal buka file : %s \n", filename);
     return 0;
   }

  memset(&buf, '\0', sizeof(buf));
  memset(&param, '\0', sizeof(param));
  memset(&value, '\0', sizeof(value));

  while(fgets(buf, (int)sizeof(buf), configF) != NULL) {

     head = buf[0];
     if(head != '#' && head != '\0' && head != '\n' && head != '\r') {
       // printf("%c\n",head);

       get = split(buf, delim);

       if(get != NULL) {
         for(i=0; get[i] != NULL; i++) {
           memset(&param[0], 0, sizeof(param));
           memset(&value[0], 0, sizeof(value));

           strcpy(param, get[0]);
           strcpy(value, get[1]);

         }
         split_free(get);
       }
       
       /* printf("param %s , value %s \n", param, value); */

       if(strcmp(param, symbol) == 0) {
           // printf("inside param %s\n", param);
           strcpy(result, value);
           // printf("got val %s \n", val);

           fclose(configF);

           if(get != NULL) {
             for(i=0; get[i] != NULL; i++) {
              // do nothing
             }
             if (get != NULL) {
               get--;
               free(get[0]);
               free(get);
             }
           }

           return 1;
       } 

     }
     memset(&buf, '\0', sizeof(buf));
  }
  fclose(configF);

  if(get != NULL) {
    for(i=0; get[i] != NULL; i++) {
      // do nothing
    }
    if (get != NULL) {
      get--;
      free(get[0]);
      free(get);
    }
  }

  return 1;
}

