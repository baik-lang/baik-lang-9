// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

int getlex( void );
void ungetlex( void );
char GetChar( void );
int lex_ident( void );
int lex_const( void );
int lex_string( void );

int checkFloat( void );
int lex_double( void );

double strtodbl(char *c);

int lex_array( void );

void getArrayName(char str[MAX_STRING_LEN],char retVal[MAX_STRING_LEN]);
void getArrayIdx(char str[MAX_STRING_LEN], char retVal[MAX_STRING_LEN]);

int checkArray( void );
int checkDummyArray( char buf[MAX_STRING_LEN] );

int checkObject( void );
int checkObjectFunc( void );

int lex_object( void );
int lex_object_func( void );
char *getObjectName(char str[MAX_STRING_LEN]);
char *getObjectParam(char str[MAX_STRING_LEN]);
char *getObjectFunction(char str[MAX_STRING_LEN]);
char *getObjectFunctionParam(char str[MAX_STRING_LEN]);

void checkInstanceValidation(char object_str[MAX_STRING_LEN]);
void checkObjectValidation(char object_str[MAX_STRING_LEN]);
void checkObjectFuncValidation(char object_str[MAX_STRING_LEN]);

int LineCounter( void );
void Error( const char *format, ... );

VAL_LABEL expression( void  );
VAL_LABEL AndOr( void  );
VAL_LABEL NotFunc( void  );
VAL_LABEL Compare( void  );
VAL_LABEL AddSub( void  );
VAL_LABEL MultiDiv( void  );
VAL_LABEL Factor( void );

void ReadSource( int firstTime );
void Interpreter( void );

//int expression( void );
//int AndOr( void );
//int NotFunc( void );
//int Compare( void );
//int AddSub( void );
//int MulDiv( void );
//int Factor( void );

