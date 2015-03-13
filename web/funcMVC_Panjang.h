// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

VAL_LABEL funcMVC_Panjang() {
  VAL_LABEL datx;

  VAL_LABEL valdat, tmpdat;

  memset(&datx, '\0', sizeof(datx));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));


      /* ======================================================== */
      /* PANJANG              =================================== */
      /* ======================================================== */
      if( !strcmp(lex.detail.string, "PANJANG") || 
                 !strcmp(lex.detail.string, "panjang") ||
                 !strcmp(lex.detail.string, "Panjang") ) { 
         /* printf("PANJANG function\n"); */
         memset(&tmpdat, '\0', sizeof(tmpdat));
         memset(&valdat, '\0', sizeof(valdat));

         getlex();
         // printf("panjang get ident : %s\n", lex.detail.ident);
         // printf("panjang get type : %d\n", lex.type);

         if(lex.type == TYPE_ARRAY) {
            if(strlen(lex.detail.array_str) > 0) {
              strcpy(valdat.array_str, lex.detail.array_str);
              getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
              getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

              /* read data */
              valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              /* printf("panjang array %d", valdat.array_max);  */
              datx.val = tmpdat.array_max;
              datx.datatype = 0;
           }

         } else if(lex.type == TYPE_STR) {
           datx.val = (long)strlen(lex.detail.string);
           datx.datatype = 0;

         } else if(lex.type == TYPE_IDENT) {
           /* read data */
           // printf("get panjang array ident\n");

             tmpdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );

	   // printf("read panjang array ident, type : \n", tmpdat.datatype);

           if(tmpdat.datatype == 3) {
             datx.val = (long)strlen(tmpdat.str);
             datx.datatype = 0;

           }
           else if(tmpdat.datatype >= 6 && tmpdat.datatype <=8) {
             /*
             printf("array type = %d\n", tmpdat.datatype); 
             printf("panjang array ident = %d\n", tmpdat.array_max); 
             */
             datx.val = tmpdat.array_max;
             datx.datatype = 0;

             /*
             printf("ident type = %d\n", datx.datatype); 
             printf("ident val = %d\n", datx.val); 
             */
           }
           else
           if(tmpdat.datatype == 10) {
             /*
             printf("array type = %d\n", tmpdat.datatype); 
             printf("panjang array ident = %d\n", tmpdat.array_max); 
             */
             datx.val = tmpdat.array_max;
             datx.datatype = 0;

             /*
             printf("ident type = %d\n", datx.datatype); 
             printf("ident val = %d\n", datx.val); 
             */
           }
           else
           {
	     // including not valued yet array
             datx.val = tmpdat.array_max;
             datx.datatype = 0;
           }


         } else {
           /* not array, so there is no length */
           datx.val = 0;
           datx.datatype = 0;
         }
	  
       }


  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

	
   return datx;
}


