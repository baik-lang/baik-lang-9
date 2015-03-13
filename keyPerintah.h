// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

//2010/12/13

void keyPerintah ()
{

  char ident[MAX_IDENT_LEN];

  VAL_LABEL valdat;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&ident, '\0', sizeof(ident));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


	  getlex();
     // printf(" DEBUG: PERINTAH lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    case TYPE_STR:
	      system( lex.detail.string );
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:
	    case TYPE_NUM:

              //printf("curr class : %s\n", currentClass);
              //printf("datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                #ifdef WINDOWS
				  WinExec((const char*)valdat.str,SW_HIDE);
                #else
                  system( valdat.str );
                #endif
              }

              break;

	    default:
	      Error("kode perintah PERINTAH salah");
	    }
	  getlex();

	fflush( stdout );

	ungetlex();
}

