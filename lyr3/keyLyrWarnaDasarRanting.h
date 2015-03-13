// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// Set warna dasar to Sel Ranting (Tree)

void keyWarnaDasarRanting ()
{

  char tmpMsg[MAX_STRING_LEN];
  char warna[MAX_STRING_LEN];

  int  n=0, i=0, j=0;
  long idx=0;                           // array index

  VAL_LABEL valdat, valdat2, tmpdat, tmpdat2;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));
  memset(warna, '\0', sizeof(warna));

  n = 0;

	do{

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
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );

              } else {

				valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 3) {
                if(n == 1) {
                  strcpy(tmpMsg, valdat.str );
                } 
              } else if(valdat.datatype == 57) {        // Cell Renderer
                if(n == 0) {
		  tmpdat  = valdat;
                  tmpdat.datatype = 57;
                } 
	      } else {
                Error("bentuk perintah warnadasar_sel salah");
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
                     tmpdat2 = ValLabel( class_tmpvar, class_sub_deep, tmpdat2, VAL_FLAG_SEARCH_R );
		   } else {
                     tmpdat2 = ValLabel( valdat.array_idx, sub_deep, tmpdat2, VAL_FLAG_SEARCH_R );
		     // printf("get idx type: %d, val %d\n", tmpdat.datatype, tmpdat.val);
	           }

                   if(tmpdat2.datatype==0)
                     idx = tmpdat2.val;
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

                if(valdat2.datatype == 60 && n == 0) {  // Array GUI 
                  memset(&tmpdat, '\0', sizeof(tmpdat));
                  tmpdat.widget   = get_gui_array(valdat2, idx);
				  tmpdat.eventbox = get_eventbox_array(valdat2, idx);
				  tmpdat.GUItype  = get_guitype_array(valdat2, idx);
                  tmpdat.datatype = 57;
				  // printf("warna dasar : get GUI array\n");
                } else {
                  Error("salah jenis untaian");
                }
                
              }

	      break;

	    default:
	      Error("bentuk perintah warnadasar_sel salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 2) {
      Error("parameter warnadasar_sel tidak lengkap");
    } else {

		if(!strcmp(tmpMsg,"merah") || !strcmp(tmpMsg,"MERAH")) {
		  strcpy(warna, "red");
		} else
		if(!strcmp(tmpMsg,"hijau") || !strcmp(tmpMsg,"HIJAU")) {
		  strcpy(warna, "green");
		} else
		if(!strcmp(tmpMsg,"biru") || !strcmp(tmpMsg,"BIRU")) {
		  strcpy(warna, "blue");
		} else
		if(!strcmp(tmpMsg,"kuning") || !strcmp(tmpMsg,"KUNING")) {
		  strcpy(warna, "yellow");
		} else 
		if(!strcmp(tmpMsg,"merah muda") || !strcmp(tmpMsg,"MERAH MUDA")) {
		  strcpy(warna, "pink");
		} else
		if(!strcmp(tmpMsg,"biru muda") || !strcmp(tmpMsg,"BIRU MUDA")) {
		  strcpy(warna, "cyan");
		} else
		if(!strcmp(tmpMsg,"hitam") || !strcmp(tmpMsg,"HITAM")) {
		  strcpy(warna, "black");
		} else
		if(!strcmp(tmpMsg,"putih") || !strcmp(tmpMsg,"PUTIH")) {
		  strcpy(warna, "white");
		} else
		if(!strcmp(tmpMsg,"jingga") || !strcmp(tmpMsg,"JINGGA")) {
		  strcpy(warna, "orange");
		} else
		if(!strcmp(tmpMsg,"salmon") || !strcmp(tmpMsg,"SALMON")) {
		  strcpy(warna, "salmon");
		} else
		if(!strcmp(tmpMsg,"violet") || !strcmp(tmpMsg,"VIOLET")) {
		  strcpy(warna, "violet");
		} else
		if(!strcmp(tmpMsg,"coklat") || !strcmp(tmpMsg,"COKLAT")) {
		  strcpy(warna, "chocolate");
		} else
		if(!strcmp(tmpMsg,"coklat tua") || !strcmp(tmpMsg,"COKLAT TUA")) {
		  strcpy(warna, "chocolate4");
		} else
		if(!strcmp(tmpMsg,"hijau tua") || !strcmp(tmpMsg,"HIJAU TUA")) {
		  strcpy(warna, "DarkGreen");
		} else
		if(!strcmp(tmpMsg,"hijau muda") || !strcmp(tmpMsg,"HIJAU MUDA")) {
		  strcpy(warna, "LightGreen");
		} else
		if(!strcmp(tmpMsg,"hijau zaitun") || !strcmp(tmpMsg,"HIJAU ZAITUN")) {
		  strcpy(warna, "OliveDrab2");
		} else
		if(!strcmp(tmpMsg,"hijau zamrud") || !strcmp(tmpMsg,"HIJAU ZAMRUD")) {
		  strcpy(warna, "aquamarine");
		} else
		if(!strcmp(tmpMsg,"melon") || !strcmp(tmpMsg,"MELON")) {
		  strcpy(warna, "honeydew");
		} else
		if(!strcmp(tmpMsg,"biru tua") || !strcmp(tmpMsg,"BIRU TUA")) {
		  strcpy(warna, "DarkBlue");
		} else
		if(!strcmp(tmpMsg,"biru langit") || !strcmp(tmpMsg,"BIRU LANGIT")) {
		  strcpy(warna, "SkyBlue");
		} else
		if(!strcmp(tmpMsg,"biru laut") || !strcmp(tmpMsg,"BIRU LAUT")) {
		  strcpy(warna, "NavyBlue");
		} else
		if(!strcmp(tmpMsg,"merah anggrek") || !strcmp(tmpMsg,"MERAH ANGGREK")) {
		  strcpy(warna, "orchid");
		} else
		if(!strcmp(tmpMsg,"merah tomat") || !strcmp(tmpMsg,"MERAH TOMAT")) {
		  strcpy(warna, "tomato");
		} else
		if(!strcmp(tmpMsg,"merah bata") || !strcmp(tmpMsg,"MERAH BATA")) {
		  strcpy(warna, "firebrick");
		} else
		if(!strcmp(tmpMsg,"putih asap") || !strcmp(tmpMsg,"PUTIH ASAP")) {
		  strcpy(warna, "WhiteSmoke");
		} else
		if(!strcmp(tmpMsg,"putih gading") || !strcmp(tmpMsg,"PUTIH GADING")) {
		  strcpy(warna, "ivory");
		} else
		if(!strcmp(tmpMsg,"putih salju") || !strcmp(tmpMsg,"PUTIH SALJU")) {
		  strcpy(warna, "snow");
		} else
		if(!strcmp(tmpMsg,"putih gandum") || !strcmp(tmpMsg,"PUTIH GANDUM")) {
		  strcpy(warna, "wheat");
		} else {
		  strcpy(warna, "LightCyan");
		}

		// printf("warna dasar SEL %d %s\n", tmpdat.datatype, warna);

        if(tmpdat.datatype == 57) {
          g_object_set(tmpdat.renderer,"background",warna,NULL);
		}
    }

	ungetlex();

}
