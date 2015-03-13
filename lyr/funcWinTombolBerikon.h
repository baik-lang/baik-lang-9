// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// UTF-8

VAL_LABEL funcWinTombolBerikon ()
{
  VAL_LABEL datx;

  char   tmpMsg[MAX_STRING_LEN * 2];
  char   tmpMsg2[MAX_STRING_LEN];
  GtkWidget *parent=NULL;
  GtkWidget *button=NULL;
  GtkWidget *labelbox=NULL;

  VAL_LABEL valdat, tmpdat;
  
  int    idx=0;                           // array index
  int    n = 0;

  char   get_name[MAX_STRING_LEN];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&get_name, '\0', sizeof(get_name));
  
  memset(&tmpMsg, '\0', sizeof(tmpMsg));
  memset(&tmpMsg2, '\0', sizeof(tmpMsg2));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


  do {
         /* get referenced string */
         getlex();

         /* printf("lex type : %d\n", lex.type);  */

         if(lex.type == TYPE_STR) {
		   if(n == 1) 
             strcpy(tmpMsg, lex.detail.string );
		   else if(n == 2) 
             strcpy(tmpMsg2, lex.detail.string );

         } else if(lex.type == TYPE_NUM) {
           #ifdef WIN32
            #ifndef S_SPLINT_S
		    if(n == 1) 
              sprintf_s(tmpMsg, sizeof(tmpMsg),"%li", lex.detail.num);
		    else if(n == 2) 
              sprintf_s(tmpMsg2, sizeof(tmpMsg2),"%li", lex.detail.num);
            #else
            snprintf(tmpMsg, sizeof(tmpMsg),"%li", lex.detail.num);
            #endif
           #else
		   if(n == 1) 
             snprintf(tmpMsg, sizeof(tmpMsg),"%li", lex.detail.num);
		    else if(n == 2) 
             snprintf(tmpMsg, sizeof(tmpMsg2),"%li", lex.detail.num);
           #endif
         } else if(lex.type == TYPE_ARRAY) {
            /* printf("akar array\n"); */

            if(strlen(lex.detail.array_str) > 0) {
              strcpy(valdat.array_str, lex.detail.array_str);
              getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
              getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_name);
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                #endif

                //printf("construct class var: %s\n", class_tmpvar);
                memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));
                strcpy(valdat.array_name, class_tmpvar);

                if(!isdigit(valdat.array_idx[0])) {
                  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                   #else
                   snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                   #endif
                  #else
                  snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                  #endif

                  //printf("construct class var: %s\n", class_tmpvar);
                  memset(&valdat.array_idx[0], '\0', sizeof(valdat.array_idx));
                  strcpy(valdat.array_idx, class_tmpvar);
                }

              }

              // printf("akar ARRAY name: %s\n", valdat.array_name);

              if(isdigit(valdat.array_idx[0])) {
                /* printf("show digit\n"); */
                idx = atoi (valdat.array_idx);
              } else {
                /* printf("show NOT digit\n"); */
                /* Read index param */
                tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                if(tmpdat.datatype==0)
                  idx = tmpdat.val;
                else
                   Error("Untaian salah masukan");
              }

              /* read data */
              valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              // itoa(idx, valdat.array_idx, 10);
              sprintf(valdat.array_idx, "%d", idx);

              /* printf("akar type %d\n", valdat.datatype); */

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 8) {

		  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
		  memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

		  strcpy(TmpStrBox.var.array_name, valdat.array_name);
                  renban = valdat.array_s;

				  // printf("TULIS get stackid: %d, idx: %d\n", renban, idx);

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
					  strcpy(tmpMsg, TmpStrBox.str.mystring);
					}

				  }

              } else {
                Error("LABEL_BERIKON: masukan data salah");
              }
           }

         } else {

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
             datx = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );

           if(datx.datatype == 40) { // GUI widget
		     if(n == 0) 
               parent = datx.widget;
		   } else if(datx.datatype == 3) {
		     if(n == 1) 
		       strcpy(tmpMsg, datx.str);
		     else if(n == 2) 
		       strcpy(tmpMsg2, datx.str);
	       } else if(datx.datatype == 0) {
               #ifdef WIN32
                 #ifndef S_SPLINT_S
		         if(n == 1) 
                   sprintf_s(tmpMsg, sizeof(tmpMsg),"%li", datx.val);
		         else if(n == 2) 
                   sprintf_s(tmpMsg2, sizeof(tmpMsg2),"%li", datx.val);
                 #else
                 snprintf(tmpMsg, sizeof(tmpMsg),"%li", datx.val);
                 #endif
               #else
		       if(n == 1) 
                 snprintf(tmpMsg, sizeof(tmpMsg),"%li", datx.val);
		       if(n == 2) 
                 snprintf(tmpMsg2, sizeof(tmpMsg2),"%li", datx.val);
               #endif

           } else {
             Error("LABEL_BERIKON: masukan data salah");
           }
         }

        n++;

	    getlex(); // pass comma

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

    ungetlex();

	if(n == 3) {
		 memset(&datx, '\0', sizeof(datx));

		 // make new label berikon
         button = gtk_button_new ();
		 labelbox = png_label_box(parent, tmpMsg2, g_locale_to_utf8(tmpMsg, -1,NULL,NULL,NULL) );
         gtk_container_add (GTK_CONTAINER (button), labelbox);

		 datx.widget   = button;
		 datx.isGUI    = 1;
		 datx.GUItype  = 3;    // Tombol - button - see ValLabel
		 datx.datatype = 40;   // widget

	} else {
      Error("parameter Label_Berikon tidak lengkap");
	}

	return datx;
}
