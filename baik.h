// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2016
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// Last 2016/2/11

// -----------------------------------------------------
// Stack for Lang Word
int funcEnum = 0;
#include "stack_funcword_struct.h"
#include "stack_funcword.h"
#include "funcword_refer.h"

// -----------------------------------------------------

extern VAL_LABEL *pstartVAR, *pendVAR;
extern VAL_LABEL *glptrVAR;

double strtodbl(char *c);


// =====================================================

// -----------------------------------------------------
// Stack for Array String
#include "stack_str_struct.h"
#include "stack_str.h"

STR_ARRY TmpStrBox;
STR_ARRY TmpStrBox2;
int      strarryPos=0;

STR_ARRY mysql_TmpStrBox;
int      mysql_strarryPos = 0;

int      mysql_renban = 0;

// -----------------------------------------------------
// Stack for Array Int
#include "stack_int_struct.h"
#include "stack_int.h"

INT_ARRY TmpIntBox;
INT_ARRY TmpIntBox2;
int intarryPos=0;

// -----------------------------------------------------
// Stack for Array Dbl
#include "stack_dbl_struct.h"
#include "stack_dbl.h"

DBL_ARRY TmpDblBox;
DBL_ARRY TmpDblBox2;
int dblarryPos=0;
// -----------------------------------------------------
long createRenban(int mynum);
int renban=0;

#ifdef USE_GTK2
// -----------------------------------------------------
// Stack for Array GUI Widget
#include "stack_gui_struct.h"
#include "stack_gui.h"

GUI_ARRY TmpGuiBox;
GUI_ARRY TmpGuiBox2;
int guiarryPos=0;
// -----------------------------------------------------
#endif

#ifdef USE_GTK3
// -----------------------------------------------------
// Stack for Array GUI Widget
#include "stack_gui_struct.h"
#include "stack_gui.h"

GUI_ARRY TmpGuiBox;
GUI_ARRY TmpGuiBox2;
int guiarryPos=0;
// -----------------------------------------------------
#endif


// =====================================================
/* TRUE FALSE definition*/

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* STRING TO DOUBLE     */
#define DECIMAL         0
#define INTEGRAL        1
#define EXPONENT        2

#define     NEGATIVE     0
#define     POSITIVE     1

#define     NOTSTART     0
#define     START        1
/* ********************* */

extern void init_rnd(unsigned long x);

VAL_LABEL returnVal;

extern VAL_LABEL expression( void );
extern VAL_LABEL AndOr( void );
extern VAL_LABEL NotFunc( void );
extern VAL_LABEL Compare( void );
extern VAL_LABEL AddSub( void );
extern VAL_LABEL MultiDiv( void );
extern VAL_LABELFactor( void );

extern void BAIK_funcword( void );

extern void IncludeCodeReader( void );
extern void ReadSource( int firstTime );
extern void Interpreter( void );

char** split(const char *str, const char *delim);
void split_free(char **arr);

// ------------------------------------------------------------------
int pos_source=0;                  // current parsing pos
char *tmp_source;
char *tmp_source_class;       // tmp source for obj
char *tmp_source_lyr;         // tmp source for lyr

extern char *tmp_source_lyr_gmb;     // tmp source for lyr gmb
extern char *tmp_source_timer;       // tmp source for lyr timer

char *tmp_for_source;         // temp src for FOR operation
char *tmp_condit_source;      // temp src for FOR condit operation

// ------------------------------------------------------------------
#define MAX_SUB_DEPTH              128
int sub_deep = 0;                  // Sub depth for Recursion
int posSub[MAX_SUB_DEPTH];         // pos for sub routine

int isLyrSub=0;
int isTimerSub=0;

char currentSub[MAX_STRING_LEN];   // current Sub name for Error

// ------------------------------------------------------------------
char currentClass[MAX_STRING_LEN];       // current Class for Object Oriented

#define MAX_CLASS_SUB_DEPTH              128
int class_sub_deep = 0;                  // Sub depth for Recursion
int posClassSub[MAX_CLASS_SUB_DEPTH];    // pos for sub routine

int posClassTemp;
int backClassTemp;

extern int lex_ident( void );
extern char last_ident[MAX_STRING_LEN];

// ..............................................................

char** split(const char *str, const char *delim);
void split_free(char **arr);

char* createTime(void);  /* international version */
char* createTime2(void); /* indonesian version    */

int dayofweek(int year,int month,int day);
char *getDay();          /* international version */
char *getDay2();         /* indonesian version    */

char *createFilename(void);
void writeLog(char msg[MAX_STRING_LEN]);

#ifdef USE_CGI
extern char *web_inputstring;
#endif

#ifdef USE_WEBSTYLE
extern void style_removeAll(void);
#endif

void BaikGarbageCollection(void);

void chop(char* input)
{
    int i;
    
    for(i=0; input[i]!='\r' && input[i]!='\n'; i++){
        //do nothing
    }
    input[i]='\0';
}

