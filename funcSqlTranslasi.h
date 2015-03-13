// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


#include "sqltrans01.h"


PARSING SQLgetlex( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg );
void SQLungetlex( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg);

PARSING SQLGetChar( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg );
PARSING SQLlex_ident( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg );
PARSING SQLlex_string(  SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg );
int SQLValLabel( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg, char *ident, int data, int flag );

SQL_VAL_LABEL *SQLMakeValLabelTree( char *ident, int data );
void SQLAddValLabelTree( SQL_VAL_LABEL *t, SQL_VAL_LABEL *n );

int SQLMakeAddValLabelTree( SQL_VAL_LABEL *t, char *ident, int data );
SQL_VAL_LABEL *SQLSearchValLabelTree( SQL_VAL_LABEL *t, char *ident );
void SQLDeleteValLabelTree( SQL_VAL_LABEL *t );

int SQLexpression( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg );
int SQLAndOr( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg );
int SQLNotFunc( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg );
int SQLCompare( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg);
int SQLAddSub( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg );
int SQLMulDiv( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg );
int SQLFactor( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg );
void SQLError( SQL_LEX_T sql_lex, SQL_S_ADDR sql_pg, const char *format, ... );


#include "sqltrans02.h"

VAL_LABEL funcSQLTranslasi ()
{
  VAL_LABEL datx;

  //SQL_LEX_T sql_lex;
  //SQL_S_ADDR sql_pg;

  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat, tmpdat;
  
  long    idx=0;                           // array index

  float tmp = 0.0;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


         getlex();
         /* printf("lex detail num : %d\n", lex.detail.num);
            printf("lex type : %d\n", lex.type); */

         if(lex.type == TYPE_NUM) {
           Error("TRANS_SQL: masukan data salah");
         } else if(lex.type == TYPE_DBL) {
           Error("TRANS_SQL: masukan data salah");
         } else if(lex.type == TYPE_STR) {
		   sprintf (datx.str, "%s", SQLInterpreter(lex.detail.string));
           datx.datatype = 3;

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

			  sprintf(valdat.array_idx, "%li", idx);

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              if(valdat.datatype == 8 && valdat.array_s != '\0') {
                if(valdat.array_s == '\0')
                  Error("TRANS_SQL: ukuran Untaian belum terdefinisi");
                memset(&tmpMsg, '\0', sizeof(tmpMsg));

                get_str_array(valdat, idx, (char *) &tmpMsg);

                sprintf (datx.str, "%s", SQLInterpreter(tmpMsg));
                datx.datatype = 3;

              } else if (valdat.datatype == 10) {
                sprintf (datx.str, "%s", SQLInterpreter(valdat.long_str[idx]));
                datx.datatype = 3;

              } else {
                Error("TRANS_SQL: masukan data salah");
              }
           }

         } else {
           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
             //printf("construct class var: %s\n", class_tmpvar);
             datx = ValLabel( class_tmpvar, sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           // datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           if(datx.datatype == 3) {
             sprintf (datx.str, "%s", SQLInterpreter(datx.str));
             datx.datatype = 3;
           } else {
             Error("TRANS_SQL: masukan data salah");
           }
         }

  // clear all sql translation
  // memset(&sql_lex, '\0', sizeof(sql_lex));
  // memset(&sql_pg, '\0', sizeof(sql_pg));
  // printf("cleaning sql...\n");
  // SQLValLabel( sql_lex, sql_pg, NULL, 0, SQL_VAL_FLAG_END );
  // printf("cleaning sql ok\n");

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

  if(tmpdat.filename != NULL)
    free(tmpdat.filename);
  if(tmpdat.folder != NULL)
    free(tmpdat.folder);
  if(tmpdat.filedata != NULL)
    free(tmpdat.filedata);
  if(tmpdat.long_str != NULL)
    free(tmpdat.long_str);

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

  return datx;

}

