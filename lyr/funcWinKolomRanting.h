// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2012
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// UTF-8

VAL_LABEL funcWinKolomRanting ()
{

  char tmpMsg[MAX_STRING_LEN];

  int  n=0, i=0;
  long    idx=0;                           // array index

  VAL_LABEL valdat,valdat2,tmpdat,tmpdat2;

 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 0) {
                strcpy(tmpMsg, g_locale_to_utf8(lex.detail.string, -1,NULL,NULL,NULL));
              } 
	      break;

	    case TYPE_NUM:
              if(n == 0) {
                sprintf(tmpMsg, "%li", lex.detail.num);
              } 
	      break;

	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              memset(&valdat, '\0', sizeof(valdat));
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

                valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 0) {                // int
                if(n == 0) {
                  sprintf(tmpMsg, "%li" , valdat.val );
                } 
			  } else if(valdat.datatype == 3) {         // Teks
                if(n == 0) {
                  sprintf(tmpMsg, "%s" , valdat.str );
                }
			  } else if(valdat.datatype == 57) {        // Cell Renderer
                if(n == 1) {
				  // printf("get renderer 1\n");
				  tmpdat  = valdat;
                  tmpdat.datatype = 57;
                } else
                if(n == 2) {
				  // printf("get renderer 2\n");
				  tmpdat2  = valdat;
                  tmpdat2.datatype = 57;
                } 
			  } else {
                Error("bentuk perintah Kolom_Ranting salah");
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

                   if(currentClass != NULL && strlen(currentClass) > 0) {
                     #ifdef WIN32
                      #ifndef S_SPLINT_S
                      sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                      #else
                      snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                      #endif
                     #else
                     snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                     #endif

                     tmpdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
		   } else {
                     tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
		     // printf("get idx type: %d, val %d\n", tmpdat.datatype, tmpdat.val);
	           }

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

                if(currentClass != NULL && strlen(currentClass) > 0) {
		  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                   #else
                   snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                   #endif
                  #else
                  snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                  #endif

                  valdat2 = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
		} else {
                  valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
		}

		//sprintf(valdat2.array_idx, "%d", idx);
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
                  Error("ukuran Untaian tidak sesuai kapasitas");

				// printf("get valdat2 type: %d, val %d\n", valdat2.datatype, valdat2.val);

                if(valdat2.datatype == 8 && n == 0) {
                  get_str_array(valdat2, idx, (char *)&tmpMsg);
				} else {
				  printf("jenis untaian belum disupport");
                }
                
              }

	      break;

	    default:
	      Error("bentuk perintah Kolom_Ranting salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

    memset(&valdat, '\0', sizeof(valdat));
    memset(&valdat2, '\0', sizeof(valdat2));

    if(n == 3){
      if(tmpdat.datatype == 57) {
		// tmpdat2.treecolumn = gtk_tree_view_column_new_with_attributes (tmpMsg, tmpdat.renderer , tmpMsg2, pos, NULL);

		valdat2.treecolumn = gtk_tree_view_column_new();
        gtk_tree_view_column_set_title(valdat2.treecolumn, tmpMsg);

        gtk_tree_view_column_pack_start(valdat2.treecolumn, tmpdat.renderer, FALSE);
        gtk_tree_view_column_set_attributes(valdat2.treecolumn, tmpdat.renderer,"pixbuf", 0,NULL);

        gtk_tree_view_column_pack_start(valdat2.treecolumn, tmpdat2.renderer, TRUE);
        gtk_tree_view_column_set_attributes(valdat2.treecolumn, tmpdat2.renderer,"text", 1, NULL);

		valdat2.datatype = 58;
		valdat2.isGUI = 1;
	  }
	} else {
      Error("parameter Kolom_Ranting tidak lengkap");
	}

	ungetlex();

	return valdat2;

}