long createRenban(int mynum)
{
	time_t present_tm;
	struct tm *my_time = NULL;
	char *now_time = NULL;

	int yy, mm, dd, hh, min, sec;
	char year[8], month[4], day[4], hour[4], minut[4], secon[16];
	char num[4];

	char mytime[22]; // yyyymmddhhmmss+renban
	char filename[11];
	char filename2[11];

	long myrenban = 0;

	//printf("inside createRenban... %d <BR>\n", mynum);

	memset(&year, '\0', sizeof(year));
	memset(&month, '\0', sizeof(month));
	memset(&day, '\0', sizeof(day));
	memset(&hour, '\0', sizeof(hour));
	memset(&minut, '\0', sizeof(minut));
	memset(&secon, '\0', sizeof(secon));
	memset(&num, '\0', sizeof(num));

	memset(&filename, '\0', sizeof(filename));
	memset(&filename2, '\0', sizeof(filename2));

	//printf("inside createRenban...stp2 %d <BR>\n", mynum);

#ifdef WIN32
	_snprintf(num, sizeof(num), "%d", mynum);
#else
	snprintf(num, sizeof(num), "%d", mynum);
#endif

	//printf("inside createRenban...stp3 %d <BR>\n", mynum);

	if (strlen(num) < 2) {
#ifdef WIN32
		_snprintf(num, sizeof(num), "0%d", mynum);
#else
		snprintf(num, sizeof(num), "0%d", mynum);
#endif
	}
	else {
#ifdef WIN32
		_snprintf(num, sizeof(num), "%d", mynum);
#else
		snprintf(num, sizeof(num), "%d", mynum);
#endif
	}

	mynum = 0;
	//printf("inside createRenban...stp4 %d <BR>\n", mynum);

	time(&present_tm);
	my_time = localtime(&present_tm);
	now_time = asctime(my_time);

	yy = my_time->tm_year + 1900;
	mm = my_time->tm_mon + 1;
	dd = my_time->tm_mday;

	hh = my_time->tm_hour;
	min = my_time->tm_min;
	sec = my_time->tm_sec;

#ifdef WIN32
#ifndef S_SPLINT_S
	_snprintf(year, sizeof(year), "%d", yy);
#else
	snprintf(year, sizeof(year), "%d", yy);
#endif
#else
	snprintf(year, sizeof(year), "%d", yy);
#endif

#ifdef WIN32
#ifndef S_SPLINT_S
	_snprintf(month, sizeof(month), "%d", mm);
#else
	snprintf(month, sizeof(month), "%d", mm);
#endif
#else
	snprintf(month, sizeof(month), "%d", mm);
#endif

#ifdef WIN32
#ifndef S_SPLINT_S
	_snprintf(day, sizeof(day), "%d", dd);
#else
	snprintf(day, sizeof(day), "%d", dd);
#endif
#else
	snprintf(day, sizeof(day), "%d", dd);
#endif


#ifdef WIN32
#ifndef S_SPLINT_S
	_snprintf(hour, sizeof(hour), "%d", hh);
#else
	snprintf(hour, sizeof(hour), "%d", hh);
#endif
#else
	snprintf(hour, sizeof(hour), "%d", hh);
#endif

#ifdef WIN32
#ifndef S_SPLINT_S
	_snprintf(minut, sizeof(minut), "%d", min);
#else
	snprintf(minut, sizeof(minut), "%d", min);
#endif
#else
	snprintf(minut, sizeof(minut), "%d", min);
#endif

#ifdef WIN32
#ifndef S_SPLINT_S
	_snprintf(secon, sizeof(secon), "%d", sec);
#else
	snprintf(secon, sizeof(secon), "%d", sec);
#endif
#else
	snprintf(secon, sizeof(secon), "%d", sec);
#endif

	memset(&mytime, '\0', sizeof(mytime));
	strcpy(mytime, year);

	if (strlen(month) < 2) {
		if (strlen(day) < 2) {
#ifdef WIN32
#ifndef S_SPLINT_S
			_snprintf(filename, sizeof(filename), "%s0%s0%s", year, month, day);
#else
			snprintf(filename, sizeof(filename), "%s0%s0%s", year, month, day);
#endif
#else
			snprintf(filename, sizeof(filename), "%s0%s0%s", year, month, day);
#endif
		}
		else {
#ifdef WIN32
#ifndef S_SPLINT_S
			_snprintf(filename, sizeof(filename), "%s0%s%s", year, month, day);
#else
			snprintf(filename, sizeof(filename), "%s0%s%s", year, month, day);
#endif
#else
			snprintf(filename, sizeof(filename), "%s0%s%s", year, month, day);
#endif
		}
	}
	else {
		if (strlen(day) < 2) {
#ifdef WIN32
#ifndef S_SPLINT_S
			_snprintf(filename, sizeof(filename), "%s%s0%s", year, month, day);
#else
			snprintf(filename, sizeof(filename), "%s%s0%s", year, month, day);
#endif
#else
			snprintf(filename, sizeof(filename), "%s%s0%s", year, month, day);
#endif
		}
		else {
#ifdef WIN32
#ifndef S_SPLINT_S
			_snprintf(filename, sizeof(filename), "%s%s%s", year, month, day);
#else
			snprintf(filename, sizeof(filename), "%s%s%s", year, month, day);
#endif
#else
			snprintf(filename, sizeof(filename), "%s%s%s", year, month, day);
#endif
		}
	}

	if (strlen(hour) < 2) {
		if (strlen(minut) < 2) {
			if (strlen(secon) < 2) {
#ifdef WIN32
#ifndef S_SPLINT_S
				_snprintf(filename2, sizeof(filename2), "0%s0%s0%s", hour, minut, secon);
#else
				snprintf(filename2, sizeof(filename2), "0%s0%s0%s", hour, minut, secon);
#endif
#else
				snprintf(filename2, sizeof(filename2), "0%s0%s0%s", hour, minut, secon);
#endif
			}
			else {
#ifdef WIN32
#ifndef S_SPLINT_S
				_snprintf(filename2, sizeof(filename2), "0%s0%s%s", hour, minut, secon);
#else
				snprintf(filename2, sizeof(filename2), "0%s0%s%s", hour, minut, secon);
#endif
#else
				snprintf(filename2, sizeof(filename2), "0%s0%s%s", hour, minut, secon);
#endif
			}
		}
		else {
			if (strlen(day) < 2) {
#ifdef WIN32
#ifndef S_SPLINT_S
				_snprintf(filename2, sizeof(filename2), "0%s%s0%s", hour, minut, secon);
#else
				snprintf(filename2, sizeof(filename2), "0%s%s0%s", hour, minut, secon);
#endif
#else
				snprintf(filename2, sizeof(filename2), "0%s%s0%s", hour, minut, secon);
#endif
			}
			else {
#ifdef WIN32
#ifndef S_SPLINT_S
				_snprintf(filename2, sizeof(filename2), "0%s%s%s", hour, minut, secon);
#else
				snprintf(filename2, sizeof(filename2), "0%s%s%s", hour, minut, secon);
#endif
#else
				snprintf(filename2, sizeof(filename2), "0%s%s%s", hour, minut, secon);
#endif
			}
		}
	}
	else {
		if (strlen(minut) < 2) {
			if (strlen(secon) < 2) {
#ifdef WIN32
#ifndef S_SPLINT_S
				_snprintf(filename2, sizeof(filename2), "%s0%s0%s", hour, minut, secon);
#else
				snprintf(filename2, sizeof(filename2), "%s0%s0%s", hour, minut, secon);
#endif
#else
				snprintf(filename2, sizeof(filename2), "%s0%s0%s", hour, minut, secon);
#endif
			}
			else {
#ifdef WIN32
#ifndef S_SPLINT_S
				_snprintf(filename2, sizeof(filename2), "%s0%s%s", hour, minut, secon);
#else
				snprintf(filename2, sizeof(filename2), "%s0%s%s", hour, minut, secon);
#endif
#else
				snprintf(filename2, sizeof(filename2), "%s0%s%s", hour, minut, secon);
#endif
			}
		}
		else {
			if (strlen(day) < 2) {
#ifdef WIN32
#ifndef S_SPLINT_S
				_snprintf(filename2, sizeof(filename2), "%s%s0%s", hour, minut, secon);
#else
				snprintf(filename2, sizeof(filename2), "%s%s0%s", hour, minut, secon);
#endif
#else
				snprintf(filename2, sizeof(filename2), "%s%s0%s", hour, minut, secon);
#endif
			}
			else {
#ifdef WIN32
#ifndef S_SPLINT_S
				_snprintf(filename2, sizeof(filename2), "%s%s%s", hour, minut, secon);
#else
				snprintf(filename2, sizeof(filename2), "%s%s%s", hour, minut, secon);
#endif
#else
				snprintf(filename2, sizeof(filename2), "%s%s%s", hour, minut, secon);
#endif
			}
		}
	}

#ifdef WIN32
#ifndef S_SPLINT_S
	_snprintf(mytime, sizeof(mytime), "%s%s", filename2, num);
#else
	snprintf(mytime, sizeof(mytime), "%s%s", filename2, num);
#endif
#else
	snprintf(mytime, sizeof(mytime), "%s%s", filename2, num);
#endif

	//printf("inside renban %s <BR>\n", mytime);

	myrenban = atol(mytime);
	//printf("myrenban %d\n", myrenban);

	return myrenban;
}


