// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyPdfWarnaHuruf ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0, mysize=0;

  HPDF_Doc  pdf=NULL;
  HPDF_Page ppage=NULL;

  VAL_LABEL valdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

    //printf("keyPdfSetHuruf\n");
	do{

	  getlex();

	  switch( lex.type )
	    {

	    case TYPE_STR:
			if(n == 1)
			  strcpy(tmpMsg, lex.detail.string);
	      break;  

	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

			  if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
              } else {
                valdat = ValLabel( lex.detail.string, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }


              if(valdat.datatype == 71) {
                if(n == 0) {
				  pdf = valdat.pdf;
				  ppage = valdat.pdf_page;
				  if(ppage == NULL) {
				    printf("ppage NULL !\n");
				  }
				}

			  } else if(valdat.datatype == 3) {
				if(n == 1)
				  strcpy(tmpMsg, valdat.str);
			  } else {
                Error("bentuk perintah pdf_warnahuruf salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah pdf_warnahuruf salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(n!=2) {
      Error("bentuk perintah pdf_warnahuruf salah");
	} else {
      if( ! strcmp(tmpMsg, "MERAH") || ! strcmp(tmpMsg, "merah") )
         HPDF_Page_SetRGBFill (ppage, 1.0, 0.0, 0.0);
      if( ! strcmp(tmpMsg, "HIJAU") || ! strcmp(tmpMsg, "hijau") )
         HPDF_Page_SetRGBFill (ppage, 0.0, 1.0, 0.0);
      if( ! strcmp(tmpMsg, "BIRU") || ! strcmp(tmpMsg, "biru") )
         HPDF_Page_SetRGBFill (ppage, 0.0, 0.0, 1.0);
      if( ! strcmp(tmpMsg, "HITAM") || ! strcmp(tmpMsg, "hitam") )
         HPDF_Page_SetRGBFill (ppage, 0.0, 0.0, 0.0);
      if( ! strcmp(tmpMsg, "PUTIH") || ! strcmp(tmpMsg, "putih") )
         HPDF_Page_SetRGBFill (ppage, 1.0, 1.0, 1.0);


	  //printf("line RGB color ok\n");
	}

	ungetlex();

}

