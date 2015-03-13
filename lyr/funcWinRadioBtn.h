// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// TOMBOL_COBLOS - UTF8

VAL_LABEL funcWinRadioBtn ()
{
  char tmpMsg0[MAX_STRING_LEN];
  char tmpMsg[MAX_STRING_LEN];

  int  n=0;

  VAL_LABEL datx,valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg0, '\0', sizeof(tmpMsg0));
  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:

	          // printf("%s n : %d\n", lex.detail.string, n);
              if(n == 0) {
                strcpy(tmpMsg0, lex.detail.string );
              } else
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

                // ungetlex();
                // valdat = expression("",0);

				tmpdat.datatype = 40;
				valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 3) {
                if(n == 0) {
                  strcpy(tmpMsg0, lex.detail.string );
                } else
                if(n == 1) {
                  sprintf(tmpMsg, "%s" , valdat.str );
                } 
			  } else if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat.widget   = valdat.widget;
				  tmpdat.eventbox = valdat.eventbox;
				  tmpdat.GUItype  = valdat.GUItype;
                  tmpdat.datatype = 40;
                } 
			  } else {
                Error("bentuk perintah TOMBOL_COBLOS salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah TOMBOL_COBLOS salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' && lex.detail.symbol != '\n');

	ungetlex();

    if(n == 1) {
     // set ident
	 strcpy(datx.ident, tmpMsg0);

	 // printf("tmpMsg0 : %s\n", tmpMsg0);

     // make tombol radio

     // printf("no grup\n");
     datx.widget  =  gtk_radio_button_new_with_label(NULL, g_locale_to_utf8(tmpMsg0, -1,NULL,NULL,NULL));

     // make also eventbox for parent/base canvas
     datx.eventbox = gtk_event_box_new();

	 datx.isGUI    = 1;
	 datx.GUItype  = 7;    // Tombol Radio
	 datx.datatype = 40;   // widget

	 return datx;

	} else if(n == 2) {
     // set ident
	 strcpy(datx.ident, tmpMsg);

	 // printf("tmpMsg0 : %s\n", tmpMsg0);

     // make tombol radio
     if(! strcmp(tmpMsg0, "NULL")) {
       // printf("no grup\n");
       datx.widget  =  gtk_radio_button_new_with_label(NULL, g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL));
	 } else {
       // printf("with grup\n");
       datx.widget  =  gtk_radio_button_new_with_label((GSList*)tmpdat.widget, g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL));
	 }

     // make also eventbox for parent/base canvas
     datx.eventbox = gtk_event_box_new();

	 datx.isGUI    = 1;
	 datx.GUItype  = 7;    // Tombol Radio
	 datx.datatype = 40;   // widget

	 return datx;

    } else {
      Error("parameter TOMBOL_COBLOS tidak lengkap");
	  return datx;

	}

}
