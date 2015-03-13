// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef USE_SQLITE
#include "sqlite3.h"

#include <stdio.h>
#include <stdlib.h>

sqlite3 *sqlite_connect (char *db_name)
{
 sqlite3 *db = NULL;   /* ponter to handler */
 int     err = 0;


 db = (sqlite3 *)malloc(sizeof(db));
 // open database
 err = sqlite3_open(db_name, &db);

 if (err != SQLITE_OK) {
   // show error and exit.
   fprintf(stderr, "gagal buka file db dari SQLite\n");
   fprintf(stderr, "buka sqlite3: %s\n", sqlite3_errmsg(db));
   exit(1);
 }

 if(db == NULL) {
   fprintf(stderr, "gagal buka file db dari SQLite\n");
   exit(-1);
 }

 return(db);
}

void sqlite_disconnect(sqlite3 *db) {
  sqlite3_close(db);
}

#endif


