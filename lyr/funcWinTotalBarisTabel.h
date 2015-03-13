// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinTotalBarisTabel ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int    n=0, i=0, j=0;
  int    idx=0;

  int    line_num=0;

  char      class_tmpvar[MAX_STRING_LEN];
  char      tmpstr[MAX_STRING_LEN];

  GtkTreeIter       iter;

  GtkTreeModel      *model;
  gboolean          success;

  GtkWidget         *treeview;
  GtkListStore      *store;
  
  treeview  = NULL;
  store     = NULL;
  model     = NULL;
 
  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&tmpstr, '\0', sizeof(tmpstr));

  //printf("WinTotalBarisTabel\n");

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
               valdat = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
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

				  model   = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
                  success = gtk_tree_model_get_iter_first(model, &iter);
                  j = 0;
                  while(success) {
					success = gtk_tree_model_iter_next(model, &iter);
					j++;
                  }
                  line_num = j;
                  // printf("line tot: %d\n", line_num);

                } 
             } else {
				 Error("Salah: Total_Baris_Tabel salah masukan");
			 }

           } else {
             Error("Salah: Total_Baris_Tabel salah masukan");
           }

  datx.val = line_num;
  datx.datatype = 0;

  return datx;
}


