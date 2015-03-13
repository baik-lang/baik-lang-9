// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyPilih ()
{
  char tmpMsg[MAX_STRING_LEN];

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat, valdat0;

  long    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmp_str, '\0', sizeof(tmp_str));
  
  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    getlex();

	if( lex.type == TYPE_IDENT ){
          // keep parameter name
          strcpy(tmpMsg, lex.detail.ident);
          // get parameter value
          memset(&valdat,'\0',sizeof(valdat));

          if(currentClass != NULL && strlen(currentClass) > 0) {

            #ifdef WIN32
             #ifndef S_SPLINT_S
             sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, tmpMsg);
             #else
             snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, tmpMsg);
             #endif
            #else
            snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, tmpMsg);
            #endif

            valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
          } else {
            valdat = ValLabel( tmpMsg, sub_deep, valdat, VAL_FLAG_SEARCH_R );
		  }

		  // printf("pilih ident %s , type %d , val %d \n", tmpMsg, valdat.datatype, valdat.val);

          // get { code
          getlex();

          if( lex.type != TYPE_SYM || strncmp(lex.detail.string , "{", 1) != 0 ) {
            Error("kode PILIH salah : tanpa tanda pembuka {");
          }


	  do{
        getlex();
	    if( lex.type == _SAMA ) {
              // get CASE value
              getlex();

              // get NUM value
              if(lex.type == TYPE_NUM) {
                if(valdat.datatype == 0) {
                  if(valdat.val == lex.detail.num) {
                    break;
                    // interprete case code.
                  } else 
                    do {
                      getlex();
                    } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                    if( lex.type == _EOF )
                       Error("PILIH tanpa AKHIRPILIH");
                    continue;
                } else {
                  continue;
                }

              } else if(lex.type == TYPE_DBL) {
                if(valdat.datatype == 1) {
                  if(valdat.floatdata == lex.detail.dblnum) {
                    break;
                    // interprete case code.
                  } else 
                    do {
                      getlex();
                    } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                    if( lex.type == _EOF )
                       Error("PILIH tanpa AKHIRPILIH");
                    continue;
                } else {
                  continue;
                }


              } else if(lex.type == TYPE_STR) {
                if(valdat.datatype == 3) {
                  if(!strcmp(lex.detail.string, valdat.str)) {
                    break;
                    // interprete case code.
                  } else 
                    do {
                      getlex();
                    } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                    if( lex.type == _EOF )
                       Error("PILIH tanpa AKHIRPILIH");
                    continue;
                } else {
                  continue;
                }


              } else if( lex.type == TYPE_IDENT ){
                // get parameter value
                memset(&valdat2,'\0',sizeof(valdat2));
                memset(&tmpMsg, '\0', sizeof(tmpMsg));

                // keep parameter name
                strcpy(tmpMsg, lex.detail.ident);

                if(currentClass != NULL && strlen(currentClass) > 0) {
                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, tmpMsg);
                   #else
                   snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, tmpMsg);
                   #endif
                  #else
                  snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, tmpMsg);
                  #endif

                  valdat2 = ValLabel( class_tmpvar, class_sub_deep, valdat2, VAL_FLAG_SEARCH_R );
                } else {
                  valdat2 = ValLabel( tmpMsg, sub_deep, valdat2, VAL_FLAG_SEARCH_R );
		        }

		        // printf("pilih get value type %d , val %d \n", valdat2.datatype, valdat2.val);

                if(valdat.datatype == valdat2.datatype) {
                  // printf("sejenis %d\n", valdat.datatype);
                  if((valdat.datatype == 0 && valdat.val == valdat2.val) ||
                     (valdat.datatype == 1 && valdat.floatdata == valdat2.floatdata) ||
                     (valdat.datatype == 3 && !strcmp(valdat.str, valdat2.str)) )
                  {
                    // printf("sama\n");
                    break;
                    // interprete case code.

                  } else {
                    // printf("tidak sama\n");
                    do {
                      getlex();
                    } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                    if( lex.type == _EOF )
                       Error("PILIH tanpa AKHIRPILIH");
                    continue;
                  }
                } else {
                   // printf("tidak sejenis\n");
                  do {
                    getlex();
                  } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                  if( lex.type == _EOF )
                     Error("PILIH tanpa AKHIRPILIH");
                  continue;
                }

              } else if(lex.type == TYPE_ARRAY) {

                if(strlen(lex.detail.array_str) > 0) {
                  strcpy(valdat0.array_str, lex.detail.array_str);

                  getArrayName(lex.detail.array_str, (char *)&valdat0.array_name);
                  getArrayIdx(lex.detail.array_str, (char *)&valdat0.array_idx);

                  if(isdigit(valdat0.array_idx[0])) {
                    /* printf("show digit\n"); */
                    idx = atol (valdat0.array_idx);
                  } else {
                    /* printf("show NOT digit\n"); */
                    /* Read index param */
                    if(currentClass != NULL && strlen(currentClass) > 0) {
                      #ifdef WIN32
                       #ifndef S_SPLINT_S
                       sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_idx);
                       #else
                       snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_idx);
                       #endif
                      #else
                      snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_idx);
                      #endif

                      tmpdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
				    } else {
                      tmpdat = ValLabel( valdat0.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
				    }

                    if(tmpdat.datatype==0)
                      idx = tmpdat.val;
                    else
                      Error("Untaian salah masukan p1");
                  }

		  // printf("pilih get array: %s idx %s, idx val %d \n", valdat0.array_name, valdat0.array_idx, idx);

                  if(currentClass != NULL && strlen(currentClass) > 0) {
		    memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                    #ifdef WIN32
                     #ifndef S_SPLINT_S
                     sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_name);
                     #else
                     snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_name);
                     #endif
                    #else
                    snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_name);
                    #endif

                    valdat2 = ValLabel( class_tmpvar, sub_deep, valdat0, VAL_FLAG_SEARCH_R );
		  } else {
	            valdat2 = ValLabel( valdat0.array_name, sub_deep, valdat0, VAL_FLAG_SEARCH_R );
                  }

	          // printf("pilih get array value type %d val %d \n", valdat2.datatype, get_int_array(valdat2, idx));

                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx);
                   #else
                   snprintf(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx);
                   #endif
                  #else
                  snprintf(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx);
                  #endif

                  if(idx < 0 || idx > (valdat2.array_max-1))
                    Error("ukuran Untaian tidak sesuai kapasitas p1");

                  if((valdat.datatype == 0 && valdat2.datatype == 6 && valdat.val == get_int_array(valdat2, idx)) ||
                     (valdat.datatype == 1 && valdat2.datatype == 7 && valdat.floatdata == get_dbl_array(valdat2, idx)) ||
                     (valdat.datatype == 3 && valdat2.datatype == 8 ) )
                  {
                    // printf("sama\n");
                    break;
                    // interprete case code.

                  } else {
                    // printf("tidak sama\n");
                    do {
                      getlex();
                    } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                    if( lex.type == _EOF )
                       Error("PILIH tanpa AKHIRPILIH");
                    continue;
                  }

                }


              } else {
                continue;
              }


            } // end if SAMA


	  }while( strncmp(lex.detail.string , "}", 1) != 0 && lex.type != _EOF );
	  if( lex.type == _EOF )
	    Error("PILIH tanpa tanda penutup }");

	} // end TYPE_IDENT

    else

	if( lex.type == TYPE_ARRAY ){
          // keep parameter name
          strcpy(tmpMsg, lex.detail.array_str);

          // get parameter value
          memset(&valdat,'\0',sizeof(valdat));

          strcpy(valdat0.array_str, lex.detail.array_str);
          getArrayName(lex.detail.array_str, (char *)&valdat0.array_name);
          getArrayIdx(lex.detail.array_str, (char *)&valdat0.array_idx);

          if(isdigit(valdat0.array_idx[0])) {
            /* printf("show digit\n"); */
            idx = atol (valdat0.array_idx);
          } else {
            /* printf("show NOT digit\n"); */
            /* Read index param */

            if(currentClass != NULL && strlen(currentClass) > 0) {
              #ifdef WIN32
                #ifndef S_SPLINT_S
                sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_idx);
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_idx);
                #endif
              #else
              snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_idx);
              #endif

              tmpdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
            } else {
              tmpdat = ValLabel( valdat0.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
            }

            if(tmpdat.datatype==0)
              idx = tmpdat.val;
            else
              Error("Untaian salah masukan");
          }

          if(currentClass != NULL && strlen(currentClass) > 0) {
            #ifdef WIN32
              #ifndef S_SPLINT_S
              sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_name);
              #else
              snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_name);
              #endif
            #else
            snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat0.array_name);
            #endif

            valdat = ValLabel( class_tmpvar, class_sub_deep, valdat0, VAL_FLAG_SEARCH_R );
	  } else {
            valdat = ValLabel( valdat0.array_name, sub_deep, valdat0, VAL_FLAG_SEARCH_R );
	  }

          #ifdef WIN32
           #ifndef S_SPLINT_S
           sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
           #else
           snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
           #endif
          #else
          snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
          #endif

          if(idx < 0 || idx > (valdat.array_max-1))
             Error("ukuran Untaian tidak sesuai kapasitas p333 ");


          // get { code
          getlex();

          if( lex.type != TYPE_SYM || strncmp(lex.detail.string , "{", 1) != 0 ) {
            Error("kode PILIH salah : tanpa tanda pembuka {");
          }


	  do{
            getlex();
	    if( lex.type == _SAMA ) {
              // get CASE value
              getlex();

              // get NUM value
              if(lex.type == TYPE_NUM) {
                if(valdat.datatype == 6) {
                  if(get_int_array(valdat, idx) == lex.detail.num) {
                    break;
                    // interprete case code.
                  } else 
                    do {
                      getlex();
                    } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                    if( lex.type == _EOF )
                       Error("PILIH tanpa AKHIRPILIH");
                    continue;
                } else {
                  continue;
                }

              } else if(lex.type == TYPE_DBL) {
                if(valdat.datatype == 7) {
                  if(get_dbl_array(valdat, idx) == lex.detail.dblnum) {
                    break;
                    // interprete case code.
                  } else 
                    do {
                      getlex();
                    } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                    if( lex.type == _EOF )
                       Error("PILIH tanpa AKHIRPILIH");
                    continue;
                } else {
                  continue;
                }


              } else if(lex.type == TYPE_STR) {
                if(valdat.datatype == 8) {

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				  memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				  strcpy(TmpStrBox.var.array_name, valdat.array_name);
                  renban = valdat.array_s;

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

                  if(!strcmp(lex.detail.string, TmpStrBox.str.mystring)) {
                    break;
                    // interprete case code.
                  } else 
                    do {
                      getlex();
                    } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                    if( lex.type == _EOF )
                       Error("PILIH tanpa AKHIRPILIH");
                    continue;
                } else {
                  continue;
                }


              } else if( lex.type == TYPE_IDENT ){
                // get parameter value
                memset(&valdat2,'\0',sizeof(valdat2));
                memset(&tmpMsg, '\0', sizeof(tmpMsg));

                // keep parameter name
                strcpy(tmpMsg, lex.detail.ident);

                if(currentClass != NULL && strlen(currentClass) > 0) {
                  sprintf(class_tmpvar, "%s->%s", currentClass, tmpMsg);
                  valdat2 = ValLabel( class_tmpvar, sub_deep, valdat2, VAL_FLAG_SEARCH_R );
                } else {
                  valdat2 = ValLabel( tmpMsg, sub_deep, valdat2, VAL_FLAG_SEARCH_R );
		        }

                // valdat2 = ValLabel( lex.detail.ident, valdat2, VAL_FLAG_SEARCH_R );
                if(valdat.datatype == valdat2.datatype) {
                  // printf("sejenis\n");
                  if((valdat.datatype == 6 && get_int_array(valdat, idx) == valdat2.val) ||
                     (valdat.datatype == 7 && get_dbl_array(valdat, idx) == valdat2.floatdata) ||
                     (valdat.datatype == 8 ) )
                  {
                    // printf("sama\n");
                    break;
                    // interprete case code.

                  } else {
                    // printf("tidak sama\n");
                    do {
                      getlex();
                    } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                    if( lex.type == _EOF )
                       Error("PILIH tanpa AKHIRPILIH");
                    continue;
                  }
                } else {
                  // printf("tidak sejenis\n");
                  do {
                    getlex();
                  } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                  if( lex.type == _EOF )
                     Error("PILIH tanpa AKHIRPILIH");
                  continue;
                }

              } else if(lex.type == TYPE_ARRAY) {

                if(strlen(lex.detail.array_str) > 0) {
                  strcpy(valdat0.array_str, lex.detail.array_str);

                  getArrayName(lex.detail.array_str, (char *)&valdat0.array_name);
                  getArrayIdx(lex.detail.array_str, (char *)&valdat0.array_idx);

                  // printf("pilih ARRAY1 sama ARRAY2\n");

                  if(isdigit(valdat0.array_idx[0])) {
                    /* printf("show digit\n"); */
                    idx2 = atol (valdat0.array_idx);
                  } else {
                    /* printf("show NOT digit\n"); */
                    /* Read index param */

                    if(currentClass != NULL && strlen(currentClass) > 0) {
                      sprintf(class_tmpvar, "%s->%s", currentClass, valdat0.array_idx);			  
                      tmpdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
			        } else {
                      tmpdat = ValLabel( valdat0.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
			        }

                    if(tmpdat.datatype==0)
                      idx2 = tmpdat.val;
                    else
                      Error("Untaian salah masukan p2");
                  }

                  if(currentClass != NULL && strlen(currentClass) > 0) {
				    memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                    sprintf(class_tmpvar, "%s->%s", currentClass, valdat0.array_name);
	                valdat2 = ValLabel( class_tmpvar, sub_deep, valdat0, VAL_FLAG_SEARCH_R );
				  } else {
	                valdat2 = ValLabel( valdat0.array_name, sub_deep, valdat0, VAL_FLAG_SEARCH_R );
				  }


                  sprintf(valdat2.array_idx, "%li", idx2);

                  if(idx2 < 0 || idx2 > (valdat2.array_max-1))
                    Error("ukuran Untaian tidak sesuai kapasitas p2");

                   /*
                   printf("arr1 type : %d\n", valdat.datatype);
                   printf("arr1 idx : %d\n", idx);
                   printf("arr2 type : %d\n", valdat2.datatype);
                   printf("arr2 idx : %d\n", idx2);
                   */

                  if((valdat.datatype == 6 && valdat2.datatype == 6 &&  get_int_array(valdat, idx) == get_int_array(valdat2, idx2) ) ||
                     (valdat.datatype == 7 && valdat2.datatype == 7 && get_dbl_array(valdat, idx) == get_dbl_array(valdat2, idx2)) ||
                     (valdat.datatype == 8 ) )
                  {
                    // printf("sama\n");
                    break;
                    // interprete case code.

                  } else {
                    // printf("tidak sama\n");
                    do {
                      getlex();
                    } while ( lex.type != _AKHIRPILIH && lex.type != _EOF );
                    if( lex.type == _EOF )
                       Error("PILIH tanpa AKHIRPILIH");
                    continue;
                  }

                }


              } else {
                continue;
              }


            } // end if SAMA


	  }while( strncmp(lex.detail.string , "}", 1) != 0 && lex.type != _EOF );
	  if( lex.type == _EOF )
	    Error("PILIH tanpa tanda penutup }");

	} // end TYPE_ARRAY


  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));

  if(valdat.filename != NULL)
    free(valdat.filename);
  if(valdat.folder != NULL)
    free(valdat.folder);
  if(valdat.filedata != NULL)
    free(valdat.filedata);
  if(valdat.long_str != NULL)
    free(valdat.long_str);

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  if(tmpdat.filename != NULL)
    free(tmpdat.filename);
  if(tmpdat.folder != NULL)
    free(tmpdat.folder);
  if(tmpdat.filedata != NULL)
    free(tmpdat.filedata);
  if(tmpdat.long_str != NULL)
    free(tmpdat.long_str);

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);


}

