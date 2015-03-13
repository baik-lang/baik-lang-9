// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

int last_pt_ident;
char last_ident[MAX_STRING_LEN];

int getlex( void )
{
  char c='\0';
  int  i=0;
  int  j=0;
  int  k=0;

  if( lex.type == _EOF )
    return FALSE;

  pg.back_pt = pg.pt;

  c= GetChar();
  memset( &lex, 0, sizeof(BAIK_LEX) );

  if(c == '\n' || c == '\r') 
    return FALSE;

  // printf("lex c=%c \n", c);  

  if( isdigit( c ) ) {
   i = checkFloat();

   if(i == 1){
     // printf("float\n");
     return( lex_double() );
   } else {
     // printf("not float\n");
     return( lex_const() );
   }
  }
  else
  if( c == 0x22 ) {
    return( lex_string() );
  } 
  else
  if( isalpha( c ) || c == '_' ) {
     i = checkArray();
	 //printf("check array: %d\n", i);

   if(i == 1){
     return( lex_array() );
   } else {
     j = checkObject();
     if(j == 1){
       k = checkObjectFunc();
       if(k == 1){
         // Object Function
         return( lex_object_func() );
       } else {
         // Object Param
         return( lex_object() );
       }
     } else {
	   last_pt_ident = pg.pt;
       return( lex_ident() );
     }
   }

  }
  else
  if( c == '\0' ){
    lex.type = _EOF;
    return FALSE;
  }
  else
  {
    lex.type = TYPE_SYM;
    lex.detail.symbol = c;
    pg.pt++;
    pos_source++;
  }  
  return FALSE;
}


void ungetlex( void )
{
  pg.pt = pg.back_pt;
}


char GetChar( void )
{
  char c='\0';

  char b_c='\0';
  int  i = 0, bk_pt = 0;

  // get back ident
  memset(&last_ident, '\0', sizeof(last_ident) );

  if(last_pt_ident < pg.pt) {
	bk_pt = last_pt_ident;

	i=0;
	do {
      b_c = pg.source[bk_pt];
	  last_ident[i] = b_c;
      bk_pt++; i++;
	} while( !isspace( b_c ) && b_c != '\0' );
	last_ident[i] = '\0';
	   
	//printf("pt ident back %s\n", last_ident);

  }

  // get current char
  do{
    c = pg.source[pg.pt++];
    pos_source++;  

    /* Skip Comment */
    if( c == '#' )
      do{ 
        c = pg.source[pg.pt++]; 
        pos_source++;  

      }while( c != '\0' && c != '\n' && c != '\r' );

  }while( isspace( c ) && c != '\0' );

  pg.pt--;
  pos_source--;

  return c;
}

int lex_const( void )
{
  char c;
  int num = 0;

  while( isdigit( c = pg.source[pg.pt++] ) ) {
    num = num * 10 + (int)(c - '0');
    pos_source++;
  }
  
  lex.detail.num = num;
  
  pg.pt--;
  pos_source--;

  lex.type = TYPE_NUM;
  
  return FALSE;
}

int lex_double( void )
{
  char c; 
  int  i = 0;

  memset( &lex, 0, sizeof(BAIK_LEX) );

  do{
    c = pg.source[pg.pt++];

    // printf("%d %d \n", pg.pt, pg.back_pt);
    pos_source++; 

    if( c == '\0' ) {
        break;
    }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
        break;
    }

    if( i > (MAX_STRING_LEN - 1) )
      Error("melebihi kapasitas MAX_STRING_LEN");
    
    lex.detail.string[i++] = (char)c;

  }while( !isspace( c ) && c != '\0' &&  c != ',' &&  c != '(' &&  c != ')'
           &&  c != '{' &&  c != '}' &&  c != ';' );

  if(lex.detail.string[i-1] == ',' ||
     lex.detail.string[i-1] == '(' ||
     lex.detail.string[i-1] == ')' ||
     lex.detail.string[i-1] == '{' ||
     lex.detail.string[i-1] == '}' ||
     lex.detail.string[i-1] == ';' ) {

       lex.detail.string[i-1] = '\0';
  } 

  pg.pt--;
  
  lex.detail.string[i] = '\0';

  /* printf("double str %s \n", lex.detail.string); */

  lex.detail.dblnum = strtodbl(lex.detail.string);

  /* printf("double %f \n", lex.detail.dblnum); */

  lex.type = TYPE_DBL;


  return FALSE;
}

