// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyAksi_Tutup_Program ()
{
  int  n=0, i=0, j=0;

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, valdat2, tmpdat, tmpdat2;
  
  int    idx=0;                           // array index

  int    isArrDummy=0;

  int    size = 0;
  char   get_name[MAX_STRING_LEN];

  GtkWidget *widget; 

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];


  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&get_name, '\0', sizeof(get_name));
  
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));


	  getlex();

	  switch( lex.type )
	    {
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              //printf("curr class : %s\n", currentClass);
              //printf("datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

			  if(valdat.widget == NULL) {
                exit(0);
			  }

			  widget = (GtkWidget *)malloc(sizeof(widget));
			  widget = valdat.widget;

			  if(valdat.datatype == 40) {
				  if(valdat.GUItype == 0) {        // window widget
				    g_signal_connect_swapped(G_OBJECT(widget), "destroy",
					  G_CALLBACK(win_destroy), G_OBJECT(widget));
				  } else if(valdat.GUItype == 10){ // Menu Item
				    g_signal_connect(G_OBJECT(widget), "activate",
					  G_CALLBACK(win_destroy), NULL);
				  } else if(valdat.GUItype == 3){ // Tombol
				    g_signal_connect(G_OBJECT(valdat.widget), "clicked",
					  G_CALLBACK(win_destroy), NULL);
				  }

			  } else {
                Error("parameter pada kode perintah Aksi_Tutup_Program salah");
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
                     sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_idx);
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
                  sprintf(class_tmpvar, "%s->%s", currentClass, valdat.array_name);
                  valdat2 = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
				} else {
                  valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
				}
                // ltoa(idx, valdat2.array_idx, 10);
				sprintf(valdat2.array_idx, "%d", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

				// printf("get valdat2 type: %d, val %d\n", valdat2.datatype, valdat2.val);

                if(valdat2.datatype == 60) {  // Array GUI 
                  memset(&tmpdat, '\0', sizeof(tmpdat));
                  tmpdat.widget   = get_gui_array(valdat2, idx);
				  tmpdat.eventbox = get_eventbox_array(valdat2, idx);
				  tmpdat.GUItype  = get_guitype_array(valdat2, idx);
                  tmpdat.datatype = 40;

				  // printf("aksi tutup program : get GUI array , type %d\n", tmpdat.GUItype);

			      widget = (GtkWidget *)malloc(sizeof(widget));
			      widget = tmpdat.widget;

				  if(tmpdat.GUItype == 0) {        // window widget
				    g_signal_connect_swapped(G_OBJECT(widget), "destroy",
					  G_CALLBACK(win_destroy), G_OBJECT(widget));
				  } else if(tmpdat.GUItype == 10){ // Menu Item
				    g_signal_connect(G_OBJECT(widget), "activate",
					  G_CALLBACK(win_destroy), NULL);
				  } else if(tmpdat.GUItype == 3){ // Tombol
				    g_signal_connect(G_OBJECT(tmpdat.widget), "clicked",
					  G_CALLBACK(win_destroy), NULL);
				  }

                } else {
                  Error("salah jenis untaian");
                }
                
              }

	      break;


	    default:
	      Error("kode perintah Aksi_Tutup_Program salah");
	    }
	  getlex();

	ungetlex();

}


