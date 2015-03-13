// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#include "oracle_common.h"

char** ORADBrows_get(OCI_Resultset *ora_res);
char** ORADBfields_get(OCI_Resultset *ora_res);

VAL_LABEL funcORADB_KONEKSI ()
{
  VAL_LABEL datx;
  int  n=0, i=0, j=0;

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0, idx2=0;                           // array index

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];
  char   dat_c[MAX_STRING_LEN];

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
             } else
             if(n == 1) {
               strcpy(dat_b, lex.detail.string);
             } else
             if(n == 2) {
               strcpy(dat_c, lex.detail.string);
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
               } else
               if(n == 1) {
                 strcpy(dat_b, valdat.str);
               } else
               if(n == 2) {
                 strcpy(dat_c, valdat.str);
               } 
             }

           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        /* printf("n:%d\n", n); */

        if(n==3) {
          /* 
          printf("a: %s\n", dat_a);     // tns_name
          printf("b: %s\n", dat_b);     // username
          printf("c: %s\n", dat_c);     // password
          */
		  datx.ora_conn = ora_connect(dat_a, dat_b, dat_c);

		  if(datx.ora_conn == NULL) {
            //writeLog("Koneksi Oracle DB Salah");
			datx.isOraOpen = 0;
          } else {
            //writeLog("Koneksi Oracle DB Okey");
			datx.isOraOpen = 1;
          }

          datx.datatype    = 71;                   /* Ora Conn  */

        } else {
          Error("ORADB_KONEKSI: masukan data salah");
        }


  return datx;
}

VAL_LABEL funcORADB_HASIL ()
{
  OCI_Statement  *st = NULL;
  VAL_LABEL datx;
  int  n=0, i=0, j=0;
  int  dat_num=0;

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0, idx2=0;                           // array index

  char   dat_a[MAX_STRING_LEN * 2];
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

  datx.val = 0; // set init result 0 - NG


        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             Error("ORADB_HASIL: masukan data salah");
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
                     Error("ORADB_HASIL: ukuran Untaian belum terdefinisi");

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
             if(valdat.datatype == 71) { // oracle conn
               if(n == 0) {
                 strcpy(dat_d, lex.detail.ident);

				 tmpdat = valdat;
                 tmpdat.ora_conn = valdat.ora_conn;
				 tmpdat.isOraOpen = valdat.isOraOpen;

				 // printf("get pg_conn\n");

				 if(valdat.ora_conn == NULL) {
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
          
          datx.ora_res = NULL;

		  st  = OCI_StatementCreate(tmpdat.ora_conn);
          OCI_ExecuteStmt(st, dat_a);

		  // below just for deletion only - not used(?)
          // printf("affected rows %d \n", OCI_GetAffectedRows(st));

		  datx.ora_res = OCI_GetResultset(st);

		  // keep var conn ??
		  datx.ora_conn    = tmpdat.ora_conn;
		  datx.isOraOpen   = tmpdat.isOraOpen;

		  // keep var stmt and sql ??
		  datx.ora_stmt    = st;
		  strcpy(datx.sql_tmp, dat_a);

		  datx.datatype    = 72;                   /* Oracle result  */

		  if(datx.ora_res  == NULL) {
		    // printf("Hasil Oracle DB NULL\n");
                    //writeLog("Hasil Oracle DB NULL");
			datx.val = -1;
		  } else {
		    // printf("Hasil Oracle DB OK\n");
		        datx.val = 1;  // OK
		  }

		  st = NULL;

          /* printf("stored data num: %d\n", (int)mysql_num_rows(datx.my_res) ); */
          memset(&tmpdat, '\0', sizeof(tmpdat));

        } else {
          Error("ORADB_HASIL: masukan data salah");
        }

  
  return datx;
}

VAL_LABEL funcORADB_TOTAL ()
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
           if(valdat.datatype == 72) { // oracle_result

		     if(valdat.ora_res == NULL) {
               Error("ORADB_TOTAL Salah: Hasil ORADB NIL");
			 } else {
               // printf("get ora_res not null, OK \n");
			 }

             while (OCI_FetchNext(valdat.ora_res)) {
              // do nothing
			 }

             datx.val= OCI_GetRowCount(valdat.ora_res);
             datx.datatype = 0;

             // keep stmt ??
			 datx.ora_stmt = valdat.ora_stmt;

             // Need Exec SQL again to keep first pos !!!
			 OCI_ExecuteStmt(valdat.ora_stmt, valdat.sql_tmp);

             // printf("get stored data num: %d\n", datx.val );

           } else {
           Error("ORADB_TOTAL: masukan data salah");
           }
         } else {
           Error("ORADB_TOTAL: masukan data salah");
         } 

    return datx;
}