char* source_join(const char* a, const char* b)
{

    size_t la = strlen(a);
    size_t lb = strlen(b);
    char* p = malloc(la + lb + 1);
    memcpy(p, a, la);
    memcpy(p + la, b, lb + 1);
    
    return p;
 }
                        



/* ----------------------------------------------------------- */
/* Create time based on the current date */
/* ----------------------------------------------------------- */
char* createTime()
{
  time_t present_tm;
  struct tm *my_time=NULL;
  char *now_time=NULL;

  int yy, mm, dd, hh, min, sec;
  char year[8], month[4], day[4], hour[4], minut[4], secon[16];

  char mytime[22]; // yyyy-mm-dd hh:mm:ss
  char filename[11];
  char filename2[11];
  char *mt=NULL;

  memset(&year, '\0', sizeof(year));
  memset(&month, '\0', sizeof(month));
  memset(&day, '\0', sizeof(day));
  memset(&hour, '\0', sizeof(hour));
  memset(&minut, '\0', sizeof(minut));
  memset(&secon, '\0', sizeof(secon));


  mt = NULL;
  time(&present_tm);
  my_time = localtime(&present_tm);
  now_time = asctime(my_time);

  yy = my_time->tm_year + 1900;
  mm = my_time->tm_mon + 1;
  dd = my_time->tm_mday;

  hh  = my_time->tm_hour;
  min = my_time->tm_min;
  sec = my_time->tm_sec;

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(year, sizeof(year),"%d", yy);
    #else
    snprintf(year, sizeof(year),"%d", yy);
    #endif
  #else
  snprintf(year, sizeof(year),"%d", yy);
  #endif

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(month, sizeof(month),"%d", mm);
    #else
    snprintf(month, sizeof(month),"%d", mm);
    #endif
  #else
  snprintf(month, sizeof(month),"%d", mm);
  #endif

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(day, sizeof(day),"%d", dd);
    #else
    snprintf(day, sizeof(day),"%d", dd);
    #endif
  #else
  snprintf(day, sizeof(day),"%d", dd);
  #endif


  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(hour, sizeof(hour),"%d", hh);
    #else
    snprintf(hour, sizeof(hour),"%d", hh);
    #endif
  #else
  snprintf(hour, sizeof(hour),"%d", hh);
  #endif

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(minut, sizeof(minut),"%d", min);
    #else
    snprintf(minut, sizeof(minut),"%d", min);
    #endif
  #else
  snprintf(minut, sizeof(minut),"%d", min);
  #endif

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(secon, sizeof(secon),"%d", sec);
    #else
    snprintf(secon, sizeof(secon),"%d", sec);
    #endif
  #else
  snprintf(secon, sizeof(secon),"%d", sec);
  #endif

  memset(&mytime[0], '\0', sizeof(mytime));
  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(mytime, sizeof(mytime),"%s-",year);
    #else
    snprintf(mytime, sizeof(mytime),"%s-",year);
    #endif
  #else
  snprintf(mytime, sizeof(mytime),"%s-",year);
  #endif

  if( strlen(month) < 2) {
     if( strlen(day) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s-0%s-0%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s-0%s-0%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s-0%s-0%s", year, month, day);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s-0%s-%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s-0%s-%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s-0%s-%s", year, month, day);
       #endif
     }
  } else {
     if( strlen(day) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s-%s-0%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s-%s-0%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s-%s-0%s", year, month, day);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s-%s-%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s-%s-%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s-%s-%s", year, month, day);
       #endif
     }
  }


  if( strlen(hour) < 2) {
   if( strlen(minut) < 2) {
     if( strlen(secon) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"0%s:0%s:0%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"0%s:0%s:0%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"0%s:0%s:0%s", hour, minut, secon);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"0%s:0%s:%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"0%s:0%s:%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"0%s:0%s:%s", hour, minut, secon);
       #endif
     }
   } else {
     if( strlen(secon) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"0%s:%s:0%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"0%s:%s:0%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"0%s:%s:0%s", hour, minut, secon);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"0%s:%s:%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"0%s:%s:%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"0%s:%s:%s", hour, minut, secon);
       #endif
     }
   }
  } else {
   if( strlen(minut) < 2) {
     if( strlen(secon) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"%s:0%s:0%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"%s:0%s:0%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"%s:0%s:0%s", hour, minut, secon);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"%s:0%s:%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"%s:0%s:%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"%s:0%s:%s", hour, minut, secon);
       #endif
     }
   } else {
     if( strlen(secon) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"%s:%s:0%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"%s:%s:0%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"%s:%s:0%s", hour, minut, secon);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"%s:%s:%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"%s:%s:%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"%s:%s:%s", hour, minut, secon);
       #endif
     }
   }
  }

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(mytime, sizeof(mytime),"%s %s", filename, filename2);
    #else
    snprintf(mytime, sizeof(mytime),"%s %s", filename, filename2);
    #endif
  #else
  snprintf(mytime, sizeof(mytime),"%s %s", filename, filename2);
  #endif

  mt = mytime;

  // if(isDEBUG == 1)   printf("mytime tot = %s\n", mt);

  return mt;
}

