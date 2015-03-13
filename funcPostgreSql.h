// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#include "pq_common.h"

char** PGDBfields_get(PGresult *pg_res);
char** PGDBrows_get(PGresult *pg_res, int baris_num);

VAL_LABEL funcPGSQL_KONEKSI ()
{
  VAL_LABEL datx;
  int  n=0, i=0, j=0;
  int  dat_num=0;

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0, idx2=0;                           // array index

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];
  char   dat_c[MAX_STRING_LEN];
  char   dat_d[MAX_STRING_LEN];

  float tmp = 0.0;

  int    isArrDummy=0;

  int    size = 0;
  char   get_name[MAX_STRING_LEN];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  memset(&dat_c, '\0', sizeof(dat_c));
  memset(&dat_d, '\0', sizeof(dat_d));

  memset(&get_name, '\0', sizeof(get_name));
  
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             if(n == 4) {
               dat_num = lex.detail.num;
             }
           } else if(lex.type == TYPE_STR) {
             if(n == 0) {
               strcpy(dat_a, lex.detail.string);
             } else
             if(n == 1) {
               strcpy(dat_b, lex.detail.string);
             } else
             if(n == 2) {
               strcpy(dat_c, lex.detail.string);
             } else
             if(n == 3) {
               strcpy(dat_d, lex.detail.string);
             }

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

                 sprintf(valdat.array_idx, "%d", idx);

                 if(idx < 0 || idx > MAX_ARRAY)
                   Error("ukuran Untaian tidak sesuai kapasitas");

                 if(valdat.datatype == 8 && valdat.array_s != '\0') {
                   if(valdat.array_s == '\0')
                     Error("PGDB_KONEKSI: ukuran Untaian belum terdefinisi");

                   memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				   memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				   strcpy(TmpStrBox.var.array_name, valdat.array_name);
                   renban = valdat.array_s;

				   if(renban < 0) {
                    printf("variabel untaian tidak ditemukan\n");
				   } else {
                    TmpStrBox.str.stackid = renban;
                    TmpStrBox.str.idx = idx;

					strarryPos = string_findData(TmpStrBox.str);
					if(strarryPos < 0) {
  					  // printf("\n! nilai untaian kata tidak ditemukan");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);

					}

				   }

                   if(n == 0) {
                     strcpy(dat_a, TmpStrBox.str.mystring);
                   } else
                   if(n == 1) {
                     strcpy(dat_b, TmpStrBox.str.mystring);
                   } else
                   if(n == 2) {
                     strcpy(dat_c, TmpStrBox.str.mystring);
                   } else
                   if(n == 3) {
                     strcpy(dat_d, TmpStrBox.str.mystring);
                   }
                 }

                 if(valdat.datatype == 6 && valdat.array_i != '\0') {
                   if(n == 4) {
                     dat_num = get_int_array(valdat, idx);
                   } 
                 }

               }

           } else {

             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               //printf("construct class var: %s\n", class_tmpvar);
               valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, datx, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 0) {
               if(n == 4) {
                 dat_num = valdat.val;
               }
             } else 
             if(valdat.datatype == 3) {
               if(n == 0) {
                 strcpy(dat_a, valdat.str);
               } else
               if(n == 1) {
                 strcpy(dat_b, valdat.str);
               } else
               if(n == 2) {
                 strcpy(dat_c, valdat.str);
               } else
               if(n == 3) {
                 strcpy(dat_d, valdat.str);
               }
             }

           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n==5) {
          /* 
          printf("a: %s\n", dat_a);     // hostname
          printf("b: %s\n", dat_b);     // username
          printf("c: %s\n", dat_c);     // password
          printf("d: %s\n", dat_d);     // tblname
          printf("num: %d\n", dat_num); // port
          */
		  datx.pg_conn = pgdb_connect(dat_a, dat_b, dat_c, dat_d, dat_num);

		  if(datx.pg_conn == NULL) {
            // writeLog("Koneksi PostgreSql DB Salah");
			datx.isPgdbOpen = 0;
		  } else if(datx.pg_conn == CONNECTION_BAD) {
            // writeLog("Koneksi PostgreSql DB Salah");
			datx.isPgdbOpen = 0;
          } else {
            // writeLog("Koneksi PostgreSql DB Okey");
			// printf("Koneksi PostgreSql DB Okey \n");
			datx.isPgdbOpen = 1;
          }

          datx.datatype    = 61;                   /* Pgdb Conn  */

        } else {
          Error("PGDB_KONEKSI: masukan data salah");
        }


  return datx;
}


