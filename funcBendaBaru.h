// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcBendaBaru ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

         getlex();

        if(currentClass != NULL && strlen(currentClass) > 0) {
          Error("Dilarang membuat Benda dalam Benda");
        }

         if (lex.type == TYPE_IDENT) {
             valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
			 // printf("get ident %s type %d\n", lex.detail.ident, valdat.datatype);

             if(valdat.datatype == 30){               // Class Definition
               datx.datatype = 31;                    // Class Instance
               datx.isClassInit = 0;                  // AWALAN has not been set
               // save obj name reference
               strcpy(datx.benda_name, lex.detail.ident);
             } else {
               Error("BendaBaru: masukan data salah");
             }
         } else {
           Error("BendaBaru: masukan data salah");
         }

         datx.datatype = 31;  /* Class Instance */

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

  return datx;
}