double strtodbl(char *c)
{

  int digit, expo, state, intsign, expsign, exppos, intpos;
  double integral, decimal, declen, num;
     
  num = 0;                /*Final Result*/
  state = INTEGRAL;       /*Check if real of integral part     */
  digit = 0;
  integral = 0;           /*Integral Part*/
  decimal = 0;            /*Real Part*/
  declen = 0;             /*Length of number after decimal*/
  expo = 0;
  intsign = POSITIVE;     /*Flag for storing sign of number*/
  expsign = POSITIVE;     /*Flag for storing sign of exponent*/
  exppos = START;         /*Check current position of exponent as start point or not*/
  intpos = START;         /*Check current position of number as start point or not*/

    // printf("strdbl start\n");
    while(*c != '\0' && *c != ' ' && *c != '\n')
    {
        if(*c == '.') 
            if(state == INTEGRAL)
               /*The string is now the real part*/
                state = DECIMAL;                      
            else
            /*Invalid Input. More than one decimal point or decimal point 
              in exponent.
            */
                    Error("strtodbl: invalid input");
                       
        else if(*c == 'e' || *c == 'E')
            state = EXPONENT;
        else if(*c >= '0' && *c <= '9')
        {
               digit = *c -'0';
            if(state == INTEGRAL)
               {
                /*Calculate Integral Part */
                integral = integral*10 + digit;
                /*Not the starting point of the number*/
                    intpos = NOTSTART;
               }
            else if(state == DECIMAL)
            {
                    /*Calculate Real Part*/
                decimal = decimal*10 + digit;
                ++declen;
                    intpos = NOTSTART;
            }
            else if(state == EXPONENT)
               {
                 /*Calculate the Exponent Part if any*/
                expo = expo*10 + digit ;
                    exppos = NOTSTART;
               }
        }
          else if(*c == '-')
          {
            /*Check is number is negative.*/
               if (state == INTEGRAL && intpos == START && intsign != NEGATIVE)
                    intsign = NEGATIVE;
               else if(state == DECIMAL && integral == 0 && intpos == START && intsign != NEGATIVE)
                    intsign = NEGATIVE;
               /*-----------------------------*/
               
               /*check if exponent is negative*/
               else if(state == EXPONENT && exppos == START && expsign != NEGATIVE)
                    expsign = NEGATIVE;
               /*----------------------------*/
               else
                    Error("strtodbl: no state");
          }
        else if(!isdigit(*c))
        /*Input contains an invalid character*/
               Error("strtodbl: not digit");
          /*Next character*/
        ++c;
    }
     
     num = integral + decimal/pow(10,declen);
     /*Make changes is number or exponent is negative*/
     if (intsign == NEGATIVE)
          num = -num;
     if (expsign == NEGATIVE)
          expo = - expo;
     
     num = num*pow(10,expo);

    //printf("strdbl end\n");
    return num;
} 

