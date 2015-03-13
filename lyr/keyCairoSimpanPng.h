
// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// simpan lukisan

void keyCairoSimpanLukisan ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  char   dat_a[MAX_STRING_LEN];

  cairo_surface_t *surface=NULL;

  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;
	do{

	  getlex();
          // if(isDEBUG == 1) printf(" DEBUG: SIMPAN_LUKISAN lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    
	    case TYPE_STR:
              if(n == 1) {                        /* png filename */
                if(lex.detail.string  != '\0' && strlen(lex.detail.string) > 0) {
                  sprintf(dat_a, "%s", lex.detail.string );
                } else {
                  Error("kode perintah SIMPAN_LUKISAN salah : nama File");
                }
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

                /* ÉfÅ[É^ì«Ç›çûÇ› */
	            valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                sprintf(valdat2.array_idx, "%li", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(valdat2.datatype == 8  && valdat2.array_s != '\0') {
                  if(valdat2.array_s == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				  memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				  strcpy(TmpStrBox.var.array_name, valdat2.array_name);
                  renban = valdat2.array_s;

				  if(renban < 0) {
                    printf("variabel untaian tidak ditemukan\n");
				  } else {
                    TmpStrBox.str.stackid = renban;
                    TmpStrBox.str.idx = idx;

					strarryPos = string_findData(TmpStrBox.str);
					if(strarryPos < 0) {
  					  // printf("\n! nilai untaian kata tidak ditemukan");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);

					}

				  }

				  if(n == 1) {                       /* png filename */
                    strcpy(dat_a, TmpStrBox.str.mystring );

				  }

                } else if (valdat2.datatype == 10) {
                  if(n == 1)                        /* png filename */
                    strcpy(dat_a, valdat2.long_str[idx]);
                }

              }

              break;

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
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

               valdat = ValLabel( lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

			  }

              //printf("\n datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.datatype == 3) {
                if(n == 1) {                        /* png filename */
                  if(strlen(valdat.str) > 0) {
                    sprintf(dat_a, "%s", valdat.str);
                  } else {
                    Error("kode perintah SIMPAN_LUKISAN salah : nama File");
                  }
                }
              } else if(valdat.datatype == 81) {    /* cairo surface      */
				  if(n == 0) {
                    surface  = valdat.cr_surface;
				  }
              } else {
                 Error("kode perintah SIMPAN_LUKISAN salah");
              }

	      break;

	    default:
	      Error("kode perintah SIMPAN_LUKISAN salah");
	    }

      n++;
	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

    if(n != 2) {
      Error("parameter kode perintah SIMPAN_LUKISAN salah");
    } else {
      /* printf("png file: %s\n", dat_a); */
	  if(surface != NULL) {
        cairo_surface_write_to_png(surface, dat_a);
      }

    }

	ungetlex();

}
