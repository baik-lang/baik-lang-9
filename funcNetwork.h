// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcPing ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  int  n=0, i=0, j=0;
  int  dat_num=0, dat_num2=0;

  char   tmpMsg[MAX_STRING_LEN * 2];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             if(n == 1) {
               dat_num = lex.detail.num;
             } else
             if(n == 2) {
               dat_num2 = lex.detail.num;
             }
           } else if(lex.type == TYPE_STR) {
             if(n == 0) {
               strcpy(dat_a, lex.detail.string);
             } 
           } else if(lex.type == TYPE_IDENT) {
              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
              } else {
                valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }

              if(valdat.datatype == 0) {
                if(n == 1) {
				  dat_num = valdat.val;
                } else
                if(n == 2) {
                  dat_num2 = valdat.val;
                }
			  } else
              if(valdat.datatype == 3) {
                if(n == 0) {
				  strcpy(dat_a, valdat.str);
                } 
			  }
		   }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n==3) {
          //printf("hostname: %s\n", dat_a);     // hostname
          //printf("ping num: %d\n", dat_num);        // exe times
          //printf("ping timeout: %d\n", dat_num2);   // timeout
          
          #ifdef WINDOWS
            datx.val = Ping_win(dat_a, dat_num, dat_num2);
            datx.datatype  = 0;
          #else
            datx.val = Ping_ux(dat_a, dat_num, dat_num2);
            datx.datatype  = 0;
          #endif

        } else {
          Error("PING: masukan data salah");
        }

  return datx;
}

VAL_LABEL funcIKAT_SOKET ()
{
  VAL_LABEL datx;
  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  int  n=0, i=0, j=0;
  int  dat_num=0, dat_num2=0;

  #ifdef WINDOWS
  SOCKET  tmpSock;
  #else
  int     tmpSock;
  #endif

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("inside funcIKAT_SOKET\n");
  memset(&datx, '\0', sizeof(datx));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
	         Error("IKAT_SOKET: masukan data salah");
           } else if(lex.type == TYPE_STR) {
             if(n == 1)
              strcpy(dat_b, lex.detail.string);
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
               if(n == 0)
                 if(datx.datatype == 4 || datx.datatype == 5) {
                   i = datx.datatype;
                   tmpSock = datx.sock;
                 }
               if(n == 1)
                 strcpy(dat_b, lex.detail.string);
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=2) {
	     Error("IKAT_SOKET: masukan data salah");
        } else {
             /* printf("b: %s\n", dat_b); */

             #ifdef WINDOWS
			  // printf(" start ikatSocket...\n");
              datx.sock = ikatSocket(tmpSock, dat_b); 
             #else
              datx.sock = ux_ikatSocket(tmpSock, dat_b);
             #endif

             datx.datatype = i;

             ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_W );

             // printf("ikat socket: %s type %d\n", dat_b, i);
        }


  return datx;
}

VAL_LABEL funcTRIMA_SOKET ()
{
  VAL_LABEL datx;

  char   class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


  // printf("inside funcTRIMA_SOKET\n");

         getlex();

         if(lex.type == TYPE_NUM) {
           Error("TRIMA_SOKET: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           Error("TRIMA_SOKET: masukan data salah");
         } else {

           datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );

           if(datx.datatype == 4 || datx.datatype == 5) {
             if(datx.sock == '\0' ) {
               Error("socket null");
             }

             #ifdef WINDOWS
              //printf("...");
	      fflush(stdout);
	      //printf("sock: %s\n", datx.ident);
	      // printf(".\n", datx.datatype);
              datx.sock = terimaSocket(datx.sock); 
             #else
              datx.sock = ux_terimaSocket(datx.sock);
             #endif

           } else {
             Error("TRIMA_SOKET: masukan data salah");
           }
         }

    return datx;
}

VAL_LABEL funcBACA_SOKET ()
{
  VAL_LABEL datx;

  char   class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  // printf("inside funcBACA_SOKET\n");

         getlex();

         if(lex.type == TYPE_NUM) {
           Error("BACA_SOKET: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           Error("BACA_SOKET: masukan data salah");
         } else {
           datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 4 || datx.datatype == 5) {

             #ifdef WINDOWS
              strcpy(datx.str , bacaSocket(datx.sock) ); 
             #else
              strcpy(datx.str , (char *)ux_bacaSocket(datx.sock) );
             #endif

              datx.datatype = 3;
           } else {
             Error("BACA_SOKET: masukan data salah");
           }
         }

      return datx;
}

