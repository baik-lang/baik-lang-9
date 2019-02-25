// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2016
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// Last Update : Feb 13, 2016

#include "my_common.h"

char** DBfields_get(MYSQL_RES *my_res);
char** DBrows_get(MYSQL_RES *my_res);

VAL_LABEL funcMYSQL_KONEKSI ()
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
                     Error("MYSQL_KONEKSI: ukuran Untaian belum terdefinisi");

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
               valdat = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
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
          datx.my_conn = do_connect(dat_a, dat_b, dat_c, dat_d, dat_num, "my_sock", 0);

          if(datx.my_conn == NULL) {
			// printf("Koneksi Mysql DB Nil : Salah");
            datx.isMysqlOpen = 0;
          } else {
            // writeLog("Koneksi Mysql DB Okey");
            datx.isMysqlOpen = 1;
          }

          datx.datatype    = 11;                   /* Mysql Conn  */

        } else {
          Error("MYSQL_KONEKSI: masukan data salah");
        }


  return datx;
}

VAL_LABEL funcMYSQL_HASIL ()
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

  //printf("inside funcMYSQL_HASIL <BR>\n");
  datx.val = 0;  // set init result 0 (NG)

        n = 0; i = 0;
        do {
           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_NUM) {
             Error("MYSQL_HASIL: masukan data salah");
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
                     Error("MYSQL_HASIL: ukuran Untaian belum terdefinisi");

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
               valdat = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

             // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             if(valdat.datatype == 3) {
               if(n == 1) {
                 strcpy(dat_a, valdat.str);
               }
             } else
             if(valdat.datatype == 11) {
               if(n == 0) {
                 strcpy(dat_d, lex.detail.ident);
                 tmpdat.my_conn = valdat.my_conn;
               }
             }

           }

           n++;

           getlex();

        }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

        ungetlex();

        //printf("MYSQL_HASIL param n:%d <BR>\n", n); 

        if(n==2) {

          //printf("sql: %s <BR>\n", dat_a);     // long sqlstr
          //printf("con: %s <BR>\n", dat_d);     // conn

          if (mysql_query(tmpdat.my_conn, dat_a))  {
            printf("Salah menjalankan SQL: %s !\n", dat_a);
            do_disconnect(tmpdat.my_conn);
            Error("MYSQL_HASIL: gagal");
          }
          // printf("exec SQL OK <BR>\n");

          datx.my_res= mysql_store_result(tmpdat.my_conn);
          datx.datatype    = 12;                   /* Mysql res  */
          datx.val         = 1;                    // result OK

          /* printf("stored data num: %d\n", (int)mysql_num_rows(datx.my_res) ); */
          memset(&tmpdat, '\0', sizeof(tmpdat));

        } else {
          printf("MYSQL_HASIL: masukan data salah !\n");        
          Error("MYSQL_HASIL: masukan data salah");
        }

  
  return datx;
}

VAL_LABEL funcMYSQL_TOTAL ()
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
             valdat = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 12) {
             datx.val = (int)mysql_num_rows(valdat.my_res);
             datx.datatype = 0;

             /* printf("get stored data num: %d\n", datx.val ); */
           } else {
           Error("MYSQL_TOTAL: masukan data salah");
           }
         } else {
           Error("MYSQL_TOTAL: masukan data salah");
         } 

    return datx;
}


VAL_LABEL funcMYSQL_RESULT_STATUS ()
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
             valdat = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(valdat.datatype == 12) {
             datx.val = valdat.val;       // passing result
             datx.datatype = 0;

             /* printf("get stored data num: %d\n", datx.val ); */
           } else {
           Error("MYSQL_STATUS: masukan data salah");
           }
         } else {
           Error("MYSQL_STATUS: masukan data salah");
         } 

    return datx;
}


VAL_LABEL funcMYSQL_NAMAKOLOM ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  int    j=0;
  char **get=NULL;
  char   class_tmpvar[MAX_STRING_LEN];
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
             valdat = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
 
           // printf("kolom type %d\n", valdat.datatype);

           if(valdat.datatype == 12) {
             get = DBfields_get(valdat.my_res);

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
             Error("MYSQL_NAMAKOLOM: masukan data salah");
           }
         } else {
           Error("MYSQL_NAMAKOLOM: masukan data salah");
         } 


      return datx;
}


VAL_LABEL funcMYSQL_ISIDATA ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;
  int  j=0;
  char class_tmpvar[MAX_STRING_LEN];

  char tmpstr[MAX_STRING_LEN];
  char **get=NULL;

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
  memset(&tmpstr, '\0', sizeof(tmpstr));

         getlex();
		 // printf("lex ident: %s\n", lex.detail.ident);
         // printf("lex type : %d\n", lex.type);

         if(lex.type == TYPE_IDENT) {

           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
             //printf("construct class var: %s\n", class_tmpvar);
             valdat = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

		   //printf("get valdat ident : %s <BR>\n", valdat.ident);
		   //printf("get valdat dt type : %d <BR>\n", valdat.datatype);

		   mysql_renban++;
		   datx.datatype = 8;                                   // save as real array
		   datx.array_s = createRenban(mysql_renban);

           if(valdat.datatype == 12) {

			   get = DBrows_get(valdat.my_res);

			   for (j = 0; get[j] != '\0'; j++) {
				   //printf("ggggggggggggggggggggggggggggggggggg %d <BR> \n", j);

				   // Array String
				   memset(&tmpstr, '\0', sizeof(tmpstr));
				   tmpdat.datatype = 8;
				   strcpy(tmpdat.array_name, "mysql_DBrows");

				   tmpdat = ValLabel(tmpdat.array_name, 1, tmpdat, VAL_FLAG_SEARCH_R);

				   get_mysql_str_array(tmpdat, j, (char *)&tmpstr);

				   //printf("get mysql str array : %i %s <BR>\n", j, tmpstr);
				   //printf("mysql #2 renban %d <BR>\n", mysql_renban);

				   save_str_array(datx, j, tmpstr);
			   }

             datx.array_max = j;

             split_free(get);

             /* printf("get stored data num: %d\n", datx.val ); */
           } else {
           Error("MYSQL_DATA: masukan data salah");
           }
         } else {
           Error("MYSQL_DATA: masukan data salah");
         } 

		 //printf("datx dt type : %d <BR>\n", datx.datatype);
  
      return datx;
}


