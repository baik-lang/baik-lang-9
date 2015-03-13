// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

VAL_LABEL funcWinModelRanting ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0;

  VAL_LABEL valdat,valdat2,tmpdat,tmpdat2;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

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

              if(valdat.datatype == 56) { // TreeStore
                if(n == 0) {
				  tmpdat  = valdat;
                  tmpdat.datatype = 56;
                } 
			  } else {
                Error("bentuk perintah Model_Ranting salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah Model_Ranting salah");
	    }


    if(tmpdat.datatype == 56) {
      // printf("Model Ranting ...\n");
	  if(tmpdat.treestore == NULL) {
        printf("Error! TreeStore NULL");
	  }

      tmpdat2.widget   = gtk_tree_view_new_with_model (GTK_TREE_MODEL (tmpdat.treestore));;
	  tmpdat2.datatype = 40; // Gtk Widget
	  tmpdat2.isGUI    = 1;
	  tmpdat2.GUItype  = 24;

	  // clear mem
	  // g_object_unref (G_OBJECT (tmpdat.treestore));
	} else {
      Error("parameter Model_Ranting tidak lengkap");
	}

	return tmpdat2;

}
