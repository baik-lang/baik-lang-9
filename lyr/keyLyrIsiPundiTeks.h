// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyIsiPundiTeks ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0, i=0, j=0;
  long    idx=0;                           // array index

  GtkTreeIter iter;

  VAL_LABEL valdat,valdat2,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 1) {
                strcpy(tmpMsg, lex.detail.string );
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
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 3) {
                if(n == 1) {
                  strcpy(tmpMsg, valdat.str );
                } 
		  } else if(valdat.datatype == 47) { // list_store STRING
                if(n == 0) {
		  tmpdat  = valdat;
                  tmpdat.datatype = 47;
                } 
	      } else {
                Error("bentuk perintah Isi_Pundi_Teks salah");
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
                  sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_name);
                  valdat2 = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
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
		} else {
		  printf("jenis untaian belum disupport");
                }
                
              }

	      break;

	    default:
	      Error("bentuk perintah Isi_Pundi_Teks salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 2) {
      Error("parameter Isi_Pundi_Teks tidak lengkap");
    } else {
      if(tmpdat.datatype == 47) {
        gtk_list_store_append (tmpdat.liststore, &iter);
        gtk_list_store_set (tmpdat.liststore, &iter, 0, g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL), -1);
	  }
    }

	ungetlex();

}
