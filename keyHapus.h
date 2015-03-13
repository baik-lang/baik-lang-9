// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// 2015/7/15

void keyHapus ()
{
  char ident[MAX_IDENT_LEN];

  char logMsg[MAX_STRING_LEN * 2],
       tmpMsg[MAX_STRING_LEN * 2];

  long  n=0, i=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];


  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  
  memset(&ident, '\0', sizeof(ident));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));
  memset(&logMsg, '\0', sizeof(logMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));
  memset(&tmp_str, '\0', sizeof(tmp_str));

  do {
	  getlex();

      strcpy(tmpMsg, lex.detail.ident);

      // printf(" DEBUG: HAPUS name %s lex.type %d , deep %d\n", tmpMsg, lex.type, sub_deep);

	  switch( lex.type )
	    {
	    case TYPE_IDENT:
              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
				// printf("tulis: construct class var: %s , deep %d\n", class_tmpvar, class_sub_deep);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              } else {
                valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              // printf("name %s type %d\n", tmpMsg, valdat.datatype);

              if(valdat.datatype >=0 && valdat.datatype <=8) {
				// printf("hapus ident0: %s\n", valdat.ident);

				if(valdat.datatype == 6) {
				  for(i=0; i<valdat.array_max; i++)
                    del_int_array(valdat, i);
				}

				if(valdat.datatype == 7) {
				  for(i=0; i<valdat.array_max; i++)
                    del_dbl_array(valdat, i);
				}

				if(valdat.datatype == 8) {
				  for(i=0; i<valdat.array_max; i++)
                    del_str_array(valdat, i);
				}

                memset(&tmpdat,'\0',sizeof(tmpdat));
                ValLabel( lex.detail.ident , sub_deep, tmpdat, VAL_FLAG_SEARCH_W ); // delete memory stack

              } else if(valdat.datatype ==31) {  // class instance
                // printf("hapus objek %s\n", valdat.ident);
                // printf("benda name: %s\n", valdat.benda_name);

                // Get All params of Benda
                class_params_init();
                // Set Benda name for searching
                strcpy(tmpnode.class_name , valdat.benda_name);
                // Searching all params of Benda
                class_findParams(tmpnode);

                if(class_params.total == 0) {
                   // printf("parameter not found\n");
                } else {
                  // printf("parameter found\n");

                  for(i=0; i<class_params.total; i++) {
                    // printf("%d pos %d name: %s\n", i, class_params.pos[i], class_params.name[i]);
                    // get real value of each param
                    tmpnode = node_getElement(i);

                    memset(&tmp_str, '\0', sizeof(tmp_str));
					sprintf(tmp_str,"%s->%s", lex.detail.ident, tmpnode.param_name);
                    if(tmpnode.param_name !=NULL && strlen(tmpnode.param_name) >= 0) {
                      // printf("clear memory of obj param: %s\n", tmp_str);
                      memset(&tmpdat,'\0',sizeof(tmpdat));
                      tmpdat.datatype = -1;
                      ValLabel( tmp_str , sub_deep, tmpdat, VAL_FLAG_SEARCH_W ); // delete memory stack
                    }
                  }
                }

                // printf("clear memory of obj: %s\n", valdat.ident);
                memset(&tmpdat,'\0',sizeof(tmpdat));
                tmpdat.datatype = -1;
                ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_W );

              #ifdef USE_GTK2

			  } else if(valdat.datatype == 40 && valdat.GUItype == 21) {  //Tabel
                // printf("CLEAR TABEL \n");
				gtk_list_store_clear(valdat.liststore);

                memset(&tmpdat,'\0',sizeof(tmpdat));
                ValLabel( lex.detail.ident , sub_deep, tmpdat, VAL_FLAG_SEARCH_W ); // delete memory stack

			//  } else if(valdat.datatype == 42 ) {  //font desc
			//	if(valdat.pango_layout != NULL) {
            //      // printf("CLEAR font desc \n");
			//	  pango_font_description_free(valdat.font_desc);
			//	}

                memset(&tmpdat,'\0',sizeof(tmpdat));
                ValLabel( lex.detail.ident , sub_deep, tmpdat, VAL_FLAG_SEARCH_W ); // delete memory stack

              #endif

              } else {
                strcpy(ident, valdat.ident);
				// printf("hapus ident: %s , type %d\n", ident, valdat.datatype);
                memset(&tmpdat,'\0',sizeof(tmpdat));
				tmpdat.datatype = valdat.datatype;
                ValLabel( ident , sub_deep, tmpdat, VAL_FLAG_SEARCH_D ); // delete memory stack
              }
	      break;

	    case TYPE_ARRAY:

              if(strlen(lex.detail.array_str) > 0) {

                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atol (valdat.array_idx);
                } else {
				   // printf("show NOT digit : %s\n", valdat.array_idx);
                   /* Read index param */

                   if(currentClass != NULL && strlen(currentClass) > 0) {
                     sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_idx);
                     tmpdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
				   } else {
                     tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
				     // printf("get idx type: %d, val %d\n", tmpdat.datatype, tmpdat.val);
   		           }

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

				// get real value of array
				// printf("search array: %s\n", valdat.array_name);
                if(currentClass != NULL && strlen(currentClass) > 0) {
				  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_name);
                  valdat2 = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
				} else {
                  valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
				}
                // ltoa(idx, valdat2.array_idx, 10);
				sprintf(valdat2.array_idx, "%li", idx);

				// printf("idx %d\n", idx);
				// printf("max kapasitas %d\n", valdat2.array_max);
                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

				// printf("get valdat2 type: %d, val %d\n", valdat2.datatype, valdat2.val);

                if(valdat2.datatype == 6) {
                  del_int_array(valdat2, idx);
                } else if (valdat2.datatype == 7) {
                  del_dbl_array(valdat2, idx);
                } else if (valdat2.datatype == 8) {
                  del_str_array(valdat2, idx);
                } else {
                  if(currentClass != NULL && strlen(currentClass) > 0) {
                    ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_D );
				  } else {
                    ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_D );
				  }
                }
                
              }

	      break;

	    default:
	      Error("kode perintah HAPUS salah");
	    }


		getlex();

		// printf("chek next %d\n",  lex.type);

	} while (lex.type == TYPE_SYM && lex.detail.symbol == ','  && lex.detail.symbol != '\n');

	ungetlex();

	// printf("end keyHapus\n");
}


