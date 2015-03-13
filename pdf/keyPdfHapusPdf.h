// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyPdfHapus ()
{

  HPDF_Doc  pdf=NULL;

  VAL_LABEL valdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  // printf("keyPdfAkhirTeks\n");

  getlex();

  if( lex.type == TYPE_IDENT) {

	if(currentClass != NULL && strlen(currentClass) > 0) {
       sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
       //printf("construct class var: %s\n", class_tmpvar);
       valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
    } else {
       valdat = ValLabel( lex.detail.string, sub_deep, valdat, VAL_FLAG_SEARCH_R );
    }

    if(valdat.datatype == 70) {
      pdf = valdat.pdf;
	} else {
      Error("bentuk perintah pdf_hapus salah");
	}

  } else {
        Error("bentuk perintah pdf_hapus salah");
  }

  HPDF_Free(pdf);

}
