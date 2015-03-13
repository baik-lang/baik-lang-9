// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyObject (char object_str[MAX_STRING_LEN])
{
  int  n=0, i=0;

  char ident[MAX_STRING_LEN];
  char dat_a[MAX_STRING_LEN];
  char dat_b[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&ident, '\0', sizeof(ident));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  
  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


        // printf("DEBUG: case TYPE_OBJECT\n");

	    strcpy( ident, object_str );

        // object name
        strcpy(dat_a, getObjectName(object_str) );
        // object param
        strcpy(dat_b, getObjectParam(object_str) );
        
        /*
        printf("For TREE object str : %s , len %d\n",ident, strlen(ident));
        
        printf("For Check obj name: %s\n",dat_a);
        printf("For Check obj param: %s len %d\n",dat_b, strlen(dat_b));
        */

        // check for member existance and scope
        checkObjectValidation(object_str);

	    getlex();
	    if( lex.type == _EOF )
	     Error("interupsi yang tidak diinginkan");

	    if( lex.detail.symbol != '=' )    
	     Error("benda salah masukan");

        getlex();
	    if( lex.type == _EOF )
	     Error("interupsi yang tidak diinginkan");

        ungetlex();
        // printf("start ekspresi\n");
        valdat = expression();

        strcpy(valdat.ident, ident);
        strcpy(valdat.benda_name, dat_a);
        strcpy(valdat.benda_param, dat_b);
        valdat.isClassVar = 1;

        /*
        printf("For TREE ident : %s\n",ident);
        printf("For TREE datatype %d\n",valdat.datatype);
        printf("For TREE val %d\n",valdat.val);
        printf("For TREE dbl %f\n",valdat.floatdata);
        */

        // write into tree
        ValLabel( ident, class_sub_deep, valdat, VAL_FLAG_SEARCH_W );
}

