// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

void keyUntuk()
{
  int i=0;
  VAL_LABEL valdat;

  memset(&valdat, '\0', sizeof(valdat));

        loop_flag++;
        if(loop_flag > MAX_LOOP_LEN) {
          Error("Terlalu banyak pengulangan UNTUK");
        }

        i=0;

        /* throw out ( */
        getlex();

        if( lex.type != TYPE_SYM || strncmp(lex.detail.string , "(", 1) != 0 ) {
           Error("UNTUK salah : tanpa tanda (");
        }

        /* Keep init statement */
        i=0;
        forInitSource[loop_flag][i] = '('; i++;
        
        do {
         forInitSource[loop_flag][i] = pg.source[pg.pt];
         i++;
         pg.pt++;

        } while(pg.source[pg.pt] != ';' );

        forInitSource[loop_flag][i] = ')';
        // printf("init source %s\n", forInitSource[loop_flag]);

        posForTemp[loop_flag]  = pg.pt;
        backForTemp[loop_flag] = pg.back_pt;

	    // /////////////////////////////////////////////
        /* Interprete Increament                      */
	    // /////////////////////////////////////////////
	    // printf(" interpret FOR init : %s\n",  forInitSource[loop_flag]);
        memset(&tmp_for_source, '\0', sizeof(tmp_for_source));
        tmp_for_source = pg.source;
        
        pg.source = forInitSource[loop_flag];
        pg.pt = 0;

        InterpreterForInitIncr();

        // printf(" interpret FOR init OK\n");

	    pg.source  = tmp_for_source;
        pg.pt      = posForTemp[loop_flag];
        pg.back_pt = backForTemp[loop_flag];

        /* throw out sym ; */
        getlex();

        if( lex.type != TYPE_SYM || strncmp(lex.detail.string , ";", 1) != 0 ) {
           Error("kode UNTUK salah : setelah inisialisasi harus ada tanda ;");
        }

        /* Keep condition statement */
        i=0;
		forConditSource[loop_flag][i] = '\0';
        forConditSource[loop_flag][i] = '('; i++;

        do {
		 if(pg.source[pg.pt] != ' ') {
           forConditSource[loop_flag][i] = pg.source[pg.pt];
           i++;
		 }
           pg.pt++;

        } while(pg.source[pg.pt] != ';' );

        forConditSource[loop_flag][i] = ')';
        forConditSource[loop_flag][i+1] = '\0';

        // printf("condit src %s\n", forConditSource[loop_flag]);

        do{
	      getlex();
	    }while( strncmp(lex.detail.string , ";", 1) != 0 && lex.type != _EOF );

        if( lex.type == _EOF )
           Error("UNTUK salah : tanpa tanda ;");

        if( lex.type != TYPE_SYM || strncmp(lex.detail.string , ";", 1) != 0 ) {
           Error("kode UNTUK salah : setelah kondisi harus ada tanda ;");
        }

        /* Keep increase statement */
        i=0;
        forPlusSource[loop_flag][i] = '('; i++;
        do {
         forPlusSource[loop_flag][i] = pg.source[pg.pt];
         i++;
         pg.pt++;

        } while(pg.source[pg.pt] != ')' );

        forPlusSource[loop_flag][i] = ')';
        // printf("incr forPlusSource[loop_flag] %s\n", forPlusSource[loop_flag]);

        do{
	      getlex();
	    }while( strncmp(lex.detail.string , ")", 1) != 0 && lex.type != _EOF );

        if( lex.type == _EOF )
           Error("UNTUK salah : tanpa tanda )");

        do{
          getlex();
        }while( lex.type != _ULANG && lex.type != _EOF );

        if( lex.type == _EOF )
           Error("UNTUK tanpa ULANG");

        /* Keep Start Point to do FOR loop */
        posForStart[loop_flag]  = pg.pt;
        backForStart[loop_flag] = pg.back_pt;

        do{
          getlex();
        }while( lex.type != _LAGI && lex.type != _EOF );

        if( lex.type == _EOF )
           Error("UNTUK tanpa LAGI");

        posForTemp[loop_flag]  = pg.pt;
        backForTemp[loop_flag] = pg.back_pt;

        forExecDone[loop_flag] = 0; /* execute before done */

        //printf("loop %d -> %s \n", loop_flag, forConditSource[loop_flag]); 

        // printf("forExecDone[loop_flag] %d\n", forExecDone[loop_flag]);

        while( interpretForCondition(forConditSource[loop_flag],
                                     posForStart[loop_flag],
                                     backForStart[loop_flag] ) &&
                                     !forExecDone[loop_flag]
                                     ) {
          /* Interprete LOOP contents                   */
          //printf(" interpret LOOP start\n"); 

          pg.pt = posForStart[loop_flag];
          pg.back_pt = backForStart[loop_flag];

          InterpreterForIncr( posForTemp[loop_flag] );
          
		  //printf(" interpret OK\n");          

		  // /////////////////////////////////////////////
          /* Interprete Increament                      */
		  // /////////////////////////////////////////////
		  // printf(" interpret FOR plus : %s\n",  forPlusSource[loop_flag]);
          memset(&tmp_for_source, '\0', sizeof(tmp_for_source));

          tmp_for_source = pg.source;
          pg.source  = forPlusSource[loop_flag];
          pg.pt =  0;

          InterpreterForInitIncr();

	      // printf(" interpret plus OK\n");
	      pg.source  = tmp_for_source;

          pg.pt      = posForTemp[loop_flag];
          pg.back_pt = backForTemp[loop_flag];

        }

        pg.pt      = posForTemp[loop_flag];
        pg.back_pt = backForTemp[loop_flag];

        forExecDone[loop_flag] = 1; /* already done */

        /* printf("after loop: %d \n", loop_flag); */

		if(loop_flag > 0)
        loop_flag--;

        /* printf("after loop: %d \n", loop_flag); */
        /* printf("after loop pos string: %s \n", lex.detail.string); */

  if(valdat.filename != NULL)
    free(valdat.filename);
  if(valdat.folder != NULL)
    free(valdat.folder);
  if(valdat.filedata != NULL)
    free(valdat.filedata);
  if(valdat.long_str != NULL)
    free(valdat.long_str);

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

}


