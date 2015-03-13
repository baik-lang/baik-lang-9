// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia.
// 
// ///////////////////////////////////////////////////////////////////

#ifdef WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#endif

#include <stdio.h>
#include <libpq-fe.h>

PGconn *pgdb_connect (char *host_name, char *user_name, char *password, char *db_name,
            unsigned int port_num);
void pgdb_disconnect(PGconn *conn);

