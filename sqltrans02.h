// //////////////////////////////////////////////////////////////////////
// Penerjemah SQL untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
//
// Last Update : 2010/06/29 - Support MultiThread Parsing
// //////////////////////////////////////////////////////////////////////

// -----------------------------------------------
// Padanan Kata-Kata SQL dengan Translasinya
// -----------------------------------------------
//   SQL Keyword          |   Translasi SQL
// -----------------------------------------------
//   SELECT                      AMBIL
//   SELECT DISTINCT             AMBIL TUNGGAL
//   FROM                        DARI
//   INSERT INTO                 MASUKKAN
//   VALUES                      BERNILAI
//   UPDATE                      PERBARUI
//   SET                         SET
//   DELETE                      HAPUS
//   TRUNCATE TABLE              PANGKAS TABEL
//   CREATE TABLE                BUAT TABEL
//   WHERE                       DIMANA
//   AND                         DAN
//   OR                          ATAU
//   NOT                         BUKAN
//   LIKE                        SEPERTI
//   IS                          IALAH
//   NULL                        NIL
//   NVL (Oracle)                JIKA_NIL
//   ISNULL (MsSQL)              JIKA_KOSONG
//   EXISTS                      ADA
//   ALL                         SEMUANYA
//   ORDER BY                    DENGAN URUTAN
//   GROUP BY                    DENGAN GRUP
//   ASC                         MENANJAK
//   DESC                        MENURUN
//   IN                          DALAM
//   MERGE INTO                  LEBURKAN
//   HAVING                      MEMILIKI
//   SUM                         JUMLAH
//   AVG                         RATA-RATA
//   COUNT                       TOTAL
//   TOP                         ATAS
//   LIMIT                       BATASAN
//   INNER JOIN                  HUBUNGAN DALAM
//   CROSS JOIN                  HUBUNGAN SILANG
//   OUTER JOIN                  HUBUNGAN LUAR
//   LEFT OUTER JOIN             HUBUNGAN LUAR KIRI
//   RIGHT OUTER JOIN            HUBUNGAN LUAR KANAN
//   FULL OUTER JOIN             HUBUNGAN LUAR PENUH
//   JOIN                        HUBUNGAN
//   SYSDATE                     TANGGALAN
//   DATE_FORMAT                 FORMAT_TANGGAL
//   TIME_FORMAT                 FORMAT_WAKTU
//   TO_CHAR                     KE_HURUF
//   TO_DATE                     KE_TANGGAL
//   DUMMY                       TABEL_SISTEM
//   CASE                        PILIH
//   WHEN                        KETIKA
//   THEN                        MAKA
//   ELSE                        LAINNYA
//   END                         SELESAI
//   AS                          SEBAGAI
//   UNION                       GABUNGAN
//   INTERSECT                   POTONGAN
// -----------------------------------------------
//
//=== Contoh 1
//  kalimat sql : AMBIL nama, sektor, TOTAL(nama) DARI Tbl_Sales DENGAN GRUP sektor
//  SQL stmt : select nama ,sektor ,count (nama ) from Tbl_Sales GROUP BY sektor
//
//=== Contoh 2
//  kalimat sql : MASUKKAN p_name (no, nama, alamat) BERNILAI (1, 'Haris', 'Tokyo-Jepang')
//  SQL stmt : insert into p_name (no ,nama ,alamat )values (1 ,'Haris' ,'Tokyo-Jepang' )
//
//=== Contoh 3
//  kalimat sql : BUAT TABEL tbl_barang ( nomer INTEGER BUKAN NIL, nama  VARCHAR(3, kunci utama(nomer) )
//  SQL stmt : create table tbl_barang (nomer INTEGER NOT NULL ,nama VARCHAR (32 ),PRIMARY KEY (nomer ))
//
//=== Contoh 4
//  kalimat sql : PERBARUI tbl_sche_group SET namaproyek = 'myprojectname' DIMANA namagrup = 'grname'
//  SQL stmt : update tbl_sche_group SET namaproyek ='myprojectname' where namagrup ='grname'

// //////////////////////////////////////////////////////////////////////


char *SQLInterpreter( char perintah[4096] );



// ==================================