/* indonesian version of time expression */
char* createTime2()
{
  time_t present_tm;
  struct tm *my_time=NULL;
  char *now_time=NULL;

  int yy, mm, dd, hh, min, sec;
  char year[8], month[4], day[4], hour[4], minut[4], secon[16];

  char mytime[22]; // dd-mm-yyyy hh:mm:ss
                   // hari-bulan-tahun
  char filename[11];
  char filename2[11];
  char *mt=NULL;

  memset(&year, '\0', sizeof(year));
  memset(&month, '\0', sizeof(month));
  memset(&day, '\0', sizeof(day));
  memset(&hour, '\0', sizeof(hour));
  memset(&minut, '\0', sizeof(minut));
  memset(&secon, '\0', sizeof(secon));


  mt = NULL;
  time(&present_tm);
  my_time = localtime(&present_tm);
  now_time = asctime(my_time);

  yy = my_time->tm_year + 1900;
  mm = my_time->tm_mon + 1;
  dd = my_time->tm_mday;

  hh  = my_time->tm_hour;
  min = my_time->tm_min;
  sec = my_time->tm_sec;

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(year, sizeof(year),"%d", yy);
    #else
    snprintf(year, sizeof(year),"%d", yy);
    #endif
  #else
  snprintf(year, sizeof(year),"%d", yy);
  #endif

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(month, sizeof(month),"%d", mm);
    #else
    snprintf(month, sizeof(month),"%d", mm);
    #endif
  #else
  snprintf(month, sizeof(month),"%d", mm);
  #endif

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(day, sizeof(day),"%d", dd);
    #else
    snprintf(day, sizeof(day),"%d", dd);
    #endif
  #else
  snprintf(day, sizeof(day),"%d", dd);
  #endif


  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(hour, sizeof(hour),"%d", hh);
    #else
    snprintf(hour, sizeof(hour),"%d", hh);
    #endif
  #else
  snprintf(hour, sizeof(hour),"%d", hh);
  #endif

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(minut, sizeof(minut),"%d", min);
    #else
    snprintf(minut, sizeof(minut),"%d", min);
    #endif
  #else
  snprintf(minut, sizeof(minut),"%d", min);
  #endif

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(secon, sizeof(secon),"%d", sec);
    #else
    snprintf(secon, sizeof(secon),"%d", sec);
    #endif
  #else
  snprintf(secon, sizeof(secon),"%d", sec);
  #endif

  memset(&mytime[0], '\0', sizeof(mytime));
  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(mytime, sizeof(mytime),"%s-",year);
    #else
    snprintf(mytime, sizeof(mytime),"%s-",year);
    #endif
  #else
  snprintf(mytime, sizeof(mytime),"%s-",year);
  #endif

  if( strlen(month) < 2) {
     if( strlen(day) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s-0%s-0%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s-0%s-0%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s-0%s-0%s", year, month, day);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s-0%s-%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s-0%s-%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s-0%s-%s", year, month, day);
       #endif
     }
  } else {
     if( strlen(day) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s-%s-0%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s-%s-0%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s-%s-0%s", year, month, day);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s-%s-%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s-%s-%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s-%s-%s", year, month, day);
       #endif
     }
  }

  if( strlen(hour) < 2) {
   if( strlen(minut) < 2) {
     if( strlen(secon) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"0%s:0%s:0%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"0%s:0%s:0%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"0%s:0%s:0%s", hour, minut, secon);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"0%s:0%s:%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"0%s:0%s:%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"0%s:0%s:%s", hour, minut, secon);
       #endif
     }
   } else {
     if( strlen(secon) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"0%s:%s:0%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"0%s:%s:0%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"0%s:%s:0%s", hour, minut, secon);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"0%s:%s:%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"0%s:%s:%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"0%s:%s:%s", hour, minut, secon);
       #endif
     }
   }
  } else {
   if( strlen(minut) < 2) {
     if( strlen(secon) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"%s:0%s:0%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"%s:0%s:0%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"%s:0%s:0%s", hour, minut, secon);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"%s:0%s:%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"%s:0%s:%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"%s:0%s:%s", hour, minut, secon);
       #endif
     }
   } else {
     if( strlen(secon) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"%s:%s:0%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"%s:%s:0%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"%s:%s:0%s", hour, minut, secon);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename2, sizeof(filename2),"%s:%s:%s", hour, minut, secon);
         #else
         snprintf(filename2, sizeof(filename2),"%s:%s:%s", hour, minut, secon);
         #endif
       #else
       snprintf(filename2, sizeof(filename2),"%s:%s:%s", hour, minut, secon);
       #endif
     }
   }
  }

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(mytime, sizeof(mytime),"%s %s", filename, filename2);
    #else
    snprintf(mytime, sizeof(mytime),"%s %s", filename, filename2);
    #endif
  #else
  snprintf(mytime, sizeof(mytime),"%s %s", filename, filename2);
  #endif

  mt = mytime;

  // if(isDEBUG == 1)   printf("mytime tot = %s\n", mt);

  return mt;
}

