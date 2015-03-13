// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyRambuSalah ()
{
  int  n=0;

  char title[128], logo[128],
       msg[MAX_STRING_LEN],
	   tmpMsg[MAX_STRING_LEN];

  VAL_LABEL valdat, tmpdat;

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

              if(n == 0) {
                strcpy(title, lex.detail.string );
              } else if(n == 1) {
                strcpy(msg, lex.detail.string );
              } else if(n == 2) {
                strcpy(logo, lex.detail.string );
              } 

	      break;
	    
	    case TYPE_IDENT:
	    case TYPE_NUM:

              ungetlex();
              valdat = expression();

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                strcpy(tmpMsg, valdat.str );
              } else {
                #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(tmpMsg, sizeof(tmpMsg),"%li", valdat.val );
                   #else
                   snprintf(tmpMsg, sizeof(tmpMsg),"%li", valdat.val );
                   #endif
                #else
                  snprintf(tmpMsg, sizeof(tmpMsg),"%li", valdat.val );
                #endif
              }

              if(n == 0) {
                strcpy(title, tmpMsg );
              } else if(n == 1) {
                strcpy(msg, tmpMsg );
              } else if(n == 2) {
                strcpy(logo, tmpMsg );
              } 

	      break;

	    default:
	      Error("bentuk perintah Rambu_Salah salah");
	    }

          n++;

	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    //printf("n=%d \n", n);

	memset(&popupDat, '\0', sizeof(popupDat));
	// passing string into global popup-data with new memory allocation
	popupDat.title  = g_strdup(title);
	popupDat.msg    = g_strdup(msg);

    if(n == 2) {
	  popupDat.logo   = NULL; // must be initialize

      win_rambu_error(tmpdat.widget, NULL);

    } else if(n==3) {
	  popupDat.logo   = g_strdup(logo);

      win_rambu_error(tmpdat.widget, NULL);
	} else {
      Error("Rambu_Salah tidak lengkap");
	}

	ungetlex();


}

