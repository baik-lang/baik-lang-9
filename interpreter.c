// //////////////////////////////////////////////////////////////////////
// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2016
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
// //////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/stat.h>

#include "baik_word.h"
#include "baik_struct.h"
#include "val_label.h"
#include "baik_lexer.h"

#ifndef S_SPLINT_S
#include "multiplatform_struct.h"
#endif

#include "stack_funcword_struct.h"
extern int funcEnum;
extern void save_funcword(char funcname[MAX_IDENT_LEN], char alias[MAX_IDENT_LEN]);

extern BAIK_LEX lex;
extern BAIK_ADDR pg;

extern BAIK_ADDR tmp_pg;

extern char last_ident[MAX_STRING_LEN];

void Interpreter( void );
extern void BaikGarbageCollection(void);

extern void InterpreterSub( int endSub, char subName[MAX_STRING_LEN] );
extern void InterpreterParam( int progType, int endSub, char subName[MAX_STRING_LEN] );

extern void InterpreterLyrSub( int endSub, char subName[MAX_STRING_LEN] );
extern void InterpreterLyrParam( int progType, int endSub, char subName[MAX_STRING_LEN] );

extern int InterpreterTimerSub( int endSub, char subName[MAX_STRING_LEN] );

extern void subtituteParam(char tmp_param[MAX_STRING_LEN*2],char get_param[MAX_STRING_LEN], char orig_param[MAX_STRING_LEN]);
extern int checkParamNum(char get_param[MAX_STRING_LEN], char orig_param[MAX_STRING_LEN]);
extern char** split(const char *str, const char *delim);
extern void split_free(char **arr);

#define MAX_SUB_DEPTH              64

extern int sub_deep;
extern int isLyrSub;
extern int isTimerSub;

extern int posSub[MAX_SUB_DEPTH]; 

extern VAL_LABEL get_Minus_Val(void);

/* array max length               */
#define MAX_ARRAY          999999000

int isDoArray = 0;
int DoArrayIdx = -1;
char DoArrayName[MAX_STRING_LEN];

extern VAL_LABEL returnVal;

extern char *tmp_source;
extern char *tmp_source_class;
extern char *tmp_source_lyr;
char *tmp_source_lyr_gmb;
char *tmp_source_timer;

extern char *tmp_for_source;
extern char *tmp_condit_source;

char *inc_tmp_source;
int  inc_pt;
int  inc_back_pt;

FILE *inc_fp;
char incname[MAX_STRING_LEN];

#ifdef WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4047)

extern char** win_dir_content(const char *path);

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

#include <dirent.h>

DIR *owndir;

#endif

char **dirtp;

extern char currentClass[MAX_STRING_LEN];   // current Class for Object Oriented

extern VAL_LABEL interpretIndexParam(char source[MAX_STRING_LEN], int tmp_pt, int back_pt, char currentClass[MAX_STRING_LEN]);

// --------------------------------------
// Stack for Array String
#include "stack_str_struct.h"

extern STR_ARRY TmpStrBox;
extern STR_ARRY TmpStrBox2;
extern int      strarryPos;

extern int      renban;

// Feb 11, 2016
extern STR_ARRY mysql_TmpStrBox;
extern int      mysql_strarryPos;

extern int      mysql_renban;

extern long createRenban(int mynum);
// --------------------------------------

// --------------------------------------
// Stack for Array Int
#include "stack_int_struct.h"

extern INT_ARRY TmpIntBox;
extern INT_ARRY TmpIntBox2;
extern int intarryPos;
// --------------------------------------
// Stack for Array Dbl
#include "stack_dbl_struct.h"

extern DBL_ARRY TmpDblBox;
extern DBL_ARRY TmpDblBox2;
extern int dblarryPos;
// --------------------------------------

#ifdef USE_GTK2
// --------------------------------------
// Stack for Array Gui Widget
#include "stack_gui_struct.h"

extern GUI_ARRY TmpGuiBox;
extern GUI_ARRY TmpGuiBox2;
extern int guiarryPos;

extern GtkPrintSettings *BAIK_PRINT_settings;
// --------------------------------------
#endif

#ifdef USE_GTK3

#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>

// --------------------------------------
// Stack for Array Gui Widget
#include "stack_gui_struct.h"

extern GUI_ARRY TmpGuiBox;
extern GUI_ARRY TmpGuiBox2;
extern int guiarryPos;

extern GtkPrintSettings *BAIK_PRINT_settings;
// --------------------------------------
#endif

// ..............................................................
int if_deep  =   0;
#define MAX_IF   10
int currKalauResult[MAX_IF];

// ..............................................................
#define MAX_LOOP_LEN     1024
int loop_flag    =   0;

void InterpreterForInitIncr(void);
void InterpreterForIncr( int endPos );
int interpretForCondition(char *src, int tmp_pt, int back_pt);

int posForStart[MAX_LOOP_LEN];
int backForStart[MAX_LOOP_LEN];
int posForTemp[MAX_LOOP_LEN];
int backForTemp[MAX_LOOP_LEN];
int statFor[MAX_LOOP_LEN];

// ..............................................................
int forExecDone[MAX_LOOP_LEN];     // 0->notyet , 1->done */
int f_deep=0;                      // loop to check untuk depth */
char forInitSource[MAX_LOOP_LEN][MAX_STRING_LEN],
     forConditSource[MAX_LOOP_LEN][MAX_STRING_LEN],
     forPlusSource[MAX_LOOP_LEN][MAX_STRING_LEN];

// ..............................................................

int while_flag   =   0;
int w_deep       =   0;
int interpretWhileCondition(char *src, int tmp_pt, int back_pt);
void InterpreterWhileIncr( int endPos );

int posWhile[MAX_LOOP_LEN];
int backWhile[MAX_LOOP_LEN];
int statWhile[MAX_LOOP_LEN];

int posWhileStart[MAX_LOOP_LEN];
int backWhileStart[MAX_LOOP_LEN];
int posWhileTemp[MAX_LOOP_LEN];
int backWhileTemp[MAX_LOOP_LEN];

char whileConditSource[MAX_LOOP_LEN][MAX_STRING_LEN];
int  whileLakuPos[MAX_LOOP_LEN];

// ..............................................................
int whileExecDone[MAX_LOOP_LEN];     // 0->notyet , 1->done */


// ..............................................................
int get_int_array(VAL_LABEL valdat, long idx);
void save_int_array(VAL_LABEL valdat, long idx, int val);
double get_dbl_array(VAL_LABEL valdat, long idx);
void save_dbl_array(VAL_LABEL valdat, long idx, double dbl);
int get_str_array(VAL_LABEL valdat, long idx, char retVal[MAX_STRING_LEN]);
void save_str_array(VAL_LABEL valdat, long idx, char entryVal[MAX_STRING_LEN]);

#ifdef USE_GTK2
GtkWidget *get_gui_array(VAL_LABEL valdat, long idx);
GtkWidget *get_eventbox_array(VAL_LABEL valdat, long idx);
int get_guitype_array(VAL_LABEL valdat, long idx);
void save_gui_array(VAL_LABEL valdat, long idx, GtkWidget *widget, GtkWidget *eventbox, int GUItype);
#endif

#ifdef USE_GTK3
GtkWidget *get_gui_array(VAL_LABEL valdat, long idx);
GtkWidget *get_eventbox_array(VAL_LABEL valdat, long idx);
int get_guitype_array(VAL_LABEL valdat, long idx);
void save_gui_array(VAL_LABEL valdat, long idx, GtkWidget *widget, GtkWidget *eventbox, int GUItype);
#endif
// ..............................................................

extern int posClassTemp;
extern int backClassTemp;

#define MAX_CLASS_SUB_DEPTH                     128
extern int class_sub_deep;                      // Sub depth for Recursion
extern int posClassSub[MAX_CLASS_SUB_DEPTH];    // pos for sub routine

extern void InterpreterClassSub( int endSub, char className[MAX_STRING_LEN] );
extern void InterpreterClassParam( int progType, int endSub, char className[MAX_STRING_LEN] );

#include "lyr/haris_string.h"

#include "keySaklar.h"

// ..............................................................

// ///////////////////////////////////
// MYSQL Header
// ///////////////////////////////////
#ifdef USE_MYSQL
#include "my_common.h"
#endif

// ///////////////////////////////////
// PGSQL Header
// ///////////////////////////////////
#ifdef USE_PGSQL
#include "pq_common.h"
#endif

// ///////////////////////////////////
// ORACLE Header
// ///////////////////////////////////
#ifdef USE_OCI
#include "oracle_common.h"
#endif

// ///////////////////////////////////
// SQLITE Header
// ///////////////////////////////////
#ifdef USE_SQLITE
#include "sqlite_common.h"
#endif


// ..............................................................

#include "web/webview01.h"
#include "web/webexpression.h"
#include "web/webview02.h"
#include "web/keyMVC_Tutup.h"
#include "web/keyMVC_Untuk.h"
#include "web/keyMVC_Array.h"
#include "web/keyMVC_Untaian.h"

#include "array_refer_func.h"

// ///////////////////////////////////
// GTK2 Header
// ///////////////////////////////////
#ifdef USE_GTK2
int MOUSE_POS_X  = 0;
int MOUSE_POS_Y  = 0;
int MOUSE_TIME   = 0;
int MOUSE_BUTTON = 0;

int EKSPOS_POS_X   = 0;
int EKSPOS_POS_Y   = 0;
int EKSPOS_WIDTH   = 0;
int EKSPOS_HEIGHT  = 0;

int KEYBOARD_VALUE = 0;
int KEYBOARD_STATE = 0;
char *KEYBOARD_STRING = NULL;

int posLyrSub;
int posLyrSubBack;
int lyr_sub_deep;

extern char* hhstring_add(char orig[], char addstr[]);


#include "lyr/gtk_common.h"

#include "lyr/keyLyrTambahMenu.h"
#include "lyr/keyLyrAkhirMenu.h"

#include "lyr/keyLyrAksiFungsi.h"
#include "lyr/keyLyrAksiLencanaJatidiri.h"
#include "lyr/keyLyrAksiRambuAwas.h"
#include "lyr/keyLyrAksiRambuInfo.h"
#include "lyr/keyLyrAksiRambuSalah.h"
#include "lyr/keyLyrAksiTutupProgram.h"
#include "lyr/keyLyrAksiTutupLayar.h"

#include "lyr/keyLyrAksiSiapPrint.h"
#include "lyr/keyLyrAksiPrintTeks.h"
#include "lyr/keyLyrMulaiCetak.h"
#include "lyr/keyLyrSetOperasiCetak.h"
#include "lyr/keyLyrTulisTeksCetak.h"

#include "lyr/keyLyrTampilLayar.h"
#include "lyr/keyLyrLayarTitel.h"
#include "lyr/keyLyrLayarLuas.h"
#include "lyr/keyLyrLayarLogo.h"
#include "lyr/keyLyrHiasLayar.h"
#include "lyr/keyLyrHiasAlas.h"
#include "lyr/keyLyrIsiAlasTegak.h"
#include "lyr/keyLyrTampilElemen.h"
#include "lyr/keyLyrSembunyiElemen.h"
#include "lyr/keyLyrSubMenu.h"
#include "lyr/keyLyrSusunMenu.h"
#include "lyr/keyLyrSusunPapanStatus.h"
#include "lyr/keyLyrTambahAkselerasi.h"
#include "lyr/keyLyrSetSensitif.h"
#include "lyr/keyLyrTampilPopup.h"
#include "lyr/keyLyrTambahAksiTekanKetik.h"
#include "lyr/keyLyrTambahAksiLepasKetik.h"
#include "lyr/keyLyrTambahAksiTekanPenunjuk.h"
#include "lyr/keyLyrTambahAksiLepasPenunjuk.h"
#include "lyr/keyLyrTambahAksiPenunjukBergerak.h"
#include "lyr/keyLyrRambuInfo.h"
#include "lyr/keyLyrRambuSalah.h"
#include "lyr/keyLyrRambuAwas.h"
#include "lyr/keyLyrSetWarnaHuruf.h"
#include "lyr/keyLyrSetWarnaDasar.h"
#include "lyr/keyLyrSetJenisHuruf.h"
#include "lyr/keyLyrSetPilihan.h"
#include "lyr/keyLyrWinSetLabel.h"
#include "lyr/keyLyrWinSetTombol.h"
#include "lyr/keyLyrWinSetMasukan.h"
#include "lyr/keyLyrWinSetToolTip.h"
#include "lyr/keyLyrWinSetKertas.h"
#include "lyr/keyLyrSetPapanStatus.h"
#include "lyr/keyLyrHapusPapanStatus.h"
#include "lyr/keyLyrWinTabelAtribut.h"
#include "lyr/keyLyrWinTabelData.h"
#include "lyr/keyLyrWinHapusSelTabel.h"
#include "lyr/keyLyrWinTulisTabel.h"
#include "lyr/keyLyrWinTulisSelTabel.h"

