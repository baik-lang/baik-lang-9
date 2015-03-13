// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyAksi_Tutup_Layar ()
{
  int  n=0, i=0, j=0;

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat, tmpdat2;
  
  int    idx=0, idx2=0;                           // array index

  int    isArrDummy=0;

  int    size = 0;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];


  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

	do{

	  getlex();

	  switch( lex.type )
	    {
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              //printf("curr class : %s\n", currentClass);
              //printf("datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

			  if(valdat.datatype == 40) {
				  if(n == 0) {
				    tmpdat = valdat;     // Action Widget : button dll
				  } else if(n == 1) { 
				    tmpdat2 = valdat;    // Target to close : windows
				  }

			  } else {
                Error("parameter pada kode perintah Aksi_Tutup_Layar salah");
			  }

              break;

	    default:
	      Error("kode perintah Aksi_Tutup_Layar salah");
	    }

	  n++;
	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(n == 2) {
	  printf ("action type %d\n", tmpdat.GUItype);
      if(tmpdat.datatype == 40 && tmpdat2.GUItype == 0) {
				  if(tmpdat.GUItype == 0) {        // window widget
				    g_signal_connect(G_OBJECT(tmpdat.widget), "destroy",
                      G_CALLBACK (gtk_widget_destroyed),
					  &tmpdat2.widget);
				  } else if(tmpdat.GUItype == 10){ // Menu Item
					// printf("menu tutup layar...\n");
				    g_signal_connect_swapped(G_OBJECT(tmpdat.widget), "activate",
                      G_CALLBACK (gtk_widget_destroy),
				      GTK_WINDOW(tmpdat2.widget));
				  } else if(tmpdat.GUItype == 3){ // Tombol
					g_signal_connect_swapped (G_OBJECT(tmpdat.widget), "clicked", 
                      G_CALLBACK (gtk_widget_destroy),
				      GTK_WINDOW(tmpdat2.widget));
				  }
	  }
	} else {
	  Error("kode perintah Aksi_Tutup_Layar salah");
	}

	ungetlex();

}
