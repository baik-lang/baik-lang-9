// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyWinHapusSelTabel ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int  n=0, i=0, j=0;
  int  idx=0;
  double k=0.0;

  char    class_tmpvar[MAX_STRING_LEN];

  char    tmpstr[MAX_STRING_LEN];

  GtkTreeIter       iter;
  GtkTreeSelection  *selection=NULL;
  gboolean          success;

  GtkWidget         *treeview;
  GtkListStore      *store;
  
  treeview  = NULL;
  store = NULL;
 
  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&tmpstr, '\0', sizeof(tmpstr));

  //printf("HapusSelTabel\n");

           getlex();
		   //printf("type %d %s\n",lex.type, lex.detail.string);

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
               valdat = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.string, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

	     //printf("get ident type type %d with n %d\n", valdat.datatype, n);

             if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat    = valdat;
                  tmpdat.datatype = 40;

				  treeview  = valdat.widget;

				  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
				  if(selection) {
				    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
                    success = gtk_tree_selection_get_selected(selection, NULL, &iter);
				    if(success) gtk_list_store_remove(store, &iter);
				  }

                } 
             } else {
				 Error("Salah: Hapus_Sel_Tabel salah masukan");
			 }

           } else {
             Error("Salah: Hapus_Sel_Tabel salah masukan");
           }


}

