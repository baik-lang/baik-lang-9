// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// Set warna huruf to perangkat

void keySetWarnaHuruf ()
{

  char tmpMsg[MAX_STRING_LEN];

  GdkColor mycolor;

  int  n=0;
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


  tmpdat2.datatype = 0; // just init

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

			  // printf("look for warna %s\n", lex.detail.ident);

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
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {
		valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

	      // printf("get warna n %d type %d gui %d\n", n, valdat.datatype, valdat.isGUI);

              if(valdat.datatype == 3 && valdat.isGUI != 1) {
                if(n == 1) {
                  strcpy(tmpMsg, valdat.str );
                }
              } else if(valdat.datatype == 3 && valdat.isGUI == 1) {
                if(n == 1) {
                 strcpy(tmpMsg, valdat.str );
                 // printf("tmpdat2 dialog warna\n");
		  tmpdat2   = valdat;
                  tmpdat2.datatype = 43;
                } 
			  } else if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat.widget   = valdat.widget;
				  tmpdat.GUItype  = valdat.GUItype;
                  tmpdat.datatype = 40;
                } 
			  } else if(valdat.datatype == 43) { // color from dialog
                if(n == 1) {
	              // printf("tmpdat2 dialog warna\n");
				  tmpdat2   = valdat;
                  tmpdat2.datatype = 43;
                }
			  } else {
                Error("bentuk perintah Set_WarnaHuruf salah");
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

                  valdat2 = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
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
                  tmpdat.datatype = 40;
				  // printf("warna huruf : get GUI array\n");
                } else {
                  Error("salah jenis untaian");
                }
                
              }

	      break;

	    default:
	      Error("bentuk perintah Set_WarnaHuruf salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 2) {
      Error("parameter Titel_Layar tidak lengkap");
    } else {

	  if(tmpdat2.datatype == 0) {

		if(!strcmp(tmpMsg,"merah") || !strcmp(tmpMsg,"MERAH")) {
		  gdk_color_parse((gchar*) "red", &mycolor);
		} else
		if(!strcmp(tmpMsg,"hijau") || !strcmp(tmpMsg,"HIJAU")) {
		  gdk_color_parse((gchar*) "green", &mycolor);
		} else
		if(!strcmp(tmpMsg,"biru") || !strcmp(tmpMsg,"BIRU")) {
		  gdk_color_parse((gchar*) "blue", &mycolor);
		} else
		if(!strcmp(tmpMsg,"kuning") || !strcmp(tmpMsg,"KUNING")) {
		  gdk_color_parse((gchar*) "yellow", &mycolor);
		} else 
		if(!strcmp(tmpMsg,"merah muda") || !strcmp(tmpMsg,"MERAH MUDA")) {
		  gdk_color_parse((gchar*) "pink", &mycolor);
		} else
		if(!strcmp(tmpMsg,"biru muda") || !strcmp(tmpMsg,"BIRU MUDA")) {
		  gdk_color_parse((gchar*) "cyan", &mycolor);
		} else
		if(!strcmp(tmpMsg,"hitam") || !strcmp(tmpMsg,"HITAM")) {
		  gdk_color_parse((gchar*) "black", &mycolor);
		} else
		if(!strcmp(tmpMsg,"putih") || !strcmp(tmpMsg,"PUTIH")) {
		  gdk_color_parse((gchar*) "white", &mycolor);
		} else
		if(!strcmp(tmpMsg,"jingga") || !strcmp(tmpMsg,"JINGGA")) {
		  gdk_color_parse((gchar*) "orange", &mycolor);
		} else
		if(!strcmp(tmpMsg,"salmon") || !strcmp(tmpMsg,"SALMON")) {
		  gdk_color_parse((gchar*) "salmon", &mycolor);
		} else
		if(!strcmp(tmpMsg,"violet") || !strcmp(tmpMsg,"VIOLET")) {
		  gdk_color_parse((gchar*) "violet", &mycolor);
		} else
		if(!strcmp(tmpMsg,"coklat") || !strcmp(tmpMsg,"COKLAT")) {
		  gdk_color_parse((gchar*) "chocolate", &mycolor);
		} else
		if(!strcmp(tmpMsg,"coklat tua") || !strcmp(tmpMsg,"COKLAT TUA")) {
		  gdk_color_parse((gchar*) "chocolate4", &mycolor);
		} else
		if(!strcmp(tmpMsg,"hijau tua") || !strcmp(tmpMsg,"HIJAU TUA")) {
		  gdk_color_parse((gchar*) "DarkGreen", &mycolor);
		} else
		if(!strcmp(tmpMsg,"hijau muda") || !strcmp(tmpMsg,"HIJAU MUDA")) {
		  gdk_color_parse((gchar*) "LightGreen", &mycolor);
		} else
		if(!strcmp(tmpMsg,"hijau zaitun") || !strcmp(tmpMsg,"HIJAU ZAITUN")) {
		  gdk_color_parse((gchar*) "OliveDrab2", &mycolor);
		} else
		if(!strcmp(tmpMsg,"hijau zamrud") || !strcmp(tmpMsg,"HIJAU ZAMRUD")) {
		  gdk_color_parse((gchar*) "aquamarine", &mycolor);
		} else
		if(!strcmp(tmpMsg,"melon") || !strcmp(tmpMsg,"MELON")) {
		  gdk_color_parse((gchar*) "honeydew", &mycolor);
		} else
		if(!strcmp(tmpMsg,"biru tua") || !strcmp(tmpMsg,"BIRU TUA")) {
		  gdk_color_parse((gchar*) "DarkBlue", &mycolor);
		} else
		if(!strcmp(tmpMsg,"biru langit") || !strcmp(tmpMsg,"BIRU LANGIT")) {
		  gdk_color_parse((gchar*) "SkyBlue", &mycolor);
		} else
		if(!strcmp(tmpMsg,"biru laut") || !strcmp(tmpMsg,"BIRU LAUT")) {
		  gdk_color_parse((gchar*) "NavyBlue", &mycolor);
		} else
		if(!strcmp(tmpMsg,"merah anggrek") || !strcmp(tmpMsg,"MERAH ANGGREK")) {
		  gdk_color_parse((gchar*) "orchid", &mycolor);
		} else
		if(!strcmp(tmpMsg,"merah tomat") || !strcmp(tmpMsg,"MERAH TOMAT")) {
		  gdk_color_parse((gchar*) "tomato", &mycolor);
		} else
		if(!strcmp(tmpMsg,"merah bata") || !strcmp(tmpMsg,"MERAH BATA")) {
		  gdk_color_parse((gchar*) "firebrick", &mycolor);
		} else
		if(!strcmp(tmpMsg,"putih asap") || !strcmp(tmpMsg,"PUTIH ASAP")) {
		  gdk_color_parse((gchar*) "WhiteSmoke", &mycolor);
		} else
		if(!strcmp(tmpMsg,"putih gading") || !strcmp(tmpMsg,"PUTIH GADING")) {
		  gdk_color_parse((gchar*) "ivory", &mycolor);
		} else
		if(!strcmp(tmpMsg,"putih salju") || !strcmp(tmpMsg,"PUTIH SALJU")) {
		  gdk_color_parse((gchar*) "snow", &mycolor);
		} else
		if(!strcmp(tmpMsg,"putih gandum") || !strcmp(tmpMsg,"PUTIH GANDUM")) {
		  gdk_color_parse((gchar*) "wheat", &mycolor);
		} else {
		  gdk_color_parse((gchar*) "LightCyan", &mycolor);
		}

	  } else{
	    // printf("mycolor dialog warna\n");
		mycolor = tmpdat2.color;
	  }

	  if(tmpdat.GUItype == 5 ||   // input - masukan
		   tmpdat.GUItype == 12) {  // text area - kertas
             gtk_widget_modify_text(tmpdat.widget, GTK_STATE_NORMAL, &mycolor);
	  } else {                  // label - button dll
          gtk_widget_modify_fg(tmpdat.widget, GTK_STATE_NORMAL, &mycolor);
	  }
    }

	ungetlex();

}


