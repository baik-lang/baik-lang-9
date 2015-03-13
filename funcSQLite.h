// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


#include "sqlite_common.h"

char** SQLITEDBfields_get(sqlite3_stmt  *sqlite_res);
char** SQLITEDBrows_get(sqlite3_stmt  *sqlite_res);

VAL_LABEL funcSQLITE_KONEKSI ()
{
  VAL_LABEL datx;
  int  n=0, i=0, j=0;

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0, idx2=0;                           // array index

  char   dat_a[MAX_STRING_LEN];                   // db filename

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

  memset(&get_name, '\0', sizeof(get_name));
  
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_STR) {
             if(n == 0) {
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
                     Error("SQLITE_KONEKSI: ukuran Untaian belum terdefinisi");

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
               if(n == 0) {
                 strcpy(dat_a, valdat.str);
               } 
             }

           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n==1) {
          /* 
          printf("a: %s\n", dat_a);     // db_name
          */
		  datx.sqlite_conn = sqlite_connect(dat_a);

		  if(datx.sqlite_conn == NULL) {
            //writeLog("Koneksi Sqlite DB Salah");
			datx.isSqliteOpen = 0;
          } else {
            //writeLog("Koneksi Sqlite DB Okey");
			datx.isSqliteOpen = 1;
          }

          datx.datatype    = 81;                   /* Sqlite Conn  */

        } else {
          Error("SQLITE_KONEKSI: masukan data salah");
        }


  return datx;
}

VAL_LABEL funcSQLITE_HASIL ()
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

  datx.val = 0;  // set init result 0 / NG
  
        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             Error("SQLITE_HASIL: masukan data salah");
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
                     Error("SQLITE_HASIL: ukuran Untaian belum terdefinisi");

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
             if(valdat.datatype == 81) { // sqlite conn
               if(n == 0) {
                 strcpy(dat_d, lex.detail.ident);

				 tmpdat = valdat;
				 tmpdat.sqlite_conn  = valdat.sqlite_conn;
				 tmpdat.isSqliteOpen = valdat.isSqliteOpen;

				 // printf("get sqlite_conn\n");

				 if(valdat.sqlite_conn == NULL) {
				   printf("get valdat sqlite_conn NULL !\n");
				 }

               }
             }

           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        // printf("SQLITE_HASIL n:%d\n", n);

        if(n==2) {
          
          // printf("hasil sql: %s\n", dat_a);     // long sqlstr
          // printf("con: %s\n", dat_d);           // conn
		  datx.sqlite_stmt = NULL;

		  sqlite3_prepare(tmpdat.sqlite_conn, dat_a, strlen(dat_a), &datx.sqlite_stmt, NULL);

		  // keep var conn
		  datx.sqlite_conn  = tmpdat.sqlite_conn;
		  datx.isSqliteOpen = tmpdat.isSqliteOpen;

		  // keep var sql
		  strcpy(datx.sql_tmp, dat_a);
		  // printf("saved sql : %s\n", datx.sql_tmp);

		  datx.datatype    = 82;                   /* sqlite stmt  */
                  datx.val         = 1;

		  if(datx.sqlite_stmt  == NULL) {
		    printf("Hasil Sqlite DB NiL\n");
            // writeLog("Hasil Sqlite DB NULL");
			datx.val = -1;
		  } else {
		    // printf("Hasil Sqlite DB OK\n");
		  }

          memset(&tmpdat, '\0', sizeof(tmpdat));

        } else {
          Error("SQLITE_HASIL: masukan data salah");
        }

  
  return datx;
}