char *SQLInterpreter( char perintah[4096] )
{
  // create sql_lex and sql_pg in Lokal, not Global
  SQL_LEX_T sql_lex;  /* getlex関数が呼ばれた時に値がいれられる */
  SQL_S_ADDR sql_pg;  /* 現在実行しているプログラムの位置を表す */

  PARSING par;

  char SQLstmt[4096];
  char stmt[MAX_IDENT_LEN];
  char *retSQL = NULL;

  char ident[MAX_IDENT_LEN];

  memset( &sql_lex, 0, sizeof(sql_lex) );
  memset( &sql_pg, 0, sizeof(sql_pg) );

  /* 最初に変数とラベルの探索木のトップを生成しておく */
  if( SQLValLabel(sql_lex, sql_pg, "sqlr00t", 0, SQL_VAL_FLAG_START ) )
    SQLError(sql_lex, sql_pg, "Salah: Memori untuk sql tidak beres!");

  memset( &SQLstmt, 0, sizeof(SQLstmt) );
  
  /* lexをゼロクリア */
  memset( &sql_lex, 0, sizeof(SQL_LEX_T) );

  /* ソースコードを先頭に戻す */
  sql_pg.pt      = 0;
  sql_pg.back_pt = 0;

  /* ソースコードを読込む */
  sql_pg.source = (char *)malloc((int)strlen(perintah)+1);
  sql_pg.source = perintah;

  // printf("source perintah:%s\n", perintah);

  /* ここからプログラムの解釈実行を始める */
  do{
    // clear tmp stmt
    memset( &stmt, 0, sizeof(stmt) );

    /* データの取得 */
    par = SQLgetlex(sql_lex, sql_pg);
    sql_lex = par.sql_lex;
    sql_pg  =par.sql_pg;

    // printf("first lex:%s\n", sql_lex.detail.ident);

    switch( sql_lex.type )
      {

      case _SQLEND:
	/* プログラムの終了 */
	sql_lex.type = _SQL_EOF;
	break;

      case TYPE_SQL_SYM:
          //printf("%s", sql_lex.detail.ident);
          strcpy(stmt, sql_lex.detail.ident);
          strcat(SQLstmt, stmt);
	break;

      case TYPE_SQL_STR:
          //printf("'%s' ", sql_lex.detail.string);
          #ifdef WIN32
           #ifndef S_SPLINT_S
           sprintf_s(stmt, sizeof(stmt),"'%s' ", sql_lex.detail.ident);
           #else
           snprintf(stmt, sizeof(stmt),"'%s' ", sql_lex.detail.ident);
           #endif
          #else
          snprintf(stmt, sizeof(stmt),"'%s' ", sql_lex.detail.ident);
          #endif

          strcat(SQLstmt, stmt);
	break;

      case TYPE_SQL_IDENT:
	/* translasi */
        memset( &ident, 0, sizeof(ident) );
	strcpy( ident, sql_lex.detail.ident );

        if(! strcmp(ident, "ambil") || ! strcmp(ident, "AMBIL")) {
          par = SQLgetlex(sql_lex, sql_pg);
          sql_lex = par.sql_lex;
          sql_pg  =par.sql_pg;
          if(! strcmp(sql_lex.detail.string, "tunggal") || ! strcmp(sql_lex.detail.string, "TUNGGAL")) {
            //printf("select distinct ");
            strcpy(stmt,"select distinct ");
            strcat(SQLstmt, stmt);
          } else {
            //printf("select %s ", sql_lex.detail.ident);
            #ifdef WIN32
             #ifndef S_SPLINT_S
             sprintf_s(stmt, sizeof(stmt),"select %s ",  sql_lex.detail.string);
             #else
             snprintf(stmt, sizeof(stmt),"select %s ",  sql_lex.detail.string);
             #endif
            #else
            snprintf(stmt, sizeof(stmt),"select %s ",  sql_lex.detail.string);
            #endif

            strcat(SQLstmt, stmt);
          }
        } else

        if(! strcmp(ident, "dari") || ! strcmp(ident, "DARI")) {
          //printf(" from %s ", sql_lex.detail.ident);
          strcpy(stmt," from ");
          strcat(SQLstmt, stmt);
        } else

        if(! strcmp(ident, "masukkan") || ! strcmp(ident, "MASUKKAN") ) {
          //printf("insert into ");
          strcpy(stmt,"insert into ");
          strcat(SQLstmt, stmt);
        } else

        if(! strcmp(ident, "leburkan") || ! strcmp(ident, "LEBURKAN")) {
          //printf("merge into ");
          strcat(SQLstmt, "merge into ");
        } else

        if(! strcmp(ident, "bernilai") || ! strcmp(ident, "BERNILAI")) {
          //printf("values ");
          strcat(SQLstmt, "values ");
        } else 

        if(! strcmp(ident, "perbarui") || ! strcmp(ident, "PERBARUI")) {
          //printf("update ");
          strcat(SQLstmt, "update ");
        } else

        if(! strcmp(ident, "hapus") || ! strcmp(ident, "HAPUS")) {
          //printf("delete ");
          strcat(SQLstmt, "delete ");
        } else

        if(! strcmp(ident, "pangkas") || ! strcmp(ident, "PANGKAS")) {
          par = SQLgetlex(sql_lex, sql_pg);
          sql_lex = par.sql_lex;
          sql_pg  =par.sql_pg;
          if(! strcmp(sql_lex.detail.string, "tabel")) {
            //printf("truncate table ");
            strcat(SQLstmt, "truncate table ");
          }
        } else

        if(! strcmp(ident, "buat") || ! strcmp(ident, "BUAT")) {
          par = SQLgetlex(sql_lex, sql_pg);
          sql_lex = par.sql_lex;
          sql_pg  =par.sql_pg;
          if(! strcmp(sql_lex.detail.string, "tabel") || ! strcmp(sql_lex.detail.string, "TABEL")) {
            // printf("create table ");
            strcat(SQLstmt, "create table ");
          }
        } else

        if(! strcmp(ident, "kunci") || ! strcmp(ident, "KUNCI")) {
          par = SQLgetlex(sql_lex, sql_pg);
          sql_lex = par.sql_lex;
          sql_pg  =par.sql_pg;
          if(! strcmp(sql_lex.detail.string, "utama") || ! strcmp(sql_lex.detail.string, "UTAMA")) {
            // printf("PRIMARY KEY ");
            strcat(SQLstmt, "PRIMARY KEY ");
          }
        } else

        if(! strcmp(ident, "dimana") || ! strcmp(ident, "DIMANA")) {
          par = SQLgetlex(sql_lex, sql_pg);
          sql_lex = par.sql_lex;
          sql_pg  =par.sql_pg;
          if(sql_lex.type != TYPE_SQL_SYM) {
            //printf("where %s ", sql_lex.detail.ident);
            #ifdef WIN32
             #ifndef S_SPLINT_S
             sprintf_s(stmt, sizeof(stmt),"where %s ", sql_lex.detail.ident);
             #else
             snprintf(stmt, sizeof(stmt),"where %s ", sql_lex.detail.ident);
             #endif
            #else
            snprintf(stmt, sizeof(stmt),"where %s ", sql_lex.detail.ident);
            #endif

            strcat(SQLstmt, stmt);
          } else {
            //printf("where %s ", sql_lex.detail.ident);
            #ifdef WIN32
             #ifndef S_SPLINT_S
             sprintf_s(stmt, sizeof(stmt),"where %s ", sql_lex.detail.ident);
             #else
             snprintf(stmt, sizeof(stmt),"where %s ", sql_lex.detail.ident);
             #endif
            #else
            snprintf(stmt, sizeof(stmt),"where %s ", sql_lex.detail.ident);
            #endif

            strcat(SQLstmt, stmt);
          }
        } else

        if(! strcmp(ident, "set") || ! strcmp(ident, "SET")) {
          //printf("and %s ", sql_lex.detail.ident);
          strcpy(stmt,"SET ");
          strcat(SQLstmt, stmt);
        } else


        if(! strcmp(ident, "dan") || ! strcmp(ident, "DAN")) {
          //printf("and %s ", sql_lex.detail.ident);
          strcpy(stmt,"and ");
          strcat(SQLstmt, stmt);
        } else

        if(! strcmp(ident, "atau") || ! strcmp(ident, "ATAU")) {
          //printf("or %s ", sql_lex.detail.ident);
          strcpy(stmt,"or ");
          strcat(SQLstmt, stmt);
        } else

        if(! strcmp(ident, "ialah") || ! strcmp(ident, "IALAH")) {
          //printf("is ");
          strcat(SQLstmt, "is ");
        } else 

        if(! strcmp(ident, "kosong") || ! strcmp(ident, "nil") ||
           ! strcmp(ident, "KOSONG") || ! strcmp(ident, "NIL")) {
          //printf("NULL ");
          strcat(SQLstmt,"NULL ");
        } else 

        if(! strcmp(ident, "jika_nil") || ! strcmp(ident, "JIKA_NIL")) {    // oracle
          //printf("NVL ");
          strcat(SQLstmt,"NVL ");
        } else 

        if(! strcmp(ident, "jika_kosong") || ! strcmp(ident, "JIKA_KOSONG")) { // sql server
          //printf("ISNULL ");
          strcat(SQLstmt,"ISNULL ");
        } else 

        if(! strcmp(ident, "ada") || ! strcmp(ident, "ADA")) {
          //printf(" EXISTS ");
          strcat(SQLstmt, " EXISTS ");
        } else 

        if(! strcmp(ident, "semuanya") || ! strcmp(ident, "SEMUANYA")) {
          //printf(" ALL ");
          strcat(SQLstmt, " ALL ");
        } else 

        if(! strcmp(ident, "bukan") || ! strcmp(ident, "BUKAN")) {
          //printf("NOT ");
          strcat(SQLstmt,"NOT ");
        } else 

        if(! strcmp(ident, "seperti") || ! strcmp(ident, "SEPERTI")) {
          //printf("like ");
          strcat(SQLstmt,"like ");
        } else 

        if(! strcmp(ident, "dengan") || ! strcmp(ident, "DENGAN")) {
          par = SQLgetlex(sql_lex, sql_pg);
          sql_lex = par.sql_lex;
          sql_pg  =par.sql_pg;

          strcpy( ident, sql_lex.detail.string );
          if(! strcmp(sql_lex.detail.string, "urutan") || ! strcmp(ident, "URUTAN")) {
            //printf("ORDER BY ");
            strcat(SQLstmt,"ORDER BY ");
          } else
          if(! strcmp(sql_lex.detail.string, "grup") || ! strcmp(ident, "GRUP")) {
            //printf("GROUP BY ");
            strcat(SQLstmt,"GROUP BY ");
          }
        } else 

        if(! strcmp(ident, "menanjak") || ! strcmp(ident, "MENANJAK")) {
          //printf("ASC ");
          strcat(SQLstmt,"ASC ");
        } else 

        if(! strcmp(ident, "menurun") || ! strcmp(ident, "MENURUN")) {
          //printf("DESC ");
          strcat(SQLstmt,"DESC ");
        } else 

        if(! strcmp(ident, "dalam") || ! strcmp(ident, "DALAM")) {
          //printf("IN ");
          strcat(SQLstmt,"IN ");
        } else 

        if(! strcmp(ident, "memiliki") || ! strcmp(ident, "MEMILIKI")) {
          //printf("having ");
          strcat(SQLstmt,"having ");
        } else 

        if(! strcmp(ident, "jumlah") || ! strcmp(ident, "JUMLAH")) {
          //printf("sum ");
          strcat(SQLstmt,"sum ");
        } else 

        if(! strcmp(ident, "rata-rata") || ! strcmp(ident, "RATA-RATA")) {
          //printf("avg ");
          strcat(SQLstmt,"avg ");
        } else 

        if(! strcmp(ident, "total") || ! strcmp(ident, "TOTAL")) {
          //printf("count ");
          strcat(SQLstmt,"count ");
        } else 

        if(! strcmp(ident, "dalam") || ! strcmp(ident, "DALAM")) {
          //printf("IN ");
          strcat(SQLstmt,"IN ");
        } else 

        if(! strcmp(ident, "atas") || ! strcmp(ident, "ATAS")) {
          //printf("top ");
          strcat(SQLstmt,"top ");
        } else 

        if(! strcmp(ident, "batasan") || ! strcmp(ident, "BATASAN")) {
          //printf("limit ");
          strcat(SQLstmt,"limit ");
        } else 

        if(! strcmp(ident, "hubungan") || ! strcmp(ident, "HUBUNGAN")) {
          par = SQLgetlex(sql_lex, sql_pg);
          sql_lex = par.sql_lex;
          sql_pg  =par.sql_pg;

          strcpy( ident, sql_lex.detail.string );
          if(! strcmp(sql_lex.detail.string, "dalam") || ! strcmp(ident, "DALAM")) {
            //printf("inner join ");
            strcat(SQLstmt,"inner join ");
          } else
          if(! strcmp(sql_lex.detail.string, "silang") || ! strcmp(ident, "SILANG")) {
            //printf("cross join ");
            strcat(SQLstmt,"cross join ");
          } else
          if(! strcmp(sql_lex.detail.string, "luar") || ! strcmp(ident, "LUAR")) {
            memset( &par, 0, sizeof(par) );
            par = SQLgetlex(sql_lex, sql_pg);
            sql_lex = par.sql_lex;
            sql_pg  =par.sql_pg;
            if(! strcmp(sql_lex.detail.string, "kiri") || ! strcmp(ident, "KIRI")) {
              //printf("left outer join ");
              strcat(SQLstmt,"left outer join ");
            } else
            if(! strcmp(sql_lex.detail.string, "kanan") || ! strcmp(ident, "KANAN")) {
              //printf("right outer join ");
              strcat(SQLstmt,"right outer join ");
            } else
            if(! strcmp(sql_lex.detail.string, "penuh") || ! strcmp(ident, "PENUH")) {
              //printf("full outer join ");
              strcat(SQLstmt,"full outer join ");
            } else {
              //printf("outer join ");
              strcat(SQLstmt,"outer join ");
            }
          } else {
            //printf("join ");
            strcat(SQLstmt,"join ");
          }
        } else 

        if(! strcmp(ident, "tanggalan") || ! strcmp(ident, "TANGGALAN")) {
          //printf("SYSDATE ");
          strcat(SQLstmt,"SYSDATE ");
        } else 

        if(! strcmp(ident, "format_tanggal") || ! strcmp(ident, "FORMAT_TANGGAL")) {
          //printf("DATE_FORMAT ");
          strcat(SQLstmt,"DATE_FORMAT ");
        } else 

        if(! strcmp(ident, "format_waktu") || ! strcmp(ident, "FORMAT_WAKTU")) {
          //printf("TIME_FORMAT ");
          strcat(SQLstmt,"TIME_FORMAT ");
        } else 

        if(! strcmp(ident, "ke_huruf") || ! strcmp(ident, "KE_HURUF")) {
          //printf("TO_CHAR ");
          strcat(SQLstmt,"TO_CHAR ");
        } else 

        if(! strcmp(ident, "ke_tanggal") || ! strcmp(ident, "KE_TANGGAL")) {
          //printf("TO_DATE ");
          strcat(SQLstmt,"TO_DATE ");
        } else 

        if(! strcmp(ident, "tabel_sistem") || ! strcmp(ident, "TABEL_SISTEM")) {
          //printf("dummy ");
          strcat(SQLstmt,"dummy ");
        } else 

        if(! strcmp(ident, "pilih") || ! strcmp(ident, "PILIH")) {
          //printf("CASE ");
          strcat(SQLstmt,"CASE ");
        } else 

        if(! strcmp(ident, "ketika") || ! strcmp(ident, "KETIKA")) {
          //printf("WHEN ");
          strcat(SQLstmt,"WHEN ");
        } else 

        if(! strcmp(ident, "maka") || ! strcmp(ident, "MAKA")) {
          //printf("THEN ");
          strcat(SQLstmt,"THEN ");
        } else 

        if(! strcmp(ident, "lainnya") || ! strcmp(ident, "LAINNYA")) {
          //printf("ELSE ");
          strcat(SQLstmt,"ELSE ");
        } else 

        if(! strcmp(ident, "selesai") || ! strcmp(ident, "SELESAI")) {
          //printf("END ");
          strcat(SQLstmt,"END ");
        } else 

        if(! strcmp(ident, "sebagai") || ! strcmp(ident, "SEBAGAI")) {
          //printf("AS ");
          strcat(SQLstmt,"AS ");
        } else 

        if(! strcmp(ident, "gabungan") || ! strcmp(ident, "GABUNGAN")) {
          //printf("UNION ");
          strcat(SQLstmt,"UNION ");
        } else 

        if(! strcmp(ident, "potongan") || ! strcmp(ident, "POTONGAN")) {
          //printf("INTERSECT ");
          strcat(SQLstmt,"INTERCEST ");
        } else 


        {
          //printf("%s ", sql_lex.detail.ident);
          #ifdef WIN32
           #ifndef S_SPLINT_S
           sprintf_s(stmt, sizeof(stmt),"%s ", sql_lex.detail.ident);
           #else
           snprintf(stmt, sizeof(stmt),"%s ", sql_lex.detail.ident);
           #endif
          #else
          snprintf(stmt, sizeof(stmt),"%s ", sql_lex.detail.ident);
          #endif

          strcat(SQLstmt, stmt);
        }

	break;

      case _SQL_EOF:
	/* ファイルの終了ならば、そのままループ脱出 */
	break;

      default:
        SQLError(sql_lex, sql_pg, "salah: tidak bisa ditranslasi !");
	break;
      }

  }while( sql_lex.type != _SQL_EOF );

  SQLValLabel( sql_lex, sql_pg, "", 0, SQL_VAL_FLAG_END );

  // メモリ開放
  if(sql_pg.source != NULL) {
    free(sql_pg.source);
  }

  // printf("\n%s\n", SQLstmt);

  retSQL = SQLstmt;

  return retSQL;
}



