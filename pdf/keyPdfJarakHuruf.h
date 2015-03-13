// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyPdfJarakHuruf ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0;
  double mysize=0.0;

  HPDF_Doc  pdf=NULL;
  HPDF_Page ppage=NULL;

  VAL_LABEL valdat, valdat2, tmpdat;
  int idx=0;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

    //printf("keyPdfJarakHuruf\n");
	do{

	  getlex();

	  switch( lex.type )
	    {

	    case TYPE_DBL:
			if(n == 1)
			  mysize = lex.detail.dblnum;
	      break;  

	    case TYPE_NUM:
			if(n == 1)
			  mysize = (double)lex.detail.num;
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

			  } else if(valdat.datatype == 0) {
				if(n == 1)
				  mysize = (double) valdat.val;
			  } else if(valdat.datatype == 1) {
				if(n == 1)
				  mysize =  valdat.floatdata;
			  } else {
                Error("bentuk perintah pdf_jarakhuruf salah");
			  }

	      break;

        case TYPE_ARRAY:
              /* printf("write array\n"); */

              if(strlen(lex.detail.array_str) > 0) {
                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atol (valdat.array_idx);
                } else {
                   /* printf("show NOT digit\n"); */
                   /* Read index param */
                   tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

	            valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                sprintf(valdat2.array_idx, "%d", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  if(n == 1)  
                    mysize = (double) get_int_array(valdat2, idx);
                } 

                if(valdat2.datatype == 7) {
                  if(valdat2.array_d == '\0')
                    Error("ukuran Untaian belum terdefinisi: pecahan");

                  if(n == 1)  
                    mysize = get_dbl_array(valdat2, idx);
                } 

              }

          break;

	    default:
	      Error("bentuk perintah pdf_jarakhuruf salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(n!=2) {
      Error("bentuk perintah pdf_jarakhuruf salah");
	} else {
      /* char-spacing */
	  HPDF_Page_SetCharSpace (ppage, mysize);
	}

	ungetlex();


  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

}

