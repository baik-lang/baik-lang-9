// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyHiasAlas ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0;
  long idx=0;                           // array index

  int  num_a=0, num_b=0;
  int  num_c=0, num_d=0;

  VAL_LABEL valdat, valdat2, tmpdat, tmpdat2, tmpdat3;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));
  memset(&tmpdat3, '\0', sizeof(tmpdat3));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
   
	    case TYPE_NUM:
              if(n == 2) {
				num_a = lex.detail.num;
			  } else if(n == 3) {
                num_b = lex.detail.num;
			  } else if(n == 4) {
                num_c = lex.detail.num;
			  } else if(n == 5) {
                num_d = lex.detail.num;
			  }
	      break;

	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

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
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat.widget   = valdat.widget;
                  tmpdat.datatype = 40;
				  tmpdat.GUItype  = valdat.GUItype;
				} else if(n == 1) {
				  tmpdat2.widget   = valdat.widget;
				  tmpdat2.eventbox = valdat.eventbox;
                  tmpdat2.datatype = 40;
				  tmpdat2.GUItype  = valdat.GUItype;
				}
			  } else if(valdat.datatype == 0) {
                if(n == 2) {
				  num_a = valdat.val;
			    } else if(n == 3) {
                  num_b = valdat.val;
			    } else if(n == 4) {
                  num_c = valdat.val;
			    } else if(n == 5) {
                  num_d = valdat.val;
			    }
			  } else {
                Error("bentuk perintah Hias_Alas salah");
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

		   memset(&tmpdat3, '\0', sizeof(tmpdat3));
                   if(currentClass != NULL && strlen(currentClass) > 0) {
                     #ifdef WIN32
                      #ifndef S_SPLINT_S
                      sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                      #else
                      snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                      #endif
                     #else
                     snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                     #endif
                     tmpdat3 = ValLabel( class_tmpvar, class_sub_deep, tmpdat3, VAL_FLAG_SEARCH_R );
				   } else {
                     tmpdat3 = ValLabel( valdat.array_idx, sub_deep, tmpdat3, VAL_FLAG_SEARCH_R );
				     // printf("get idx type: %d, val %d\n", tmpdat.datatype, tmpdat.val);
   		           }

                   if(tmpdat3.datatype==0)
                     idx = tmpdat3.val;
                   else
                      Error("Untaian salah masukan");
                }

				// get real value of array
				// printf("search array: %s\n", valdat.array_name);
                if(currentClass != NULL && strlen(currentClass) > 0) {
		  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                   #else
                   snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                   #endif
                  #else
                  snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                  #endif
                  valdat2 = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
		} else {
                  valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
		}
                // ltoa(idx, valdat2.array_idx, 10);
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx);
                 #else
                 snprintf(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx);
                 #endif
                #else
                snprintf(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx);
                #endif

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

				// printf("get valdat2 type: %d, val %d\n", valdat2.datatype, valdat2.val);

                if(valdat2.datatype == 60 && n == 1) {  // Array GUI 
			      memset(&tmpdat2, '\0', sizeof(tmpdat2));
                  tmpdat2.widget   = get_gui_array(valdat2, idx);
				  tmpdat2.eventbox = get_eventbox_array(valdat2, idx);
				  tmpdat2.GUItype  = get_guitype_array(valdat2, idx);
                  tmpdat2.datatype = 40;
				  // printf("hias alas n1 : get GUI array\n");
                } else {
                  Error("salah jenis untaian");
                }
                
              }

	      break;

	    default:
	      Error("bentuk perintah Hias_Alas salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 6) {
      Error("parameter Hias_Alas tidak lengkap");
    } else {
      // tmpdat : base (window / frame)
      // tmpdat2: other widgets

	  if(tmpdat.GUItype == 1) { // fixed frame container

		if(tmpdat2.GUItype == 4 || tmpdat2.GUItype == 6) { // label or combo-text
          gtk_fixed_put(GTK_FIXED(tmpdat.widget), tmpdat2.eventbox, num_a, num_b); // base
	      gtk_widget_set_size_request(tmpdat2.eventbox, num_c, num_d);

		  gtk_container_add(GTK_CONTAINER(tmpdat2.eventbox), tmpdat2.widget);      // label

		} else {
          gtk_fixed_put(GTK_FIXED(tmpdat.widget), tmpdat2.widget, num_a, num_b);
	      gtk_widget_set_size_request(tmpdat2.widget, num_c, num_d);
		}

	  } else  {
        Error("parameter Hias_Alas tidak benar");
	  }

    }

	ungetlex();

    // printf("Hias_Alas finished. \n");
}

