// //////////////////////////////////////////////////////////////////////
// Web MVC View Parser - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
//
// //////////////////////////////////////////////////////////////////////


MVCPARSING MVCInterpreter( char perintah[262144], int pt_start , int pt_stop );
MVCPARSING MVCgetlex(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVCungetlex(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVCGetChar(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVCGetNextChar(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVClex_ident(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING  MVClex_const(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVClex_double( MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg );
MVCPARSING MVClex_string(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVClex_array(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);

MVCPARSING MVClex_htmltag(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);

int MVCcheckFloat( MVC_S_ADDR mvc_pg );
int MVCcheckArray( MVC_S_ADDR mvc_pg );

int MVCLineCounter(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
void MVCError(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg, const char *format, ...);

int inside_web_code;

MVCPARSING keyMVC_Untuk(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING keyMVC_Array(char ident[MAX_STRING_LEN], MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING keyMVC_Untaian(char ident[MAX_STRING_LEN], MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);

MVCPARSING MVC_expression(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_AndOr(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_NotFunc(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_Compare(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_AddSub(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_MultiDiv(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);
MVCPARSING MVC_Factor(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg);

// Interprete View Code of MVC (Max 1 MB File)
MVCPARSING MVCInterpreter( char perintah[262144], int pt_start, int pt_stop )
{
  // create mvc_lex and mvc_pg in Lokal, not Global
  MVC_LEX_T mvc_lex;  
  MVC_S_ADDR mvc_pg;  

  int mvc_pg_stop;

  MVCPARSING par;

  char MVCstmt[4096];
  char stmt[MAX_IDENT_LEN];
  char *retMVC = NULL;

  char   tmp_str[MAX_STRING_LEN];
  char   ident[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  long    idx=0;     // array index
  int i = 0;

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmp_str, '\0', sizeof(tmp_str));
  memset(&ident, '\0', sizeof(ident));  

  memset( &mvc_lex, 0, sizeof(mvc_lex) );
  memset( &mvc_pg, 0, sizeof(mvc_pg) );

  memset( &MVCstmt, 0, sizeof(MVCstmt) );
  
  memset( &mvc_lex, 0, sizeof(MVC_LEX_T) );

  mvc_pg.pt      = 0;
  mvc_pg.back_pt = 0;
  mvc_pg_stop    = pt_stop;
  
  if(pt_start != 0) {
    mvc_pg.pt      = pt_start;
    mvc_pg.back_pt = pt_start;
  }

  mvc_pg.source = (char *)malloc((int)strlen(perintah)+1);
  mvc_pg.source = perintah;

  //printf("source perintah:%s\n", perintah);
  //printf("start pt %d\n", mvc_pg.pt);
  //printf("stop pt %d\n", mvc_pg_stop);  

  do {
    // clear tmp stmt
    memset( &stmt, 0, sizeof(stmt) );

    memset( &par, 0, sizeof(par) );
    par = MVCgetlex(mvc_lex, mvc_pg);
    mvc_lex = par.mvc_lex;
    mvc_pg  =par.mvc_pg;

    //printf("lex:%d\n", mvc_lex.type);

    switch( mvc_lex.type )
      {

      case _MVCEND:
    	mvc_lex.type = _MVC_EOF;
	  break;
	  
      case TYPE_MVC_STR:
            printf("! outside str %s", mvc_lex.detail.string);
            exit(1);
	  break;	  

      case _MVC_START:
            // printf("%c",mvc_lex.detail.symbol);
            memset( &par, 0, sizeof(par) );
            par = MVCgetlex(mvc_lex, mvc_pg);
            mvc_lex = par.mvc_lex;
            mvc_pg  =par.mvc_pg;      
          break;
          
      case _MVC_STOP:
            // printf("%c",mvc_lex.detail.symbol);
            memset( &par, 0, sizeof(par) );
            par = MVCgetlex(mvc_lex, mvc_pg);
            mvc_lex = par.mvc_lex;
            mvc_pg  =par.mvc_pg;    
            // printf("2stop");
          break;          


      case _MVC_TULIS:
           //printf("\nmvctulis...pt %d\n", mvc_pg.pt);

	  do{

 	    par = MVCgetlex(mvc_lex, mvc_pg);
	    mvc_lex = par.mvc_lex;
	    mvc_pg = par.mvc_pg;

            //printf("type %d\n", mvc_lex.type);

	    switch (mvc_lex.type)
	    {
	       case TYPE_MVC_STR:
                  //printf("str\n");
                                  
		  printf("%s", mvc_lex.detail.string);

		  break;

           case TYPE_MVC_ARRAY:
              //printf("Tulis mvc array\n");

              if(strlen(mvc_lex.detail.array_str) > 0) {
                strcpy(valdat.array_str, mvc_lex.detail.array_str);
                getArrayName(mvc_lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(mvc_lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atol (valdat.array_idx);
                } else {
                   // printf("show NOT digit : %s\n", valdat.array_idx);
                   /* Read index param */

                   tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
                   // printf("get idx type: %d, val %d\n",tmpdat.datatype, tmpdat.val);

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

                // get real value of array
                //printf("search array: %s\n", valdat.array_name);
                
                valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                // ltoa(idx, valdat2.array_idx, 10);
                sprintf(valdat2.array_idx, "%li", idx);

                //printf("idx %d\n", idx);
                //printf("array max kapasitas %d\n", valdat2.array_max);

                if(valdat2.array_max <= 0) {
                  printf("nil ");  // Untaian nil / terhapus
                } else {
                  if(idx < 0 || idx > (valdat2.array_max-1))
                    Error("ukuran Untaian tidak sesuai kapasitas");
                }

                //printf("get valdat2 type: %d \n", valdat2.datatype);

                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  if(get_int_array(valdat2, idx) == '\r') {
                    printf("nil");
                  } else {
                    printf("%d", get_int_array(valdat2, idx) );
                  }

                } else if (valdat2.datatype == 7) {
                  if(valdat2.array_d == '\0')
                    Error("ukuran Untaian belum terdefinisi: pecahan");

                  if(get_dbl_array(valdat2, idx) == '\r') {
                    printf("nil");
                  } else {
                    printf("%f", get_dbl_array(valdat2, idx) );
                  }

                } else if (valdat2.datatype == 8) {
                  // printf("tulis arry string\n");
                  if(valdat2.array_s == '\0')
                    Error("ukuran Untaian belum terdefinisi: kata");

                  if(!get_str_array(valdat2, idx, (char *)&tmp_str)) {
                    printf("nil %s", tmp_str);
                  } else {
                    printf("%s", tmp_str );
                  }

                } else if (valdat2.datatype == 10) {
                  if(valdat2.long_str != NULL) {
                    printf("%s", valdat2.long_str[idx]);
                  }
                } else {
                  printf("");
                }

             }

            break;


          case TYPE_MVC_IDENT:
              //printf("ident\n");
                                  
              valdat = ValLabel(mvc_lex.detail.ident, 0, valdat, VAL_FLAG_SEARCH_R);

	      if (valdat.str != '\0' && strlen(valdat.str) > 0) {
		  for (i = 0; i < (int)strlen(valdat.str); i++)
	            printf("%c", valdat.str[i]);
		  }
	      else if (valdat.datatype == 1) {
		  printf("%f", valdat.floatdata);
	      }
	      else if (valdat.datatype == 0) {
		  printf("%d", valdat.val);
	      }

	    break;

	    default:
	        Error("kode perintah MVC TULIS salah");
	   }
			  
            par = MVCgetlex(mvc_lex, mvc_pg);
            //printf("pos %d back %d ", par.mvc_pg.pt, par.mvc_pg.back_pt);
            mvc_lex = par.mvc_lex;
            mvc_pg  = par.mvc_pg;
            
	  } while (mvc_lex.type == TYPE_MVC_SYM && mvc_lex.detail.symbol == ',');

	  fflush(stdout);

          //printf("c %c %c", mvc_pg.source[mvc_pg.pt], mvc_pg.source[mvc_pg.back_pt]);

          if(mvc_pg.source[mvc_pg.pt] == '>') {
            par = MVCgetlex(mvc_lex, mvc_pg);
            mvc_lex = par.mvc_lex;
            mvc_pg  = par.mvc_pg;
          } else {
                  
            //printf("ungetlex\n");
            par = MVCungetlex(mvc_lex, mvc_pg);
            mvc_lex = par.mvc_lex;
            mvc_pg  = par.mvc_pg;                  

            //printf("c %c %c", mvc_pg.source[mvc_pg.pt], mvc_pg.source[mvc_pg.back_pt]);
                  
           }
	  break;

      case _MVC_UNTUK:
           //printf("GET UNTUK...\n");
           par = keyMVC_Untuk(mvc_lex, mvc_pg);
           mvc_lex = par.mvc_lex;
           mvc_pg  = par.mvc_pg;
          // printf("FINISH UNTUK...pt %d\n", mvc_pg.pt);           
	  break;

      case _MVC_ULANG:

	  break;

      case _MVC_LAGI:
            //printf("LAGI , pt %d\n", mvc_pg.pt);
	  break;

      case TYPE_MVC_SYM:
           printf("%c",mvc_lex.detail.symbol);

	  break;
	  
      case TYPE_MVC_IDENT:
           strcpy( ident, mvc_lex.detail.ident );
           
           if( inside_web_code != 1 ) {      
             printf("%s ",mvc_lex.detail.ident);
           } else {
             par = MVCungetlex(mvc_lex, mvc_pg);
             mvc_lex = par.mvc_lex;
             mvc_pg  = par.mvc_pg;                             

             par = MVC_expression(mvc_lex, mvc_pg);
             mvc_lex = par.mvc_lex;
             mvc_pg  = par.mvc_pg;           

             tmpdat.datatype  = par.datatype;
             tmpdat.val       = par.val;
             tmpdat.floatdata = par.floatdata;
             strcpy(tmpdat.str, par.str);
             tmpdat.array_max = par.array_max;
             tmpdat.array_i   = par.array_i;
             tmpdat.array_d   = par.array_d;             
             tmpdat.array_s   = par.array_s;

             //printf ("saving ident %s ...\n", ident);
             ValLabel( ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_W );

           }

	  break;	  
	  
      case TYPE_MVC_ARRAY:
           strcpy( ident, mvc_lex.detail.array_str);
           if( inside_web_code != 1 ) {      
             printf("%s ",ident);
           } else {
             par = keyMVC_Array(ident, mvc_lex, mvc_pg);
             mvc_lex = par.mvc_lex;
             mvc_pg  = par.mvc_pg;                             
           }

	  break;	  	  
	  
      case _MVC_UNTAI:
           //printf("_MVC_UNTAI\n");
           strcpy( ident, mvc_lex.detail.string);
           if( inside_web_code != 1 ) {      
             printf("%s ",ident);
           } else {
             par = keyMVC_Untaian(ident, mvc_lex, mvc_pg);
             mvc_lex = par.mvc_lex;
             mvc_pg  = par.mvc_pg;                             
           }

	  break;	  	  	  
	  
	  
      case TYPE_MVC_HTMLTAG:
           if( inside_web_code != 1 ) {
             printf("%s",mvc_lex.detail.ident);
           } else {
             printf("inside code...\n");
             printf("%s",mvc_lex.detail.ident);             
             exit(1);
           }

	  break;	  	  

      case _MVC_EOF:
	  break;

      default:
        printf("salah: tidak bisa baca view ! <BR>\n");
		exit(1);
	  break;

      }

  }while( mvc_lex.type != _MVC_EOF && mvc_pg.pt < mvc_pg_stop );

  par.mvc_lex = mvc_lex;
  par.mvc_pg  = mvc_pg;
  
  return par;

}


MVCPARSING MVCgetlex( MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg )
{
  MVCPARSING par;
  MVCPARSING par1;
  
  char c='\0';
  char c1='\0';

  int  i=0;

  par.mvc_lex = mvc_lex;
  par.mvc_pg  = mvc_pg;
  par.c       = c;

  par1.mvc_lex = mvc_lex;
  par1.mvc_pg  = mvc_pg;
  par1.c       = c;

  if( mvc_lex.type == _MVC_EOF ) {

    return par;
  }

  // printf("getlex source: %s\n", mvc_pg.source);

  mvc_pg.back_pt = mvc_pg.pt;

  par = MVCGetChar(mvc_lex, mvc_pg);
  mvc_pg = par.mvc_pg;
  c      = par.c;
  
  par1 = MVCGetNextChar(mvc_lex, mvc_pg);
  c1   = par1.c;  
  
  memset( &mvc_lex, 0, sizeof(MVC_LEX_T) );
  
  // printf("getlex c: %c\n", c);
  // printf("getlex c1: %c\n", c1);

  if( inside_web_code != 1 ) { 
    if( c == '<' && isalpha(c1) )
      return( MVClex_htmltag(mvc_lex, mvc_pg) );  
  }
    
  if( c == '<' && c1 == '/' )
    return( MVClex_htmltag(mvc_lex, mvc_pg) );      
  

  if( isalpha( c ) || c == '_' ) {
    i = MVCcheckArray( mvc_pg );
    
    if(i == 1) {
      return( MVClex_array(mvc_lex, mvc_pg) );
    } else {
      return( MVClex_ident(mvc_lex, mvc_pg) );
    }
  }

  if(inside_web_code != 1) {
    if( isdigit( c ) )
      return( MVClex_ident(mvc_lex, mvc_pg) );
  }

  if( isdigit( c ) ) {
     i = MVCcheckFloat( mvc_pg );
     
     if(i == 1){
        // printf("float\n");
        return( MVClex_double(mvc_lex, mvc_pg) );
     } else {
        // printf("not float\n");
        return( MVClex_const(mvc_lex, mvc_pg) );
     }
  }

  if( c == 0x22 )
    return( MVClex_string(mvc_lex, mvc_pg) );

  if( c == '\0' ) {
    mvc_lex.type = _MVC_EOF;

    par.c = c;
    par.mvc_pg  = mvc_pg;
    par.mvc_lex = mvc_lex;

    return par;
  }
  else
  if( c == '<' && c1 == '?' ) {
    inside_web_code = 1;
    mvc_lex.type = _MVC_START;
    // printf ("MVC_START<BR>\n");
    mvc_lex.detail.symbol = c1;    
    mvc_pg.pt++;

    par.c = c1;
    par.mvc_pg.pt  = mvc_pg.pt++;
    par.mvc_lex = mvc_lex;
                
    return par;
  }  
  else
  if( c == '?' && c1 == '>' ) {
    inside_web_code = 0;
    mvc_lex.type = _MVC_STOP;
    // printf ("MVC_STOP<BR>");    
    mvc_lex.detail.symbol = ' ';    
    mvc_pg.pt++;

    par.c = c1;
    par.mvc_pg.pt  = mvc_pg.pt++;
    par.mvc_lex = mvc_lex;
                
    return par;
  }    

  //printf("lex get sym\n");

  mvc_lex.type = TYPE_MVC_SYM;
  mvc_lex.detail.symbol = c;
  mvc_pg.pt++;
  

  par.c = c;
  par.mvc_pg  = mvc_pg;
  par.mvc_lex = mvc_lex;


  return par;
}


MVCPARSING MVCungetlex( MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
  MVCPARSING par;

  mvc_pg.pt = mvc_pg.back_pt;

  par.mvc_pg  = mvc_pg;
  par.mvc_lex = mvc_lex;  

  return par;  
}


MVCPARSING MVCGetChar( MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg )
{
  MVCPARSING par;
  char c;

  do{
    c = mvc_pg.source[mvc_pg.pt++];
    if( c == '#' )
      do{ c = mvc_pg.source[mvc_pg.pt++]; }while( c != '\0' && c != '\n' );
  }while( isspace( c ) && c != '\0' );

  if ( isspace(c) ) {
    printf("&nbsp;");
  }

  mvc_pg.pt--;

  par.c = c;
  par.mvc_pg  = mvc_pg;
  par.mvc_lex = mvc_lex;

  return par;
}

MVCPARSING MVCGetNextChar( MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg )
{
  MVCPARSING par;
    char c;
    
      do{
          c = mvc_pg.source[mvc_pg.pt++];
          if( c == '#' )
            do{ c = mvc_pg.source[mvc_pg.pt++]; }while( c != '\0' && c != '\n' );
          c = mvc_pg.source[mvc_pg.pt++];
      }while( isspace( c ) && c != '\0' );
                      
      mvc_pg.pt--;
      mvc_pg.pt--;
                        
      par.c = c;
      par.mvc_pg  = mvc_pg;
      par.mvc_lex = mvc_lex;
                              
      return par;
 }



MVCPARSING MVClex_htmltag( MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg )
{
  MVCPARSING par;
  char c;
  int i = 0;

  // printf("lex_htmltag\n");
  
  while( ( c = mvc_pg.source[mvc_pg.pt++] ) != '>' && inside_web_code == 0 ){
    

    if( i > 1024 )
      MVCError(mvc_lex, mvc_pg, "salah : melebihi panjang kapasitas 1024!\n" );

    mvc_lex.detail.ident[i++] = (char)c;
  }
  mvc_lex.detail.ident[i] = '>';
  mvc_lex.detail.ident[i++] = '\0';  

  mvc_pg.pt--;

  mvc_lex.type = TYPE_MVC_HTMLTAG;
  
  //printf("get html tag : %s\n", mvc_lex.detail.ident);

  par.c = c;
  par.mvc_pg  = mvc_pg;
  par.mvc_lex = mvc_lex;


  return par;
}


MVCPARSING MVClex_ident( MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg )
{
  MVCPARSING par;
  char c;
  int i = 0;

  // printf("lex_ident\n");
  
  while( isalnum( c = mvc_pg.source[mvc_pg.pt++] ) || c == '_' ){

    if( i > (MAX_IDENT_LEN - 1) )
      MVCError(mvc_lex, mvc_pg, "salah : melebihi panjang kapasitas %d", MAX_IDENT_LEN );

    mvc_lex.detail.ident[i++] = (char)c;
  }
  mvc_lex.detail.ident[i] = '\0';
  mvc_pg.pt--;

  mvc_lex.type = TYPE_MVC_IDENT;
  
  
  if( ! strcmp(mvc_lex.detail.ident, "LABEL") )
    mvc_lex.type = _MVCLABEL;
    
  if( ! strcmp(mvc_lex.detail.ident, "<?ina") )
    mvc_lex.type = _MVC_START;

  if( ! strcmp(mvc_lex.detail.ident, "?>") )
    mvc_lex.type = _MVC_STOP;    
  
  if (!strcmp(mvc_lex.detail.ident, "TULIS") || !strcmp(mvc_lex.detail.ident, "tulis")
	  || !strcmp(mvc_lex.detail.ident, "Tulis")) 
	    mvc_lex.type = _MVC_TULIS;
	    
  if (!strcmp(mvc_lex.detail.ident, "UNTUK") || !strcmp(mvc_lex.detail.ident, "untuk")
	  || !strcmp(mvc_lex.detail.ident, "Untuk")) 
	    mvc_lex.type = _MVC_UNTUK;	    
	    
  if (!strcmp(mvc_lex.detail.ident, "ULANG") || !strcmp(mvc_lex.detail.ident, "ulang")
	  || !strcmp(mvc_lex.detail.ident, "Ulang")) 
	    mvc_lex.type = _MVC_ULANG;	    	    

  if (!strcmp(mvc_lex.detail.ident, "LAGI") || !strcmp(mvc_lex.detail.ident, "lagi")
	  || !strcmp(mvc_lex.detail.ident, "Lagi")) 
	    mvc_lex.type = _MVC_LAGI;	    

  if( ! strcmp(mvc_lex.detail.ident, "DAN") || ! strcmp(mvc_lex.detail.ident, "dan")
        || ! strcmp(mvc_lex.detail.ident, "Dan"))    
            mvc_lex.type = _MVC_AND;
        
  if( ! strcmp(mvc_lex.detail.ident, "ATAU") || ! strcmp(mvc_lex.detail.ident, "atau")
        || ! strcmp(mvc_lex.detail.ident, "Atau"))    
            mvc_lex.type = _MVC_OR;
                
  if( ! strcmp(mvc_lex.detail.ident, "NOT") || ! strcmp(mvc_lex.detail.ident, "not")
        || ! strcmp(mvc_lex.detail.ident, "Not") || ! strcmp(mvc_lex.detail.ident, "BUKAN")
        || ! strcmp(mvc_lex.detail.ident, "bukan") || ! strcmp(mvc_lex.detail.ident, "Bukan"))
            mvc_lex.type = _MVC_NOT;

  if (!strcmp(mvc_lex.detail.ident, "END") || !strcmp(mvc_lex.detail.ident, "end") )
    mvc_lex.type = _MVCEND;

  if( ! strcmp(mvc_lex.detail.ident, "UNTAIAN") || ! strcmp(mvc_lex.detail.ident, "untaian")
        || ! strcmp(mvc_lex.detail.ident, "Untaian") || !strcmp(mvc_lex.detail.ident, "LARIK")
        || ! strcmp(mvc_lex.detail.ident, "larik") || ! strcmp(mvc_lex.detail.ident, "Larik"))
            mvc_lex.type = _MVC_UNTAI;

  // printf("get ident: %s\n", mvc_lex.detail.ident);

  par.c = c;
  par.mvc_pg  = mvc_pg;
  par.mvc_lex = mvc_lex;


  return par;
}


MVCPARSING  MVClex_const(  MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg )
{
  MVCPARSING par;
  char c;
  int num = 0;

  while( isdigit( c = mvc_pg.source[mvc_pg.pt++] ) )
    num = num * 10 + (int)(c - '0');
  
  mvc_lex.detail.num = num;
  
  mvc_pg.pt--;
  mvc_lex.type = TYPE_MVC_NUM;
  
  par.c = c;
  par.mvc_pg  = mvc_pg;
  par.mvc_lex = mvc_lex;

  //printf("lexnum:%d\n", par.mvc_lex.detail.num);

  return par;
}


MVCPARSING MVClex_double( MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg )
{
  char c; 
  int  i = 0;

  MVCPARSING par;

  memset(&par, '\0', sizeof(par));

  memset( &lex, 0, sizeof(BAIK_LEX) );

  do{
    c = mvc_pg.source[mvc_pg.pt++];

    // printf("%d %d \n", mvc_pg.pt, mvc_pg.back_pt);

    if( c == '\0' ) {
        break;
    }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
        break;
    }

    if( i > (MAX_STRING_LEN - 1) )
      Error("melebihi kapasitas MAX_STRING_LEN");
    
    mvc_lex.detail.string[i++] = (char)c;

  }while( !isspace( c ) && c != '\0' &&  c != ',' &&  c != '(' &&  c != ')'
           &&  c != '{' &&  c != '}' &&  c != ';' );

  if(mvc_lex.detail.string[i-1] == ',' ||
     mvc_lex.detail.string[i-1] == '(' ||
     mvc_lex.detail.string[i-1] == ')' ||
     mvc_lex.detail.string[i-1] == '{' ||
     mvc_lex.detail.string[i-1] == '}' ||
     mvc_lex.detail.string[i-1] == ';' ) {

       mvc_lex.detail.string[i-1] = '\0';
  } 

  mvc_pg.pt--;
  
  mvc_lex.detail.string[i] = '\0';

  /* printf("double str %s \n", mvc_lex.detail.string); */

  mvc_lex.detail.dblnum = strtodbl(mvc_lex.detail.string);

  /* printf("double %f \n", mvc_lex.detail.dblnum); */

  mvc_lex.type = TYPE_MVC_DBL;

  par.c = c;
  par.mvc_pg  = mvc_pg;
  par.mvc_lex = mvc_lex;

  return par;
}

// =============================================================================

int MVCcheckFloat( MVC_S_ADDR mvc_pg )
{
  char c='\0';
  int  isFloat = 0;
  int  i = 0,n = 0;

  /* printf("pg before %d\n", mvc_pg.pt); */

  do{
    c = mvc_pg.source[mvc_pg.pt++];
    n++;

    if(c == '.')
      isFloat = 1;

  }while( !isspace( c ) && c != '\0' );

  for(i=0; i<n; i++)
    mvc_pg.pt--;

  /* printf("pg after %d\n", mvc_pg.pt); */

  return isFloat;
}

int MVCcheckArray( MVC_S_ADDR mvc_pg )
{
  char c='\0';
  int  isArray = 0;
  int  i,n = 0;
  int  posKiri = 0, posKanan = 0;
  int  numKiri = 0, numKanan = 0;

  int  adaKurung = 0;

  /* printf("pg before %d\n", pg.pt); */

  //printf("inside checkArray: ");
  do{
    c = mvc_pg.source[mvc_pg.pt++];
    //printf("%c", c);

    n++;

    if(c == '[') {
      posKiri = mvc_pg.pt;
      numKiri++;
    }
    else if(c == ']') {
      posKanan = mvc_pg.pt;
      numKanan++;
    }
    else if(c == '(') {
      adaKurung = 1;
        }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
        break;
    }

  }while( !isspace( c ) && c != '=' && c != ',' && c != '(' && c != '\0' );
  //printf("\n");

  if(numKiri == 1 && numKanan == 1 && posKiri < posKanan && adaKurung == 0) {
    isArray = 1;
  }

  //printf("isArry %d\n", isArray);

  for(i=0; i<n; i++)
    mvc_pg.pt--;

  /* printf("pg after %d\n", pg.pt); */

  return isArray;

}

MVCPARSING MVClex_array(  MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg )
{
  char allarray[MAX_STRING_LEN];
  char c = '\0';
  int  i = 0;
  int  pp = 0;

  MVCPARSING par;
  
  memset(&par, '\0', sizeof(par));
  memset( allarray, '\0', sizeof(allarray) );

  do{
    c = mvc_pg.source[mvc_pg.pt++];

    if( c == '\0' ) {
        break;
    }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
        break;
    }


    if( i > (MAX_STRING_LEN - 1) )
      Error("melebihi kapasitas MAX_STRING_LEN");

    mvc_lex.detail.array_str[i++] = (char)c;

    pp = i;

    //printf("lex i-2 : %c  ,  ", mvc_lex.detail.array_str[pp-2]);
    //printf("lex i-1 : %c  ,  ", mvc_lex.detail.array_str[pp-1]);
    //printf("lex i : %c\n", mvc_lex.detail.array_str[pp]);

  if(mvc_lex.detail.array_str[pp-2] == ']' && mvc_lex.detail.array_str[pp-1] == '+')
          break;
  if(mvc_lex.detail.array_str[pp-2] == ']' && mvc_lex.detail.array_str[pp-1] == '-')
          break;

  }while( !isspace( c ) && c != '=' && c != ',' && c != '\0' &&  c != '(' && c != ')' 
          &&  c != '{' &&  c != '}' &&  c != ';'
                  );


  if(mvc_lex.detail.array_str[i-1] == ',' ||
     mvc_lex.detail.array_str[i-1] == '(' ||
     mvc_lex.detail.array_str[i-1] == ')' ||
     mvc_lex.detail.array_str[i-1] == '=' ||
     mvc_lex.detail.array_str[i-1] == '{' ||
     mvc_lex.detail.array_str[i-1] == '}' ||
     mvc_lex.detail.array_str[i-1] == ';'
         ) {
       mvc_lex.detail.array_str[i-1] = '\0';
  }

  if(mvc_lex.detail.array_str[pp-2] == ']' && mvc_lex.detail.array_str[pp-1] == '+') {
       mvc_lex.detail.array_str[i-1] = '\0';
  }

  if(mvc_lex.detail.array_str[pp-2] == ']' && mvc_lex.detail.array_str[pp-1] == '-') {
       mvc_lex.detail.array_str[i-1] = '\0';
  }

  mvc_pg.pt--;

  mvc_lex.detail.array_str[i] = '\0';
  strcpy(allarray, mvc_lex.detail.array_str);

  //printf("lex array str %s \n", allarray);

  mvc_lex.type = TYPE_MVC_ARRAY;

  par.c = c;
  par.mvc_pg  = mvc_pg;
  par.mvc_lex = mvc_lex;
  strcpy(par.array_str, allarray);  
      
  return par;
}




MVCPARSING MVClex_string(  MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg )
{
  MVCPARSING par;
  #ifndef S_SPLINT_S
  char c = 0x51;
  #else
  char c = '\0';
  #endif
  int i = 0;
  
  mvc_pg.pt++;
  
  while( (c = mvc_pg.source[mvc_pg.pt++]) != 0x22 )

  {
    if( c == '\0' )
    	MVCError(mvc_lex, mvc_pg, "salah! kata tanpa tanda petik");

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' )
      continue;

    if( c == '\\' ){

      c = mvc_pg.source[mvc_pg.pt++];

      switch( c )
      {
        case 'b':
          c = '\b';
          break;

        case 'f':
          c = '\f';
          break;

        case 'r':
          c = '\r';
          break;

        case 'n':
          c = '\n';
          break;

        case 't':
          c = '\t';
          break;
      }
    }
    
    if( i > (MAX_STRING_LEN - 1) )
      MVCError(mvc_lex, mvc_pg, "salah! melebihi MAX_STRING_LEN");
    
    mvc_lex.detail.string[i++] = (char)c;
  }
  
  mvc_lex.detail.string[i] = '\0';
  mvc_lex.type = TYPE_MVC_STR;

  par.c = c;
  par.mvc_pg  = mvc_pg;
  par.mvc_lex = mvc_lex;


  return par;
}


int MVCLineCounter(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg)
{
	char *ptr = NULL;
	int counter = 1;

	for (ptr = mvc_pg.source; ptr < (mvc_pg.source + mvc_pg.pt); ptr++)
	if (*ptr == '\n')
		counter++;

	return counter;
}


void MVCError(MVC_LEX_T mvc_lex, MVC_S_ADDR mvc_pg, const char *format, ...)
{
	va_list list;
	fprintf(stderr, "baris %u: ", MVCLineCounter(mvc_lex, mvc_pg));

	va_start(list, format);
	vfprintf(stderr, format, list);
	va_end(list);

	fprintf(stderr, "\n");


	BaikGarbageCollection();

	exit(1);
}




// ///////////////////////////////////////////////////////
