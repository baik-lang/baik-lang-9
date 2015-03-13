// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// ambil teks dari label

VAL_LABEL funcWinTeksLabel ()
{

  int  n=0;

  VAL_LABEL datx,valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  // printf("enter Teks_Label\n");

	  getlex();
      // printf(" DEBUG: grup_tombol_radio lex.type %d , lex.symbol %c\n", lex.type , lex.detail.symbol);

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
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {
                //ungetlex();
                // valdat = expression("",0);

		valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              // printf("ident type %d\n", valdat.datatype);

              if(valdat.datatype == 40) {
                if(n == 0) {
		  // printf("grup tombol : get widget\n");
		  tmpdat.widget   = valdat.widget;
		  tmpdat.eventbox = valdat.eventbox;
		  tmpdat.GUItype  = valdat.GUItype;
		  // printf("get GUItype %d\n", valdat.GUItype);
                  tmpdat.datatype = 40;
                } 
			  } else {
                Error("bentuk perintah teks_label salah 0");
			  }

	      break;

	    default:
	      Error("bentuk perintah teks_label salah 1");
	    }

      // printf("GUI type %d\n", tmpdat.GUItype);
    
	  if(tmpdat.GUItype == 4) {  // Label
	    strcpy(datx.str , g_locale_from_utf8(gtk_label_get_text(GTK_LABEL(tmpdat.widget)),
                              -1,
                              NULL,
                              NULL,
                              NULL) );
	  } else {
        Error("Salah parameter untuk Teks_Label");
	  }

	 datx.datatype = 3;   // string
	 return datx;


}


