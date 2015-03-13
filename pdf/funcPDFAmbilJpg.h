// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcPDFAmbilJpg ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  int n=0;
  char fname[MAX_STRING_LEN];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&fname, '\0', sizeof(fname));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  do {
    /* get referenced ident */
    getlex();

    /* printf("lex type : %d\n", lex.type);  */

    if(lex.type == TYPE_IDENT) {

           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
             //printf("construct class var: %s\n", class_tmpvar);
             datx = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 70) {  // get PDF
			 if(n==0) {
               valdat = datx;
			   valdat.datatype = datx.datatype;
			 }
		   } else if(datx.datatype == 3) {
			 if(n == 1) {
               strcpy(fname, datx.str);
			 }
           } else {
             Error("pdf_ambiljpg: masukan data salah");
           }
	} else if(lex.type == TYPE_STR) {
      if(n == 1) {
        strcpy(fname, lex.detail.string);
	  }
    } else {
      Error("pdf_ambiljpg: masukan data salah");
    }

	n++;
	getlex();

  }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');
  
  ungetlex();

  if(n == 2) {
	// make new page
    //printf ("pdf get jpg %s\n", fname);

    memset(&datx, '\0', sizeof(datx));
	datx.pdf_image = HPDF_LoadJpegImageFromFile (valdat.pdf, fname);
    datx.datatype = 73;   // pdf image

    //printf ("pdf get jpg ok\n");

  } else {
    Error("pdf_ambiljpg: masukan data salah");
  }

  return datx;
}


