// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyPdfSetHuruf()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0, mysize=0;

  HPDF_Doc  pdf=NULL;
  HPDF_Page ppage=NULL;
  HPDF_Font pfont=NULL;
  char name[MAX_STRING_LEN];

  VAL_LABEL valdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

    //printf("keyPdfSetHuruf\n");
	do{

	  getlex();

	  switch( lex.type )
	    {

	    case TYPE_STR:
			if(n == 1) {
			  strcpy(name, lex.detail.string);
			}
	      break; 

	    case TYPE_NUM:
			if(n == 2) {
			  mysize =  lex.detail.num;
			}
	      break;   

	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

			  if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
              } else {
                valdat = ValLabel( lex.detail.string, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }


              if(valdat.datatype == 71) {
                if(n == 0) {
				  pdf = valdat.pdf;
				  ppage = valdat.pdf_page;
				  if(ppage == NULL) {
				    printf("ppage NULL !\n");
				  }
				}

		      } else if(valdat.datatype == 3) {
			    if(n == 1) {
                  strcpy(name, valdat.str);
			    }

			  } else if(valdat.datatype == 0) {
				if(n == 2) {
				  mysize = valdat.val;
				}
			  } else {
                Error("bentuk perintah pdf_sethuruf salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah pdf_sethuruf salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(n!=3) {
      Error("bentuk perintah pdf_sethuruf salah");
	} else {
	  //printf("set font %s size %d\n", name , mysize);
	  pfont = HPDF_GetFont (pdf, name, NULL);
	  HPDF_Page_SetFontAndSize (ppage, pfont, mysize);
	  //printf("set font size ok\n");
	}

	ungetlex();

}
