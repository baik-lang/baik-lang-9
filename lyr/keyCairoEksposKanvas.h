// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyEksposKanvas ()
{

  int  n=0;

  VAL_LABEL valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

	  getlex(); n++;

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

              if(valdat.datatype == 40) {  // canvas
			    tmpdat          = valdat;
                tmpdat.datatype = 40;
			  } else {
                Error("bentuk perintah Ekspos_Kanvas salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah Ekspos_Kanvas salah");
	    }



    if(n != 1) {
      Error("parameter Ekspos_Kanvas tidak lengkap");
    } else {
      // gtk_widget_draw(tmpdat.widget, NULL);
	  // gtk_widget_queue_draw(tmpdat.widget);
    }

}