VAL_LABEL funcSQLITE_TOTAL ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  int    err, tot = 0;

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

           if(valdat.datatype == 82) { // sqlite_stmt
			 // printf("funcSQLITE_TOTAL : get sql stmt...\n");

			 if(valdat.sqlite_stmt == NULL) {
               Error("SQLITE_TOTAL Salah: Hasil SQLITE NIL");
			 } else {
               // printf("get sqlite_stmt not null, OK \n");
			 }

			 tot = 0;
			 while ((err = sqlite3_step(valdat.sqlite_stmt)) == SQLITE_ROW) {
              // do nothing
			   tot++;
			 }

             datx.val= tot;
             datx.datatype = 0;

             // Need Exec SQL again to keep first pos
             // printf("exec sql again : %s\n", valdat.sql_tmp);
	     valdat.sqlite_stmt = NULL;
	     sqlite3_prepare(valdat.sqlite_conn,  valdat.sql_tmp, strlen( valdat.sql_tmp), &valdat.sqlite_stmt, NULL);

	     if(valdat.sqlite_stmt  == NULL) {
	       printf("Hasil Sqlite again NiL\n");
               // writeLog("Hasil Sqlite DB NULL");
               datx.val = -1;
	     } else {
	       // printf("Hasil Sqlite again OK\n");
	     }

			 // save stmt
			 // printf("save stmt %s\n", lex.detail.ident);
             memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               ValLabel( class_tmpvar , class_sub_deep, valdat, VAL_FLAG_SEARCH_W );
		     } else {
               ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_W );
		     }

             // keep stmt and sql
			 datx.sqlite_stmt = valdat.sqlite_stmt;
			 strcpy(datx.sql_tmp, valdat.sql_tmp);			 
			 
			 // printf("get stored data num: %d\n", datx.val );

           } else {
           Error("SQLITE_TOTAL: masukan data salah");
           }
         } else {
           Error("SQLITE_TOTAL: masukan data salah");
         } 

    return datx;
}

VAL_LABEL funcSQLITE_RESULT_STATUS ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  int    tot = 0;

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

           if(valdat.datatype == 82) { // sqlite_stmt
		 // printf("funcSQLITE_TOTAL : get sql stmt...\n");

             datx.val= valdat.val;  // passing result
             datx.datatype = 0;

             // Need Exec SQL again to keep first pos
             // printf("exec sql again : %s\n", valdat.sql_tmp);
	     valdat.sqlite_stmt = NULL;
	     sqlite3_prepare(valdat.sqlite_conn,  valdat.sql_tmp, strlen( valdat.sql_tmp), &valdat.sqlite_stmt, NULL);

	     if(valdat.sqlite_stmt  == NULL) {
	       printf("Hasil Sqlite again NiL\n");
               // writeLog("Hasil Sqlite DB NULL");
               datx.val = -1;
	     } else {
	       // printf("Hasil Sqlite again OK\n");
	     }

			 // save stmt
			 // printf("save stmt %s\n", lex.detail.ident);
             memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               ValLabel( class_tmpvar , class_sub_deep, valdat, VAL_FLAG_SEARCH_W );
		     } else {
               ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_W );
		     }

             // keep stmt and sql
		 datx.sqlite_stmt = valdat.sqlite_stmt;
		 strcpy(datx.sql_tmp, valdat.sql_tmp);			 
			 
		 // printf("get stored data num: %d\n", datx.val );

           } else {
           Error("SQLITE_STATUS: masukan data salah");
           }
         } else {
           Error("SQLITE_STATUS: masukan data salah");
         } 

    return datx;
}


VAL_LABEL funcSQLITE_NAMAKOLOM ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  int    j=0;
  char   class_tmpvar[MAX_STRING_LEN];

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

           // printf("kolom type %d\n", valdat.datatype);

		   if(valdat.sqlite_stmt == NULL) {
             Error("SQLITE_NAMAKOLOM Salah: Hasil SQLITE NIL");
		   }

           if(valdat.datatype == 82) { // sqlite3_stmt
			 datx.long_str = SQLITEDBfields_get(valdat.sqlite_stmt);

             for(j=0; datx.long_str[j] != '\0'; j++) {
              // do nothing, need for counting max
             }

             datx.array_max = j;
             datx.isLongStr = 1;
             datx.datatype  = 10;

             /* printf("get stored data num: %d\n", datx.val ); */
           } else {
             Error("SQLITE_NAMAKOLOM: masukan data salah");
           }
         } else {
           Error("SQLITE_NAMAKOLOM: masukan data salah");
         } 


      return datx;
}

