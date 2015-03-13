// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinDataBarisTabel  ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int    n=0, i=0, j=0;
  int    idx=0;
  double k=0.0;
  int    col_num=0;
  int    line_num=0;

  char      class_tmpvar[MAX_STRING_LEN];
  char      **type;
  char      tmpstr[MAX_STRING_LEN];
  char      tmpstr2[MAX_STRING_LEN];

  GtkTreeIter       iter;
  GError            *error = NULL;

  char              *allstr;

  GtkTreeSelection  *selection;
  GtkTreeModel      *model;
  gboolean          success;

  gchar             *myval;
  GdkPixbuf         *pix[20];

  GtkWidget         *treeview;
  GtkListStore      *store;
  
  treeview  = NULL;
  store     = NULL;
  selection = NULL;
  model     = NULL;
  type      = NULL;
  myval     = NULL;
  allstr    = NULL;

  for(i=0; i<20; i++) {
    pix[i] = NULL;
  }
 
  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&tmpstr, '\0', sizeof(tmpstr));
  memset(&tmpstr2, '\0', sizeof(tmpstr2));

  // printf("HapusSelTabel\n");

           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_IDENT) {
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
             if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat    = valdat;
                  tmpdat.datatype = 40;

				  treeview  = valdat.widget;

 		          i = 0;
		          type = split(tmpdat.tblcoltype, "|");
                  while(type[i] != NULL && strlen(type[i]) > 0) {
				    // printf("type %d %s\n", i, type[i]);
				    pix[i] = NULL;
                    i++;
                  }
				  col_num = i;

				  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
				  model     = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

				  if(selection) {
				    // model = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
                    success = gtk_tree_selection_get_selected(selection, NULL, &iter);

					// get data
					allstr = (char *)malloc(sizeof(char *));
					allstr = hhstring_add("" , ""); 
					for(i = 0; i<col_num; i++) {
					  myval = NULL;
				      memset(&tmpstr, '\0', sizeof(tmpstr));
					  strcpy(tmpstr, type[i]);
					  if(!strcmp(tmpstr, "gambar") || !strcmp(tmpstr,"GAMBAR")) {

				        gtk_tree_model_get(model, &iter, i, &pix[i], -1);
						allstr = hhstring_add(allstr , "<GAMBAR>,"); 

                        // memset(&tmpstr2, '\0', sizeof(tmpstr2));
						// sprintf(tmpstr2, "pic%d.png",i);
                        // gdk_pixbuf_save (pix[i], tmpstr2, "png", &error, NULL);

					  } else {
				        gtk_tree_model_get(model, &iter, i, &myval, -1);
				        memset(&tmpstr2, '\0', sizeof(tmpstr2));
						strcpy(tmpstr2, myval);
						allstr = hhstring_add(allstr , tmpstr2); 
						allstr = hhstring_add(allstr , ","); 
					  }
					}
					//printf("all:%s\n", allstr);

					// save string data
					datx.str2  = NULL;
					datx.str2 = allstr;

					// save pixbuf data
					for(i=0;i<20;i++)
					  datx.pixbuf[i] = pix[i];
					// save original col type
					strcpy(datx.tblcoltype , tmpdat.tblcoltype);

					datx.isGUI = 1;
				  }

				  if(type != NULL)
				    split_free(type);

                } 
             } else {
				 Error("Salah: Baris_Terpilih salah masukan");
			 }

           } else {
             Error("Salah: Baris_Terpilih salah masukan");
           }



  // memset(&tmpstr2, '\0', sizeof(tmpstr2));
  // sprintf(tmpstr2, "datx2.png");
  // gdk_pixbuf_save (datx.pixbuf[2], tmpstr2, "png", &error, NULL);

  datx.datatype = 45; // Data Baris Tabel - see defValLabel

  return datx;

}


