// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

MVCPARSING keyMVC_Array(char array_str[MAX_STRING_LEN], MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{

  char idx_source2[MAX_STRING_LEN];

  char dat_a[MAX_STRING_LEN];
  char dat_b[MAX_STRING_LEN];
  VAL_LABEL valdat,                            // for saving and returning value
            valdat2, tmpdat;
  VAL_LABEL datx, daty;

  long idx=0, idx2=0;                           // array index
  int plusplus=0;

  long   tmpint=0;
  double tmpdbl=0.0;
  char   tmpstr[MAX_STRING_LEN];

  MVCPARSING par;
  
  memset(&par, '\0', sizeof(par));

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&datx, '\0', sizeof(datx));
  memset(&daty, '\0', sizeof(daty));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&tmpstr, '\0', sizeof(tmpstr));
  memset(&idx_source2, '\0', sizeof(idx_source2));

  //printf("===> inside keyMVC_Array: %s\n", array_str);

  if(renban != '\0')
    renban++;
  else
    renban = 0;

  if(renban > 999) {
    renban = 0;
  }
  //printf("keyArray renban %d \n", renban);

    // //////////////////////////////////
    // NOT Dummy array / Real Array
    // //////////////////////////////////

    memset(&valdat, '\0', sizeof(valdat));
    valdat.datatype = 6;

    isDoArray = 1;

    if(strlen(array_str) > 0) {
      // //////////////////////
      // preparing variabel ...
      // //////////////////////
      getArrayName(array_str, (char *)&valdat.array_str);
      getArrayName(array_str, (char *)&valdat.array_name);
      //printf("get array_name: %s\n", valdat.array_name);

      getArrayIdx(array_str, (char *)&valdat.array_idx);

      // //////////////////////
      // preparing index ... : valdat is prepared Variable, idx is current index
      // //////////////////////

      //printf("get array_idx: %s\n", valdat.array_idx);

      if(isdigit(valdat.array_idx[0])) {
        idx = atoi (valdat.array_idx);
      } else {
        /* Read index param */
      
        //getlex();
        par = MVCgetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  = par.mvc_pg;

        if( mvc_lex.detail.symbol == ']' ) {
          // single ident param idx
          //ungetlex();
          par = MVCungetlex(mvc_lex, mvc_pg);
          mvc_lex = par.mvc_lex;
          mvc_pg  = par.mvc_pg;
          
          tmpdat = ValLabel( valdat.array_idx, sub_deep, datx, VAL_FLAG_SEARCH_R );
        } else {
          // expression param idx
          //ungetlex();
          par = MVCungetlex(mvc_lex, mvc_pg);
          mvc_lex = par.mvc_lex;
          mvc_pg  = par.mvc_pg;

          memset(&idx_source2, '\0', sizeof(idx_source2));
          strcpy(idx_source2, "{ ");
          strcat(idx_source2, valdat.array_idx);
          strcat(idx_source2, " }");
          
          //printf("interpretIndexParam\n");
          tmpdat = interpretIndexParam(idx_source2, mvc_pg.pt, mvc_pg.back_pt, "");
        }
      
        if(tmpdat.datatype==0)
          idx = tmpdat.val;
        else if(tmpdat.datatype==1)
	  idx = (long)abs((int)tmpdat.floatdata);
        else
          Error("Untaian salah masukan");

      } // end if(isdigit(valdat.array_idx[0]))

      DoArrayIdx = idx;
      strcpy(DoArrayName, valdat.array_name);

      if(idx < 0 || idx > MAX_ARRAY)
        Error("ukuran Untaian tidak sesuai kapasitas");

    } // end  if(strlen(array_str) > 0) {

    // //////////////////////
    // get symbol for equal or minmin/plusplus
    // //////////////////////
    //getlex();
    par = MVCgetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  = par.mvc_pg;


    if( mvc_lex.type == _MVC_EOF )
      Error("interupsi yang tidak diinginkan");

    /* substitute */
    if( mvc_lex.type == TYPE_MVC_SYM && (mvc_lex.detail.symbol == '=' || mvc_lex.detail.symbol == '+' || mvc_lex.detail.symbol == '-' )) {
      // substitusi atau ++ atau --
       if( mvc_lex.detail.symbol == '+' )  {
	    plusplus = 1;
       } else if( mvc_lex.detail.symbol == '-' )  {
	    plusplus = -1;
       }
    } else {
	printf("simbol %c \n", mvc_lex.detail.symbol);
        Error("untaian salah! bukan masukan atau operasi matematik ");
    }

    // //////////////////////
    // get Value or symbol   : valdat is prepared Variable, idx is current index
    // //////////////////////
    //getlex();
    par = MVCgetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  = par.mvc_pg;

    if( mvc_lex.type == _MVC_EOF )
       Error("interupsi yang tidak diinginkan");

    // printf("2=> %s\n",lex.detail.string);
    //printf("Array Val => type : %d\n", mvc_lex.type);

    if( mvc_lex.detail.symbol == '+'  && mvc_lex.type == TYPE_MVC_SYM)  { // plusplus
      if(plusplus == 1) {
        // printf("array plusplus \n");

	// get real value of valdat from prepared one
	valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
	// apply prepared idx into real value
        // ltoa(idx, valdat.array_idx, 10);

        #ifdef WIN32
        sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
        #else
        snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
        #endif

        if(valdat.array_name != NULL && valdat.datatype == 6) {
	  tmpint = get_int_array(valdat, idx);
          save_int_array(valdat, idx, tmpint + 1);
	  // nothing changed with current stackid
          valdat.datatype = 6;

        } else
        if(valdat.array_name != NULL&& valdat.datatype == 7) {
	  tmpdbl = get_dbl_array(valdat, idx);
          save_dbl_array(valdat, idx, tmpdbl + 1.0);
	  // nothing changed with current stackid
          valdat.datatype = 7;
        }
      }

    } else if( mvc_lex.detail.symbol == '-'  && mvc_lex.type == TYPE_MVC_SYM)  { // minmin
      if(plusplus == -1) {
        // printf("array minmin \n");

	// get real value of valdat from prepared one
	valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
	// apply prepared idx into real value
        // ltoa(idx, valdat.array_idx, 10);

        #ifdef WIN32
        sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
        #else
        snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
        #endif

        if(valdat.array_name != NULL && valdat.datatype == 6) {
	  tmpint = get_int_array(valdat, idx);
          save_int_array(valdat, idx, tmpint - 1);
	  // nothing changed with current stackid
          valdat.datatype = 6;

        } else
        if(valdat.array_name != NULL&& valdat.datatype == 7) {
	  tmpdbl = get_dbl_array(valdat, idx);
          save_dbl_array(valdat, idx, tmpdbl - 1.0);
	  // nothing changed with current stackid
          valdat.datatype = 7;
        }

      } else { // branch from if(plusplus == -1) {

        // //////////////////////
        // get Minus Value 
        // //////////////////////
	//getlex();
        par = MVCgetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  = par.mvc_pg;

	// printf("expression ident with minus : %s idx %d\n", valdat.array_name, idx);

	// get real value of valdat from prepared one
        valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
	// apply prepared idx into real value
        // ltoa(idx, valdat.array_idx, 10);

        #ifdef WIN32
        sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
        #else
        snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
        #endif

                if(mvc_lex.type == TYPE_MVC_NUM) {
                  // printf("idx %d val %d \n", idx, lex.detail.num);
                  // printf("get int for int array, renban: %d \n", valdat.array_i);
                  
		  mvc_lex.detail.num =  0 - mvc_lex.detail.num; 
                  save_int_array(valdat, idx, mvc_lex.detail.num);
		  // nothing changed with current stackid
                  valdat.datatype = 6;

		  // printf("get num OK\n");
                } else if(mvc_lex.type == TYPE_MVC_DBL) {
                  // printf("idx %d val %f \n", idx, lex.detail.dblnum);
                  mvc_lex.detail.dblnum =  0.0 - mvc_lex.detail.dblnum;
                  save_dbl_array(valdat, idx, mvc_lex.detail.dblnum);
		  // nothing changed with current stackid
                  valdat.datatype  = 7;
		  // printf("get DBL OK\n");
                } else if(mvc_lex.type == TYPE_MVC_ARRAY) {
                  strcpy(daty.array_str, mvc_lex.detail.array_str);

                  getArrayName(mvc_lex.detail.array_str, (char *)&daty.array_name);
                  getArrayIdx(mvc_lex.detail.array_str, (char *)&daty.array_idx);

                  // printf("factor ARRAY name: %s\n", valdat.array_name);

                  if(isdigit(daty.array_idx[0])) {
                    /* printf("show digit\n"); */
                    idx2 = atol (daty.array_idx);
                  } else {
                    /* printf("show NOT digit\n"); */
                    /* Read index param */
                    datx = ValLabel( daty.array_idx, sub_deep, daty, VAL_FLAG_SEARCH_R );
                    if(datx.datatype==0)
                      idx2 = datx.val;
                    else
                      Error("Untaian salah masukan");
                  }

                  daty = ValLabel( daty.array_name, sub_deep, daty, VAL_FLAG_SEARCH_R );

                  #ifdef WIN32
                  sprintf_s(daty.array_idx, sizeof(daty.array_idx),"%li", idx2);
                  #else
                  snprintf(daty.array_idx, sizeof(daty.array_idx),"%li", idx2);
                  #endif


                  // ltoa(idx2, daty.array_idx, 10);

                  if(idx2 < 0 || idx2 > MAX_ARRAY)
                    Error("ukuran Untaian tidak sesuai kapasitas");

                  /* printf("array substitution\n"); */
                  if(daty.datatype == 6) {
		    tmpint = 0 - get_int_array(daty, idx2);
		    save_int_array(valdat, idx, tmpint);
		    // nothing changed with current stackid
                    valdat.datatype = 6;

		  }
                  else
                  if(daty.datatype == 7) {
		    tmpdbl = 0.0 - get_dbl_array(daty, idx2);
		    save_dbl_array(valdat, idx, tmpdbl);
		    // nothing changed with current stackid
                    valdat.datatype  = 7;
                  }
		  else {
                    Error("Salah bentuk bilangan negatif");
		  }

	        } // end if(lex.type == TYPE_MVC_ARRAY

      } // end branch from if(plusplus == -1) {


    } else if( mvc_lex.type != TYPE_MVC_STR  ) {                          /* entry math func */
      //printf ("Array val not string \n");

      /* Read Real Array , to get Idx val */
      valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

      #ifdef WIN32
      sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
      #else
      snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
      #endif

      // ltoa(idx, valdat.array_idx, 10);
      //printf("evaluate array : %s\n", valdat.array_name);
      //printf("evaluate type : %d\n", valdat.datatype);
      //printf("evaluate scope : %d\n", valdat.scope);

      /* == Get variable value == */
      if(mvc_lex.type == TYPE_MVC_DBL) {
        // //////////////////////////////////////////
        // TYPE_DBL
        // //////////////////////////////////////////
	// printf("get dbl for dbl array, renban: %d \n", valdat.array_d);
        valdat.datatype = 7;
	save_dbl_array(valdat, idx, mvc_lex.detail.dblnum);

      } else if(mvc_lex.type == TYPE_MVC_NUM) {
        // //////////////////////////////////////////
        // TYPE_NUM
        // //////////////////////////////////////////
        //printf("get num, idx %d val %d \n", idx, mvc_lex.detail.num);

        if(tmpdat.datatype == 0) {
	   //printf("get int for int array, renban: %d \n", valdat.array_i);
           valdat.datatype = 6;
	   save_int_array(valdat, idx, mvc_lex.detail.num);
        }

      } else if(mvc_lex.type == TYPE_MVC_ARRAY) {
        // //////////////////////////////////////////
        // TYPE_ARRAY
        // //////////////////////////////////////////
        // printf("get input type array\n"); 

            if(strlen(mvc_lex.detail.array_str) > 0) {
              // printf("array string : %s\n", lex.detail.array_str);
              strcpy(valdat2.array_str, mvc_lex.detail.array_str);
              getArrayName(lex.detail.array_str, (char *)&valdat2.array_name);
              getArrayIdx(lex.detail.array_str, (char *)&valdat2.array_idx);

              // printf("get valdat2 idx2 %s\n", valdat2.array_idx);

              if(isdigit(valdat2.array_idx[0])) {
                /* printf("show digit\n"); */
                idx2 = atol (valdat2.array_idx);
              } else {
                /* printf("show NOT digit\n"); */
                /* Read index param */
                tmpdat = ValLabel( valdat2.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                if(tmpdat.datatype==0)
                  idx2 = tmpdat.val;
                else
                   Error("ccc Untaian salah masukan");
              }

              if(valdat.datatype == 8) {
	        // get real value
                valdat2 = ValLabel( valdat.array_name, sub_deep, valdat2, VAL_FLAG_SEARCH_R );

                #ifdef WIN32
                sprintf_s(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx2);
                #else
                snprintf(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx2);
                #endif

                // ltoa(idx2, valdat2.array_idx, 10);
              } else {
                //ungetlex();
                par = MVCungetlex(mvc_lex, mvc_pg);
                mvc_lex = par.mvc_lex;
                mvc_pg  = par.mvc_pg;

		//valdat2 = expression();

                //printf("before MVC expression\n");
                par = MVC_expression(mvc_lex, mvc_pg);
                //printf("after MVC expression\n");
                memset(&valdat2, '\0', sizeof(valdat2));
                valdat2.datatype  = par.datatype;
                valdat2.val       = par.val;
                valdat2.floatdata = par.floatdata;
                valdat2.array_i   = par.array_i;
                valdat2.array_d   = par.array_d;
                valdat2.array_s   = par.array_s;
                strcpy(valdat2.str, par.str);
                strcpy(valdat2.array_str, par.array_str);
                strcpy(valdat2.array_idx, par.array_idx);
		
                #ifdef WIN32
                sprintf_s(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx2);
                #else
                snprintf(valdat2.array_idx, sizeof(valdat2.array_idx),"%li", idx2);
                #endif

                // ltoa(idx2, valdat2.array_idx, 10);
                // printf("get valdat2 idx2 %s\n", valdat2.array_idx);

                if(idx < 0 || idx > MAX_ARRAY)
                  Error("ukuran Untaian tidak sesuai kapasitas");
                if(idx2 < 0 || idx2 > MAX_ARRAY)
                  Error("ukuran Untaian tidak sesuai kapasitas");

                // printf("==get idx2 %d\n", idx2);
		// printf("==get input type %d val %d\n", valdat2.datatype, valdat2.val);

                if(valdat2.datatype == 0) {
		  save_int_array(valdat, idx, valdat2.val);
                  valdat.datatype = 6;

                } else if(valdat2.datatype == 1) {
		  save_dbl_array(valdat, idx, valdat2.floatdata);
                  valdat.datatype = 7;

	        } else if(valdat2.datatype == 3) {
		  save_str_array(valdat, idx, valdat2.str);
                  valdat.datatype = 8;

  	        } else if(valdat2.datatype == 6) {
	  	  valdat.array_i = valdat2.array_i;
                  valdat.datatype = 6;

                } else if(valdat2.datatype == 7) {
		  valdat.array_d = valdat2.array_d;
                  valdat.datatype = 7;

                } else if(valdat2.datatype == 8) {
	          // printf("array: get array string\n");
                  // valdat.array_s = valdat2.array_s;
                  get_str_array(valdat2, idx2, (char *)&tmpstr);
	          save_str_array(valdat, idx, tmpstr);
                  valdat.datatype = 8;

                } else {
                  Error("0 nilai input larik belum disupport"); 
                }
              } // end if(valdat.datatype == 8) {

            } // end if(strlen(mvc_lex.detail.array_str) > 0) {

      } else if(mvc_lex.type == TYPE_MVC_IDENT) {
	// //////////////////////////////////////////
	// TYPE_IDENT
	// //////////////////////////////////////////
        // printf("get input type IDENT : %s\n", lex.detail.ident); 

        // get real value
        valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

        #ifdef WIN32
        sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
        #else
        snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
        #endif

        // ltoa(idx, valdat.array_idx, 10);

        //ungetlex();
        par = MVCungetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  = par.mvc_pg;

        //tmpdat = expression(); 
        //printf("before MVC expression\n");
        par = MVC_expression(mvc_lex, mvc_pg);
        //printf("after MVC expression\n");
        memset(&tmpdat, '\0', sizeof(tmpdat));
        tmpdat.datatype  = par.datatype;
        tmpdat.val       = par.val;
        tmpdat.floatdata = par.floatdata;
        strcpy(tmpdat.str, par.str);
        strcpy(tmpdat.array_str, par.array_str);
        strcpy(tmpdat.array_idx, par.array_idx);

        // printf("get input type %d\n", tmpdat.datatype);
             
        if(tmpdat.datatype == 0) {
	   // printf("get int for int array, renban: %d \n", valdat.array_i);
           valdat.datatype = 6;
	   save_int_array(valdat, idx, tmpdat.val);
        } else if(tmpdat.datatype == 1) {
           valdat.datatype = 7;
	   save_dbl_array(valdat, idx, tmpdat.floatdata);
        } else if(tmpdat.datatype == 6) {
	   // printf("get int Array for int Array, renban: %d \n", valdat.array_i);

           valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

           #ifdef WIN32
           sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
           #else
           snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
           #endif

           // ltoa(idx, valdat.array_idx, 10);
           idx2 = atol(tmpdat.array_idx);

           tmpint = get_int_array(tmpdat, idx2);

           save_int_array(valdat, idx, tmpint);
           valdat.datatype = 6;

        } else if(tmpdat.datatype == 7) {
	  // printf("get dbl Array for dbl Array, renban: %d \n", valdat.array_d);

          valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

          #ifdef WIN32
          sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
          #else
          snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
          #endif

          // ltoa(idx, valdat.array_idx, 10);
          idx2 = atol(tmpdat.array_idx);

	  tmpdbl = get_dbl_array(tmpdat, idx2);

          save_dbl_array(valdat, idx, tmpdbl);
          valdat.datatype = 7;

        } else if(tmpdat.datatype == 3) {
          /* printf("string: %s\n", tmpdat.str); */
          valdat.datatype = 8;
          save_str_array(valdat, idx, tmpdat.str);

        } else if(tmpdat.datatype == 8) {
          // printf("IDENT : string arry"); 

          #ifdef WIN32
          sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
          #else
          snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
          #endif

          // ltoa(idx, valdat.array_idx, 10);
          idx2 = atol(tmpdat.array_idx);

          get_str_array(tmpdat, idx2, (char *)&tmpstr);
	  save_str_array(valdat, idx, tmpstr);
          valdat.datatype = 8;

        } else {
          Error("tipe nilai yang lain belum disupport");
        }

             
      } else if(mvc_lex.type == TYPE_MVC_SYM) {
        // //////////////////////////////////////////
        // TYPE_SYM
        // //////////////////////////////////////////
        // printf("equal input type SYM : %c\n", lex.detail.symbol); 

        //getlex();
        par = MVCgetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  = par.mvc_pg;

        if( mvc_lex.detail.symbol == '-'  && mvc_lex.type == TYPE_MVC_SYM)  { // make min
	  // printf("make min sym\n");
          valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );
          if(isdigit(valdat.array_idx[0])) {
            /* printf("show digit\n"); */
            idx = atoi (valdat.array_idx);
          } else {
            /* printf("show NOT digit\n"); */
            /* Read index param */
            datx = ValLabel( valdat.array_idx, sub_deep, valdat, VAL_FLAG_SEARCH_R );
            if(datx.datatype==0)
              idx = datx.val;
            else
              Error("Untaian salah masukan");
          }

	} // branch if( lex.detail.symbol == '+' )
	else {
          // printf("expression ident\n");
          //ungetlex();
          par = MVCungetlex(mvc_lex, mvc_pg);
          mvc_lex = par.mvc_lex;
          mvc_pg  = par.mvc_pg;

          //tmpdat = expression(); 
          //printf("before MVC expression\n");
          par = MVC_expression(mvc_lex, mvc_pg);
          //printf("after MVC expression\n");
          memset(&tmpdat, '\0', sizeof(tmpdat));
          tmpdat.datatype  = par.datatype;
          tmpdat.val       = par.val;
          tmpdat.floatdata = par.floatdata;
          strcpy(tmpdat.str, par.str);
          strcpy(tmpdat.array_str, par.array_str);
          strcpy(tmpdat.array_idx, par.array_idx);


          if(tmpdat.datatype == 0) {
	    save_int_array(valdat, idx, 0 - tmpdat.val);
            valdat.datatype = 6;

          } else if(tmpdat.datatype == 1) {
	    save_dbl_array(valdat, idx, 0.0 - tmpdat.floatdata);
            valdat.datatype = 7;
           }
	} // end if( mvc_lex.detail.symbol == '+' )

      } // end if (mvc_lex.type == TYPE_SYM

      /*
      printf("store arr datatype %d\n", valdat.datatype);
           
      printf("store arr ALL : %s\n", valdat.array_str);
      printf("store arr name : %s\n", valdat.array_name);
      printf("store arr idx : %s\n", valdat.array_idx);
      printf("store arr max : %d\n", valdat.array_max);

      printf("store arr int : %d\n", valdat.array_i[idx]);
      */

      /* Write Array Value to Node memory tree */
      ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_W );
      // printf("store OK\n"); 

      memset(&valdat, '\0', sizeof(valdat));
      memset(&valdat2, '\0', sizeof(valdat2));
      memset(&tmpdat, '\0', sizeof(tmpdat));          

    } else {
      // printf ("arry string var : %s\n", valdat.array_name);

      /* Read Array Max Value from Node memory tree */
      valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

      if(idx==0) {
        /* start new array */
        /* printf("new array value\n"); */
        valdat.datatype = 8;
      }else {
        /* add array content */
        /* printf("add array value\n"); */
        if(valdat.array_s == '\0') {
           Error("Untaian ke-[0] belum terisi: kata");
        } else {
           /* printf("array num value\n"); */
           valdat.datatype = 8;
        }
      }

      #ifdef WIN32
      sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
      #else
      snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%li", idx);
      #endif

      // ltoa(idx, valdat.array_idx, 10);
      /* == Get variable value == */

      strcpy(tmpstr, mvc_lex.detail.string);
      // printf("input str : %s \n", keep_string); 
      save_str_array(valdat, idx, tmpstr);

      /* Write Array Value to Node memory tree */
      ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_W );

    }

  // //////////////////////////////////
  // Akhir Real Array
  // //////////////////////////////////

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

  par.mvc_lex = mvc_lex;
  par.mvc_pg  = mvc_pg;
  
  return par;

}

