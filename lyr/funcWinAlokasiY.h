// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// ambil pos y dari widget

VAL_LABEL funcWinAlokasiY ()
{

  int  n=0;
  VAL_LABEL datx,valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  // printf("enter Alokasi_Y\n");

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
				tmpdat.datatype = 40;
				valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              if(valdat.datatype == 40) {                       // Widget
                if(n == 0) {
                  datx.val = valdat.widget->allocation.y;       // alloc y
	              datx.datatype = 0;   // int
                } 
			  } else {
                Error("bentuk perintah Alokasi_Y salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah Alokasi_Y salah");
	    }

	 datx.datatype = 0;   // int
	 return datx;

}

