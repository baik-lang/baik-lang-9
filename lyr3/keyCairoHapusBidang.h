// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyCairoHapusBidang ()
{

  int  n=0;

  VAL_LABEL valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


  	do{

	  getlex();

	  switch( lex.type )
	    {
    
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

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 81) {  // cairo_surface

	            if(valdat.cr_surface != NULL)
                   cairo_surface_destroy(valdat.cr_surface);

			  } else {
                Error("bentuk perintah Hapus_Bidang salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah Hapus_Bidang salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	ungetlex();

  memset(&valdat, '\0', sizeof(valdat));

}

