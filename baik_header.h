// ---------------------------------------------------------------------
//  
// BAIK (Bahasa Anak Indonesia untuk Komputer) versi 9.4
// Object Oriented Programming Language
//
// BAIK ver.9.4 Ready for Professional Web, Desktop and Cloud Computing
// Haris Script Language : Multi Platform Version
//
// Copyright Haris Hasanudin (2017/2/11)
// ---------------------------------------------------------------------


int LineCounter( void );
void Error( const char *format, ... );

#ifdef WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4244)

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#include "regex.h"
#include <direct.h>

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <fcntl.h>
#include <regex.h>

#include <unistd.h>
#include <sys/param.h>

#include <arpa/inet.h>
#include <sys/select.h>
//#include "ux_pingbody.h"

#include <dirent.h>

extern DIR *owndir;

#endif




/* ********************* */
// ///////////////////////////////////
// MYSQL Header
// ///////////////////////////////////
//#include <mysql.h>
//#include "my_common.h"

// ///////////////////////////////////
// PGSQL Header
// ///////////////////////////////////
//#include <libpq-fe.h>
//#include "pq_common.h"

// ///////////////////////////////////
// ORACLE Header
// ///////////////////////////////////
//#include "ocilib.h"
//#include "oracle_common.h"

// ///////////////////////////////////
// SQLITE Header
// ///////////////////////////////////
//#include "sqlite3.h"
//#include "sqlite_common.h"


#include "baik_word.h"
#include "baik_struct.h"

#include "val_label.h"

extern BAIK_LEX lex;  
extern BAIK_ADDR pg;  

extern BAIK_ADDR tmp_pg; 

#include "baik_lexer.h"
#include "haris_node_struct.h"
#include "baik.h"

#include "haris_node_vector.h"
#include "baik_lexer_body.h"

#ifndef S_SPLINT_S
#include "multiplatform_struct.h"
#include "multiplatform.h"
#endif

// ---------------------------------------------------------------------

void showBaikVersion() {
	fprintf(stderr, "BAIK (Bahasa Anak Indonesia untuk Komputer) versi 9.4\n");
	fprintf(stderr, "Optimized for Web and GPIO robot controlling\n");
	fprintf(stderr, "Copyright Haris Hasanudin 2005-2017\n\n");
	fprintf(stderr, "cara pakai: baik [-v|-h ] <source file>\n");
	fprintf(stderr, "-v : lihat versi\n");
	fprintf(stderr, "-h : lihat cara pakai\n");
	exit(0);
}

