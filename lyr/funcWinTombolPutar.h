// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinTombolPutar ()
{
  VAL_LABEL datx;
  int  n=0;

  char   tmpMsg[MAX_STRING_LEN];
  char   tmpMsg2[MAX_STRING_LEN];

  double in0 = 0.0;
  double in1 = 0.0;
  double in2 = 0.0;

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
  memset(tmpMsg2, '\0', sizeof(tmpMsg2));

  n = 0;

	do{

         /* get referenced string */
         getlex();

         /* printf("lex type : %d\n", lex.type);  */

         if(lex.type == TYPE_NUM) {
		   if(n == 0)
             in0 = (double) lex.detail.num;
		   else if(n == 1)
             in1 = (double) lex.detail.num;
		   else if(n == 2)
             in2 = (double) lex.detail.num;

		 } else if(lex.type == TYPE_DBL) {
		   if(n == 0)
             in0 = (double) lex.detail.dblnum;
		   else if(n == 1)
             in1 = (double) lex.detail.dblnum;
		   else if(n == 2)
             in2 = (double) lex.detail.dblnum;

		 } else if(lex.type == TYPE_STR) {
            Error("Salah perintah TombolPutar");
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

              if(valdat.datatype == 6) {
                if(n == 0)
					in0 = (double)get_int_array(valdat,idx);
				else if(n == 1)
					in1 = (double)get_int_array(valdat,idx);
				else if(n == 2)
					in2 = (double)get_int_array(valdat,idx);

			  } else if(valdat.datatype == 7) {
                if(n == 0)
					in0 = get_dbl_array(valdat,idx);
				else if(n == 1)
					in1 = get_dbl_array(valdat,idx);
				else if(n == 2)
					in2 = get_dbl_array(valdat,idx);

              } else {
                Error("TombolPutar: masukan data salah");
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
             datx = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 1) {
		     if(n == 0)
				 in0 = (double)datx.val;
			 else if(n == 1)
			     in1 = (double)datx.val;
			 else if(n == 2)
				 in2 = (double)datx.val;
		   } else if(datx.datatype == 2) {
		     if(n == 0)
				 in0 = datx.floatdata;
			 else if(n == 1)
				 in1 = datx.floatdata;
			 else if(n == 2)
				 in2 = datx.floatdata;
           } else {
             Error("TombolPutar: masukan data salah");
           }
         }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(n == 3) {
        // printf("%f %f %f \n", in0, in1, in2);

		if(in2 == 0.0)
			Error("TombolPutar: penambahan tidak boleh nol");
		 // tombolputar
		 datx.widget   = gtk_spin_button_new_with_range(in0, in1, in2);

		 datx.isGUI    = 1;
		 datx.GUItype  = 13;   // SpinButton - TombolPutar - see ValLabel
		 datx.datatype = 40;   // widget
	} else {
      Error("TombolPutar: masukan data salah");
	}

    ungetlex();

	return datx;
}