VAL_LABEL funcPGSQL_HASIL ()
{
  VAL_LABEL datx;
  int  n=0, i=0, j=0;
  int  dat_num=0;

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0, idx2=0;                           // array index

  char   dat_a[MAX_STRING_LEN];
  char   dat_d[MAX_STRING_LEN];

  float tmp = 0.0;

  int    isArrDummy=0;

  int    size = 0;
  char   get_name[MAX_STRING_LEN];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_d, '\0', sizeof(dat_d));

  memset(&get_name, '\0', sizeof(get_name));
  
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  datx.val = 0;   // set init result 0
  
        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             Error("PGSQL_HASIL: masukan data salah");
           } else if(lex.type == TYPE_STR) {
             if(n == 1) {
               strcpy(dat_a, lex.detail.string);
             } 
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

                 sprintf(valdat.array_idx, "%d", idx);

                 if(idx < 0 || idx > MAX_ARRAY)
                   Error("ukuran Untaian tidak sesuai kapasitas");

                 if(valdat.datatype == 8 && valdat.array_s != '\0') {
                   if(valdat.array_s == '\0')
                     Error("PGSQL_HASIL: ukuran Untaian belum terdefinisi");

                   memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				   memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				   strcpy(TmpStrBox.var.array_name, valdat.array_name);
                   renban = valdat.array_s;

				   if(renban < 0) {
                    printf("variabel untaian tidak ditemukan\n");
				   } else {
                    TmpStrBox.str.stackid = renban;
                    TmpStrBox.str.idx = idx;

					strarryPos = string_findData(TmpStrBox.str);
					if(strarryPos < 0) {
  					  // printf("\n! nilai untaian kata tidak ditemukan");
					} else {
                      TmpStrBox.str = string_getElement(strarryPos);

					}

				   }

                   if(n == 1) {
                     strcpy(dat_a, TmpStrBox.str.mystring);
                   }
                 }

               }

           } else {

             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               //printf("construct class var: %s\n", class_tmpvar);
               valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, datx, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 3) {
               if(n == 1) {
                 strcpy(dat_a, valdat.str);
               }
             } else
             if(valdat.datatype == 61) { // pgsql conn
               if(n == 0) {
                 strcpy(dat_d, lex.detail.ident);

				 tmpdat = valdat;
                 tmpdat.pg_conn = valdat.pg_conn;
				 tmpdat.isPgdbOpen = valdat.isPgdbOpen;

				 // printf("get pg_conn\n");

				 if(valdat.pg_conn == NULL) {
				   printf("get valdat pg_conn NULL !\n");
				 }

               }
             }

           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        // printf("PGSQL_HASIL n:%d\n", n);

        if(n==2) {
          
          // printf("hasil sql: %s\n", dat_a);     // long sqlstr
          // printf("con: %s\n", dat_d);           // conn
          
          datx.pg_res = NULL;
	  datx.pg_res = PQexec(tmpdat.pg_conn, dat_a);

	  // keep var conn ???
	  datx.pg_conn    = tmpdat.pg_conn;
	  datx.isPgdbOpen = tmpdat.isPgdbOpen;
          
	  datx.datatype    = 62;                   /* Pgsql res  */
          datx.val         = 1;          // set result status OK

	  if(datx.pg_res  == NULL) {
	    printf("Hasil PostgreSql DB NULL\n");
            // writeLog("Hasil PostgreSql DB NULL");
		datx.val = -1;
	  }

	  if(PQresultStatus(datx.pg_res) != PGRES_TUPLES_OK) {
            // writeLog("Hasil PostgreSql DB Salah ");
		datx.val = -1;
	  }


          /* printf("stored data num: %d\n", (int)mysql_num_rows(datx.my_res) ); */
          memset(&tmpdat, '\0', sizeof(tmpdat));

        } else {
          Error("PGSQL_HASIL: masukan data salah");
        }

  
  return datx;
}