VAL_LABEL funcSQLITE_ISIDATA ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  VAL_LABEL tmpdat;
  int    j=0;
  char    class_tmpvar[MAX_STRING_LEN];
  int    num=0;

  memset(&datx, '\0', sizeof(datx));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

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

           // valdat = ValLabel( lex.detail.ident, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype = 82) { // sqlite_stmt
             tmpdat = valdat;

			 if(valdat.sqlite_stmt == NULL) {
               Error("SQLITE_ISIDATA Salah: Hasil SQLITE NIL");
		     }
           } else {
           Error("SQLITE_ISIDATA: masukan data salah");
           }
         } else {
           Error("SQLITE_ISIDATA: masukan data salah");
         } 

         // skip comma
		 getlex();
		 // printf("ident char : %c\n", lex.detail.ident[0]);
		 if(lex.detail.ident[0] != ',') {
           Error("SQLITE_ISIDATA: masukan data salah");
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
           Error("SQLITE_ISIDATA: masukan data salah");
           }
         } else {
           Error("SQLITE_ISIDATA: masukan data salah");
         } 

		 if(tmpdat.sqlite_stmt != NULL) {
			 datx.long_str = SQLITEDBrows_get(tmpdat.sqlite_stmt);

             for(j=0; datx.long_str[j] != '\0'; j++) {
              // do nothing, need for counting max
             }

             datx.array_max = j;
             datx.isLongStr = 1;
             datx.datatype  = 10;

             /* printf("get stored data num: %d\n", datx.val ); */
		 }
  
      return datx;
}

// /////////////////////////////////////////////////////////////////////////////


char** SQLITEDBfields_get(sqlite3_stmt  *sqlite_res)
{
   int  fieldcount = 0;

   char **arr = NULL; 
   int  n   = 0;    
   int  i   = 0;  
   char *buf=NULL;
   char *tp=NULL;

   char a_cell[1024];

	if (sqlite_res == NULL) {
           return NULL;
	}

	buf = (char*)malloc(strlen((char *)sqlite_res) + 1);
	if (buf == NULL) {
		return NULL;
	}
	strcpy(buf, (char *)sqlite_res);

    fieldcount = (int)sqlite3_column_count(sqlite_res);

        n = 0;
        for(i=0; i < fieldcount; i++) {
           char **a = (char**)realloc(arr, sizeof(*arr) * (n+3));
           memset(&a_cell, '\0', sizeof(a_cell));
		   sprintf(a_cell,"%s", sqlite3_column_name(sqlite_res, i));

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
	}

    memset(&a_cell, '\0', sizeof(a_cell));

	return arr;
}


char** SQLITEDBrows_get(sqlite3_stmt  *sqlite_res) {
   int  fieldcount = 0;

   char **arr = NULL; 
   int  n   = 0;    
   int  i   = 0;  
   int  j   = 0;  
   char *buf=NULL;
   char *tp=NULL;

   char a_cell[1024];


	if (sqlite_res == NULL) {
           return NULL;
	}

    fieldcount = (int)sqlite3_column_count(sqlite_res);
	// fetch next one
    sqlite3_step(sqlite_res);

    // printf(">>> column num %d \n", fieldcount);


	buf = (char*)malloc(strlen((char *)sqlite_res) + 1);
	if (buf == NULL) {
		return NULL;
	}
	strcpy(buf, (char *)sqlite_res);


        n = 0;
        for(i=0; i < fieldcount; i++) {
           char **a = (char**)realloc(arr, sizeof(*arr) * (n+3));
           memset(&a_cell, '\0', sizeof(a_cell));

		   sprintf(a_cell,"%s", sqlite3_column_text(sqlite_res, i)); 

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
	}

    memset(&a_cell, '\0', sizeof(a_cell));

	return arr;
}