#include "lyr/keyLyrIsiPundiTeks.h"
#include "lyr/keyLyrIsiPundiAngka.h"
#include "lyr/keyLyrIsiPundiGambar.h"

#include "lyr/keyLyrIsiTeksRampung.h"
#include "lyr/keyLyrSetTeksRampung.h"
#include "lyr/keyLyrHapusTeksTerpilih.h"
#include "lyr/keyLyrSalinTeksPapanklip.h"
#include "lyr/keyLyrPotongTeksPapanklip.h"
#include "lyr/keyLyrUnduhTeksPapanklip.h"
#include "lyr/WinTanggalanBaik.h"
#include "lyr/keyLyrWinTanggalan.h"
#include "lyr/keyLyrSimpanTeks.h"

#include "lyr/keyCairoTeks.h"
#include "lyr/keyCairoAtributTeks.h"
#include "lyr/keyCairoGaris.h"
#include "lyr/keyCairoTebalGaris.h"
#include "lyr/keyCairoPucukGaris.h"
#include "lyr/keyCairoGarisPutus.h"
#include "lyr/keyCairoBentukSambungan.h"
#include "lyr/keyCairoKotak.h"
#include "lyr/keyCairoKotakIsi.h"
#include "lyr/keyCairoHapusLatar.h"
#include "lyr/keyCairoHapusBidang.h"
#include "lyr/keyCairoHapusPola.h"
#include "lyr/keyCairoSimpanPng.h"
#include "lyr/keyCairoWarnaPena.h"
#include "lyr/keyCairoWarnaTransparan.h"
#include "lyr/keyCairoPudarPena.h"
#include "lyr/keyCairoPindahPena.h"
#include "lyr/keyCairoGeserPena.h"
#include "lyr/keyCairoKlipPena.h"
#include "lyr/keyCairoKlipLingkaran.h"
#include "lyr/keyCairoKlipKotak.h"
#include "lyr/keyCairoGoresPena.h"
#include "lyr/keyCairoGoresPenaJaga.h"
#include "lyr/keyCairoLukisPena.h"
#include "lyr/keyCairoIsiPena.h"
#include "lyr/keyCairoIsiPenaJaga.h"
#include "lyr/keyCairoTutupKurva.h"
#include "lyr/keyCairoPolaWarna.h"
#include "lyr/keyCairoSetAsal.h"
#include "lyr/keyCairoSetAsalBidang.h"
#include "lyr/keyCairoLingkaran.h"
#include "lyr/keyCairoLingkaranIsi.h"
#include "lyr/keyCairoLekukanTeks.h"
#include "lyr/keyCairoLekukanBaru.h"

#include "lyr/keyLyrTambahAksiEkspos.h"
#include "lyr/keyLyrTambahAksiAtur.h"
#include "lyr/keyCairoEksposKanvas.h"

#include "lyr/keyCairoGeserLatar.h"
#include "lyr/keyCairoSkalaLatar.h"
#include "lyr/keyCairoPutarLatar.h"

#include "lyr/keyLyrDetakWaktu.h"
#include "lyr/keyCairoLukisPixmap.h"
#include "lyr/keyCairoHapusPixmap.h"

#include "lyr/keyLyrLembarBuku.h"
#include "lyr/keyLyrTabBuku.h"

#include "lyr/keyLyrTambahRanting.h"
#include "lyr/keyLyrWarnaDasarRanting.h"
#include "lyr/keyLyrWarnaHurufRanting.h"
#include "lyr/keyLyrJenisHurufRanting.h"
#endif


// ///////////////////////////////////
// GTK3 Header
// ///////////////////////////////////
#ifdef USE_GTK3
int MOUSE_POS_X = 0;
int MOUSE_POS_Y = 0;
int MOUSE_TIME = 0;
int MOUSE_BUTTON = 0;

int EKSPOS_POS_X = 0;
int EKSPOS_POS_Y = 0;
int EKSPOS_WIDTH = 0;
int EKSPOS_HEIGHT = 0;

int KEYBOARD_VALUE = 0;
int KEYBOARD_STATE = 0;
char *KEYBOARD_STRING = NULL;

int posLyrSub;
int posLyrSubBack;
int lyr_sub_deep;

extern char* hhstring_add(char orig[], char addstr[]);


#include "lyr3/gtk_common.h"

#include "lyr3/keyLyrTambahMenu.h"
#include "lyr3/keyLyrAkhirMenu.h"

#include "lyr3/keyLyrAksiFungsi.h"

#include "lyr3/keyLyrAksiLencanaJatidiri.h"

#include "lyr3/keyLyrAksiRambuAwas.h"
#include "lyr3/keyLyrAksiRambuInfo.h"
#include "lyr3/keyLyrAksiRambuSalah.h"

#include "lyr3/keyLyrAksiTutupProgram.h"
#include "lyr3/keyLyrAksiTutupLayar.h"

#include "lyr3/keyLyrAksiSiapPrint.h"
#include "lyr3/keyLyrAksiPrintTeks.h"

#include "lyr3/keyLyrMulaiCetak.h"

#include "lyr3/keyLyrSetOperasiCetak.h"
#include "lyr3/keyLyrTulisTeksCetak.h"

#include "lyr3/keyLyrTampilLayar.h"
#include "lyr3/keyLyrLayarTitel.h"
#include "lyr3/keyLyrLayarLuas.h"
#include "lyr3/keyLyrLayarLogo.h"
#include "lyr3/keyLyrHiasLayar.h"
#include "lyr3/keyLyrHiasAlas.h"
#include "lyr3/keyLyrIsiAlasTegak.h"
#include "lyr3/keyLyrTampilElemen.h"
#include "lyr3/keyLyrSembunyiElemen.h"
#include "lyr3/keyLyrSubMenu.h"
#include "lyr3/keyLyrSusunMenu.h"
#include "lyr3/keyLyrSusunPapanStatus.h"
#include "lyr3/keyLyrTambahAkselerasi.h"
#include "lyr3/keyLyrSetSensitif.h"
#include "lyr3/keyLyrTampilPopup.h"


#include "lyr3/keyLyrTambahAksiTekanKetik.h"
#include "lyr3/keyLyrTambahAksiLepasKetik.h"
#include "lyr3/keyLyrTambahAksiTekanPenunjuk.h"
#include "lyr3/keyLyrTambahAksiLepasPenunjuk.h"
#include "lyr3/keyLyrTambahAksiPenunjukBergerak.h"


#include "lyr3/keyLyrRambuInfo.h"
#include "lyr3/keyLyrRambuSalah.h"
#include "lyr3/keyLyrRambuAwas.h"

#include "lyr3/keyLyrSetWarnaHuruf.h"
#include "lyr3/keyLyrSetWarnaDasar.h"
#include "lyr3/keyLyrSetJenisHuruf.h"
#include "lyr3/keyLyrSetPilihan.h"
#include "lyr3/keyLyrWinSetLabel.h"
#include "lyr3/keyLyrWinSetTombol.h"
#include "lyr3/keyLyrWinSetMasukan.h"

#include "lyr3/keyLyrWinSetToolTip.h"


#include "lyr3/keyLyrWinSetKertas.h"
#include "lyr3/keyLyrSetPapanStatus.h"
#include "lyr3/keyLyrHapusPapanStatus.h"
#include "lyr3/keyLyrWinTabelAtribut.h"
#include "lyr3/keyLyrWinTabelData.h"
#include "lyr3/keyLyrWinHapusSelTabel.h"
#include "lyr3/keyLyrWinTulisTabel.h"
#include "lyr3/keyLyrWinTulisSelTabel.h"

#include "lyr3/keyLyrIsiPundiTeks.h"
#include "lyr3/keyLyrIsiPundiAngka.h"
#include "lyr3/keyLyrIsiPundiGambar.h"

#include "lyr3/keyLyrIsiTeksRampung.h"
#include "lyr3/keyLyrSetTeksRampung.h"
#include "lyr3/keyLyrHapusTeksTerpilih.h"
#include "lyr3/keyLyrSalinTeksPapanklip.h"
#include "lyr3/keyLyrPotongTeksPapanklip.h"
#include "lyr3/keyLyrUnduhTeksPapanklip.h"

#include "lyr3/WinTanggalanBaik.h"
#include "lyr3/keyLyrWinTanggalan.h"

#include "lyr3/keyLyrSimpanTeks.h"

#include "lyr3/keyCairoTeks.h"
#include "lyr3/keyCairoAtributTeks.h"
#include "lyr3/keyCairoGaris.h"
#include "lyr3/keyCairoTebalGaris.h"
#include "lyr3/keyCairoPucukGaris.h"
#include "lyr3/keyCairoGarisPutus.h"
#include "lyr3/keyCairoBentukSambungan.h"
#include "lyr3/keyCairoKotak.h"
#include "lyr3/keyCairoKotakIsi.h"
#include "lyr3/keyCairoHapusLatar.h"
#include "lyr3/keyCairoHapusBidang.h"
#include "lyr3/keyCairoHapusPola.h"
#include "lyr3/keyCairoSimpanPng.h"
#include "lyr3/keyCairoWarnaPena.h"
#include "lyr3/keyCairoWarnaTransparan.h"
#include "lyr3/keyCairoPudarPena.h"
#include "lyr3/keyCairoPindahPena.h"
#include "lyr3/keyCairoGeserPena.h"
#include "lyr3/keyCairoKlipPena.h"
#include "lyr3/keyCairoKlipLingkaran.h"
#include "lyr3/keyCairoKlipKotak.h"
#include "lyr3/keyCairoGoresPena.h"
#include "lyr3/keyCairoGoresPenaJaga.h"
#include "lyr3/keyCairoLukisPena.h"
#include "lyr3/keyCairoIsiPena.h"
#include "lyr3/keyCairoIsiPenaJaga.h"
#include "lyr3/keyCairoTutupKurva.h"
#include "lyr3/keyCairoPolaWarna.h"
#include "lyr3/keyCairoSetAsal.h"
#include "lyr3/keyCairoSetAsalBidang.h"
#include "lyr3/keyCairoLingkaran.h"
#include "lyr3/keyCairoLingkaranIsi.h"
#include "lyr3/keyCairoLekukanTeks.h"
#include "lyr3/keyCairoLekukanBaru.h"

#include "lyr3/keyLyrTambahAksiEkspos.h"
#include "lyr3/keyLyrTambahAksiAtur.h"
#include "lyr3/keyCairoEksposKanvas.h"

#include "lyr3/keyCairoGeserLatar.h"
#include "lyr3/keyCairoSkalaLatar.h"
#include "lyr3/keyCairoPutarLatar.h"

#include "lyr3/keyLyrDetakWaktu.h"

//#include "lyr3/keyCairoLukisPixmap.h"
//#include "lyr3/keyCairoHapusPixmap.h"

#include "lyr3/keyLyrLembarBuku.h"
#include "lyr3/keyLyrTabBuku.h"

#include "lyr3/keyLyrTambahRanting.h"
#include "lyr3/keyLyrWarnaDasarRanting.h"
#include "lyr3/keyLyrWarnaHurufRanting.h"
#include "lyr3/keyLyrJenisHurufRanting.h"
#endif


