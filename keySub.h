// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#include <sys/stat.h>

extern char currentSub[MAX_STRING_LEN];

extern struct all_class_params class_params;
extern void class_params_init(void);
extern void class_findParams(struct node_list data);

extern int node_findData(struct node_list data);
extern struct node_list node_getElement(int n);

char *tmp_source2=NULL;
struct stat inc_st;

void keySub (char ident[MAX_STRING_LEN])
{
  int i=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];
  char   dat_c[MAX_STRING_LEN];
  char   dat_d[MAX_STRING_LEN];
  char   logMsg[MAX_STRING_LEN];
  char   tmpMsg[MAX_STRING_LEN];

  VAL_LABEL valdat, valdat2, tmpdat;
  
  char   **mysplit = NULL;

  int point=0;

  char sub_name[MAX_STRING_LEN],
       sub_param[MAX_STRING_LEN],
       sub_tmpparam[MAX_STRING_LEN*2];

  char get_param[MAX_STRING_LEN],
       orig_param[MAX_STRING_LEN],
       param_source[MAX_STRING_LEN * 2];

  char tmp_str[MAX_STRING_LEN];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  memset(&dat_c, '\0', sizeof(dat_c));
  memset(&dat_d, '\0', sizeof(dat_d));
  memset(&logMsg, '\0', sizeof(logMsg));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

        // printf("subroutine\n");                                 
        memset(&sub_name, '\0', sizeof(sub_name));
        memset(&sub_param, '\0', sizeof(sub_param));
        memset(&sub_tmpparam, '\0', sizeof(sub_tmpparam));

        memset(&get_param, '\0', sizeof(get_param));
        memset(&orig_param, '\0', sizeof(orig_param));
        memset(&param_source, '\0', sizeof(param_source));

        memset(&tmp_str, '\0', sizeof(tmp_str));


        getlex();

        if( lex.type == TYPE_OBJECT_FUNC ) {
          //printf("case TYPE_OBJECT_FUNC %s\n", lex.detail.object_str);

          // printf("getObject ...\n");
          // object name
          strcpy(dat_a, getObjectName(lex.detail.object_str) );
          //printf("getObject Name OK.\n");
          // object function
          strcpy(dat_b, getObjectFunction(lex.detail.object_str) );
          // printf("getObject Func OK.\n");
          // object function param
          strcpy(dat_c, getObjectFunctionParam(lex.detail.object_str) );
          //printf("getObject Func Param OK.\n");
        
          /*
          printf("For TREE object str : %s , len %d\n",ident, strlen(ident));
          printf("For obj name: %s\n",dat_a);
          printf("For obj func: %s len %d\n",dat_b, strlen(dat_b));
          printf("For obj func param: %s\n",dat_c);
          */

          // check for function existance
          checkObjectFuncValidation(lex.detail.object_str);

          if(strcmp(dat_b, "awalan") == 0 || strcmp(dat_b, "Awalan") == 0) {
            // printf(" Object func init\n");

            // Get All params of Benda
            class_params_init();
            // Set Benda name for searching
            strcpy(tmpnode.class_name , tmpdat.benda_name);
            // Searching all params of Benda
            class_findParams(tmpnode);

            if(class_params.total == 0) {
              // printf("parameter not found\n");
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
                  //printf("ope: %s\n", tmpnode.param_operation);

                  mysplit = split(tmpnode.param_operation, "=");
                  // printf("split: %c\n", mysplit[1][0]);

                  // write variable into tree
                  valdat.scope = tmpnode.scope;
                  ValLabel( dat_d, class_sub_deep, valdat, VAL_FLAG_SEARCH_W );

                  memset(&tmp_str, '\0', sizeof(tmp_str));
                  if(isalpha(mysplit[1][0]) && !isspace(mysplit[1][0])) {
                    //printf("split param: %s\n", mysplit[1]);
                    #ifdef WIN32
                     #ifndef S_SPLINT_S
                     sprintf_s(tmp_str, sizeof(tmp_str),"%s->%s=%s->%s", dat_a, mysplit[0], dat_a, mysplit[1]);
                     #else
                     snprintf(tmp_str, sizeof(tmp_str),"%s->%s=%s->%s", dat_a, mysplit[0], dat_a, mysplit[1]);
                     #endif
                    #else
                    snprintf(tmp_str, sizeof(tmp_str),"%s->%s=%s->%s", dat_a, mysplit[0], dat_a, mysplit[1]);
                    #endif

                  } else {
                    sprintf(tmp_str,"%s->%s", dat_a, tmpnode.param_operation);
                    #ifdef WIN32
                     #ifndef S_SPLINT_S
                     sprintf_s(tmp_str, sizeof(tmp_str),"%s->%s", dat_a, tmpnode.param_operation);
                     #else
                     snprintf(tmp_str, sizeof(tmp_str),"%s->%s", dat_a, tmpnode.param_operation);
                     #endif
                    #else
                    snprintf(tmp_str, sizeof(tmp_str),"%s->%s", dat_a, tmpnode.param_operation);
                    #endif

                  }
                  // printf("new ope :%s\n", tmp_str);


                  if(mysplit != NULL)
                    split_free(mysplit);

                  // if not local, interprete init param
                  //if(tmpnode.scope != 1) {
                    memset(&tmp_source2, '\0', sizeof(tmp_source2));

                    posClassTemp  = pg.pt;
                    backClassTemp = pg.back_pt;

                    /* Interprete Class Init   */
                    tmp_source2 = pg.source;

                    pg.source  = tmp_str;
                    pg.pt = 0;
                    pg.back_pt = 0;
                    // printf("ope :%s\n", tmp_str);

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
                    valdat = expression();
                    // printf("check after expression %s...\n", dat_d);
                    // printf(" type %d\n", valdat.datatype);
                    // printf(" num %d\n", valdat.val);
                    // printf(" dbl %f\n", valdat.floatdata);

	                ValLabel( dat_d, class_sub_deep, valdat, VAL_FLAG_SEARCH_W );

                    pg.source  = tmp_source2;
                    pg.pt      = posClassTemp;
                    pg.back_pt = backClassTemp;

                //}

                } else {
                  // just write empty variable into tree
                  valdat.scope = tmpnode.scope;
                  valdat.datatype = 0;
                  ValLabel( tmp_str, class_sub_deep, valdat, VAL_FLAG_SEARCH_W );
                } // end  if(strlen(tmpnode.param_operation) > 0) {

                // just checking BENDA
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
            // printf(" Benda name : %s\n", valdat.benda_name);
            // printf(" has init : %d\n", valdat.isClassInit);
            // set AWALAN inited
            valdat.isClassInit = 1;
            ValLabel( dat_a, class_sub_deep, valdat, VAL_FLAG_SEARCH_W );

          } else {
            // printf(" Object func other\n");
          }

          // Get Benda Name from object-name from Tree Memory
	  memset(&tmpdat, '\0', sizeof(tmpdat));
          tmpdat = ValLabel( dat_a, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
          //printf(" Benda name : %s\n", tmpdat.benda_name);

          // check if AWALAN not yet inited
          if(tmpdat.isClassInit == 0) {
            memset(&logMsg, '\0', sizeof(logMsg));
            #ifdef WIN32
             #ifndef S_SPLINT_S
             sprintf_s(logMsg, sizeof(logMsg),"Benda %s belum ada awalan !", dat_a);
             #else
             snprintf(logMsg, sizeof(logMsg),"Benda %s belum ada awalan !", dat_a);
             #endif
            #else
            snprintf(logMsg, sizeof(logMsg),"Benda %s belum ada awalan !", dat_a);
            #endif

            Error(logMsg);
          }

          #ifdef WIN32
           #ifndef S_SPLINT_S
           sprintf_s(tmpMsg, sizeof(tmpMsg),"%s->%s", tmpdat.benda_name, dat_b);
           #else
           snprintf(tmpMsg, sizeof(tmpMsg),"%s->%s", tmpdat.benda_name, dat_b);
           #endif
          #else
          snprintf(tmpMsg, sizeof(tmpMsg),"%s->%s", tmpdat.benda_name, dat_b);
          #endif
          //printf(" Benda Function sub : %s\n", tmpMsg);

          // Get Function from Tree Memory
	  memset(&tmpdat, '\0', sizeof(tmpdat));
          tmpdat = ValLabel( tmpMsg, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
          
          //printf(" datatype : %d\n", tmpdat.datatype);
          //printf(" MEM func : %s\n", tmpdat.sub_name);
          //printf(" MEM func param : %s\n", tmpdat.sub_param);
          
          if(tmpdat.datatype != 32) {
            Error("Gagal ambil referensi fungsi untuk BENDA");
          }

          /* Keep Param into temporary vars         */
          strcpy(get_param, dat_c);
          //strcpy(orig_param, tmpdat.sub_param);

          if(strlen(tmpdat.sub_param) > 0) {
            #ifdef WIN32
             #ifndef S_SPLINT_S
             sprintf_s(orig_param, sizeof(orig_param),"%s->%s", dat_a, tmpdat.sub_param);
             #else
             snprintf(orig_param, sizeof(orig_param),"%s->%s", dat_a, tmpdat.sub_param);
             #endif
            #else
            snprintf(orig_param, sizeof(orig_param),"%s->%s", dat_a, tmpdat.sub_param);
            #endif
          }

          //printf("get_param:%s\n", get_param);
          //printf("orig_param:%s\n", orig_param);

          /* check parameter count                  */
          if(checkParamNum(get_param, orig_param) != 0) {
            memset(&logMsg, '\0', sizeof(logMsg));
            #ifdef WIN32
             #ifndef S_SPLINT_S
             sprintf_s(logMsg, sizeof(logMsg),"Benda %s : Jumlah parameter fungsi tidak benar !", dat_a);
             #else
             snprintf(logMsg, sizeof(logMsg),"Benda %s : Jumlah parameter fungsi tidak benar !", dat_a);
             #endif
            #else
            snprintf(logMsg, sizeof(logMsg),"Benda %s : Jumlah parameter fungsi tidak benar !", dat_a);
            #endif
            Error(logMsg);
          }

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
            memset(&tmp_source, '\0', sizeof(tmp_source));
            memset(&tmp_source_class, '\0', sizeof(tmp_source_class));

            // keep orig source
            tmp_source_class = pg.source;

            if( stat( tmpdat.sub_file, &inc_st ) != 0 ) {
              fprintf( stderr, "kode luar tidak ditemukan: %s\n", tmpdat.sub_file );
              exit( -1 );
	        }

            if( ( inc_fp = fopen(tmpdat.sub_file, "r") ) == NULL ) {
              fprintf( stderr, "tidak bisa buka Kode Luar %s\n", tmpdat.sub_file );
              exit( -1 );
            }

            tmp_source = (char *)calloc(inc_st.st_size + 9, sizeof(char));
            if( tmp_source == NULL ){
              fprintf( stderr, "calloc error\n" );
              exit( -1 );
            }

            fread( tmp_source, 1, inc_st.st_size, inc_fp );
            fclose( inc_fp );

            // set source to included file source
            pg.source = tmp_source;

            // clear temporary source
            memset(&tmp_source, '\0', sizeof(tmp_source));
            tmp_source = NULL;
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
            pg.source = tmp_source_class;

            // clear temporary source
            memset(&tmp_source_class, '\0', sizeof(tmp_source_class));
            tmp_source_class = NULL;
          }

          valdat.datatype = 9;                      /* function type */
          strcpy(valdat.sub_name , sub_name);       /* function name */
          strcpy(valdat.sub_param , sub_param);     /* function      */

          memset(&tmpdat, '\0',sizeof(tmpdat));

#ifdef S_SPLINT_S
          memcpy((void *)tmpdat, (void *)returnVal, sizeof(returnVal));
#else
          memcpy(&tmpdat, &returnVal, sizeof(returnVal));
#endif

	  if(strlen(ident) > 0) {
	      // printf("saving obj sub %s ...\n", ident);
             ValLabel( ident, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
	  }

	} else

        if( lex.type == TYPE_IDENT ) {

			memset(&sub_name, '\0', sizeof(sub_name));
			memset(&sub_param, '\0', sizeof(sub_param));
			memset(&sub_tmpparam, '\0', sizeof(sub_tmpparam));

            //printf("sub name string: %s\n", lex.detail.string);

            if(lex.detail.string != NULL && strlen(lex.detail.string) > 0)
              strcpy(sub_name, lex.detail.string);
            else
              strcpy(sub_name, "");

            // printf(" start to search sub : %s\n", sub_name);

            valdat.val = -1;
            valdat = ValLabel( sub_name, 0, valdat, VAL_FLAG_SEARCH_R );

            /* printf("evaluate search result\n"); */
        
            point = valdat.val;
            // printf("point %d, type %d \n", point, valdat.datatype);

            if( point == -1 ) {
              Error("SUB tidak ditemukan");
            } else {
              //printf("SUB ada\n");
              //printf("SUB start : %d\n",valdat.sub_pt_start);
              //printf("SUB end : %d\n",valdat.sub_pt_end);
            }
            valdat.val = 0;

            /* printf("evaluate OK\n"); */

            getlex();
            /* printf("sub ( string: %s\n", lex.detail.string);
            */

            if( lex.type != TYPE_SYM || strncmp(lex.detail.string , "(", 1) != 0 ) {
              Error("kode SUB salah : tanpa tanda (");
            }

            strcpy(sub_param, "");

            while( lex.detail.string[0] != ')' && lex.type != _EOF  ) {
              getlex();

              if(lex.detail.string[0] == ')' )
                break;

              /*
              if( lex.type != TYPE_IDENT ) {
                Error("kode SUB salah");
              }
              */

              if(lex.type == TYPE_NUM) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(tmp_str, sizeof(tmp_str),"%li", lex.detail.num);
                 #else
                 snprintf(tmp_str, sizeof(tmp_str),"%li", lex.detail.num);
                 #endif
                #else
                snprintf(tmp_str, sizeof(tmp_str),"%li", lex.detail.num);
                #endif

                strcat(sub_param, tmp_str);
              }
              else if(lex.type == TYPE_DBL) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(tmp_str, sizeof(tmp_str),"%f", lex.detail.dblnum);
                 #else
                 snprintf(tmp_str, sizeof(tmp_str),"%f", lex.detail.dblnum);
                 #endif
                #else
                snprintf(tmp_str, sizeof(tmp_str),"%f", lex.detail.dblnum);
                #endif

                strcat(sub_param, tmp_str);
              }
              else if(lex.detail.string != '\0' && strlen(lex.detail.string) > 0) {
                strcat(sub_param, lex.detail.string);
              }
              else if(lex.type == TYPE_SYM) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(tmp_str, sizeof(tmp_str),"%c", lex.detail.symbol);
                 #else
                 snprintf(tmp_str, sizeof(tmp_str),"%c", lex.detail.symbol);
                 #endif
                #else
                snprintf(tmp_str, sizeof(tmp_str),"%c", lex.detail.symbol);
                #endif

                strcat(sub_param, tmp_str);
              }

            } // end while

            /* Keep Param into temporary vars         */
            strcpy(get_param, sub_param);
            strcpy(orig_param, valdat.sub_param);

            /* check parameter count                  */
            if(checkParamNum(get_param, orig_param) != 0)
              Error("Definisi SUB tidak benar");
          
            //printf("sub get param: %s\n", sub_param);
            //printf("sub orig param: %s\n", valdat.sub_param);
          
            posSub[sub_deep] = pg.pt;
            //printf("start sub %d\n", posSub[sub_deep]); 

            /* Keep Param into temporary vars         */
            strcpy(get_param, sub_param);
            strcpy(orig_param, valdat.sub_param);
            // printf("keep sub params ok\n");

            /* set global params into SUB param vars  */
            subtituteParam((char *)&sub_tmpparam, get_param, orig_param);

            if(sub_tmpparam != '\0' && strlen(sub_tmpparam) > 0)
              strcpy(param_source , sub_tmpparam );
            else
              strcpy(param_source , "" );

            posSub[sub_deep] = pg.pt;

            //printf("start interprete sub params %d\n", posSub[sub_deep]); 

            memset(&tmp_source, '\0', sizeof(tmp_source));
            tmp_source = pg.source;
        
            pg.source = param_source;
            pg.pt = 0;

            InterpreterParam(2, posSub[sub_deep], sub_name);

            // printf("interprete param ok\n");

            pg.source = tmp_source;
            pg.pt = posSub[sub_deep];

            /* printf("-----------\n");               */
            /* put pointer to function start point    */   
            pg.pt = valdat.sub_pt_start;

            /* throw out '{' symbol                   */
            getlex();

            // printf("SUB end: %d\n", valdat.sub_pt_end);

            /* Interprete SUB                         */
            InterpreterSub(valdat.sub_pt_end, sub_name);

            // printf("-----------\n");
            /* put pointer back to main program       */
            pg.pt = posSub[sub_deep];

            //printf("back to main program, pos %d\n", posSub[sub_deep]); 
            //printf("back ret POS1: %d\n", pg.pt);
            //printf("back SUB end: %d\n", valdat.sub_pt_end);

            valdat.datatype = 9;                      /* function type */
            strcpy(valdat.sub_name , sub_name);       /* function name */
            strcpy(valdat.sub_param , sub_param);     /* function      */

            memset(&tmpdat, '\0',sizeof(tmpdat));
