// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcCairoBidangGambar ()
{
  VAL_LABEL datx;

  int  n=0, i=0, j=0;
  int  dat_num=0, dat_num2=0;

  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        n = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             if(n == 0)
              dat_num  = lex.detail.num;
             if(n == 1)
              dat_num2 = lex.detail.num;
           } else if(lex.type == TYPE_DBL) {
             Error("BidangGambar: masukan data salah");
           } else if(lex.type == TYPE_STR) {
             Error("BidangGambar: masukan data salah");
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

              sprintf(valdat.array_idx , "%li", idx);

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 6 ) {
                if(valdat.array_i == '\0')
                  Error("BidangGambar: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */
                if(n == 0)
                  dat_num = get_int_array(valdat, idx) ;
                if(n == 1)
                  dat_num2 = get_int_array(valdat, idx);

              } else {
                Error("BidangGambar: masukan data salah");
              }
            }


           } else {
             // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );

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

             if(valdat.datatype == 0) {
               if(n == 0)
                 dat_num  = valdat.val;
               if(n == 1)
                 dat_num2 = valdat.val;
             } else {
                Error("BidangGambar: masukan data salah");
             }
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=2) {
	     Error("BidangGambar: masukan data salah");
        } else {
            /* printf("bingkai x: %d\n", dat_num);
            printf("bingkai y: %d\n", dat_num2); */

			datx.cr_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, dat_num , dat_num2);
            datx.datatype   = 81;       /* cairo surface */
        }

        return datx;
}


