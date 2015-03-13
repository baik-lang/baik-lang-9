// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

GtkTreeIter funcIsiSimpulRanting ()
{

  char tmpMsg[MAX_STRING_LEN];
  char tmpMsg2[MAX_STRING_LEN];
  int  n=0;
  long    idx=0;                           // array index

  GtkTreeIter iter;

  GdkPixbuf *icon = NULL;
  GError *error = NULL;

  VAL_LABEL valdat,valdat2,tmpdat,tmpdat2;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));
  memset(tmpMsg2, '\0', sizeof(tmpMsg2));

  n = 0;

	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 1) {
                strcpy(tmpMsg, lex.detail.string );
              } else
              if(n == 2) {
                strcpy(tmpMsg2, lex.detail.string );
              } 
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

             if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
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

                valdat = ValLabel( lex.detail.ident , sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 3) {         // Teks
                if(n == 1) {
                  strcpy(tmpMsg, valdat.str );
                } else
                if(n == 2) {
                  strcpy(tmpMsg2, valdat.str );
                } 
			  } else if(valdat.datatype == 56) { // TreeStore
                if(n == 0) {
				  // printf("get TreeStore ... \n");
				  tmpdat  = valdat;
                  tmpdat.datatype = 56;
                } 
			  } else if(valdat.datatype == 55) { // TreeIter
                if(n == 3) {
				  // printf("get TreeIter ... \n");
				  tmpdat2 = valdat;
                  tmpdat2.datatype = 55;
                } 
			  } else {
                Error("bentuk perintah Isi_Ranting_Teks salah");
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

                if(valdat2.datatype == 8 && n == 1) {
                  get_str_array(valdat2, idx, (char *)&tmpMsg);
		} else if(valdat2.datatype == 8 && n == 2) {
                  get_str_array(valdat2, idx, (char *)&tmpMsg2);
		} else {
		  printf("jenis untaian belum disupport");
                }
                
              }

	      break;

	    default:
	      Error("bentuk perintah Isi_Ranting_Teks salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


	// printf("Isi Ranting Teks ...\n");

    icon = gdk_pixbuf_new_from_file(tmpMsg, &error);
	if(error) {
      Error("tidak bisa ambil file gambar \n");
	} 

    if(n == 3) {
	  // printf("param n 2 \n");
	  if(tmpdat.treestore == NULL) {
        printf("Error! TreeStore NULL 2 \n");
	  }

      if(tmpdat.datatype == 56) {
        gtk_tree_store_append (tmpdat.treestore, &iter, NULL);
        gtk_tree_store_set (tmpdat.treestore, &iter, 0, icon, 1, g_locale_to_utf8(tmpMsg2, -1,NULL,NULL,NULL), -1);
	  }
    } else if(n == 4){
	  // printf("param n 3 \n");
	  if(tmpdat.treestore == NULL) {
        printf("Error! TreeStore NULL \n");
	  }

	  if(&tmpdat2.treeiter == NULL) {
        printf("Warn! TreeIter NULL \n");
	  }

      if(tmpdat.datatype == 56) {
        gtk_tree_store_append (tmpdat.treestore, &iter, &tmpdat2.treeiter);
        gtk_tree_store_set (tmpdat.treestore, &iter, 0, icon, 1, g_locale_to_utf8(tmpMsg2, -1,NULL,NULL,NULL), -1);
	  }
	} else {
      Error("parameter Isi_Ranting_Teks tidak lengkap");
	}

	ungetlex();

	return iter;

}