VAL_LABEL funcORADB_RESULT_STATUS ()
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
           if(valdat.datatype == 72) { // oracle_result

	     if(valdat.ora_res == NULL) {
               Error("ORADB_TOTAL Salah: Hasil ORADB NIL");
             } else {
               // printf("get ora_res not null, OK \n");
	     }

             while (OCI_FetchNext(valdat.ora_res)) {
              // do nothing
	     }

             datx.val= valdat.val;  // passing result
             datx.datatype = 0;

             // keep stmt ??
		 datx.ora_stmt = valdat.ora_stmt;

             // Need Exec SQL again to keep first pos !!!
		 OCI_ExecuteStmt(valdat.ora_stmt, valdat.sql_tmp);

             // printf("get stored data num: %d\n", datx.val );

           } else {
           Error("ORADB_STATUS: masukan data salah");
           }
         } else {
           Error("ORADB_STATUS: masukan data salah");
         } 

    return datx;
}

VAL_LABEL funcORADB_NAMAKOLOM ()
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
  memset(&tmpstr, '\0', sizeof(tmpstr));

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
 
           // printf("kolom type %d\n", valdat.datatype);

           if(valdat.datatype == 72) {
			 valdat.ora_res = OCI_GetResultset(valdat.ora_stmt);

             get = ORADBfields_get(valdat.ora_res);

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
             Error("ORADB_NAMAKOLOM: masukan data salah");
           }
         } else {
           Error("ORADB_NAMAKOLOM: masukan data salah");
         } 


      return datx;
}

VAL_LABEL funcORADB_ISIDATA ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  int    j=0;
  char    class_tmpvar[MAX_STRING_LEN];

  char tmpstr[MAX_STRING_LEN];
  char **get=NULL;

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
  memset(&tmpstr, '\0', sizeof(tmpstr));

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
           if(valdat.datatype == 72) {
			 valdat.ora_res = OCI_GetResultset(valdat.ora_stmt);

             get = ORADBrows_get(valdat.ora_res);

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
           Error("ORADB_DATA: masukan data salah");
           }
         } else {
           Error("ORADB_DATA: masukan data salah");
         } 

  
      return datx;
}


char** ORADBrows_get(OCI_Resultset *ora_res) {
    int  rowcount = 0;
	int  fieldcount = 0;

   char **arr = NULL; 
   int  n   = 0;    
   int  i   = 0;  
   int  j   = 0;  
   char *buf=NULL;
   char *tp=NULL;

   char a_cell[1024];


	if (ora_res == NULL) {
           return NULL;
	}

    fieldcount = (int)OCI_GetColumnCount(ora_res);
	OCI_FetchNext(ora_res);

    // printf(">>> column num %d \n", fieldcount);

    rowcount = OCI_GetRowCount(ora_res);

	if (rowcount <= 0) {
           return NULL;
	}

	buf = (char*)malloc(strlen((char *)ora_res) + 1);
	if (buf == NULL) {
		return NULL;
	}
	strcpy(buf, (char *)ora_res);


        n = 0;
        for(i=0; i < fieldcount; i++) {
           char **a = (char**)realloc(arr, sizeof(*arr) * (n+3));
           memset(&a_cell, '\0', sizeof(a_cell));
		   sprintf(a_cell,"%s", OCI_GetString(ora_res, i+1)); /// ora get start from 1

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
      free(buf);
	}

    memset(&a_cell, '\0', sizeof(a_cell));

	return arr;
}

char** ORADBfields_get(OCI_Resultset *ora_res)
{
   int  fieldcount = 0;
   OCI_Column *col = NULL;

   char **arr = NULL; 
   int  n   = 0;    
   int  i   = 0;  
   char *buf=NULL;
   char *tp=NULL;

   char a_cell[1024];

	if (ora_res == NULL) {
           return NULL;
	}

	buf = (char*)malloc(strlen((char *)ora_res) + 1);
	if (buf == NULL) {
		return NULL;
	}
	strcpy(buf, (char *)ora_res);

    fieldcount = (int)OCI_GetColumnCount(ora_res);

        n = 0;
        for(i=0; i < fieldcount; i++) {
           char **a = (char**)realloc(arr, sizeof(*arr) * (n+3));
           memset(&a_cell, '\0', sizeof(a_cell));

           col = OCI_GetColumn(ora_res, i+1);
		   sprintf(a_cell,"%s", OCI_GetColumnName(col));

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