/* day name calculation    */
/* 0:sunday ... 6:saturday */
int dayofweek(int year,int month,int day)
{
        if(month <= 2){
                year--;
                month += 12;
        }
        
        return (year + (year / 4) - (year / 100) + (year / 400) +
                                ((13 * month + 8) / 5) + day) % 7;
}

char* getDay()
{
  time_t present_tm;
  struct tm *my_time=NULL;
  char *now_time=NULL;

  int yy, mm, dd;

  int day;
  char myday[22];

  char *mt=NULL;

  mt = NULL;
  time(&present_tm);
  my_time = localtime(&present_tm);
  now_time = asctime(my_time);

  yy = my_time->tm_year + 1900;
  mm = my_time->tm_mon + 1;
  dd = my_time->tm_mday;

  memset(&myday,'\0',sizeof(myday));

  day = dayofweek(yy,mm,dd);

  if(day == 0) {
    strcpy(myday, "sunday");
  } else if(day == 1) {
    strcpy(myday, "monday");
  } else if(day == 2) {
    strcpy(myday, "tuesday");
  } else if(day == 3) {
    strcpy(myday, "wednesday");
  } else if(day == 4) {
    strcpy(myday, "thursday");
  } else if(day == 5) {
    strcpy(myday, "friday");
  } else if(day == 6) {
    strcpy(myday, "saturday");
  } else {
    strcpy(myday, "Nil");
  }

  mt = myday;

  return mt;
}

