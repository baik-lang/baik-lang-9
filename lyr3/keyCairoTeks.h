// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// lukis_teks

void keyCairoTeks ()
{

  int  n=0, mysize=0;

  cairo_t *cr=NULL;
  double w=0.0;
  double h=0.0;
  char   teks[MAX_STRING_LEN];

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
  memset(teks, '\0', sizeof(teks));

  n = 0;

  // printf("keyCairoTeks\n");
	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_DBL:
			if(n == 1) {
			  w =  lex.detail.dblnum;
			}
			if(n == 2) {
			  h =  lex.detail.dblnum;
			}
	      break;   

	    case TYPE_NUM:
			if(n == 1) {
			  w =  (double)lex.detail.num;
			}
			if(n == 2) {
			  h =  (double)lex.detail.num;
			}
	      break; 

		case TYPE_SYM:
		   if(lex.type == TYPE_SYM && lex.detail.symbol == '-') {
             mindat = get_Minus_Val();        // consider minus param
			 if(mindat.datatype == 0) {
				if(n == 1) {
					w = (double)mindat.val;
				} else
				if(n == 2) {
					h = (double)mindat.val;
				} 
			 } else
			 if(mindat.datatype == 1) {
				if(n == 1) {
					w = mindat.floatdata;
				} else
				if(n == 2) {
					h = mindat.floatdata;
				} 
			 } 
		   }
		  break;

	    case TYPE_STR:
			if(n == 3) {
			  strcpy(teks, lex.detail.string);
			}
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
                if(n == 3) {
				  strcpy(teks, valdat.str);
				}
			  } else if(valdat.datatype == 1) {
				if(n == 1) {
					w = valdat.floatdata;
				}
				if(n == 2) {
					h = valdat.floatdata;
				}
			  } else if(valdat.datatype == 0) {
				if(n == 1) {
					w = (double)valdat.val;
				}
				if(n == 2) {
					h = (double)valdat.val;
				}
			  } else {
                Error("bentuk perintah lukis_teks salah");
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

                  if(n == 1)                           /* width */
                    w = (double) get_int_array(valdat2, idx);
                  if(n == 2)                           /* high */
                    h = (double) get_int_array(valdat2, idx);
                } 

                if(valdat2.datatype == 7) {
                  if(valdat2.array_d == '\0')
                    Error("ukuran Untaian belum terdefinisi: pecahan");

                  if(n == 1)                           /* width */
                    w = get_dbl_array(valdat2, idx);
                  if(n == 2)                           /* high */
                    h = get_dbl_array(valdat2, idx);
                } 

                if(valdat2.datatype == 8) {
                  if(valdat2.array_s == '\0')
                    Error("ukuran Untaian belum terdefinisi: teks");

                  if(n == 3)                           /* teks */
                    get_str_array(valdat2, idx, (char *)&teks);
                } 

              }

           break;

	    default:
	      Error("bentuk perintah lukis_teks salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(n!=4) {
      Error("bentuk perintah lukis_teks salah");
	} else {
      cairo_move_to(cr, w, h);
      cairo_show_text(cr, teks);
	}

	ungetlex();

  //memset(&valdat, '\0', sizeof(valdat));
  //memset(&valdat2, '\0', sizeof(valdat2));
  //memset(&tmpdat, '\0', sizeof(tmpdat));

}



