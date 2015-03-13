// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// lukis_lingkaran

void keyCairoLingkaran ()
{

  int  n=0, mysize=0;

  cairo_t *cr=NULL;
  double x=0.0;
  double y=0.0;
  double r=0.0;
  double theta1=0.0;
  double theta2=0.0;

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

  n = 0;

  // printf("keyCairoLingkaran\n");
	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_DBL:
			if(n == 1) {
			  x =  lex.detail.dblnum;
			} else
			if(n == 2) {
			  y =  lex.detail.dblnum;
			} else
			if(n == 3) {
			  r =  lex.detail.dblnum;
			} else
			if(n == 4) {
			  theta1 =  lex.detail.dblnum;
			} else
			if(n == 5) {
			  theta2 =  lex.detail.dblnum;
			}
	      break;   

	    case TYPE_NUM:
			if(n == 1) {
			  x =  (double)lex.detail.num;
			} else
			if(n == 2) {
			  y =  (double)lex.detail.num;
			} else
			if(n == 3) {
			  r =  (double)lex.detail.num;
			} else
			if(n == 4) {
			  theta1 =  (double)lex.detail.num;
			} else
			if(n == 5) {
			  theta2 =  (double)lex.detail.num;
			}
	      break; 

		case TYPE_SYM:
		   if(lex.type == TYPE_SYM && lex.detail.symbol == '-') {
             mindat = get_Minus_Val();        // consider minus param
			 if(mindat.datatype == 0) {
				if(n == 1) {
					x = (double)mindat.val;
				} else
				if(n == 2) {
					y = (double)mindat.val;
				} else
				if(n == 3) {
					r = (double)mindat.val;
				} else
				if(n == 4) {
					theta1 = (double)mindat.val;
				} else
				if(n == 5) {
					theta2 = (double)mindat.val;
				}
			 } else
			 if(mindat.datatype == 1) {
				if(n == 1) {
					x = mindat.floatdata;
				} else
				if(n == 2) {
					y = mindat.floatdata;
				} else
				if(n == 3) {
					r = mindat.floatdata;
				} else
				if(n == 4) {
					theta1 = mindat.floatdata;
				} else
				if(n == 5) {
					theta2 = mindat.floatdata;
				}
			 } 
		   }
		  break;

	    case TYPE_STR:
             Error("lukis_lingkaran: masukan data salah");
	      break;   

	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

             if(currentClass != NULL && strlen(currentClass) > 0) {
               #ifdef WIN32
                #ifndef S_SPLINT_S
                sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #endif
               #else
               snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
               #endif

                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
              } else {
                valdat = ValLabel( lex.detail.string, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }

              if(valdat.datatype == 80) { // cairo img
                if(n == 0) {
				  cr = valdat.cr_img;
				}
			  } else if(valdat.datatype == 3) {
                Error("lukis_lingkaran: masukan data salah");
			  } else if(valdat.datatype == 1) {
				if(n == 1) {
					x = valdat.floatdata;
				} else
				if(n == 2) {
					y = valdat.floatdata;
				} else
				if(n == 3) {
					r = valdat.floatdata;
				} else
				if(n == 4) {
					theta1 = valdat.floatdata;
				} else
				if(n == 5) {
					theta2 = valdat.floatdata;
				}
			  } else if(valdat.datatype == 0) {
				if(n == 1) {
					x = (double)valdat.val;
				} else
				if(n == 2) {
					y = (double)valdat.val;
				} else
				if(n == 3) {
					r = (double)valdat.val;
				} else
				if(n == 4) {
					theta1 = (double)valdat.val;
				} else
				if(n == 4) {
					theta2 = (double)valdat.val;
				}
			  } else {
                Error("bentuk perintah lukis_lingkaran salah");
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

                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(valdat2.array_idx, sizeof(valdat2.array_idx),"%d", idx);
                 #else
                 snprintf(valdat2.array_idx, sizeof(valdat2.array_idx),"%d", idx);
                 #endif
                #else
                snprintf(valdat2.array_idx, sizeof(valdat2.array_idx),"%d", idx);
                #endif

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  if(n == 1)                           /* x */
                    x = (double) get_int_array(valdat2, idx);
                  if(n == 2)                           /* y */
                    y = (double) get_int_array(valdat2, idx);
                  if(n == 3)                           /* r */
                    r = (double) get_int_array(valdat2, idx);
                  if(n == 4)                           /* theta1 */
                    theta1 = (double) get_int_array(valdat2, idx);
                  if(n == 5)                           /* theta2 */
                    theta2 = (double) get_int_array(valdat2, idx);
                } 

                if(valdat2.datatype == 7) {
                  if(valdat2.array_d == '\0')
                    Error("ukuran Untaian belum terdefinisi: pecahan");

                  if(n == 1)                           /* x */
                    x = get_dbl_array(valdat2, idx);
                  if(n == 2)                           /* y */
                    y = get_dbl_array(valdat2, idx);
                  if(n == 3)                           /* r */
                    r = get_dbl_array(valdat2, idx);
                  if(n == 4)                           /* theta1 */
                    theta1 = get_dbl_array(valdat2, idx);
                  if(n == 5)                           /* theta2 */
                    theta2 = get_dbl_array(valdat2, idx);
                } 

              }

           break;

	    default:
	      Error("bentuk perintah lukis_lingkaran salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	ungetlex();

	if(n!=6) {
      Error("bentuk perintah lukis_lingkaran salah");
	} else {

	  cairo_arc(cr, x, y, r, theta1, theta2);
	  cairo_stroke (cr);

	}

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

}



