// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2012
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// UTF-8

void keyTambahMenu ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0, i=0, j=0;
  long idx=0;                           // array index

  VAL_LABEL valdat,valdat2,tmpdat, tmpdat2,tmpdat3;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));
  memset(&tmpdat3, '\0', sizeof(tmpdat3));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

  // printf("keyTambahMenu\n");
	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
   
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

              if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat.widget   = valdat.widget;
                  tmpdat.datatype = 40;
				  tmpdat.GUItype  = valdat.GUItype;
				} else if(n == 1) {
				  tmpdat2.widget   = valdat.widget;
                  tmpdat2.datatype = 40;
				  tmpdat2.GUItype  = valdat.GUItype;
				}
			  } else {
                Error("bentuk perintah Tambah_Menu salah");
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
                     #ifdef WIN32
                      #ifndef S_SPLINT_S
                      sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                      #else
                      snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                      #endif
                     #else
                     snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                     #endif
                     tmpdat3 = ValLabel( class_tmpvar, class_sub_deep, tmpdat3, VAL_FLAG_SEARCH_R );
                   } else {
                     tmpdat3 = ValLabel( valdat.array_idx, sub_deep, tmpdat3, VAL_FLAG_SEARCH_R );
		     // printf("get idx type: %d, val %d\n", tmpdat.datatype, tmpdat.val);
   		   }

                   if(tmpdat3.datatype==0)
                     idx = tmpdat3.val;
                   else
                      Error("Untaian salah masukan");
                }

		// get real value of array
		// printf("search array: %s\n", valdat.array_name);
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

                // ltoa(idx, valdat2.array_idx, 10);
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

                if(valdat2.datatype == 60 && n == 0) {           // Array GUI 
                  memset(&tmpdat, '\0', sizeof(tmpdat));
                  tmpdat.widget   = get_gui_array(valdat2, idx);
				  tmpdat.eventbox = get_eventbox_array(valdat2, idx);
				  tmpdat.GUItype  = get_guitype_array(valdat2, idx);
                  tmpdat.datatype = 40;
				  // printf("warna dasar : get GUI array\n");
				} else if(valdat2.datatype == 60 && n == 1) {    // Array GUI
                  memset(&tmpdat2, '\0', sizeof(tmpdat2));
                  tmpdat2.widget   = get_gui_array(valdat2, idx);
				  tmpdat2.eventbox = get_eventbox_array(valdat2, idx);
				  tmpdat2.GUItype  = get_guitype_array(valdat2, idx);
                  tmpdat2.datatype = 40;
                } else {
                  Error("salah jenis untaian");
                }
                
              }

	      break;

	    default:
	      Error("bentuk perintah Tambah_Menu salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 2) {
      Error("parameter Tambah_Menu tidak lengkap");
    } else {
      gtk_menu_shell_append(GTK_MENU_SHELL(tmpdat.widget), tmpdat2.widget);
    }

	ungetlex();

}