// =============================================================================
// Function for Array
// =============================================================================
int lex_array( void )
{
  char allarray[MAX_STRING_LEN];
  char c; 
  int  i = 0;
  int  pp = 0;

  memset( allarray, '\0', sizeof(allarray) );

  do{
    c = pg.source[pg.pt++];

    /* printf("%d %d \n", pg.pt, pg.back_pt); */
    pos_source++; 

    if( c == '\0' ) {
        break;
    }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
        break;
    }


    if( i > (MAX_STRING_LEN - 1) )
      Error("melebihi kapasitas MAX_STRING_LEN");
    
    lex.detail.array_str[i++] = (char)c;

	pp = i;

    //printf("lex i-2 : %c  ,  ", lex.detail.array_str[pp-2]);
    //printf("lex i-1 : %c  ,  ", lex.detail.array_str[pp-1]);
    //printf("lex i : %c\n", lex.detail.array_str[pp]);

  if(lex.detail.array_str[pp-2] == ']' && lex.detail.array_str[pp-1] == '+')
	  break;
  if(lex.detail.array_str[pp-2] == ']' && lex.detail.array_str[pp-1] == '-')
	  break;

  }while( !isspace( c ) && c != '=' && c != ',' && c != '\0' &&  c != '(' &&  c != ')'
          &&  c != '{' &&  c != '}' &&  c != ';'  
		  );



  if(lex.detail.array_str[i-1] == ',' ||
     lex.detail.array_str[i-1] == '(' ||
     lex.detail.array_str[i-1] == ')' ||
     lex.detail.array_str[i-1] == '=' ||
     lex.detail.array_str[i-1] == '{' ||
     lex.detail.array_str[i-1] == '}' ||
     lex.detail.array_str[i-1] == ';'  
	 ) {
       lex.detail.array_str[i-1] = '\0';
  } 

  if(lex.detail.array_str[pp-2] == ']' && lex.detail.array_str[pp-1] == '+') {
       lex.detail.array_str[i-1] = '\0';
  }

  if(lex.detail.array_str[pp-2] == ']' && lex.detail.array_str[pp-1] == '-') {
       lex.detail.array_str[i-1] = '\0';
  }

  pg.pt--;
  pos_source--;
  
  lex.detail.array_str[i] = '\0';
  strcpy(allarray, lex.detail.array_str);

  // printf("arr str %s \n", allarray);

  lex.type = TYPE_ARRAY;

  return FALSE;
}

void getArrayName(char str[MAX_STRING_LEN], char retVal[MAX_STRING_LEN]) {
  char myname[MAX_STRING_LEN];

  int i=0, n=0;

  do {
   myname[i] = str[i];
   i++;
  } while (str[i] != '[' && str[i] != '\0');

  myname[i] = '\0';

  strcpy(retVal, myname);
  // printf("inside arry name: %s\n", myname); 

}

void getArrayIdx(char str[MAX_STRING_LEN], char retVal[MAX_STRING_LEN]) {
  char myidx[MAX_STRING_LEN];

  int i=0, n=0;

  do {
   i++;
  } while (str[i] != '[' && str[i] != '\0');

  n = 0; i++;
  do {
   myidx[n] = str[i];
   i++;n++;
  } while (str[i] != ']' && str[i] != '\0');

  myidx[n] = '\0';
  
  strcpy(retVal, myidx);
  // printf("inside arry idx %s\n", myidx);

}

// =============================================================================

int checkArray( void )
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
    c = pg.source[pg.pt++];
    //printf("%c", c);

    n++;

    if(c == '[') {
      posKiri = pg.pt;
      numKiri++;
    } 
    else if(c == ']') {
      posKanan = pg.pt;
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
    pg.pt--;

  /* printf("pg after %d\n", pg.pt); */

  return isArray;
}

int checkDummyArray( char buf[MAX_STRING_LEN] )
{
  char c='\0';
  int  pos = 0;
  int  isDummy = 0;
  int  n = 0;
  int  posKiri = 0, posKanan = 0;
  int  numKiri = 0, numKanan = 0;

  /* printf("pg before %d\n", pg.pt); */

  do{
    c = buf[pos++];
    n++;

    if(c == '[') {
      posKiri = pos;
      numKiri++;
    } 
    else if(c == ']') {
      posKanan = pos;
      numKanan++;
    }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
        break;
    }

  }while( !isspace( c ) && c != '=' && c != '\0' );

  if(numKiri == 1 && numKanan == 1 && ((posKiri + 1) == posKanan) ) {
    isDummy = 1;
  }

  /* printf("isDummy %d\n", isArray); */

  return isDummy;
}

