// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyKalau ()
{
    VAL_LABEL valdat;
	int num_kalau=0;
	int num_akhirkalau=0;

	memset(&valdat, '\0', sizeof(valdat));

    if_deep++;

    valdat = expression();
    //printf("KALAU cond val %d\n", valdat.val);

	if( valdat.val ){
      // printf("condit OK\n");
      currKalauResult[if_deep] = 1; 
	  do{
	    getlex();
	  }while( lex.type != _MAKA && lex.type != _EOF );
	  if( lex.type == _EOF )
	    Error("KALAU tanpa MAKA");
	}
	else{
     // printf("condit false\n");
     currKalauResult[if_deep] = 0; 

	  do{
	    getlex();

		if( lex.type == _KALAU ) {
	      num_kalau++;
		  if_deep++;
		}
	    if( lex.type == _STOPKALAU ) {
	      num_akhirkalau--;
		  if_deep--;
		}

		// printf("lex %s\n", lex.detail.string);
		// printf("num kalau %d\n", num_kalau);
		// printf("num akhir %d\n", num_akhirkalau);

		if(num_kalau != num_akhirkalau && num_kalau >=0 && num_akhirkalau >= 0) {
          // there is kalau inside kalau
			do {
              getlex();
			}while( lex.type != _STOPKALAU && lex.type != _EOF );
			ungetlex();
		}

	  }while( (lex.type != _STOPKALAU ) && 
                   lex.type != _KELUARSELAGI &&
                   lex.type != _KELUARUNTUK &&
                   lex.type != _LANJUT &&
                   lex.type != _LAINNYA && 
                   lex.type != _LAINKALAU && 
				   lex.type != _EOF );
       // printf("type %d\n", lex.type);

	  if( lex.type == _EOF )
	    Error("KALAU tanpa STOPKALAU");
	}

	if(lex.type == _LAINKALAU)
	  ungetlex();

}

void keyLainKalau ()
{
    VAL_LABEL valdat;
	int num_kalau=0;
	int num_akhirkalau=0;

    memset(&valdat, '\0', sizeof(valdat));
    valdat = expression();
    // printf("cond val %d\n", valdat.val);

	if( valdat.val ){
	  // condit OK
      currKalauResult[if_deep] = 1; 
	  do{
	    getlex();
	  }while( lex.type != _MAKA && lex.type != _EOF );
	  if( lex.type == _EOF )
	    Error("LAINKALAU tanpa MAKA");
	}
	else{
	  // condit NG
      currKalauResult[if_deep] = 0; 
	  do{
	    getlex();

		if( lex.type == _KALAU ) {
	      num_kalau++;
		  if_deep++;
		}
	    if( lex.type == _STOPKALAU ) {
	      num_akhirkalau--;
		  if_deep--;
		}

		if(num_kalau != num_akhirkalau && num_kalau >= 0 && num_akhirkalau >= 0) {
          // there is kalau inside lainkalau
			do {
              getlex();
			}while( lex.type != _STOPKALAU && lex.type != _EOF );
			ungetlex();
		}

	  }while( (lex.type != _STOPKALAU ) && 
                   lex.type != _KELUARSELAGI &&
                   lex.type != _KELUARUNTUK &&
                   lex.type != _LANJUT &&
                   lex.type != _LAINNYA && 
                   lex.type != _LAINKALAU && 
                   lex.type != _EOF );
	  if( lex.type == _EOF )
	    Error("KALAU tanpa STOPKALAU");
	}

	if(lex.type == _LAINNYA || lex.type == _LAINKALAU) {
	  ungetlex();
	}

}