/* --------------------------------------------------------
 * プログラムから単語を取得する関数群
 * グローバルの LEX_T lex 構造体にデータを格納する
 -------------------------------------------------------- */

PARSING SQLgetlex( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  PARSING par;
  char c='\0';

  par.sql_lex = sql_lex;
  par.sql_pg  = sql_pg;
  par.c       = c;

  if( sql_lex.type == _SQL_EOF ) {
    if(par.sql_pg.source != NULL)
      free(par.sql_pg.source);

    return par;
  }

  // printf("getlex source: %s\n", sql_pg.source);

  sql_pg.back_pt = sql_pg.pt;

  par = SQLGetChar(sql_lex, sql_pg);
  sql_pg = par.sql_pg;
  c      = par.c;
  memset( &sql_lex, 0, sizeof(SQL_LEX_T) );
  
  // printf("getlex char: %c\n", c);

  if( isalpha( c ) || c == '_' )
    return( SQLlex_ident(sql_lex, sql_pg) );

  if( isdigit( c ) )
    return( SQLlex_ident(sql_lex, sql_pg) );

  /* single quotation */
  #ifndef S_SPLINT_S
  if( c == 0x27 )
    return( SQLlex_string(sql_lex, sql_pg) );
  #endif

  if( c == '\0' ){
    sql_lex.type = _SQL_EOF;

    par.c = c;
    par.sql_pg  = sql_pg;
    par.sql_lex = sql_lex;

    if(par.sql_pg.source != NULL)
      free(par.sql_pg.source);

    return par;
  }

  sql_lex.type = TYPE_SQL_SYM;
  sql_lex.detail.symbol = c;
  sql_pg.pt++;
  

  par.c = c;
  par.sql_pg  = sql_pg;
  par.sql_lex = sql_lex;

    if(par.sql_pg.source != NULL)
      free(par.sql_pg.source);

  return par;
}


