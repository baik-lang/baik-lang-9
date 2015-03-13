// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyArrayDummy (char array_str[MAX_STRING_LEN])
{
  long  n=0, i=0, j=0;

  char dat_a[MAX_STRING_LEN];
  char dat_b[MAX_STRING_LEN];
  VAL_LABEL valdat,                            // for saving and returning value
	        valdat2, tmpdat;
  VAL_LABEL datx;

  char **get=NULL;

  char   tmpstr[MAX_STRING_LEN];

  char class_tmpvar[MAX_STRING_LEN];

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&datx, '\0', sizeof(datx));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&tmpstr, '\0', sizeof(tmpstr));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

       
         // printf("dummy array = %d, tmp renban %d\n", checkDummyArray(lex.detail.array_str), renban );
         
         getArrayName(array_str, (char *)&valdat.array_str);
         getArrayName(array_str, (char *)&valdat.array_name);
         strcpy(valdat.array_idx, "0");

         if(currentClass != NULL && strlen(currentClass) > 0) {
           sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_name);
           //printf("construct class var: %s\n", class_tmpvar);
           memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));
           strcpy(valdat.array_name, class_tmpvar);
         }

         strcat(valdat.array_str, "[256]");

         /* printf("store init array : type %d\n", valdat.datatype); */

         getlex();
         if( lex.type == _EOF )
	       Error("interupsi yang tidak diinginkan");

         if( lex.detail.symbol != '=' )                          /* substitute */
	       Error("bbb untaian salah masukan");

         getlex();
         if( lex.type == _EOF )
           Error("interupsi yang tidak diinginkan");

         /* ******************************************************************* */
         /* PISAH Function */
         /* ******************************************************************* */
         if(! strcmp(lex.detail.string, "pisah")  || !strcmp(lex.detail.string, "PISAH") ) {
           /* printf("%d %s\n",strcmp(lex.detail.string, "pisah"), lex.detail.string);  */
           /* printf("tulis PISAH function\n"); */
           memset(&dat_a, '\0', sizeof(dat_a));
           memset(&dat_b, '\0', sizeof(dat_b));

           n = 0; i = 0;
           do {
             getlex();
             /* printf("%d %s\n",n, lex.detail.string); */

             if(lex.type == TYPE_NUM || lex.type == TYPE_DBL) {
              Error("PISAH: masukan data salah");
             } else if(lex.type == TYPE_STR || lex.type == TYPE_DBL) {
               if(n == 0) {
                 strcpy(dat_a, lex.detail.string);
               } else
               if(n == 1) {
                 strcpy(dat_b, lex.detail.string);
               }
             } else if(lex.type == TYPE_ARRAY) {
              Error("PISAH: masukan data salah");
             } else {
               tmpdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
               /* printf("PISAH GET IDENT : %d\n", tmpdat.datatype); */
               if(tmpdat.datatype == 3) {
                 if(n == 0) {
                   strcpy(dat_a, tmpdat.str);
                 } else
                 if(n == 1) {
                   strcpy(dat_b, tmpdat.str);
                 }
               }
               else
               if(tmpdat.datatype == 10) {
                 // do nothing
               }

             }

             n++;

             getlex();

           }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');
           ungetlex();

           /* printf("n:%d\n", n); */

           if(n!=2) {
	         Error("PISAH: masukan data salah");
           } else {
             /*
             printf("a: %s\n", dat_a); 
             printf("b: %s\n", dat_b); 
             */

             if(tmpdat.datatype == 10) {
               valdat.long_str = tmpdat.long_str;
               valdat.array_max = tmpdat.array_max;
               valdat.isLongStr = 1;
               valdat.datatype  = 10;

             } else {
			   // store each value as array for real value ... do not use char** (refering only)
               get = NULL;
               get = split(dat_a, dat_b);
               for(j = 0; get[j]!=NULL; j++) {
				 if(j==0) {
			       valdat.array_s = createRenban(renban);
			       valdat.datatype = 8;
				 }
				 memset(&tmpstr, '\0', sizeof(tmpstr));
				 strcpy(tmpstr, get[j]);
                 save_str_array(valdat, j, tmpstr);
               }
               valdat.array_max = j;
               split_free(get);

             }

             ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_W );
             memset(&valdat, '\0', sizeof(valdat));

           }
           /* printf("split write dummy array ok\n"); */

		 } else

         /* ******************************************************************* */
         /* a[] = {1,2,3,4,5} */
         /* ******************************************************************* */
		 if(strncmp(lex.detail.string, "{", 1) == 0 ) {
           /* printf("%d %s\n",strcmp(lex.detail.string, "pisah"), lex.detail.string);  */
		   // printf("Def Array {...}\n");

           renban++;
		   if(renban > 999) {
             renban = 0;
		   }

           n = 0; i = 0;
           do {
             getlex();
             /* printf("%d %s\n",n, lex.detail.string); */

             if(lex.type == TYPE_NUM) {
			   //printf("%d\n", lex.detail.num);
			   if(n==0) {
			     valdat.array_i = createRenban(renban);
				 valdat.datatype = 6;
			   }
			   save_int_array(valdat, n, lex.detail.num);
             } else if(lex.type == TYPE_DBL) {
			   //printf("%f\n", lex.detail.dblnum);
			   if(n==0) {
			     valdat.array_d = createRenban(renban);
				 valdat.datatype = 7;
			   }
			   save_dbl_array(valdat, n, lex.detail.dblnum);
             } else if(lex.type == TYPE_STR) {
			   //printf("%s\n", lex.detail.string);
			   if(n==0) {
			     valdat.array_s = createRenban(renban);
				 valdat.datatype = 8;
			   }
			   save_str_array(valdat, n, lex.detail.string);
             } else if(lex.type == TYPE_IDENT) {
               tmpdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
               if(tmpdat.datatype == 0) {
				 //printf("%d\n", tmpdat.val);
			     if(n==0) {
			       valdat.array_i = createRenban(renban);
				   valdat.datatype = 6;
			     }
			     save_int_array(valdat, n, tmpdat.val);
               } else
               if(tmpdat.datatype == 1) {
				 //printf("%f\n", tmpdat.floatdata);
			     if(n==0) {
			       valdat.array_d = createRenban(renban);
				   valdat.datatype = 7;
			     }
				 save_dbl_array(valdat, n, tmpdat.floatdata);
               } else
               if(tmpdat.datatype == 3) {
				 //printf("%s\n", tmpdat.str);
			     if(n==0) {
			       valdat.array_s = createRenban(renban);
				   valdat.datatype = 8;
			     }
				 save_str_array(valdat, n, tmpdat.str);
			   } else {
				   Error("data untaian: salah masukan");
			   }

			 } else {
			   Error("data untaian: salah masukan");
			 }

             n++;

			 // skip comma
             getlex();

           }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

		   // do not ungetlex() - skip sym }
		   if( strncmp(lex.detail.string , "}", 1) != 0 ) {
			 Error("data untaian : tanpa tanda }");
           }

           getlex();
		   //printf("next lex %s\n", lex.detail.string);
		   ungetlex();

           //printf("create array with n:%d\n", n);

           if(n >= MAX_ARRAY) {
	         Error("untaian: melebihi kapasitas");
           } else {
             valdat.array_max = n;
             valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_W );

           }

           if(valdat.array_i != '\0')
			   valdat.array_i = '\0';
           if(valdat.array_d != '\0')
			   valdat.array_d = '\0';
           if(valdat.array_s != '\0')
			   valdat.array_s = '\0';

		   memset(&valdat, '\0', sizeof(valdat));

         } else

         /* ******************************************************************* */
         /* BACA_DIR Function */
         /* ******************************************************************* */
         if(! strcmp(lex.detail.string, "baca_dir")  || !strcmp(lex.detail.string, "BACA_DIR") ) {
             /* printf("tulis BACA_DIR function\n"); */
             memset(&dat_a, '\0', sizeof(dat_a));
             memset(&dat_b, '\0', sizeof(dat_b));

             n = 0; i = 0;

             getlex();
             /* printf("%d %s\n",n, lex.detail.string); */

             if( lex.type == _EOF )
               Error("interupsi yang tidak diinginkan");

             if(lex.type == TYPE_NUM || lex.type == TYPE_DBL) {
                Error("BACA_DIR: masukan data salah");
             } else if(lex.type == TYPE_STR) {
               strcpy(dat_a, lex.detail.string);
             } else if(lex.type == TYPE_ARRAY) {
              Error("BACA_DIR: masukan data salah");
             } else {
               tmpdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
               if(tmpdat.datatype == 3) {
                 strcpy(dat_a, tmpdat.str);
               }
             }

			 /* printf("a: %s\n", dat_a);  */

			 // store each value as array for real value ... do not use char** (refering only)
             get = NULL;

             #ifdef WINDOWS
             get = win_dir_content(dat_a);
             #else
             get = (char **)dir_content(dat_a);
             #endif

             for(j = 0; get[j]!=NULL; j++) {

			   if(j==0) {
			     valdat.array_s = createRenban(renban);
			     valdat.datatype = 8;
			   }
			   memset(&tmpstr, '\0', sizeof(tmpstr));
			   strcpy(tmpstr, get[j]);
               save_str_array(valdat, j, tmpstr);

             }

             valdat.array_max = j;
             split_free(get);

             ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_W );
             memset(&valdat, '\0', sizeof(valdat));                          

             #ifdef WINDOWS
  	         if(dirtp != NULL) {
	           free (dirtp);
	         }
             #else
             if(owndir != NULL) {
               closedir (owndir);
             }
             #endif

             /* printf("write dummy array ok\n"); */

		 } 
         /* printf("endif array FUNC OK\n"); */

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

}