// =============================================================================
// Function for Object
// =============================================================================

int lex_object( void )
{
  char allobject[MAX_STRING_LEN];

  char c = '\0'; 
  int  i = 0;

  memset( &allobject[0], '\0', sizeof(allobject) );
  memset( &lex.detail.object_str[0], '\0', sizeof(lex.detail.object_str) );


  do{
    c = pg.source[pg.pt++];

    /* printf("%d %d \n", pg.pt, pg.back_pt); */
    pos_source++; 

    if( c == '\0' ) {
        break;
    }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
        break;
    }

    if( i > (MAX_STRING_LEN - 1) )
      Error("melebihi kapasitas MAX_STRING_LEN");
    
    lex.detail.object_str[i++] = (char)c;

  }while( !isspace( c ) && c != '=' && c != ',' && c != '\0' &&  c != '(' &&  c != ')'
          &&  c != '{' &&  c != '}' &&  c != ';' );

  if(lex.detail.object_str[i-1] == ',' ||
     lex.detail.object_str[i-1] == '(' ||
     lex.detail.object_str[i-1] == ')' ||
     lex.detail.object_str[i-1] == '=' ||
     lex.detail.object_str[i-1] == '{' ||
     lex.detail.object_str[i-1] == '}' ||
     lex.detail.object_str[i-1] == ' ' ||
     lex.detail.object_str[i-1] == ';' ) {

       lex.detail.object_str[i-1] = '\0';
  } 

  pg.pt--;
  
  lex.detail.object_str[i] = '\0';
  strcpy(allobject, lex.detail.object_str);

  // printf("lex_obj str : %s , len %d\n", allobject, strlen(allobject)); 

  lex.type = TYPE_OBJECT;


  return FALSE;
}

int lex_object_func( void )
{
  char allobjectfunc[MAX_STRING_LEN];

  char c = '\0'; 
  int  i = 0;

  memset( &lex.detail.object_str, '\0', sizeof(lex.detail.object_str) );

  memset( &allobjectfunc, '\0', sizeof(allobjectfunc) );

  do{
    c = pg.source[pg.pt++];

    /* printf("%d %d \n", pg.pt, pg.back_pt); */
    pos_source++; 

    if( c == '\0' ) {
        break;
    }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
        break;
    }

    if( i > (MAX_STRING_LEN - 1) )
      Error("melebihi kapasitas MAX_STRING_LEN");
    
    lex.detail.object_str[i++] = (char)c;

  }while( !isspace( c ) && c != '=' && c != '\0'
          &&  c != '{' &&  c != '}' &&  c != ';' );

  if(lex.detail.object_str[i-1] == '=' ||
     lex.detail.object_str[i-1] == '{' ||
     lex.detail.object_str[i-1] == '}' ||
     lex.detail.object_str[i-1] == ' ' ||
     lex.detail.object_str[i-1] == ';' ) {

       lex.detail.object_str[i-1] = '\0';
  } 


  pg.pt--;
  
  lex.detail.object_str[i] = '\0';
  strcpy(allobjectfunc, lex.detail.object_str);

  // printf("lex_obj str : %s ok\n", allobjectfunc); 


  lex.type = TYPE_OBJECT_FUNC;


  return FALSE;
}

char *getObjectName(char str[MAX_STRING_LEN]) {
  char name[MAX_STRING_LEN];
  char *ret;
  int i=0;

  ret = NULL;
  memset(&name,'\0',sizeof(name));

  do {
   name[i] = str[i];
   i++;
  } while (str[i] != '-' && str[i] != '\0');

  name[i] = '\0';

  ret = name;

  strcat(name, "");
  // printf("inside getObjectName %s\n", name);

  return ret;
}

