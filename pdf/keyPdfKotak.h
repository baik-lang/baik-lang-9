// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyPdfKotak ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0, mysize=0;

  double x1=0.0, y1=0.0;
  double x2=0.0, y2=0.0;

  HPDF_Doc  pdf=NULL;
  HPDF_Page ppage=NULL;

  VAL_LABEL valdat, valdat2, tmpdat;
  VAL_LABEL mindat;  
  int idx=0;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&mindat, '\0', sizeof(mindat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

    //printf("keyPdfKotak\n");
	do{

	  getlex();

	  switch( lex.type )
	    {

	    case TYPE_NUM:
			if(n == 1)
			  x1 = (double) lex.detail.num;
			if(n == 2)
			  y1 = (double) lex.detail.num;
			if(n == 3)
			  x2 = (double) lex.detail.num;
			if(n == 4)
			  y2 = (double) lex.detail.num;
	      break;  

	    case TYPE_DBL:
			if(n == 1)
			  x1 = (double) lex.detail.dblnum;
			if(n == 2)
			  y1 = (double) lex.detail.dblnum;
			if(n == 3)
			  x2 = (double) lex.detail.dblnum;
			if(n == 4)
			  y2 = (double) lex.detail.dblnum;
	      break;   

		case TYPE_SYM:
		   if(lex.type == TYPE_SYM && lex.detail.symbol == '-') {
             mindat = get_Minus_Val();        // consider minus param
			 if(mindat.datatype == 0) {
				if(n == 1) {
					x1 = (double)mindat.val;
				} else
				if(n == 2) {
					y1 = (double)mindat.val;
				} else
				if(n == 3) {
					x2 = (double)mindat.val;
				} else
				if(n == 4) {
					y2 = (double)mindat.val;
				}
			 } else
			 if(mindat.datatype == 1) {
				if(n == 1) {
					x1 = mindat.floatdata;
				} else
				if(n == 2) {
					y1 = mindat.floatdata;
				} else
				if(n == 3) {
					x2 = mindat.floatdata;
				} else
				if(n == 4) {
					y2 = mindat.floatdata;
				}
			 } 
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

			  } else if(valdat.datatype == 0) {
				if(n == 1)
				  x1 = (double) valdat.val;
				if(n == 2)
				  y1 = (double) valdat.val;
				if(n == 3)
				  x2 = (double) valdat.val;
				if(n == 4)
				  y2 = (double) valdat.val;

			  } else if(valdat.datatype == 1) {
				if(n == 1)
				  x1 = valdat.floatdata;
				if(n == 2)
				  y1 = valdat.floatdata;
				if(n == 3)
				  x2 = valdat.floatdata;
				if(n == 4)
				  y2 = valdat.floatdata;

			  } else {
                Error("bentuk perintah pdf_kotak salah");
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

                  if(n == 1)                           /* ord x start */
                    x1 = (double) get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord y start */
                    y1 = (double) get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord x end   */
                    x2 = (double) get_int_array(valdat2, idx);
                  if(n == 4)                           /* ord y end   */
                    y2 = (double) get_int_array(valdat2, idx);
                } 

                if(valdat2.datatype == 7) {
                  if(valdat2.array_d == '\0')
                    Error("ukuran Untaian belum terdefinisi: pecahan");

                  if(n == 1)                           /* ord x start */
                    x1 = get_dbl_array(valdat2, idx);
                  if(n == 2)                           /* ord y start */
                    y1 = get_dbl_array(valdat2, idx);
                  if(n == 3)                           /* ord x end   */
                    x2 = get_dbl_array(valdat2, idx);
                  if(n == 4)                           /* ord y end   */
                    y2 = get_dbl_array(valdat2, idx);
                } 

              }

           break;

	    default:
	      Error("bentuk perintah pdf_kotak salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(n!=5) {
      Error("bentuk perintah pdf_kotak salah");
	} else {
      HPDF_Page_Rectangle (ppage, x1, y1, x2, y2);
      HPDF_Page_Stroke (ppage);
	  //printf("draw rect ok\n");
	}

	ungetlex();

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

}
