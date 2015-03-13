// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// Set jenis huruf to perangkat GUI

void keySetJenisHuruf ()
{

  char tmpMsg[MAX_STRING_LEN];

  int  n=0, i=0, j=0;

  VAL_LABEL valdat, tmpdat, tmpdat2;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  // printf("set_jenishuruf\n");

  n = 0;

	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 1) {
                strcpy(tmpMsg, lex.detail.string );

				tmpdat2.font_desc = pango_font_description_from_string(tmpMsg);
				tmpdat2.isGUI    = 1;
                tmpdat2.GUItype  = 15;   // font
				tmpdat2.datatype = 42;
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
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 3) {
                if(n == 1) {
                  sprintf(tmpMsg, "%s" , valdat.str );

				  tmpdat2.font_desc = pango_font_description_from_string(tmpMsg);
				  tmpdat2.isGUI    = 1;
                  tmpdat2.GUItype  = 15;   // font
				  tmpdat2.datatype = 42;
                } 
			  } else if(valdat.datatype == 40) {  // widget
                if(n == 0) {
				  tmpdat = valdat;
                  tmpdat.datatype = 40;
                } 
			  } else if(valdat.datatype == 42) {  // font dialog
                if(n == 1) {
				  tmpdat2 = valdat;
                  tmpdat2.datatype = 42;
                }
			  } else {
                Error("bentuk perintah Set_JenisHuruf salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah Titel_Layar salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 2) {
      Error("parameter Titel_Layar tidak lengkap");
    } else {
      if(tmpdat.isGUI == 1) {
        gtk_widget_modify_font(tmpdat.widget, tmpdat2.font_desc);
	  }
    }

	ungetlex();

}


