// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keySimpanTeks ()
{

  int  n=0, i=0, j=0;

  char logMsg[MAX_STRING_LEN * 2],
       tmpMsg[MAX_STRING_LEN * 2];

  VAL_LABEL valdat, valdat2, tmpdat, valdat0;
  
  int    idx=0, idx2=0;                           // array index

  int    isArrDummy=0;

  FILE   *tmpfile =NULL;
  char   *mystr   =NULL;
 
  int    isFileOpen;

  int    size = 0;
  char   get_name[MAX_STRING_LEN];


  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("simpan teks...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&valdat0, '\0', sizeof(valdat0));

  memset(&get_name, '\0', sizeof(get_name));
  
  memset(&tmpMsg, '\0', sizeof(tmpMsg));
  memset(&logMsg, '\0', sizeof(logMsg));;

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  memset(tmpMsg, '\0', sizeof(tmpMsg));
  memset(logMsg, '\0', sizeof(logMsg));

  strcpy(logMsg, "");

  n = 0;

	do{

          memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {

	    
	    case TYPE_IDENT:
              ungetlex();
              valdat = expression();

              if(valdat.datatype == 41) { // get tex
               if(n == 1) {
				 // printf("get teks ...\n");
				 mystr = valdat.str2;     // dont use strcpy
				 // printf("get teks OK\n");
               }
              } else
              if(valdat.datatype == 2) { // get File
               if(n == 0) {
				 // printf("get file ...\n");
                 tmpfile    = valdat.filedata;
                 isFileOpen = valdat.isFileOpen;
		         // printf("get file OK\n");
               }
              } 

	        break;


	    default:
	      Error("bentuk perintah SIMPAN_TEKS salah");
	    }

          n++;

	  getlex();


	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(n != 2) {
      Error("bentuk perintah SIMPAN_TEKS salah");
	} else {
        if(isFileOpen == 1) {
          fprintf(tmpfile, "%s", mystr);
          fflush( tmpfile );
        }
	}

	ungetlex();


}

