// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcSSL_aes128cbc_encrypt ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  int n=0;

  char plaintext[MAX_STRING_LEN];
  char ciphertext[MAX_STRING_LEN];
  char mykey[EVP_MAX_KEY_LENGTH];


  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&plaintext, '\0', sizeof(plaintext));
  memset(&ciphertext, '\0', sizeof(ciphertext));
  memset(&mykey, '\0', sizeof(mykey));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  do {
    /* get referenced ident */
    getlex();

    /* printf("lex type : %d\n", lex.type);  */

    if(lex.type == TYPE_IDENT) {

           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
             //printf("construct class var: %s\n", class_tmpvar);
             datx = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

           if(datx.datatype == 3) {
			 if(n == 0) {
               strcpy(plaintext, datx.str);
			 } else
			 if(n == 1) {
               strcpy(mykey, datx.str);
			 }
           } else {
             Error("enkripsi_aes128cbc: masukan data salah");
           }
	} else if(lex.type == TYPE_STR) {
      if(n == 0) {
        strcpy(plaintext, lex.detail.string);
	  } else
      if(n == 1) {
        strcpy(mykey, lex.detail.string);
	  }
    } else {
      Error("enkripsi_aes128cbc: masukan data salah");
    }

	n++;
	getlex();

  }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');
  
  ungetlex();

  if(n == 2) {
    //printf ("enkripsi 3ds %s\n", plaintext);

    memset(&datx, '\0', sizeof(datx));
	encrypt_aes128cbc(plaintext, (char *)&ciphertext, mykey);
	strcpy(datx.str, ciphertext);
    datx.datatype = 3;

  } else {
    Error("enkripsi_aes128cbc: masukan data salah");
  }

  return datx;
}


VAL_LABEL funcSSL_aes128cbc_decrypt ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat;
  int n=0;

  char plaintext[MAX_STRING_LEN];
  char ciphertext[MAX_STRING_LEN];
  char mykey[EVP_MAX_KEY_LENGTH];


  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&plaintext, '\0', sizeof(plaintext));
  memset(&ciphertext, '\0', sizeof(ciphertext));
  memset(&mykey, '\0', sizeof(mykey));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  do {
    /* get referenced ident */
    getlex();

    /* printf("lex type : %d\n", lex.type);  */

    if(lex.type == TYPE_IDENT) {

           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
             //printf("construct class var: %s\n", class_tmpvar);
             datx = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
           } else {
             datx = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
           }

		   if(datx.datatype == 3) {
			 if(n == 0) {
               strcpy(ciphertext, datx.str);
			 } else
			 if(n == 1) {
               strcpy(mykey, datx.str);
			 }
           } else {
             Error("dekripsi_aes128cbc: masukan data salah");
           }
	} else if(lex.type == TYPE_STR) {
      if(n == 0) {
        strcpy(ciphertext, lex.detail.string);
	  } else
      if(n == 1) {
        strcpy(mykey, lex.detail.string);
	  }
    } else {
      Error("dekripsi_aes128cbc: masukan data salah");
    }

	n++;
	getlex();

  }while( lex.type == TYPE_SYM && lex.detail.symbol == ',');
  
  ungetlex();

  if(n == 2) {
    //printf ("enkripsi 3ds %s\n", plaintext);

    memset(&datx, '\0', sizeof(datx));
	decrypt_aes128cbc((char *)&plaintext, ciphertext, mykey);
	strcpy(datx.str, plaintext);
    datx.datatype = 3;

  } else {
    Error("dekripsi_aes128cbc: masukan data salah");
  }

  return datx;
}


