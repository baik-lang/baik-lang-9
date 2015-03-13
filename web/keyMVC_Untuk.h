// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

MVCPARSING MVCInterpreterForInitIncr(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
void MVCInterpreterForIncr( int endPos, MVC_S_ADDR mvc_pg);
int MVCinterpretForCondition(char *src, int tmp_pt, int back_pt);

MVCPARSING keyMVC_Untuk(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  int i=0;
  int ret=0;
  VAL_LABEL valdat;

  MVCPARSING par;
      
  memset(&par, '\0', sizeof(par));
  
  memset(&valdat, '\0', sizeof(valdat));

        loop_flag++;
        if(loop_flag > MAX_LOOP_LEN) {
          Error("Terlalu banyak pengulangan UNTUK");
        }

        i=0;

        /* throw out ( */
        par = MVCgetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  = par.mvc_pg;

        //printf("key UNTUK lex %d %s <BR>\n", mvc_lex.type, mvc_lex.detail.string);

        if( mvc_lex.type != TYPE_MVC_SYM || strncmp(mvc_lex.detail.string , "(", 1) != 0 ) {
           Error("UNTUK salah : tanpa tanda (");
        }

        /* Keep init statement */
        i=0;
        forInitSource[loop_flag][i] = '('; i++;
        
        do {
          forInitSource[loop_flag][i] = mvc_pg.source[mvc_pg.pt];
          i++;
          mvc_pg.pt++;

        } while(mvc_pg.source[mvc_pg.pt] != ';' );

        forInitSource[loop_flag][i] = ')';

        //printf("MVC Untuk init source %s <BR>\n", forInitSource[loop_flag]);

        posForTemp[loop_flag]  = mvc_pg.pt;
        backForTemp[loop_flag] = mvc_pg.back_pt;

        // /////////////////////////////////////////////
        /* Interprete Increament                      */
        // /////////////////////////////////////////////
        // printf(" interpret FOR init : %s\n",  forInitSource[loop_flag]);
        memset(&tmp_for_source, '\0', sizeof(tmp_for_source));
        tmp_for_source = mvc_pg.source;
        
        mvc_pg.source = forInitSource[loop_flag];
        mvc_pg.pt = 0;

        par = MVCInterpreterForInitIncr(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg = par.mvc_pg;

        //printf(" MVC interpret FOR init OK /////////////////// <BR>\n");

        mvc_pg.source  = tmp_for_source;
        mvc_pg.pt      = posForTemp[loop_flag];
        mvc_pg.back_pt = backForTemp[loop_flag];

        /* throw out sym ; */
        par = MVCgetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  =par.mvc_pg;

        //printf("type %d\n", mvc_lex.type);

        if( mvc_lex.type != TYPE_MVC_SYM || strncmp(mvc_lex.detail.string , ";", 1) != 0 ) {
           Error("kode UNTUK salah : setelah inisialisasi harus ada tanda ;");
        }

        /* Keep condition statement */
        i=0;
	forConditSource[loop_flag][i] = '\0';
        forConditSource[loop_flag][i] = '('; i++;

        do {
	 if(mvc_pg.source[mvc_pg.pt] != ' ') {
           forConditSource[loop_flag][i] = mvc_pg.source[mvc_pg.pt];
           i++;
		 }
           mvc_pg.pt++;

        } while(mvc_pg.source[mvc_pg.pt] != ';' );

        forConditSource[loop_flag][i] = ')';
        forConditSource[loop_flag][i+1] = '\0';

        //printf("condit src %s\n", forConditSource[loop_flag]);

        do{
              par = MVCgetlex(mvc_lex, mvc_pg);
              mvc_lex = par.mvc_lex;
              mvc_pg  =par.mvc_pg;	      
	      
	}while( strncmp(mvc_lex.detail.string , ";", 1) != 0 && mvc_lex.type != _MVC_EOF );

        if( mvc_lex.type == _MVC_EOF )
           Error("UNTUK salah : tanpa tanda ;");

        if( mvc_lex.type != TYPE_MVC_SYM || strncmp(mvc_lex.detail.string , ";", 1) != 0 ) {
           Error("kode UNTUK salah : setelah kondisi harus ada tanda ;");
        }

        /* Keep increase statement */
        i=0;
        forPlusSource[loop_flag][i] = '('; i++;
        do {
         forPlusSource[loop_flag][i] = mvc_pg.source[mvc_pg.pt];
         i++;
         mvc_pg.pt++;

        } while(mvc_pg.source[mvc_pg.pt] != ')' );

        forPlusSource[loop_flag][i] = ')';
        
        //printf("incr forPlusSource[loop_flag] %s\n", forPlusSource[loop_flag]);

        do{
          par = MVCgetlex(mvc_lex, mvc_pg);
          mvc_lex = par.mvc_lex;
          mvc_pg  =par.mvc_pg;	      
	}while( strncmp(mvc_lex.detail.string , ")", 1) != 0 && mvc_lex.type != _MVC_EOF );

        if( mvc_lex.type == _MVC_EOF )
           Error("UNTUK salah : tanpa tanda )");

        do{
          par = MVCgetlex(mvc_lex, mvc_pg);
          mvc_lex = par.mvc_lex;
          mvc_pg  =par.mvc_pg;          
          //printf("lex %d %s\n", mvc_lex.type, mvc_lex.detail.string);
        }while( mvc_lex.type != _MVC_ULANG && mvc_lex.type != _MVC_EOF );

        if( mvc_lex.type == _MVC_EOF )
           Error("UNTUK tanpa ULANG");

        //printf("check ULANG OK , lex %d , pt %d <BR>\n", mvc_lex.type, mvc_pg.pt);
        
        /* Keep Start Point to do FOR loop */
        posForStart[loop_flag]  = mvc_pg.pt;
        backForStart[loop_flag] = mvc_pg.back_pt;

        do{
          par = MVCgetlex(mvc_lex, mvc_pg);
          mvc_lex = par.mvc_lex;
          mvc_pg  =par.mvc_pg;                    
          //printf("lex %d %s\n", mvc_lex.type, mvc_lex.detail.string);
        }while( mvc_lex.type != _MVC_LAGI && mvc_lex.type != _MVC_EOF );

        if( mvc_lex.type == _MVC_EOF )
           Error("UNTUK tanpa LAGI");

        posForTemp[loop_flag]  = mvc_pg.pt;
        backForTemp[loop_flag] = mvc_pg.back_pt;

        forExecDone[loop_flag] = 0; /* execute before done */

        //printf("check LAGI OK, type %d, pt %d <BR>\n", mvc_lex.type, mvc_pg.pt);
        
        //printf("LOOP START %d -> %s \n", loop_flag, forConditSource[loop_flag]); 

        // printf("forExecDone[loop_flag] %d\n", forExecDone[loop_flag]);

        while( MVCinterpretForCondition(forConditSource[loop_flag],
                                     posForStart[loop_flag],
                                     backForStart[loop_flag] ) &&
                                     !forExecDone[loop_flag]
                                     ) {
          /* Interprete LOOP contents                   */
          //printf(" interpret LOOP start <BR>\n"); 

          mvc_pg.pt = posForStart[loop_flag];
          mvc_pg.back_pt = backForStart[loop_flag];

          MVCInterpreterForIncr( posForTemp[loop_flag], mvc_pg );
          
	  //printf(" interpret LOOP OK <BR>\n");          

	  // /////////////////////////////////////////////
          /* Interprete Increament                      */
	  // /////////////////////////////////////////////
	  // printf(" interpret FOR plus : %s\n",  forPlusSource[loop_flag]);
          memset(&tmp_for_source, '\0', sizeof(tmp_for_source));

          tmp_for_source = mvc_pg.source;
          mvc_pg.source  = forPlusSource[loop_flag];
          mvc_pg.pt =  0;

          par = MVCInterpreterForInitIncr(mvc_lex, mvc_pg);

	  //printf(" interpret plus OK\n");
	  mvc_pg.source  = tmp_for_source;

          mvc_pg.pt      = posForTemp[loop_flag];
          mvc_pg.back_pt = backForTemp[loop_flag];

        }

        mvc_pg.pt      = posForTemp[loop_flag];
        mvc_pg.back_pt = backForTemp[loop_flag];

        forExecDone[loop_flag] = 1; /* already done */

        //printf("after loop, loop_flag: %d \n", loop_flag);
        //printf("after loop, pt: %d <BR>\n", mvc_pg.pt);

	if(loop_flag > 0)
          loop_flag--;

        /* printf("after loop: %d \n", loop_flag); */
        /* printf("after loop pos string: %s \n", lex.detail.string); */

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

  par.mvc_lex = mvc_lex;
  par.mvc_pg  = mvc_pg;

  return par;
}


int MVCinterpretForCondition(char *src, int tmp_pt, int back_pt) {
  VAL_LABEL valdat;
  char *source;

  MVC_LEX_T mvc_lex;
  MVC_S_ADDR mvc_pg;
    
  MVCPARSING par;
      
  memset(&par, '\0', sizeof(par));
  memset( &mvc_lex, 0, sizeof(mvc_lex) );
  memset( &mvc_pg, 0, sizeof(mvc_pg) );

  source = NULL;
  source = src;

  //printf("inside interpretForCondition ... <BR>\n");

  /* valdat init */
  memset(&valdat, '\0', sizeof(valdat));
  valdat.val = 0;
  memset(&valdat.str, '\0', sizeof(valdat.str));

  tmp_condit_source = pg.source;

  mvc_pg.pt      = 0;
  mvc_pg.back_pt = 0;
  memset(&mvc_pg.source, '\0', sizeof(mvc_pg.source));
  mvc_pg.source  = source;

  //printf("inside condit source %s <BR>\n", mvc_pg.source);

  /* throw out ';' or '('  symbol            */
  par = MVCgetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;  

  /* skip if nothing                         */
  par = MVCgetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;                    

  if(strncmp(mvc_lex.detail.string , ")", 1) == 0)
    return (int)NULL;
  if(strncmp(mvc_lex.detail.string , ";", 1) == 0)
    return (int)NULL;

  par = MVCungetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;                      

  //printf("before MVC expression\n");  
  par = MVC_expression(mvc_lex, mvc_pg);
  //printf("after MVC expression\n");  

  mvc_pg.source  = tmp_condit_source;
  mvc_pg.pt      = tmp_pt;
  mvc_pg.back_pt = back_pt;

  //printf("inside condit result %d <BR>\n", par.val);

  tmp_condit_source = NULL;

  valdat.val = par.val;
  valdat.datatype = par.datatype;

  return valdat.val;
}

MVCPARSING MVCInterpreterForInitIncr(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  VAL_LABEL tmpdat; // saving value

  MVCPARSING par;
      
  memset(&par, '\0', sizeof(par));

  int plusplus=0;
  VAL_LABEL valdat, datx;
  char ident[MAX_STRING_LEN];
  char class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&datx, '\0', sizeof(datx));
  memset(&ident, '\0', sizeof(ident));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    //printf("MVCInterpreterForInitIncr <BR>\n");

    /* throw out '(' symbol                   */
    par = MVCgetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  =par.mvc_pg;  

    par = MVCgetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  =par.mvc_pg;  

    if(strncmp(mvc_lex.detail.string , ")", 1) == 0)
      return par;

    par = MVCungetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  =par.mvc_pg;      

    //printf("param src: %s <BR>\n", mvc_pg.source);

    do{
      memset(&valdat, '\0', sizeof(valdat));
      memset(&datx, '\0', sizeof(datx));
      memset(&ident, '\0', sizeof(ident));
         
      // first ident
      par = MVCgetlex(mvc_lex, mvc_pg);
      mvc_lex = par.mvc_lex;
      mvc_pg  =par.mvc_pg;  

      //printf("do type %d first ident: %s\n", mvc_lex.type, mvc_lex.detail.string);

      if(mvc_lex.type == TYPE_MVC_IDENT) {
        // keep first ident in memory
        memset(&ident, '\0', sizeof(ident));
        strcpy(ident, mvc_lex.detail.ident);

        // get equal sym or plusplus
        par = MVCgetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  =par.mvc_pg;  	    
	    
        // printf("ident: %s\n", lex.detail.string);
        if( mvc_lex.type == _MVC_EOF )
          Error("interupsi yang tidak diinginkan");

        if( mvc_lex.type == TYPE_MVC_SYM && (mvc_lex.detail.symbol == '=' || mvc_lex.detail.symbol == '+' || mvc_lex.detail.symbol == '-')) {
          // substitusi atau ++ atau --
	      if( mvc_lex.detail.symbol == '+' )  {
	        plusplus = 1;
	      } else if( mvc_lex.detail.symbol == '-' )  {
	        plusplus = -1;
	      }
	    } else {
          Error("salah parameter Untuk! bukan masukan atau operasi matematik");
	    }

        // get value
        // printf("get value\n");
        
        par = MVCgetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  =par.mvc_pg;  	    

        // printf("type %d", mvc_lex.type);

        if( mvc_lex.type == TYPE_MVC_SYM && mvc_lex.detail.symbol == '+' )  { // plusplus
	  if(plusplus == 1) {
	    // printf("plusplus \n");

            datx = ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_R );

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

            datx = ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_R );

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
            memset(&datx, 0, sizeof(datx));
            //printf("get lex %d \n", mvc_lex.type);

	    if(mvc_lex.type == TYPE_MVC_NUM) {
		  datx.val = mvc_lex.detail.num;
		  datx.datatype = 0;

                  //printf("get val %d \n", datx.val);		  
		  
            } else if(mvc_lex.type == TYPE_MVC_STR) {
                if(mvc_lex.detail.string != '\0' && strlen(mvc_lex.detail.string) > 0) {
                  strcpy(datx.str , mvc_lex.detail.string);
	        } else {
                  strcpy(datx.str , "");
	        }
		  datx.datatype = 3;
	    } else if(mvc_lex.type == TYPE_MVC_IDENT) {

 	      //printf("Ident val : %s\n", mvc_lex.detail.ident);

              par = MVCungetlex(mvc_lex, mvc_pg);
              mvc_lex = par.mvc_lex;
              mvc_pg  =par.mvc_pg;  	    
              par = MVCungetlex(mvc_lex, mvc_pg);
              mvc_lex = par.mvc_lex;
              mvc_pg  = par.mvc_pg;  	    

 	      //printf("pt before expression : %d\n", mvc_pg.pt);
              par = MVC_expression(mvc_lex, mvc_pg);
              mvc_lex = par.mvc_lex;
              mvc_pg  = par.mvc_pg;

 	      //printf("pt after expression : %d\n", mvc_pg.pt);

	      // valdat = ValLabel( mvc_lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              datx.val       = par.val;
              datx.floatdata = par.floatdata;
	      datx.datatype  = par.datatype;

	      //printf("get datatype :%d , val : %d \n", datx.datatype, datx.val);

            }
 
	//printf("ForInitIncr saving ident ...%s  deep %d <BR>\n", ident, sub_deep);
	//printf("saving type ...%d <BR>\n", datx.datatype);
	//printf("saving value ...%d <BR>\n", datx.val);
	//printf("saving dbl ...%f\n", datx.floatdata);

	ValLabel( ident, sub_deep, datx, VAL_FLAG_SEARCH_W );
		
      }

      //printf("after do type %d string: %s\n", mvc_lex.type, mvc_lex.detail.string);


    }while( mvc_lex.type != _MVC_EOF && strncmp(mvc_lex.detail.string , ";", 1) != 0  &&
		    strncmp(mvc_lex.detail.string , ")", 1) != 0);

    return par;

}

void MVCInterpreterForIncr( int endPos, MVC_S_ADDR mvc_pg)
{
  char ident[MAX_IDENT_LEN];
  VAL_LABEL tmpdat;

  MVC_LEX_T mvc_lex;
    
  MVCPARSING par;
      
  memset(&par, '\0', sizeof(par));
  memset( &mvc_lex, 0, sizeof(mvc_lex) );

  memset(&ident, '\0', sizeof(ident));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  /* Do as For - Function Program */
  //printf("\n===inside FOR interpret, loop_flag: %d <BR>\n", loop_flag);
  //printf("start pt %d, end %d <BR>\n", mvc_pg.pt, endPos);

    do{

       par = MVCInterpreter(mvc_pg.source, mvc_pg.pt, endPos);
       mvc_lex = par.mvc_lex;
       mvc_pg = par.mvc_pg;

       //printf("===after FOR interpret, loop_flag: %d , after a loop Pos %d <BR>\n", loop_flag, pg.pt);

    }while( mvc_pg.pt != endPos && mvc_lex.type != _MVC_LAGI  && mvc_lex.type != _MVC_EOF );

    mvc_pg.source  = tmp_for_source;

    if(loop_flag > 1) {
      do{
        // getlex();
        par = MVCgetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  =par.mvc_pg;  	    

      }while( mvc_pg.pt != endPos && mvc_lex.type != _LAGI  && strncmp(mvc_lex.detail.string , "}", 1) != 0 && mvc_lex.type != _MVC_EOF );

   }

}

