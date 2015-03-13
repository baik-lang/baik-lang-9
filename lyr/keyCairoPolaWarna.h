
// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyCairoPolaWarna ()
{
  double  dat_num1=0.0, dat_num2=0.0, dat_num3=0.0, dat_num4=0.0;
  int  n=0, i=0, j=0;

  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  cairo_pattern_t *pat=NULL;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             if(n == 1)
              dat_num1  = (double)lex.detail.num;
             if(n == 2)
              dat_num2  = (double)lex.detail.num;
             if(n == 3)
              dat_num3  = (double)lex.detail.num;
             if(n == 4)
              dat_num4  = (double)lex.detail.num;
           } else if(lex.type == TYPE_DBL) {
             if(n == 1)
              dat_num1  = lex.detail.dblnum;
             if(n == 2)
              dat_num2  = lex.detail.dblnum;
             if(n == 3)
              dat_num3  =lex.detail.dblnum;
             if(n == 4)
              dat_num4  =lex.detail.dblnum;
           } else if(lex.type == TYPE_STR) {
             Error("Pola_Warna: masukan data salah");
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
                  Error("Pola_Warna: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */
                if(n == 1)
                  dat_num1 = (double)get_int_array(valdat, idx) ;
                if(n == 2)
                  dat_num2 = (double)get_int_array(valdat, idx);
                if(n == 3)
                  dat_num3 = (double)get_int_array(valdat, idx);
                if(n == 4)
                  dat_num4 = (double)get_int_array(valdat, idx);

			  } else if(valdat.datatype == 7) {
                if(valdat.array_d == '\0')
                  Error("Pola_Warna: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */
                if(n == 1)
                  dat_num1 = get_dbl_array(valdat, idx) ;
                if(n == 2)
                  dat_num2 = get_dbl_array(valdat, idx);
                if(n == 3)
                  dat_num3 = get_dbl_array(valdat, idx);
                if(n == 4)
                  dat_num4 = get_dbl_array(valdat, idx);

              } else {
                Error("Pola_Warna: masukan data salah");
              }
            }


           } else {

             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               //printf("construct class var: %s\n", class_tmpvar);
               valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 0) {
               if(n == 1)                       /* offset / percent   */
                 dat_num1  = (double)valdat.val;
               if(n == 2)                       /* red   */
                 dat_num2 = (double)valdat.val;
               if(n == 3)                       /* green */
                 dat_num3  = (double)valdat.val;
               if(n == 4)                       /* blue  */
                 dat_num4  = (double)valdat.val;


			 } else if(valdat.datatype == 1) {
               if(n == 1)                       /* offset   */
                 dat_num1  = valdat.floatdata;
               if(n == 2)                       /* red   */
                 dat_num2 = valdat.floatdata;
               if(n == 3)                       /* green */
                 dat_num3  = valdat.floatdata;
               if(n == 4)                       /* blue  */
                 dat_num4  = valdat.floatdata;

			 } else if(valdat.datatype == 82){  /* cairo pattern */
               if(n == 0)
                 pat  = valdat.cr_pattern;

			   if(pat == NULL)
				   printf("pola_warna: pola Nil!\n");
             } else {
               Error("Pola_Warna: masukan data salah");
             }
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=5) {
          Error("Pola_Warna: masukan data salah");
        } else {
	      cairo_pattern_add_color_stop_rgb (pat, dat_num1, dat_num2, dat_num3, dat_num4);
        }

}


