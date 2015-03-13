// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#include "ocilib.h"

OCI_Connection *ora_connect (char *tns_name, char *user_name, char *password);

void ora_disconnect(OCI_Connection *conn);

char** ORADBrows_get(OCI_Resultset *ora_res);