void SQLungetlex( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg)
{
  sql_pg.pt = sql_pg.back_pt;
}


PARSING SQLGetChar( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  PARSING par;
  char c;

  do{
    c = sql_pg.source[sql_pg.pt++];
    if( c == '#' )
      do{ c = sql_pg.source[sql_pg.pt++]; }while( c != '\0' && c != '\n' );
  }while( isspace( c ) && c != '\0' );

  sql_pg.pt--;

  par.c = c;
  par.sql_pg  = sql_pg;
  par.sql_lex = sql_lex;

  if(par.sql_pg.source != NULL)
    free(par.sql_pg.source);

  return par;
}



/* 変数名もしくは、ラベル名もしくは、予約語であるときに
 * getlex関数から呼ばれる
 * 引数：なし
 * 戻り値：どんな場合でもFALSEを返す
 */
PARSING SQLlex_ident( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  PARSING par;
  char c;
  int i = 0;
  
  /* アルファベットもしくは数字もしくは'_'なら
     識別子として読み込む */
  while( isalnum( c = sql_pg.source[sql_pg.pt++] ) || c == '_' ){

    if( i > (MAX_IDENT_LEN - 1) )
      SQLError(sql_lex, sql_pg, "salah : melebihi panjang kapasitas %d", MAX_IDENT_LEN );

    sql_lex.detail.ident[i++] = (char)c;
  }
  sql_lex.detail.ident[i] = '\0';
  sql_pg.pt--;

  sql_lex.type = TYPE_SQL_IDENT;
  
  /* 予約語ならばsql_lex.typeを変更する */


  
  if( ! strcmp(sql_lex.detail.ident, "LABEL") )
    sql_lex.type = _SQLLABEL;
  
  
  if( ! strcmp(sql_lex.detail.ident, "END") )
    sql_lex.type = _SQLEND;

  // printf("get ident: %s\n", sql_lex.detail.ident);

  par.c = c;
  par.sql_pg  = sql_pg;
  par.sql_lex = sql_lex;

  if(par.sql_pg.source != NULL)
    free(par.sql_pg.source);

  return par;
}



