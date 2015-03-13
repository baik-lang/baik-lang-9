// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyPdfSimpanPdf ()
{

  int  n=0;

  HPDF_Doc  pdf=NULL;
  char   fname[MAX_STRING_LEN];

  VAL_LABEL valdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
  memset(fname, '\0', sizeof(fname));

  n = 0;

  // printf("keyPdfSimpanPdf\n");
	do{

	  getlex();

	  switch( lex.type )
	    {

	    case TYPE_STR:
			if(n == 1) {
			  strcpy(fname, lex.detail.string);
			}
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

              if(valdat.datatype == 70) { // PDF
                if(n == 0) {
				  pdf = valdat.pdf;
				}
			  } else if(valdat.datatype == 3) {
                if(n == 1) {
				  strcpy(fname, valdat.str);
				}
			  } else {
                Error("bentuk perintah pdf_teks salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah pdf_teks salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(n!=2) {
      Error("bentuk perintah pdf_teks salah");
	} else {
      HPDF_SaveToFile (pdf, fname);
	}

	ungetlex();

}
