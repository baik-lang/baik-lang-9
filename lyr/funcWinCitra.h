// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

//GTK IMAGE = CITRA
VAL_LABEL funcWinCitra ()
{
  VAL_LABEL datx;

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0;                           // array index

  char   get_name[MAX_STRING_LEN];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&get_name, '\0', sizeof(get_name));
  
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

         /* get referenced string */
         getlex();

         /* printf("lex type : %d\n", lex.type);  */

         if(lex.type == TYPE_STR) {
           strcpy(tmpMsg, lex.detail.string );
         } else if(lex.type == TYPE_ARRAY) {
            /* printf("akar array\n"); */

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
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #else
               snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #endif
              #else
              snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
              #endif

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
					  sprintf(tmpMsg,"%s", TmpStrBox.str.mystring);
					}

				  }

              } else {
                Error("CITRA: masukan data salah");
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
           if(datx.datatype == 3) {
             strcpy(tmpMsg, datx.str);
           } else {
             Error("CITRA: masukan data salah");
           }
         }

  datx.widget   = gtk_image_new_from_file(tmpMsg);

  datx.isGUI    = 1;
  datx.GUItype  = 22;   // Citra - GtkImage from file - see ValLabel
  datx.datatype = 40;   // widget

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

  #ifdef USE_GTK2
  if(valdat.widget != NULL)
    free(valdat.widget);
  if(valdat.eventbox != NULL)
    free(valdat.eventbox);
  if(valdat.font_desc != NULL)
    free(valdat.font_desc);
  if(valdat.liststore != NULL)
    free(valdat.liststore);
  if(valdat.completion != NULL)
    free(valdat.completion);
  if(valdat.buffer != NULL)
    free(valdat.buffer);
  if(valdat.treestore != NULL)
    free(valdat.treestore);
  if(valdat.treecolumn != NULL)
    free(valdat.treecolumn);
  if(valdat.clipboard != NULL)
    free(valdat.clipboard);
  if(valdat.renderer != NULL)
    free(valdat.renderer);
  if(valdat.cr_surface != NULL)
    free(valdat.cr_surface);
  if(valdat.cr_img != NULL)
    free(valdat.cr_img);
  if(valdat.cr_pattern != NULL)
    free(valdat.cr_pattern);
  if(valdat.pixmap != NULL)
    free(valdat.pixmap);
  if(valdat.gtk_print_set != NULL)
    free(valdat.gtk_print_set);
  if(valdat.gtk_print_ope != NULL)
    free(valdat.gtk_print_ope);
  if(valdat.pango_layout != NULL)
    free(valdat.pango_layout);
  if(valdat.str2 != NULL)
    free(valdat.str2);

  if(tmpdat.widget != NULL)
    free(tmpdat.widget);
  if(tmpdat.eventbox != NULL)
    free(tmpdat.eventbox);
  if(tmpdat.font_desc != NULL)
    free(tmpdat.font_desc);
  if(tmpdat.liststore != NULL)
    free(tmpdat.liststore);
  if(tmpdat.completion != NULL)
    free(tmpdat.completion);
  if(tmpdat.buffer != NULL)
    free(tmpdat.buffer);
  if(tmpdat.treestore != NULL)
    free(tmpdat.treestore);
  if(tmpdat.treecolumn != NULL)
    free(tmpdat.treecolumn);
  if(tmpdat.clipboard != NULL)
    free(tmpdat.clipboard);
  if(tmpdat.renderer != NULL)
    free(tmpdat.renderer);
  if(tmpdat.cr_surface != NULL)
    free(tmpdat.cr_surface);
  if(tmpdat.cr_img != NULL)
    free(tmpdat.cr_img);
  if(tmpdat.cr_pattern != NULL)
    free(tmpdat.cr_pattern);
  if(tmpdat.pixmap != NULL)
    free(tmpdat.pixmap);
  if(tmpdat.gtk_print_set != NULL)
    free(tmpdat.gtk_print_set);
  if(tmpdat.gtk_print_ope != NULL)
    free(tmpdat.gtk_print_ope);
  if(tmpdat.pango_layout != NULL)
    free(tmpdat.pango_layout);
  if(tmpdat.str2 != NULL)
    free(tmpdat.str2);
  #endif


  return datx;
}