/* 数字であるときにgetlex関数から呼ばれる
 * 引数：なし
 * 戻り値：どんな場合でもFALSEを返す
 */
PARSING  SQLlex_const(  SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  PARSING par;
  char c;
  int num = 0;
  
  /* 文字列の数字をint型に変換 */
  while( isdigit( c = sql_pg.source[sql_pg.pt++] ) )
    num = num * 10 + (int)(c - '0');
  
  sql_lex.detail.num = num;
  
  sql_pg.pt--;
  sql_lex.type = TYPE_SQL_NUM;
  
  par.c = c;
  par.sql_pg  = sql_pg;
  par.sql_lex = sql_lex;

  if(par.sql_pg.source != NULL)
    free(par.sql_pg.source);

  return par;
}



PARSING SQLlex_string(  SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  PARSING par;
  #ifndef S_SPLINT_S
  char c = 0x51;
  #else
  char c = '\0';
  #endif
  int i = 0;
  
  sql_pg.pt++;
  
  #ifndef S_SPLINT_S
  while( (c = sql_pg.source[sql_pg.pt++]) != 0x27 )
  #else
  while( (c = sql_pg.source[sql_pg.pt++]) != '\0' )
  #endif

  {
    if( c == '\0' )
    	SQLError(sql_lex, sql_pg, "salah! kata tanpa tanda petik");

    /* 以下の文字は無視しますが、 */
    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' )
      continue;

    /* 文字列として書かれてあったら受理します */
    if( c == '\\' ){

      c = sql_pg.source[sql_pg.pt++];

      switch( c )
      {
        case 'b':
          c = '\b';
          break;

        case 'f':
          c = '\f';
          break;

        case 'r':
          c = '\r';
          break;

        case 'n':
          c = '\n';
          break;

        case 't':
          c = '\t';
          break;
      }
    }
    
    if( i > (MAX_STRING_LEN - 1) )
      SQLError(sql_lex, sql_pg, "salah! melebihi MAX_STRING_LEN");
    
    sql_lex.detail.string[i++] = (char)c;
  }
  
  sql_lex.detail.string[i] = '\0';
  sql_lex.type = TYPE_SQL_STR;

  par.c = c;
  par.sql_pg  = sql_pg;
  par.sql_lex = sql_lex;

  if(par.sql_pg.source != NULL)
    free(par.sql_pg.source);

  return par;
}