VAL_LABEL funcTULIS_SOKET ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat,tmpdat;
  int    i=0,j=0,n=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  long    idx=0;

  #ifdef WINDOWS
  SOCKET  tmpSock;
  #else
  int     tmpSock;
  #endif

  char   class_tmpvar[MAX_STRING_LEN];

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

           if(lex.type == TYPE_NUM) {
             if(n == 1) {
               sprintf(dat_b, "%li", lex.detail.num);
             }
           } else if(lex.type == TYPE_STR || lex.type == TYPE_DBL) {
             if(n == 1) {
               strcpy(dat_b, lex.detail.string);
             }
           } else if(lex.type == TYPE_ARRAY) {
             if(n == 1) {

               if(strlen(lex.detail.array_str) > 0) {
                 strcpy(valdat.array_str, lex.detail.array_str);
                 getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                 getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                 if(currentClass != NULL && strlen(currentClass) > 0) {
                   sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_name);
                   //printf("construct class var: %s\n", class_tmpvar);
                   memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));
                   strcpy(valdat.array_name, class_tmpvar);

                   if(!isdigit(valdat.array_idx[0])) {
                     memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                     sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_idx);
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

				 sprintf(valdat.array_idx, "%li", idx);

                 if(idx < 0 || idx > MAX_ARRAY)
                   Error("ukuran Untaian tidak sesuai kapasitas");

                 if(valdat.datatype == 6) {
                   if(valdat.array_i == '\0')
                     Error("tulis_soket: ukuran Untaian belum terdefinisi");

                   sprintf(dat_b, "%d", get_int_array(valdat, idx));
                 } else if(valdat.datatype == 7) {
                   if(valdat.array_d == '\0')
                     Error("tulis_soket: ukuran Untaian belum terdefinisi");

                   sprintf(dat_b, "%f", get_dbl_array(valdat, idx) );
                 } else if(valdat.datatype == 8) {
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
  					  printf("nilai untaian kata tidak ditemukan\n");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);
                      strcpy(dat_b, TmpStrBox.str.mystring);
					}

				  }


                   // strcpy(dat_b, valdat.array_s[idx].str);
                 }
               }

             }
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
               if(n == 0)
                 if(datx.datatype == 4 || datx.datatype == 5) {
                   i = datx.datatype;
                   tmpSock = datx.sock;
                 }
               if(n == 1)
                 strcpy(dat_b, lex.detail.string);
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=2) {
	     Error("TULIS_SOKET: masukan data salah");
        } else {
             /* printf("b: %s\n", dat_b); */

             #ifdef WINDOWS
              datx.val = tulisSocket(tmpSock, dat_b); 
             #else
              datx.val = ux_tulisSocket(tmpSock, dat_b);
             #endif

             datx.datatype = 0;
             /* printf("konfig: %s\n", datx.str); */
        }

        return datx;
}


VAL_LABEL funcKONEK_SOKET ()
{
  VAL_LABEL datx;
  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  int  n=0, i=0, j=0;

  #ifdef WINDOWS
  SOCKET  tmpSock;
  #else
  int     tmpSock;
  #endif

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
	     Error("KONEK_SOKET: masukan data salah");
           } else if(lex.type == TYPE_STR) {
             if(n == 1)
              strcpy(dat_a, lex.detail.string);
             if(n == 2)
              strcpy(dat_b, lex.detail.string);
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
               if(n == 0)
                 if(datx.datatype == 4 || datx.datatype == 5) {
                   i = datx.datatype;
                   tmpSock = datx.sock;
                 }
               if(n == 1)
                 strcpy(dat_a, lex.detail.string);
               if(n == 2)
                 strcpy(dat_b, lex.detail.string);
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=3) {
	     Error("KONEK_SOKET: masukan data salah");
        } else {
             /* printf("b: %s\n", dat_b); */
             #ifdef WINDOWS
              datx.val = connectSocket(tmpSock, dat_a, dat_b); 
             #else
              datx.val = ux_connectSocket(tmpSock, dat_a, dat_b);
             #endif

             datx.datatype = 0;
             /* printf("konfig: %s\n", datx.str); */
        }

          return datx;
}
