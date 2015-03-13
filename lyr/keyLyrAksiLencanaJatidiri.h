// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// UTF-8

void keyAksi_Lencana_Jatidiri ()
{
  int  n=0, i=0, j=0;

  char name[128],
	   ver[128],
       logo[128],
	   author[128],
	   comment[128],
       www[128];

  char tmpMsg[128];

  VAL_LABEL valdat, tmpdat;

  AboutData *dat;

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&name, '\0', sizeof(name));
  memset(&ver, '\0', sizeof(ver));
  memset(&logo, '\0', sizeof(logo));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));


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
                strcpy(name, g_locale_to_utf8(lex.detail.string, -1,NULL,NULL,NULL));
              } else if(n == 2) {
                strcpy(ver, g_locale_to_utf8(lex.detail.string, -1,NULL,NULL,NULL) );
              } else if(n == 3) {
                strcpy(author, g_locale_to_utf8(lex.detail.string, -1,NULL,NULL,NULL) );
              } else if(n == 4) {
                strcpy(comment, g_locale_to_utf8(lex.detail.string, -1,NULL,NULL,NULL) );
              } else if(n == 5) {
                strcpy(www, g_locale_to_utf8(lex.detail.string, -1,NULL,NULL,NULL) );
              } else if(n == 6) {
                strcpy(logo, g_locale_to_utf8(lex.detail.string, -1,NULL,NULL,NULL) );
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
                strcpy(name, g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL) );
              } else if(n == 2) {
                strcpy(ver, g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL) );
              } else if(n == 3) {
                strcpy(author, g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL));
              } else if(n == 4) {
                strcpy(comment, g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL) );
              } else if(n == 5) {
                strcpy(www, g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL) );
              } else if(n == 6) {
                strcpy(logo, g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL) );
              } 

	      break;

	    default:
	      Error("bentuk perintah Aksi_Jatidiri salah");
	    }

          n++;

	  getlex();


	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

    // printf("name=%s \n", name);
    // printf("msg=%s \n", ver);
    // printf("logo=%s \n", logo);
    // printf("n=%d --------- \n", n);

	memset(&aboutDat, '\0', sizeof(aboutDat));
	// passing string into global popup-data with new memory allocation
	aboutDat.name  = g_strdup(name);
	aboutDat.ver   = g_strdup(ver);

	dat = (AboutData *)malloc(sizeof(AboutData));

	dat->name    = NULL;
	dat->ver     = NULL;
	dat->author  = NULL;
	dat->comment = NULL;
	dat->www     = NULL;

	dat->name    = g_strdup(name);
	dat->ver     = g_strdup(ver);
	dat->author  = g_strdup(author);
	dat->comment = g_strdup(comment);
	dat->www     = g_strdup(www);

    if(n == 6) {
	  dat->logo   = " "; // must be initialize
	  
	  if(tmpdat.GUItype == 3) { // Button, NOT window widget
          g_signal_connect(G_OBJECT(tmpdat.widget), "clicked",
				  GTK_SIGNAL_FUNC(win_lencana_jatidiri), dat);

	  } else if(tmpdat.GUItype == 10) { // MenuItem, NOT window widget
          g_signal_connect(G_OBJECT(tmpdat.widget), "activate",
				  GTK_SIGNAL_FUNC(win_lencana_jatidiri), dat);
	  }

    } else if(n==7) {
	  dat->logo   = g_strdup(logo);

	  if(tmpdat.GUItype == 3) { // Button, NOT window widget
          g_signal_connect(G_OBJECT(tmpdat.widget), "clicked",
				  GTK_SIGNAL_FUNC(win_lencana_jatidiri), dat);

	  } else if(tmpdat.GUItype == 10) { // MenuItem, NOT window widget
          g_signal_connect(G_OBJECT(tmpdat.widget), "activate",
				  GTK_SIGNAL_FUNC(win_lencana_jatidiri), dat);
	  }

	} else {
      Error("Aksi_Lencana_Jatidiri tidak lengkap");
	}

	ungetlex();


}


