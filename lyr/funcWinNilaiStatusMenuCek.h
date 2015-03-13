// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// ambil teks dari label

VAL_LABEL funcWinNilaiStatusMenuCek ()
{

  int  n=0;

  VAL_LABEL datx,valdat,tmpdat;
 
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
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
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
				  tmpdat  = valdat;
                  tmpdat.datatype = 40;
                } 
			  } else {
                Error("bentuk perintah status_menu_cek salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah status_menu_cek salah");
	    }

    
	  if(tmpdat.GUItype == 18) {  // Isi Menu Cek
	    datx.val = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(tmpdat.widget));
	  } else {
        Error("Salah parameter untuk status_menu_cek");
	  }

	 datx.datatype = 0;   // int
	 return datx;


}


