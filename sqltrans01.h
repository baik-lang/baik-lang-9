// //////////////////////////////////////////////////////////////////////
// Penerjemah SQL untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
// //////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/stat.h>


/* TRUE FALSE の定義 */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


#define MAX_STRING_LEN  300


enum
{
  _SQLEND,      //10

  _SQLLABEL,    //11

  _SQL_AND,      /* かつ */
  _SQL_OR,       /* もしくは */
  _SQL_NOT,      /* 否定 */

  _SQL_EOF,      /* ファイルの終端 */

/* 予約語以外のデータ */
  TYPE_SQL_NUM,   /* 12 数字 */
  TYPE_SQL_IDENT, /* 13 変数名あるいは、ラベル名 */
  TYPE_SQL_STR,   /* 14 文字列 */
  TYPE_SQL_SYM,   /* 15 特殊文字 */

/* ValLabel関数の第三引数のフラグ */
  SQL_VAL_FLAG_START,      /* 探索木の作成（メモリ確保）     */
  SQL_VAL_FLAG_SEARCH_R,   /* 探索木からデータを検索読み込み */
  SQL_VAL_FLAG_SEARCH_W,   /* 探索木からデータを検索書き込み */
  SQL_VAL_FLAG_END,        /* 探索木の消去（メモリ解放）     */
};


typedef struct
{
  /* 上記に定義しているデータを格納する変数 */
  int type;

  /* 予約語以外のデータの場合は、そのデータを入れる変数群 */
  union{
    int num;                      /* 数字 */
    char ident[MAX_IDENT_LEN];    /* 変数名 or ラベル名 */
    char string[MAX_STRING_LEN];  /* 文字列 */
    char symbol;                  /* 特殊文字 */
  }detail;

} SQL_LEX_T;
/* 単語を格納する構造体。格納を担当するのはgetlex関数
 * 単語は「予約語」「数字」「変数名 or ラベル名」「文字列」「特殊文字」の
 * 5つの中のいずれかしか無い。予約語以外だったら、
 * そのデータも取得する。
 */

typedef struct
{
  int pt;        /* 現在実行している位置 */
  int back_pt;   /* 過去実行した位置 */
  char *source;  /* 実行すべきプログラム */
} SQL_S_ADDR;
/* 実行中のプログラムの位置を示す構造体。
 * source[pt] により、現在実行中プログラムの位置を示す。
 */

///* 上記2つの構造体のグローバル */
//SQL_LEX_T sql_lex;  /* getlex関数が呼ばれた時に値がいれられる */
//SQL_S_ADDR sql_pg;  /* 現在実行しているプログラムの位置を表す */


typedef struct _sql_val_label
{
  struct _sql_val_label *left;   /* 左のデータのポインタ */
  struct _sql_val_label *right;  /* 右のデータのポインタ */

  char ident[MAX_IDENT_LEN]; /* 変数名もしくはラベル名 */
  int data;                  /* 変数の値もしくはラベルの位置 */

} SQL_VAL_LABEL;
/* VAL_LABEL構造体は、ValLabel関数で管理される 
 * この構造体は、プログラムに使用される変数やラベルを持ち
 * 二分探索木により管理される。
 */

typedef struct
{

  SQL_LEX_T sql_lex;  /* getlex関数が呼ばれた時に値がいれられる */
  SQL_S_ADDR sql_pg;  /* 現在実行しているプログラムの位置を表す */
  char c;

} PARSING;