/* indonesian version of time expression */
char* getDay2()
{
  time_t present_tm;
  struct tm *my_time=NULL;
  char *now_time=NULL;

  int yy=0, mm=0, dd=0, hh=0, min=0, sec=0;

  int day;
  char myday[22];
  char myday2[22];

  char *mt=NULL;

  mt = NULL;
  time(&present_tm);
  my_time = localtime(&present_tm);
  now_time = asctime(my_time);

  yy = my_time->tm_year + 1900;
  mm = my_time->tm_mon + 1;
  dd = my_time->tm_mday;

  hh  = my_time->tm_hour;
  min = my_time->tm_min;
  sec = my_time->tm_sec;

  memset(&myday,'\0',sizeof(myday));
  memset(&myday2,'\0',sizeof(myday2));

  day = dayofweek(yy,mm,dd);

  if(day == 0) {
    strcpy(myday, "minggu");
  } else if(day == 1) {
    strcpy(myday, "senin");
  } else if(day == 2) {
    strcpy(myday, "selasa");
  } else if(day == 3) {
    strcpy(myday, "rabu");
  } else if(day == 4) {
    strcpy(myday, "kamis");
  } else if(day == 5) {
    strcpy(myday, "jumat");
  } else if(day == 6) {
    strcpy(myday, "sabtu");
  } else {
    strcpy(myday, "Nil");
  }

  strcpy(myday2, myday);

  mt = myday;

  return mt;
}

void writeLog(char msg[MAX_STRING_LEN]) {
  FILE *fp=NULL;
  char filename[11];
  char mytime[22];
  char logMsg[MAX_STRING_LEN];

  memset(&filename, '\0', sizeof(filename));
  memset(&mytime, '\0', sizeof(mytime));
  memset(&logMsg, '\0', sizeof(logMsg));

  // printf("writeLog : memset OK\n");

  strcpy(filename , createFilename());                          // yyyymmdd
  strcpy(mytime , createTime());                                // yyyy-mm-dd hh:min:sec

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(logMsg, sizeof(logMsg),"%s %s", mytime, msg);
    #else
    snprintf(logMsg, sizeof(logMsg),"%s %s", mytime, msg);
    #endif
  #else
  snprintf(logMsg, sizeof(logMsg),"%s %s", mytime, msg);
  #endif

  // printf("file log %s \n", filename);
  // printf("log %s \n", logMsg);

  if(filename == '\0') {
    printf("memory tidak cukup ! \n");
    strcpy(filename , "yyyymmdd.log");
  } else {
    // if(isDEBUG == 1) printf("filename : %s\n", filename);
 
    fp = fopen(filename, "a");
    if(fp == NULL) {
       printf("Salah: Tidak bisa tulis ke File\n");
	} else {
	   // printf("writeLog : file open OK\n");
	}

    if ( EOF == fprintf(fp, "%s \n", logMsg) )
      printf("Salah: Tidak bisa tulis ke File\n");

	fflush(fp);
	// printf("writeLog : file flush OK\n");

    fclose(fp);
	// printf("writeLog : file close OK\n");

    memset(&filename, '\0', sizeof(filename));
    memset(&mytime, '\0', sizeof(mytime));
    memset(&logMsg, '\0', sizeof(logMsg));

  }
}

