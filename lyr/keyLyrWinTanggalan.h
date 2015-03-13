// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyWinTanggalan ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0, i=0, j=0;

  VAL_LABEL valdat,tmpdat, tmpdat2;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

  // printf("keyTambahMenu\n");
	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
			if(n == 1) {
			  strcpy(tmpMsg, lex.detail.string);
			}
	      break;   

	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

			  if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 40 || valdat.datatype == 3) {
                if(n == 0) {
				  tmpdat = valdat;
				}
			  } else if(valdat.datatype == 3) {
				if(n == 1) {
				  strcpy(tmpMsg, valdat.str);
				}
			  } else {
                Error("bentuk perintah Tanggalan salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah Tanggalan salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(tmpdat.datatype == 40 || tmpdat.datatype == 3) {
	  if(n == 1) {
	    // no pic file
        create_tanggalan_baik(tmpdat, "");
	  } else if(n == 2) {
	    // with target and pic file
        create_tanggalan_baik(tmpdat, tmpMsg);
      } else {
        Error("parameter Tanggalan tidak lengkap");
      }
	}

	ungetlex();

}