char *getObjectParam(char str[MAX_STRING_LEN]) {
  char name[MAX_STRING_LEN];
  char *ret;
  int i=0, n=0;

  ret = NULL;
  memset(&name,'\0',sizeof(name));

  do {
   // do nothing
   i++;
  } while (str[i] != '-' && str[i] != '\0');

  i++; i++; // skip -> sign

  n = 0;
  do {
   name[n] = str[i];
   i++; n++;
  } while (str[i] != '\0');

  name[n] = '\0';

  ret = name;

  strcat(name, "");
  //printf("inside getObjectParam %s\n", name);

  return ret;
}

char *getObjectFunction(char str[MAX_STRING_LEN]) {
  char name[MAX_STRING_LEN];
  char *ret;
  int i=0, n=0;

  ret = NULL;
  memset(&name,'\0',sizeof(name));

  do {
   // do nothing
   i++;
  } while (str[i] != '-' && str[i] != '\0');

  i++; i++; // skip -> sign

  n = 0;
  do {
   name[n] = str[i];
   i++; n++;
  } while (str[i] != '(');

  name[n] = '\0';

  ret = name;

  strcat(name, "");
  // printf("inside getObjectParam %s\n", name);

  return ret;
}

char *getObjectFunctionParam(char str[MAX_STRING_LEN]) {
  char name[MAX_STRING_LEN];
  char *ret;
  int i=0, n=0;

  ret = NULL;
  memset(&name,'\0',sizeof(name));

  // printf("get str : %s\n", str);

  do {
   // do nothing
   i++;
  } while (str[i] != '-' && str[i] != '\0');

  i++; i++; // skip -> sign

  do {
   i++;
  } while (str[i] != '(');

  i++;      // skip (

  if(str[i++] == ')' ) {
    strcpy(name, "");

  } else {
    i--;

    n = 0;
    do {
     name[n] = str[i];
     i++; n++;
    } while (str[i] != ')');

    name[n] = '\0';

  }

  ret = name;

  strcat(name, "");
  // printf("p n:%s\n", name);

  return ret;
}

// =============================================================================

int checkObject( void )
{
  char c='\0';
  int  isObj = 0;
  int  i,n = 0;
  int  posKiri = 0, posKanan = 0;
  int  numKiri = 0, numKanan = 0;

  /* printf("pg before %d\n", pg.pt); */

  do{
    c = pg.source[pg.pt++];
    n++;

    if(c == '-') {
      posKiri = pg.pt;
      numKiri++;
    } 
    else if(c == '>') {
      posKanan = pg.pt;
      numKanan++;
    }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
        break;
    }

  }while( !isspace( c ) && c != '=' && c != '\0' );

  if(numKiri == 1 && numKanan == 1 && (posKanan == (posKiri + 1)) ) {
    isObj = 1;
  }

  // printf("isObj %d\n", isObj);

  for(i=0; i<n; i++)
    pg.pt--;

  /* printf("pg after %d\n", pg.pt); */

  return isObj;
}

int checkObjectFunc( void )
{
  char c='\0';
  int  isObjFunc = 0;
  int  i = 0, n = 0;
  int  posKiri = 0, posKanan = 0;
  int  numKiri = 0, numKanan = 0;
  int  posKiri2 = 0, posKanan2 = 0;
  int  numKiri2 = 0, numKanan2 = 0;

  /* printf("pg before %d\n", pg.pt); */

  do{
    c = pg.source[pg.pt++];
    n++;

    if(c == '-') {
      posKiri = pg.pt;
      numKiri++;
    } 
    else if(c == '>') {
      posKanan = pg.pt;
      numKanan++;
    }
    else if(c == '(') {
      posKiri2 = pg.pt;
      numKiri2++;
    }
    else if(c == ')') {
      posKanan2 = pg.pt;
      numKanan2++;
    }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
        break;
    }

  }while( !isspace( c ) && c != '=' && c != '\0' );

  if(numKiri == 1 && numKanan == 1 && (posKanan == (posKiri + 1)) && 
     numKiri2 == 1 && numKanan2 == 1 && posKiri2 < posKanan2) {
     isObjFunc = 1;
  }

  // printf("isObjFunc %d\n", isObjFunc);

  for(i=0; i<n; i++)
    pg.pt--;

  /* printf("pg after %d\n", pg.pt); */

  return isObjFunc;
}


