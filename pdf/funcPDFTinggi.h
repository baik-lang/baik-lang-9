// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcPDFTinggi ()
{
  VAL_LABEL datx;
  HPDF_Page ppage=NULL;
  

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));

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

           // datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 71) {  // get PDF page
             ppage = datx.pdf_page;
           } else {
             Error("pdf_tinggi: masukan data salah");
           }
  } else {
   Error("pdf_tinggi: masukan data salah");
  }

  if(ppage != NULL) {
    // get page width
    memset(&datx, '\0', sizeof(datx));
    datx.floatdata = HPDF_Page_GetHeight (ppage);
    datx.datatype = 1;   // double
  } else {
	printf("get W : ppage NULL\n");
  }

  //printf("get H %f\n", datx.floatdata);

  return datx;
}


