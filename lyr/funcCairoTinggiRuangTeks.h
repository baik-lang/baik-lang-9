// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcCairoTinggiRuangTeks ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;

  int n=0;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


    /* get referenced ident */
    getlex(); n++;

    /* printf("lex type : %d\n", lex.type);  */

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
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
           } else {
                valdat = ValLabel( lex.detail.string, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           }

           if(valdat.datatype == 84) {                // cairo_text_extents_t
			 if(n == 1) {
			   datx.val = valdat.cr_text_ext.height;  // height
			   datx.datatype = 0;
			 }
           } else {
             Error("lebar_ruang_teks: masukan data salah");
           }
    } else {
      Error("lebar_ruang_teks: masukan data salah");
    }

  if(n == 1) {
    datx.datatype = 0;   // int
  } else {
    Error("lebar_ruang_teks: masukan data salah");
  }

  return datx;
}