int interpretForCondition(char *src, int tmp_pt, int back_pt) {
  VAL_LABEL valdat;
  char *source;

  source = NULL;
  source = src;

  // printf("inside interpretForCondition\n");

  /* valdat init */
  memset(&valdat, '\0', sizeof(valdat));
  valdat.val = 0;
  memset(&valdat.str, '\0', sizeof(valdat.str));

  tmp_condit_source = pg.source;

  pg.pt      = 0;
  pg.back_pt = 0;
  memset(&pg.source, '\0', sizeof(pg.source));
  pg.source  = source;

  // printf("inside condit source %s\n", pg.source);

  /* throw out ';' or '('  symbol            */
  getlex();

  /* skip if nothing                         */
  getlex();
  if(strncmp(lex.detail.string , ")", 1) == 0)
    return (int)NULL;
  if(strncmp(lex.detail.string , ";", 1) == 0)
    return (int)NULL;

  ungetlex();
  valdat = expression();

  pg.source  = tmp_condit_source;
  pg.pt      = tmp_pt;
  pg.back_pt = back_pt;

  // printf("inside result %d\n", valdat.val);

  tmp_condit_source = NULL;

  return valdat.val;
}

void InterpreterForInitIncr()
{
  VAL_LABEL tmpdat; // saving value

  int plusplus=0;
  VAL_LABEL valdat, datx;
  char ident[MAX_STRING_LEN];
  char class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&datx, '\0', sizeof(datx));
  memset(&ident, '\0', sizeof(ident));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    pg.pt      = 0;
    pg.back_pt = 0;

    /* throw out '(' symbol                   */
    getlex();

    getlex();
    if(strncmp(lex.detail.string , ")", 1) == 0)
      return;

    ungetlex();

    // printf("param src: %s\n", pg.source);

    do{
      memset(&valdat, '\0', sizeof(valdat));
      memset(&datx, '\0', sizeof(datx));
      memset(&ident, '\0', sizeof(ident));
         
      // first ident
      getlex();
      // printf("type %d ident: %s\n", lex.type, lex.detail.string);

      if(lex.type == TYPE_IDENT) {
        // keep first ident in memory
        memset(&ident, '\0', sizeof(ident));
	    strcpy(ident, lex.detail.ident);

        // get equal sym or plusplus
	    getlex();
	    // printf("ident: %s\n", lex.detail.string);
	    if( lex.type == _EOF )
          Error("interupsi yang tidak diinginkan");

        if( lex.type == TYPE_SYM && (lex.detail.symbol == '=' || lex.detail.symbol == '+' || lex.detail.symbol == '-')) {
          // substitusi atau ++ atau --
	      if( lex.detail.symbol == '+' )  {
	        plusplus = 1;
	      } else if( lex.detail.symbol == '-' )  {
	        plusplus = -1;
	      }
	    } else {
          Error("salah parameter Untuk! bukan masukan atau operasi matematik");
	    }

        // get value
	    getlex();

	    if( lex.type == TYPE_SYM && lex.detail.symbol == '+' )  { // plusplus
		  if(plusplus == 1) {
		    // printf("plusplus \n");

            // datx = ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_R );

            if(currentClass != NULL && strlen(currentClass) > 0) {
              sprintf(class_tmpvar, "%s->%s", currentClass, ident);
              datx = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
            } else {
              datx = ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
            }

			if(datx.ident != NULL && datx.datatype == 0) {
			  datx.val++;
              //ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_W );
			} else
			if(datx.ident != NULL && datx.datatype == 1) {
			  datx.floatdata = datx.floatdata + 1.0;
              //ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_W );
			}
		  }
	    } else if( lex.detail.symbol == '-' )  { // minmin
		  if(plusplus == -1) {
		    // printf("minmin \n");

            // datx = ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_R );

            if(currentClass != NULL && strlen(currentClass) > 0) {
              sprintf(class_tmpvar, "%s->%s", currentClass, ident);
              datx = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
            } else {
              datx = ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
            }

			if(datx.ident != NULL && datx.datatype == 0) {
			  datx.val--;
              //ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_W );
			} else
			if(datx.ident != NULL && datx.datatype == 1) {
			  datx.floatdata = datx.floatdata + 1.0;
              //ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_W );
			}
		  }
	    } else

	    if(lex.type == TYPE_NUM) {
		  datx.val = lex.detail.num;
		  datx.datatype = 0;
	    } else if(lex.type == TYPE_DBL) {
		  datx.floatdata = lex.detail.dblnum;
		  datx.datatype = 1;
        } else if(lex.type == TYPE_STR) {
            if(lex.detail.string != '\0' && strlen(lex.detail.string) > 0) {
                  strcpy(datx.str , lex.detail.string);
	        } else {
                  strcpy(datx.str , "");
	        }
		  datx.datatype = 3;
	    } else if(lex.type == TYPE_IDENT) {
		  // printf("ident val : %s\n", lex.detail.ident);
	      // valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
          ungetlex();
          ungetlex();
          valdat = expression();

		  // printf("get datatype :%d , val : %d \n", valdat.datatype, valdat.val);
          datx = valdat;
		  datx.datatype = valdat.datatype;
        }

	    // printf("saving ident ...%s\n", ident);
	    // printf("saving type ...%d\n", datx.datatype);
	    //printf("saving value ...%d\n", datx.val);
	    //printf("saving dbl ...%f\n", datx.floatdata);
        // save ident

	    // ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_W );
		
		if(currentClass != NULL && strlen(currentClass) > 0) {
		   memset(&class_tmpvar, '\0', sizeof(class_tmpvar));
           sprintf(class_tmpvar, "%s->%s", currentClass, ident);
	       // printf("saving ident ...%s\n",class_tmpvar);
	       ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_W );
        } else {
	       // printf("saving ident ...%s\n", ident);
	       ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_W );
        }

      }

    }while( lex.type != _EOF && strncmp(lex.detail.string , ";", 1) != 0  &&
		    strncmp(lex.detail.string , ")", 1) != 0);


}

