// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyUnduhTeksPapanklip ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0, i=0, j=0;

  VAL_LABEL valdat,tmpdat,tmpdat2;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  GtkTextBuffer *buffer;

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 1) {
                strcpy(tmpMsg, lex.detail.string );
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
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("type %d\n", valdat.datatype);

			  if(valdat.datatype == 40 && valdat.GUItype == 12) { // Kertas
                if(n == 0) {
				  // printf("get Kertas\n");
				  tmpdat = valdat;
				  tmpdat.datatype = 40;
                } 
			  } else if(valdat.datatype == 51) { // CLIPBOARD
                if(n == 1) {
				  // printf("get Clipboard\n");
				  tmpdat2 = valdat;
				  tmpdat2.datatype = 51;
                } 
			  } else {
                Error("bentuk perintah Unduh_Teks_Papanklip salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah Unduh_Teks_Papanklip salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 2) {
      Error("parameter Unduh_Teks_Papanklip tidak lengkap");
    } else {
	  if(tmpdat.GUItype == 12) { // Kertas - textarea
         buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tmpdat.widget));
         gtk_text_buffer_paste_clipboard(buffer, tmpdat2.clipboard, NULL, 1); // paste
	  } else {
	     Error("parameter Unduh_Teks_Papanklip salah");
	  }
    }

	ungetlex();

}