// =============================================================================

int lex_string( void )
{
  char c = 0x51;  /* 0x22(double quotation) */
  int i = 0;

  memset( &lex, 0, sizeof(BAIK_LEX) );
  
  pg.pt++;
  pos_source++;
  

  while( (c = pg.source[pg.pt++]) != 0x22 )
  {
    // printf("%d %d \n", pg.pt, pg.back_pt);
    pos_source++; 

    if( c == '\0' ) {
        break;
    	//Error("String without double quotation");
    }

    if( c == '\r' || c == '\n' || c == '\b' || c == '\f' || c == '\t' ) {
      continue;
    }

    if( c == '\\' ){

      c = pg.source[pg.pt++];
      pos_source++;

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
      Error("melebihi kapasitas MAX_STRING_LEN");
    
    lex.detail.string[i++] = (char)c;

  }
  
//  printf("%s \n", lex.detail.string);

  lex.detail.string[i] = '\0';
  lex.type = TYPE_STR;

  if(lex.detail.string == '\0' || lex.detail.string[0] == '\0'
     || strlen(lex.detail.string) <= 0) {
        strcpy(lex.detail.string , "");
  }

  return FALSE;
}



int checkFloat( void )
{
  char c='\0';
  int  isFloat = 0;
  int  i = 0,n = 0;

  /* printf("pg before %d\n", pg.pt); */

  do{
    c = pg.source[pg.pt++];
    n++;

    if(c == '.')
      isFloat = 1;

  }while( !isspace( c ) && c != '\0' );

  for(i=0; i<n; i++)
    pg.pt--;

  /* printf("pg after %d\n", pg.pt); */

  return isFloat;
}

// ////////////////////////////////////////////////////////////////
/* ****************************************************** */
/* Copyright Haris Hasanudin 2005-2015                    */
/* ****************************************************** */
/* Kupersembahkan untuk istriku tercinta Masako,          */
/* anakku tersayang Takumi dan Tomoki                     */
/* serta seluruh putra putri Indonesia                    */
/* ****************************************************** */

void checkInstanceValidation(char object_str[MAX_STRING_LEN]) {
    char dat_a[MAX_STRING_LEN],
         dat_b[MAX_STRING_LEN],
         tmpMsg[MAX_STRING_LEN];

    VAL_LABEL tmpdat, tmpdat2;
    struct node_list tmpnode;

    memset(&tmpdat, '\0', sizeof(tmpdat));
    memset(&tmpdat2, '\0', sizeof(tmpdat2));
    memset(&tmpnode, '\0', sizeof(tmpnode));
    memset(&dat_a, '\0', sizeof(dat_a));
    memset(&dat_b, '\0', sizeof(dat_b));
    memset(&tmpMsg, '\0', sizeof(tmpMsg));

    // object name
    strcpy(dat_a, getObjectName(object_str) );
    // object param
    strcpy(dat_b, getObjectParam(object_str) );
        
    /*
    printf("For TREE object str : %s , len %d\n",ident, strlen(ident));
    /*
    printf("For Check obj name: %s\n",dat_a);
    printf("For Check obj param: %s len %d\n",dat_b, strlen(dat_b));
    */

    // Check if object-name is already definited as BENDA
    tmpdat = ValLabel( dat_a, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
    if(strlen(tmpdat.ident) > 0 && tmpdat.datatype == 31) {  // Class Instance
        // this is instance
        // Check if param is already definited as member of Object
        tmpdat2 = ValLabel( tmpdat.benda_name, sub_deep, tmpdat2, VAL_FLAG_SEARCH_R );
        if(strlen(tmpdat2.ident) > 0 && tmpdat2.datatype == 30) {  // Class Definition
          // do nothing
        } else {
          sprintf(tmpMsg,"Tidak ada definisi %s sebagai BENDA", tmpdat.benda_name);
          Error(tmpMsg);
        }
            
    } else {
        // sprintf(tmpMsg,"%s belum terdefinisikan sebagai instans BENDA", lex.detail.object_name);
        // Error(tmpMsg);
    }

}


void checkObjectValidation(char object_str[MAX_STRING_LEN]) {
    char dat_a[MAX_STRING_LEN],
         dat_b[MAX_STRING_LEN],
         tmpMsg[MAX_STRING_LEN];

    int i=0;
    VAL_LABEL tmpdat, tmpdat2;
    struct node_list tmpnode;

    memset(&tmpdat, '\0', sizeof(tmpdat));
    memset(&tmpdat2, '\0', sizeof(tmpdat2));
    memset(&tmpnode, '\0', sizeof(tmpnode));
    memset(&dat_a, '\0', sizeof(dat_a));
    memset(&dat_b, '\0', sizeof(dat_b));
    memset(&tmpMsg, '\0', sizeof(tmpMsg));

    // object name
    strcpy(dat_a, getObjectName(object_str) );
    // object param
    strcpy(dat_b, getObjectParam(object_str) );
        
    /*
    printf("For TREE object str : %s , len %d\n",ident, strlen(ident));
    /*
    printf("For Check obj name: %s\n",dat_a);
    printf("For Check obj param: %s len %d\n",dat_b, strlen(dat_b));
    */

    // Check if object-name is already definited as BENDA
    tmpdat = ValLabel( dat_a, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
    if(strlen(tmpdat.ident) > 0 && tmpdat.datatype == 31) {  // Class Instance
        /*
        printf("obj in tree\n");
        printf("obj orig ident: %s\n", tmpdat.orig_ident);
        printf("obj datatype: %d Class Instance\n", tmpdat.datatype);
        printf("obj refer def : %s\n", tmpdat.benda_name);
        */

        // Check if param is already definited as member of Object
        tmpdat2 = ValLabel( tmpdat.benda_name, sub_deep, tmpdat2, VAL_FLAG_SEARCH_R );
        if(strlen(tmpdat2.ident) > 0 && tmpdat2.datatype == 30) {  // Class Definition
          /*
          printf("obj DEF in tree\n");
          printf("obj DEF orig ident: %s\n", tmpdat2.orig_ident);
          printf("obj DEF datatype: %d Class Definition\n", tmpdat2.datatype);

          i = node_getCount();
          printf("Total Param num : %d\n", i);

          tmpnode = node_getElement(2);
          printf("get Param 2 (obj) : %s\n", tmpnode.class_name);
          printf("get Param 2 (name) : %s\n",tmpnode.param_name);

          printf("For search Param (obj) : %s\n", tmpdat.benda_name);
          printf("For search Param (name) : %s\n",dat_b);
          */

          strcpy(tmpnode.class_name , tmpdat.benda_name);
          strcpy(tmpnode.param_name , dat_b);
          tmpnode.member_type = 1;                       // as parameter

          i = node_findData(tmpnode);

          if(i >= 0) {
            // printf("parameter found\n");
          } else {
            sprintf(tmpMsg,"Tidak ada parameter %s pada %s", dat_b, tmpdat.benda_name);
            Error(tmpMsg);
          }

          // Check if param scope
          tmpnode = node_getElement(i);
          if(tmpnode.scope ==1) {
            sprintf(tmpMsg,"%s : cakupan lokal, tidak bisa direferensi dari luar.", dat_b);
            Error(tmpMsg);
          }

        } else {
          sprintf(tmpMsg,"Tidak ada definisi %s sebagai BENDA", tmpdat.benda_name);
          Error(tmpMsg);
        }
            
    } else {
        sprintf(tmpMsg,"%s belum terdefinisikan sebagai instans BENDA", lex.detail.object_name);
        Error(tmpMsg);
    }

}

void checkObjectFuncValidation(char object_str[MAX_STRING_LEN]) {
    char dat_a[MAX_STRING_LEN],
         dat_b[MAX_STRING_LEN],
         tmpMsg[MAX_STRING_LEN];

    int i=0;
    VAL_LABEL tmpdat, tmpdat2;
    struct node_list tmpnode;

    // printf("checkObjectFuncValidation\n");

    memset(&tmpdat, '\0', sizeof(tmpdat));
    memset(&tmpdat2, '\0', sizeof(tmpdat2));
    memset(&tmpnode, '\0', sizeof(tmpnode));
    memset(&dat_a, '\0', sizeof(dat_a));
    memset(&dat_b, '\0', sizeof(dat_b));
    memset(&tmpMsg, '\0', sizeof(tmpMsg));

    // printf("For Check obj : %s\n",object_str);

    // object name
    strcpy(dat_a, getObjectName(object_str) );

    // object function
    strcpy(dat_b, getObjectFunction(object_str) );
        
    
    // printf("For Check obj name: %s\n",dat_a);
    // printf("For Check obj function: %s len %d\n",dat_b, strlen(dat_b));
    
    // Check if object-name is already definited as BENDA
    tmpdat = ValLabel( dat_a, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
    if(strlen(tmpdat.ident) > 0 && tmpdat.datatype == 31) {  // Class Instance
        /*
        printf("obj in tree\n");
        printf("obj orig ident: %s\n", tmpdat.orig_ident);
        printf("obj datatype: %d Class Instance\n", tmpdat.datatype);
        printf("obj refer def : %s\n", tmpdat.benda_name);
        */

        // Check if param is already definited as member of Object
        tmpdat2 = ValLabel( tmpdat.benda_name, sub_deep, tmpdat2, VAL_FLAG_SEARCH_R );
        if(strlen(tmpdat2.ident) > 0 && tmpdat2.datatype == 30) {  // Class Definition
          /*
          printf("obj DEF in tree\n");
          printf("obj DEF orig ident: %s\n", tmpdat2.orig_ident);
          printf("obj DEF datatype: %d Class Definition\n", tmpdat2.datatype);

          i = node_getCount();
          printf("Total Param num : %d\n", i);

          tmpnode = node_getElement(7);
          printf("get Func 2 (obj) : %s\n", tmpnode.class_name);
          printf("get Func 2 (name) : %s\n",tmpnode.function_name);

          printf("For search Func (obj) : %s\n", tmpdat.benda_name);
          printf("For search Func (name) : %s\n",dat_b);
          */

          strcpy(tmpnode.class_name , tmpdat.benda_name);
          if(strcmp(dat_b,"awalan")==0 ||
             strcmp(dat_b,"Awalan")==0 ||
             strcmp(dat_b,"AWALAN")==0 ) {
            strcpy(tmpnode.function_name , tmpdat.benda_name);
          } else {
            strcpy(tmpnode.function_name , dat_b);
          }
          tmpnode.member_type = 2;                       // as function

          i = node_findData(tmpnode);

          if(i >= 0) {
            // printf("function found\n");
          } else {
            sprintf(tmpMsg,"Tidak ada fungsi %s pada %s", dat_b, tmpdat.benda_name);
            Error(tmpMsg);
          }

          // Check if param scope
          /*
          tmpnode = node_getElement(i);
          if(tmpnode.scope ==1) {
            sprintf(tmpMsg,"%s : cakupan lokal, tidak bisa direferensi dari luar.", dat_b);
            Error(tmpMsg);
          }
          */

        } else {
          sprintf(tmpMsg,"Tidak ada definisi %s sebagai BENDA", tmpdat.benda_name);
          Error(tmpMsg);
        }
            
    } else {
        sprintf(tmpMsg,"%s belum terdefinisikan sebagai instans BENDA", lex.detail.object_name);
        Error(tmpMsg);
    }

}
