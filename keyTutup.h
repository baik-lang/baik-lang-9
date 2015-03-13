// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// Last Update : 10-10-2015

void keyTutup ()
{
  char ident[MAX_IDENT_LEN];

  int  n=0;

  VAL_LABEL valdat, tmpdat;
  
  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];


  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  
  memset(&ident, '\0', sizeof(ident));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_IDENT:
              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("get tutup type %d\n", valdat.datatype);
              // printf("get tutup file is open %d\n", valdat.isFileOpen);
              // printf("get tutup ident %s\n", valdat.ident);

              /* CLOSE SOCKET */
              if(valdat.datatype == 4 || valdat.datatype == 5) {
                // printf("tutup soket\n");

                #ifdef WINDOWS
	              closeSocket( valdat.sock ); 
                #else
                  close( valdat.sock );
                  /* printf("tutup soket\n"); */
                #endif

                ValLabel( valdat.ident, sub_deep, valdat, VAL_FLAG_SEARCH_W );
                /* printf("socket closed\n"); */

              /* CLOSE FILE */
              } else if(valdat.datatype == 2) {
                if(valdat.isFileOpen == 1) {
		          fclose(valdat.filedata);
                  valdat.isFileOpen = 0;

                  ValLabel( valdat.ident, sub_deep, valdat, VAL_FLAG_SEARCH_W );
                  // printf("file closed\n");

                }


              #ifdef USE_MYSQL
              /* CLOSE MYSQL */
              } else if(valdat.datatype == 11) {
                if(valdat.isMysqlOpen == 1) {
                  do_disconnect(valdat.my_conn);
                  valdat.isMysqlOpen = 0;

                  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  if(currentClass != NULL && strlen(currentClass) > 0) {
                    sprintf(class_tmpvar, "%s->%s", currentClass, valdat.ident);
                    ValLabel( class_tmpvar , class_sub_deep, valdat, VAL_FLAG_SEARCH_W );
				  } else {
                    ValLabel( valdat.ident , sub_deep, valdat, VAL_FLAG_SEARCH_W );
				  }
                  // printf("mysql closed %s\n", valdat.ident);

                }
              #endif

              #ifdef USE_PGSQL
				/* CLOSE PostgreSql */
              } else if(valdat.datatype == 61) {  // pgsql_conn
				// printf("con is open : %d \n", valdat.isPgdbOpen);

				if(valdat.isPgdbOpen == 1) {
				  pgdb_disconnect(valdat.pg_conn);
				  valdat.isPgdbOpen = 0;
				  valdat.pg_res     = NULL;
				  valdat.pg_conn    = NULL;

				  // conn
				  valdat.datatype = 61;

                  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  if(currentClass != NULL && strlen(currentClass) > 0) {
                    sprintf(class_tmpvar, "%s->%s", currentClass, valdat.ident);
                    ValLabel( class_tmpvar , class_sub_deep, valdat, VAL_FLAG_SEARCH_W );
				  } else {
                    ValLabel( valdat.ident , sub_deep, valdat, VAL_FLAG_SEARCH_W );
				  }

                  // printf("pgsql closed\n");

                }

              } else if(valdat.datatype == 62) { // pgsql_result
				// printf("con is open : %d \n", valdat.isPgdbOpen);

				if(valdat.isPgdbOpen == 1) {
				  pgdb_disconnect(valdat.pg_conn);
				  valdat.isPgdbOpen = 0;
				  valdat.pg_res     = NULL;
				  valdat.pg_conn    = NULL;

                  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  if(currentClass != NULL && strlen(currentClass) > 0) {
                    sprintf(class_tmpvar, "%s->%s", currentClass, valdat.ident);
                    ValLabel( class_tmpvar , class_sub_deep, valdat, VAL_FLAG_SEARCH_W );
				  } else {
                    ValLabel( valdat.ident , sub_deep, valdat, VAL_FLAG_SEARCH_W );
				  }
                  // printf("pgsql closed\n");

                }
              #endif

              #ifdef USE_OCI
              /* CLOSE ORACLE */
              } else if(valdat.datatype == 71) {
                if(valdat.isOraOpen == 1) {
                  ora_disconnect(valdat.ora_conn);
                  valdat.isOraOpen = 0;

                  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  if(currentClass != NULL && strlen(currentClass) > 0) {
                    sprintf(class_tmpvar, "%s->%s", currentClass, valdat.ident);
                    ValLabel( class_tmpvar , class_sub_deep, valdat, VAL_FLAG_SEARCH_W );
				  } else {
                    ValLabel( valdat.ident , sub_deep, valdat, VAL_FLAG_SEARCH_W );
				  }
                  // printf("oracle closed\n");
                }
              #endif

              #ifdef USE_SQLITE
              /* CLOSE SQLITE */
              } else if(valdat.datatype == 81) {
				if(valdat.isSqliteOpen == 1) {
				  sqlite_disconnect(valdat.sqlite_conn);
				  valdat.isSqliteOpen = 0;

                  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
                  if(currentClass != NULL && strlen(currentClass) > 0) {
                    sprintf(class_tmpvar, "%s->%s", currentClass, valdat.ident);
                    ValLabel( class_tmpvar , class_sub_deep, valdat, VAL_FLAG_SEARCH_W );
				  } else {
                    ValLabel( valdat.ident , sub_deep, valdat, VAL_FLAG_SEARCH_W );
				  }
                  // printf("sqlite closed\n");

                }
              #endif

              } else {
	            Error("variabel harus sebagai SOKET/ARSIP/KONEKSIDB");
              }
	      break;
	    default:
	      Error("kode perintah TUTUP salah");
	    }


  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

}



