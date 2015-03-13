// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// ambil teks dari kertas

VAL_LABEL funcWinTeksTerpilih ()
{

  int  n=0;

  VAL_LABEL datx,valdat,tmpdat;
 
  GtkTextIter   start, end;
  gchar         *utf8_text;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  // printf("enter teks_masukan\n");

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
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {
                //ungetlex();
                // valdat = expression("",0);

				tmpdat.datatype = 40;
				valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              // printf("ident type %d\n", valdat.datatype);

              if(valdat.datatype == 40) {
                if(n == 0) {
				  // printf("grup tombol : get widget\n");
				  tmpdat.widget   = valdat.widget;
				  tmpdat.eventbox = valdat.eventbox;
				  tmpdat.GUItype  = valdat.GUItype;
                  tmpdat.datatype = 40;
                } 
			  } else {
                Error("bentuk perintah posisi_kertas salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah posisi_kertas salah");
	    }
     
	  if(tmpdat.GUItype == 12) {  // Kertas - Text Area
		  datx.buffer = NULL;
		  datx.buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tmpdat.widget));
		  datx.val = gtk_text_buffer_get_selection_bounds(datx.buffer, &start, &end);

		  utf8_text = gtk_text_buffer_get_text (datx.buffer, &start, &end, TRUE);

		  // Dont make malloc
		  datx.str2 = NULL;
		  datx.str2 = utf8_text;

		  datx.IterStart = start;
		  datx.IterEnd   = end;
	      datx.datatype = 50;   // GtkTeksBuffer
	  } else {
        Error("Salah parameter untuk Posisi_Kertas");
	  }

	 return datx;


}

