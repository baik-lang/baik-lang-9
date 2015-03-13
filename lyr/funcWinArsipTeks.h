// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2012
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

VAL_LABEL funcBacaTeks ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int  n=0, i=0, x1=0;
  int  idx=0;

  FILE    *tmpfile=NULL;
  struct stat st;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        getlex();
        /* printf("%d %s\n",n, lex.detail.string); */
		// showDialog("start BacaTeks", "BacaTeks");

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

         // valdat = ValLabel( lex.detail.ident, datx, VAL_FLAG_SEARCH_R );
         if(valdat.datatype == 2) {           // File
           tmpfile = valdat.filedata;

		   // printf("get filename : %s\n", valdat.sub_file);
		   if( stat( valdat.sub_file, &st ) != 0 ){
			   Error( "Baca_Teks : Arsip tidak ditemukan \n");
			  datx.val = 0;
           }

		   datx.str2 = (char *)calloc(st.st_size + 2, sizeof(char));
		   if( datx.str2 == NULL ){
             fprintf( stderr, "memori tidak cukup\n" );
			 datx.val = 0;
             exit( -1 );
           }

		   // printf("store text:\n");
		   i = 0;
		   while (fscanf(valdat.filedata, "%c", &x1) ==1) {
			   datx.str2[i] = x1;
			   // printf("%c", x1);
			   i++;
		   }
		   datx.str2[i] = '\0'; // close with NULL

		   datx.val = 1;


           datx.datatype = 41; // special long text

         }
        }


    return datx;
}


VAL_LABEL funcWinSeluruhArsip ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  gsize  length=0;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        getlex();
		// showDialog("start BacaTeks", "WinSeluruhArsip");
        // printf(" get lex type %d %s\n", lex.type, lex.detail.string);

        if(lex.type == TYPE_STR) {
		 // showDialog("get TYPE_STR", "WinSeluruhArsip");
		 g_file_get_contents (lex.detail.string, &datx.str2, &length, NULL);
		 datx.val = 1;
         datx.datatype = 41; // special long tex

		} else if(lex.type == TYPE_IDENT) {
		 // showDialog("get TYPE_IDENT", "WinSeluruhArsip");
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

		 // printf("seluruh_arsip : get type %d , name : %s \n", valdat.datatype, valdat.str);

		 // showDialog(valdat.str, "WinSeluruhArsip");

         if(valdat.datatype == 3 || valdat.datatype == 44) {     // str or filename from dialog
		   g_file_get_contents (valdat.str, &datx.str2, &length, NULL);
		   datx.val = 1;
           datx.datatype = 41; // special long text

		   // printf("**********\n");
		   // printf("%s\n", datx.str2);
		   // printf("**********\n");

         } else {
		   // showDialog("get NOTHING!", "WinSeluruhArsip");
		 }

        }

		// printf("seluruh_arsip OK\n");

    return datx;
}

VAL_LABEL funcWinPisahBarisArsip ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int  num_lines=0;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        getlex();
        /* printf("%d %s\n",n, lex.detail.string); */

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

         // valdat = ValLabel( lex.detail.ident, datx, VAL_FLAG_SEARCH_R );
		 if(valdat.datatype == 41 && valdat.str2 != NULL) {  // special long text
		   datx.long_str = g_strsplit(valdat.str2, "\n", 0);
		   datx.isLongStr = 1;

		   num_lines = 0;
		   while(datx.long_str[num_lines] != NULL) {
	           num_lines++;

               // printf("-> %s\n", datx.long_str[num_lines]);
		   }
		   datx.val = num_lines;
           // printf("=> tot %d \n", num_lines);

           datx.datatype = 100; // teks per baris
         }
        }

		// printf("pisah_baris_arsip OK\n");

    return datx;
}

VAL_LABEL funcWinJumlahBarisArsip ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int  num_lines=0;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        getlex();
        /* printf("%d %s\n",n, lex.detail.string); */

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

         // valdat = ValLabel( lex.detail.ident, datx, VAL_FLAG_SEARCH_R );
		 if(valdat.datatype == 100) {  // teks per baris
		   datx.val = valdat.val;
           datx.datatype = 0;
         }
        }

		// printf("jumlah_baris_arsip OK\n");

    return datx;
}

VAL_LABEL funcWinTeksPerBaris ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int  n=0;
  int  num=0;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  n = 0;

  // printf ("teks_per_baris ................\n");

  do {
        getlex();
        /* printf("%d %s\n",n, lex.detail.string); */

        if(lex.type == TYPE_NUM) {
          if(n == 1) {
			num = lex.detail.num;
          } 

		} else if(lex.type == TYPE_DBL) {
          if(n == 1) {
			num = (int)lex.detail.dblnum;
          } 

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
           valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
         } else {
           valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
         }

		 if(valdat.datatype == 100) {  // teks per baris
          if(n == 0) {
            tmpdat.long_str = valdat.long_str;
		    tmpdat.val = valdat.val;
            tmpdat.datatype = valdat.datatype;
			// printf("get teks all baris \n");
		  }

		 } else if(valdat.datatype == 0) { 
          if(n == 1) {
			num = valdat.val;
			// printf("get i %d \n", num);
          } 

		 } else if(valdat.datatype == 1) { 
          if(n == 1) {
		    num = (int)valdat.floatdata;
          } 
		 }

		}

        n++;

	    getlex(); // pass comma

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' && lex.type != _EOF);

    ungetlex();

	if(n == 2) {
      // printf("extract baris, get teks \n");

	  if( tmpdat.long_str[num] != NULL)
        strcpy(datx.str, tmpdat.long_str[num]);
	  else
        strcpy(datx.str, "");
	} else {
      Error("parameter pada kode perintah teks_per_baris salah ");
	}

    datx.datatype = 3;

	// printf("teks_per_baris OK\n");

    return datx;
}

