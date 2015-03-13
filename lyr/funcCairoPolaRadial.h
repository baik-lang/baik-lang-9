// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcCairoPolaRadial () 
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;
  VAL_LABEL mindat; 

  double  x0=0.0, y0=0.0, r0=0.0;
  double  x1=0.0, y1=0.0, r1=0.0;
  int  n=0, i=0;

  long    idx=0; 
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&mindat, '\0', sizeof(mindat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

      n = 0;
      do {
         getlex();

         if(lex.type == TYPE_NUM) {
             if(n == 0)
              x0   = (double)lex.detail.num;
             if(n == 1)
              y0  = (double)lex.detail.num;
             if(n == 2)
              r0  = (double)lex.detail.num;
             if(n == 3)
              x1  = (double)lex.detail.num;
             if(n == 4)
              y1  = (double)lex.detail.num;
             if(n == 5)
              r1  = (double)lex.detail.num;
         } else if(lex.type == TYPE_DBL) {
             if(n == 0)
              x0   = lex.detail.dblnum;
             if(n == 1)
              y0  = lex.detail.dblnum;
             if(n == 2)
              r0  = lex.detail.dblnum;
             if(n == 3)
              x1  =lex.detail.dblnum;
             if(n == 4)
              y1  =lex.detail.dblnum;
             if(n == 5)
              r1  =lex.detail.dblnum;

           } else if(lex.type == TYPE_SYM) {
  		     if(lex.type == TYPE_SYM && lex.detail.symbol == '-') {
               mindat = get_Minus_Val();        // consider minus param
			   if(mindat.datatype == 0) {
                if(n == 0)
                  x0  = mindat.val;
                if(n == 1)
                  y0 = mindat.val;
                if(n == 2)
                  r0 = mindat.val;
                if(n == 3)
                  x1 = mindat.val;
                if(n == 4)
                  y1 = mindat.val;
                if(n == 5)
                  r1 = mindat.val;
			   } else
			   if(mindat.datatype == 1) {
                if(n == 0)
                  x0  = mindat.floatdata;
                if(n == 1)
                  y0 = mindat.floatdata;
                if(n == 2)
                  r0 = mindat.floatdata;
                if(n == 3)
                  x1 = mindat.floatdata;
                if(n == 4)
                  y1 = mindat.floatdata;
                if(n == 5)
                  r1 = mindat.floatdata;
			   } 
		     }

         } else if(lex.type == TYPE_STR) {
             Error("PolaRadial: masukan data salah");
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

              if(valdat.datatype == 6 ) {
                if(valdat.array_i == '\0')
                  Error("PolaRadial: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */
                if(n == 0)
                  x0  = (double)get_int_array(valdat, idx) ;
                if(n == 1)
                  y0 = (double)get_int_array(valdat, idx) ;
                if(n == 2)
                  r0 = (double)get_int_array(valdat, idx);
                if(n == 3)
                  x1 = (double)get_int_array(valdat, idx);
                if(n == 4)
                  y1 = (double)get_int_array(valdat, idx);
                if(n == 5)
                  r1 = (double)get_int_array(valdat, idx);

			  } else if(valdat.datatype == 7) {
                if(valdat.array_d == '\0')
                  Error("PolaRadial: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */
                if(n == 0)
                  x0  = get_dbl_array(valdat, idx) ;
                if(n == 1)
                  y0 = get_dbl_array(valdat, idx) ;
                if(n == 2)
                  r0 = get_dbl_array(valdat, idx);
                if(n == 3)
                  x1 = get_dbl_array(valdat, idx);
                if(n == 4)
                  y1 = get_dbl_array(valdat, idx);
                if(n == 5)
                  r1 = get_dbl_array(valdat, idx);

              } else {
                Error("PolaRadial: masukan data salah");
              }
            }

		 } else if (lex.type == TYPE_IDENT) {
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

             if(valdat.datatype == 0){ 
                if(n == 0)
                  x0  = valdat.val;
                if(n == 1)
                  y0 = valdat.val;
                if(n == 2)
                  r0 = valdat.val;
                if(n == 3)
                  x1 = valdat.val;
                if(n == 4)
                  y1 = valdat.val;
                if(n == 5)
                  r1 = valdat.val;

			 } else

             if(valdat.datatype == 1){ 
                if(n == 0)
                  x0  = valdat.floatdata;
                if(n == 1)
                  y0 = valdat.floatdata;
                if(n == 2)
                  r0 = valdat.floatdata;
                if(n == 3)
                  x1 = valdat.floatdata;
                if(n == 4)
                  y1 = valdat.floatdata;
                if(n == 5)
                  r1 = valdat.floatdata;

             } else {
               Error("PolaRadial: masukan data salah");
             }
         } else {
           Error("PolaRadial: masukan data salah");
         }

         n++;

         getlex();

      }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

      ungetlex();

      if(n!=6) {
          Error("PolaRadial: masukan data salah");
      } else {
          datx.cr_pattern = cairo_pattern_create_radial (x0, y0, r0, x1, y1, r1);
		  datx.datatype = 82; // cairo pattern
      }

      return datx;
}