VAL_LABEL funcPGSQL_TOTAL ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_IDENT) {

           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
             //printf("construct class var: %s\n", class_tmpvar);
             valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 62) { // pgsql_result

		     if(valdat.pg_res == NULL) {
               Error("PGSQL_TOTAL Salah: Hasil PGSQL NIL");
		     }

             datx.val = (int)PQntuples(valdat.pg_res);
             datx.datatype = 0;

             /* printf("get stored data num: %d\n", datx.val ); */
           } else {
           Error("PGSQL_TOTAL: masukan data salah");
           }
         } else {
           Error("PGSQL_TOTAL: masukan data salah");
         } 

    return datx;
}


VAL_LABEL funcPGSQL_RESULT_STATUS ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;

  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_IDENT) {

           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
             //printf("construct class var: %s\n", class_tmpvar);
             valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 62) { // pgsql_result

	     if(valdat.pg_res == NULL) {
               Error("PGSQL_STATUS Salah: Hasil PGSQL NIL");
	     }

             datx.val = valdat.val;   // passing result
             datx.datatype = 0;

             /* printf("get stored data num: %d\n", datx.val ); */
           } else {
           Error("PGSQL_STATUS: masukan data salah");
           }
         } else {
           Error("PGSQL_STATUS: masukan data salah");
         } 

    return datx;
}

VAL_LABEL funcPGSQL_NAMAKOLOM ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  int    j=0;
  char   class_tmpvar[MAX_STRING_LEN];
  char **get=NULL;
  char tmpstr[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

         getlex();
		 //printf("lex ident : %s\n", lex.detail.ident);
         //printf("lex type : %d\n", lex.type);

         if(lex.type == TYPE_IDENT) {

           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
             //printf("construct class var: %s\n", class_tmpvar);
             valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // printf("kolom type %d\n", valdat.datatype);

		   if(valdat.pg_res == NULL) {
             Error("PGSQL_NAMAKOLOM Salah: Hasil PGSQL NIL");
		   }

           if(valdat.datatype == 62) { // pgsql_result
             get = PGDBfields_get(valdat.pg_res);

             for(j=0; get[j] != '\0'; j++) {

			   if(j==0) {
			     datx.array_s = createRenban(renban);
			     datx.datatype = 8;                      // save as real array
			   }
			   memset(&tmpstr, '\0', sizeof(tmpstr));
			   sprintf(tmpstr, "%s", get[j]);
               save_str_array(datx, j, tmpstr);
			 }

             datx.array_max = j;
             split_free(get);

             /* printf("get stored data num: %d\n", datx.val ); */
           } else {
             Error("PGSQL_NAMAKOLOM: masukan data salah");
           }
         } else {
           Error("PGSQL_NAMAKOLOM: masukan data salah");
         } 


      return datx;
}

VAL_LABEL funcPGSQL_ISIDATA ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  VAL_LABEL tmpdat;
  int  j=0;
  char class_tmpvar[MAX_STRING_LEN];
  int  num=0;
  char tmpstr[MAX_STRING_LEN];
  char **get=NULL;


  memset(&datx, '\0', sizeof(datx));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
  memset(&tmpstr, '\0', sizeof(tmpstr));

         // get PG result
         getlex();
		 // printf("lex detail ident : %s\n", lex.detail.ident);
         // printf("lex type : %d\n", lex.type);

         if(lex.type == TYPE_IDENT) {

           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
             //printf("construct class var: %s\n", class_tmpvar);
             valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
            }

           if(valdat.datatype = 62) { // pgsql_result
             tmpdat = valdat;

		     if(valdat.pg_res == NULL) {
               Error("PGSQL_ISIDATA Salah: Hasil PGSQL NIL");
		     }
           } else {
           Error("PGSQL_ISIDATA: masukan data salah");
           }
         } else {
           Error("PGSQL_ISIDATA: masukan data salah");
         } 

         // skip comma
		 getlex();
		 // printf("ident char : %c\n", lex.detail.ident[0]);
		 if(lex.detail.ident[0] != ',') {
           Error("PGSQL_ISIDATA: masukan data salah");
		 }

		 // get num of line
         getlex();
         // printf("lex detail num : %d\n", lex.detail.num);
         // printf("lex type : %d\n", lex.type);

         if(lex.type == TYPE_NUM) {
			 num = lex.detail.num;
		 } else if(lex.type == TYPE_IDENT) {

           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
             //printf("construct class var: %s\n", class_tmpvar);
             valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
            }

           // valdat = ValLabel( lex.detail.ident, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 0) {
			   num = valdat.val;
           } else {
           Error("PGSQL_ISIDATA: masukan data salah");
           }
         } else {
           Error("PGSQL_ISIDATA: masukan data salah");
         } 

		 if(tmpdat.pg_res != NULL) {
             get = PGDBrows_get(tmpdat.pg_res, num);

             for(j=0; get[j] != '\0'; j++) {

			   if(j==0) {
			     datx.array_s = createRenban(renban);
			     datx.datatype = 8;                      // save as real array
			   }
			   memset(&tmpstr, '\0', sizeof(tmpstr));
			   sprintf(tmpstr, "%s", get[j]);
               save_str_array(datx, j, tmpstr);

             }

             datx.array_max = j;
             split_free(get);

             /* printf("get stored data num: %d\n", datx.val ); */
		 }
  
      return datx;
}

