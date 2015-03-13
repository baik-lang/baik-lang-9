// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyAksi_Rambu_Salah ()
{
  int  n=0, i=0, j=0;

  char title[128], logo[128],
       msg[MAX_STRING_LEN],
	   tmpMsg[MAX_STRING_LEN];

  VAL_LABEL valdat, tmpdat;

  PopupData *dat;

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&title, '\0', sizeof(title));
  memset(&msg, '\0', sizeof(msg));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));
  memset(&logo, '\0', sizeof(logo));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  
  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


    n = 0;

	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:

              if(n == 1) {
                strcpy(title, lex.detail.string );
              } else if(n == 2) {
                strcpy(msg, lex.detail.string );
              } else if(n == 3) {
                strcpy(logo, lex.detail.string );
              } 

	      break;
	    
	    case TYPE_IDENT:
	    case TYPE_NUM:

			  ungetlex();
              valdat = expression();

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                sprintf(tmpMsg, "%s" , valdat.str );
              } else {
                sprintf(tmpMsg, "%li" , valdat.val );
              }

              if(valdat.datatype == 40) {
			    if(n == 0) {
				  tmpdat.widget   = valdat.widget;
                  tmpdat.datatype = 40;
				  tmpdat.GUItype  = valdat.GUItype;
			    }
			  }

              if(n == 1) {
                strcpy(title, tmpMsg );
              } else if(n == 2) {
                strcpy(msg, tmpMsg );
              } else if(n == 3) {
                strcpy(logo, tmpMsg );
              } 

	      break;

	    default:
	      Error("bentuk perintah AksiRambuSalah salah");
	    }

          n++;

	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

    //printf("title=%s \n", title);
    //printf("msg=%s \n", msg);
    //printf("logo=%s \n", logo);
    //printf("n=%d --------- \n", n);

	memset(&popupDat, '\0', sizeof(popupDat));
	// passing string into global popup-data with new memory allocation
	popupDat.title  = g_strdup(title);
	popupDat.msg    = g_strdup(msg);

	dat = (PopupData *)malloc(sizeof(PopupData));
	dat->title = g_strdup(title);
	dat->msg   = g_strdup(msg);

    if(n == 3) {
	  dat->logo   = " "; // must be initialize
	  
      gtk_object_set_data(GTK_OBJECT(tmpdat.widget), "lbl_aksi_error", dat); 
	  
	  if(tmpdat.GUItype == 3) { // Button, NOT window widget
          g_signal_connect_swapped(G_OBJECT(tmpdat.widget), "clicked",
				  G_CALLBACK(win_rambu_error), tmpdat.widget);
	  } else if(tmpdat.GUItype == 10) { // MenuItem, NOT window widget
          g_signal_connect_swapped(G_OBJECT(tmpdat.widget), "activate",
				  G_CALLBACK(win_rambu_error), tmpdat.widget);
	  }

    } else if(n==4) {
	  dat->logo   = g_strdup(logo);

	  gtk_object_set_data(GTK_OBJECT(tmpdat.widget), "lbl_aksi_error", dat); 


	  if(tmpdat.GUItype == 3) { // Button, NOT window widget
         g_signal_connect_swapped(G_OBJECT(tmpdat.widget), "clicked",
				  G_CALLBACK(win_rambu_error), tmpdat.widget);

	  } else if(tmpdat.GUItype == 10) { // MenuItem, NOT window widget
          g_signal_connect_swapped(G_OBJECT(tmpdat.widget), "activate",
				  G_CALLBACK(win_rambu_error), tmpdat.widget);
	  }

	} else {
      Error("Aksi_Rambu_Salah tidak lengkap");
	}

	ungetlex();


}

