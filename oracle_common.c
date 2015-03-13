// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef USE_OCI
#include "ocilib.h"
#include <stdio.h>


OCI_Connection *ora_connect (char *tns_name, char *user_name, char *password)
{
 OCI_Connection *conn = NULL;   /* pointer to handler */
 int     initStat = 0;

 if (!OCI_Initialize(NULL, NULL, OCI_ENV_DEFAULT)) {
   initStat = 0;
   fprintf(stderr, "gagal inisialisasi oracle\n");
   fprintf(stderr, "periksa oracle client library !\n");
 } else {
   initStat = 1;
 }

 if(initStat) {
   conn = OCI_ConnectionCreate(tns_name, user_name, password, OCI_SESSION_DEFAULT);
 }

 if(conn == NULL) {
   fprintf(stderr, "gagal koneksi ke oracle\n");
   fprintf(stderr, "periksa koneksi ke oracle server !\n");
   exit(-1);
 }

 return(conn);
}

void ora_disconnect(OCI_Connection *conn) {
  OCI_Cleanup();
}

#endif