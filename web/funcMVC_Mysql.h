// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

MVCPARSING MVCgetlex(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVCungetlex(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);

#include "../my_common.h"

char** DBrows_get(MYSQL_RES *my_res);

MVCPARSING funcMVC_MYSQL_ISIDATA (MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  MVCPARSING par;

  VAL_LABEL datx, valdat;
  int  j=0;

  char tmpstr[MAX_STRING_LEN];
  char **get=NULL;

  memset(&par, '\0', sizeof(par));
  memset(&datx, '\0', sizeof(datx));  
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpstr, '\0', sizeof(tmpstr));

  //printf("inside funcMVC_MYSQL_ISIDATA <BR>\n");

         //getlex();
         par = MVCgetlex(mvc_lex, mvc_pg);
         mvc_lex = par.mvc_lex;
         mvc_pg  = par.mvc_pg;

	 // printf("mvc_lex ident: %s\n", mvc_lex.detail.ident);
         // printf("mvc_lex type : %d\n", mvc_lex.type);

         if(mvc_lex.type == TYPE_MVC_IDENT) {

           valdat = ValLabel( mvc_lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );

	   //printf("get ident : %s <BR>\n", valdat.ident);
           //printf("get dttype : %d <BR>\n", valdat.datatype);

           if(valdat.datatype == 12) {
             get = (char **)DBrows_get(valdat.my_res);

             for(j=0; get[j] != '\0'; j++) {

			   if(j==0) {
			     datx.array_s = createRenban(renban);
			     datx.datatype = 8;                      // save as real array
			   }
			   memset(&tmpstr, '\0', sizeof(tmpstr));
			   sprintf(tmpstr, "%s", get[j]);
                           save_str_array(datx, j, tmpstr);

                           par.array_s  = datx.array_s;
                           par.datatype = datx.datatype;


             }

             datx.array_max = j;
             par.array_max  = j;
             
             split_free(get);

             /* printf("get stored data num: %d\n", datx.val ); */
           } else {
             Error("MYSQL_DATA: masukan data salah");
           }
         } else {
           Error("MYSQL_DATA: masukan data salah");
         } 


      par.mvc_lex = mvc_lex;
      par.mvc_pg  = mvc_pg;  

      return par;
}


// ///////////////////////////////////////////////////////////////////////////

/* ****************************************************** */
/* Mysql handle */
/* ****************************************************** */

