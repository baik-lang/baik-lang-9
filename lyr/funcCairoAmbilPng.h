// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcCairoAmbilPng ()
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
             datx = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 3) {
			 if(n == 1) {
               strcpy(fname, datx.str);
			 }
           } else {
             Error("bidang_ambilpng: masukan data salah");
           }
	} else if(lex.type == TYPE_STR) {
      if(n == 1) {
        strcpy(fname, lex.detail.string);
	  }
    } else {
      Error("bidang_ambilpng: masukan data salah");
    }

  if(n == 1) {
    memset(&datx, '\0', sizeof(datx));
	datx.cr_surface = cairo_image_surface_create_from_png (fname);
    datx.datatype = 81;   // cairo surface

    //printf ("get png ok\n");

  } else {
    Error("bidang_ambilpng: masukan data salah");
  }

  return datx;
}