// ///////////////////////////////////
// PDF Header
// ///////////////////////////////////
#ifdef USE_PDF
#include "pdf/keyPdfSetHuruf.h"
#include "pdf/keyPdfTeks.h"
#include "pdf/keyPdfAwalTeks.h"
#include "pdf/keyPdfAkhirTeks.h"
#include "pdf/keyPdfSimpanPdf.h"
#include "pdf/keyPdfHapusPdf.h"
#include "pdf/keyPdfWarnaHuruf.h"
#include "pdf/keyPdfJarakHuruf.h"
#include "pdf/keyPdfJarakKata.h"
#include "pdf/keyPdfGaris.h"
#include "pdf/keyPdfKotak.h"
#include "pdf/keyPdfTebalGaris.h"
#include "pdf/keyPdfWarnaGaris.h"
#include "pdf/keyPdfPng.h"
#include "pdf/keyPdfJpg.h"
#endif

// ///////////////////////////////////
// CGI Header
// ///////////////////////////////////
#ifdef USE_CGI
extern void getPostCgi(void);
#endif

// ///////////////////////////////////
// WEBSTYLE + JS AJAX
// ///////////////////////////////////
#ifdef USE_WEBSTYLE
#include "webstyle/haris_webstyle_vector.h"
#include "webstyle/keyHtmltag.h"
#endif

// ..............................................................

#include "keyTulis.h"
#include "keySurat.h"
#include "keySub.h"
#include "keyUntaian.h"
#include "keyArray.h"
#include "keyUntuk.h"
#include "keySelagi.h"
#include "keyKalau.h"



#include "keyTunggu.h"
#include "keyPerintah.h"

#include "haris_node_struct.h"
#include "keyObject.h"
#include "keyObjectFunc.h"

#include "keyTulisarsip.h"
#include "keyTutup.h"
#include "keyPilih.h"
#include "keyHapus.h"

#ifndef S_SPLINT_S
#include "keyWindowsOnly.h"
#endif

#ifdef USE_GD
#include "keyGDGraphics.h"
#endif
// --------------------------------------------------------------------------

void BAIK_funcword( void )
{
  //printf("BAIK_funcword ... \n");
  //save_funcword("AKAR", "AKAR");
  //funcword_printData();
}

void ReadSource( int firstTime )
{
  VAL_LABEL tmpdat;
  VAL_LABEL valdat;
  VAL_LABEL objdat;    // obj
  VAL_LABEL paramdat;  // obj param

  char sub_name[MAX_STRING_LEN],
       sub_param[MAX_STRING_LEN*2];
  char obj_name[MAX_STRING_LEN],
       obj_param[MAX_STRING_LEN*2];
  char tmp_sub_name[MAX_STRING_LEN];

  struct  node_list benda_member;
  struct  node_list tmpnode;

  int  n=0, i=0;
  char c='\0';
  int  isThereMainSub=0;
  int  scope=0;

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&objdat, '\0', sizeof(objdat));
  memset(&paramdat, '\0', sizeof(paramdat));

  memset(&sub_name, '\0', sizeof(sub_name));
  memset(&sub_param, '\0', sizeof(sub_param));
  memset(&tmp_sub_name, '\0', sizeof(tmp_sub_name)); // obj

  memset(&obj_name, '\0', sizeof(obj_name));
  memset(&obj_param, '\0', sizeof(obj_param));

  memset(&benda_member, '\0', sizeof(benda_member));
  memset(&tmpnode, '\0', sizeof(tmpnode));

  if(firstTime == 1) {

    if( ValLabel( "r00t", 0, valdat, VAL_FLAG_START ).val == 1 )
      Error("Interpreter salah: tidak bisa buat searching tree/memori tidak cukup");

  }

  do{

    getlex();

    if( lex.type == _LONCATLABEL ){
      
      getlex();
      
      if( lex.type != TYPE_IDENT )
	Error("Salah kalimat LONCATLABEL");
      
      strcpy(tmpdat.ident, lex.detail.ident);
      tmpdat.val = pg.pt;
      ValLabel( lex.detail.ident, 0, tmpdat, VAL_FLAG_SEARCH_W );
    }

    else

    if( lex.type == _SUB ) {
      // printf("get pendefinisian sub\n");

      memset(&sub_name, '\0', sizeof(sub_name));
      memset(&sub_param, '\0', sizeof(sub_param));

      getlex();
      
      if( lex.type != TYPE_IDENT ) {
         Error("kode SUB salah 0");
      }

      valdat.val = pg.pt; 
      valdat.datatype = 9;

      /* printf("sub name string: %s\n", lex.detail.string);
      */

      strcpy(sub_name, lex.detail.string);
      // printf("sub name: %s\n", sub_name);

      getlex();
      

      if( lex.type != TYPE_SYM || strncmp(lex.detail.string , "(", 1) != 0 ) {
         Error("kode SUB salah : tanpa tanda (");
      }

      strcpy(sub_param, "");
      while( lex.detail.string[0] != ')' && lex.type != _EOF  ) {
        getlex();

        if(lex.detail.string[0] == ')' )
          break;

        if( lex.type != TYPE_IDENT ) {
         Error("kode SUB salah 1");
        }
        strcat(sub_param, lex.detail.string);

        getlex();
        if(lex.detail.string[0] == ',') {
          strcat(sub_param, lex.detail.string);
        }
      }

      // printf("sub param: %s\n", sub_param);
      
      getlex();
      /* printf("sub { string: %s\n", lex.detail.string);
      */

      if( lex.type != TYPE_SYM || strncmp(lex.detail.string , "{", 1) != 0 ) {
         Error("kode SUB salah : tanpa tanda {");
      }

      valdat.sub_pt_start = pg.pt - 1;          /* start function */

      while( lex.detail.string[0] != '}' && lex.type != _EOF  ) {
        getlex();
      }

      i = valdat.sub_pt_start;
      do {
        c = pg.source[i++];
      } while(c != '}' && c != _EOF);

      valdat.sub_pt_end = i;                    /* end function */

      strcpy(valdat.sub_name , sub_name);       /* function name */
      strcpy(valdat.sub_param , sub_param);     /* function      */

      ValLabel( sub_name, 0, valdat, VAL_FLAG_SEARCH_W );

      // printf("simpan posisi sub ok\n");
    }

    else

    if( lex.type == _DEF_BENDA ) {
      memset(&obj_name, '\0', sizeof(obj_name));

      getlex();
      
      if( lex.type != TYPE_IDENT ) {
         Error("kode DefinisiBenda salah");
      }

      objdat.val = pg.pt; 
      objdat.datatype = 30;  // Class Definition

      strcpy(obj_name, lex.detail.string);

      getlex();
      /* printf("sub ( string: %s\n", lex.detail.string);
      */

      if( lex.type != TYPE_SYM || strncmp(lex.detail.string , "[", 1) != 0 ) {
         Error("kode DefinisiBenda salah : tanpa tanda [");
      }

      objdat.benda_pt_start = pg.pt - 1;          /* start object */

      scope = 0;
      while( lex.detail.string[0] != ']' && lex.type != _EOF  ) {

        getlex();

        // Determine the SCOPE
        if( lex.type == _LOKAL ) {
          scope = 1;
        }
        else

        // VARIABLE inside Class
        if( lex.type == TYPE_IDENT ) {
          // printf("Obj param : %s\n", lex.detail.ident);
          memset(&obj_param, '\0', sizeof(obj_param));
          memset(&benda_member, '\0', sizeof(benda_member));

          strcpy (obj_param, lex.detail.ident);

          benda_member.member_type = 1;                  // as parameter
          strcpy(benda_member.class_name , obj_name);    // class name
          strcpy(benda_member.param_name , obj_param);   // param name

          if(scope == 1) {
            benda_member.scope = scope;
            scope = 0;
          }

          // printf("Obj name : %s\n", obj_name);
          // printf("Obj param : %s\n", obj_param);

          paramdat.isClassVar = 1;                       // variable inside class

          getlex();
          if(lex.detail.string[0] == '=') {
            // subtitusi
            getlex();
            if( lex.type == _DEF_BENDA ) {
              Error("penulisan parameter pada DefinisiBenda salah");
            }

            strcpy(benda_member.param_operation , obj_param);  // param operation syntax,  e.g. a=1
            strcat(benda_member.param_operation , "=");        // dont put space

            if( lex.type == TYPE_IDENT ) {
              strcat(benda_member.param_operation , lex.detail.ident);
            } else
            if( lex.type == TYPE_NUM ) {
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(benda_member.param_operation, sizeof(benda_member.param_operation),"%s=%li", obj_param, lex.detail.num);
               #else
               snprintf(benda_member.param_operation, sizeof(benda_member.param_operation),"%s=%li", obj_param, lex.detail.num);
               #endif
              #else
              snprintf(benda_member.param_operation, sizeof(benda_member.param_operation),"%s=%li", obj_param, lex.detail.num);
              #endif
            } else
            if( lex.type == TYPE_DBL ) {
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(benda_member.param_operation, sizeof(benda_member.param_operation),"%s=%f", obj_param, lex.detail.dblnum);
               #else
               snprintf(benda_member.param_operation, sizeof(benda_member.param_operation),"%s=%f", obj_param, lex.detail.dblnum);
               #endif
              #else
              snprintf(benda_member.param_operation, sizeof(benda_member.param_operation),"%s=%f", obj_param, lex.detail.dblnum);
              #endif

            } else
            if( lex.type == TYPE_STR ) {
              strcat(benda_member.param_operation , "\"");
              strcat(benda_member.param_operation , lex.detail.string);
              strcat(benda_member.param_operation , "\"");
            } else
            if( lex.type == TYPE_ARRAY ) {
              strcat(benda_member.param_operation , lex.detail.array_str);
            }

            strcat(benda_member.param_operation , " }"); // dummy for stopping

            // printf("subtitusi: %s\n", benda_member.param_operation );


            // ungetlex();
          } else {
            ungetlex();
          }

          // add param into LIST as a member of class
          node_addLast(benda_member);

          /*
          i = node_getCount();
          printf("Total Param num : %d\n", i);
          for(n=0;n<i;n++) {
            tmpnode = node_getElement(n);
            printf(" set %d Obj name : %s\n", n, tmpnode.class_name);
            printf(" set %d Obj param : %s\n", n, tmpnode.param_name);
            printf(" set %d Obj scope : %d\n", n, tmpnode.scope);
          }
          */


        // FUNCTION inside Class
        } else if( lex.type == _SUB ) {
          memset(&sub_name, '\0', sizeof(sub_name));
          memset(&tmp_sub_name, '\0', sizeof(tmp_sub_name));
          memset(&sub_param, '\0', sizeof(sub_param));

          memset(&benda_member, '\0', sizeof(benda_member));

          memset(&valdat, '\0', sizeof(valdat));             // for saving sub like a param

          if(scope == 1) {
            benda_member.scope = scope;
            scope = 0;
          }

          getlex();

          if( lex.type != TYPE_IDENT) {
            Error("penulisan SUB fungsi pada DefinisiBenda salah");
          }

          valdat.val = pg.pt;                                // Obj pos
          valdat.datatype = 32;                              // Var Type : Class Function

          benda_member.member_type = 2;                      // as function
          strcpy(benda_member.class_name , obj_name);        // class name

          strcpy(tmp_sub_name, lex.detail.ident);
          strcpy(benda_member.function_name , tmp_sub_name); // function name

          // add param into LIST as a member of class
          node_addLast(benda_member);

          // printf("read sub: %s\n", tmp_sub_name);
          if(strcmp(tmp_sub_name, "awalan") == 0 ||
             strcmp(tmp_sub_name, "Awalan") == 0 ||
             strcmp(tmp_sub_name, "AWALAN") == 0 ) {
            Error("kode SUB pada DefinisiBenda salah : tidak boleh dengan nama AWALAN");
          }

          if(strcmp(obj_name,lex.detail.ident) == 0) {
            isThereMainSub = 1;
            // printf("main sub: %s\n", lex.detail.ident);
            #ifdef WIN32
             #ifndef S_SPLINT_S
             sprintf_s(sub_name, sizeof(sub_name),"%s->awalan",obj_name);
             #else
             snprintf(sub_name, sizeof(sub_name),"%s->awalan",obj_name);
             #endif
            #else
            snprintf(sub_name, sizeof(sub_name),"%s->awalan",obj_name);
            #endif
          } else {
            // printf("other sub: %s\n", lex.detail.ident);
            #ifdef WIN32
             #ifndef S_SPLINT_S
             sprintf_s(sub_name, sizeof(sub_name),"%s->%s",obj_name, tmp_sub_name);
             #else
             snprintf(sub_name, sizeof(sub_name),"%s->%s",obj_name, tmp_sub_name);
             #endif
            #else
            snprintf(sub_name, sizeof(sub_name),"%s->%s",obj_name, tmp_sub_name);
            #endif
          }
          // printf("creating sub name: %s\n", sub_name);

          // read symbol '(' of function
          getlex();
          if( lex.type != TYPE_SYM || strncmp(lex.detail.string , "(", 1) != 0 ) {
             Error("kode SUB pada DefinisiBenda salah : tanpa tanda (");
          }

          strcpy(sub_param, "");
          while( lex.detail.string[0] != ')' && lex.type != _EOF  ) {
            getlex();

            if(lex.detail.string[0] == ')' )
              break;

            if( lex.type != TYPE_IDENT ) {
             Error("kode SUB pada DefinisiBenda salah");
            }
            strcat(sub_param, lex.detail.string);

            memset(&benda_member, '\0', sizeof(benda_member));
            benda_member.member_type = 1;                  // as parameter
            strcpy(benda_member.class_name , obj_name);    // class name
            strcpy(benda_member.param_name , lex.detail.string);   // param name

            // add param into LIST as a member of class
            node_addLast(benda_member);

            getlex();
            if(lex.detail.string[0] == ',') {
              strcat(sub_param, lex.detail.string);
            }
          }

          // printf("sub param: %s\n", sub_param);

          getlex();
          if( lex.type != TYPE_SYM || strncmp(lex.detail.string , "{", 1) != 0 ) {
             Error("kode SUB salah : tanpa tanda {");
          }

          valdat.sub_pt_start = pg.pt - 1;          /* start function */

          do {
            getlex();
          } while (lex.detail.string[0] != '}' && c != _EOF);

          i = valdat.sub_pt_start;
          do {
            c = pg.source[i++];
          } while(c != '}' && c != _EOF);

          valdat.sub_pt_end = i;                    /* end function */

          // printf("sub pg start: %d\n", valdat.sub_pt_start);
          // printf("sub pg end: %d\n", valdat.sub_pt_end);

          strcpy(valdat.sub_name , sub_name);       /* function name */
          strcpy(valdat.sub_param , sub_param);     /* function      */

          //if(src_id != 0) {
          //  strcpy(valdat.sub_file , inc_file);     /* function include file */
          //}

          // save FUNCTION of OBJECT into Tree Memory.
          ValLabel( sub_name, sub_deep, valdat, VAL_FLAG_SEARCH_W );
          // printf("save sub ok\n");

        }

      } // end   while( lex.detail.string[0] != ']' && lex.type != _EOF  )


      i = objdat.benda_pt_start;
      do {
        c = pg.source[i++];
      } while(c != ']' && c != _EOF);

      objdat.benda_pt_end = i;


      strcpy(objdat.benda_name , obj_name);       /* class name */

      if(isThereMainSub != 1) {
        Error("Tidak ada fungsi utama dalam DefinisiBenda");
      }

      // save OBJECT into Tree Memory.
      ValLabel( obj_name, sub_deep, objdat, VAL_FLAG_SEARCH_W );
      // printf("save obj ok\n");

    } // end     if( lex.type == _DEF_BENDA ) {

  }while( lex.type != _EOF );
  
  memset( &lex, 0, sizeof(BAIK_LEX) );

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));


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

}

