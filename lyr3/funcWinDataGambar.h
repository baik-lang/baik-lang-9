// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinDataGambar  ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int    n=0, i=0, pos=0;
  int    idx=0;

  GError    *error = NULL;

  char      class_tmpvar[MAX_STRING_LEN];
  char      tmpstr[MAX_STRING_LEN];
  char      tmpstr2[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&tmpstr, '\0', sizeof(tmpstr));
  memset(&tmpstr2, '\0', sizeof(tmpstr2));

  // printf("HapusSelTabel\n");

  n = 0;

	do{
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
		     if(n == 1)
               pos = lex.detail.num;
           } else
           if(lex.type == TYPE_IDENT) {
		     // printf("get type IDENT \n");

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

			 // printf("get type type %d with n %d\n", valdat.datatype, n);
             // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 0) {
                if(n == 1) {
				  pos = valdat.val;
                } 
			 } else
			 if(valdat.datatype == 45) {
                if(n == 0) {
				  tmpdat = valdat;
				  for(i=0;i<20;i++)
				    tmpdat.pixbuf[i] = valdat.pixbuf[i];

                    // memset(&tmpstr2, '\0', sizeof(tmpstr2));
				    // sprintf(tmpstr2, "valdatpic2.png");
					// gdk_pixbuf_save (valdat.pixbuf[2], tmpstr2, "png", &error, NULL);

                } 
             } else {
				 Error("Salah: Data_Gambar salah masukan");
			 }

           } else {
             Error("Salah: Data_Gambar salah masukan");
           }


        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

  ungetlex();

  if(n == 2) {
    // printf("Data Gambar pos %d\n", pos);

    strcpy(datx.tblcoltype,"<GAMBAR>");

    // memset(&tmpstr2, '\0', sizeof(tmpstr2));
	// sprintf(tmpstr2, "datapic%d.png",pos);
    // gdk_pixbuf_save (tmpdat.pixbuf[pos], tmpstr2, "png", &error, NULL);

    datx.pixbuf[0] = tmpdat.pixbuf[pos];
	datx.isGUI     = 1;
    datx.datatype  = 46; // A single pixbuf data - see defValLabel
  } else {
    Error("Salah: Data_Gambar salah masukan");
  }

  return datx;

}


