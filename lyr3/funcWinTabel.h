// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinTabel ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int  n=0, i=0;
  int  idx=0;

  char    **each;

  char    tmpstr[MAX_STRING_LEN];
  char    myrender[MAX_STRING_LEN];
  char    class_tmpvar[MAX_STRING_LEN];

  GtkWidget         *treeview;
  GtkListStore      *liststore;
  GtkCellRenderer   *renderer;

  int N_COLUMN    = 0;
  int COL_MAX     = 20;

  int COL_TYPE[20]; // MAX 20

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpstr, '\0', sizeof(tmpstr));
  memset(&myrender, '\0', sizeof(myrender));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  each      = NULL;
  treeview  = NULL;
  liststore = NULL;
  renderer  = NULL;

  for(i=0; i<20; i++) {
    COL_TYPE[i] = 0;
  }

        n = 0; i = 0;
        getlex();

           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_STR) {
			 if(n ==0) {
               strcpy(myrender, lex.detail.string);
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

                 // itoa(idx, valdat.array_idx, 10);
                 sprintf(valdat.array_idx, "%d", idx);

                 if(idx < 0 || idx > MAX_ARRAY)
                   Error("ukuran Untaian tidak sesuai kapasitas");
                 
				 if(valdat.datatype == 8 && valdat.array_s != '\0') {
                   if(valdat.array_s == '\0')
                     Error("tulis_soket: ukuran Untaian belum terdefinisi");

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
				   if(n == 0) {
					 strcpy(myrender, TmpStrBox.str.mystring);
				   }

                 } // end if(valdat.datatype == 8)

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
               valdat = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 3) {
			   if( n == 0) {
		         strcpy(myrender, valdat.str);
		       }
             } else {
				 Error("Salah: Tabel salah masukan");
			 }

           }

           n++;


	each = split(myrender, "|");
	i=0;
    while(each[i] != NULL && strlen(each[i]) > 0) {
	  COL_TYPE[i] = 0; // init
      i++;
    }

	if(i > COL_MAX) {
      Error("Tabel Salah: jumlah kolom terlalu banyak");
	}

	i=0;
    while(each[i] != NULL && strlen(each[i]) > 0) {
	  memset(&tmpstr, '\0', sizeof(tmpstr));
      strcpy(tmpstr, each[i]);
      // printf("each %d %s\n", i, tmpstr);

      if( !strcmp(tmpstr, "TEKS") || !strcmp(tmpstr, "teks") ) {
        COL_TYPE[i] = G_TYPE_STRING;
	  } 
	  else
      if( !strcmp(tmpstr, "ANGKA") || !strcmp(tmpstr, "angka") ) {
        // COL_TYPE[i] = G_TYPE_UINT;
        COL_TYPE[i] = G_TYPE_STRING;
	  } 
	  else
      if( !strcmp(tmpstr, "GAMBAR") || !strcmp(tmpstr, "gambar") ) {
        COL_TYPE[i] = GDK_TYPE_PIXBUF;
	  } 
	  i++;
    } // end while

    split_free(each);

  N_COLUMN = i;

  if(N_COLUMN == 1)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0]);
  } else if(N_COLUMN == 2)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1]);
  } else if(N_COLUMN == 3)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2]);
  } else if(N_COLUMN == 4)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2],COL_TYPE[3]); 
  } else if(N_COLUMN == 5)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4]);
  } else if(N_COLUMN == 6)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5]);
  } else if(N_COLUMN == 7)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6]);
  } else if(N_COLUMN == 8)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7]);
  } else if(N_COLUMN == 9)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8]);
  } else if(N_COLUMN == 10)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9]);
  } else if(N_COLUMN == 11)  {
    liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9],
                COL_TYPE[10]);
  } else if(N_COLUMN == 12)  {
   liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9],
                COL_TYPE[10], COL_TYPE[11]);
  } else if(N_COLUMN == 13)  {
   liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9],
                COL_TYPE[10], COL_TYPE[11], COL_TYPE[12]);
  } else if(N_COLUMN == 14)  {
   liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9],
                COL_TYPE[10], COL_TYPE[11], COL_TYPE[12], COL_TYPE[13]);
  } else if(N_COLUMN == 15)  {
   liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9],
                COL_TYPE[10], COL_TYPE[11], COL_TYPE[12], COL_TYPE[13],
                COL_TYPE[14]);
  } else if(N_COLUMN == 16)  {
   liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9],
                COL_TYPE[10], COL_TYPE[11], COL_TYPE[12], COL_TYPE[13],
                COL_TYPE[14], COL_TYPE[15]);
  } else if(N_COLUMN == 17)  {
   liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9],
                COL_TYPE[10], COL_TYPE[11], COL_TYPE[12], COL_TYPE[13],
                COL_TYPE[14], COL_TYPE[15], COL_TYPE[16]);
  } else if(N_COLUMN == 18)  {
   liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9],
                COL_TYPE[10], COL_TYPE[11], COL_TYPE[12], COL_TYPE[13],
                COL_TYPE[14], COL_TYPE[15], COL_TYPE[16], COL_TYPE[17]);
  } else if(N_COLUMN == 19)  {
   liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9],
                COL_TYPE[10], COL_TYPE[11], COL_TYPE[12], COL_TYPE[13],
                COL_TYPE[14], COL_TYPE[15], COL_TYPE[16], COL_TYPE[17],
                COL_TYPE[18]);
  } else if(N_COLUMN == 20)  {
   liststore = gtk_list_store_new(N_COLUMN, COL_TYPE[0],	COL_TYPE[1],
                COL_TYPE[2], COL_TYPE[3], COL_TYPE[4], COL_TYPE[5],
                COL_TYPE[6], COL_TYPE[7], COL_TYPE[8], COL_TYPE[9],
                COL_TYPE[10], COL_TYPE[11], COL_TYPE[12], COL_TYPE[13],
                COL_TYPE[14], COL_TYPE[15], COL_TYPE[16], COL_TYPE[17],
                COL_TYPE[18], COL_TYPE[19]);
  } else {
    Error("Salah Tabel : ukuran tabel tidak sesuai");
  }

  //printf("Tabel tblcoltype : %s\n", myrender);

	  treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(liststore));

	  datx.widget    = treeview;
	  datx.liststore = liststore;
	  datx.isGUI    = 1;
	  datx.GUItype  = 21;
	  datx.datatype = 40;                // treeview widget
	  datx.val      = N_COLUMN;

	  strcpy(datx.tblcoltype, myrender); // keep model
	  
	  g_object_unref(liststore);


  if(valdat.filename != NULL)
    free(valdat.filename);
  if(valdat.folder != NULL)
    free(valdat.folder);
  if(valdat.filedata != NULL)
    free(valdat.filedata);
  if(valdat.long_str != NULL)
    free(valdat.long_str);

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  if(tmpdat.filename != NULL)
    free(tmpdat.filename);
  if(tmpdat.folder != NULL)
    free(tmpdat.folder);
  if(tmpdat.filedata != NULL)
    free(tmpdat.filedata);
  if(tmpdat.long_str != NULL)
    free(tmpdat.long_str);

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);


  return datx;
}


