// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcJumUntaian ()
{
  VAL_LABEL datx;
  long  j=0;

  VAL_LABEL valdat;
  
  int    dat_num=0;
  double dat_dbl = 0.0;



  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


         getlex();

         // printf("lex type : %d\n", lex.type); 
         // printf("lex ident : %s\n", lex.detail.ident); 

         if(lex.type == TYPE_NUM) {
           Error("JUMLAH_UNTAIAN: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("JUMLAH_UNTAIAN: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           Error("JUMLAH_UNTAIAN: masukan data salah");
         } else if(lex.type == TYPE_ARRAY) {
           Error("JUMLAH_UNTAIAN: masukan data salah, dilarang ada besaran");
         } else {


           // printf("lex ident : %s\n", lex.detail.ident); 
           valdat = ValLabel(lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           // printf("get ident type : %d\n", valdat.datatype); 

           if(valdat.datatype == 6 && valdat.array_i != '\0') {
                dat_num = 0;
                for(j=0; j< valdat.array_max; j++) {
                    dat_num = dat_num + get_int_array(valdat, j);
                }
                datx.val = dat_num;
                datx.datatype = 0;
           } else if(valdat.datatype == 7 && valdat.array_d != '\0') {
                dat_dbl = 0.0;
                for(j=0; j < valdat.array_max; j++) {
                    dat_dbl = dat_dbl + get_dbl_array(valdat, j);
                }
                datx.floatdata = dat_dbl;
                datx.datatype = 1;
           } else {
             Error("JUMLAH_UNTAIAN: IDENT masukan data salah");
           }

         }

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

  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);

  return datx;
}


VAL_LABEL funcAveUntaian ()
{
  VAL_LABEL datx;
  long  j=0;

  VAL_LABEL valdat;
  
  int    dat_num=0;
  double dat_dbl = 0.0;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));


  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("RATARATA_UNTAIAN: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("RATARATA_UNTAIAN: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           Error("RATARATA_UNTAIAN: masukan data salah");
         } else if(lex.type == TYPE_ARRAY) {
           Error("RATARATA: masukan data salah, dilarang ada besaran");
         } else {
           valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 6 && valdat.array_i != '\0') {
                dat_num = 0;
                for(j=0; j< valdat.array_max; j++) {
                    dat_num = dat_num + get_int_array(valdat, j);
                }
                datx.floatdata = (double)dat_num / valdat.array_max;
                datx.datatype = 1;
           } else if(valdat.datatype == 7 && valdat.array_d != '\0') {
                dat_dbl = 0.0;
                for(j=0; j< valdat.array_max; j++) {
                    dat_dbl = dat_dbl + get_dbl_array(valdat, j);
                }
                datx.floatdata = dat_dbl / valdat.array_max;
                datx.datatype = 1;
           } else {
             Error("RATARATA_UNTAIAN: masukan data salah");
           }

         }

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

  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);

  return datx;
}


VAL_LABEL funcVarUntaian ()
{
  VAL_LABEL datx;
  long  j=0;

  VAL_LABEL valdat;
  
  int    dat_num=0;
  double dat_dbl = 0.0,
	     dat_dbl2 = 0.0;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("VARIAN_UNTAIAN: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("VARIAN_UNTAIAN: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           Error("VARIAN_UNTAIAN: masukan data salah");
         } else if(lex.type == TYPE_ARRAY) {
           Error("VARIAN: masukan data salah, dilarang ada besaran");
         } else {
           valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 6 && valdat.array_i != '\0') {
                dat_num = 0;
                for(j=0; j< valdat.array_max; j++) {
                    dat_num = dat_num + get_int_array(valdat, j);
                }
                dat_dbl = (double)dat_num / valdat.array_max;

                dat_dbl2 = 0.0;
                for(j=0; j< valdat.array_max; j++) {
                  dat_dbl2 = dat_dbl2 + pow(get_int_array(valdat, j) - dat_dbl , 2);
                }

                datx.floatdata = dat_dbl2 / (valdat.array_max - 1);

                datx.datatype = 1;
           } else if(valdat.datatype == 7 && valdat.array_d != '\0') {
                dat_dbl = 0.0;
                for(j=0; j< valdat.array_max; j++) {
                    dat_dbl = dat_dbl + get_dbl_array(valdat, j);
                }
                dat_dbl = dat_dbl / valdat.array_max;

                dat_dbl2 = 0.0;
                for(j=0; j< valdat.array_max; j++) {
                  dat_dbl2 = dat_dbl2 + pow(get_dbl_array(valdat, j) - dat_dbl , 2);
                }

                datx.floatdata = dat_dbl2 / (valdat.array_max - 1);

                datx.datatype = 1;
           } else {
             Error("VARIAN_UNTAIAN: masukan data salah");
           }

         }

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

  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);

  return datx;
}


VAL_LABEL funcStdDevUntaian ()
{
  VAL_LABEL datx;
  long  j=0;

  VAL_LABEL valdat;
  
  int    dat_num=0;
  double dat_dbl = 0.0,
	     dat_dbl2 = 0.0;


  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("STD_DEVIASI: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("STD_DEVIASI: masukan data salah");
         } else if(lex.type == TYPE_STR) {
           Error("STD_DEVIASI: masukan data salah");
         } else if(lex.type == TYPE_ARRAY) {
           Error("STD_DEVIASI: masukan data salah, dilarang ada besaran");
         } else {
           valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 6 && valdat.array_i != '\0') {
                dat_num = 0;
                for(j=0; j< valdat.array_max; j++) {
                    dat_num = dat_num + get_int_array(valdat, j);
                }
                dat_dbl = (double)dat_num / valdat.array_max;

                dat_dbl2 = 0.0;
                for(j=0; j< valdat.array_max; j++) {
                  dat_dbl2 = dat_dbl2 + pow(get_int_array(valdat, j) - dat_dbl , 2);
                }

                datx.floatdata = sqrt ( dat_dbl2 / (valdat.array_max - 1) );

                datx.datatype = 1;
           } else if(valdat.datatype == 7 && valdat.array_d != '\0') {
                dat_dbl = 0.0;
                for(j=0; j< valdat.array_max; j++) {
                    dat_dbl = dat_dbl + get_dbl_array(valdat, j);
                }
                dat_dbl = dat_dbl / valdat.array_max;

                dat_dbl2 = 0.0;
                for(j=0; j< valdat.array_max; j++) {
                  dat_dbl2 = dat_dbl2 + pow(get_dbl_array(valdat, j) - dat_dbl , 2);
                }

                datx.floatdata = sqrt ( dat_dbl2 / (valdat.array_max - 1) );

                datx.datatype = 1;
           } else {
             Error("STD_DEVIASI: masukan data salah");
           }

         }

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

  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);

  return datx;
}


