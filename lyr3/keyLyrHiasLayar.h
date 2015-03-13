// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyHiasLayar ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0;

  VAL_LABEL valdat,tmpdat, tmpdat2;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

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

              if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat.widget   = valdat.widget;
                  tmpdat.datatype = 40;
				  tmpdat.GUItype  = valdat.GUItype;
				} else if(n == 1) {
				  tmpdat2.widget   = valdat.widget;
                  tmpdat2.datatype = 40;
				  tmpdat2.GUItype  = valdat.GUItype;
				}
			  } else {
                Error("bentuk perintah Hias_Layar salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah Hias_Layar salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 2) {
      Error("parameter Hias_Layar tidak lengkap");
    } else {
	  if(tmpdat.GUItype == 21) {
        gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)tmpdat.widget, tmpdat2.widget);
	  } else {
        gtk_container_add(GTK_CONTAINER(tmpdat.widget), tmpdat2.widget);
	  }
    }

	ungetlex();

}


void keyHiasLayarGulung ()
{
   keyHiasLayar ();
}

