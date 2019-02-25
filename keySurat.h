// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// 2015/8/13 For WebMail : AUTH PLAIN

void keySurat ()
{

  char ident[MAX_IDENT_LEN];

  char logMsg[MAX_STRING_LEN * 2],
       tmpMsg[MAX_STRING_LEN * 2];

  int  n=0;

  char mailfrom[128],
        mailto[1024],
        subject[256],
		password[1024],
        body[4096],
        mailServer[1024], mailPort[8];

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat,tmpdat;
  
  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&mailfrom, '\0', sizeof(mailfrom));
  memset(&mailto, '\0', sizeof(mailto));
  memset(&subject, '\0', sizeof(subject));
  memset(&password, '\0', sizeof(password));
  memset(&body, '\0', sizeof(body));
  memset(&mailServer, '\0', sizeof(mailServer));
  memset(&mailPort, '\0', sizeof(mailPort));

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&tmp_str, '\0', sizeof(tmp_str));
  
  memset(&ident, '\0', sizeof(ident));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));
  memset(&logMsg, '\0', sizeof(logMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


    n = 0;

	do{
      memset(tmpMsg, '\0', sizeof(tmpMsg));
	  getlex();
	  switch( lex.type )
	    {
	    case TYPE_STR:

              if(n == 0) {
                strcpy(mailfrom, lex.detail.string );
              } else if(n == 1) {
                strcpy(mailto, lex.detail.string );
              } else if(n == 2) {
                strcpy(subject, lex.detail.string );
              } else if(n == 3) {
                strcpy(body, lex.detail.string );
              } else if(n == 4) {
                strcpy(mailServer, lex.detail.string );
			  } else if (n == 5) {
				strcpy(password, lex.detail.string);
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

              if(n == 0) {
                strcpy(mailfrom, tmpMsg );
              } else if(n == 1) {
                strcpy(mailto, tmpMsg );
              } else if(n == 2) {
                strcpy(subject, tmpMsg );
              } else if(n == 3) {
                strcpy(body, tmpMsg );
              } else if(n == 4) {
                strcpy(mailServer, tmpMsg );
              } else if(n == 5) {
                strcpy(password, tmpMsg );
              } 

	      break;

	    default:
	      Error("bentuk perintah SURAT salah");
	    }

          n++;
	      getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    //printf("n=%d \n", n);

    if(n == 5) {
          /*
          printf("from %s \n", mailfrom);
          printf("to %s \n", mailto);
          printf("subj %s \n", subject);
          printf("body %s \n", body);
          printf("server %s \n", mailServer);
          */

         #ifdef WINDOWS
         if (win_sendMail(mailServer, "25", mailfrom, mailto, subject, body) == 0) {
           printf("Kirim mail OK\n");
         } else {
           printf("Gagal kirim mail\n");
         }
         #else
         if (ux_sendMail(mailServer, "25", mailfrom, mailto, subject, body) == 0) {
           printf("Kirim mail OK\n");
         } else {
           printf("Gagal kirim mail\n");
         }
         #endif
	}
	else if (n == 6) {
        #ifdef WINDOWS
		if (win_sendMail2(mailServer, "587", password, mailfrom, mailto, subject, body) == 0) {
			//printf("send mail.\n");
		}
		else {
			printf("Gagal kirim mail\n");
		}
        #else
		if (ux_sendMail2(mailServer, "587", password, mailfrom, mailto, subject, body) == 0) {
			//printf("send mail.\n");
		}
		else {
			printf("Gagal kirim mail\n");
		}
        #endif
	}
	else {
		Error("SURAT tidak lengkap");
	}

	ungetlex();


  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);


  if(valdat.filename != NULL)
    free(valdat.filename);
  if(valdat.folder != NULL)
    free(valdat.folder);
  if(valdat.filedata != NULL)
    free(valdat.filedata);
  if(valdat.long_str != NULL)
    free(valdat.long_str);

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  if(tmpdat.filename != NULL)
    free(tmpdat.filename);
  if(tmpdat.folder != NULL)
    free(tmpdat.folder);
  if(tmpdat.filedata != NULL)
    free(tmpdat.filedata);
  if(tmpdat.long_str != NULL)
    free(tmpdat.long_str);

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);


}