// ///////////////////////////////////////////////////////////////////////////////

// Read Include File and merge into pg.source
void IncludeCodeReader()
{
	char ident[MAX_IDENT_LEN];
	char logMsg[MAX_STRING_LEN], tmpMsg[MAX_STRING_LEN];

	int  i = 0;
	int  isIncluded = 0;

	char lineCode[1024];
	char entireCode[262144];  // max 1MB include file

	char *allsrc = NULL;

	char sub_name[MAX_STRING_LEN],
		tmp_sub_name[MAX_STRING_LEN],
		sub_param[MAX_STRING_LEN * 2];
	char obj_name[MAX_STRING_LEN],
		obj_param[MAX_STRING_LEN * 2];

	struct  node_list benda_member;
	struct  node_list tmpnode;

	VAL_LABEL valdat;
	VAL_LABEL objdat;
	VAL_LABEL paramdat;

	memset(&lineCode, '\0', sizeof(lineCode));
	memset(&entireCode, '\0', sizeof(entireCode));

	memset(&valdat, '\0', sizeof(valdat));
	memset(&objdat, '\0', sizeof(objdat));
	memset(&paramdat, '\0', sizeof(paramdat));

	memset(&sub_name, '\0', sizeof(sub_name));
	memset(&tmp_sub_name, '\0', sizeof(tmp_sub_name));
	memset(&sub_param, '\0', sizeof(sub_param));

	memset(&obj_name, '\0', sizeof(obj_name));
	memset(&obj_param, '\0', sizeof(obj_param));

	memset(&ident, '\0', sizeof(ident));
	memset(&logMsg, '\0', sizeof(logMsg));
	memset(&tmpMsg, '\0', sizeof(tmpMsg));

	memset(&benda_member, '\0', sizeof(benda_member));
	memset(&tmpnode, '\0', sizeof(tmpnode));

	inc_tmp_source = NULL;
	inc_tmp_source = (char *)malloc(strlen(pg.source) + 1);
	for (i = 0; i < (int)strlen(pg.source); i++)
		inc_tmp_source[i] = pg.source[i];
	inc_tmp_source[i] = '\0';

	//printf("inside IncludeCodeReader ...<BR>\n");
	isIncluded = 1;

	getlex();

	inc_pt = pg.pt;
	inc_back_pt = pg.back_pt;

	//printf("getlex pos : %d \n", pg.pt);
	//printf("getlex OK : type %d   %s <BR>\n", lex.type, lex.detail.string);

	switch (lex.type)
	{
	case TYPE_STR:

		// clear filename
		memset(&incname, '\0', sizeof(incname));
		strcpy(incname, lex.detail.string);
		//printf("STR Code luar %s <BR>\n", incname);

		if ((inc_fp = fopen(incname, "r")) == NULL) {
		        printf("Gagal Buka file ! <BR>\n");
			fprintf(stderr, "tidak bisa buka Kode Luar %s\n", incname);
			exit(-1);
		}
		//printf("open file OK<BR>\n");

		strcpy(lineCode, "");

		// printf("reading file ...\n");
		strcpy(entireCode, "");
		while (fgets(lineCode, (int)sizeof(lineCode), inc_fp) != '\0') {
			// printf("buf : %s\n",lineCode);
			strcat(entireCode, lineCode);
			memset(&lineCode, '\0', sizeof(lineCode));
		}

		fclose(inc_fp);
		inc_fp = NULL;
		// printf("fclose OK\n");

		//printf("1&&&&&&&&&&&&&&&&&&&&&&\n");
		//printf("%s",entireCode);
		//printf("\n");
		//printf("&&&&&&&&&&&&&&&&&&&&&&\n");

		break;
		

	case TYPE_IDENT:

                memset(&valdat, '\0', sizeof(valdat));
                valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                if(valdat.str != NULL && valdat.datatype == 3) {
                  //printf("get file : %s <BR>\n", valdat.str);
                
  		  // clear filename
		  memset(&incname, '\0', sizeof(incname));
		  strcpy(incname, valdat.str);
		  //printf("IDENT Code luar %s <BR>\n", incname);
                }

		if ((inc_fp = fopen(incname, "r")) == NULL) {
		        printf("Gagal buka file ! <BR>\n");
			fprintf(stderr, "tidak bisa buka Kode Luar %s\n", incname);
			exit(-1);
		}
		//printf("open file OK<BR>\n");

		strcpy(lineCode, "");

		// printf("reading file ...\n");
		strcpy(entireCode, "");
		while (fgets(lineCode, (int)sizeof(lineCode), inc_fp) != '\0') {
			// printf("buf : %s\n",lineCode);
			strcat(entireCode, lineCode);
			memset(&lineCode, '\0', sizeof(lineCode));
		}

		fclose(inc_fp);
		inc_fp = NULL;
		// printf("fclose OK\n");

		//printf("1&&&&&&&&&&&&&&&&&&&&&&\n");
		//printf("%s",entireCode);
		//printf("\n");
		//printf("&&&&&&&&&&&&&&&&&&&&&&\n");

		break;
		
		
	}

	// merge
	allsrc = hhstring_add(inc_tmp_source, entireCode);

	pg.pt = inc_pt;
	pg.back_pt = inc_back_pt;

	//printf("33&&&&&&&&&&&&&&&&&&&&&&\n");
	//printf("%s",tmp_source2);
	//printf("33&&&&&&&&&&&&&&&&&&&&&&\n");


  if(isIncluded) {
    // printf("there is inluce file...\n");

    if(pg.source != NULL) free (pg.source);
    pg.source = (char *)malloc(strlen(allsrc)+1);
    for(i=0; i<(int)strlen(allsrc); i++)
      pg.source[i] = allsrc[i];  
    pg.source[i] = '\0';

    if(allsrc != NULL)
      free( allsrc );
    
   if(inc_tmp_source != NULL)
     free( inc_tmp_source );    


    //printf("&&&&&&&&&&&&&&&&&&&&&&<BR>\n");
    //printf("%s",pg.source);
    //printf("&&&&&&&&&&&&&&&&&&&&&&<BR>\n");

  } else {
   if(inc_tmp_source != NULL)
     free( inc_tmp_source );
  }

  memset(&lineCode, '\0', sizeof(lineCode));
  memset(&entireCode, '\0', sizeof(entireCode));

  
  // printf("Include File finished ...\n");

}



// Read Include MVC View File
void IncludeViewCode()
{
	char ident[MAX_IDENT_LEN];
	char logMsg[MAX_STRING_LEN], tmpMsg[MAX_STRING_LEN];

	int  i = 0;
	int  isIncluded = 0;

	char lineCode[1024];
	char entireCode[262144];  // max 1MB include file

	char *allsrc = NULL;

	char sub_name[MAX_STRING_LEN],
		tmp_sub_name[MAX_STRING_LEN],
		sub_param[MAX_STRING_LEN * 2];
	char obj_name[MAX_STRING_LEN],
		obj_param[MAX_STRING_LEN * 2];

	struct  node_list benda_member;
	struct  node_list tmpnode;

	VAL_LABEL valdat;
	VAL_LABEL objdat;
	VAL_LABEL paramdat;

	memset(&lineCode, '\0', sizeof(lineCode));
	memset(&entireCode, '\0', sizeof(entireCode));

	memset(&valdat, '\0', sizeof(valdat));
	memset(&objdat, '\0', sizeof(objdat));
	memset(&paramdat, '\0', sizeof(paramdat));

	memset(&sub_name, '\0', sizeof(sub_name));
	memset(&tmp_sub_name, '\0', sizeof(tmp_sub_name));
	memset(&sub_param, '\0', sizeof(sub_param));

	memset(&obj_name, '\0', sizeof(obj_name));
	memset(&obj_param, '\0', sizeof(obj_param));

	memset(&ident, '\0', sizeof(ident));
	memset(&logMsg, '\0', sizeof(logMsg));
	memset(&tmpMsg, '\0', sizeof(tmpMsg));

	memset(&benda_member, '\0', sizeof(benda_member));
	memset(&tmpnode, '\0', sizeof(tmpnode));

	inc_tmp_source = NULL;
	inc_tmp_source = (char *)malloc(strlen(pg.source) + 1);
	for (i = 0; i < (int)strlen(pg.source); i++)
		inc_tmp_source[i] = pg.source[i];
	inc_tmp_source[i] = '\0';

	//printf("inside IncludeViewCode ...<BR>\n");
	isIncluded = 1;

	getlex();

	inc_pt = pg.pt;
	inc_back_pt = pg.back_pt;

	//printf("getlex pos : %d \n", pg.pt);
	//printf("getlex OK : type %d   %s <BR>\n", lex.type, lex.detail.string);

	switch (lex.type)
	{
	case TYPE_STR:

		// clear filename
		memset(&incname, '\0', sizeof(incname));
		strcpy(incname, lex.detail.string);
		// printf("STR Code luar %s <BR>\n", incname);

		if ((inc_fp = fopen(incname, "r")) == NULL) {
		        printf("Gagal buka file ! <BR>\n");
			fprintf(stderr, "tidak bisa buka Kode Luar %s\n", incname);
			exit(-1);
		}
		//printf("open file OK<BR>\n");

		strcpy(lineCode, "");

		// printf("reading file ...\n");
		strcpy(entireCode, "");
		while (fgets(lineCode, (int)sizeof(lineCode), inc_fp) != '\0') {
			// printf("buf : %s\n",lineCode);
			strcat(entireCode, lineCode);
			memset(&lineCode, '\0', sizeof(lineCode));
		}

		fclose(inc_fp);
		inc_fp = NULL;
		// printf("fclose OK\n");

		//printf("1&&&&&&&&&&&&&&&&&&&&&&\n");
		//printf("%s",entireCode);
		//printf("\n");
		//printf("&&&&&&&&&&&&&&&&&&&&&&\n");

                MVCInterpreter( entireCode , 0, 262144);

		break;
		

	case TYPE_IDENT:

                memset(&valdat, '\0', sizeof(valdat));
                valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                if(valdat.str != NULL && valdat.datatype == 3) {
                  //printf("get file : %s <BR>\n", valdat.str);
                
  		  // clear filename
		  memset(&incname, '\0', sizeof(incname));
		  strcpy(incname, valdat.str);
		  //printf("IDENT Code luar %s <BR>\n", incname);
                }

		if ((inc_fp = fopen(incname, "r")) == NULL) {
		        printf("Gagal buka file ! <BR>\n");
			fprintf(stderr, "tidak bisa buka Kode Luar %s\n", incname);
			exit(-1);
		}
		//printf("open file OK<BR>\n");

		strcpy(lineCode, "");

		// printf("reading file ...\n");
		strcpy(entireCode, "");
		while (fgets(lineCode, (int)sizeof(lineCode), inc_fp) != '\0') {
			// printf("buf : %s\n",lineCode);
			strcat(entireCode, lineCode);
			memset(&lineCode, '\0', sizeof(lineCode));
		}

		fclose(inc_fp);
		inc_fp = NULL;
		// printf("fclose OK\n");

		//printf("1&&&&&&&&&&&&&&&&&&&&&&\n");
		//printf("%s",entireCode);
		//printf("\n");
		//printf("&&&&&&&&&&&&&&&&&&&&&&\n");

                MVCInterpreter( entireCode , 0, 262144);

		break;
		
		
	}

	pg.pt = inc_pt;
	pg.back_pt = inc_back_pt;


  memset(&lineCode, '\0', sizeof(lineCode));
  memset(&entireCode, '\0', sizeof(entireCode));

  
  // printf("Include File finished ...\n");

}