/* --------------------------------------------------------
 * 変数とラベルを管理する関数群
 * 二分探索木に作成して、変数とラベルを管理する
 -------------------------------------------------------- */


/* 二分探索木を管理する関数 
 * flag = SQL_VAL_FLAG_START ならば二分探索木を生成
 * flag = SQL_VAL_FLAG_SEARCH_W ならば二分探索木にデータ追加
 * flag = SQL_VAL_FLAG_SEARCH_R ならば二分探索木からデータ読みこみ
 * flag = SQL_VAL_FLAG_END ならば二分探索木を削除
 * 戻り値：SQL_VAL_FLAG_STARTとSQL_VAL_FLAG_ENDのときは失敗時TRUE、成功時FALSE
 *         SQL_VAL_FLAG_SEARCH_R(W)のときはデータが戻り値となる
 */
int SQLValLabel( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg, char *ident, int data, int flag )
{
  static SQL_VAL_LABEL *SQLroot;
  int ret = 0;

  if( flag == SQL_VAL_FLAG_START ){

    SQLroot = NULL;
    if(ident != NULL) {
      SQLroot = SQLMakeValLabelTree( ident, data );
    }

    if( SQLroot == NULL )
      return TRUE;
    else
      return FALSE;
  }

  if( flag == SQL_VAL_FLAG_SEARCH_W || flag == SQL_VAL_FLAG_SEARCH_R ){

    SQL_VAL_LABEL *node = SQLSearchValLabelTree( SQLroot, ident );

    if( node != NULL ){
      ret = node->data;
      if( flag == SQL_VAL_FLAG_SEARCH_W )
        ret = data;

      if(node != NULL)
        free(node);
      if(node->right != NULL)
        free(node->right);
      if(node->left != NULL)
        free(node->left);
      if(node->ident != NULL)
        free(node->ident);

      return ret;

    }else{
      if( flag == SQL_VAL_FLAG_SEARCH_W ){
	if( SQLMakeAddValLabelTree( SQLroot, ident, data ) )
	  SQLError(sql_lex, sql_pg, "salah ! memori MakeAddValLabelTree");
      }

      if(node != NULL)
        free(node);
      if(node->right != NULL)
        free(node->right);
      if(node->left != NULL)
        free(node->left);
      if(node->ident != NULL)
        free(node->ident);

      return data;
    }
  }

  if( flag == SQL_VAL_FLAG_END ){
    // printf("delete sql memori ...\n");
    SQLDeleteValLabelTree( SQLroot );
    return FALSE;
  }

  return TRUE;
}


/* 二分探索木のノードを生成する関数
 * メモリ領域の生成とデータの設定を行う
 * 戻り値：失敗時はNULL、成功時は生成したノードのポインタ
 */
SQL_VAL_LABEL *SQLMakeValLabelTree( char *ident, int data )
{
  SQL_VAL_LABEL *node=NULL;

  if( (node = (SQL_VAL_LABEL *)malloc( sizeof(SQL_VAL_LABEL)) ) == NULL )
    return NULL;

  strcpy( node->ident, ident );
  node->data = data;

  node->left  = NULL;
  node->right = NULL;

  return node;
}


