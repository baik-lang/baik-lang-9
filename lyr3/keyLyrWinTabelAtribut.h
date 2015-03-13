// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyWinTabelAtribut ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int  n=0, i=0, j=0;
  int  idx=0;

  char    class_tmpvar[MAX_STRING_LEN];
  char    tmpstr[MAX_STRING_LEN];
  char    **type;

  GtkWidget         *treeview;
  GtkListStore      *liststore;
  GtkCellRenderer   *renderer[20];
  GtkTreeViewColumn *column;

  int COLUMN_NO = 0;

  treeview  = NULL;
  liststore = NULL;
  column    = NULL;
  type      = NULL;

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
  memset(&tmpstr, '\0', sizeof(tmpstr));


        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_STR) {
			 if(n > 0) {
			   memset(&tmpstr, '\0', sizeof(tmpstr));
               strcpy(tmpstr, type[n -1]);
		       // printf("add atribut type %d %s\n", (n - 1), tmpstr);

               if(!strcmp(tmpstr, "GAMBAR") || !strcmp(tmpstr, "gambar")) {
  			     // printf("get str %d %s\n", COLUMN_NO, lex.detail.string);
			     column = gtk_tree_view_column_new_with_attributes(
				   lex.detail.string,
				   renderer[n - 1],
				   "pixbuf",
				   COLUMN_NO,
				   NULL);
			   } else {
  			     // printf("get str %d %s\n", COLUMN_NO, lex.detail.string);
			     column = gtk_tree_view_column_new_with_attributes(
				   lex.detail.string,
				   renderer[n - 1],
				   "text",
				   COLUMN_NO,
				   NULL);
			   }
			   gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
			   COLUMN_NO++;
			 }
           } else if(lex.type == TYPE_ARRAY) {
               if(strlen(lex.detail.array_str) > 0) {
                 strcpy(valdat.array_str, lex.detail.array_str);
                 getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                 getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                 if(currentClass != NULL && strlen(currentClass) > 0) {
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

                 //itoa(idx, valdat.array_idx, 10);
                 #ifdef WIN32
                  #ifndef S_SPLINT_S
                  sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
                  #else
                  snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
                  #endif
                 #else
                 snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
                 #endif

                 if(idx < 0 || idx > MAX_ARRAY)
                   Error("ukuran Untaian tidak sesuai kapasitas");

                 if(valdat.datatype == 8 && valdat.array_s != '\0') {
                   if(valdat.array_s == '\0')
                     Error("tabel_atribut: ukuran Untaian belum terdefinisi");

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
				   if(n > 0) {
			         memset(&tmpstr, '\0', sizeof(tmpstr));
                     strcpy(tmpstr, type[n -1]);
		             // printf("add atribut type %d %s\n", (n - 1), tmpstr);

                     if(!strcmp(tmpstr, "GAMBAR") || !strcmp(tmpstr, "gambar")) {
  			           column = gtk_tree_view_column_new_with_attributes(
				         TmpStrBox.str.mystring,
				         renderer[n - 1],
				         "pixbuf",
				         COLUMN_NO,
				         NULL);
			         } else {
				       column = gtk_tree_view_column_new_with_attributes(
					     TmpStrBox.str.mystring,
					     renderer[n - 1],
					     "text",
					     COLUMN_NO,
					     NULL);
					 }
			         gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
					 COLUMN_NO++;
				   }

                 } // end if(valdat.datatype == 8)

               }

           } else if(lex.type == TYPE_IDENT) {
		     // printf("get type IDENT \n");

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
               valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

             // printf("get type type %d with n %d\n", valdat.datatype, n);
             // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 3) {
			   if( n > 0) {
			     memset(&tmpstr, '\0', sizeof(tmpstr));
                 strcpy(tmpstr, type[n -1]);
		         // printf("add atribut type %d %s\n", (n - 1), tmpstr);

                 if(!strcmp(tmpstr, "GAMBAR") || !strcmp(tmpstr, "gambar")) {
			       column = gtk_tree_view_column_new_with_attributes(
				            valdat.str,
				            renderer[n - 1],
				            "pixbuf",
				            COLUMN_NO,
				            NULL);
			     } else {
			       column = gtk_tree_view_column_new_with_attributes(
				            valdat.str,
					        renderer[n -1],
					        "text",
					        COLUMN_NO,
					        NULL);
				 }
			     gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
			   	 COLUMN_NO++;
		       }
			 } else if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat    = valdat;
                  tmpdat.datatype = 40;

				  treeview  = valdat.widget;
		          liststore = valdat.liststore;

		          i = 0;
		          type = split(tmpdat.tblcoltype, "|");
                  while(type[i] != NULL && strlen(type[i]) > 0) {
					memset(&tmpstr, '\0', sizeof(tmpstr));
                    strcpy(tmpstr, type[i]);
		            // printf("atribut type %d %s\n", i, tmpstr);

					renderer[i] = NULL;
                    if(!strcmp(tmpstr, "ANGKA") || !strcmp(tmpstr, "angka")) {
                      renderer[i] = gtk_cell_renderer_text_new();
                    }
                    else
                    if(!strcmp(tmpstr, "TEKS") || !strcmp(tmpstr, "teks")) {
                      renderer[i] = gtk_cell_renderer_text_new();
                    }
			        else
                    if(!strcmp(tmpstr, "GAMBAR") || !strcmp(tmpstr, "gambar")) {
                      renderer[i] = gtk_cell_renderer_pixbuf_new();
                    }

                    i++;
                  }

                } 
             } else {
				 Error("Salah: Tabel_Atribut salah masukan");
			 }

           } else {
             Error("Salah: Tabel_Atribut salah masukan");
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

}

