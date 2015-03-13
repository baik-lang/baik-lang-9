// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyWinTabelData ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int  n=0, i=0, j=0;
  int  idx=0;
  double k=0.0;

  char    class_tmpvar[MAX_STRING_LEN];

  char    *allstr=NULL;

  char    **each=NULL;
  char    **type=NULL;

  int       val[20];
  GdkPixbuf *pix[20];
  char    tmpstr[MAX_STRING_LEN];

  GtkTreeIter       iter;

  GtkWidget         *treeview=NULL;
  GtkListStore      *store=NULL;
  
  int COLUMN_NAME = 0;
  int col_num = 0;



  allstr  = NULL;
  each    = NULL;

  treeview  = NULL;
  store = NULL;
 
  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&tmpstr, '\0', sizeof(tmpstr));

  // printf("Tabel Data start...\n");

        n = 0; i = 0;
        do {
           getlex();
		   // printf("getlex %d type %d %s\n",n, lex.type, lex.detail.string);

           if(lex.type == TYPE_NUM) {
		     memset(&tmpstr, '\0', sizeof(tmpstr));
			 sprintf(tmpstr,"%li", lex.detail.num);
			 if(n > 0) {
			   COLUMN_NAME++;
			   if(n == 1) {
                 allstr = hhstring_add(tmpstr , "|"); 
			   } else {
                 allstr = hhstring_add(allstr , tmpstr); 
                 allstr = hhstring_add(allstr , "|"); 
			   }
			 }
           }
		   else
           if(lex.type == TYPE_DBL) {
		     memset(&tmpstr, '\0', sizeof(tmpstr));
			 sprintf(tmpstr,"%f", lex.detail.dblnum);
			 if(n > 0) {
			   COLUMN_NAME++;
			   if(n == 1) {
                 allstr = hhstring_add(tmpstr , "|"); 
			   } else {
                 allstr = hhstring_add(allstr , tmpstr); 
                 allstr = hhstring_add(allstr , "|"); 
			   }
			 }
           }
		   else
           if(lex.type == TYPE_STR) {
			 if(n > 0) {
			   COLUMN_NAME++;
			   if(n == 1) {
                 allstr = hhstring_add(lex.detail.string , "|"); 
			   } else {
                 allstr = hhstring_add(allstr , lex.detail.string); 
                 allstr = hhstring_add(allstr , "|"); 
			   }
			 }
           } else if(lex.type == TYPE_ARRAY) {
			   // printf("get array %s\n", lex.detail.string);

               if(strlen(lex.detail.array_str) > 0) {
                 strcpy(valdat.array_str, lex.detail.array_str);
                 getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                 getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                 if(currentClass != NULL && strlen(currentClass) > 0) {
                   sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_name);
                   //printf("construct class var: %s\n", class_tmpvar);
                   memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));
                   strcpy(valdat.array_name, class_tmpvar);

                   if(!isdigit(valdat.array_idx[0])) {
                     memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                     sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_idx);
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

                 if(valdat.datatype == 6 && valdat.array_i != '\0') { // int
				   // printf("get array int\n");
		           memset(&tmpstr, '\0', sizeof(tmpstr));
				   j = get_int_array(valdat, idx);
				   sprintf(tmpstr,"%d", j);
				   // printf("get string int %s\n", tmpstr);

				   if(n == 1) {
                     allstr = hhstring_add(tmpstr , "|"); 
			       } else {
                     allstr = hhstring_add(allstr , tmpstr); 
                     allstr = hhstring_add(allstr , "|"); 
			       }
				   // printf("get array int OK\n");
				 } else
                 if(valdat.datatype == 7 && valdat.array_d != '\0') { // dbl
				   // printf("get array int\n");
		           memset(&tmpstr, '\0', sizeof(tmpstr));
				   k = get_dbl_array(valdat, idx);
				   sprintf(tmpstr,"%f", k);
				   // printf("get string int %s\n", tmpstr);

				   if(n == 1) {
                     allstr = hhstring_add(tmpstr , "|"); 
			       } else {
                     allstr = hhstring_add(allstr , tmpstr); 
                     allstr = hhstring_add(allstr , "|"); 
			       }
				   // printf("get array int OK\n");
				 } else
                 if(valdat.datatype == 8 && valdat.array_s != '\0') { // str
                   if(valdat.array_s == '\0')
                     Error("tabel_data: ukuran Untaian belum terdefinisi");

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
					 COLUMN_NAME++;
			         if(n == 1) {
                       allstr = hhstring_add(TmpStrBox.str.mystring , "|"); 
			         } else {
                       allstr = hhstring_add(allstr , TmpStrBox.str.mystring); 
                       allstr = hhstring_add(allstr , "|"); 
			         }
				   }

                 } // end if(valdat.datatype == 8)

               }

           } else if(lex.type == TYPE_IDENT) {
		     // printf("get type IDENT \n");

             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               //printf("construct class var: %s\n", class_tmpvar);
               valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

			 // printf("get type type %d with n %d\n", valdat.datatype, n);
             // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 0) { // int
		       memset(&tmpstr, '\0', sizeof(tmpstr));
			   sprintf(tmpstr,"%li", valdat.val);
			   if( n > 0) {
			   	 COLUMN_NAME++;

				 if(n == 1) {
                   allstr = hhstring_add(tmpstr , "|"); 
			     } else {
                   allstr = hhstring_add(allstr , tmpstr); 
                   allstr = hhstring_add(allstr , "|"); 
			     }
		       }
			 } else
             if(valdat.datatype == 1) { // dbl
		       memset(&tmpstr, '\0', sizeof(tmpstr));
			   sprintf(tmpstr,"%f", valdat.floatdata);
			   if( n > 0) {
			   	 COLUMN_NAME++;

				 if(n == 1) {
                   allstr = hhstring_add(tmpstr , "|"); 
			     } else {
                   allstr = hhstring_add(allstr , tmpstr); 
                   allstr = hhstring_add(allstr , "|"); 
			     }
		       }
			 } else
             if(valdat.datatype == 3) { // str
			   if( n > 0) {
			   	 COLUMN_NAME++;

				 if(n == 1) {
                   allstr = hhstring_add(valdat.str , "|"); 
			     } else {
                   allstr = hhstring_add(allstr , valdat.str); 
                   allstr = hhstring_add(allstr , "|"); 
			     }
		       }
			 } else if(valdat.datatype == 40) {
                if(n == 0) {
				  //printf("get widget tblcoltype: %s\n",valdat.tblcoltype);
				  tmpdat    = valdat;
                  tmpdat.datatype = 40;

				  treeview  = valdat.widget;
		          store = valdat.liststore;
                } 
             } else {
				 Error("Salah: Tabel_Data salah masukan");
			 }

           } else {
             Error("Salah: Tabel_Data salah masukan");
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

		// printf("after looping\n");
		// printf("after looping, allstr: %s\n",allstr);
		// printf("after looping, tblcoltype: %s\n",tmpdat.tblcoltype);


		i = 0;
		type = split(tmpdat.tblcoltype, "|");

        while(type[i] != NULL && strlen(type[i]) > 0) {
		 // printf("type %d %s\n", i, type[i]);
		 val[i] = 0;    // int init
		 pix[i] = NULL; // pic init

         i++;
        }

		// printf("allstr : %s\n", allstr);
		each = split(allstr, "|");
		i=0;
        while(each[i] != NULL && strlen(each[i]) > 0) {
		 // printf("dat %d %s\n", i, each[i]);
         strcpy(tmpstr, type[i]);
		 if(!strcmp(tmpstr, "angka") || !strcmp(tmpstr, "ANGKA")) {
           val[i] = atoi(each[i]);
		 } else if(!strcmp(tmpstr, "gambar") || !strcmp(tmpstr, "GAMBAR")) {
		   pix[i] = win_create_pixbuf(each[i]);
		 }

         i++;
        }
		// printf("all i : %d, column %d\n", i, COLUMN_NAME);

		store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
		gtk_list_store_append(store, &iter);

          memset(&tmpstr, '\0', sizeof(tmpstr));

		if(i >= 1 && i <= 20) {
          // data per line
		  for(j = 0; j < i; j++) {
             // data per col num
             col_num = j;
		     // printf("type %d %s\n", col_num, type[col_num]);
             memset(&tmpstr, '\0', sizeof(tmpstr));
             strcpy(tmpstr, type[col_num]);
             if(!strcmp(tmpstr, "ANGKA") || !strcmp(tmpstr, "angka")) {
               // gtk_list_store_set(store, &iter, col_num, val[col_num], -1);
               gtk_list_store_set(store, &iter, col_num, each[col_num], -1);
             }
             else
             if(!strcmp(tmpstr, "TEKS") || !strcmp(tmpstr, "teks")) {
               gtk_list_store_set(store, &iter, col_num, each[col_num], -1);
             }
			 else
             if(!strcmp(tmpstr, "GAMBAR") || !strcmp(tmpstr, "gambar")) {
               gtk_list_store_set(store, &iter, col_num, pix[col_num], -1);
             }
          } // end for(j = 0; j < i)

		} else {
		  Error("Salah Tabel_Data : ukuran tabel tidak sesuai");
		}

		// printf("Tabel Data finishing ...\n");
		split_free(each);
		split_free(type);

}