// ///////////////////////////////////////////////////////////////////////////

/* ****************************************************** */
/* Mysql handle */
/* ****************************************************** */

char** DBfields_get(MYSQL_RES *my_res)
{
   MYSQL_FIELD *my_fd = NULL;                  //MYSQL_NAMAKOLOM

   char **arr = NULL; 
   int  n   = 0;    
   int  i   = 0;  
   char *buf=NULL;
   char *tp=NULL;

	if (my_res == NULL) {
           return NULL;
	}

	buf = (char*)malloc(strlen((char *)my_res) + 1);
	if (buf == NULL) {
		return NULL;
	}
	strcpy(buf, (char *)my_res);


        n = 0;
        for(i=0; my_fd=mysql_fetch_field(my_res); i++) {
           char **a = (char**)realloc(arr, sizeof(*arr) * (n+3));
           if(my_fd->name != NULL) {
                tp = (char*)malloc(strlen(my_fd->name) + 1);
                strcpy(tp, my_fd->name);

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

        my_fd = NULL;

        // printf("res %s\n", arr[0]);
        // printf("res %s\n", arr[1]);

	return arr;
}

char** DBrows_get(MYSQL_RES *my_res)
{
	VAL_LABEL valdat;
	char   tmpstr[MAX_STRING_LEN];

	MYSQL_ROW   my_row = NULL;    //MYSQL_DATABARIS
	int         rowcount = 0;

	char **arr = NULL;
	int  n = 0;
	int  i = 0;
	char *buf = NULL;
	char *tp = NULL;

	if (my_res == NULL) {
		return NULL;
	}

	//printf("*** DBrows_get ...%d <BR>\n", mysql_renban);

	memset(&tmpstr, '\0', sizeof(tmpstr));
	memset(&valdat, '\0', sizeof(valdat));
	valdat.val = -1;
	valdat.array_i = '\0';
	valdat.array_d = '\0';
	valdat.datatype = -1;

//	if (mysql_renban != '\0')
		mysql_renban++;
//	else
//		mysql_renban = 0;

	if (mysql_renban > 9999) {
		mysql_renban = 0;
	}

	//printf("after ++, mysql renban %d <BR>\n", mysql_renban);

	// ///////////////////////////////////////////////////////
	// create STRING array
	// ///////////////////////////////////////////////////////
	memset(&mysql_TmpStrBox, '\0', sizeof(mysql_TmpStrBox));
	memset(&mysql_TmpStrBox.var.array_name, '\0', sizeof(mysql_TmpStrBox.var.array_name));
	strcpy(mysql_TmpStrBox.var.array_name, "mysql_DBrows");
	// printf("start createRenban \n");
	mysql_TmpStrBox.var.stackid = createRenban(mysql_renban);       // create stackid here
	valdat.array_s = mysql_TmpStrBox.var.stackid;                   // keep stackid
	//printf("mysql renban %d <BR>\n", mysql_renban);
	//printf("STACKID %d <BR>\n", mysql_TmpStrBox.var.stackid);

	if (stackStr_getID(mysql_TmpStrBox.var) >= 0.0) {
	//	printf("nama variabel sudah terpakai! \n");
	}
	else {
		stackStr_addFirst(mysql_TmpStrBox.var);
	}
	
	/* Store Array Initialization to Node memory tree */
	valdat.datatype = 8;
	strcpy(valdat.array_name, "baik_mysql_DBrows");
	ValLabel(valdat.array_name, 1, valdat, VAL_FLAG_SEARCH_W);

	rowcount = (int)mysql_num_rows(my_res);
	my_row = mysql_fetch_row(my_res);

	/* printf(">>> data num %d \n", rowcount); */

	if (rowcount <= 0) {
		return NULL;
	}

	buf = (char*)malloc(strlen((char *)my_row) + 1);
	if (buf == NULL) {
		return NULL;
	}
	strcpy(buf, (char *)my_row);

	/* printf(">>> row num %d \n", (int)mysql_num_fields(my_res)); */

	n = 0;
	for (i = 0; i < (int)mysql_num_fields(my_res); i++) {
		char **a = (char**)realloc(arr, sizeof(*arr) * (n + 3));
		if (my_row[i] != NULL && strlen(my_row[i])>0) {
			tp = (char*)malloc(strlen(my_row[i]) + 1);
			if (strlen(my_row[i]) > 0) {
				strcpy(tp, my_row[i]);

				memset(&tmpstr, '\0', sizeof(tmpstr));
				strcpy(tmpstr, my_row[i]);

				memset(&valdat, '\0', sizeof(valdat));
				valdat.datatype = 8;
				strcpy(valdat.array_name, "baik_mysql_DBrows");
				save_mysql_str_array(valdat, i, tmpstr);
				
				//printf("mysql renban %d <BR>\n", mysql_renban);
				//printf("Save mysql Str Array %d data: %s <BR>\n", i, my_row[i]);
			}
			else {
				strcpy(tp, "");
			}

			a[++n] = tp;
			arr = a;
		}
		else {
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
	else {
		free(buf);
	}

	my_row = NULL;
	return arr;
}
