// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyCairoPucukGaris ()
{

  int  n=0, mysize=0;

  cairo_t *cr=NULL;
  double x=0.0;

  char   teks[MAX_STRING_LEN];

  VAL_LABEL valdat, valdat2, tmpdat;
  int idx=0;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
  memset(teks, '\0', sizeof(teks));

  n = 0;

  // printf("keyCairoPucukGaris\n");
	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
			if(n == 1) {
			  strcpy(teks, lex.detail.string);
			} 
	      break;   

	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

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

              if(valdat.datatype == 80) { // cairo img
                if(n == 0) {
				  cr = valdat.cr_img;
				}
			  } else if(valdat.datatype == 3) {
                if(n == 0) {
				  strcpy(teks, valdat.str);
				}

			  } else {
                Error("bentuk perintah pucuk_garis salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah pucuk_garis salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	ungetlex();

	if(n!=2) {
      Error("bentuk perintah pucuk_garis salah");
	} else {
	  if( ! strcmp(teks, "bundar") || ! strcmp(teks, "BUNDAR")) {
	    // printf("set cap bundar\n");
        cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND);
	  } else
	  if( ! strcmp(teks, "normal") || ! strcmp(teks, "NORMAL")) {
	    // printf("set cap normal\n");
        cairo_set_line_cap  (cr, CAIRO_LINE_CAP_BUTT);
	  } else {
        cairo_set_line_cap  (cr, CAIRO_LINE_CAP_BUTT);
	  }
	}

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

}