/* Create filename based on the current date */
char *createFilename()
{
  time_t present_tm;
  struct tm *my_time=NULL;
  char *now_time=NULL;

  int yy=0, mm=0, dd=0;
  char year[8], month[4], day[4];
  char filename[11];
  char *f=NULL;

  memset(&year, '\0', sizeof(year));
  memset(&month, '\0', sizeof(month));
  memset(&day, '\0', sizeof(day));

  time(&present_tm);
  my_time = localtime(&present_tm);
  now_time = asctime(my_time);

  yy = my_time->tm_year + 1900;
  mm = my_time->tm_mon + 1;
  dd = my_time->tm_mday;


  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(year, sizeof(year),"%d", yy);
    #else
    snprintf(year, sizeof(year),"%d", yy);
    #endif
  #else
  snprintf(year, sizeof(year),"%d", yy);
  #endif

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(month, sizeof(month),"%d", mm);
    #else
    snprintf(month, sizeof(month),"%d", mm);
    #endif
  #else
  snprintf(month, sizeof(month),"%d", mm);
  #endif

  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(day, sizeof(day),"%d", dd);
    #else
    snprintf(day, sizeof(day),"%d", dd);
    #endif
  #else
  snprintf(day, sizeof(day),"%d", dd);
  #endif

  memset(&filename, '\0', sizeof(filename));
  #ifdef WIN32
    #ifndef S_SPLINT_S
    sprintf_s(filename, sizeof(filename),"%s%s%s", year, month, day);
    #else
    snprintf(filename, sizeof(filename),"%s%s%s", year, month, day);
    #endif
  #else
  snprintf(filename, sizeof(filename),"%s%s%s", year, month, day);
  #endif

  if( strlen(month) < 2) {
     if( strlen(day) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s0%s0%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s0%s0%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s0%s0%s", year, month, day);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s0%s%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s0%s%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s0%s%s", year, month, day);
       #endif
     }
  } else {
     if( strlen(day) < 2) {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s%s0%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s%s0%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s%s0%s", year, month, day);
       #endif
     } else {
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(filename, sizeof(filename),"%s%s%s", year, month, day);
         #else
         snprintf(filename, sizeof(filename),"%s%s%s", year, month, day);
         #endif
       #else
       snprintf(filename, sizeof(filename),"%s%s%s", year, month, day);
       #endif
     }
  }



  f = filename;

  // if(isDEBUG == 1) printf("f tot = %s\n", f);

  return f;
}



/* --------------------------------------------------------
 * Error Function
 -------------------------------------------------------- */

int LineCounter( void )
{
  char *myptr = NULL;
  int counter = 1;

  for(myptr = pg.source; myptr < (pg.source + pg.pt); myptr++ )
    if( *myptr == '\n' )
      counter++;

  if(strlen(currentSub) > 0) {
    counter = counter - posSub[sub_deep];
  }

  return counter;
}

void Error( const char *format, ... )
{
  va_list list;
  char msg[256];

  memset(&msg, '\0', sizeof(msg));
  if(strlen(currentSub) > 0) {
    #ifdef WINDOWS
    sprintf_s(msg, sizeof(msg), "Dalam Sub %s: Salah di sekitar baris %u: ", currentSub, LineCounter());
    MessageBox(NULL, msg, "Kesalahan pada Program BAIK!", 0);
    #else
    fprintf( stderr, "Dalam Sub %s: Salah di sekitar baris %u: ", currentSub, LineCounter() );
	fprintf( stderr, "posisi pada atau sebelum: %s %s\n", last_ident, lex.detail.ident);
    #endif
  } else {
    #ifdef WINDOWS
    sprintf_s(msg, sizeof(msg), "Program Utama : Salah di sekitar baris %u \n", LineCounter());
    MessageBox(NULL, msg, "Kesalahan pada Program BAIK!", 0);
    #else
    fprintf( stderr, "Program Utama : Salah di sekitar baris %u \n", LineCounter() );
	fprintf( stderr, "posisi pada atau sebelum: %s %s\n", last_ident, lex.detail.ident);
    #endif
  }
  
  va_start( list, format );
  vfprintf( stderr, format, list );
  va_end( list );
  
  fprintf( stderr, "\n");

  BaikGarbageCollection();

  exit(0);
}



int checkParamNum(char get_param[MAX_STRING_LEN], char orig_param[MAX_STRING_LEN]) {
  int getNum = 0, origNum = 0;

   int i = 0;
   char **get,
        **orig;

   // printf("check num get: %s\n", get_param);
   // printf("check num orig: %s\n", orig_param);

   get = NULL;
   orig = NULL;

   get = split(get_param, ",");

   if(get != NULL) {
     i=0;
     while(get[i] != NULL && strlen(get[i]) > 0) {
       i++;
       getNum++;
     }
   }

   orig = split(orig_param, ",");

   if(orig != NULL) {
     i=0;
     while(orig[i] != NULL && strlen(orig[i]) > 0) {
       i++;
       origNum++;
     }
   }

   if(get != NULL)
     split_free(get);
   if(orig != NULL)
     split_free(orig);

   // printf("origNum %d \n", origNum);

   get = NULL;
   orig = NULL;   

   if(getNum == origNum)
     return 0;
   else
     return -1;

}