#ifdef S_SPLINT_S
          memcpy((void *)tmpdat, (void *)returnVal, sizeof(returnVal));
#else
          memcpy(&tmpdat, &returnVal, sizeof(returnVal));
#endif

	    if(strlen(ident) > 0) {
	      //printf("saving sub %s ...\n", ident);
              ValLabel( ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
	    }


	    //if (sub_deep > 0 ) { // still fungsi inside fungsi
	    if (sub_deep > 0 ||  isLyrSub > 0 || isTimerSub > 0 ) { // still fungsi inside fungsi

              do{
               Interpreter();
              }while( pg.pt <= valdat.sub_pt_end && strncmp(lex.detail.string , "}", 1) != 0 &&
                  lex.type != _EOF );
		    }


		} else {
			printf("%s ", ident);
			Error("kode SUB salah");
        }

  if(mysplit != NULL)
    free(mysplit);

  if(tmpnode.nodeType != NULL)
    free(tmpnode.nodeType);
  if(tmpnode.pnext != NULL)
    free(tmpnode.pnext);

  if(valdat2.filename != NULL)
    free(valdat2.filename);
  if(valdat2.folder != NULL)
    free(valdat2.folder);
  if(valdat2.filedata != NULL)
    free(valdat2.filedata);
  if(valdat2.long_str != NULL)
    free(valdat2.long_str);

  if(valdat2.left != NULL)
    free(valdat2.left);
  if(valdat2.right != NULL)
    free(valdat2.right);
  if(valdat2.pnext != NULL)
    free(valdat2.pnext);

}

