// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#ifdef WINDOWS
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifndef S_SPLINT_S

#include <mysql.h>
#include "my_common.h"

MYSQL *
do_connect (char *host_name, char *user_name, char *password, char *db_name,
            unsigned int port_num, char *socket_name, unsigned int flags)
{
 MYSQL   *conn=NULL;   /* ponter to handler */

 conn = mysql_init(NULL);

 if(conn == NULL) {
   fprintf(stderr, "gagal inisialisasi mysql\n");
   fprintf(stderr, "periksa mysql client library !\n");
   exit(-1);
 }
// if(mysql_real_connect(conn, host_name, user_name, password, 
//                      db_name, port_num, socket_name, flags) == NULL) {
                      
 if(mysql_real_connect(conn, host_name, user_name, password, 
                      db_name, port_num, NULL, 0) == NULL) {                      
   fprintf(stderr, "gagal mysql_real_connect()\n");
   fprintf(stderr, "periksa koneksi ke mysql server ! %s\n", mysql_error(conn));
   exit(-1);
 }

 return(conn);
}

void do_disconnect(MYSQL *conn) {
 mysql_close(conn);

}

#endif

