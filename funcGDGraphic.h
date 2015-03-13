// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcLebarGambar ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
  
         getlex();

         if (lex.type == TYPE_IDENT) {
             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               //printf("construct class var: %s\n", class_tmpvar);
               valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             }

             //valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 20){               /* gd img */
               datx.val = valdat.gdimg->sx;
             } else {
               Error("LebarGambar: masukan data salah");
             }
         } else {
           Error("LebarGambar: masukan data salah");
         }

         datx.datatype = 0;  /* int */

  return datx;
}

VAL_LABEL funcPanjangGambar ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
  
         getlex();

         if (lex.type == TYPE_IDENT) {
             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               //printf("construct class var: %s\n", class_tmpvar);
               valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 20){               /* gd img */
               datx.val = valdat.gdimg->sy;
             } else {
               Error("PanjangGambar: masukan data salah");
             }
         } else {
           Error("PanjangGambar: masukan data salah");
         }

         datx.datatype = 0;  /* int */

    return datx;
}


VAL_LABEL funcLebarHuruf ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
  
         getlex();

         if (lex.type == TYPE_IDENT) {
             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               //printf("construct class var: %s\n", class_tmpvar);
               valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 22){               /* gd font */
               datx.val = valdat.gdfont->w;
             } else {
               Error("LebarHuruf: masukan data salah");
             }
         } else {
           Error("LebarHuruf: masukan data salah");
         }

         datx.datatype = 0;  /* int */

      return datx;
}

VAL_LABEL funcTinggiHuruf ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();

         if (lex.type == TYPE_IDENT) {
             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               //printf("construct class var: %s\n", class_tmpvar);
               valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 22){               /* gd font */
               datx.val = valdat.gdfont->h;
             } else {
               Error("TinggiHuruf: masukan data salah");
             }
         } else {
           Error("TinggiHuruf: masukan data salah");
         }

         datx.datatype = 0;  /* int */

        return datx;
}

VAL_LABEL funcBuatGambar ()
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
             Error("BuatGambar: masukan data salah");
           } else if(lex.type == TYPE_STR) {
             Error("BuatGambar: masukan data salah");
           } else if(lex.type == TYPE_ARRAY) {
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

              sprintf(valdat.array_idx , "%d", idx);

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 6 ) {
                if(valdat.array_i == '\0')
                  Error("BuatGambar: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */
                if(n == 0)
                  dat_num = get_int_array(valdat, idx) ;
                if(n == 1)
                  dat_num2 = get_int_array(valdat, idx);

              } else {
                Error("BuatGambar: masukan data salah");
              }
            }


           } else {
             // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );

             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
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
                Error("BuatGambar: masukan data salah");
             }
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=2) {
	     Error("BuatGambar: masukan data salah");
        } else {
            /* printf("bingkai x: %d\n", dat_num);
            printf("bingkai y: %d\n", dat_num2); */

            datx.gdimg = gdImageCreate(dat_num , dat_num2);
            datx.datatype = 20;       /* img */
        }

        return datx;
}

VAL_LABEL funcWarnaGambar ()
{
  VAL_LABEL datx;

  int  dat_num=0, dat_num2=0, dat_num3=0;

  int  n=0, i=0, j=0;

  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index


  gdImagePtr dat_img=NULL;

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
             if(n == 1)
              dat_num  = lex.detail.num;
             if(n == 2)
              dat_num2 = lex.detail.num;
             if(n == 3)
              dat_num3  = lex.detail.num;
           } else if(lex.type == TYPE_DBL) {
             Error("WarnaGambar: masukan data salah");
           } else if(lex.type == TYPE_STR) {
             Error("WarnaGambar: masukan data salah");
           } else if(lex.type == TYPE_ARRAY) {
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

              sprintf(valdat.array_idx , "%d", idx);

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 6) {
                if(valdat.array_i == '\0')
                  Error("WarnaGambar: ukuran Untaian belum terdefinisi");

                /* printf("%d", valdat.array_i[idx]); */
                if(n == 1)
                  dat_num = get_int_array(valdat, idx) ;
                if(n == 2)
                  dat_num2 = get_int_array(valdat, idx);
                if(n == 3)
                  dat_num3 = get_int_array(valdat, idx);

              } else {
                Error("WarnaGambar: masukan data salah");
              }
            }


           } else {

             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               //printf("construct class var: %s\n", class_tmpvar);
               valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 0) {
               if(n == 1)                       /* red   */
                 dat_num  = valdat.val;
               if(n == 2)                       /* green */
                 dat_num2 = valdat.val;
               if(n == 3)                       /* blue  */
                 dat_num3  = valdat.val;
             } else if(valdat.datatype == 20){  /* gd img */
               if(n == 0)
                 dat_img  = valdat.gdimg;
             } else {
             Error("WarnaGambar: masukan data salah");
             }
           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n!=4) {
	     Error("WarnaGambar: masukan data salah");
        } else {
            /* printf("R: %d\n", dat_num);
            printf("G: %d\n", dat_num2);
            printf("B: %d\n", dat_num3); */

            datx.val = gdImageColorAllocate(dat_img, dat_num, dat_num2, dat_num3);
            datx.datatype = 0;       /* int for color */
        }

          return datx;
}