// ///////////////////////////////////////////////////////////////////////////

/* ****************************************************** */
/* PostgreSql handle */
/* ****************************************************** */


char** PGDBfields_get(PGresult *pg_res)
{
   int  fieldcount = 0;

   char **arr = NULL; 
   int  n   = 0;    
   int  i   = 0;  
   char *buf=NULL;
   char *tp=NULL;

   char a_cell[1024];

	if (pg_res == NULL) {
           return NULL;
	}

	buf = (char*)malloc(strlen((char *)pg_res) + 1);
	if (buf == NULL) {
		return NULL;
	}
	strcpy(buf, (char *)pg_res);

    fieldcount = (int)PQnfields(pg_res);

        n = 0;
        for(i=0; i < fieldcount; i++) {
           char **a = (char**)realloc(arr, sizeof(*arr) * (n+3));
           memset(&a_cell, '\0', sizeof(a_cell));
		   sprintf(a_cell,"%s", PQfname(pg_res, i));

           if(a_cell[0] != '\0' && strlen(a_cell)>0 ) {
             tp = (char*)malloc(strlen(a_cell) + 1);
             if(strlen(a_cell) > 0) {
                strcpy(tp, a_cell);
                // printf("%d data: %s\n", i, a_cell);
             } else {
                strcpy(tp, "");
             }

		     a[++n] = tp;
		     arr = a;
           }

	}

	if (arr != '\0') {
		arr[0] = buf;
		arr++;
		arr[n] = '\0';
	} else {
      free(buf);
	}

    memset(&a_cell, '\0', sizeof(a_cell));

	return arr;
}

char** PGDBrows_get(PGresult *pg_res, int baris_num)
{
   int  rowcount   = 0;
   int  fieldcount = 0;

   char **arr = NULL; 
   int  n   = 0;    
   int  i   = 0;  
   int  j   = 0;  
   char *buf=NULL;
   char *tp=NULL;

   char a_cell[1024];


	if (pg_res == NULL) {
           return NULL;
	}

    rowcount   = (int)PQntuples(pg_res);
    fieldcount = (int)PQnfields(pg_res);

    /* printf(">>> data num %d \n", rowcount); */

	if (rowcount <= 0) {
           return NULL;
	}

	buf = (char*)malloc(strlen((char *)pg_res) + 1);
	if (buf == NULL) {
		return NULL;
	}
	strcpy(buf, (char *)pg_res);


        n = 0;
        for(i=0; i < fieldcount; i++) {
           char **a = (char**)realloc(arr, sizeof(*arr) * (n+3));
           memset(&a_cell, '\0', sizeof(a_cell));
		   sprintf(a_cell,"%s", PQgetvalue(pg_res, baris_num, i));

           if(a_cell[0] != '\0' && strlen(a_cell)>0 ) {
             tp = (char*)malloc(strlen(a_cell) + 1);
             if(strlen(a_cell) > 0) {
                strcpy(tp, a_cell);
                // printf("%d data: %s\n", i, a_cell);
             } else {
                strcpy(tp, "");
             }

		     a[++n] = tp;
		     arr = a;
           } else {
             // printf("%d OTHER\n", i);
             tp = (char*)malloc(2);
             strcpy(tp, " ");

		     a[++n] = tp;
		     arr = a;
           }
	    }

	if (arr != '\0') {
		arr[0] = buf;
		arr++;
		arr[n] = '\0';
	} else {
      free (buf);
	}

    memset(&a_cell, '\0', sizeof(a_cell));

	return arr;
}