void InterpreterForIncr( int endPos )
{
  char ident[MAX_IDENT_LEN];
  VAL_LABEL tmpdat;

  memset(&ident, '\0', sizeof(ident));
  memset(&tmpdat, '\0', sizeof(tmpdat));

    /* Do as For - Function Program */
    //printf("\n===inside FOR interpret, loop_flag: %d , endPos %d\n", loop_flag, endPos);
    do{

       Interpreter();

	   //printf("===after FOR interpret, loop_flag: %d , after a loop Pos %d\n", loop_flag, pg.pt);

    }while( pg.pt != endPos && lex.type != _LAGI  && lex.type != _EOF );

    pg.source  = tmp_for_source;

	if(loop_flag > 1) {
      do{
        getlex();

		switch( lex.type )
		{

        case _CEK_MEMORI:
  	      // debug inside Tree
          ValLabel( "", 0, tmpdat, VAL_FLAG_PRINT );
	    break;

        case _RETURN:
	      getlex();

	      switch( lex.type )
	      {
	       case TYPE_STR:
              if(lex.detail.string  != '\0' && strlen(lex.detail.string) > 0) {
                strcpy(returnVal.str , lex.detail.string );
              } else {
                strcpy(returnVal.str , "" );
              }
              returnVal.datatype = 3;
	       break;
	    
	       case TYPE_NUM:
              returnVal.val = lex.detail.num;
              returnVal.datatype = 0;
	       break;

	       case TYPE_IDENT:
	       case TYPE_ARRAY:
			  // printf ("return IDENT / ARRAY : %s\n", lex.detail.ident);
              memset(&tmpdat, '\0', sizeof(tmpdat));
			  tmpdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
	          //ungetlex();
              //tmpdat = expression();

			  // printf ("type %d, val %d\n", tmpdat.datatype, tmpdat.val);
              if(tmpdat.datatype == 0) {
	            returnVal.val = tmpdat.val;
                returnVal.datatype = 0;
              } else if(tmpdat.datatype == 3) {
                strcpy(returnVal.str , tmpdat.str );
                returnVal.datatype = 3;
              } else {
                returnVal = tmpdat;
              }

			  if(sub_deep > 0) {
	            // printf ("return IDENT OK, try to go to ending ...\n");
	            while( lex.type != TYPE_SYM && lex.detail.symbol != '}' ) {
                getlex();
	            if( lex.type == _EOF )
	              Error("RETURN error");
                }
	          }

	       break;

	       default:
	         Error("kode perintah RETURN salah");
	       }
	    break;

        case TYPE_SYM:
          if( lex.type == TYPE_SYM && lex.detail.symbol == '&' )  {
	        strcpy( ident, "");
		    // sub routine
            keySub(ident);
		  }
	    break;

        case _UNTAI:
          strcpy( ident, "");
	  	  // sub routine
          keyUntaian(ident);
	    break;

        case TYPE_ARRAY:
          strcpy( ident, lex.detail.array_str);
		  // sub routine
          keyArray(ident);
	    break;

        }

      }while( pg.pt != endPos && lex.type != _LAGI  && strncmp(lex.detail.string , "}", 1) != 0 && lex.type != _EOF );
	}

}

