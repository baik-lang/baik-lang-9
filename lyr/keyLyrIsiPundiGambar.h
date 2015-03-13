// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2012
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyIsiPundiGambar ()
{

  GdkPixbuf *tmpPix=NULL;

  int  n=0, i=0, j=0;
  long idx=0;                           // array index

  GtkTreeIter iter;

  VAL_LABEL valdat,valdat2,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  n = 0;

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
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 0) {
                if(n == 46) {  // A single pixbuf data - see defValLabel
                  tmpPix = valdat.pixbuf[0];
                } 
			  } else if(valdat.datatype == 47) { // list_store STRING
                if(n == 0) {
				  tmpdat  = valdat;
                  tmpdat.datatype = 47;
                } 
			  } else {
                Error("bentuk perintah Isi_Pundi_Gambar salah");
			  }

	      break;


	    default:
	      Error("bentuk perintah Isi_Pundi_Gambar salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 2) {
      Error("parameter Isi_Pundi_Gambar tidak lengkap");
    } else {
      if(tmpdat.datatype == 47) {
        gtk_list_store_append (tmpdat.liststore, &iter);
        gtk_list_store_set (tmpdat.liststore, &iter, 0, tmpPix, -1);
	  }
    }

	ungetlex();

}