/* 二分探索木にノードを追加する関数
 * 戻り値：なし
 */
void SQLAddValLabelTree( SQL_VAL_LABEL *t, SQL_VAL_LABEL *n )
{
  int judge = strcmp( t->ident, n->ident );

  if( judge > 0 ){
    if( t->left != NULL )
      SQLAddValLabelTree( t->left, n );
    else
      t->left = n;
  }

  if( judge < 0 ){
    if( t->right != NULL )
      SQLAddValLabelTree( t->right, n );
    else
      t->right = n;
  }
}



int SQLMakeAddValLabelTree( SQL_VAL_LABEL *t, char *ident, int data )
{
  SQL_VAL_LABEL *node=NULL;

  if( (node = SQLMakeValLabelTree( ident, data )) == NULL )
    return TRUE;

  SQLAddValLabelTree( t, node );

  if(node != NULL)
   free(node);

  return FALSE;
}



SQL_VAL_LABEL *SQLSearchValLabelTree( SQL_VAL_LABEL *t, char *ident )
{
  int judge = strcmp( t->ident, ident );

  if( judge == 0 )
    return t;

  if( judge > 0 && t->left != NULL )
      return ( SQLSearchValLabelTree( t->left, ident ) );

  if( judge < 0 && t->right != NULL )
      return ( SQLSearchValLabelTree( t->right, ident ) );

  return NULL;
}


void SQLDeleteValLabelTree( SQL_VAL_LABEL *t )
{
  if( t->left != NULL )
    SQLDeleteValLabelTree( t->left );

  if( t->right != NULL )
    SQLDeleteValLabelTree( t->right );

  if( t != NULL) {
    free( t );
  }
}




int SQLexpression( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  return ( SQLAndOr(sql_lex, sql_pg) );
}



int SQLAndOr( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  int x = SQLNotFunc(sql_lex, sql_pg);

  SQLgetlex(sql_lex, sql_pg);
  if( sql_lex.type == _SQL_EOF )
    SQLError(sql_lex, sql_pg, "salah ! alur diluar perkiraan");

  while ( sql_lex.type == _SQL_OR || sql_lex.type == _SQL_AND ){

    switch( sql_lex.type )
      {
      case _SQL_AND:
	x = ( x && SQLNotFunc(sql_lex, sql_pg) ) ? 1 : 0;
	break;
      case _SQL_OR:
	x = ( x || SQLNotFunc(sql_lex, sql_pg) ) ? 1 : 0;
	break;
      }

    SQLgetlex(sql_lex, sql_pg);
  }

  SQLungetlex(sql_lex, sql_pg);
  return x;
}



int SQLNotFunc( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  SQLgetlex(sql_lex, sql_pg);
  if( sql_lex.type == _SQL_EOF )
    SQLError(sql_lex, sql_pg, "salah ! alur diluar perkiraan");

  if( sql_lex.type != _SQL_NOT ){
    SQLungetlex(sql_lex, sql_pg);
    return ( SQLCompare(sql_lex, sql_pg) );
  }

  return( ( SQLCompare(sql_lex, sql_pg) != 0 ) ? 0 : 1 );
}



int SQLCompare( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  int x = SQLAddSub(sql_lex, sql_pg);
  int y = x;
  
  char symbol;

  SQLgetlex(sql_lex, sql_pg);
  if( sql_lex.type == _SQL_EOF )
    SQLError(sql_lex, sql_pg, "salah ! alur diluar perkiraan");

  if( ( sql_lex.type != TYPE_SQL_SYM ) || 
      ( sql_lex.detail.symbol != '=' &&
        sql_lex.detail.symbol != '<' &&
        sql_lex.detail.symbol != '>' ) ){
    SQLungetlex(sql_lex, sql_pg);
    return y;
  }

  symbol = sql_lex.detail.symbol;

  SQLgetlex(sql_lex, sql_pg);
  if( sql_lex.type == _SQL_EOF )
    SQLError(sql_lex, sql_pg, "salah ! alur diluar perkiraan");

  switch( symbol )
    {
    case '=':
      if( sql_lex.type == TYPE_SQL_SYM ){
	switch( sql_lex.detail.symbol )
	  {
	    /* '=='だったら同値判定 */
	  case '=':
	    y = ( x == SQLAddSub(sql_lex, sql_pg) ) ? 1 : 0;
	    break;
	  default:
	    SQLError(sql_lex, sql_pg, "salah! setelah '=' ada tanda selain '='");
	  }
      }
      /* '='だけだったら代入 */
      else{
	SQLungetlex(sql_lex, sql_pg);
	return ( SQLAddSub(sql_lex, sql_pg) );
      }
      break;
      
    case '>':
      if( sql_lex.type == TYPE_SQL_SYM ){
	switch( sql_lex.detail.symbol )
	  {
	    /* '>='だったら以下判定 */
	  case '=':
	    y = ( x >= SQLAddSub(sql_lex, sql_pg) ) ? 1 : 0;
	    break;
	  default:
	    SQLError(sql_lex, sql_pg, "salah! setelah '>' ada tanda selain '='");
	  }
      }
      /* '>'だけだったら未満判定 */
      else{
	SQLungetlex(sql_lex, sql_pg);
	y = ( x > SQLAddSub(sql_lex, sql_pg) ) ? 1 : 0;
      }
      break;
      
    case '<':
      if( sql_lex.type == TYPE_SQL_SYM ){
	switch( sql_lex.detail.symbol )
	  {
	    /* '<>'だったら否定判定 */
	  case '>':
	    y = ( x != SQLAddSub(sql_lex, sql_pg) ) ? 1 : 0;
	    break;
	    /* '<='だったら以上判定 */
	  case '=':
	    y = ( x <= SQLAddSub(sql_lex, sql_pg) ) ? 1 : 0;
	    break;
	  default:
	    SQLError(sql_lex, sql_pg, "setelah '<' ada tanda selain  '>' atau '='");
	  }
      }
      else{
	SQLungetlex(sql_lex, sql_pg);
	y = ( x < SQLAddSub(sql_lex, sql_pg) ) ? 1 : 0;
      }
      break;
      
    default:
      SQLError(sql_lex, sql_pg, "salah bentuk kata");
    }

  return y;
}



