// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

VAL_LABEL interpretIndexParam(char source[MAX_STRING_LEN], int tmp_pt, int back_pt, char currentClass[MAX_STRING_LEN]) {
  VAL_LABEL valdat, valdat2;
  char ident[MAX_STRING_LEN];
  char ope='\0', ope2='\0';
  int  num=0;
  char *idx_tmp_source;

  // printf ("inside interpretIndex\n");

  memset(&ident, '\0', sizeof(ident));
 
  /* valdat init */
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  idx_tmp_source = NULL;
  idx_tmp_source = pg.source;

  pg.pt      = 0;
  pg.back_pt = 0;
  pg.source  = source;

  /* throw out ';' or '{'  symbol            */
  getlex();

  /* skip if nothing                         */
  getlex();
  if(strncmp(lex.detail.string , "}", 1) == 0) {

  if(valdat2.left != NULL)
    free(valdat2.left);
  if(valdat2.right != NULL)
    free(valdat2.right);
  if(valdat2.pnext != NULL)
    free(valdat2.pnext);

  if(idx_tmp_source != NULL)
    free(idx_tmp_source);

    return valdat;

  }
  ungetlex();

  // printf ("start interpret index\n");

  // first ident
  getlex();
  if(lex.type == TYPE_IDENT) {
      memset(&ident, '\0', sizeof(ident));
	  strcpy(ident, lex.detail.ident);
	  valdat = ValLabel( ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
  } else {
	  Error("salah indeks");
  }

  // printf("get idx ident:%s \n", ident);

  // get operator
  getlex();
  if(lex.type == TYPE_SYM && lex.detail.symbol != '}')
		ope = lex.detail.symbol;
  else if(lex.type == TYPE_SYM && lex.detail.symbol == '}')
		ope = '}';
  else
        Error("salah indeks");

  // printf("get ope: %c \n", ope);

  if(ope != '}') {
    // 2-nd ident or ope or numeric
    getlex();
	// printf("get type2: %d \n", lex.type);

    if(lex.type == TYPE_IDENT) {
      memset(&ident, '\0', sizeof(ident));
	  strcpy(ident, lex.detail.ident);
	  valdat2 = ValLabel( ident, sub_deep, valdat2, VAL_FLAG_SEARCH_R );
    } else if(lex.type == TYPE_SYM && lex.detail.symbol != '}') {
		ope2 = lex.detail.symbol;
	} else if(lex.type == TYPE_NUM) {
		num = lex.detail.num;
    } else {
	  Error("salah indeks");
    }

    // printf("get num:%d \n", num);

    if(valdat.datatype == 0) {
	  if(ope == '+') {
	    if(ope2 == '+') {
          // printf("plus plus\n");
	      valdat.val++;
	    } else if(num != 0) {
          // printf("plus\n");
		  valdat.val = valdat.val + num;
	    } else if(valdat2.datatype == 0) {
          // printf("plus val\n");
		  valdat.val = valdat.val + valdat2.val;
	    }
	  } else if(ope == '-') {
	    if(ope2 == '-') {
          // printf("min min\n");
	      valdat.val--;
	    } else if(num != 0) {
          // printf("minus\n");
		  valdat.val = valdat.val - num;
	    } else if(valdat2.datatype == 0) {
          // printf("minus val\n");
		  valdat.val = valdat.val - valdat2.val;
	    }
	  } else if(ope == '*') {
	    if(num != 0) {
          // printf("minus\n");
		  valdat.val = valdat.val * num;
	    } else if(valdat2.datatype == 0) {
          // printf("minus val\n");
		  valdat.val = valdat.val * valdat2.val;
		} else {
	      Error("salah indeks");
		}
	  } else {
	    Error("salah indeks");
	  }

	} else {
	  Error("salah indeks");
    }
  } 


  if(valdat2.left != NULL)
    free(valdat2.left);
  if(valdat2.right != NULL)
    free(valdat2.right);
  if(valdat2.pnext != NULL)
    free(valdat2.pnext);

  pg.pt      = tmp_pt;
  pg.back_pt = back_pt;
  pg.source  = NULL;
  pg.source  = idx_tmp_source;

  return valdat;
}