void subtituteParam(char tmp_param[MAX_STRING_LEN*2], char get_param[MAX_STRING_LEN], char orig_param[MAX_STRING_LEN]) {
  char ret[MAX_STRING_LEN * 2];
  char tmp[MAX_STRING_LEN];

   int i=0;
   char **get,
        **orig;

   memset(&ret, '\0', sizeof(ret));
   memset(&tmp, '\0', sizeof(tmp));

   get = NULL;
   orig = NULL;

   get = split(get_param, ",");
   orig = split(orig_param, ",");

   // printf("substitut get-> %s\n", get_param);
   // printf("substitut orig-> %s\n", orig_param);

   strcpy(ret, "{ ");

   if(get != NULL) {
     i=0;
     while(get[i] != NULL && strlen(get[i]) > 0) {
       memset(&tmp, '\0', sizeof(tmp));
       #ifdef WIN32
         #ifndef S_SPLINT_S
         sprintf_s(tmp, sizeof(tmp),"%s = %s ", orig[i] ,get[i]);
         #else
         snprintf(tmp, sizeof(tmp),"%s = %s ", orig[i] ,get[i]);
         #endif
       #else
       snprintf(tmp, sizeof(tmp),"%s = %s ", orig[i] ,get[i]);
       #endif

       // printf("substitut i=%d %s = %s \n", i, orig[i] ,get[i]);

       strcat(ret, tmp);

       i++;
     }

   }

   #ifdef S_SPLINT_S
   if(get != NULL)
     free(get);
   if(orig != NULL)
     free(orig);
   #endif
   split_free(get);
   split_free(orig);

   strcat(ret, " }");

   strcpy(tmp_param, ret);

}


// split case sensitive ! do not change 2010-09-18
char** split(const char *str, const char *delim)
{
	char **arr = '\0'; 
	int    n   = 0;    
	char *buf=NULL, *tp=NULL;

	if (str == '\0' || delim == '\0') {
		return '\0';
	}

	buf = (char*)malloc(strlen(str) + 1);
	if (buf == '\0') {
		return '\0';
	}
        strcpy(buf, str);

	for(tp = strtok(buf, delim); tp; tp = strtok('\0', delim)) {
		char **a = (char**)realloc(arr, sizeof(*arr) * (n+3));
		if (a == '\0') {
			free(arr);
			free(buf);    // a must
			return '\0';
		}
		a[++n] = tp;
		arr = a;
	}

	if (arr != '\0') {
		arr[0] = buf;
		arr++;
		arr[n] = '\0';
	} else {
          free ( buf );  // a must
        }

	return arr;
}

void split_free(char **arr)
{
	if (arr != '\0') {
		arr--;

		free(arr[0]);
		free(arr);
	}
}

void BaikGarbageCollection(void) {
  VAL_LABEL tmpdat;

  // clear all param in MAV
  memset(&tmpdat, '\0', sizeof(tmpdat));
  ValLabel( "", 0, tmpdat, VAL_FLAG_END );



  // clear node param in Object Operation
  node_removeAll();

  // clear array
  int_removeAll();
  stackInt_removeAll();
  dbl_removeAll();
  stackDbl_removeAll();
  string_removeAll();
  stackStr_removeAll();

  #ifdef USE_CGI
  if(web_inputstring != NULL ) {
     free(web_inputstring);
  }
  #endif

  #ifdef USE_WEBSTYLE
  style_removeAll();
  #endif

  // clear source
  free( pg.source );
  free( tmp_pg.source );

  exit(0);

}

void BaikInit(void) {
  renban = 1;
  tmp_source = NULL;
  tmp_source_class = NULL;
  tmp_source_lyr = NULL;
  tmp_source_lyr_gmb = NULL;
  tmp_source_timer = NULL;
  tmp_for_source = NULL;
  tmp_condit_source = NULL;

  pstartVAR = NULL;
  pendVAR   = NULL;
  glptrVAR  = NULL;

  memset(&returnVal, 0, sizeof(returnVal));
  returnVal.pnext = NULL;
  returnVal.left = NULL;
  returnVal.right = NULL;
  returnVal.long_str = NULL;
  returnVal.filedata = NULL;
  returnVal.filename = NULL;
  #ifdef USE_GTK2
  returnVal.widget = NULL;
  returnVal.eventbox = NULL;
  returnVal.font_desc = NULL;
  returnVal.liststore = NULL;
  returnVal.completion = NULL;
  returnVal.buffer = NULL;
  returnVal.treestore = NULL;
  returnVal.treecolumn = NULL;
  returnVal.clipboard = NULL;
  returnVal.renderer = NULL;
  returnVal.str2 = NULL;
  returnVal.pixmap = NULL;
  #endif
#ifdef USE_GTK3
  returnVal.widget = NULL;
  returnVal.eventbox = NULL;
  returnVal.font_desc = NULL;
  returnVal.liststore = NULL;
  returnVal.completion = NULL;
  returnVal.buffer = NULL;
  returnVal.treestore = NULL;
  returnVal.treecolumn = NULL;
  returnVal.clipboard = NULL;
  returnVal.renderer = NULL;
  returnVal.str2 = NULL;
#endif
}

// ///////////////////////////////////////////////////////////////////////////


// Software BAIK ini dilindungi Hak Cipta dan Undang-Undang //////////////////

