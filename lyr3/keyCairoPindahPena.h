
// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyCairoPindahPena ()
{
  double  dat_num=0.0, dat_num2=0.0;
  int  n=0, i=0, j=0;

  VAL_LABEL valdat, tmpdat;
  VAL_LABEL mindat;  
  long    idx=0;                           // array index

  cairo_t *cr_img=NULL;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&mindat, '\0', sizeof(mindat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             if(n == 1)
              dat_num  = (double)lex.detail.num;
             if(n == 2)
              dat_num2 = (double)lex.detail.num;

           } else if(lex.type == TYPE_DBL) {
             if(n == 1)
              dat_num  = lex.detail.dblnum;
             if(n == 2)
              dat_num2 = lex.detail.dblnum;

           } else if(lex.type == TYPE_SYM) {
  		     if(lex.type == TYPE_SYM && lex.detail.symbol == '-') {
               mindat = get_Minus_Val();        // consider minus param
			   if(mindat.datatype == 0) {
                 if(n == 1)
				   dat_num  = mindat.val;
                 if(n == 2)
                   dat_num2 = mindat.val;
			   } else
			   if(mindat.datatype == 1) {
                 if(n == 1)
				   dat_num  = mindat.floatdata;
                 if(n == 2)
                   dat_num2 = mindat.floatdata;
			   } 
		     }

           } else if(lex.type == TYPE_STR) {
             Error("Pindah_Pena: masukan data salah");
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
                idx = atol (valdat.array_idx);
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

              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
               #else
               snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
               #endif
              #else
              snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
              #endif

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 6) {
                if(valdat.array_i == '\0')
                  Error("Pindah_Pena: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */
                if(n == 1)
                  dat_num = (double)get_int_array(valdat, idx) ;
                if(n == 2)
                  dat_num2 = (double)get_int_array(valdat, idx);

			  } else if(valdat.datatype == 7) {
                if(valdat.array_d == '\0')
                  Error("Pindah_Pena: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */
                if(n == 1)
                  dat_num = get_dbl_array(valdat, idx) ;
                if(n == 2)
                  dat_num2 = get_dbl_array(valdat, idx);

              } else {
                Error("Pindah_Pena: masukan data salah");
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
               valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 0) {
               if(n == 1)                       /* x   */
                 dat_num  = (double)valdat.val;
               if(n == 2)                       /* y */
                 dat_num2 = (double)valdat.val;


			 } else if(valdat.datatype == 1) {
               if(n == 1)                       /* x   */
                 dat_num  = valdat.floatdata;
               if(n == 2)                       /* y   */
                 dat_num2 = valdat.floatdata;

			 } else if(valdat.datatype == 80){  /* cairo cr */
               if(n == 0)
                 cr_img  = valdat.cr_img;
             } else {
               Error("Pindah_Pena: masukan data salah");
             }
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=3) {
          Error("Pindah_Pena: masukan data salah");
        } else {
          /* printf("R: %d\n", dat_num);
          printf("G: %d\n", dat_num2);
          printf("B: %d\n", dat_num3); */

	      cairo_move_to(cr_img, dat_num, dat_num2);

        }

}
