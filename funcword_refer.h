// ////////////////////////////////////////////////////////////////

// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


// ////////////////////////////////////////////////////////////////


// //////////////////////////////////////////////////////////////////////
int get_enum_funcword(char funcname[MAX_IDENT_LEN]) {
  int ret = '\0';
  struct funcword_list data;

  if(strlen(funcname) < 0)
    Error("kata kunci salah masukan");

  memset(&data, '\0', sizeof(data));
  // get current funcname
  strcpy(data.funcname, funcname);

  ret = funcword_getEnum(data);

  return ret;
}


void save_funcword(char funcname[MAX_IDENT_LEN], char alias[MAX_IDENT_LEN] ) {
  int ret = '\0';
  int pos = -1;
  struct funcword_list data;

  if(strlen(funcname) < 0)
    Error("kata kunci/fungsi salah masukan");

  memset(&data, '\0', sizeof(data));
  // get current funcword
  strcpy(data.funcname, funcname);
  if(strlen(alias) > 0)
    strcpy(data.alias, alias);


  funcEnum = funcword_getEnum(data);
  if(funcEnum < 0) {
    // set value
    pos = funcword_getCount() + 1;
	data.enumid = pos;

    printf(" add funcword enum %d , value: %s\n", data.enumid, data.funcname);

    funcword_addFirst(data);
  } else {
    printf(" %s enum %d , sudah terpakai \n", funcname, funcEnum);
    Error("nama kata kunci/fungsi sudah terpakai");
  }

}

