// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// UTF-8

void keyWinSetKertas ()
{

  char *txtMsg = NULL;
  char tmpMsg[MAX_STRING_LEN];

  int  n=0, i=0, j=0;

  VAL_LABEL valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  n = 0;

  // printf("setKertas ...\n");

	do{

      getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 1) {
			    strcpy(tmpMsg, lex.detail.string);
			    txtMsg = (char *)malloc(sizeof(tmpMsg) + 2);
                txtMsg = g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL);
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

              if(valdat.datatype == 3) {        // Get From String
                if(n == 1) {
				  //printf ("get from String : %s\n", valdat.str);
				  strcpy(tmpMsg, valdat.str);
				  txtMsg = (char *)malloc(sizeof(tmpMsg) + 2);
				  txtMsg = tmpMsg;
                } 
			  } else if(valdat.datatype == 41) { // Get From Teks
                if(n == 1) {
				  txtMsg = (char *)malloc(sizeof(valdat.str2) + 2);
				  txtMsg = valdat.str2;
				  //printf ("get from teks : %s\n", valdat.str2);
                }
			  } else if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat = valdat;
				  tmpdat.datatype = 40;
                } 
			  } else {
                Error("bentuk perintah SET_KERTAS salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah SET_KERTAS salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    // printf("do setKertas ...\n");

    if(n != 2) {
      Error("parameter SET_KERTAS tidak lengkap");
    } else {
	  // printf("teks : %s\n", txtMsg);

	  if(tmpdat.GUItype == 12) { // Kertas - textarea
		 gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(tmpdat.widget)), txtMsg, -1);
	  } else {
	     Error("parameter SET_KERTAS harus KERTAS");
	  }
    }

	ungetlex();

}


