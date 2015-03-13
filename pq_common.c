// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
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
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifdef USE_PGSQL
#include <libpq-fe.h>

extern void Error( const char *format, ... );
extern char** split(const char *str, const char *delim);
extern void split_free(char **arr);

PGconn *pgdb_connect (char *host_name, char *user_name, char *password, char *db_name,
			  unsigned int port_num) {

  char msg[1024];

  char host[256];
  int  iDot, isIP = 0;
  char **get = NULL;
  PGconn *myconn = NULL;

  memset(&msg, '\0', sizeof(msg));
  memset(&host, '\0', sizeof(host));
  
  strcpy(host, host_name);
  get = split(host_name, ".");

  if(get != NULL) {
    iDot=0;
    while(get[iDot] != NULL && strlen(get[iDot]) > 0) {
      iDot++;
    }
  }
  // printf("dot num %d\n", iDot);
  split_free(get);

  if(isdigit(host[0]) && iDot == 4) { 
    isIP = 1;
  }

  if(isIP) {
    sprintf(msg, "hostaddr=%s user=%s password=%s dbname=%s port=%d ", host_name, user_name, password, db_name, port_num);
  } else {
    sprintf(msg, "host=%s user=%s password=%s dbname=%s port=%d ", host_name, user_name, password, db_name, port_num);
  }
  // printf("pq param : %s\n", msg);

  myconn = PQconnectdb(msg);

  if (PQstatus(myconn) == CONNECTION_BAD) {
    Error("Koneksi ke PostgreSql salah, periksa database server !");
  }

  return myconn;
}


void pgdb_disconnect(PGconn *conn) {
  PQfinish(conn);
  conn = NULL;
}

#endif

