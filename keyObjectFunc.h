// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// 2010/12/17


void keyObjectFunc (char object_str[MAX_STRING_LEN])
{
  int  n=0, i=0;

  char ident[MAX_STRING_LEN];
  char dat_a[MAX_STRING_LEN];
  char dat_b[MAX_STRING_LEN];
  char dat_c[MAX_STRING_LEN];
  char dat_d[MAX_STRING_LEN];

  char tmp_str[MAX_STRING_LEN];
  char tmpMsg[MAX_STRING_LEN];
  char logMsg[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  char **mysplit;
  char sub_tmpparam[MAX_STRING_LEN*2];

  char get_param[MAX_STRING_LEN],
       orig_param[MAX_STRING_LEN],
       param_source[MAX_STRING_LEN * 2];
  char each_param[MAX_STRING_LEN];

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&ident, '\0', sizeof(ident));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  memset(&dat_c, '\0', sizeof(dat_c));
  memset(&dat_d, '\0', sizeof(dat_d));

  memset(&tmp_str, '\0', sizeof(tmp_str));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));
  memset(&logMsg, '\0', sizeof(logMsg));
  memset(&tmpnode, '\0', sizeof(tmpnode));

  memset(&sub_tmpparam, '\0', sizeof(sub_tmpparam));

  memset(&get_param, '\0', sizeof(get_param));
  memset(&orig_param, '\0', sizeof(orig_param));
  memset(&param_source, '\0', sizeof(param_source));
  memset(&each_param, '\0', sizeof(each_param));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  mysplit = NULL;

        //printf("DEBUG: case TYPE_OBJECT_FUNC\n");
        //printf("DEBUG: sub_deep %d\n", sub_deep);
        //printf("DEBUG: class_sub_deep %d\n", class_sub_deep);

	    strcpy( ident, object_str );

        // printf("getObject ...%s\n",lex.detail.object_str);
        // Object Name
        strcpy(dat_a, getObjectName(object_str) );

		// Set Current Object Name for Global
		memset(&currentClass, '\0', sizeof(currentClass));
        strcpy(currentClass, dat_a);

        // printf("getObject Name OK.\n");
        // object function
        strcpy(dat_b, getObjectFunction(object_str) );
        // printf("getObject Func OK.\n");
        // object function param
        strcpy(dat_c, getObjectFunctionParam(object_str) );
        // printf("getObject Func Param OK.\n");
        
        /*
        printf("For TREE object str : %s , len %d\n",ident, strlen(ident));
        printf("For obj name: %s\n",dat_a);
        printf("For obj func: %s len %d\n",dat_b, strlen(dat_b));
        printf("For obj func param: %s\n",dat_c);
        */

        // check for function existance
        checkObjectFuncValidation(object_str);

        if(strcmp(dat_b, "awalan") == 0 || strcmp(dat_b, "Awalan") == 0) {
          // printf(" Object func init / awalan\n");

          // Get All params of Benda
          class_params_init();
          // Set Benda name for searching
          strcpy(tmpnode.class_name , tmpdat.benda_name);
          // Searching all params of Benda
          class_findParams(tmpnode);

          if(class_params.total == 0) {
            // printf("has no parameter\n");
          } else {
            // printf("parameter found\n");

            for(i=0; i<class_params.total; i++) {
              // printf("%d pos %d name: %s\n", i, class_params.pos[i], class_params.name[i]);

              // get real value of each param
              tmpnode = node_getElement(i);

              memset(&tmp_str, '\0', sizeof(tmp_str));
              sprintf(tmp_str,"%s->%s", dat_a, tmpnode.param_name);
              // keep new param name for object
              strcpy(dat_d, tmp_str);
              // printf("init new param: %s\n", dat_d);

              // do param init operation if any
              if(strlen(tmpnode.param_operation) > 0) {
                // printf("ope: %s\n", tmpnode.param_operation);

                mysplit = split(tmpnode.param_operation, "=");
                // printf("split: %c\n", mysplit[1][0]);

                // write variable into tree
                valdat.scope = tmpnode.scope;
                ValLabel( dat_d, sub_deep, valdat, VAL_FLAG_SEARCH_W );

                memset(&tmp_str, '\0', sizeof(tmp_str));
                if(isalpha(mysplit[1][0]) && !isspace(mysplit[1][0])) {
                  //printf("split param: %s\n", mysplit[1]);
                  sprintf(tmp_str,"%s->%s=%s->%s", dat_a, mysplit[0], dat_a, mysplit[1]);
                } else {
                  sprintf(tmp_str,"%s->%s", dat_a, tmpnode.param_operation);
                }

                // printf("new ope :%s\n", tmp_str);
                split_free(mysplit);

                // if not local, interprete init param
                //if(tmpnode.scope != 1) {
                  memset(&tmp_source_class, '\0', sizeof(tmp_source_class));

                  posClassTemp  = pg.pt;
                  backClassTemp = pg.back_pt;

                  /* Interprete Class Init   */
                  tmp_source_class = pg.source;

                  pg.source  = tmp_str;
                  pg.pt = 0;
                  pg.back_pt = 0;
                  // printf("Awalan ope :%s\n", tmp_str);

                  // skip param
                  getlex();
                  // printf("lex: %s\n", lex.detail.string);

                  // skip equal char =
                  getlex();
                  // printf("lex: %s\n", lex.detail.string);

                  // get value
                  getlex();
                  // printf("lex: %s\n", lex.detail.string);
	              if( lex.type == _EOF )
	                Error("interupsi yang tidak diinginkan");

                  ungetlex();
                  
                  // Save value into Tree
                  // printf("check before expression %s...\n", dat_d);
                  valdat = expression();
                  // printf("check after expression %s...\n", dat_d);
                  // printf(" type %d\n", valdat.datatype);
                  // printf(" num %d\n", valdat.val);
                  // printf(" dbl %f\n", valdat.floatdata);

	              ValLabel( dat_d, sub_deep, valdat, VAL_FLAG_SEARCH_W );

                  pg.source  = tmp_source_class;
                  pg.pt      = posClassTemp;
                  pg.back_pt = backClassTemp;

                //}


              } else {
                // just write empty variable into tree
                valdat.scope = tmpnode.scope;
                valdat.datatype = 0;
                ValLabel( tmp_str, sub_deep, valdat, VAL_FLAG_SEARCH_W );
              } // end  if(strlen(tmpnode.param_operation) > 0) {

              // just checking
              //
              //valdat =  ValLabel( dat_d, valdat, VAL_FLAG_SEARCH_W );
              //printf("check after saving %s...\n", dat_d);
              //printf(" type %d\n", valdat.datatype);
              //printf(" num %d\n", valdat.val);
              //printf(" dbl %f\n", valdat.floatdata);

              //printf(" Masih perlu substitusi parameter sub class\n");
              //


            }

          } // end if(class_params.total == 0) {

          memset(&valdat, '\0', sizeof(valdat));
          valdat = ValLabel( dat_a, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );

          //printf(" Benda name : %s\n", valdat.benda_name);
          //printf(" has init : %d\n", valdat.isClassInit);
          // set AWALAN inited
          valdat.isClassInit = 1;
          ValLabel( dat_a, class_sub_deep, valdat, VAL_FLAG_SEARCH_W );

        } else {
          // printf(" Object func other\n");

        }

        // Get Benda Name from object-name from Tree Memory
        tmpdat = ValLabel( dat_a, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
        // printf(" Get Benda name from Tree : %s\n", tmpdat.benda_name);

        // check if AWALAN not yet inited
        if(tmpdat.isClassInit == 0) {
           memset(&logMsg, '\0', sizeof(logMsg));
           sprintf(logMsg,"Benda %s belum ada awalan !", dat_a);
           Error(logMsg);
        }

        sprintf(tmpMsg, "%s->%s", tmpdat.benda_name, dat_b);
        // printf(" Function sub : %s\n", tmpMsg);

        // Get Function from Tree Memory
        tmpdat = ValLabel( tmpMsg, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
        
        // printf(" datatype : %d\n", tmpdat.datatype);
        // printf(" MEM func : %s\n", tmpdat.sub_name);
        // printf(" MEM func param : %s\n", tmpdat.sub_param);
        
        if(tmpdat.datatype != 32) {
          Error("Gagal ambil referensi fungsi untuk BENDA");
        }

        /* Keep Param into temporary vars         */
        strcpy(get_param, dat_c);
        //strcpy(orig_param, tmpdat.sub_param);


        strcpy(orig_param, "");
        if(strlen(tmpdat.sub_param) > 0) {
          // printf("correct orig obj param\n");
          mysplit = split(tmpdat.sub_param, ",");

          n=0;
          while(mysplit[n] != NULL && strlen(mysplit[n]) > 0) {
            n++;
          }
          // printf("tot param : %d\n", n);

          for(i=0;i<n;i++) {
		    memset(&each_param, '\0', sizeof(each_param));
            sprintf(each_param,"%s->%s", dat_a, mysplit[i]);
            // printf("each :%s\n", each_param);
            strcat(orig_param, each_param);
            if(i != (n-1)) {
              strcat(orig_param, ",");
            }
            // printf("get orig :%s\n", orig_param);
          }
          
          split_free(mysplit);
        }

        // just write empty variable into tree
        //memset(&valdat, '\0', sizeof(valdat));
        //valdat.datatype = 0;
        //ValLabel( orig_param, valdat, VAL_FLAG_SEARCH_W );

        // printf("get_param:%s\n", get_param);
        // printf("orig_param:%s\n", orig_param);

        /* check parameter count                  */
        if(checkParamNum(get_param, orig_param) != 0) {
          memset(&logMsg, '\0', sizeof(logMsg));
          sprintf(logMsg,"Benda %s : Jumlah parameter fungsi tidak benar !", dat_a);
          Error(logMsg);
        }

        // printf("obj get_param:%s\n", get_param);
        // printf("obj orig_param:%s\n", orig_param);

        /* set global params into SUB param vars  */
        subtituteParam((char *)&sub_tmpparam, get_param, orig_param);
        // printf("obj subtitute param: %s\n", sub_tmpparam);

        if(sub_tmpparam != '\0' && strlen(sub_tmpparam) > 0)
          strcpy(param_source , sub_tmpparam );
        else
          strcpy(param_source , "" );

        // printf("subtitute state: %s\n", param_source);

        posClassSub[class_sub_deep] = pg.pt;

        //printf("start interprete sub params\n");
        /* Interprete Params                      */
        memset(&tmp_source, '\0', sizeof(tmp_source));
        tmp_source_class = pg.source;
        
        pg.source = param_source;
        pg.pt = 0;

        // Interpreter(6, posSub[sub_deep], dat_a);
        InterpreterClassParam(2, posClassSub[class_sub_deep], dat_a);  // dat_a is Object Name

        // printf("interprete func param ok\n");

        pg.source = tmp_source_class;
        pg.pt = posClassSub[class_sub_deep];

        // printf("----------- 1\n");
        /* put pointer to function start point    */   
        pg.pt = tmpdat.sub_pt_start;

		if(strlen(tmpdat.sub_file) > 0) {
            // sub source code is in include file
            // printf("sub include file %s\n", valdat.sub_file);
            //memset(&tmp_source, '\0', sizeof(tmp_source));
            //memset(&tmp_source_class, '\0', sizeof(tmp_source_class));

            // keep orig source
            //tmp_source_class = pg.source;

            //if( ( inc_fp = fopen(tmpdat.sub_file, "r") ) == NULL ) {
            //  fprintf( stderr, "tidak bisa buka Kode Luar %s\n", tmpdat.sub_file );
            //  exit( -1 );
            //}

            //tmp_source = (char *)calloc(inc_st.st_size + 9, sizeof(char));
            //if( tmp_source == NULL ){
            //  fprintf( stderr, "calloc error\n" );
            //  exit( -1 );
            //}

            //fread( tmp_source, 1, inc_st.st_size, inc_fp );
            //fclose( inc_fp );

            // set source to included file source
            //pg.source = tmp_source;

            // clear temporary source
            // memset(&tmp_source, '\0', sizeof(tmp_source));
            //tmp_source = NULL;

		}


        /* throw out '{' symbol                   */
        getlex();

        /* Interprete Class SUB                   */
        // pass class name
        InterpreterClassSub(tmpdat.sub_pt_end, dat_a);

        // printf("-----------\n");
        /* put pointer back to main program       */
        pg.pt = posClassSub[class_sub_deep];

        if(strlen(tmpdat.sub_file) > 0) {
          // sub source code is in include file

          // set source back to orig source
          // pg.source = tmp_source_class;

          // clear temporary source
          // memset(&tmp_source_class, '\0', sizeof(tmp_source_class));
          // tmp_source_class = NULL;

        }

        //valdat.datatype = 9;                      /* function type */
        //strcpy(valdat.sub_name , sub_name);       /* function name */
        //strcpy(valdat.sub_param , sub_param);     /* function      */

        //printf("DEBUG2: sub_deep %d\n", sub_deep);
        //printf("DEBUG2: class_sub_deep %d\n", class_sub_deep);

		//if (sub_deep > 0 ) { // still fungsi inside fungsi
		if (sub_deep > 0 ||  isLyrSub > 0 || isTimerSub > 0 ) { // still fungsi inside fungsi
          do{
            Interpreter();
          }while( pg.pt <= valdat.sub_pt_end && strncmp(lex.detail.string , "}", 1) != 0 &&
                 lex.type != _EOF );
		}

}


