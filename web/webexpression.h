// //////////////////////////////////////////////////////////////////////
// Web MVC View Parser - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
//
// //////////////////////////////////////////////////////////////////////

// ///////////////////////////////////
// MYSQL Function
// ///////////////////////////////////
#ifdef USE_MYSQL
#include "./funcMVC_Mysql.h"
#endif

MVCPARSING MVCInterpreter( char perintah[262144], int pt_start , int pt_stop );
MVCPARSING MVCgetlex(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVCungetlex(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);

MVCPARSING MVC_expression(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_AndOr(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_NotFunc(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_Compare(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_AddSub(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_MultiDiv(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_Factor(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);


MVCPARSING MVC_expression(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  return ( MVC_AndOr(mvc_lex, mvc_pg) );
}



MVCPARSING MVC_AndOr(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  MVCPARSING dat, tmp;

  MVCPARSING par;

  memset(&par, '\0', sizeof(par));

  memset(&dat, '\0', sizeof(dat));
  memset(&tmp, '\0', sizeof(tmp));

  dat.val=0; tmp.val=0;
  dat = MVC_NotFunc(mvc_lex, mvc_pg);
  mvc_lex = dat.mvc_lex;
  mvc_pg  = dat.mvc_pg;  

  //getlex();
  par = MVCgetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;

  if( mvc_lex.type == _MVC_EOF )
    Error("MVC_AndOr: Program berhenti diluar perkiraan");

  while ( mvc_lex.type == _MVC_OR || mvc_lex.type == _MVC_AND ){

    switch( mvc_lex.type )
      {
      case _MVC_AND:
        tmp = MVC_NotFunc(mvc_lex, mvc_pg);
        mvc_lex = tmp.mvc_lex;
        mvc_pg  = tmp.mvc_pg;
	dat.val = ( dat.val && tmp.val ) ? 1 : 0;
	break;
      case _MVC_OR:
        tmp = MVC_NotFunc(mvc_lex, mvc_pg);
        mvc_lex = tmp.mvc_lex;
        mvc_pg  = tmp.mvc_pg;
	dat.val = ( dat.val || tmp.val ) ? 1 : 0;
	break;
      }

    //getlex();
    par = MVCgetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  = par.mvc_pg;
  }

  //ungetlex();
  par = MVCungetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  = par.mvc_pg;

  //printf("after MVC_AndOr val %d\n", dat.val);
  //printf("after MVC_AndOr pt %d\n", mvc_pg.pt);

  dat.mvc_lex = mvc_lex;
  dat.mvc_pg  = mvc_pg;

  return dat;
}



MVCPARSING MVC_NotFunc(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  MVCPARSING datx, tmp;

  MVCPARSING par;

  memset(&par, '\0', sizeof(par));

  memset(&datx, '\0', sizeof(datx));
  memset(&tmp, '\0', sizeof(tmp));

  datx.val=0; tmp.val=0;
  
  //printf("inside MVC_NotFunc\n");

  //getlex();
  par = MVCgetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;

  if( mvc_lex.type == _MVC_EOF )
    Error("MVC_NotFunc: Program berhenti diluar perkiraan");

  if( mvc_lex.type != _MVC_NOT ){
    //ungetlex();
    par = MVCungetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  = par.mvc_pg;

    //printf("MVC_NotFunc: before MVC_Compare1, pt %d\n", mvc_pg.pt);
    
    tmp = MVC_Compare(mvc_lex, mvc_pg);
    mvc_lex = tmp.mvc_lex;
    mvc_pg  = tmp.mvc_pg;

    //printf("MVC_NotFunc: after MVC_Compare1, pt %d\n", mvc_pg.pt);

    return ( tmp );
  }

  //printf("MVC_NotFunc: before MVC_Compare2, pt %d\n", mvc_pg.pt);

  tmp = MVC_Compare(mvc_lex, mvc_pg);
  mvc_lex = tmp.mvc_lex;
  mvc_pg  = tmp.mvc_pg;  

  //printf("MVC_NotFunc: after MVC_Compare2, pt %d\n", mvc_pg.pt);

  datx.val = ( ( tmp.val != 0 ) ? 0 : 1 );

  // printf("MVC_NotFunc datx_val %d\n" , datx.val);

  datx.mvc_lex = mvc_lex;
  datx.mvc_pg  = mvc_pg;

  return datx;
}


MVCPARSING MVC_Compare(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  MVCPARSING datx = MVC_AddSub(mvc_lex, mvc_pg);
  MVCPARSING daty = datx;

  MVCPARSING datx2;

  char symbol;

  MVCPARSING tmp;

  MVCPARSING par;

  memset(&par, '\0', sizeof(par));

  memset(&datx2, '\0', sizeof(datx2));
  memset(&tmp, '\0', sizeof(tmp));

  mvc_lex = datx.mvc_lex;
  mvc_pg  = datx.mvc_pg;

  //printf("start Compare pt %d\n", mvc_pg.pt);
  //printf("start Compare source %s\n", mvc_pg.source);  

  //getlex();
  par = MVCgetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;

  //printf("after getlex Compare pt %d\n", mvc_pg.pt);
  //printf("lex type %d sym %c\n", mvc_lex.type, mvc_lex.detail.symbol);

  if( mvc_lex.type == _MVC_EOF )
    Error("MVC_Compare: Program berhenti diluar perkiraan");

  if( ( mvc_lex.type != TYPE_MVC_SYM ) || 
      ( mvc_lex.detail.symbol != '=' &&
        mvc_lex.detail.symbol != '<' &&
        mvc_lex.detail.symbol != '>' ) ){

    //ungetlex();
    //printf("Compare before ungetlex pt %d\n", mvc_pg.pt);    
    
    par = MVCungetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  = par.mvc_pg;

    //printf("Compare after ungetlex pt %d\n", mvc_pg.pt);

    //printf("FAILED/END Comparison\n");

    daty.mvc_lex = mvc_lex;
    daty.mvc_pg  = mvc_pg;

    return daty;
  }
  
  //printf("Start Comparison\n");
  

  symbol = mvc_lex.detail.symbol;

  //getlex();
  par = MVCgetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;

  //printf("after getlex Compare pt %d\n", mvc_pg.pt);
  //printf("lex type %d \n", mvc_lex.type);

  if( mvc_lex.type == _MVC_EOF )
    Error("MVC_Compare: Program berhenti diluar perkiraan");

  switch( symbol )
    {
    case '=':
      if( mvc_lex.type == TYPE_MVC_SYM ){
	switch( mvc_lex.detail.symbol )
	  {

	  case '=':
            /* printf("perbandingan , type %d\n", datx.datatype); */
            if(datx.datatype == 0) {
              /*
              perbandingan : integer
              return : integer
              */
              daty.val = ( datx.val == MVC_AddSub(mvc_lex, mvc_pg).val ) ? 1 : 0;
            } else if(datx.datatype == 1) {
              daty.val = ( datx.floatdata == MVC_AddSub(mvc_lex, mvc_pg).floatdata ) ? 1 : 0;
            } else if(datx.datatype == 3 || datx.datatype == 42 ) {
              tmp = MVC_AddSub(mvc_lex, mvc_pg);
              if( !strcmp(datx.str, tmp.str) ) {
                daty.val = 1;
              } else { 
                daty.val = 0;
              }   
            }

	    break;
	  default:
	    Error("setelah '=', ada simbol lain selain '=' ");
	  }
      }
      /* '=' */
      else{
	    //ungetlex();
            par = MVCungetlex(mvc_lex, mvc_pg);
            mvc_lex = par.mvc_lex;
            mvc_pg  =par.mvc_pg;
	    return ( MVC_AddSub(mvc_lex, mvc_pg) );
      }
      break;
      
    case '>':
      if( mvc_lex.type == TYPE_MVC_SYM ){
	switch( mvc_lex.detail.symbol )
	  {
	    /* '>=' */
	  case '=':
            if(datx.datatype == 0) {
              daty.val = ( datx.val >= MVC_AddSub(mvc_lex, mvc_pg).val ) ? 1 : 0;
            } else  if(datx.datatype == 1) {
              daty.val = ( datx.floatdata >= MVC_AddSub(mvc_lex, mvc_pg).floatdata ) ? 1 : 0;
            }

	    break;
	  default:
	    Error("setelah '>', ada simbol lain selain '=' ");
	  }
      }
      /* '>' */
      else{
	//ungetlex();
        par = MVCungetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  =par.mvc_pg;

        if(datx.datatype == 0) {
          daty.val = ( datx.val > MVC_AddSub(mvc_lex, mvc_pg).val ) ? 1 : 0;
        } else  if(datx.datatype == 1) {
          daty.val = ( datx.floatdata > MVC_AddSub(mvc_lex, mvc_pg).floatdata ) ? 1 : 0;
        }
        
      }
      break;
      
    case '<':
      if( mvc_lex.type == TYPE_MVC_SYM ){
	switch( mvc_lex.detail.symbol )
	  {
	    /* '<>' */
	  case '>':
            if(datx.datatype == 0) {
              daty.val = ( datx.val != MVC_AddSub(mvc_lex, mvc_pg).val ) ? 1 : 0;
            } else  if(datx.datatype == 1) {
              daty.val = ( datx.floatdata != MVC_AddSub(mvc_lex, mvc_pg).floatdata ) ? 1 : 0;
            } else  if(datx.datatype == 3) { 
              tmp = MVC_AddSub(mvc_lex, mvc_pg);
              daty.val = ( strcmp(datx.str, tmp.str) ) ? 1 : 0;
            }
	    break;
	    /* '<=' */
	  case '=':
            if(datx.datatype == 0) {
              daty.val = ( datx.val <= MVC_AddSub(mvc_lex, mvc_pg).val ) ? 1 : 0;
            } else  if(datx.datatype == 1) {
              daty.val = ( datx.floatdata <= MVC_AddSub(mvc_lex, mvc_pg).floatdata ) ? 1 : 0;
            }

	    break;
	  default:
	    Error("setelah '<', ada simbol lain selain '>' atau '=' ");
	  }
      }
      else{
        //printf("< less than comparison\n");
	//ungetlex();
        par = MVCungetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  =par.mvc_pg;

        if(datx.datatype == 0) {
          daty.val = ( datx.val < MVC_AddSub(mvc_lex, mvc_pg).val ) ? 1 : 0;
        } else  if(datx.datatype == 1) {
          daty.val = ( datx.floatdata < MVC_AddSub(mvc_lex, mvc_pg).floatdata ) ? 1 : 0;
        }
        
        //printf("compare result : %d\n", daty.val);
      }
      break;
      
    default:
      Error("Salah tata kalimat");
    }

  //printf("after Compare pt %d\n", mvc_pg.pt);

  daty.mvc_lex = mvc_lex;
  daty.mvc_pg  = mvc_pg;

  return daty;
}



MVCPARSING MVC_AddSub(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  /* datatype¡§0->int, 1->float, 2->File, 3->String */

  MVCPARSING datx = MVC_MultiDiv(mvc_lex, mvc_pg);
  MVCPARSING datx2;

  MVCPARSING par;

  memset(&par, '\0', sizeof(par));
  memset(&datx2, '\0', sizeof(datx2));

  // printf("MVC_AddSub datatype : %d\n" , datx.datatype); 
  mvc_lex = datx.mvc_lex;
  mvc_pg  = datx.mvc_pg;
  
  //printf("start AddSub pt %d\n", mvc_pg.pt);  
  //printf("start AddSub source %s\n", mvc_pg.source);

  //getlex();
  par = MVCgetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;

  if( mvc_lex.type == _MVC_EOF )
    Error("MVC_AddSub: Program berhenti diluar perkiraan");
  
  while( mvc_lex.type == TYPE_MVC_SYM && 
	 ( mvc_lex.detail.symbol == '+' ||
	   mvc_lex.detail.symbol == '-' ) ){

    switch( mvc_lex.detail.symbol )
      {
      case '+':
        if(datx.datatype == 0) {
          datx2 = MVC_MultiDiv(mvc_lex, mvc_pg);
          if(datx2.datatype == 0) {
            datx.val = datx.val + datx2.val;
            datx.datatype = 0;
          } else if(datx2.datatype == 1) {
            datx.floatdata = datx.val + datx2.floatdata;
            datx.datatype = 1;
          } else {
            Error("salah dalam penjumlahan");
          }
	} else if(datx.datatype == 1) {
          datx2 = MVC_MultiDiv(mvc_lex, mvc_pg);
          if(datx2.datatype == 0) {
            datx.floatdata = datx.floatdata + datx2.val;
          } else if(datx2.datatype == 1) {
            datx.floatdata = datx.floatdata + datx2.floatdata;
          } else {
            Error("salah dalam penjumlahan");
          }
          datx.datatype = 1;
          /* printf("f (a+b) : %f\n" , datx.floatdata); */
	} else {
          Error("salah dalam penjumlahan");
        }
	break;
	
      case '-':
        if(datx.datatype == 0) {
          datx2 = MVC_MultiDiv(mvc_lex, mvc_pg);
          if(datx2.datatype == 0) {
            datx.val = datx.val - datx2.val;
            datx.datatype = 0;
          } else if(datx2.datatype == 1) {
            datx.floatdata = datx.val - datx2.floatdata;
            datx.datatype = 1;
          } else {
            Error("salah dalam pengurangan");
          }
        } else if(datx.datatype == 1) {
          datx2 = MVC_MultiDiv(mvc_lex, mvc_pg);
          if(datx2.datatype == 0) {
            datx.floatdata = datx.floatdata - datx2.val;
          } else if(datx2.datatype == 1) {
            datx.floatdata = datx.floatdata - datx2.floatdata;
          } else {
            Error("salah dalam pengurangan");
          }
          datx.datatype = 1;
        } else {
          Error("salah dalam pengurangan");
        }
	break;
      }

    //getlex();
    par = MVCgetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  =par.mvc_pg;

  }

  //ungetlex();
  par = MVCungetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;

  //printf("after AddSub pt %d\n", mvc_pg.pt);

  datx.mvc_lex = mvc_lex;
  datx.mvc_pg  = mvc_pg;

  return datx;
}




MVCPARSING MVC_MultiDiv(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  /* datatype¡§0->int, 1->float, 2->File, 3->String */

  MVCPARSING datx = MVC_Factor(mvc_lex, mvc_pg);
  MVCPARSING daty = datx;

  MVCPARSING par;

  memset(&par, '\0', sizeof(par));

  // printf("MVC_MultiDiv datatype  : %d\n" , datx.datatype);
  // printf("MVC_MultiDiv ident : %s\n" , datx.str);

  mvc_lex = datx.mvc_lex;
  mvc_pg  = datx.mvc_pg;  
  
  //printf("start MulitDiv pt %d\n", mvc_pg.pt);  
  
  //getlex();
  par = MVCgetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;

  if( mvc_lex.type == _MVC_EOF )
    Error("MVC_MultiDiv: Program berhenti diluar perkiraan");

  while( mvc_lex.type == TYPE_MVC_SYM && 
	 ( mvc_lex.detail.symbol == '*' ||
	   mvc_lex.detail.symbol == '/' ||
	   mvc_lex.detail.symbol == '^' ||
	   mvc_lex.detail.symbol == '%' ) ){
    
    switch( mvc_lex.detail.symbol )
      {
      case '*':
	datx = MVC_Factor(mvc_lex, mvc_pg);

        if(daty.datatype == 0 && datx.datatype == 0) {
	  daty.val = daty.val * datx.val;
          daty.datatype = 0;
        } else if(daty.datatype == 1 && datx.datatype == 0) {
	  daty.floatdata = daty.floatdata * datx.val;
          daty.datatype = 1;
        } else if(daty.datatype == 0 && datx.datatype == 1) {
	  daty.floatdata = daty.val * datx.floatdata;
          daty.datatype = 1;
        } else if(daty.datatype == 1 && datx.datatype == 1) {
	  daty.floatdata = daty.floatdata * datx.floatdata;
          daty.datatype = 1;

        } else {
	  Error("Salah dalam perkalian");
        }


	break;
	
      case '/':
	datx = MVC_Factor(mvc_lex, mvc_pg);

        if(daty.datatype == 0 && datx.datatype == 0) {
	  if( datx.val == 0 )
	    Error("Dibagi dengan Nol");
	  daty.floatdata = (float)daty.val / (float)datx.val;
        } else if(daty.datatype == 1 && datx.datatype == 0) {
	  if( datx.val == 0 )
	    Error("Dibagi dengan Nol");
	  daty.floatdata = daty.floatdata / (float)datx.val;
        } else if(daty.datatype == 0 && datx.datatype == 1) {
	  if( datx.floatdata == 0.0 )
	    Error("Dibagi dengan Nol");
	  daty.floatdata = (float)daty.val / datx.floatdata;
        } else if(daty.datatype == 1 && datx.datatype == 1) {
	  if( datx.floatdata == 0.0 )
	    Error("Dibagi dengan Nol");
	  daty.floatdata = daty.floatdata / datx.floatdata;

        } else {
	  Error("Salah dalam pembagian");
        }

        //printf("y: %d\n" , daty.val);
        //printf("x: %d\n" , datx.val);
        // printf("f (y/x) : %f\n" , daty.floatdata);

        daty.val = datx.val; /* pos */

        daty.datatype = 1;

	break;
	
      case '^':
	datx = MVC_Factor(mvc_lex, mvc_pg);

        if(daty.datatype == 0 && datx.datatype == 0) {
	  daty.val = (int) pow ( (double)daty.val , (double)datx.val );
          daty.datatype = 0;
        } else if(daty.datatype == 1 && datx.datatype == 0) {
	  daty.floatdata = pow ( daty.floatdata , (double)datx.val );
          daty.val = datx.val; /* pos */
          daty.datatype = 1;
        } else if(daty.datatype == 0 && datx.datatype == 1) {
	  daty.floatdata = pow ( (double)daty.val , datx.floatdata );
          daty.val = datx.val; /* pos */
          daty.datatype = 1;
        } else if(daty.datatype == 1 && datx.datatype == 1) {
	  daty.floatdata = pow ( daty.floatdata , datx.floatdata );
          daty.val = datx.val; /* pos */
          daty.datatype = 1;

        } else {
	  Error("Salah dalam pemangkatan");
        }

        //printf("y: %d\n" , daty.val);
        //printf("x: %d\n" , datx.val);
        //printf("f (y^x) : %f\n" , daty.floatdata);

	break;


      case '%':
	datx = MVC_Factor(mvc_lex, mvc_pg);

        if(daty.datatype == 0 && datx.datatype == 0) {
	  if( datx.val == 0 )
	    Error("Dibagi dengan Nol untuk modulus");
	  daty.val = daty.val % datx.val;
        } else if(daty.datatype == 1 && datx.datatype == 0) {
	  if( datx.val == 0 )
	    Error("Dibagi dengan Nol untuk modulus");
	  daty.val = abs(daty.floatdata) % datx.val;
        } else if(daty.datatype == 0 && datx.datatype == 1) {
	  if( datx.floatdata == 0.0 )
	    Error("Dibagi dengan Nol untuk modulus");
	  daty.val = daty.val % abs(datx.floatdata);
        } else if(daty.datatype == 1 && datx.datatype == 1) {
	  if( datx.floatdata == 0.0 )
	    Error("Dibagi dengan Nol untuk modulus");
	  daty.val = abs(daty.floatdata) % abs(datx.floatdata);

        } else {
	  if( datx.val == 0 )
	    Error("Dibagi dengan Nol untuk modulus");
	  daty.val = daty.val % datx.val;
        }

        //printf("y: %d\n" , daty.val);
        //printf("x: %d\n" , datx.val);
        // printf("f (y/x) : %f\n" , daty.floatdata);

        daty.datatype = 0;

	break;
      }

    //getlex();
    par = MVCgetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  =par.mvc_pg;
  }

  //ungetlex();
  par = MVCungetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  =par.mvc_pg;

  //printf("after MulitDiv pt %d\n", mvc_pg.pt);

  daty.mvc_lex = mvc_lex;
  daty.mvc_pg  = mvc_pg;

  return daty;
}




MVCPARSING MVC_Factor(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  MVCPARSING datx;
  
  char   tmp_ident[MAX_STRING_LEN];

  char   logMsg[MAX_STRING_LEN];
  char   tmpMsg[MAX_STRING_LEN];

  char   **mysplit=NULL;

  float tmp   = 0.0;
  int   point = 0;
  int   n     = 0;

  int  i=0, j=0;

  char get_param[MAX_STRING_LEN],
       orig_param[MAX_STRING_LEN],
       param_source[MAX_STRING_LEN * 2];

  VAL_LABEL valdat, tmpdat;
  int    idx = 0;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  MVCPARSING par;

  memset(&par, '\0', sizeof(par));

  //printf("Enter MVC_Factor\n");

  memset(&datx, '\0', sizeof(datx));

  memset(&logMsg, '\0', sizeof(logMsg));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmp_ident, '\0', sizeof(tmp_ident));

  memset(&get_param, '\0', sizeof(get_param));
  memset(&orig_param, '\0', sizeof(orig_param));
  memset(&param_source, '\0', sizeof(param_source));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  valdat.val     = 0;

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  //printf("start Factor pt %d\n", mvc_pg.pt);


  //getlex();
  par = MVCgetlex(mvc_lex, mvc_pg);
  mvc_lex = par.mvc_lex;
  mvc_pg  = par.mvc_pg;

  strcpy(tmp_ident, mvc_lex.detail.string);
  
  //printf("lex type : %d , pt %d\n", mvc_lex.type, mvc_pg.pt); 
  

  switch( mvc_lex.type )
    {
    case TYPE_MVC_IDENT:
        // printf("MVC_Factor IDENT: %s <BR>\n", tmp_ident);
 
        /* ======================================================== */
        /* MYSQL_ISIDATA       ==================================== */
        /* ======================================================== */
        if( !strcmp(tmp_ident, "MYSQL_ISIDATA") ||
            !strcmp(tmp_ident, "mysql_isidata") ||
            !strcmp(tmp_ident, "Mysql_IsiData") ) {

            //printf("MVC_IDENT : MYSQL_DATA function\n"); 
            datx = funcMVC_MYSQL_ISIDATA(mvc_lex, mvc_pg);

            //printf("get datx datatype : %d\n", datx.datatype);
            //printf("get datx array_max : %d\n", datx.array_max);            

            mvc_lex = datx.mvc_lex;
            mvc_pg  = datx.mvc_pg;

        }else {
          valdat = ValLabel(tmp_ident, 0, valdat, VAL_FLAG_SEARCH_R);
        
          datx.datatype  = valdat.datatype;
          datx.val       = valdat.val;
          datx.floatdata = valdat.floatdata;
          strcpy(datx.str , valdat.str);
          strcpy(datx.array_str,  valdat.array_str);
          strcpy(datx.array_name, valdat.array_name);
          strcpy(datx.array_idx,  valdat.array_idx);
        }
        
        //printf("Factor IDENT datatype %d\n", datx.datatype);
        //printf("Factor IDENT float %f\n", datx.floatdata);
        //printf("Factor IDENT val %d <BR>\n", datx.val);
        //printf("Factor IDENT str %s\n", datx.str);  

        memset(&valdat, '\0', sizeof(valdat));

      break;
      
    case TYPE_MVC_NUM:
      //printf("MVC_Factor NUM\n");

      if(mvc_lex.detail.num != '\0')
        datx.val = mvc_lex.detail.num;
      else
        datx.val = 0;

       /*printf("Factor NUM val %d\n", datx.val);
         printf("Factor NUM str %s\n", datx.str); */

      break;

    case TYPE_MVC_DBL:
      // printf("Factor DBL\n");

      if(mvc_lex.detail.dblnum != '\0')
        datx.floatdata = mvc_lex.detail.dblnum;
      else
        datx.floatdata = 0.0;

      datx.datatype = 1;

      // printf("Factor DBL val %f\n", datx.floatdata);

      break;

    case TYPE_MVC_STR:
      // printf("Factor STR\n");
      if(mvc_lex.detail.num != '\0')
        datx.val = mvc_lex.detail.num;
      else
        datx.val = 0;

      /* printf("var string pos : %d\n", mvc_lex.detail.num);
         printf("var string : %s\n", mvc_lex.detail.string);  */
	  if(mvc_lex.detail.string != '\0' && strlen(mvc_lex.detail.string) > 0) {
        strcpy(datx.str , mvc_lex.detail.string);
	  } else {
        strcpy(datx.str , "");
	  }

      break;

    case TYPE_MVC_ARRAY:
      //printf("Factor ARRAY\n"); 

      break;

      
    case TYPE_MVC_SYM:

      /* ******************* minus number ********************  */
      if( mvc_lex.detail.symbol == '-' )  {
        /* printf("minus number\n");                            */

        //getlex();
        par = MVCgetlex(mvc_lex, mvc_pg);
        mvc_lex = par.mvc_lex;
        mvc_pg  =par.mvc_pg;


        if(mvc_lex.type == TYPE_MVC_NUM) {

          mvc_lex.detail.num = 0 - mvc_lex.detail.num;

          datx.val      = mvc_lex.detail.num;
          datx.datatype = 0;

        } else if(mvc_lex.type == TYPE_MVC_DBL) {

          mvc_lex.detail.dblnum =  0.0 - mvc_lex.detail.dblnum;

          datx.floatdata = mvc_lex.detail.dblnum;
          datx.datatype  = 1;

        } else {
          Error("Salah bentuk bilangan negatif");
        }

      } 

      break;
      
    default:
      Error("Label/Variabel: Salah tata kalimat");
    }

     
     //printf("  Factor type %d\n", datx.datatype);

     /*
     printf("  Factor val %d\n", datx.val);
     printf("  Factor str %s\n", datx.str); 
     */

  //printf("after Factor pt %d\n", mvc_pg.pt);
  //printf("after Factor source %s\n", mvc_pg.source);  

  datx.mvc_lex = mvc_lex;
  datx.mvc_pg  = mvc_pg;
  datx.mvc_pg.pt = mvc_pg.pt;

  return datx;
}



