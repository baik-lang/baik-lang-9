// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

MVCPARSING keyMVCTutup (MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  char ident[MAX_IDENT_LEN];

  int  n=0;

  VAL_LABEL valdat, tmpdat;

  MVCPARSING par;
  
  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];


  memset(&par, '\0', sizeof(par));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  
  memset(&ident, '\0', sizeof(ident));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


          par = MVCgetlex(mvc_lex, mvc_pg);
          mvc_lex = par.mvc_lex;
          mvc_pg  =par.mvc_pg;

	  switch( mvc_lex.type )
	    {
	    case TYPE_IDENT:

              valdat = ValLabel(mvc_lex.detail.ident, 0, valdat, VAL_FLAG_SEARCH_R);

              // printf("get tutup type %d\n", valdat.datatype);
              // printf("get tutup file is open %d\n", valdat.isFileOpen);
              // printf("get tutup ident %s\n", valdat.ident);

              /* CLOSE FILE */
              if(valdat.datatype == 2) {
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

                  ValLabel( valdat.ident , sub_deep, valdat, VAL_FLAG_SEARCH_W );
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

                  ValLabel( valdat.ident , sub_deep, valdat, VAL_FLAG_SEARCH_W );
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

                  ValLabel( valdat.ident , sub_deep, valdat, VAL_FLAG_SEARCH_W );
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

                  ValLabel( valdat.ident , sub_deep, valdat, VAL_FLAG_SEARCH_W );
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

                  ValLabel( valdat.ident , sub_deep, valdat, VAL_FLAG_SEARCH_W );

                }
              #endif

              } else {
	            Error("variabel harus sebagai ARSIP/KONEKSIDB");
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

  return par;
  
}



