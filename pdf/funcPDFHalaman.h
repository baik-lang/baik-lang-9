// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcPDFHalaman ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

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

           if(datx.datatype == 70) {  // get PDF
			 if(datx.pdf == NULL) {
			   Error("gagal ambil definisi pdf");
			 }
             valdat = datx;
			 valdat.datatype = datx.datatype;
           } else {
             Error("pdf_halaman: masukan data salah");
           }
  } else {
   Error("pdf_halaman: masukan data salah");
  }

  // make new page
  memset(&datx, '\0', sizeof(datx));
  datx.pdf      = valdat.pdf;
  datx.pdf_page = HPDF_AddPage (valdat.pdf);
  datx.datatype = 71;   // pdf halaman

  return datx;
}


