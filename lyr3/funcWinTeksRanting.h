// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2012
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinTeksRanting ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int    n=0;

  char      class_tmpvar[MAX_STRING_LEN];
  char      tmpstr[MAX_STRING_LEN];
  gchar     *name=NULL;

  GtkTreeIter       iter;

  GtkTreeSelection  *selection;
  GtkTreeModel      *model;
  gboolean          success;

  GtkWidget         *treeview;
  GtkListStore      *store;
  
  treeview  = NULL;
  store     = NULL;
  selection = NULL;
  model     = NULL;
 
  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&tmpstr, '\0', sizeof(tmpstr));

  // printf("TeksRanting\n");

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

             if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat    = valdat;
                  tmpdat.datatype = 40;

				  treeview  = valdat.widget;

				  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
				  model     = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

				  if(selection) {
				    // model = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
                    success = gtk_tree_selection_get_selected(selection, NULL, &iter);

					gtk_tree_model_get (model, &iter, 1, &name, -1);
                    strcpy(datx.str, name);
					// printf ("selected : %s\n", name);
				  } else {
                    // not selected
					// printf ("not selected \n");
                    strcpy(datx.str, "");
				  }

                } 
             } else {
				 Error("Salah: Teks_Ranting salah masukan");
			 }

           } else {
             Error("Salah: Teks_Ranting salah masukan");
           }


  datx.datatype = 3; // as string

  return datx;

}


