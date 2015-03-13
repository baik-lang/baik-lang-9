// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// Set warna huruf to Sel Ranting (Tree)

void keyJenisHurufRanting ()
{
  int  n=0;

  char tmpMsg[MAX_STRING_LEN];
  char tmpMsg2[MAX_STRING_LEN];

  VAL_LABEL valdat, valdat2, tmpdat, tmpdat2;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));
  memset(tmpMsg2, '\0', sizeof(tmpMsg2));

  n = 0;
  // printf("JenisHurufRanting ...\n");

	do{

      getlex();

	  switch( lex.type )
	    {
	    
	    case TYPE_STR:
              if(n == 1) {
                strcpy(tmpMsg, lex.detail.string );
              } else
              if(n == 2) {
                strcpy(tmpMsg2, lex.detail.string );
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
                valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              } else {

				valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 3) {
                if(n == 1) {
                  sprintf(tmpMsg, "%s" , valdat.str );
                } else
                if(n == 2) {
                  sprintf(tmpMsg2, "%s" , valdat.str );
                } 
			  } else if(valdat.datatype == 57) {        // Cell Renderer
                if(n == 0) {
				  tmpdat  = valdat;
                  tmpdat.datatype = 57;
                } 
			  } else {
                Error("bentuk perintah jenishuruf_sel salah");
			  }

	      break;

	      default:
	        Error("bentuk perintah jenishuruf_sel salah");

	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	// printf("Jenis : %s %s\n", tmpMsg, tmpMsg2);

	if(n == 3) {
		if( ! strcmp(tmpMsg, "normal") && ! strcmp(tmpMsg2, "normal")) {
          g_object_set(tmpdat.renderer, "weight", PANGO_WEIGHT_NORMAL, NULL);
          g_object_set(tmpdat.renderer, "style", PANGO_STYLE_NORMAL, NULL);
		} else
		if( ! strcmp(tmpMsg, "tebal") && ! strcmp(tmpMsg2, "normal")) {
          g_object_set(tmpdat.renderer, "weight", PANGO_WEIGHT_BOLD, "weight-set", TRUE, NULL);
          g_object_set(tmpdat.renderer, "style", PANGO_STYLE_NORMAL, NULL);
		} else
		if( ! strcmp(tmpMsg, "normal") && ! strcmp(tmpMsg2, "miring")) {
          g_object_set(tmpdat.renderer, "weight", PANGO_WEIGHT_NORMAL, NULL);
          g_object_set(tmpdat.renderer, "style", PANGO_STYLE_ITALIC, NULL);
		} else
		if( ! strcmp(tmpMsg, "tebal") && ! strcmp(tmpMsg2, "miring")) {
          g_object_set(tmpdat.renderer, "weight", PANGO_WEIGHT_BOLD, "weight-set", TRUE, NULL);
          g_object_set(tmpdat.renderer, "style", PANGO_STYLE_ITALIC, NULL);
		} else {
	      Error("parameter perintah jenishuruf_sel salah");
		}
	} else {
	  Error("bentuk perintah jenishuruf_sel salah");
	}

	ungetlex();
}