// ///////////////////////////////////////////////////////////////////////////////

void Interpreter( void )
{
  char ident[MAX_IDENT_LEN];
  VAL_LABEL tmpdat; // saving value

  VAL_LABEL valdat, datx;

  int plusplus=0;

  char tmp_str[MAX_STRING_LEN];

  //---------------------------------------------------------------
  int   idx=0;                  // array index
  char  dat_a[MAX_STRING_LEN];          // used in: TULIS
  char  class_tmpvar[MAX_STRING_LEN];   // used in: TULIS
  //---------------------------------------------------------------

    memset(&tmpdat, '\0', sizeof(tmpdat));
    memset(&valdat, '\0', sizeof(valdat));
    memset(&datx, '\0', sizeof(datx));

    memset(&tmp_str, '\0', sizeof(tmp_str));
    memset(&dat_a, '\0', sizeof(dat_a));
    memset(&ident, '\0', sizeof(ident));
    memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    getlex();

    switch( lex.type )
      {

      case _CEK_MEMORI:
	    // debug inside Tree
        ValLabel( "", 0, tmpdat, VAL_FLAG_PRINT );
	  break;

      case _LONCATLABEL:
            // do nothing
	    getlex();
	  break;

      case _TULIS:
            keyTulis();
	  break;

      case _TULISLOG:
            keyTulisLog();
	  break;

      case _TULIS_RINCI:
            keyTulisRinci();
	  break;

      case _TULIS_ARSIP:
        keyTulisarsip();
      break;

      case _SURAT:
         keySurat();
      break;

      case _TUTUP:
        keyTutup();
      break;

      case _PERINTAH:
            keyPerintah();
	  break;

      case _KODE_LUAR:
          //printf("enter KODE_LUAR ...<BR>\n");
          IncludeCodeReader();
                
          //printf("start ReadSource ...<BR>\n");
          inc_pt = pg.pt;
          inc_back_pt = pg.pt;

          pg.pt = 0;
          pg.back_pt = 0;
          memset(&lex, 0, sizeof(BAIK_LEX));
                          
          // re-populate SUB positions
          // just add new one 
          ReadSource(2); 
          pg.pt = inc_pt;
          pg.back_pt = inc_back_pt;
          
          //printf("ReadSource OK ...<BR>\n");          

      break;
      
      
      case _RUPA:
          //printf("enter RUPA ...<BR>\n");

          IncludeViewCode();
                
          //printf("RUPA DONE ...<BR>\n");

      break;      

      #ifndef S_SPLINT_S

      case _MUSIK:
        keyMusik();
      break;
      
      case _MUSIK_BGM:
        keyMusikBGM();
      break;      

      case _JENDELA:
        // Windows Only
        keyJendela();
      break;

      #endif

      case _TUNGGU:
            keyTunggu();
	  break;

      case _HAPUS:
            keyHapus();
	  break;

      case _RETURN:
	  getlex();

	  memset(&returnVal, '\0', sizeof(returnVal));
	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(lex.detail.string  != '\0' && strlen(lex.detail.string) > 0) {
                strcpy(returnVal.str , lex.detail.string );
              } else {
                strcpy(returnVal.str , "" );
              }
              returnVal.datatype = 3;
	      break;
	    
	    case TYPE_NUM:
              returnVal.val = lex.detail.num;
              returnVal.datatype = 0;
	      break;

	    case TYPE_IDENT:
	    case TYPE_ARRAY:
	      //printf ("return IDENT / ARRAY : %s\n", lex.detail.ident);
	      //printf ("currClass : %s\n", currentClass);
              memset(&tmpdat, '\0', sizeof(tmpdat));

              if(currentClass != NULL && strlen(currentClass) > 0) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.string);
                #endif

		//printf("tulis: construct class var: %s , deep %d\n", class_tmpvar, class_sub_deep);
                tmpdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              } else {
                tmpdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
	      }

               // printf ("type %d, val %d\n", tmpdat.datatype, tmpdat.val);
              if(tmpdat.datatype == 0) {
	        returnVal.val = tmpdat.val;
                returnVal.datatype = 0;
              } else if(tmpdat.datatype == 3) {
                strcpy(returnVal.str , tmpdat.str );
                returnVal.datatype = 3;
              } else {
                returnVal = tmpdat;
              }

              if(sub_deep > 0) {
	         // printf ("return IDENT OK, try to go to ending ...\n");
	         while( lex.type != TYPE_SYM && lex.detail.symbol != '}' ) {
                    getlex();
	            if( lex.type == _EOF )
	              Error("RETURN error");
                 }
	      }

	      break;

	    default:
	      Error("kode perintah RETURN salah");
	    }
	break;

      case _MASUK:
	getlex();
	if( lex.type == TYPE_IDENT ){
	  int num;
	  char buf[1024];
	  fgets( buf, sizeof(buf), stdin);
	  num = atoi(buf);

          strcpy(tmpdat.ident, lex.detail.ident);
          tmpdat.val = num;
	  ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
	}
	else
	  Error("Salah kalimat Masuk");
	break;
	
      // # ############################ PILIH ###############################
      case _PILIH:
       keyPilih();
      break;

      case _AKHIRPILIH:
        do{
            getlex();
        }while( strncmp(lex.detail.string , "}", 1) != 0 && lex.type != _EOF );

        if( lex.type == _EOF )
          Error("PILIH tanpa tanda penutup }");
      break;
      // # ############################ -PILIH- ###############################

      // # ############################ KALAU ################################	
      case _KALAU:
        keyKalau();
		// printf("after KALAU: curr result %d\n", currKalauResult[if_deep]);
	break;

      case _LAINKALAU:
        // printf("DEBUG: case LAINKALAU\n");
		if(currKalauResult[if_deep] == 0) {
          keyLainKalau();
		} else {
	      do {
	       getlex();
	      }while( (lex.type != _STOPKALAU ) && 
                   lex.type != _EOF );
	      if( lex.type == _EOF )
	        Error("KALAU tanpa STOPKALAU");
	    }
		// printf("after LAINKALAU: curr result %d\n", currKalauResult[if_deep]);
	break;

      case _LAINNYA:
        //printf("LAINNYA: if deep %d\n", if_deep);
		//printf("LAINNYA: curr result %d\n", currKalauResult[if_deep]);
		if(currKalauResult[if_deep] == 1) {
	      do{
	       getlex();
	      }while( lex.type != _STOPKALAU && lex.type != _EOF );
	      if( lex.type == _EOF )
	        Error("KALAU tanpa STOPKALAU");
		}
	break;

      case _STOPKALAU:
	     if_deep--;
		 // printf("stop_kalau pos: %d\n", pg.pt);
         // do nothing
	break;

      // # ############################ -KALAU- ################################


      // # ############################ UNTUK ################################
      case _UNTUK:
        //if(isDEBUG == 1) printf("DEBUG: case UNTUK\n");
        keyUntuk();
      break;

      case _ULANG:
        //if(isDEBUG == 1) printf("DEBUG: case ULANG\n");
      break;

      case _KELUARUNTUK:
        //if(isDEBUG == 1) printf("DEBUG: case KELUARUNTUK\n");
        forExecDone[loop_flag] = 1;
        do{
          getlex();
        }while( lex.type != _LAGI && lex.type != _EOF );
      break;

      case _LAGI:
		// printf("DEBUG: case LAGI, loop : %d\n", loop_flag);
		// printf("LAGI, LAST pos : %d, fdeep %d, loop_flg %d\n", pg.pt, f_deep, loop_flag);
      break;

      case _LANJUT:
        //if(isDEBUG == 1) printf("DEBUG: case LANJUT\n");
        do{
          getlex();
        }while( lex.type != _BALIKLAGI && lex.type != _LAGI && lex.type != _EOF );
        ungetlex();
      break;

      // # ############################ -UNTUK- ################################


      // # ############################ SELAGI ################################

      case _SELAGI:
        // printf("DEBUG: case SELAGI\n");
        keySelagi();
      break;

      case _KELUARSELAGI:
        // printf("DEBUG: case KELUARSELAGI\n");
        whileExecDone[while_flag] = 0;
        do{
          getlex();
        }while( lex.type != _BALIKLAGI && lex.type != _EOF );
      break;

      case _BALIKLAGI:
        // printf("DEBUG: case BALIKLAGI\n");
        if(while_flag > 1) {
          for(w_deep=1; w_deep < while_flag; w_deep++) {
            do{
              getlex();
            }while( lex.type != _BALIKLAGI  );
          }
        }
      break;

      // # ############################ -SELAGI- ################################

      /*  === GD Graphic Handle ============================== start ==== */

      #ifdef USE_GD

      case _GAMBAR_GARIS:
        // printf("DEBUG: case GAMBAR_GARIS\n");
        keyGAMBAR_GARIS();
      break;

      case _GAMBAR_GARIS_PUTUS:
        // printf("DEBUG: case GAMBAR_GARIS_PUTUS\n");
        keyGAMBAR_GARIS_PUTUS();
      break;

      case _GAMBAR_KOTAK:
        // printf("DEBUG: case GAMBAR_KOTAK\n");
        keyGAMBAR_KOTAK();
      break;

      case _GAMBAR_KOTAK_ISI:
        // printf("DEBUG: case GAMBAR_KOTAK_ISI\n");
        keyGAMBAR_KOTAK_ISI();
      break;

      case _GAMBAR_LINGKARAN:
        // printf("DEBUG: case GAMBAR_LINGKARAN\n");
        keyGAMBAR_LINGKARAN();
      break;

      case _GAMBAR_LINGKARAN_ISI:
        // printf("DEBUG: case GAMBAR_LINGKARAN_ISI\n");
        keyGAMBAR_LINGKARAN_ISI();
      break;

      case _SIMPAN_GAMBAR_PNG:
        // printf("DEBUG: case SIMPAN_GAMBAR_PNG\n");
        memset(dat_a, '\0', sizeof(dat_a));
        keySIMPAN_GAMBAR_PNG();
      break;

      case _SIMPAN_GAMBAR_JPG:
        // printf("DEBUG: case SIMPAN_GAMBAR_JPG\n");
        memset(dat_a, '\0', sizeof(dat_a));
        keySIMPAN_GAMBAR_JPG();
      break;

      //  _GAMBAR_POLIGON,        /* 35 gdImagePolygon          */
      //  _GAMBAR_POLIGON_ISI,    /* 36 gdImageFilledPolygon    */

      case _GAMBAR_HURUF:
        // printf("DEBUG: case GAMBAR_HURUF\n");
        keyGAMBAR_HURUF();
      break;

      case _HAPUS_GAMBAR:
        // printf("DEBUG: case HAPUS_GAMBAR\n");
        keyHAPUS_GAMBAR();
      break;

      #endif
      /*  === GD Graphic Handle ============================== end ==== */

      case _SAKLAR_HIDUP:
        keySAKLAR_HIDUP();
      break;

      case _SAKLAR_MATI:
        keySAKLAR_MATI();
      break;


      /*  ============================================================= */
      #ifdef USE_GTK2
      /*  === GUI GTK Handle =============================== start ==== */

      case _PAKAI_LAYAR:
        //we need to initialize all these functions so that gtk knows
        //to be thread-aware
        #ifdef WIN32
        if (!g_thread_supported()){ 
          g_thread_init(NULL);
        }

        gdk_threads_init();
        gdk_threads_enter();
        #endif
        
        gtk_set_locale();

        gtk_init(NULL, NULL);
      break;

      case _KIBAR_LAYAR:
		gtk_main();
        gdk_threads_leave();
      break;

      case _TAMPIL_LAYAR:
        keyTampil_Layar();
      break;

      case _TAMPIL_ELEMEN:
        keyTampil_Elemen();
      break;

      case _SEMBUNYI_ELEMEN:
        keySembunyi_Elemen();
      break;

      case _TITEL_LAYAR:
       keyTitelLayar();
      break;

      case _LUAS_LAYAR:
       keyLuasLayar();
      break;

      case _LOGO_LAYAR:
       keyLogoLayar();
      break;

      case _HIAS_LAYAR:
       keyHiasLayar();
      break;

      case _HIAS_LAYAR_GULUNG:
       keyHiasLayarGulung();
      break;

      case _HIAS_ALAS:
       keyHiasAlas();
      break;

      case _ISI_ALAS_TEGAK:
       keyIsiAlasTegak();
      break;

      case _SET_WARNAHURUF:
       keySetWarnaHuruf();
      break;

      case _SET_WARNADASAR:
       keySetWarnaDasar();
      break;

      case _SET_JENISHURUF:
       keySetJenisHuruf();
      break;

      case _SET_PILIHAN:
       keySetPilihan();
      break;

	  // ////////////////////////////////////////////////
      case _AKSI_TUTUP_PROGRAM:
        keyAksi_Tutup_Program(); // END Program
      break;

      case _AKSI_TUTUP_LAYAR:
        keyAksi_Tutup_Layar();   // Just Close Win
      break;

      case _AKSI_FUNGSI:
        keyAksi_Fungsi();
      break;

      case _AKSI_TEKAN_KETIK:
        keyAksi_Tekan_Papanketik();
      break;

      case _AKSI_LEPAS_KETIK:
        keyAksi_Lepas_Papanketik();
      break;

      case _AKSI_TEKAN_MOUSE:
        keyAksi_Tekan_Penunjuk();
      break;

      case _AKSI_LEPAS_MOUSE:
        keyAksi_Lepas_Penunjuk();
      break;

      case _AKSI_MOUSE_BERGERAK:
        keyAksi_Penunjuk_Bergerak();
      break;

      case _AKSI_RAMBU_INFO:
        keyAksi_Rambu_Info();
      break;

      case _AKSI_RAMBU_AWAS:
        keyAksi_Rambu_Awas();
      break;

      case _AKSI_RAMBU_SALAH:
        keyAksi_Rambu_Salah();
      break;

      case _AKSI_JATIDIRI:
        keyAksi_Lencana_Jatidiri();
      break;


	  // ////////////////////////////////////////////////

      case _AKSI_SIAP_CETAK:
        keyAksi_SiapPrint();
      break;

      case _AKSI_CETAK_TEKS:
        keyAksi_PrintTeks();
      break;

      case _MULAI_CETAK:
        keyMulaiCetak();
      break;

      case _SET_OPERASI_CETAK:
        keySetOperasiCetak();
      break;

      case _TULIS_TEKS_CETAK:
        keyTulisTeksCetak();
      break;

	  // ////////////////////////////////////////////////

      case _SUBMENU:
       keySubMenu();
      break;

      case _TAMBAH_MENU:
       keyTambahMenu();
      break;

      case _AKHIR_MENU:
       keyAkhirMenu();
      break;

      case _SUSUN_MENU:
       keySusunMenu();
      break;

      case _TAMBAH_AKSELERASI:
       keyTambahAkselerasi();
      break;

      case _SET_SENSITIF:
       keySetSensitif();
      break;

      case _TAMPIL_POPUP:
        keyTampil_Popup();
      break;

      case _SUSUN_PAPAN_STATUS:
       keySusunPapanStatus();
      break;

	  // -----------------------------------------------

      case _RAMBU_INFO:
       keyRambuInfo();
      break;

      case _RAMBU_SALAH:
       keyRambuSalah();
      break;

      case _RAMBU_AWAS:
       keyRambuAwas();
      break;

	  // ////////////////////////////////////////////////

      case _SET_LABEL:
        keyWinSetLabel();
      break;

      case _SET_TOMBOL:
        keyWinSetTombol();
      break;

      case _SET_MASUKAN:
        keyWinSetMasukan();
      break;

      case _SET_TIPS:
        keyWinSetToolTip();
      break;

      case _SET_KERTAS:
        keyWinSetKertas();
      break;

      case _SET_STATUS:
        keySetPapanStatus();
      break;

      case _HAPUS_STATUS:
        keyHapusPapanStatus();
      break;

      case _TABEL_ATRIBUT:
        keyWinTabelAtribut();
      break;

      case _TABEL_DATA:
        keyWinTabelData();
      break;

      case _HAPUS_SEL_TABEL:
        keyWinHapusSelTabel();
      break;

      case _TULIS_SEL_TABEL:
        keyWinTulisSelTabel();
      break;

      case _TULIS_TABEL:
        keyWinTulisTabel();
      break;

      case _SIMPAN_TEKS:
        keySimpanTeks();
      break;

      case _ISI_PUNDI_TEKS:
        keyIsiPundiTeks();
      break;

      case _ISI_TEKS_RAMPUNG:
        keyIsiTeksRampung();
      break;

      case _SET_TEKS_RAMPUNG:
        keySetTeksRampung();
      break;

      case _HAPUS_TEKS_TERPILIH:
        keyHapusTeksTerpilih();
      break;

      case _SALIN_TEKS_PAPANKLIP:
        keySalinTeksPapanklip();
      break;

      case _POTONG_TEKS_PAPANKLIP:
        keyPotongTeksPapanklip();
      break;

      case _UNDUH_TEKS_PAPANKLIP:
        keyUnduhTeksPapanklip();
      break;

      case _TANGGALAN:
        keyWinTanggalan();
      break;

      case _LEMBAR_BUKU:
       keyLembarBuku();
      break;

      case _TAB_BUKU:
       keyTabBuku();
      break;

      case _TAMBAH_RANTING:
       keyTambahRanting();
      break;

      case _WARNADASAR_SEL:
       keyWarnaDasarRanting();
      break;

      case _WARNAHURUF_SEL:
       keyWarnaHurufRanting();
      break;

      case _JENISHURUF_SEL:
       keyJenisHurufRanting();
      break;

	  // === Cairo Handle =================================
      case _AKSI_EKSPOS:
        keyAksi_Ekspos();
      break;

      case _AKSI_ATUR:
        keyAksi_Atur();
      break;

      case _EKSPOS_KANVAS:
        keyEksposKanvas();
      break;

      case _LUKIS_TEKS:
        keyCairoTeks();
      break;

      case _LUKIS_GARIS:
        keyCairoGaris();
      break;

      case _LUKIS_KOTAK:
        keyCairoKotak();
      break;

      case _LUKIS_KOTAK_ISI:
        keyCairoKotakIsi();
      break;

      case _LUKIS_LINGKARAN:
        keyCairoLingkaran();
      break;

      case _LUKIS_LINGKARAN_ISI:
        keyCairoLingkaranIsi();
      break;

      case _HAPUS_LATAR:
        keyCairoHapusLatar();
      break;

      case _HAPUS_BIDANG:
        keyCairoHapusBidang();
      break;

      case _HAPUS_POLA:
        keyCairoHapusPola();
      break;

      case _POLA_WARNA:
        keyCairoPolaWarna();
      break;

      case _SET_ASAL:
        keyCairoSetAsal();
      break;

      case _SET_ASALBIDANG:
        keyCairoSetAsalBidang();
      break;

      case _SIMPAN_LUKISAN:
        keyCairoSimpanLukisan();
      break;

      case _WARNA_PENA:
        keyCairoWarnaPena();
      break;

      case _WARNA_TRANSPARAN:
        keyCairoWarnaTransparan();
      break;

      case _PUDAR_PENA:
        keyCairoPudarPena();
      break;

      case _PINDAH_PENA:
        keyCairoPindahPena();
      break;

      case _GESER_PENA:
        keyCairoGeserPena();
      break;

      case _KLIP_PENA:
        keyCairoKlipPena();
      break;

      case _KLIP_LINGKARAN:
        keyCairoKlipLingkaran();
      break;

      case _KLIP_KOTAK:
        keyCairoKlipKotak();
      break;

      case _GORES_PENA:
        keyCairoGoresPena();
      break;

      case _GORES_PENA_JAGA:
        keyCairoGoresPenaJaga();
      break;

      case _LUKIS_PENA:
        keyCairoLukisPena();
      break;

      case _ISI_PENA:
        keyCairoIsiPena();
      break;

      case _ISI_PENA_JAGA:
        keyCairoIsiPenaJaga();
      break;

      case _TEBAL_GARIS:
        keyCairoTebalGaris();
      break;

      case _PUCUK_GARIS:
        keyCairoPucukGaris();
      break;

      case _BENTUK_SAMBUNGAN:
        keyCairoBentukSambungan();
      break;

      case _GARIS_PUTUS:
        keyCairoGarisPutus();
      break;

      case _ATRIBUT_TEKS:
        keyCairoAtributTeks();
      break;

      case _LEKUKAN_TEKS:
        keyCairoLekukanTeks();
      break;

      case _LEKUKAN_BARU:
        keyCairoLekukanBaru();
      break;

      case _TUTUP_KURVA:
        keyCairoTutupKurva();
      break;

      case _GESER_LATAR:
        keyCairoGeserLatar();
      break;

      case _SKALA_LATAR:
        keyCairoSkalaLatar();
      break;

      case _PUTAR_LATAR:
        keyCairoPutarLatar();
      break;

      case _DETAK_WAKTU:
        keyDetak_Waktu();
      break;

      case _STOP_DETAK:
        // do nothing
      break;

      case _HAPUS_PIXMAP:
        keyCairoHapusPixmap();
      break;

      case _LUKIS_PIXMAP:
        keyCairoLukisPixmap();
      break;

      /*  === GUI GTK Handle ================================= end ==== */
      #endif
      /*  ============================================================= */























	  /*  ============================================================= */
      #ifdef USE_GTK3
	  /*  === GUI GTK Handle =============================== start ==== */

	  case _PAKAI_LAYAR:
		  //we need to initialize all these functions so that gtk knows
		  //to be thread-aware

		  //printf("call pakai_layar in GTK3\n");

		  g_log_set_handler("Gdk", G_LOG_LEVEL_CRITICAL, my_log_handler, NULL);


          #ifdef WIN32
		  if (!g_thread_supported()){
			  g_thread_init(NULL);
		  }

		  //gdk_threads_init(); // Not Work with GTK3
		  //gdk_threads_enter(); // Not Work with GTK3
          #endif

		  //gtk_set_locale(); // Not Work with GTK3

		  gtk_init(NULL, NULL);
		  break;

	  case _KIBAR_LAYAR:
		  gtk_main();
		  //gdk_threads_leave(); // Not Work with GTK3
		  break;

	  case _TAMPIL_LAYAR:
		  keyTampil_Layar();
		  break;

	  case _TAMPIL_ELEMEN:
		  keyTampil_Elemen();
		  break;

	  case _SEMBUNYI_ELEMEN:
		  keySembunyi_Elemen();
		  break;

	  case _TITEL_LAYAR:
		  keyTitelLayar();
		  break;

	  case _LUAS_LAYAR:
		  keyLuasLayar();
		  break;

	  case _LOGO_LAYAR:
		  keyLogoLayar();
		  break;

	  case _HIAS_LAYAR:
		  keyHiasLayar();
		  break;

	  case _HIAS_LAYAR_GULUNG:
		  keyHiasLayarGulung();
		  break;

	  case _HIAS_ALAS:
		  keyHiasAlas();
		  break;

	  case _ISI_ALAS_TEGAK:
		  keyIsiAlasTegak();
		  break;

	  case _SET_WARNAHURUF:
		  keySetWarnaHuruf();
		  break;

	  case _SET_WARNADASAR:
		  keySetWarnaDasar();
		  break;

	  case _SET_JENISHURUF:
		  keySetJenisHuruf();
		  break;

	  case _SET_PILIHAN:
		  keySetPilihan();
		  break;

		  // ////////////////////////////////////////////////
	  case _AKSI_TUTUP_PROGRAM:
		  keyAksi_Tutup_Program(); // END Program
		  break;

	  case _AKSI_TUTUP_LAYAR:
		  keyAksi_Tutup_Layar();   // Just Close Win
		  break;

	  case _AKSI_FUNGSI:
		  keyAksi_Fungsi();
		  break;

	  case _AKSI_TEKAN_KETIK:
		  keyAksi_Tekan_Papanketik();
		  break;

	  case _AKSI_LEPAS_KETIK:
		  keyAksi_Lepas_Papanketik();
		  break;

	  case _AKSI_TEKAN_MOUSE:
		  keyAksi_Tekan_Penunjuk();
		  break;

	  case _AKSI_LEPAS_MOUSE:
		  keyAksi_Lepas_Penunjuk();
		  break;

	  case _AKSI_MOUSE_BERGERAK:
		  keyAksi_Penunjuk_Bergerak();
		  break;

	  case _AKSI_RAMBU_INFO:
		  keyAksi_Rambu_Info();
		  break;

	  case _AKSI_RAMBU_AWAS:
		  keyAksi_Rambu_Awas();
		  break;

	  case _AKSI_RAMBU_SALAH:
		  keyAksi_Rambu_Salah();
		  break;

	  case _AKSI_JATIDIRI:
		  keyAksi_Lencana_Jatidiri();
		  break;


		  // ////////////////////////////////////////////////

	  case _AKSI_SIAP_CETAK:
		  keyAksi_SiapPrint();
		  break;

	  case _AKSI_CETAK_TEKS:
		  keyAksi_PrintTeks();
		  break;

	  case _MULAI_CETAK:
		  keyMulaiCetak();
		  break;

	  case _SET_OPERASI_CETAK:
		  keySetOperasiCetak();
		  break;

	  case _TULIS_TEKS_CETAK:
		  keyTulisTeksCetak();
		  break;

		  // ////////////////////////////////////////////////

	  case _SUBMENU:
		  keySubMenu();
		  break;

	  case _TAMBAH_MENU:
		  keyTambahMenu();
		  break;

	  case _AKHIR_MENU:
		  keyAkhirMenu();
		  break;

	  case _SUSUN_MENU:
		  keySusunMenu();
		  break;

	  case _TAMBAH_AKSELERASI:
		  keyTambahAkselerasi();
		  break;

	  case _SET_SENSITIF:
		  keySetSensitif();
		  break;

	  case _TAMPIL_POPUP:
		  keyTampil_Popup();
		  break;

	  case _SUSUN_PAPAN_STATUS:
		  keySusunPapanStatus();
		  break;

		  // -----------------------------------------------

	  case _RAMBU_INFO:
		  keyRambuInfo();
		  break;

	  case _RAMBU_SALAH:
		  keyRambuSalah();
		  break;

	  case _RAMBU_AWAS:
		  keyRambuAwas();
		  break;

		  // ////////////////////////////////////////////////

	  case _SET_LABEL:
		  keyWinSetLabel();
		  break;

	  case _SET_TOMBOL:
		  keyWinSetTombol();
		  break;

	  case _SET_MASUKAN:
		  keyWinSetMasukan();
		  break;

	  case _SET_TIPS:
		  keyWinSetToolTip();
		  break;

	  case _SET_KERTAS:
		  keyWinSetKertas();
		  break;

	  case _SET_STATUS:
		  keySetPapanStatus();
		  break;

	  case _HAPUS_STATUS:
		  keyHapusPapanStatus();
		  break;

	  case _TABEL_ATRIBUT:
		  keyWinTabelAtribut();
		  break;

	  case _TABEL_DATA:
		  keyWinTabelData();
		  break;

	  case _HAPUS_SEL_TABEL:
		  keyWinHapusSelTabel();
		  break;

	  case _TULIS_SEL_TABEL:
		  keyWinTulisSelTabel();
		  break;

	  case _TULIS_TABEL:
		  keyWinTulisTabel();
		  break;

	  case _SIMPAN_TEKS:
		  keySimpanTeks();
		  break;

	  case _ISI_PUNDI_TEKS:
		  keyIsiPundiTeks();
		  break;

	  case _ISI_TEKS_RAMPUNG:
		  keyIsiTeksRampung();
		  break;

	  case _SET_TEKS_RAMPUNG:
		  keySetTeksRampung();
		  break;

	  case _HAPUS_TEKS_TERPILIH:
		  keyHapusTeksTerpilih();
		  break;

	  case _SALIN_TEKS_PAPANKLIP:
		  keySalinTeksPapanklip();
		  break;

	  case _POTONG_TEKS_PAPANKLIP:
		  keyPotongTeksPapanklip();
		  break;

	  case _UNDUH_TEKS_PAPANKLIP:
		  keyUnduhTeksPapanklip();
		  break;

	  case _TANGGALAN:
		  keyWinTanggalan();
		  break;

	  case _LEMBAR_BUKU:
		  keyLembarBuku();
		  break;

	  case _TAB_BUKU:
		  keyTabBuku();
		  break;

	  case _TAMBAH_RANTING:
		  keyTambahRanting();
		  break;

	  case _WARNADASAR_SEL:
		  keyWarnaDasarRanting();
		  break;

	  case _WARNAHURUF_SEL:
		  keyWarnaHurufRanting();
		  break;

	  case _JENISHURUF_SEL:
		  keyJenisHurufRanting();
		  break;

		  // === Cairo Handle =================================
	  case _AKSI_EKSPOS:
		  keyAksi_Ekspos();
		  break;

	  case _AKSI_ATUR:
		  keyAksi_Atur();
		  break;

	  case _EKSPOS_KANVAS:
		  keyEksposKanvas();
		  break;

	  case _LUKIS_TEKS:
		  keyCairoTeks();
		  break;

	  case _LUKIS_GARIS:
		  keyCairoGaris();
		  break;

	  case _LUKIS_KOTAK:
		  keyCairoKotak();
		  break;

	  case _LUKIS_KOTAK_ISI:
		  keyCairoKotakIsi();
		  break;

	  case _LUKIS_LINGKARAN:
		  keyCairoLingkaran();
		  break;

	  case _LUKIS_LINGKARAN_ISI:
		  keyCairoLingkaranIsi();
		  break;

	  case _HAPUS_LATAR:
		  keyCairoHapusLatar();
		  break;

	  case _HAPUS_BIDANG:
		  keyCairoHapusBidang();
		  break;

	  case _HAPUS_POLA:
		  keyCairoHapusPola();
		  break;

	  case _POLA_WARNA:
		  keyCairoPolaWarna();
		  break;

	  case _SET_ASAL:
		  keyCairoSetAsal();
		  break;

	  case _SET_ASALBIDANG:
		  keyCairoSetAsalBidang();
		  break;

	  case _SIMPAN_LUKISAN:
		  keyCairoSimpanLukisan();
		  break;

	  case _WARNA_PENA:
		  keyCairoWarnaPena();
		  break;

	  case _WARNA_TRANSPARAN:
		  keyCairoWarnaTransparan();
		  break;

	  case _PUDAR_PENA:
		  keyCairoPudarPena();
		  break;

	  case _PINDAH_PENA:
		  keyCairoPindahPena();
		  break;

	  case _GESER_PENA:
		  keyCairoGeserPena();
		  break;

	  case _KLIP_PENA:
		  keyCairoKlipPena();
		  break;

	  case _KLIP_LINGKARAN:
		  keyCairoKlipLingkaran();
		  break;

	  case _KLIP_KOTAK:
		  keyCairoKlipKotak();
		  break;

	  case _GORES_PENA:
		  keyCairoGoresPena();
		  break;

	  case _GORES_PENA_JAGA:
		  keyCairoGoresPenaJaga();
		  break;

	  case _LUKIS_PENA:
		  keyCairoLukisPena();
		  break;

	  case _ISI_PENA:
		  keyCairoIsiPena();
		  break;

	  case _ISI_PENA_JAGA:
		  keyCairoIsiPenaJaga();
		  break;

	  case _TEBAL_GARIS:
		  keyCairoTebalGaris();
		  break;

	  case _PUCUK_GARIS:
		  keyCairoPucukGaris();
		  break;

	  case _BENTUK_SAMBUNGAN:
		  keyCairoBentukSambungan();
		  break;

	  case _GARIS_PUTUS:
		  keyCairoGarisPutus();
		  break;

	  case _ATRIBUT_TEKS:
		  keyCairoAtributTeks();
		  break;

	  case _LEKUKAN_TEKS:
		  keyCairoLekukanTeks();
		  break;

	  case _LEKUKAN_BARU:
		  keyCairoLekukanBaru();
		  break;

	  case _TUTUP_KURVA:
		  keyCairoTutupKurva();
		  break;

	  case _GESER_LATAR:
		  keyCairoGeserLatar();
		  break;

	  case _SKALA_LATAR:
		  keyCairoSkalaLatar();
		  break;

	  case _PUTAR_LATAR:
		  keyCairoPutarLatar();
		  break;

	  case _DETAK_WAKTU:
		  keyDetak_Waktu();
		  break;

	  case _STOP_DETAK:
		  // do nothing
		  break;

	  case _HAPUS_PIXMAP:
		  //keyCairoHapusPixmap();
		  break;

	  case _LUKIS_PIXMAP:
		  //keyCairoLukisPixmap();
		  break;

	  /*  === GUI GTK3 Handle ================================= end ==== */
      #endif
	  /*  ============================================================= */





      /*  ============================================================= */
      #ifdef USE_PDF
      /*  === PDF Handle     =============================== start ==== */

      case _PDF_SETHURUF:
        keyPdfSetHuruf();
      break;

      case _PDF_TEKS:
        keyPdfTeks();
      break;

      case _PDF_AWALTEKS:
        keyPdfAwalTeks();
      break;

      case _PDF_AKHIRTEKS:
        keyPdfAkhirTeks();
      break;

      case _PDF_SIMPANPDF:
        keyPdfSimpanPdf();
      break;

      case _PDF_HAPUS:
        keyPdfHapus();
      break;

      case _PDF_GARIS:
        keyPdfGaris();
      break;

      case _PDF_KOTAK:
        keyPdfKotak();
      break;

      case _PDF_TEBALGARIS:
        keyPdfTebalGaris();
      break;

      case _PDF_WARNAGARIS:
        keyPdfWarnaGaris();
      break;

      case _PDF_WARNAHURUF:
        keyPdfWarnaHuruf();
      break;

      case _PDF_JARAKHURUF:
        keyPdfJarakHuruf();
      break;

      case _PDF_JARAKKATA:
        keyPdfJarakKata();
      break;

      case _PDF_PNG:
        keyPdfPng();
      break;

      case _PDF_JPG:
        keyPdfJpg();
      break;

      /*  === PDF Handle     ================================= end ==== */
      #endif
      /*  ============================================================= */

      /*  ============================================================= */

      #ifdef USE_CGI
      /*  === CGI Handle     =============================== start ==== */

      case _POST_CGI:
        // printf("DEBUG: case POST CGI\n");
          getPostCgi();
      break;

      /*  === CGI Handle     ================================= end ==== */
      #endif
      /*  ============================================================= */

      #ifdef USE_WEBSTYLE
      /*  === WEBSTYLE Handle     =============================== start ==== */

	  case _SEDIA_WEBSTYLE:
        keySEDIA_WEBSTYLE();
      break;

      case _HTML_AWAL:
       keyHTML_AWAL();
      break;

      case _HTML_AKHIR:
        printf("</div> \n");   // end of <div class='con'>
        printf("</body> \n");  // end of <body>
        printf("</html> \n");
        fflush( stdout );
      break;

      case _HTML_STYLE:
       keyHTML_STYLE();
      break;

      case _HTML_MENU_AWAL:
        printf("<div class='menu'> \n");
        fflush( stdout );
      break;

      case _HTML_MENU_AKHIR:
        printf("</div> \n");
        fflush( stdout );
      break;

      case _HTML_MENU:
       keyHTML_MENU();
      break;

      case _HTML_HAKCIPTA:
       keyHTML_HAKCIPTA();
      break;

      case _ISIWEB_AWAL:
        printf("<div class='main'> \n");
        fflush( stdout );
      break;

      case _ISIWEB_AKHIR:
        printf("</div> \n\n");
        fflush( stdout );
      break;

      case _ISIWEB_TITEL:
       keyISIWEB_TITEL();
      break;

      /*  === JS AJAX Graphic Handle ============================== start ==== */

      case _HTMLJS_GAMBARSTYLE:
        keyHTMLJS_GAMBARSTYLE();
      break;

      case _HTMLJS_AWALGAMBAR:
        printf("<script type=\"text/javascript\"> \n");
        printf("function myDrawFunction() { \n");
        fflush( stdout );
      break;

      case _HTMLJS_AKHIRGAMBAR:
        printf("} \n");
        printf("var jg_doc = new jsGraphics(); \n");
        printf("myDrawFunction(); \n");
        printf("</script> \n");
        fflush( stdout );
      break;

      case _HTMLJS_WARNA:
        keyHTMLJS_WARNA();
      break;

      case _HTMLJS_GARIS:
        keyHTMLJS_GARIS();
      break;

      case _HTMLJS_KOTAK:
        keyHTMLJS_KOTAK();
      break;

      case _HTMLJS_KOTAKISI:
        keyHTMLJS_KOTAKISI();
     break;

      case _HTMLJS_LINGKARAN:
        keyHTMLJS_LINGKARAN();
      break;

      case _HTMLJS_LINGKARANISI:
        keyHTMLJS_LINGKARANISI();
      break;

      case _HTMLJS_HURUFBESAR:
        printf(" jg_doc. setFont(\"arial\",\"18px\",Font.PLAIN);  \n");
        fflush( stdout );
      break;

      case _HTMLJS_HURUFSEDANG:
        printf(" jg_doc. setFont(\"arial\",\"11px\",Font.PLAIN);  \n");
        fflush( stdout );
      break;

      case _HTMLJS_HURUFSEDANGTEBAL:
        printf(" jg_doc. setFont(\"arial\",\"11px\",Font.BOLD);  \n");
        fflush( stdout );
      break;

      case _HTMLJS_HURUFSEDANGMIRING:
        printf(" jg_doc. setFont(\"arial\",\"11px\",Font.ITALIC);  \n");
        fflush( stdout );
      break;

      case _HTMLJS_HURUFKECIL:
        printf(" jg_doc. setFont(\"arial\",\"9px\",Font.PLAIN);  \n");
        fflush( stdout );
      break;

      case _HTMLJS_TULIS:
        keyHTMLJS_TULIS();
      break;

      /*  === WEBSTYLE Handle     ================================= end ==== */
      #endif
      /*  ============================================================= */

      case _GLOBAL:
        // printf("DEBUG: case GLOBAL\n");

		do {
          getlex();

          memset(&ident,'\0',sizeof(ident));
          strcpy(ident, lex.detail.ident);

          // printf(" GLOBAL %s lex.type %d\n", ident, lex.type);
	      if( lex.type == TYPE_IDENT ){
            memset(&tmpdat,'\0',sizeof(tmpdat));
			tmpdat.scope = 2;  // set to GLOBAL 
            ValLabel( ident , sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
          } else
	      if( lex.type == TYPE_ARRAY ){
            memset(&ident,'\0',sizeof(ident));

			getArrayName(lex.detail.array_str, (char *)&ident);

            memset(&tmpdat,'\0',sizeof(tmpdat));
			tmpdat.scope = 2;  // set to GLOBAL 
			//printf(" GLOBAL %s scope %d\n", ident, tmpdat.scope);
            ValLabel( ident , sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
          } else {
            Error("kode perintah GLOBAL salah");
          }

		  // skip comma if any
          getlex();

		}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );
		ungetlex();

      break;

      case _BENDA:
        // printf("DEBUG: case BENDA\n");

		do {
          getlex();

          memset(&ident,'\0',sizeof(ident));
          strcpy(ident, lex.detail.ident);

          // printf(" BENDA %s lex.type %d\n", ident, lex.type);
	      if( lex.type == TYPE_IDENT ){
            memset(&tmpdat,'\0',sizeof(tmpdat));
            tmpdat.datatype = 31;  // Class Instance
            ValLabel( ident , sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
          } else {
            Error("kode perintah BENDA salah");
          }

		  // skip comma if any
          getlex();

		}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );
		ungetlex();

      break;

      case _DEF_BENDA:
        // printf("DEBUG: case DEF_BENDA\n");
        do {
          getlex();
        } while(lex.detail.string[0] != ']');

      break;

	  case TYPE_OBJECT:
        // printf("DEBUG: case TYPE_OBJECT\n");
	    strcpy( ident, lex.detail.object_str );
		keyObject(ident);
	  break;

	  case TYPE_OBJECT_FUNC:
        //printf("DEBUG: case TYPE_OBJECT_FUNC\n");
	    strcpy( ident, lex.detail.object_str );
		keyObjectFunc(ident);
	  break;


      case _END:
	    lex.type = _EOF;
		BaikGarbageCollection();
	  break;

      case TYPE_SYM:
        if( lex.type == TYPE_SYM && lex.detail.symbol == '&' )  {
	      strcpy( ident, "");
		  // sub routine
          keySub(ident);
		}

	  break;

      case _UNTAI:
        strcpy( ident, "");
		// sub routine
        keyUntaian(ident);
	  break;

      case TYPE_ARRAY:
        strcpy( ident, lex.detail.array_str);
		// sub routine
        keyArray(ident);
	  break;


      case TYPE_IDENT:
        // printf("case IDENT \n");
        if(currentClass != NULL && strlen(currentClass) > 0) {
           sprintf(ident, "%s->%s", currentClass, lex.detail.ident);
	} else {
          strcpy( ident, lex.detail.ident );             // keep ident
	}
        //printf (" lex ident %s\n", ident);

	getlex();
        //printf (" after ident %c\n",lex.detail.symbol);

        if( lex.type == _EOF )
          Error("TYPE_IDENT salah: diluar perkiraan");

	if( lex.detail.symbol == '=' || lex.detail.symbol == '+' || lex.detail.symbol == '-') {
          // substitusi atau ++ atau --
	  if( lex.detail.symbol == '+' )  {
	    plusplus = 1;
	  } else if( lex.detail.symbol == '-' )  {
	    plusplus = -1;
	  }
	} else {
	  Error("salah! kata fungsi tidak dikenal, bukan masukan atau operasi matematik");
	}

        getlex();

	if( lex.detail.symbol == '&' && lex.type == TYPE_SYM)  {
	  // sub routine
          keySub(ident);

	} else if( lex.detail.symbol == '+' && lex.type == TYPE_SYM)  { // plusplus
	  if(plusplus == 1) {
	    // printf("plusplus \n");
            tmpdat = ValLabel( ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
		if(tmpdat.ident != NULL && tmpdat.datatype == 0) {
		  tmpdat.val++;
              ValLabel( ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
		} else
		if(tmpdat.ident != NULL && tmpdat.datatype == 1) {
		  tmpdat.floatdata = tmpdat.floatdata + 1.0;
              ValLabel( ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
		}
	  }
	} else if( lex.detail.symbol == '-' && lex.type == TYPE_SYM)  { // minmin
	  if(plusplus == -1) {
	    // printf("minmin \n");
            tmpdat = ValLabel( ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
		if(tmpdat.ident != NULL && tmpdat.datatype == 0) {
		  tmpdat.val--;
              ValLabel( ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
		} else
		if(tmpdat.ident != NULL && tmpdat.datatype == 1) {
		  tmpdat.floatdata = tmpdat.floatdata + 1.0;
              ValLabel( ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
		}
	  } else {
            // printf("expression ident with minus\n");
            getlex();

            if(lex.type == TYPE_NUM) {
              lex.detail.num = 0 - lex.detail.num;
              tmpdat.val      = lex.detail.num;
              tmpdat.datatype = 0;
            } else if(lex.type == TYPE_DBL) {
              lex.detail.dblnum =  0.0 - lex.detail.dblnum;
              tmpdat.floatdata = lex.detail.dblnum;
              tmpdat.datatype  = 1;
            } else if(lex.type == TYPE_ARRAY) {
              strcpy(valdat.array_str, lex.detail.array_str);
              getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
              getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

              if(currentClass != NULL && strlen(currentClass) > 0) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                #endif

                //printf("construct class var: %s\n", class_tmpvar);
                memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));
                strcpy(valdat.array_name, class_tmpvar);
              }

              // printf("factor ARRAY name: %s\n", valdat.array_name);

              if(isdigit(valdat.array_idx[0])) {
                /* printf("show digit\n"); */
                idx = atoi (valdat.array_idx);
              } else {
                /* printf("show NOT digit\n"); */
                /* Read index param */
                datx = ValLabel( valdat.array_idx, sub_deep, datx, VAL_FLAG_SEARCH_R );

                if(datx.datatype==0)
                  idx = datx.val;
                else
                  Error("Untaian salah masukan");
              }

              // get real value
              valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              //ltoa(idx, valdat.array_idx, 10);
              #ifdef WIN32
               #ifndef S_SPLINT_S
               sprintf_s(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #else
               snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
               #endif
              #else
              snprintf(valdat.array_idx, sizeof(valdat.array_idx),"%d", idx);
              #endif

              if(idx < 0 || idx > MAX_ARRAY)
                Error("ukuran Untaian tidak sesuai kapasitas");

              /* printf("array substitution\n"); */
              if(valdat.datatype == 6) {
                tmpdat.val = 0 - get_int_array(valdat, idx);
                tmpdat.datatype = 0;
              }
              else
              if(valdat.datatype == 7) {
                tmpdat.floatdata = 0.0 - get_dbl_array(valdat, idx);
                tmpdat.datatype  = 1;
              }
	      else {
                Error("Salah bentuk bilangan negatif");
			  }

            } else {
              Error("Salah bentuk bilangan negatif");
            }

            ValLabel( ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
		  }
        } else {
          //printf("expression ident\n");
	  memset(&tmpdat, '\0', sizeof(tmpdat));
          strcpy(tmpdat.ident, ident);

          ungetlex();
          tmpdat = expression();

          //printf("%s get expression: %d\n", ident, tmpdat.val);
          //printf(" get type: %d\n", tmpdat.datatype);
          //printf(" deep: %d\n", sub_deep);

          ValLabel( ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_W );

          //printf("saving %s ...\n", ident);
        }
	break;

      case _EOF:

	break;

      default:
	    Error("Perintah tidak dimengerti: %s , nilai kode %d ", lex.detail.ident, lex.type);
	break;
    
    }

  //memset(&tmpdat, '\0', sizeof(tmpdat));
  //memset(&valdat, '\0', sizeof(valdat));


}

