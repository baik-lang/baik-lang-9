// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// sewing a new history ...
// my coding, my way, my inspiration ...
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

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

#ifdef WINDOWS
#pragma warning(disable:4996)
#endif

char *ToUpper(char *s);
char *ToLower(char *s);

extern BAIK_LEX lex;
extern BAIK_ADDR pg;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// ///////////////////
// lex_ident
// ///////////////////

int lex_ident( void )
{
  char c='\0';
  int i = 0;
  
  while( isalnum( c = pg.source[pg.pt++] ) || c == '_' ){

    if( i > (MAX_IDENT_LEN - 1) )
      Error("melebihi kapasitas MAX_IDENT_LEN", MAX_IDENT_LEN );

    lex.detail.ident[i++] = (char)c;
  }
  lex.detail.ident[i] = '\0';
  pg.pt--;

  lex.type = TYPE_IDENT;
  
  // //////////////////////////////////////////////////////////////////////

  if( ! strcmp(lex.detail.ident, "TULIS") || ! strcmp(lex.detail.ident, "tulis")
      || ! strcmp(lex.detail.ident, "Tulis"))    lex.type = _TULIS;

  if( ! strcmp(lex.detail.ident, "TULIS_RINCI") || ! strcmp(lex.detail.ident, "tulis_rinci")
      || ! strcmp(lex.detail.ident, "Tulis_Rinci")|| ! strcmp(lex.detail.ident, "Tulis_rinci")
      )  lex.type = _TULIS_RINCI;

  if( ! strcmp(lex.detail.ident, "TULISLOG") || ! strcmp(lex.detail.ident, "tulislog")
      || ! strcmp(lex.detail.ident, "Tulislog"))    lex.type = _TULISLOG;

  if(!strcmp(lex.detail.string, "TULIS_ARSIP") || !strcmp(lex.detail.string, "tulis_arsip")
      || !strcmp(lex.detail.string, "Tulis_arsip") ) lex.type = _TULIS_ARSIP;

  if( ! strcmp(lex.detail.ident, "PERINTAH") || ! strcmp(lex.detail.ident, "perintah")
      || ! strcmp(lex.detail.ident, "Perintah"))    lex.type = _PERINTAH;

  if( ! strcmp(lex.detail.ident, "MUSIK") || ! strcmp(lex.detail.ident, "musik")
      || ! strcmp(lex.detail.ident, "Musik"))    lex.type = _MUSIK;
      
  if( ! strcmp(lex.detail.ident, "MUSIK_PENGHIAS") || ! strcmp(lex.detail.ident, "musik_penghias")
      || ! strcmp(lex.detail.ident, "Musik_Penghias"))    lex.type = _MUSIK_BGM;      

  if( ! strcmp(lex.detail.ident, "JENDELA") || ! strcmp(lex.detail.ident, "jendela")
      || ! strcmp(lex.detail.ident, "Jendela"))    lex.type = _JENDELA;

  if( ! strcmp(lex.detail.ident, "TUNGGU") || ! strcmp(lex.detail.ident, "tunggu")
      || ! strcmp(lex.detail.ident, "Tunggu"))    lex.type = _TUNGGU;

  if( ! strcmp(lex.detail.ident, "KONEKSI") || ! strcmp(lex.detail.ident, "koneksi")
      || ! strcmp(lex.detail.ident, "Koneksi"))    lex.type = _KONEKSI;


  if( ! strcmp(lex.detail.ident, "TUTUP") || ! strcmp(lex.detail.ident, "tutup")
      || ! strcmp(lex.detail.ident, "Tutup"))    lex.type = _TUTUP;


  if( ! strcmp(lex.detail.ident, "SURAT") || ! strcmp(lex.detail.ident, "surat")
      || ! strcmp(lex.detail.ident, "Surat"))    lex.type = _SURAT;
  
  if( ! strcmp(lex.detail.ident, "MASUK") || ! strcmp(lex.detail.ident, "masuk")
      || ! strcmp(lex.detail.ident, "Masuk"))    lex.type = _MASUK;
  
  if( ! strcmp(lex.detail.ident, "KALAU") || ! strcmp(lex.detail.ident, "kalau")
      || ! strcmp(lex.detail.ident, "Kalau") || ! strcmp(lex.detail.ident, "JIKA")
	  || ! strcmp(lex.detail.ident, "jika") || ! strcmp(lex.detail.ident, "Jika")
	  )    lex.type = _KALAU;

  if( ! strcmp(lex.detail.ident, "LAINKALAU") || ! strcmp(lex.detail.ident, "lainkalau")
      || ! strcmp(lex.detail.ident, "LainKalau") || ! strcmp(lex.detail.ident, "LAINJIKA")
	  || ! strcmp(lex.detail.ident, "lainjika") || ! strcmp(lex.detail.ident, "LainJika")
	  )    lex.type = _LAINKALAU;
  
  if( ! strcmp(lex.detail.ident, "MAKA") || ! strcmp(lex.detail.ident, "maka")
      || ! strcmp(lex.detail.ident, "Maka"))    lex.type = _MAKA;

  if( ! strcmp(lex.detail.ident, "LAINNYA") || ! strcmp(lex.detail.ident, "lainnya")
      || ! strcmp(lex.detail.ident, "Lainnya"))    lex.type = _LAINNYA;

  if( ! strcmp(lex.detail.ident, "STOPKALAU") || ! strcmp(lex.detail.ident, "stopkalau")
      || ! strcmp(lex.detail.ident, "Stopkalau") || ! strcmp(lex.detail.ident, "HABIS") 
      || ! strcmp(lex.detail.ident, "habis") || ! strcmp(lex.detail.ident, "Habis")
      || ! strcmp(lex.detail.ident, "AKHIRKALAU") || ! strcmp(lex.detail.ident, "akhirkalau")
      || ! strcmp(lex.detail.ident, "Akhirkalau") || ! strcmp(lex.detail.ident, "AkhirKalau")
      || ! strcmp(lex.detail.ident, "AKHIRJIKA") || ! strcmp(lex.detail.ident, "akhirjika")
      || ! strcmp(lex.detail.ident, "Akhirjika") || ! strcmp(lex.detail.ident, "AkhirJika"))	  
   lex.type = _STOPKALAU;

  if( ! strcmp(lex.detail.ident, "SELAGI") || ! strcmp(lex.detail.ident, "selagi")
      || ! strcmp(lex.detail.ident, "Selagi"))    lex.type = _SELAGI;
  
  if( ! strcmp(lex.detail.ident, "LAKUKAN") || ! strcmp(lex.detail.ident, "lakukan")
      || ! strcmp(lex.detail.ident, "Lakukan"))    lex.type = _LAKUKAN;

  if( ! strcmp(lex.detail.ident, "BALIKLAGI") || ! strcmp(lex.detail.ident, "baliklagi")
      || ! strcmp(lex.detail.ident, "Baliklagi"))    lex.type = _BALIKLAGI;

  if( ! strcmp(lex.detail.ident, "UNTUK") || ! strcmp(lex.detail.ident, "untuk")
      || ! strcmp(lex.detail.ident, "Untuk"))    lex.type = _UNTUK;
  
  if( ! strcmp(lex.detail.ident, "ULANG") || ! strcmp(lex.detail.ident, "ulang")
      || ! strcmp(lex.detail.ident, "Ulang"))    lex.type = _ULANG;

  if( ! strcmp(lex.detail.ident, "LAGI") || ! strcmp(lex.detail.ident, "lagi")
      || ! strcmp(lex.detail.ident, "Lagi"))    lex.type = _LAGI;
  
  if( ! strcmp(lex.detail.ident, "LONCATLABEL") || ! strcmp(lex.detail.ident, "loncatlabel")
      || ! strcmp(lex.detail.ident, "LoncatLabel"))    lex.type = _LONCATLABEL;

  if( ! strcmp(lex.detail.ident, "SUB") || ! strcmp(lex.detail.ident, "sub")
      || ! strcmp(lex.detail.ident, "Sub") || ! strcmp(lex.detail.ident, "FUNGSI") 
      || ! strcmp(lex.detail.ident, "fungsi") || ! strcmp(lex.detail.ident, "Fungsi"))
   lex.type = _SUB;

  if( ! strcmp(lex.detail.ident, "BALIK") || ! strcmp(lex.detail.ident, "balik")
      || ! strcmp(lex.detail.ident, "Balik"))    lex.type = _RETURN;
  
  if( ! strcmp(lex.detail.ident, "LONCAT") || ! strcmp(lex.detail.ident, "loncat")
      || ! strcmp(lex.detail.ident, "Loncat"))    lex.type = _LONCAT;
  
  if( ! strcmp(lex.detail.ident, "END") || ! strcmp(lex.detail.ident, "end")
      || ! strcmp(lex.detail.ident, "End")  || ! strcmp(lex.detail.ident, "TAMAT") 
      || ! strcmp(lex.detail.ident, "tamat") || ! strcmp(lex.detail.ident, "Tamat"))
    lex.type = _END;

  if( ! strcmp(lex.detail.ident, "POST_CGI") || ! strcmp(lex.detail.ident, "post_cgi")
      || ! strcmp(lex.detail.ident, "Post_Cgi") || ! strcmp(lex.detail.ident, "PAKAI_CGI")
	  || ! strcmp(lex.detail.ident, "pakai_cgi") || ! strcmp(lex.detail.ident, "Pakai_Cgi")
	  )    lex.type = _POST_CGI;


  if( ! strcmp(lex.detail.ident, "UNTAIAN") || ! strcmp(lex.detail.ident, "untaian")
      || ! strcmp(lex.detail.ident, "Untaian") || !strcmp(lex.detail.ident, "LARIK")
      || ! strcmp(lex.detail.ident, "larik") || ! strcmp(lex.detail.ident, "Larik"))
    lex.type = _UNTAI;

  if( ! strcmp(lex.detail.ident, "HAPUS") || ! strcmp(lex.detail.ident, "hapus")
      || ! strcmp(lex.detail.ident, "Hapus"))    lex.type = _HAPUS;


  if( ! strcmp(lex.detail.ident, "DAN") || ! strcmp(lex.detail.ident, "dan")
      || ! strcmp(lex.detail.ident, "Dan"))    lex.type = _DAN;
  
  if( ! strcmp(lex.detail.ident, "ATAU") || ! strcmp(lex.detail.ident, "atau")
      || ! strcmp(lex.detail.ident, "Atau"))    lex.type = _ATAU;
  
  if( ! strcmp(lex.detail.ident, "NOT") || ! strcmp(lex.detail.ident, "not")
      || ! strcmp(lex.detail.ident, "Not") || ! strcmp(lex.detail.ident, "BUKAN")
      || ! strcmp(lex.detail.ident, "bukan") || ! strcmp(lex.detail.ident, "Bukan"))
    lex.type = _NOT;


  if( ! strcmp(lex.detail.ident, "GAMBARGARIS") || ! strcmp(lex.detail.ident, "gambargaris")
      || ! strcmp(lex.detail.ident, "GambarGaris"))    lex.type = _GAMBAR_GARIS;

  if( ! strcmp(lex.detail.ident, "GAMBARGARISPUTUS") || ! strcmp(lex.detail.ident, "gambargarisputus")
      || ! strcmp(lex.detail.ident, "GambarGarisPutus"))    lex.type = _GAMBAR_GARIS_PUTUS;

  if( ! strcmp(lex.detail.ident, "GAMBARPOLIGON") || ! strcmp(lex.detail.ident, "gambarpoligon")
      || ! strcmp(lex.detail.ident, "GambarPoligon"))    lex.type = _GAMBAR_POLIGON;

  if( ! strcmp(lex.detail.ident, "GAMBARPOLIGONISI") || ! strcmp(lex.detail.ident, "gambarpoligonisi")
      || ! strcmp(lex.detail.ident, "GambarPoligonIsi"))    lex.type = _GAMBAR_POLIGON_ISI;

  if( ! strcmp(lex.detail.ident, "GAMBARKOTAK") || ! strcmp(lex.detail.ident, "gambarkotak")
      || ! strcmp(lex.detail.ident, "GambarKotak"))    lex.type = _GAMBAR_KOTAK;

  if( ! strcmp(lex.detail.ident, "GAMBARKOTAKISI") || ! strcmp(lex.detail.ident, "gambarkotakisi")
      || ! strcmp(lex.detail.ident, "GambarKotakIsi"))    lex.type = _GAMBAR_KOTAK_ISI;

  if( ! strcmp(lex.detail.ident, "GAMBARLINGKARAN") || ! strcmp(lex.detail.ident, "gambarlingkaran")
      || ! strcmp(lex.detail.ident, "GambarLingkaran"))    lex.type = _GAMBAR_LINGKARAN;

  if( ! strcmp(lex.detail.ident, "GAMBARLINGKARANISI") || ! strcmp(lex.detail.ident, "gambarlingkaranisi")
      || ! strcmp(lex.detail.ident, "GambarLingkaranIsi"))    lex.type = _GAMBAR_LINGKARAN_ISI;

  if( ! strcmp(lex.detail.ident, "SIMPANGAMBARPNG") || ! strcmp(lex.detail.ident, "simpangambarpng")
      || ! strcmp(lex.detail.ident, "SimpanGambarPng"))    lex.type = _SIMPAN_GAMBAR_PNG;

  if( ! strcmp(lex.detail.ident, "SIMPANGAMBARJPG") || ! strcmp(lex.detail.ident, "simpangambarjpg")
      || ! strcmp(lex.detail.ident, "SimpanGambarJpg"))    lex.type = _SIMPAN_GAMBAR_JPG;

  if( ! strcmp(lex.detail.ident, "HAPUSGAMBAR") || ! strcmp(lex.detail.ident, "hapusgambar")
      || ! strcmp(lex.detail.ident, "HapusGambar"))    lex.type = _HAPUS_GAMBAR;

  if( ! strcmp(lex.detail.ident, "GAMBARHURUF") || ! strcmp(lex.detail.ident, "gambarhuruf")
      || ! strcmp(lex.detail.ident, "GambarHuruf"))    lex.type = _GAMBAR_HURUF;


  if( ! strcmp(lex.detail.ident, "SEDIA_WEBSTYLE") || ! strcmp(lex.detail.ident, "sedia_webstyle")
      || ! strcmp(lex.detail.ident, "Sedia_Webstyle")
      || ! strcmp(lex.detail.ident, "SEDIA_KERTASWEB") || ! strcmp(lex.detail.ident, "sedia_kertasweb")
      || ! strcmp(lex.detail.ident, "Sedia_Kertasweb") || ! strcmp(lex.detail.ident, "Sedia_kertasweb")
      )  lex.type = _SEDIA_WEBSTYLE;

  if( ! strcmp(lex.detail.ident, "HTML_AWAL") || ! strcmp(lex.detail.ident, "html_awal")
      || ! strcmp(lex.detail.ident, "Html_Awal")
      || ! strcmp(lex.detail.ident, "KERTASWEB_AWAL")  || ! strcmp(lex.detail.ident, "kertasweb_awal")
      || ! strcmp(lex.detail.ident, "Kertasweb_Awal")  || ! strcmp(lex.detail.ident, "Kertasweb_awal")
      )  lex.type = _HTML_AWAL;

  if( ! strcmp(lex.detail.ident, "HTML_STYLE") || ! strcmp(lex.detail.ident, "html_style")
      || ! strcmp(lex.detail.ident, "Html_Style")
      || ! strcmp(lex.detail.ident, "KERTASWEB_MODEL")  || ! strcmp(lex.detail.ident, "kertasweb_model")
      || ! strcmp(lex.detail.ident, "Kertasweb_model")  || ! strcmp(lex.detail.ident, "Kertasweb_model")
      )  lex.type = _HTML_STYLE;

  if( ! strcmp(lex.detail.ident, "HTML_MENU_AWAL") || ! strcmp(lex.detail.ident, "html_menu_awal")
      || ! strcmp(lex.detail.ident, "Html_Menu_Awal")
      || ! strcmp(lex.detail.ident, "KERTASWEB_MENU_AWAL") || ! strcmp(lex.detail.ident, "kertasweb_menu_awal")
      || ! strcmp(lex.detail.ident, "Kertasweb_Menu_Awal") || ! strcmp(lex.detail.ident, "Kertasweb_menu_awal")
      )  lex.type = _HTML_MENU_AWAL;

  if( ! strcmp(lex.detail.ident, "HTML_MENU_AKHIR") || ! strcmp(lex.detail.ident, "html_menu_akhir")
      || ! strcmp(lex.detail.ident, "Html_Menu_Akhir")
      || ! strcmp(lex.detail.ident, "KERTASWEB_MENU_AKHIR") || ! strcmp(lex.detail.ident, "kertasweb_menu_akhir")
      || ! strcmp(lex.detail.ident, "Kertasweb_Menu_Akhir") || ! strcmp(lex.detail.ident, "Kertasweb_menu_akhir")
      )  lex.type = _HTML_MENU_AKHIR;

  if( ! strcmp(lex.detail.ident, "HTML_MENU") || ! strcmp(lex.detail.ident, "html_menu")
      || ! strcmp(lex.detail.ident, "Html_Menu")
      || ! strcmp(lex.detail.ident, "KERTASWEB_MENU") || ! strcmp(lex.detail.ident, "kertasweb_menu")
      || ! strcmp(lex.detail.ident, "Kertasweb_Menu") || ! strcmp(lex.detail.ident, "Kertasweb_menu")
      )  lex.type = _HTML_MENU;

  if( ! strcmp(lex.detail.ident, "HTML_HAKCIPTA") || ! strcmp(lex.detail.ident, "html_hakcipta")
      || ! strcmp(lex.detail.ident, "Html_Hakcipta")
      || ! strcmp(lex.detail.ident, "KERTASWEB_HAKCIPTA") || ! strcmp(lex.detail.ident, "kertasweb_hakcipta")
      || ! strcmp(lex.detail.ident, "Kertasweb_Hakcipta") || ! strcmp(lex.detail.ident, "Kertasweb_hakcipta")
      )  lex.type = _HTML_HAKCIPTA;

  if( ! strcmp(lex.detail.ident, "ISIWEB_TITEL") || ! strcmp(lex.detail.ident, "isiweb_titel")
      || ! strcmp(lex.detail.ident, "Isiweb_Titel")
      )  lex.type = _ISIWEB_TITEL;

  if( ! strcmp(lex.detail.ident, "ISIWEB_AWAL") || ! strcmp(lex.detail.ident, "isiweb_awal")
      || ! strcmp(lex.detail.ident, "Isiweb_Awal")
      )  lex.type = _ISIWEB_AWAL;

  if( ! strcmp(lex.detail.ident, "ISIWEB_AKHIR") || ! strcmp(lex.detail.ident, "isiweb_akhir")
      || ! strcmp(lex.detail.ident, "Isiweb_Akhir")
      )  lex.type = _ISIWEB_AKHIR;

  if( ! strcmp(lex.detail.ident, "HTML_AKHIR") || ! strcmp(lex.detail.ident, "html_akhir")
      || ! strcmp(lex.detail.ident, "Html_Akhir")
      || ! strcmp(lex.detail.ident, "KERTASWEB_AKHIR")  || ! strcmp(lex.detail.ident, "Html_Akhir")
      || ! strcmp(lex.detail.ident, "Kertasweb_Akhir")  || ! strcmp(lex.detail.ident, "Kertasweb_akhir")
      )  lex.type = _HTML_AKHIR;

  if( ! strcmp(lex.detail.ident, "KODE") || ! strcmp(lex.detail.ident, "kode") ||
      ! strcmp(lex.detail.ident, "Kode") || ! strcmp(lex.detail.ident, "kode_luar") ||
      ! strcmp(lex.detail.ident, "KODE_LUAR") || ! strcmp(lex.detail.ident, "KODELUAR")
      || ! strcmp(lex.detail.ident, "KodeLuar"))    lex.type = _KODE_LUAR;

  if( ! strcmp(lex.detail.ident, "END_KODE") || ! strcmp(lex.detail.ident, "end_kode")  ||
      ! strcmp(lex.detail.ident, "AKHIR_KODE_LUAR") || ! strcmp(lex.detail.ident, "akhir_kode_luar") ||
      ! strcmp(lex.detail.ident, "Akhir_Kode_Luar") || ! strcmp(lex.detail.ident, "Akhir_kode_luar")
    ) lex.type = _END_KODE_LUAR;

  if( ! strcmp(lex.detail.ident, "PILIH") || ! strcmp(lex.detail.ident, "pilih")
      || ! strcmp(lex.detail.ident, "Pilih"))    lex.type = _PILIH;
  if( ! strcmp(lex.detail.ident, "SAMA") || ! strcmp(lex.detail.ident, "sama")
      || ! strcmp(lex.detail.ident, "Sama"))    lex.type = _SAMA;
  if( ! strcmp(lex.detail.ident, "AKHIRPILIH") || ! strcmp(lex.detail.ident, "akhirpilih")
      || ! strcmp(lex.detail.ident, "Akhirpilih") || ! strcmp(lex.detail.ident, "AkhirPilih") )
      lex.type = _AKHIRPILIH;

  if( ! strcmp(lex.detail.ident, "HTMLJS_GAMBARSTYLE") || ! strcmp(lex.detail.ident, "htmljs_gambarstyle")
      || ! strcmp(lex.detail.ident, "Htmljs_Gambarstyle") || ! strcmp(lex.detail.ident, "Htmljs_GambarStyle")
      || ! strcmp(lex.detail.ident, "KANVASWEB_MODEL") || ! strcmp(lex.detail.ident, "kanvasweb_model")
      || ! strcmp(lex.detail.ident, "Kanvasweb_Model") || ! strcmp(lex.detail.ident, "Kanvasweb_model")
      ) lex.type = _HTMLJS_GAMBARSTYLE;

  if( ! strcmp(lex.detail.ident, "HTMLJS_AWALGAMBAR") || ! strcmp(lex.detail.ident, "htmljs_awalgambar")
      || ! strcmp(lex.detail.ident, "Htmljs_Awalgambar") || ! strcmp(lex.detail.ident, "Htmljs_AwalGambar")
      || ! strcmp(lex.detail.ident, "KANVASWEB_AWALGAMBAR") || ! strcmp(lex.detail.ident, "kanvasweb_awalgambar")
      || ! strcmp(lex.detail.ident, "Kanvasweb_Awalgambar") || ! strcmp(lex.detail.ident, "Kanvasweb_AwalGambar")
      ) lex.type = _HTMLJS_AWALGAMBAR;

  if( ! strcmp(lex.detail.ident, "HTMLJS_AKHIRGAMBAR") || ! strcmp(lex.detail.ident, "htmljs_akhirgambar")
      || ! strcmp(lex.detail.ident, "Htmljs_Akhirgambar") || ! strcmp(lex.detail.ident, "Htmljs_AkhirGambar")
      || ! strcmp(lex.detail.ident, "KANVASWEB_AKHIRGAMBAR") || ! strcmp(lex.detail.ident, "kanvasweb_akhirgambar")
      || ! strcmp(lex.detail.ident, "Kanvasweb_Akhirgambar") || ! strcmp(lex.detail.ident, "Kanvasweb_AkhirGambar")
      ) lex.type = _HTMLJS_AKHIRGAMBAR;

  if( ! strcmp(lex.detail.ident, "HTMLJS_WARNA") || ! strcmp(lex.detail.ident, "htmljs_warna")
      || ! strcmp(lex.detail.ident, "Htmljs_Warna") || ! strcmp(lex.detail.ident, "Htmljs_warna")
      || ! strcmp(lex.detail.ident, "KANVASWEB_WARNA") || ! strcmp(lex.detail.ident, "kanvasweb_warna")
      || ! strcmp(lex.detail.ident, "Kanvasweb_Warna") || ! strcmp(lex.detail.ident, "Kanvasweb_warna")
      ) lex.type = _HTMLJS_WARNA;

  if( ! strcmp(lex.detail.ident, "HTMLJS_GARIS") || ! strcmp(lex.detail.ident, "htmljs_garis")
      || ! strcmp(lex.detail.ident, "Htmljs_Garis") || ! strcmp(lex.detail.ident, "Htmljs_garis")
      || ! strcmp(lex.detail.ident, "KANVASWEB_GARIS") || ! strcmp(lex.detail.ident, "kanvasweb_garis")
      || ! strcmp(lex.detail.ident, "Kanvasweb_Garis") || ! strcmp(lex.detail.ident, "Kanvasweb_garis")
      ) lex.type = _HTMLJS_GARIS;

  if( ! strcmp(lex.detail.ident, "HTMLJS_TEBALGARIS") || ! strcmp(lex.detail.ident, "htmljs_tebalgaris")
      || ! strcmp(lex.detail.ident, "Htmljs_Tebalgaris") || ! strcmp(lex.detail.ident, "Htmljs_TebalGaris")
      || ! strcmp(lex.detail.ident, "KANVASWEB_TEBALGARIS") || ! strcmp(lex.detail.ident, "kanvasweb_tebalgaris")
      || ! strcmp(lex.detail.ident, "Kanvasweb_Tebalgaris") || ! strcmp(lex.detail.ident, "Kanvasweb_TebalGaris")
      ) lex.type = _HTMLJS_TEBALGARIS;

  if( ! strcmp(lex.detail.ident, "HTMLJS_KOTAK") || ! strcmp(lex.detail.ident, "htmljs_kotak")
      || ! strcmp(lex.detail.ident, "Htmljs_Kotak") || ! strcmp(lex.detail.ident, "Htmljs_kotak")
      || ! strcmp(lex.detail.ident, "KANVASWEB_KOTAK") || ! strcmp(lex.detail.ident, "kanvasweb_kotak")
      || ! strcmp(lex.detail.ident, "Kanvasweb_Kotak") || ! strcmp(lex.detail.ident, "Kanvasweb_kotak")
      ) lex.type = _HTMLJS_KOTAK;

  if( ! strcmp(lex.detail.ident, "HTMLJS_KOTAKISI") || ! strcmp(lex.detail.ident, "htmljs_kotakisi")
      || ! strcmp(lex.detail.ident, "Htmljs_KotakIsi") || ! strcmp(lex.detail.ident, "Htmljs_kotakisi")
      || ! strcmp(lex.detail.ident, "KANVASWEB_KOTAKISI") || ! strcmp(lex.detail.ident, "kanvasweb_kotakisi")
      || ! strcmp(lex.detail.ident, "Knavasweb_KotakIsi") || ! strcmp(lex.detail.ident, "Kanvasweb_kotakisi")
      ) lex.type = _HTMLJS_KOTAKISI;

  if( ! strcmp(lex.detail.ident, "HTMLJS_LINGKARAN") || ! strcmp(lex.detail.ident, "htmljs_lingkaran")
      || ! strcmp(lex.detail.ident, "Htmljs_Lingkaran") || ! strcmp(lex.detail.ident, "Htmljs_lingkaran")
      || ! strcmp(lex.detail.ident, "KANVASWEB_LINGKARAN") || ! strcmp(lex.detail.ident, "kanvasweb_lingkaran")
      || ! strcmp(lex.detail.ident, "Kanvasweb_Lingkaran") || ! strcmp(lex.detail.ident, "Kanvasweb_lingkaran")
      ) lex.type = _HTMLJS_LINGKARAN;

  if( ! strcmp(lex.detail.ident, "HTMLJS_LINGKARANISI") || ! strcmp(lex.detail.ident, "htmljs_lingkaranisi")
      || ! strcmp(lex.detail.ident, "Htmljs_LingkaranIsi") || ! strcmp(lex.detail.ident, "Htmljs_lingkaranisi")
      || ! strcmp(lex.detail.ident, "KANVASWEB_LINGKARANISI") || ! strcmp(lex.detail.ident, "kanvasweb_lingkaranisi")
      || ! strcmp(lex.detail.ident, "Kanvasweb_LingkaranIsi") || ! strcmp(lex.detail.ident, "Kanvasweb_lingkaranisi")
      ) lex.type = _HTMLJS_LINGKARANISI;

  if( ! strcmp(lex.detail.ident, "HTMLJS_TULIS") || ! strcmp(lex.detail.ident, "htmljs_tulis")
      || ! strcmp(lex.detail.ident, "Htmljs_Tulis") || ! strcmp(lex.detail.ident, "Htmljs_tulis")
      || ! strcmp(lex.detail.ident, "KANVASWEB_TULIS") || ! strcmp(lex.detail.ident, "kanvasweb_tulis")
      || ! strcmp(lex.detail.ident, "Kanvasweb_Tulis") || ! strcmp(lex.detail.ident, "Kanvasweb_tulis")
      ) lex.type = _HTMLJS_TULIS;

  if( ! strcmp(lex.detail.ident, "HTMLJS_HURUFBESAR") || ! strcmp(lex.detail.ident, "htmljs_hurufbesar")
      || ! strcmp(lex.detail.ident, "Htmljs_HurufBesar") || ! strcmp(lex.detail.ident, "Htmljs_hurufbesar")
      || ! strcmp(lex.detail.ident, "KANVASWEB_HURUFBESAR") || ! strcmp(lex.detail.ident, "kanvasweb_hurufbesar")
      || ! strcmp(lex.detail.ident, "Kanvasweb_HurufBesar") || ! strcmp(lex.detail.ident, "Kanvasweb_hurufbesar")
      ) lex.type = _HTMLJS_HURUFBESAR;

  if( ! strcmp(lex.detail.ident, "HTMLJS_HURUFSEDANG") || ! strcmp(lex.detail.ident, "htmljs_hurufsedang")
      || ! strcmp(lex.detail.ident, "Htmljs_HurufSedang") || ! strcmp(lex.detail.ident, "Htmljs_hurufsedang")
      || ! strcmp(lex.detail.ident, "KANVASWEB_HURUFSEDANG") || ! strcmp(lex.detail.ident, "kanvasweb_hurufsedang")
      || ! strcmp(lex.detail.ident, "Kanvasweb_HurufSedang") || ! strcmp(lex.detail.ident, "Kanvasweb_hurufsedang")
      ) lex.type = _HTMLJS_HURUFSEDANG;

  if( ! strcmp(lex.detail.ident, "HTMLJS_HURUFKECIL") || ! strcmp(lex.detail.ident, "htmljs_hurufkecil")
      || ! strcmp(lex.detail.ident, "Htmljs_HurufKecil") || ! strcmp(lex.detail.ident, "Htmljs_hurufkecil")
      || ! strcmp(lex.detail.ident, "KANVASWEB_HURUFKECIL") || ! strcmp(lex.detail.ident, "kanvasweb_hurufkecil")
      || ! strcmp(lex.detail.ident, "Kanvasweb_HurufKecil") || ! strcmp(lex.detail.ident, "Kanvasweb_hurufkecil")
      ) lex.type = _HTMLJS_HURUFKECIL;

  if( ! strcmp(lex.detail.ident, "HTMLJS_HURUFSEDANGTEBAL") || ! strcmp(lex.detail.ident, "htmljs_hurufsedangtebal")
      || ! strcmp(lex.detail.ident, "Htmljs_HurufSedangTebal") || ! strcmp(lex.detail.ident, "Htmljs_hurufsedangtebal")
      || ! strcmp(lex.detail.ident, "KANVASWEB_HURUFSEDANGTEBAL") || ! strcmp(lex.detail.ident, "kanvasweb_hurufsedangtebal")
      || ! strcmp(lex.detail.ident, "Kanvasweb_HurufSedangTebal") || ! strcmp(lex.detail.ident, "Kanvasweb_hurufsedangtebal")
      ) lex.type = _HTMLJS_HURUFSEDANGTEBAL;

  if( ! strcmp(lex.detail.ident, "HTMLJS_HURUFSEDANGMIRING") || ! strcmp(lex.detail.ident, "htmljs_hurufsedangmiring")
      || ! strcmp(lex.detail.ident, "Htmljs_HurufSedangMiring") || ! strcmp(lex.detail.ident, "Htmljs_hurufsedangmiring")
      || ! strcmp(lex.detail.ident, "KANVASWEB_HURUFSEDANGMIRING") || ! strcmp(lex.detail.ident, "kanvasweb_hurufsedangmiring")
      || ! strcmp(lex.detail.ident, "Kanvasweb_HurufSedangMiring") || ! strcmp(lex.detail.ident, "Kanvasweb_hurufsedangmiring")
      ) lex.type = _HTMLJS_HURUFSEDANGMIRING;


  if( ! strcmp(lex.detail.ident, "KELUARSELAGI") || ! strcmp(lex.detail.ident, "keluarselagi")
      || ! strcmp(lex.detail.ident, "KeluarSelagi") || ! strcmp(lex.detail.ident, "KELUAR_SELAGI")
	  || ! strcmp(lex.detail.ident, "keluar_selagi") || ! strcmp(lex.detail.ident, "Keluar_Selagi")
	  )    lex.type = _KELUARSELAGI;
  if( ! strcmp(lex.detail.ident, "KELUARUNTUK") || ! strcmp(lex.detail.ident, "keluaruntuk")
      || ! strcmp(lex.detail.ident, "KeluarUntuk") || ! strcmp(lex.detail.ident, "KELUAR_UNTUK")
	  || ! strcmp(lex.detail.ident, "keluar_untuk") || ! strcmp(lex.detail.ident, "Keluar_Untuk")
	  )    lex.type = _KELUARUNTUK;
  if( ! strcmp(lex.detail.ident, "LANJUT") || ! strcmp(lex.detail.ident, "lanjut")
      || ! strcmp(lex.detail.ident, "Lanjut"))    lex.type = _LANJUT;

  if( ! strcmp(lex.detail.ident, "BENDA") || ! strcmp(lex.detail.ident, "benda")
      || ! strcmp(lex.detail.ident, "Benda"))    lex.type = _BENDA;
  if( ! strcmp(lex.detail.ident, "DEFINISIBENDA") || ! strcmp(lex.detail.ident, "definisibenda")
      || ! strcmp(lex.detail.ident, "Definisibenda") || ! strcmp(lex.detail.ident, "DefinisiBenda") 
      || ! strcmp(lex.detail.ident, "DEFBENDA") || ! strcmp(lex.detail.ident, "defbenda") 
      || ! strcmp(lex.detail.ident, "DefBenda") )
      lex.type = _DEF_BENDA;

  if( ! strcmp(lex.detail.ident, "LOKAL") || ! strcmp(lex.detail.ident, "lokal")
      || ! strcmp(lex.detail.ident, "Lokal"))    lex.type = _LOKAL;
  if( ! strcmp(lex.detail.ident, "GLOBAL") || ! strcmp(lex.detail.ident, "global")
      || ! strcmp(lex.detail.ident, "Global") || ! strcmp(lex.detail.ident, "SEMESTA")
	  || ! strcmp(lex.detail.ident, "semesta") || ! strcmp(lex.detail.ident, "Semesta")) 
	  lex.type = _GLOBAL;

#ifdef USE_GTK2
  if( ! strcmp(lex.detail.ident, "PAKAI_LAYAR") || ! strcmp(lex.detail.ident, "pakai_layar")
      || ! strcmp(lex.detail.ident, "Pakai_Layar") || ! strcmp(lex.detail.ident, "PAKAI_PEWAKTU")
	  || ! strcmp(lex.detail.ident, "pakai_pewaktu")
	  )    lex.type = _PAKAI_LAYAR;

  if( ! strcmp(lex.detail.ident, "KIBAR_LAYAR") || ! strcmp(lex.detail.ident, "kibar_layar")
      || ! strcmp(lex.detail.ident, "Kibar_Layar") || ! strcmp(lex.detail.ident, "MULAI_PEWAKTU")
	  || ! strcmp(lex.detail.ident, "mulai_pewaktu")
	  )    lex.type = _KIBAR_LAYAR;

  if( ! strcmp(lex.detail.ident, "TAMPIL_LAYAR") || ! strcmp(lex.detail.ident, "tampil_layar")
      || ! strcmp(lex.detail.ident, "Tampil_Layar"))    lex.type = _TAMPIL_LAYAR;
  if( ! strcmp(lex.detail.ident, "TITEL_LAYAR") || ! strcmp(lex.detail.ident, "titel_layar")
      || ! strcmp(lex.detail.ident, "Titel_Layar"))    lex.type = _TITEL_LAYAR;
  if( ! strcmp(lex.detail.ident, "LUAS_LAYAR") || ! strcmp(lex.detail.ident, "luas_layar")
      || ! strcmp(lex.detail.ident, "Luas_Layar"))    lex.type = _LUAS_LAYAR;
  if( ! strcmp(lex.detail.ident, "LOGO_LAYAR") || ! strcmp(lex.detail.ident, "logo_layar")
      || ! strcmp(lex.detail.ident, "Logo_Layar"))    lex.type = _LOGO_LAYAR;
  if( ! strcmp(lex.detail.ident, "HIAS_LAYAR") || ! strcmp(lex.detail.ident, "hias_layar")
      || ! strcmp(lex.detail.ident, "Hias_Layar"))    lex.type = _HIAS_LAYAR;
  if( ! strcmp(lex.detail.ident, "HIAS_LAYAR_GULUNG") || ! strcmp(lex.detail.ident, "hias_layar_gulung")
      || ! strcmp(lex.detail.ident, "Hias_Layar_Gulung"))    lex.type = _HIAS_LAYAR_GULUNG;
  if( ! strcmp(lex.detail.ident, "HIAS_ALAS") || ! strcmp(lex.detail.ident, "hias_alas")
      || ! strcmp(lex.detail.ident, "Hias_Alas"))    lex.type = _HIAS_ALAS;

  if( ! strcmp(lex.detail.ident, "ISI_ALAS_TEGAK") || ! strcmp(lex.detail.ident, "isi_alas_tegak")
      || ! strcmp(lex.detail.ident, "Isi_Alas_Tegak"))    lex.type = _ISI_ALAS_TEGAK;

  if( ! strcmp(lex.detail.ident, "AKSI_TUTUP_LAYAR") || ! strcmp(lex.detail.ident, "aksi_tutup_layar")
      || ! strcmp(lex.detail.ident, "TUTUP_LAYAR") || ! strcmp(lex.detail.ident, "tutup_layar"))
	  lex.type = _AKSI_TUTUP_LAYAR;

  if( ! strcmp(lex.detail.ident, "AKSI_TUTUP_PROGRAM") || ! strcmp(lex.detail.ident, "aksi_tutup_program")
      || ! strcmp(lex.detail.ident, "TUTUP_PROGRAM") || ! strcmp(lex.detail.ident, "tutup_program"))
	  lex.type = _AKSI_TUTUP_PROGRAM;

  if( ! strcmp(lex.detail.ident, "AKSI_FUNGSI") || ! strcmp(lex.detail.ident, "aksi_fungsi")
      || ! strcmp(lex.detail.ident, "Aksi_Fungsi") || ! strcmp(lex.detail.ident, "Aksi_fungsi"))
	  lex.type = _AKSI_FUNGSI;

  if( ! strcmp(lex.detail.ident, "AKSI_SIAP_CETAK") || ! strcmp(lex.detail.ident, "aksi_siap_cetak") )
	  lex.type = _AKSI_SIAP_CETAK;
  if( ! strcmp(lex.detail.ident, "AKSI_CETAK_TEKS") || ! strcmp(lex.detail.ident, "aksi_cetak_teks") )
	  lex.type = _AKSI_CETAK_TEKS;
  if( ! strcmp(lex.detail.ident, "MULAI_CETAK") || ! strcmp(lex.detail.ident, "mulai_cetak") )
	  lex.type = _MULAI_CETAK;
  if( ! strcmp(lex.detail.ident, "SET_OPERASI_CETAK") || ! strcmp(lex.detail.ident, "set_operasi_cetak") )
	  lex.type = _SET_OPERASI_CETAK;
  if( ! strcmp(lex.detail.ident, "TULIS_TEKS_CETAK") || ! strcmp(lex.detail.ident, "tulis_teks_cetak") )
	  lex.type = _TULIS_TEKS_CETAK;

  if( ! strcmp(lex.detail.ident, "AKSI_RAMBU_INFO") || ! strcmp(lex.detail.ident, "aksi_rambu_info")
      || ! strcmp(lex.detail.ident, "Aksi_Rambu_Info") || ! strcmp(lex.detail.ident, "AKSI_INFO")
	  || ! strcmp(lex.detail.ident, "aksi_info"))
	  lex.type = _AKSI_RAMBU_INFO;
  if( ! strcmp(lex.detail.ident, "AKSI_RAMBU_AWAS") || ! strcmp(lex.detail.ident, "aksi_rambu_awas")
      || ! strcmp(lex.detail.ident, "Aksi_Rambu_Awas") || ! strcmp(lex.detail.ident, "AKSI_AWAS")
	  || ! strcmp(lex.detail.ident, "aksi_awas"))
	  lex.type = _AKSI_RAMBU_AWAS;
  if( ! strcmp(lex.detail.ident, "AKSI_RAMBU_SALAH") || ! strcmp(lex.detail.ident, "aksi_rambu_salah")
      || ! strcmp(lex.detail.ident, "Aksi_Rambu_Info") || ! strcmp(lex.detail.ident, "AKSI_SALAH")
	  || ! strcmp(lex.detail.ident, "aksi_salah"))
	  lex.type = _AKSI_RAMBU_SALAH;

  if( ! strcmp(lex.detail.ident, "AKSI_JATIDIRI") || ! strcmp(lex.detail.ident, "aksi_jatidiri")
      || ! strcmp(lex.detail.ident, "Aksi_jatidiri") || ! strcmp(lex.detail.ident, "AKSI_LENCANA_JATIDIRI")
	  || ! strcmp(lex.detail.ident, "aksi_lencana_jatidiri"))
	  lex.type = _AKSI_JATIDIRI;

  if( ! strcmp(lex.detail.ident, "AKSI_TEKAN_PAPANKETIK") || ! strcmp(lex.detail.ident, "aksi_tekan_papanketik")
      || ! strcmp(lex.detail.ident, "Aksi_Tekan_Papanketik") || ! strcmp(lex.detail.ident, "Aksi_Tekan_PapanKetik"))
	  lex.type = _AKSI_TEKAN_KETIK;
  if( ! strcmp(lex.detail.ident, "AKSI_LEPAS_PAPANKETIK") || ! strcmp(lex.detail.ident, "aksi_lepas_papanketik")
      || ! strcmp(lex.detail.ident, "Aksi_Lepas_Papanketik") || ! strcmp(lex.detail.ident, "Aksi_Lepas_PapanKetik"))
	  lex.type = _AKSI_LEPAS_KETIK;
  if( ! strcmp(lex.detail.ident, "AKSI_TEKAN_PENUNJUK") || ! strcmp(lex.detail.ident, "aksi_tekan_penunjuk")
      || ! strcmp(lex.detail.ident, "Aksi_Tekan_Penunjuk") )
	  lex.type = _AKSI_TEKAN_MOUSE;
  if( ! strcmp(lex.detail.ident, "AKSI_LEPAS_PENUNJUK") || ! strcmp(lex.detail.ident, "aksi_lepas_penunjuk")
      || ! strcmp(lex.detail.ident, "Aksi_Lepas_Penunjuk") )
	  lex.type = _AKSI_LEPAS_MOUSE;
  if( ! strcmp(lex.detail.ident, "AKSI_PENUNJUK_BERGERAK") || ! strcmp(lex.detail.ident, "aksi_penunjuk_bergerak")
      || ! strcmp(lex.detail.ident, "Aksi_Penunjuk_Bergerak") )
	  lex.type = _AKSI_MOUSE_BERGERAK;

  if( ! strcmp(lex.detail.ident, "SUBMENU") || ! strcmp(lex.detail.ident, "submenu")
      || ! strcmp(lex.detail.ident, "Submenu"))    lex.type = _SUBMENU;
  if( ! strcmp(lex.detail.ident, "TAMBAH_MENU") || ! strcmp(lex.detail.ident, "tambah_menu")
      || ! strcmp(lex.detail.ident, "Tambah_Menu"))    lex.type = _TAMBAH_MENU;
  if( ! strcmp(lex.detail.ident, "AKHIR_MENU") || ! strcmp(lex.detail.ident, "akhir_menu")
      || ! strcmp(lex.detail.ident, "Akhir_Menu"))    lex.type = _AKHIR_MENU;
  if( ! strcmp(lex.detail.ident, "SUSUN_MENU") || ! strcmp(lex.detail.ident, "susun_menu")
      || ! strcmp(lex.detail.ident, "Susun_Menu"))    lex.type = _SUSUN_MENU;
  if( ! strcmp(lex.detail.ident, "SUSUN_PAPAN_STATUS") || ! strcmp(lex.detail.ident, "susun_papan_status")
      || ! strcmp(lex.detail.ident, "Susun_Papan_Status"))    lex.type = _SUSUN_PAPAN_STATUS;

  if( ! strcmp(lex.detail.ident, "TAMBAH_AKSELERASI") || ! strcmp(lex.detail.ident, "tambah_akselerasi")
      || ! strcmp(lex.detail.ident, "Tambah_Akselerasi"))    lex.type = _TAMBAH_AKSELERASI;
  if( ! strcmp(lex.detail.ident, "SET_SENSITIF") || ! strcmp(lex.detail.ident, "set_sensitif")
      || ! strcmp(lex.detail.ident, "Set_Sensitif"))    lex.type = _SET_SENSITIF;
  if( ! strcmp(lex.detail.ident, "TAMPIL_POPUP") || ! strcmp(lex.detail.ident, "tampil_popup")
      || ! strcmp(lex.detail.ident, "Tampil_Popup"))    lex.type = _TAMPIL_POPUP;

  if( ! strcmp(lex.detail.ident, "RAMBU_INFO") || ! strcmp(lex.detail.ident, "rambu_info")
      || ! strcmp(lex.detail.ident, "Rambu_Info"))    lex.type = _RAMBU_INFO;
  if( ! strcmp(lex.detail.ident, "RAMBU_SALAH") || ! strcmp(lex.detail.ident, "rambu_salah")
      || ! strcmp(lex.detail.ident, "Rambu_Salah"))    lex.type = _RAMBU_SALAH;
  if( ! strcmp(lex.detail.ident, "RAMBU_TANYA") || ! strcmp(lex.detail.ident, "rambu_tanya")
      || ! strcmp(lex.detail.ident, "Rambu_Tanya"))    lex.type = _RAMBU_TANYA;
  if( ! strcmp(lex.detail.ident, "RAMBU_AWAS") || ! strcmp(lex.detail.ident, "rambu_awas")
      || ! strcmp(lex.detail.ident, "Rambu_Awas") || ! strcmp(lex.detail.ident, "RAMBU_PERINGATAN")
	  || ! strcmp(lex.detail.ident, "rambu_peringatan") || ! strcmp(lex.detail.ident, "Rambu_Peringatan")
	  ) lex.type = _RAMBU_AWAS;

  if( ! strcmp(lex.detail.ident, "SET_WARNAHURUF") || ! strcmp(lex.detail.ident, "set_warnahuruf")
      || ! strcmp(lex.detail.ident, "Set_WarnaHuruf"))    lex.type = _SET_WARNAHURUF;
  if( ! strcmp(lex.detail.ident, "SET_WARNADASAR") || ! strcmp(lex.detail.ident, "set_warnadasar")
      || ! strcmp(lex.detail.ident, "Set_WarnaDasar"))    lex.type = _SET_WARNADASAR;

  if( ! strcmp(lex.detail.ident, "SET_JENISHURUF") || ! strcmp(lex.detail.ident, "set_jenishuruf")
      || ! strcmp(lex.detail.ident, "Set_JenisHuruf"))    lex.type = _SET_JENISHURUF;

  if( ! strcmp(lex.detail.ident, "SET_PILIHAN") || ! strcmp(lex.detail.ident, "set_pilihan")
      || ! strcmp(lex.detail.ident, "Set_Pilihan"))    lex.type = _SET_PILIHAN;
  if( ! strcmp(lex.detail.ident, "SET_LABEL") || ! strcmp(lex.detail.ident, "set_label")
      || ! strcmp(lex.detail.ident, "Set_Label"))    lex.type = _SET_LABEL;
  if( ! strcmp(lex.detail.ident, "SET_TOMBOL") || ! strcmp(lex.detail.ident, "set_tombol")
      || ! strcmp(lex.detail.ident, "Set_Tombol"))    lex.type = _SET_TOMBOL;
  if( ! strcmp(lex.detail.ident, "SET_MASUKAN") || ! strcmp(lex.detail.ident, "set_masukan")
      || ! strcmp(lex.detail.ident, "Set_Masukan"))    lex.type = _SET_MASUKAN;
  if( ! strcmp(lex.detail.ident, "SET_TIPS") || ! strcmp(lex.detail.ident, "set_tips")
      || ! strcmp(lex.detail.ident, "Set_Tips"))    lex.type = _SET_TIPS;
  if( ! strcmp(lex.detail.ident, "SET_KERTAS") || ! strcmp(lex.detail.ident, "set_kertas")
      || ! strcmp(lex.detail.ident, "Set_Kertas"))    lex.type = _SET_KERTAS;

  if( ! strcmp(lex.detail.ident, "TAMPILKAN") || ! strcmp(lex.detail.ident, "tampilkan")
      || ! strcmp(lex.detail.ident, "Tampilkan"))    lex.type = _TAMPIL_ELEMEN;
  if( ! strcmp(lex.detail.ident, "SEMBUNYIKAN") || ! strcmp(lex.detail.ident, "sembunyikan")
      || ! strcmp(lex.detail.ident, "Sembunyikan"))    lex.type = _SEMBUNYI_ELEMEN;

  if( ! strcmp(lex.detail.ident, "SET_STATUS") || ! strcmp(lex.detail.ident, "set_status")
      || ! strcmp(lex.detail.ident, "Set_Status"))    lex.type = _SET_STATUS;
  if( ! strcmp(lex.detail.ident, "HAPUS_STATUS") || ! strcmp(lex.detail.ident, "hapus_status")
      || ! strcmp(lex.detail.ident, "Hapus_Status"))    lex.type = _HAPUS_STATUS;

  if( ! strcmp(lex.detail.ident, "TABEL_ATRIBUT") || ! strcmp(lex.detail.ident, "tabel_atribut")
      || ! strcmp(lex.detail.ident, "Tabel_Atribut"))    lex.type = _TABEL_ATRIBUT;
  if( ! strcmp(lex.detail.ident, "TABEL_DATA") || ! strcmp(lex.detail.ident, "tabel_data")
      || ! strcmp(lex.detail.ident, "Tabel_Data"))    lex.type = _TABEL_DATA;
  if( ! strcmp(lex.detail.ident, "HAPUS_SEL_TABEL") || ! strcmp(lex.detail.ident, "hapus_sel_tabel")
      || ! strcmp(lex.detail.ident, "Hapus_SelTabel") || ! strcmp(lex.detail.ident, "HAPUS_SELTABEL")
	  || ! strcmp(lex.detail.ident, "hapus_seltabel")|| ! strcmp(lex.detail.ident, "Hapus_Seltabel")
	  )    lex.type = _HAPUS_SEL_TABEL;
  if( ! strcmp(lex.detail.ident, "TULIS_SEL_TABEL") || ! strcmp(lex.detail.ident, "tulis_sel_tabel")
      || ! strcmp(lex.detail.ident, "Tulis_SelTabel") || ! strcmp(lex.detail.ident, "TULIS_SELTABEL")
	  || ! strcmp(lex.detail.ident, "tulis_seltabel")|| ! strcmp(lex.detail.ident, "Tulis_Seltabel")
	  )    lex.type = _TULIS_SEL_TABEL;
  if( ! strcmp(lex.detail.ident, "TULIS_TABEL") || ! strcmp(lex.detail.ident, "tulis_tabel")
      || ! strcmp(lex.detail.ident, "Tulis_Tabel") )    lex.type = _TULIS_TABEL;

  if( ! strcmp(lex.detail.ident, "ISI_PUNDI_TEKS") || ! strcmp(lex.detail.ident, "isi_pundi_teks")
      || ! strcmp(lex.detail.ident, "Isi_Pundi_Teks") )    lex.type = _ISI_PUNDI_TEKS;
  if( ! strcmp(lex.detail.ident, "ISI_TEKS_RAMPUNG") || ! strcmp(lex.detail.ident, "isi_teks_rampung")
      || ! strcmp(lex.detail.ident, "Isi_Teks_Rampung") )    lex.type = _ISI_TEKS_RAMPUNG;
  if( ! strcmp(lex.detail.ident, "SET_TEKS_RAMPUNG") || ! strcmp(lex.detail.ident, "set_teks_rampung")
      || ! strcmp(lex.detail.ident, "Set_Teks_Rampung") )    lex.type = _SET_TEKS_RAMPUNG;

  if( ! strcmp(lex.detail.ident, "HAPUS_TEKS_TERPILIH") || ! strcmp(lex.detail.ident, "hapus_teks_terpilih")
      || ! strcmp(lex.detail.ident, "Hapus_Teks_Terpilih") )    lex.type = _HAPUS_TEKS_TERPILIH;
  if( ! strcmp(lex.detail.ident, "SALIN_TEKS_PAPANKLIP") || ! strcmp(lex.detail.ident, "salin_teks_papanklip")
      || ! strcmp(lex.detail.ident, "Salin_Teks_Papanklip") )    lex.type = _SALIN_TEKS_PAPANKLIP;
  if( ! strcmp(lex.detail.ident, "POTONG_TEKS_PAPANKLIP") || ! strcmp(lex.detail.ident, "potong_teks_papanklip")
      || ! strcmp(lex.detail.ident, "Potong_Teks_Papanklip") )    lex.type = _POTONG_TEKS_PAPANKLIP;
  if( ! strcmp(lex.detail.ident, "UNDUH_TEKS_PAPANKLIP") || ! strcmp(lex.detail.ident, "unduh_teks_papanklip")
      || ! strcmp(lex.detail.ident, "Unduh_Teks_Papanklip") )    lex.type = _UNDUH_TEKS_PAPANKLIP;

  if( ! strcmp(lex.detail.ident, "TANGGALAN") || ! strcmp(lex.detail.ident, "tanggalan")
      || ! strcmp(lex.detail.ident, "Tanggalan") )    lex.type = _TANGGALAN;

  if( ! strcmp(lex.detail.ident, "SIMPAN_TEKS") || ! strcmp(lex.detail.ident, "simpan_teks")
      || ! strcmp(lex.detail.ident, "Simpan_Teks") )    lex.type = _SIMPAN_TEKS;

  if( ! strcmp(lex.detail.ident, "LEMBAR_BUKU") || ! strcmp(lex.detail.ident, "lembar_buku")
      || ! strcmp(lex.detail.ident, "Lembar_Buku"))    lex.type = _LEMBAR_BUKU;
  if( ! strcmp(lex.detail.ident, "TAB_BUKU") || ! strcmp(lex.detail.ident, "tab_buku")
      || ! strcmp(lex.detail.ident, "Tab_Buku"))    lex.type = _TAB_BUKU;

  if( ! strcmp(lex.detail.ident, "TAMBAH_RANTING") || ! strcmp(lex.detail.ident, "tambah_ranting")
      || ! strcmp(lex.detail.ident, "Tambah_Ranting"))    lex.type = _TAMBAH_RANTING;
  if( ! strcmp(lex.detail.ident, "WARNAHURUF_SEL") || ! strcmp(lex.detail.ident, "warnahuruf_sel")
      || ! strcmp(lex.detail.ident, "WarnaHuruf_Sel"))    lex.type = _WARNAHURUF_SEL;
  if( ! strcmp(lex.detail.ident, "WARNADASAR_SEL") || ! strcmp(lex.detail.ident, "warnadasar_sel")
      || ! strcmp(lex.detail.ident, "WarnaDasar_Sel"))    lex.type = _WARNADASAR_SEL;
  if( ! strcmp(lex.detail.ident, "JENISHURUF_SEL") || ! strcmp(lex.detail.ident, "jenishuruf_sel")
      || ! strcmp(lex.detail.ident, "JenisHuruf_Sel"))    lex.type = _JENISHURUF_SEL;

#endif

#ifdef USE_GTK3
  if (!strcmp(lex.detail.ident, "PAKAI_LAYAR") || !strcmp(lex.detail.ident, "pakai_layar")
	  || !strcmp(lex.detail.ident, "Pakai_Layar") || !strcmp(lex.detail.ident, "PAKAI_PEWAKTU")
	  || !strcmp(lex.detail.ident, "pakai_pewaktu")
	  )    lex.type = _PAKAI_LAYAR;

  if (!strcmp(lex.detail.ident, "KIBAR_LAYAR") || !strcmp(lex.detail.ident, "kibar_layar")
	  || !strcmp(lex.detail.ident, "Kibar_Layar") || !strcmp(lex.detail.ident, "MULAI_PEWAKTU")
	  || !strcmp(lex.detail.ident, "mulai_pewaktu")
	  )    lex.type = _KIBAR_LAYAR;

  if (!strcmp(lex.detail.ident, "TAMPIL_LAYAR") || !strcmp(lex.detail.ident, "tampil_layar")
	  || !strcmp(lex.detail.ident, "Tampil_Layar"))    lex.type = _TAMPIL_LAYAR;
  if (!strcmp(lex.detail.ident, "TITEL_LAYAR") || !strcmp(lex.detail.ident, "titel_layar")
	  || !strcmp(lex.detail.ident, "Titel_Layar"))    lex.type = _TITEL_LAYAR;
  if (!strcmp(lex.detail.ident, "LUAS_LAYAR") || !strcmp(lex.detail.ident, "luas_layar")
	  || !strcmp(lex.detail.ident, "Luas_Layar"))    lex.type = _LUAS_LAYAR;
  if (!strcmp(lex.detail.ident, "LOGO_LAYAR") || !strcmp(lex.detail.ident, "logo_layar")
	  || !strcmp(lex.detail.ident, "Logo_Layar"))    lex.type = _LOGO_LAYAR;
  if (!strcmp(lex.detail.ident, "HIAS_LAYAR") || !strcmp(lex.detail.ident, "hias_layar")
	  || !strcmp(lex.detail.ident, "Hias_Layar"))    lex.type = _HIAS_LAYAR;
  if (!strcmp(lex.detail.ident, "HIAS_LAYAR_GULUNG") || !strcmp(lex.detail.ident, "hias_layar_gulung")
	  || !strcmp(lex.detail.ident, "Hias_Layar_Gulung"))    lex.type = _HIAS_LAYAR_GULUNG;
  if (!strcmp(lex.detail.ident, "HIAS_ALAS") || !strcmp(lex.detail.ident, "hias_alas")
	  || !strcmp(lex.detail.ident, "Hias_Alas"))    lex.type = _HIAS_ALAS;

  if (!strcmp(lex.detail.ident, "ISI_ALAS_TEGAK") || !strcmp(lex.detail.ident, "isi_alas_tegak")
	  || !strcmp(lex.detail.ident, "Isi_Alas_Tegak"))    lex.type = _ISI_ALAS_TEGAK;

  if (!strcmp(lex.detail.ident, "AKSI_TUTUP_LAYAR") || !strcmp(lex.detail.ident, "aksi_tutup_layar")
	  || !strcmp(lex.detail.ident, "TUTUP_LAYAR") || !strcmp(lex.detail.ident, "tutup_layar"))
	  lex.type = _AKSI_TUTUP_LAYAR;

  if (!strcmp(lex.detail.ident, "AKSI_TUTUP_PROGRAM") || !strcmp(lex.detail.ident, "aksi_tutup_program")
	  || !strcmp(lex.detail.ident, "TUTUP_PROGRAM") || !strcmp(lex.detail.ident, "tutup_program"))
	  lex.type = _AKSI_TUTUP_PROGRAM;

  if (!strcmp(lex.detail.ident, "AKSI_FUNGSI") || !strcmp(lex.detail.ident, "aksi_fungsi")
	  || !strcmp(lex.detail.ident, "Aksi_Fungsi") || !strcmp(lex.detail.ident, "Aksi_fungsi"))
	  lex.type = _AKSI_FUNGSI;

  if (!strcmp(lex.detail.ident, "AKSI_SIAP_CETAK") || !strcmp(lex.detail.ident, "aksi_siap_cetak"))
	  lex.type = _AKSI_SIAP_CETAK;
  if (!strcmp(lex.detail.ident, "AKSI_CETAK_TEKS") || !strcmp(lex.detail.ident, "aksi_cetak_teks"))
	  lex.type = _AKSI_CETAK_TEKS;
  if (!strcmp(lex.detail.ident, "MULAI_CETAK") || !strcmp(lex.detail.ident, "mulai_cetak"))
	  lex.type = _MULAI_CETAK;
  if (!strcmp(lex.detail.ident, "SET_OPERASI_CETAK") || !strcmp(lex.detail.ident, "set_operasi_cetak"))
	  lex.type = _SET_OPERASI_CETAK;
  if (!strcmp(lex.detail.ident, "TULIS_TEKS_CETAK") || !strcmp(lex.detail.ident, "tulis_teks_cetak"))
	  lex.type = _TULIS_TEKS_CETAK;

  if (!strcmp(lex.detail.ident, "AKSI_RAMBU_INFO") || !strcmp(lex.detail.ident, "aksi_rambu_info")
	  || !strcmp(lex.detail.ident, "Aksi_Rambu_Info") || !strcmp(lex.detail.ident, "AKSI_INFO")
	  || !strcmp(lex.detail.ident, "aksi_info"))
	  lex.type = _AKSI_RAMBU_INFO;
  if (!strcmp(lex.detail.ident, "AKSI_RAMBU_AWAS") || !strcmp(lex.detail.ident, "aksi_rambu_awas")
	  || !strcmp(lex.detail.ident, "Aksi_Rambu_Awas") || !strcmp(lex.detail.ident, "AKSI_AWAS")
	  || !strcmp(lex.detail.ident, "aksi_awas"))
	  lex.type = _AKSI_RAMBU_AWAS;
  if (!strcmp(lex.detail.ident, "AKSI_RAMBU_SALAH") || !strcmp(lex.detail.ident, "aksi_rambu_salah")
	  || !strcmp(lex.detail.ident, "Aksi_Rambu_Info") || !strcmp(lex.detail.ident, "AKSI_SALAH")
	  || !strcmp(lex.detail.ident, "aksi_salah"))
	  lex.type = _AKSI_RAMBU_SALAH;

  if (!strcmp(lex.detail.ident, "AKSI_JATIDIRI") || !strcmp(lex.detail.ident, "aksi_jatidiri")
	  || !strcmp(lex.detail.ident, "Aksi_jatidiri") || !strcmp(lex.detail.ident, "AKSI_LENCANA_JATIDIRI")
	  || !strcmp(lex.detail.ident, "aksi_lencana_jatidiri"))
	  lex.type = _AKSI_JATIDIRI;

  if (!strcmp(lex.detail.ident, "AKSI_TEKAN_PAPANKETIK") || !strcmp(lex.detail.ident, "aksi_tekan_papanketik")
	  || !strcmp(lex.detail.ident, "Aksi_Tekan_Papanketik") || !strcmp(lex.detail.ident, "Aksi_Tekan_PapanKetik"))
	  lex.type = _AKSI_TEKAN_KETIK;
  if (!strcmp(lex.detail.ident, "AKSI_LEPAS_PAPANKETIK") || !strcmp(lex.detail.ident, "aksi_lepas_papanketik")
	  || !strcmp(lex.detail.ident, "Aksi_Lepas_Papanketik") || !strcmp(lex.detail.ident, "Aksi_Lepas_PapanKetik"))
	  lex.type = _AKSI_LEPAS_KETIK;
  if (!strcmp(lex.detail.ident, "AKSI_TEKAN_PENUNJUK") || !strcmp(lex.detail.ident, "aksi_tekan_penunjuk")
	  || !strcmp(lex.detail.ident, "Aksi_Tekan_Penunjuk"))
	  lex.type = _AKSI_TEKAN_MOUSE;
  if (!strcmp(lex.detail.ident, "AKSI_LEPAS_PENUNJUK") || !strcmp(lex.detail.ident, "aksi_lepas_penunjuk")
	  || !strcmp(lex.detail.ident, "Aksi_Lepas_Penunjuk"))
	  lex.type = _AKSI_LEPAS_MOUSE;
  if (!strcmp(lex.detail.ident, "AKSI_PENUNJUK_BERGERAK") || !strcmp(lex.detail.ident, "aksi_penunjuk_bergerak")
	  || !strcmp(lex.detail.ident, "Aksi_Penunjuk_Bergerak"))
	  lex.type = _AKSI_MOUSE_BERGERAK;

  if (!strcmp(lex.detail.ident, "SUBMENU") || !strcmp(lex.detail.ident, "submenu")
	  || !strcmp(lex.detail.ident, "Submenu"))    lex.type = _SUBMENU;
  if (!strcmp(lex.detail.ident, "TAMBAH_MENU") || !strcmp(lex.detail.ident, "tambah_menu")
	  || !strcmp(lex.detail.ident, "Tambah_Menu"))    lex.type = _TAMBAH_MENU;
  if (!strcmp(lex.detail.ident, "AKHIR_MENU") || !strcmp(lex.detail.ident, "akhir_menu")
	  || !strcmp(lex.detail.ident, "Akhir_Menu"))    lex.type = _AKHIR_MENU;
  if (!strcmp(lex.detail.ident, "SUSUN_MENU") || !strcmp(lex.detail.ident, "susun_menu")
	  || !strcmp(lex.detail.ident, "Susun_Menu"))    lex.type = _SUSUN_MENU;
  if (!strcmp(lex.detail.ident, "SUSUN_PAPAN_STATUS") || !strcmp(lex.detail.ident, "susun_papan_status")
	  || !strcmp(lex.detail.ident, "Susun_Papan_Status"))    lex.type = _SUSUN_PAPAN_STATUS;

  if (!strcmp(lex.detail.ident, "TAMBAH_AKSELERASI") || !strcmp(lex.detail.ident, "tambah_akselerasi")
	  || !strcmp(lex.detail.ident, "Tambah_Akselerasi"))    lex.type = _TAMBAH_AKSELERASI;
  if (!strcmp(lex.detail.ident, "SET_SENSITIF") || !strcmp(lex.detail.ident, "set_sensitif")
	  || !strcmp(lex.detail.ident, "Set_Sensitif"))    lex.type = _SET_SENSITIF;
  if (!strcmp(lex.detail.ident, "TAMPIL_POPUP") || !strcmp(lex.detail.ident, "tampil_popup")
	  || !strcmp(lex.detail.ident, "Tampil_Popup"))    lex.type = _TAMPIL_POPUP;

  if (!strcmp(lex.detail.ident, "RAMBU_INFO") || !strcmp(lex.detail.ident, "rambu_info")
	  || !strcmp(lex.detail.ident, "Rambu_Info"))    lex.type = _RAMBU_INFO;
  if (!strcmp(lex.detail.ident, "RAMBU_SALAH") || !strcmp(lex.detail.ident, "rambu_salah")
	  || !strcmp(lex.detail.ident, "Rambu_Salah"))    lex.type = _RAMBU_SALAH;
  if (!strcmp(lex.detail.ident, "RAMBU_TANYA") || !strcmp(lex.detail.ident, "rambu_tanya")
	  || !strcmp(lex.detail.ident, "Rambu_Tanya"))    lex.type = _RAMBU_TANYA;
  if (!strcmp(lex.detail.ident, "RAMBU_AWAS") || !strcmp(lex.detail.ident, "rambu_awas")
	  || !strcmp(lex.detail.ident, "Rambu_Awas") || !strcmp(lex.detail.ident, "RAMBU_PERINGATAN")
	  || !strcmp(lex.detail.ident, "rambu_peringatan") || !strcmp(lex.detail.ident, "Rambu_Peringatan")
	  ) lex.type = _RAMBU_AWAS;

  if (!strcmp(lex.detail.ident, "SET_WARNAHURUF") || !strcmp(lex.detail.ident, "set_warnahuruf")
	  || !strcmp(lex.detail.ident, "Set_WarnaHuruf"))    lex.type = _SET_WARNAHURUF;
  if (!strcmp(lex.detail.ident, "SET_WARNADASAR") || !strcmp(lex.detail.ident, "set_warnadasar")
	  || !strcmp(lex.detail.ident, "Set_WarnaDasar"))    lex.type = _SET_WARNADASAR;

  if (!strcmp(lex.detail.ident, "SET_JENISHURUF") || !strcmp(lex.detail.ident, "set_jenishuruf")
	  || !strcmp(lex.detail.ident, "Set_JenisHuruf"))    lex.type = _SET_JENISHURUF;

  if (!strcmp(lex.detail.ident, "SET_PILIHAN") || !strcmp(lex.detail.ident, "set_pilihan")
	  || !strcmp(lex.detail.ident, "Set_Pilihan"))    lex.type = _SET_PILIHAN;
  if (!strcmp(lex.detail.ident, "SET_LABEL") || !strcmp(lex.detail.ident, "set_label")
	  || !strcmp(lex.detail.ident, "Set_Label"))    lex.type = _SET_LABEL;
  if (!strcmp(lex.detail.ident, "SET_TOMBOL") || !strcmp(lex.detail.ident, "set_tombol")
	  || !strcmp(lex.detail.ident, "Set_Tombol"))    lex.type = _SET_TOMBOL;
  if (!strcmp(lex.detail.ident, "SET_MASUKAN") || !strcmp(lex.detail.ident, "set_masukan")
	  || !strcmp(lex.detail.ident, "Set_Masukan"))    lex.type = _SET_MASUKAN;
  if (!strcmp(lex.detail.ident, "SET_TIPS") || !strcmp(lex.detail.ident, "set_tips")
	  || !strcmp(lex.detail.ident, "Set_Tips"))    lex.type = _SET_TIPS;
  if (!strcmp(lex.detail.ident, "SET_KERTAS") || !strcmp(lex.detail.ident, "set_kertas")
	  || !strcmp(lex.detail.ident, "Set_Kertas"))    lex.type = _SET_KERTAS;

  if (!strcmp(lex.detail.ident, "TAMPILKAN") || !strcmp(lex.detail.ident, "tampilkan")
	  || !strcmp(lex.detail.ident, "Tampilkan"))    lex.type = _TAMPIL_ELEMEN;
  if (!strcmp(lex.detail.ident, "SEMBUNYIKAN") || !strcmp(lex.detail.ident, "sembunyikan")
	  || !strcmp(lex.detail.ident, "Sembunyikan"))    lex.type = _SEMBUNYI_ELEMEN;

  if (!strcmp(lex.detail.ident, "SET_STATUS") || !strcmp(lex.detail.ident, "set_status")
	  || !strcmp(lex.detail.ident, "Set_Status"))    lex.type = _SET_STATUS;
  if (!strcmp(lex.detail.ident, "HAPUS_STATUS") || !strcmp(lex.detail.ident, "hapus_status")
	  || !strcmp(lex.detail.ident, "Hapus_Status"))    lex.type = _HAPUS_STATUS;

  if (!strcmp(lex.detail.ident, "TABEL_ATRIBUT") || !strcmp(lex.detail.ident, "tabel_atribut")
	  || !strcmp(lex.detail.ident, "Tabel_Atribut"))    lex.type = _TABEL_ATRIBUT;
  if (!strcmp(lex.detail.ident, "TABEL_DATA") || !strcmp(lex.detail.ident, "tabel_data")
	  || !strcmp(lex.detail.ident, "Tabel_Data"))    lex.type = _TABEL_DATA;
  if (!strcmp(lex.detail.ident, "HAPUS_SEL_TABEL") || !strcmp(lex.detail.ident, "hapus_sel_tabel")
	  || !strcmp(lex.detail.ident, "Hapus_SelTabel") || !strcmp(lex.detail.ident, "HAPUS_SELTABEL")
	  || !strcmp(lex.detail.ident, "hapus_seltabel") || !strcmp(lex.detail.ident, "Hapus_Seltabel")
	  )    lex.type = _HAPUS_SEL_TABEL;
  if (!strcmp(lex.detail.ident, "TULIS_SEL_TABEL") || !strcmp(lex.detail.ident, "tulis_sel_tabel")
	  || !strcmp(lex.detail.ident, "Tulis_SelTabel") || !strcmp(lex.detail.ident, "TULIS_SELTABEL")
	  || !strcmp(lex.detail.ident, "tulis_seltabel") || !strcmp(lex.detail.ident, "Tulis_Seltabel")
	  )    lex.type = _TULIS_SEL_TABEL;
  if (!strcmp(lex.detail.ident, "TULIS_TABEL") || !strcmp(lex.detail.ident, "tulis_tabel")
	  || !strcmp(lex.detail.ident, "Tulis_Tabel"))    lex.type = _TULIS_TABEL;

  if (!strcmp(lex.detail.ident, "ISI_PUNDI_TEKS") || !strcmp(lex.detail.ident, "isi_pundi_teks")
	  || !strcmp(lex.detail.ident, "Isi_Pundi_Teks"))    lex.type = _ISI_PUNDI_TEKS;
  if (!strcmp(lex.detail.ident, "ISI_TEKS_RAMPUNG") || !strcmp(lex.detail.ident, "isi_teks_rampung")
	  || !strcmp(lex.detail.ident, "Isi_Teks_Rampung"))    lex.type = _ISI_TEKS_RAMPUNG;
  if (!strcmp(lex.detail.ident, "SET_TEKS_RAMPUNG") || !strcmp(lex.detail.ident, "set_teks_rampung")
	  || !strcmp(lex.detail.ident, "Set_Teks_Rampung"))    lex.type = _SET_TEKS_RAMPUNG;

  if (!strcmp(lex.detail.ident, "HAPUS_TEKS_TERPILIH") || !strcmp(lex.detail.ident, "hapus_teks_terpilih")
	  || !strcmp(lex.detail.ident, "Hapus_Teks_Terpilih"))    lex.type = _HAPUS_TEKS_TERPILIH;
  if (!strcmp(lex.detail.ident, "SALIN_TEKS_PAPANKLIP") || !strcmp(lex.detail.ident, "salin_teks_papanklip")
	  || !strcmp(lex.detail.ident, "Salin_Teks_Papanklip"))    lex.type = _SALIN_TEKS_PAPANKLIP;
  if (!strcmp(lex.detail.ident, "POTONG_TEKS_PAPANKLIP") || !strcmp(lex.detail.ident, "potong_teks_papanklip")
	  || !strcmp(lex.detail.ident, "Potong_Teks_Papanklip"))    lex.type = _POTONG_TEKS_PAPANKLIP;
  if (!strcmp(lex.detail.ident, "UNDUH_TEKS_PAPANKLIP") || !strcmp(lex.detail.ident, "unduh_teks_papanklip")
	  || !strcmp(lex.detail.ident, "Unduh_Teks_Papanklip"))    lex.type = _UNDUH_TEKS_PAPANKLIP;

  if (!strcmp(lex.detail.ident, "TANGGALAN") || !strcmp(lex.detail.ident, "tanggalan")
	  || !strcmp(lex.detail.ident, "Tanggalan"))    lex.type = _TANGGALAN;

  if (!strcmp(lex.detail.ident, "SIMPAN_TEKS") || !strcmp(lex.detail.ident, "simpan_teks")
	  || !strcmp(lex.detail.ident, "Simpan_Teks"))    lex.type = _SIMPAN_TEKS;

  if (!strcmp(lex.detail.ident, "LEMBAR_BUKU") || !strcmp(lex.detail.ident, "lembar_buku")
	  || !strcmp(lex.detail.ident, "Lembar_Buku"))    lex.type = _LEMBAR_BUKU;
  if (!strcmp(lex.detail.ident, "TAB_BUKU") || !strcmp(lex.detail.ident, "tab_buku")
	  || !strcmp(lex.detail.ident, "Tab_Buku"))    lex.type = _TAB_BUKU;

  if (!strcmp(lex.detail.ident, "TAMBAH_RANTING") || !strcmp(lex.detail.ident, "tambah_ranting")
	  || !strcmp(lex.detail.ident, "Tambah_Ranting"))    lex.type = _TAMBAH_RANTING;
  if (!strcmp(lex.detail.ident, "WARNAHURUF_SEL") || !strcmp(lex.detail.ident, "warnahuruf_sel")
	  || !strcmp(lex.detail.ident, "WarnaHuruf_Sel"))    lex.type = _WARNAHURUF_SEL;
  if (!strcmp(lex.detail.ident, "WARNADASAR_SEL") || !strcmp(lex.detail.ident, "warnadasar_sel")
	  || !strcmp(lex.detail.ident, "WarnaDasar_Sel"))    lex.type = _WARNADASAR_SEL;
  if (!strcmp(lex.detail.ident, "JENISHURUF_SEL") || !strcmp(lex.detail.ident, "jenishuruf_sel")
	  || !strcmp(lex.detail.ident, "JenisHuruf_Sel"))    lex.type = _JENISHURUF_SEL;

#endif

#ifdef USE_PDF
  if( ! strcmp(lex.detail.ident, "PDF_SETHURUF") || ! strcmp(lex.detail.ident, "pdf_sethuruf")
      || ! strcmp(lex.detail.ident, "Pdf_SetHuruf"))    lex.type = _PDF_SETHURUF;
  if( ! strcmp(lex.detail.ident, "PDF_AWALTEKS") || ! strcmp(lex.detail.ident, "pdf_awalteks")
      || ! strcmp(lex.detail.ident, "Pdf_AwalTeks"))    lex.type = _PDF_AWALTEKS;
  if( ! strcmp(lex.detail.ident, "PDF_AKHIRTEKS") || ! strcmp(lex.detail.ident, "pdf_akhirteks")
      || ! strcmp(lex.detail.ident, "Pdf_AkhirTeks"))    lex.type = _PDF_AKHIRTEKS;
  if( ! strcmp(lex.detail.ident, "PDF_TEKS") || ! strcmp(lex.detail.ident, "pdf_teks")
      || ! strcmp(lex.detail.ident, "Pdf_Teks"))    lex.type = _PDF_TEKS;

  if( ! strcmp(lex.detail.ident, "PDF_PNG") || ! strcmp(lex.detail.ident, "pdf_png")
      || ! strcmp(lex.detail.ident, "Pdf_Png"))    lex.type = _PDF_PNG;
  if( ! strcmp(lex.detail.ident, "PDF_JPG") || ! strcmp(lex.detail.ident, "pdf_jpg")
      || ! strcmp(lex.detail.ident, "Pdf_Jpg"))    lex.type = _PDF_JPG;

  if( ! strcmp(lex.detail.ident, "PDF_SIMPANPDF") || ! strcmp(lex.detail.ident, "pdf_simpanpdf")
      || ! strcmp(lex.detail.ident, "Pdf_SimpanPdf"))    lex.type = _PDF_SIMPANPDF;
  if( ! strcmp(lex.detail.ident, "PDF_HAPUS") || ! strcmp(lex.detail.ident, "pdf_hapus")
      || ! strcmp(lex.detail.ident, "Pdf_Hapus"))    lex.type = _PDF_HAPUS;

  if( ! strcmp(lex.detail.ident, "PDF_LUKIS") || ! strcmp(lex.detail.ident, "pdf_lukis")
      || ! strcmp(lex.detail.ident, "Pdf_Lukis"))    lex.type = _PDF_LUKIS;
  if( ! strcmp(lex.detail.ident, "PDF_TEBALGARIS") || ! strcmp(lex.detail.ident, "pdf_tebalgaris")
      || ! strcmp(lex.detail.ident, "Pdf_TebalGaris"))    lex.type = _PDF_TEBALGARIS;
  if( ! strcmp(lex.detail.ident, "PDF_WARNAGARIS") || ! strcmp(lex.detail.ident, "pdf_warnagaris")
      || ! strcmp(lex.detail.ident, "Pdf_WarnaGaris"))    lex.type = _PDF_WARNAGARIS;
  if( ! strcmp(lex.detail.ident, "PDF_KOTAK") || ! strcmp(lex.detail.ident, "pdf_kotak")
      || ! strcmp(lex.detail.ident, "Pdf_Kotak"))    lex.type = _PDF_KOTAK;
  if( ! strcmp(lex.detail.ident, "PDF_POS") || ! strcmp(lex.detail.ident, "pdf_pos")
      || ! strcmp(lex.detail.ident, "Pdf_Pos"))    lex.type = _PDF_POS;
  if( ! strcmp(lex.detail.ident, "PDF_GARIS") || ! strcmp(lex.detail.ident, "pdf_garis")
      || ! strcmp(lex.detail.ident, "Pdf_Garis"))    lex.type = _PDF_GARIS;

  if( ! strcmp(lex.detail.ident, "PDF_WARNAHURUF") || ! strcmp(lex.detail.ident, "pdf_warnahuruf")
      || ! strcmp(lex.detail.ident, "Pdf_WarnaHuruf"))    lex.type = _PDF_WARNAHURUF;
  if( ! strcmp(lex.detail.ident, "PDF_JARAKHURUF") || ! strcmp(lex.detail.ident, "pdf_jarakhuruf")
      || ! strcmp(lex.detail.ident, "Pdf_JarakHuruf"))    lex.type = _PDF_JARAKHURUF;
  if( ! strcmp(lex.detail.ident, "PDF_JARAKKATA") || ! strcmp(lex.detail.ident, "pdf_jarakkata")
      || ! strcmp(lex.detail.ident, "Pdf_JarakKata"))    lex.type = _PDF_JARAKKATA;
#endif

#ifdef USE_GTK2
  if( ! strcmp(lex.detail.ident, "LUKIS_GARIS") || ! strcmp(lex.detail.ident, "lukis_garis")
      || ! strcmp(lex.detail.ident, "Lukis_Garis"))    lex.type = _LUKIS_GARIS;
  if( ! strcmp(lex.detail.ident, "LUKIS_TEKS") || ! strcmp(lex.detail.ident, "lukis_teks")
      || ! strcmp(lex.detail.ident, "Lukis_Teks"))    lex.type = _LUKIS_TEKS;
  if( ! strcmp(lex.detail.ident, "LUKIS_KOTAK") || ! strcmp(lex.detail.ident, "lukis_kotak")
      || ! strcmp(lex.detail.ident, "Lukis_Kotak"))    lex.type = _LUKIS_KOTAK;
  if( ! strcmp(lex.detail.ident, "LUKIS_KOTAKISI") || ! strcmp(lex.detail.ident, "lukis_kotakisi")
      || ! strcmp(lex.detail.ident, "Lukis_KotakIsi"))    lex.type = _LUKIS_KOTAK_ISI;
  if( ! strcmp(lex.detail.ident, "LUKIS_LINGKARAN") || ! strcmp(lex.detail.ident, "lukis_lingkaran")
      || ! strcmp(lex.detail.ident, "Lukis_Lingkaran"))    lex.type = _LUKIS_LINGKARAN;
  if( ! strcmp(lex.detail.ident, "LUKIS_LINGKARANISI") || ! strcmp(lex.detail.ident, "lukis_lingkaranisi")
      || ! strcmp(lex.detail.ident, "Lukis_LingkaranIsi"))    lex.type = _LUKIS_LINGKARAN_ISI;

  if( ! strcmp(lex.detail.ident, "SIMPAN_LUKISAN") || ! strcmp(lex.detail.ident, "simpan_lukisan")
      || ! strcmp(lex.detail.ident, "Simpan_Lukisan"))    lex.type = _SIMPAN_LUKISAN;

  if( ! strcmp(lex.detail.ident, "HAPUS_LATAR") || ! strcmp(lex.detail.ident, "hapus_latar")
      || ! strcmp(lex.detail.ident, "Hapus_Latar"))    lex.type = _HAPUS_LATAR;
  if( ! strcmp(lex.detail.ident, "HAPUS_BIDANG") || ! strcmp(lex.detail.ident, "hapus_bidang")
      || ! strcmp(lex.detail.ident, "Hapus_Bidang"))    lex.type = _HAPUS_BIDANG;
  if( ! strcmp(lex.detail.ident, "HAPUS_POLA") || ! strcmp(lex.detail.ident, "hapus_pola")
      || ! strcmp(lex.detail.ident, "Hapus_Pola"))    lex.type = _HAPUS_POLA;
  if( ! strcmp(lex.detail.ident, "POLA_WARNA") || ! strcmp(lex.detail.ident, "pola_warna")
      || ! strcmp(lex.detail.ident, "Pola_Warna"))    lex.type = _POLA_WARNA;

  if( ! strcmp(lex.detail.ident, "SET_ASAL") || ! strcmp(lex.detail.ident, "set_asal")
      || ! strcmp(lex.detail.ident, "Set_Asal"))    lex.type = _SET_ASAL;
  if( ! strcmp(lex.detail.ident, "SET_ASALBIDANG") || ! strcmp(lex.detail.ident, "set_asalbidang")
      || ! strcmp(lex.detail.ident, "Set_AsalBidang"))    lex.type = _SET_ASALBIDANG;
  if( ! strcmp(lex.detail.ident, "SET_POLA") || ! strcmp(lex.detail.ident, "set_pola")
      || ! strcmp(lex.detail.ident, "Set_Pola"))    lex.type = _SET_ASAL;

  if( ! strcmp(lex.detail.ident, "WARNA_PENA") || ! strcmp(lex.detail.ident, "warna_pena")
      || ! strcmp(lex.detail.ident, "Warna_Pena"))    lex.type = _WARNA_PENA;
  if( ! strcmp(lex.detail.ident, "WARNA_TRANSPARAN") || ! strcmp(lex.detail.ident, "warna_transparan")
      || ! strcmp(lex.detail.ident, "Warna_Transparan"))    lex.type = _WARNA_TRANSPARAN;
  if( ! strcmp(lex.detail.ident, "PUDAR_PENA") || ! strcmp(lex.detail.ident, "pudar_pena")
      || ! strcmp(lex.detail.ident, "Pudar_Pena"))    lex.type = _PUDAR_PENA;
  if( ! strcmp(lex.detail.ident, "PINDAH_PENA") || ! strcmp(lex.detail.ident, "pindah_pena")
      || ! strcmp(lex.detail.ident, "Pindah_Pena"))    lex.type = _PINDAH_PENA;
  if( ! strcmp(lex.detail.ident, "GESER_PENA") || ! strcmp(lex.detail.ident, "geser_pena")
      || ! strcmp(lex.detail.ident, "Geser_Pena"))    lex.type = _GESER_PENA;
  if( ! strcmp(lex.detail.ident, "KLIP_PENA") || ! strcmp(lex.detail.ident, "klip_pena")
      || ! strcmp(lex.detail.ident, "Klip_Pena"))    lex.type = _KLIP_PENA;
  if( ! strcmp(lex.detail.ident, "KLIP_LINGKARAN") || ! strcmp(lex.detail.ident, "klip_lingkaran")
      || ! strcmp(lex.detail.ident, "Klip_Lingkaran"))    lex.type = _KLIP_LINGKARAN;
  if( ! strcmp(lex.detail.ident, "KLIP_KOTAK") || ! strcmp(lex.detail.ident, "klip_kotak")
      || ! strcmp(lex.detail.ident, "Klip_Kotak"))    lex.type = _KLIP_KOTAK;
  if( ! strcmp(lex.detail.ident, "GORES_PENA") || ! strcmp(lex.detail.ident, "gores_pena")
      || ! strcmp(lex.detail.ident, "Gores_Pena"))    lex.type = _GORES_PENA;
  if( ! strcmp(lex.detail.ident, "GORES_PENA_JAGA") || ! strcmp(lex.detail.ident, "gores_pena_jaga")
      || ! strcmp(lex.detail.ident, "Gores_Pena_Jaga"))    lex.type = _GORES_PENA_JAGA;
  if( ! strcmp(lex.detail.ident, "LUKIS_PENA") || ! strcmp(lex.detail.ident, "lukis_pena")
      || ! strcmp(lex.detail.ident, "Lukis_Pena"))    lex.type = _LUKIS_PENA;
  if( ! strcmp(lex.detail.ident, "ISI_PENA") || ! strcmp(lex.detail.ident, "isi_pena")
      || ! strcmp(lex.detail.ident, "Isi_Pena"))    lex.type = _ISI_PENA;
  if( ! strcmp(lex.detail.ident, "ISI_PENA_JAGA") || ! strcmp(lex.detail.ident, "isi_pena_jaga")
      || ! strcmp(lex.detail.ident, "Isi_Pena_Jaga"))    lex.type = _ISI_PENA_JAGA;
  if( ! strcmp(lex.detail.ident, "TEBAL_GARIS") || ! strcmp(lex.detail.ident, "tebal_garis")
      || ! strcmp(lex.detail.ident, "Tebal_Garis"))    lex.type = _TEBAL_GARIS;
  if( ! strcmp(lex.detail.ident, "PUCUK_GARIS") || ! strcmp(lex.detail.ident, "pucuk_garis")
      || ! strcmp(lex.detail.ident, "Pucuk_Garis"))    lex.type = _PUCUK_GARIS;
  if( ! strcmp(lex.detail.ident, "BENTUK_SAMBUNGAN") || ! strcmp(lex.detail.ident, "bentuk_sambungan")
      || ! strcmp(lex.detail.ident, "Bentuk_Sambungan"))    lex.type = _BENTUK_SAMBUNGAN;
  if( ! strcmp(lex.detail.ident, "GARIS_PUTUS") || ! strcmp(lex.detail.ident, "garis_putus")
      || ! strcmp(lex.detail.ident, "Garis_Putus"))    lex.type = _GARIS_PUTUS;
  if( ! strcmp(lex.detail.ident, "ATRIBUT_TEKS") || ! strcmp(lex.detail.ident, "atribut_teks")
      || ! strcmp(lex.detail.ident, "Atribut_Teks"))    lex.type = _ATRIBUT_TEKS;
  if( ! strcmp(lex.detail.ident, "LEKUKAN_TEKS") || ! strcmp(lex.detail.ident, "lekukan_teks")
      || ! strcmp(lex.detail.ident, "Lekukan_Teks"))    lex.type = _LEKUKAN_TEKS;
  if( ! strcmp(lex.detail.ident, "LEKUKAN_BARU") || ! strcmp(lex.detail.ident, "lekukan_baru")
      || ! strcmp(lex.detail.ident, "Lekukan_Baru"))    lex.type = _LEKUKAN_BARU;
  if( ! strcmp(lex.detail.ident, "TUTUP_KURVA") || ! strcmp(lex.detail.ident, "tutup_kurva")
      || ! strcmp(lex.detail.ident, "Tutup_Kurva"))    lex.type = _TUTUP_KURVA;

  if( ! strcmp(lex.detail.ident, "AKSI_EKSPOS") || ! strcmp(lex.detail.ident, "aksi_ekspos")
      || ! strcmp(lex.detail.ident, "Aksi_ekspos") || ! strcmp(lex.detail.ident, "Aksi_Ekspos"))
	  lex.type = _AKSI_EKSPOS;
  if( ! strcmp(lex.detail.ident, "AKSI_ATUR") || ! strcmp(lex.detail.ident, "aksi_atur")
      || ! strcmp(lex.detail.ident, "Aksi_atur") || ! strcmp(lex.detail.ident, "Aksi_Atur"))
	  lex.type = _AKSI_ATUR;

  if( ! strcmp(lex.detail.ident, "EKSPOS_KANVAS") || ! strcmp(lex.detail.ident, "ekspos_kanvas")
      || ! strcmp(lex.detail.ident, "Ekspos_kanvas") || ! strcmp(lex.detail.ident, "Ekspos_Kanvas"))
	  lex.type = _EKSPOS_KANVAS;

  if( ! strcmp(lex.detail.ident, "GESER_LATAR") || ! strcmp(lex.detail.ident, "geser_latar")
      || ! strcmp(lex.detail.ident, "Geser_Latar"))    lex.type = _GESER_LATAR;
  if( ! strcmp(lex.detail.ident, "SKALA_LATAR") || ! strcmp(lex.detail.ident, "skala_latar")
      || ! strcmp(lex.detail.ident, "Skala_Latar"))    lex.type = _SKALA_LATAR;
  if( ! strcmp(lex.detail.ident, "PUTAR_LATAR") || ! strcmp(lex.detail.ident, "putar_latar")
      || ! strcmp(lex.detail.ident, "Putar_Latar"))    lex.type = _PUTAR_LATAR;

  if( ! strcmp(lex.detail.ident, "DETAK_WAKTU") || ! strcmp(lex.detail.ident, "detak_waktu")
      || ! strcmp(lex.detail.ident, "Detak_Waktu"))    lex.type = _DETAK_WAKTU;
  if( ! strcmp(lex.detail.ident, "STOP_DETAK") || ! strcmp(lex.detail.ident, "stop_detak")
      || ! strcmp(lex.detail.ident, "Stop_Detak"))    lex.type = _STOP_DETAK;
  if( ! strcmp(lex.detail.ident, "HAPUS_PIXMAP") || ! strcmp(lex.detail.ident, "hapus_pixmap")
      || ! strcmp(lex.detail.ident, "Hapus_Pixmap"))    lex.type = _HAPUS_PIXMAP;
  if( ! strcmp(lex.detail.ident, "LUKIS_PIXMAP") || ! strcmp(lex.detail.ident, "lukis_pixmap")
      || ! strcmp(lex.detail.ident, "Lukis_Pixmap"))    lex.type = _LUKIS_PIXMAP;
#endif


#ifdef USE_GTK3
  if (!strcmp(lex.detail.ident, "LUKIS_GARIS") || !strcmp(lex.detail.ident, "lukis_garis")
	  || !strcmp(lex.detail.ident, "Lukis_Garis"))    lex.type = _LUKIS_GARIS;
  if (!strcmp(lex.detail.ident, "LUKIS_TEKS") || !strcmp(lex.detail.ident, "lukis_teks")
	  || !strcmp(lex.detail.ident, "Lukis_Teks"))    lex.type = _LUKIS_TEKS;
  if (!strcmp(lex.detail.ident, "LUKIS_KOTAK") || !strcmp(lex.detail.ident, "lukis_kotak")
	  || !strcmp(lex.detail.ident, "Lukis_Kotak"))    lex.type = _LUKIS_KOTAK;
  if (!strcmp(lex.detail.ident, "LUKIS_KOTAKISI") || !strcmp(lex.detail.ident, "lukis_kotakisi")
	  || !strcmp(lex.detail.ident, "Lukis_KotakIsi"))    lex.type = _LUKIS_KOTAK_ISI;
  if (!strcmp(lex.detail.ident, "LUKIS_LINGKARAN") || !strcmp(lex.detail.ident, "lukis_lingkaran")
	  || !strcmp(lex.detail.ident, "Lukis_Lingkaran"))    lex.type = _LUKIS_LINGKARAN;
  if (!strcmp(lex.detail.ident, "LUKIS_LINGKARANISI") || !strcmp(lex.detail.ident, "lukis_lingkaranisi")
	  || !strcmp(lex.detail.ident, "Lukis_LingkaranIsi"))    lex.type = _LUKIS_LINGKARAN_ISI;

  if (!strcmp(lex.detail.ident, "SIMPAN_LUKISAN") || !strcmp(lex.detail.ident, "simpan_lukisan")
	  || !strcmp(lex.detail.ident, "Simpan_Lukisan"))    lex.type = _SIMPAN_LUKISAN;

  if (!strcmp(lex.detail.ident, "HAPUS_LATAR") || !strcmp(lex.detail.ident, "hapus_latar")
	  || !strcmp(lex.detail.ident, "Hapus_Latar"))    lex.type = _HAPUS_LATAR;
  if (!strcmp(lex.detail.ident, "HAPUS_BIDANG") || !strcmp(lex.detail.ident, "hapus_bidang")
	  || !strcmp(lex.detail.ident, "Hapus_Bidang"))    lex.type = _HAPUS_BIDANG;
  if (!strcmp(lex.detail.ident, "HAPUS_POLA") || !strcmp(lex.detail.ident, "hapus_pola")
	  || !strcmp(lex.detail.ident, "Hapus_Pola"))    lex.type = _HAPUS_POLA;
  if (!strcmp(lex.detail.ident, "POLA_WARNA") || !strcmp(lex.detail.ident, "pola_warna")
	  || !strcmp(lex.detail.ident, "Pola_Warna"))    lex.type = _POLA_WARNA;

  if (!strcmp(lex.detail.ident, "SET_ASAL") || !strcmp(lex.detail.ident, "set_asal")
	  || !strcmp(lex.detail.ident, "Set_Asal"))    lex.type = _SET_ASAL;
  if (!strcmp(lex.detail.ident, "SET_ASALBIDANG") || !strcmp(lex.detail.ident, "set_asalbidang")
	  || !strcmp(lex.detail.ident, "Set_AsalBidang"))    lex.type = _SET_ASALBIDANG;
  if (!strcmp(lex.detail.ident, "SET_POLA") || !strcmp(lex.detail.ident, "set_pola")
	  || !strcmp(lex.detail.ident, "Set_Pola"))    lex.type = _SET_ASAL;

  if (!strcmp(lex.detail.ident, "WARNA_PENA") || !strcmp(lex.detail.ident, "warna_pena")
	  || !strcmp(lex.detail.ident, "Warna_Pena"))    lex.type = _WARNA_PENA;
  if (!strcmp(lex.detail.ident, "WARNA_TRANSPARAN") || !strcmp(lex.detail.ident, "warna_transparan")
	  || !strcmp(lex.detail.ident, "Warna_Transparan"))    lex.type = _WARNA_TRANSPARAN;
  if (!strcmp(lex.detail.ident, "PUDAR_PENA") || !strcmp(lex.detail.ident, "pudar_pena")
	  || !strcmp(lex.detail.ident, "Pudar_Pena"))    lex.type = _PUDAR_PENA;
  if (!strcmp(lex.detail.ident, "PINDAH_PENA") || !strcmp(lex.detail.ident, "pindah_pena")
	  || !strcmp(lex.detail.ident, "Pindah_Pena"))    lex.type = _PINDAH_PENA;
  if (!strcmp(lex.detail.ident, "GESER_PENA") || !strcmp(lex.detail.ident, "geser_pena")
	  || !strcmp(lex.detail.ident, "Geser_Pena"))    lex.type = _GESER_PENA;
  if (!strcmp(lex.detail.ident, "KLIP_PENA") || !strcmp(lex.detail.ident, "klip_pena")
	  || !strcmp(lex.detail.ident, "Klip_Pena"))    lex.type = _KLIP_PENA;
  if (!strcmp(lex.detail.ident, "KLIP_LINGKARAN") || !strcmp(lex.detail.ident, "klip_lingkaran")
	  || !strcmp(lex.detail.ident, "Klip_Lingkaran"))    lex.type = _KLIP_LINGKARAN;
  if (!strcmp(lex.detail.ident, "KLIP_KOTAK") || !strcmp(lex.detail.ident, "klip_kotak")
	  || !strcmp(lex.detail.ident, "Klip_Kotak"))    lex.type = _KLIP_KOTAK;
  if (!strcmp(lex.detail.ident, "GORES_PENA") || !strcmp(lex.detail.ident, "gores_pena")
	  || !strcmp(lex.detail.ident, "Gores_Pena"))    lex.type = _GORES_PENA;
  if (!strcmp(lex.detail.ident, "GORES_PENA_JAGA") || !strcmp(lex.detail.ident, "gores_pena_jaga")
	  || !strcmp(lex.detail.ident, "Gores_Pena_Jaga"))    lex.type = _GORES_PENA_JAGA;
  if (!strcmp(lex.detail.ident, "LUKIS_PENA") || !strcmp(lex.detail.ident, "lukis_pena")
	  || !strcmp(lex.detail.ident, "Lukis_Pena"))    lex.type = _LUKIS_PENA;
  if (!strcmp(lex.detail.ident, "ISI_PENA") || !strcmp(lex.detail.ident, "isi_pena")
	  || !strcmp(lex.detail.ident, "Isi_Pena"))    lex.type = _ISI_PENA;
  if (!strcmp(lex.detail.ident, "ISI_PENA_JAGA") || !strcmp(lex.detail.ident, "isi_pena_jaga")
	  || !strcmp(lex.detail.ident, "Isi_Pena_Jaga"))    lex.type = _ISI_PENA_JAGA;
  if (!strcmp(lex.detail.ident, "TEBAL_GARIS") || !strcmp(lex.detail.ident, "tebal_garis")
	  || !strcmp(lex.detail.ident, "Tebal_Garis"))    lex.type = _TEBAL_GARIS;
  if (!strcmp(lex.detail.ident, "PUCUK_GARIS") || !strcmp(lex.detail.ident, "pucuk_garis")
	  || !strcmp(lex.detail.ident, "Pucuk_Garis"))    lex.type = _PUCUK_GARIS;
  if (!strcmp(lex.detail.ident, "BENTUK_SAMBUNGAN") || !strcmp(lex.detail.ident, "bentuk_sambungan")
	  || !strcmp(lex.detail.ident, "Bentuk_Sambungan"))    lex.type = _BENTUK_SAMBUNGAN;
  if (!strcmp(lex.detail.ident, "GARIS_PUTUS") || !strcmp(lex.detail.ident, "garis_putus")
	  || !strcmp(lex.detail.ident, "Garis_Putus"))    lex.type = _GARIS_PUTUS;
  if (!strcmp(lex.detail.ident, "ATRIBUT_TEKS") || !strcmp(lex.detail.ident, "atribut_teks")
	  || !strcmp(lex.detail.ident, "Atribut_Teks"))    lex.type = _ATRIBUT_TEKS;
  if (!strcmp(lex.detail.ident, "LEKUKAN_TEKS") || !strcmp(lex.detail.ident, "lekukan_teks")
	  || !strcmp(lex.detail.ident, "Lekukan_Teks"))    lex.type = _LEKUKAN_TEKS;
  if (!strcmp(lex.detail.ident, "LEKUKAN_BARU") || !strcmp(lex.detail.ident, "lekukan_baru")
	  || !strcmp(lex.detail.ident, "Lekukan_Baru"))    lex.type = _LEKUKAN_BARU;
  if (!strcmp(lex.detail.ident, "TUTUP_KURVA") || !strcmp(lex.detail.ident, "tutup_kurva")
	  || !strcmp(lex.detail.ident, "Tutup_Kurva"))    lex.type = _TUTUP_KURVA;

  if (!strcmp(lex.detail.ident, "AKSI_EKSPOS") || !strcmp(lex.detail.ident, "aksi_ekspos")
	  || !strcmp(lex.detail.ident, "Aksi_ekspos") || !strcmp(lex.detail.ident, "Aksi_Ekspos"))
	  lex.type = _AKSI_EKSPOS;
  if (!strcmp(lex.detail.ident, "AKSI_ATUR") || !strcmp(lex.detail.ident, "aksi_atur")
	  || !strcmp(lex.detail.ident, "Aksi_atur") || !strcmp(lex.detail.ident, "Aksi_Atur"))
	  lex.type = _AKSI_ATUR;

  if (!strcmp(lex.detail.ident, "EKSPOS_KANVAS") || !strcmp(lex.detail.ident, "ekspos_kanvas")
	  || !strcmp(lex.detail.ident, "Ekspos_kanvas") || !strcmp(lex.detail.ident, "Ekspos_Kanvas"))
	  lex.type = _EKSPOS_KANVAS;

  if (!strcmp(lex.detail.ident, "GESER_LATAR") || !strcmp(lex.detail.ident, "geser_latar")
	  || !strcmp(lex.detail.ident, "Geser_Latar"))    lex.type = _GESER_LATAR;
  if (!strcmp(lex.detail.ident, "SKALA_LATAR") || !strcmp(lex.detail.ident, "skala_latar")
	  || !strcmp(lex.detail.ident, "Skala_Latar"))    lex.type = _SKALA_LATAR;
  if (!strcmp(lex.detail.ident, "PUTAR_LATAR") || !strcmp(lex.detail.ident, "putar_latar")
	  || !strcmp(lex.detail.ident, "Putar_Latar"))    lex.type = _PUTAR_LATAR;

  if (!strcmp(lex.detail.ident, "DETAK_WAKTU") || !strcmp(lex.detail.ident, "detak_waktu")
	  || !strcmp(lex.detail.ident, "Detak_Waktu"))    lex.type = _DETAK_WAKTU;
  if (!strcmp(lex.detail.ident, "STOP_DETAK") || !strcmp(lex.detail.ident, "stop_detak")
	  || !strcmp(lex.detail.ident, "Stop_Detak"))    lex.type = _STOP_DETAK;
  if (!strcmp(lex.detail.ident, "HAPUS_PIXMAP") || !strcmp(lex.detail.ident, "hapus_pixmap")
	  || !strcmp(lex.detail.ident, "Hapus_Pixmap"))    lex.type = _HAPUS_PIXMAP;
  if (!strcmp(lex.detail.ident, "LUKIS_PIXMAP") || !strcmp(lex.detail.ident, "lukis_pixmap")
	  || !strcmp(lex.detail.ident, "Lukis_Pixmap"))    lex.type = _LUKIS_PIXMAP;
#endif

  if( ! strcmp(lex.detail.ident, "SAKLAR_HIDUP") || ! strcmp(lex.detail.ident, "saklar_hidup")
      || ! strcmp(lex.detail.ident, "Saklar_Hidup"))    lex.type = _SAKLAR_HIDUP;

  if( ! strcmp(lex.detail.ident, "SAKLAR_MATI") || ! strcmp(lex.detail.ident, "saklar_mati")
      || ! strcmp(lex.detail.ident, "Saklar_Mati"))    lex.type = _SAKLAR_MATI;


  if( ! strcmp(lex.detail.ident, "RUPA") || ! strcmp(lex.detail.ident, "rupa")
        || ! strcmp(lex.detail.ident, "Rupa"))    lex.type = _RUPA;
  if( ! strcmp(lex.detail.ident, "RUPA_HTML") || ! strcmp(lex.detail.ident, "rupa_html")
        || ! strcmp(lex.detail.ident, "Rupa_Html"))    lex.type = _RUPA;        


  if( ! strcmp(lex.detail.ident, "_CEK_MEMORI") || ! strcmp(lex.detail.ident, "_cek_memori")
      || ! strcmp(lex.detail.ident, "_Cek_Memori"))    lex.type = _CEK_MEMORI;

  return FALSE;
}


char *ToUpper(char *s)
{
    char *p='\0';

    for (p = s; *p; p++)  
        *p = toupper(*p); 
    return (s);           
}

char *ToLower(char *s)
{
    char *p='\0';

    for (p = s; *p; p++)  
        *p = tolower(*p); 
    return (s);           
}