int SQLAddSub( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  int x = SQLMulDiv(sql_lex, sql_pg);
  
  SQLgetlex(sql_lex, sql_pg);
  if( sql_lex.type == _SQL_EOF )
    SQLError(sql_lex, sql_pg, "salah ! alur diluar perkiraan");
  
  while( sql_lex.type == TYPE_SQL_SYM && 
	 ( sql_lex.detail.symbol == '+' ||
	   sql_lex.detail.symbol == '-' ) ){

    switch( sql_lex.detail.symbol )
      {
      case '+':
	x = x + SQLMulDiv(sql_lex, sql_pg);
	break;
	
      case '-':
	x = x - SQLMulDiv(sql_lex, sql_pg);
	break;
      }

    SQLgetlex(sql_lex, sql_pg);
  }

  SQLungetlex(sql_lex, sql_pg);
  return x;
}



int SQLMulDiv( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  int x = SQLFactor(sql_lex, sql_pg);
  int y = x;
  
  SQLgetlex(sql_lex, sql_pg);
  if( sql_lex.type == _SQL_EOF )
    SQLError(sql_lex, sql_pg, "salah ! alur diluar perkiraan");

  while( sql_lex.type == TYPE_SQL_SYM && 
	 ( sql_lex.detail.symbol == '*' ||
	   sql_lex.detail.symbol == '/' ||
	   sql_lex.detail.symbol == '%' ) ){
    
    switch( sql_lex.detail.symbol )
      {
      case '*':
	y = y * SQLFactor(sql_lex, sql_pg);
	break;
	
      case '/':
	if( (x = SQLFactor(sql_lex, sql_pg)) == 0 )
	  SQLError(sql_lex, sql_pg, "salah: dibagi dengan nol");
	y = y / x;
	break;
	
      case '%':
	if ( (x = SQLFactor(sql_lex, sql_pg)) == 0 )
	  SQLError(sql_lex, sql_pg, "salah: dibagi dengan nol");
	y = y % x;
	break;
      }

    SQLgetlex(sql_lex, sql_pg);
  }

  SQLungetlex(sql_lex, sql_pg); // from
  return y;
}



int SQLFactor( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  int x = 0;

  SQLgetlex(sql_lex, sql_pg);
  switch( sql_lex.type )
    {
    case TYPE_SQL_IDENT:
      /* 変数名もしくはラベル名だった場合はそれに対応した値を返す */
      x = SQLValLabel( sql_lex, sql_pg, sql_lex.detail.ident, 0, SQL_VAL_FLAG_SEARCH_R );
      break;
      
    case TYPE_SQL_NUM:
      /* 数値だったら、その数値を返す */
      x = sql_lex.detail.num;
      break;
      
    case TYPE_SQL_SYM:
	/* '('なら中の演算を行う */
      //if( sql_lex.detail.symbol != '(' )
	//SQLError(sql_lex, sql_pg, "syntaxエラー2");
      if( sql_lex.detail.symbol == '(' ){
	x = SQLexpression(sql_lex, sql_pg);
	SQLgetlex(sql_lex, sql_pg);
	if ( sql_lex.detail.symbol != ')' )
	  SQLError(sql_lex, sql_pg, "'(' tanpa ')'");
      }
      break;
      
    default:
      SQLError(sql_lex, sql_pg, "salah urutan kalimat");
    }

  return x;
}



/* --------------------------------------------------------
 * エラーに関する関数群
 -------------------------------------------------------- */



/* 現在実行中の行番号を計算する関数
 * 戻り値：現在実行中の行番号
 */
int SQLLineCounter( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg )
{
  char *ptr = NULL;
  int counter = 1;

  for(ptr = sql_pg.source; ptr < (sql_pg.source + sql_pg.pt); ptr++ )
    if( *ptr == '\n' )
      counter++;

  return counter;
}



void SQLError( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg, const char *format, ... )
{
  va_list list;
  fprintf( stderr, "baris %u: ", SQLLineCounter(sql_lex, sql_pg) );
  
  va_start( list, format );
  vfprintf( stderr, format, list );
  va_end( list );
  
  fprintf( stderr, "\n");
  
  SQLValLabel( sql_lex, sql_pg, "", 0, SQL_VAL_FLAG_END );

  if(sql_pg.source != NULL)
    free( sql_pg.source );

  BaikGarbageCollection();

  exit(1);
}


