// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keySelagi ()
{
  int i = 0, j = 0, k = 0;

  int num_depth  = 0; // for Selagi inside Selagi
  int num_depth2 = 0; // for Selagi inside Selagi
  int num_depth3 = 0; // for Selagi inside Selagi

  VAL_LABEL valdat;
  
  memset(&valdat, '\0', sizeof(valdat));

        while_flag++;
        // printf("before while_flag : %d \n", while_flag);

        if(while_flag > MAX_LOOP_LEN) {
          Error("Terlalu banyak pengulangan SELAGI");
        }

        posWhile[while_flag]  = pg.pt;
        backWhile[while_flag] = pg.back_pt;

        i = 0;
        do {
          getlex();
          i++;
        } while (lex.type != _LAKUKAN);
        whileLakuPos[while_flag] = pg.pt-1;
        /* printf("lakupos %d\n", lakupos); */

        pg.pt = posWhile[while_flag] ;
        pg.back_pt = backWhile[while_flag];


        /* Keep condition statement */
        i=0;
        pg.pt++;

        do {
         whileConditSource[while_flag][i] = pg.source[pg.pt++];
         i++;

         // printf("pg.pt %d char %c \n", pg.pt, pg.source[pg.pt]);

        } while(pg.pt != whileLakuPos[while_flag]);

        whileConditSource[while_flag][i-6] = '\0';

        // printf("%d condit %s\n", while_flag, whileConditSource[while_flag]);

        pg.pt = posWhile[while_flag];
        pg.back_pt =  backWhile[while_flag];

        do{
          getlex();
        }while( lex.type != _LAKUKAN && lex.type != _EOF );

        if( lex.type == _EOF )
           Error("SELAGI tanpa LAKUKAN");

        /* Keep Start Point to do WHILE loop */
        posWhileStart[while_flag]  = pg.pt;
        backWhileStart[while_flag] = pg.back_pt;

        // Please take care if there is(are) Selagi inside Selagi

        do{
            getlex();

			// Check Selagi inside Selagi
			if(lex.type == _SELAGI) {
              num_depth++;
			}

        }while( lex.type != _BALIKLAGI && lex.type != _EOF );

        if( lex.type == _EOF )
           Error("SELAGI tanpa BALIKLAGI");

		if(num_depth > 0) {
		  // there is(are) Selagi inside Selagi
		  for(j=0; j < num_depth; j++) {
            do{
              getlex();

			  // Check Selagi inside Selagi
			  if(lex.type == _SELAGI) {
                num_depth2++;
			  }

            }while( lex.type != _BALIKLAGI && lex.type != _EOF );

            if( lex.type == _EOF )
              Error("SELAGI tanpa BALIKLAGI");

		    if(num_depth2 > 0) {
		      // there is(are) Selagi inside Selagi
		      for(k=0; k < num_depth2; k++) { 
				do {
                  getlex();

			      // Check Selagi inside Selagi
			      if(lex.type == _SELAGI) {
                    num_depth3++;
			      }

				} while( lex.type != _BALIKLAGI && lex.type != _EOF );
                if( lex.type == _EOF )
                  Error("SELAGI tanpa BALIKLAGI");

		        if(num_depth3 > 0) {
		          // there is(are) Selagi inside Selagi
		          for(k=0; k < num_depth2; k++) { 
				    do {
                      getlex();
					} while( lex.type != _BALIKLAGI && lex.type != _EOF );
                    if( lex.type == _EOF )
                      Error("SELAGI tanpa BALIKLAGI");
				  }
				}

			  }
			}

		  }
		}


        /* Keep End Point of WHILE loop */
        posWhileTemp[while_flag]  = pg.pt;
        backWhileTemp[while_flag] = pg.back_pt;

        whileExecDone[while_flag] = 1; /* execute */

        while( interpretWhileCondition(whileConditSource[while_flag],
                                       posWhile[while_flag],
                                       backWhile[while_flag])  &&
                                       whileExecDone[while_flag]
                                       ) {
          
          pg.pt = posWhileStart[while_flag];
          pg.back_pt = backWhileStart[while_flag];

          InterpreterWhileIncr(posWhileTemp[while_flag]);
          
          pg.pt      = posWhileTemp[while_flag];
          pg.back_pt = backWhileTemp[while_flag];

          // printf("after while 1 : %d -> %d\n", while_flag, whileExecDone[while_flag]);

        }

        pg.pt      = posWhileTemp[while_flag];
        pg.back_pt = backWhileTemp[while_flag];

        whileExecDone[while_flag] = 0; /* done */

        while_flag--;

        // printf("after while 2 : %d -> %d\n", while_flag, whileExecDone[while_flag]);

        if(currentClass != NULL && strlen(currentClass) > 0) {
          // skip - do nothing
        } else {
          // go to the end of selagi
        }

}


int interpretWhileCondition(char *src, int tmp_pt, int back_pt) {
  VAL_LABEL valdat;
  char *source;
  char ident[MAX_IDENT_LEN];
  int  isSubstitut = 0;
  int  keep_pos = 0;
  int  back_pos = 0;

  source = NULL;
  source = src;

  // printf("inside interpretForCondition\n");

  /* valdat init */
  memset(&valdat, '\0', sizeof(valdat));
  valdat.val = 0;
  memset(&ident, '\0', sizeof(ident));  
  memset(&valdat.str, '\0', sizeof(valdat.str));

  tmp_source = pg.source;

  pg.pt      = 0;
  pg.back_pt = 0;
  pg.source  = source;

  //printf("inside source %s\n", pg.source);

  /* throw out ';' or '('  symbol            */
  getlex();

  /* skip if nothing                         */
  getlex();
  if(strncmp(lex.detail.string , ")", 1) == 0)
    return (int)NULL;
  if(strncmp(lex.detail.string , ";", 1) == 0)
    return (int)NULL;

  keep_pos = pg.pt;
  back_pos = pg.back_pt;

  if(lex.type == TYPE_IDENT) {
    // printf("inside Condit ident %s\n", lex.detail.ident);  
    strcpy(ident, lex.detail.ident);

	getlex();
	if(strncmp(lex.detail.string , "=", 1) == 0) {          // is equal
      getlex();
	  if(strncmp(lex.detail.string , "=", 1) != 0) {        // is not an equal
        isSubstitut = 1;
	  }
	  //printf("substitut in selagi\n");
	}
	pg.pt = keep_pos;
	pg.back_pt = back_pos;
  }

  ungetlex();
  valdat = expression();

  pg.source  = tmp_source;
  pg.pt      = tmp_pt;
  pg.back_pt = back_pt;

  src = NULL;

  //printf("inside result %d\n", valdat.val);
  //printf("inside result ident %s\n", valdat.ident);  
  //printf("inside result str %s\n", valdat.str);

  if(isSubstitut) {
    // save ident value
    ValLabel( ident, sub_deep, valdat, VAL_FLAG_SEARCH_W );    
  }

  return valdat.val;
}


void InterpreterWhileIncr( int endPos )
{

    /* Do as For - Function Program */
    /* printf("inside interpret : %d \n", loop_flag);*/
    do{

       Interpreter();

    }while( pg.pt <= endPos && lex.type != _BALIKLAGI  && lex.type != _EOF );

}

