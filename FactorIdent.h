// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// Language Function (LF) as described in Int. Paper about BAIK 2009

#include "funcBendaBaru.h"
#include "funcMatematik.h"
#include "funcMatUntaian.h"
#include "funcArsip.h"
#include "funcKata.h"
#include "funcString.h"

#include "funcDirektori.h"

#ifndef S_SPLINT_S
#include "funcNetwork.h"
#endif

#include "funcOther.h"

#ifdef USE_GD
#include "funcGDGraphic.h"
#endif

#include "funcSystem.h"
#include "funcRs232.h"

#include "funcSqlTranslasi.h"

#ifdef USE_MYSQL
#include "funcMysql.h"
#endif

#ifdef USE_PGSQL
#include "funcPostgreSql.h"
#endif

#ifdef USE_OCI
#include "funcOracle.h"
#endif

#ifdef USE_SQLITE
#include "funcSQLite.h"
#endif

#ifdef USE_GTK2
#include "lyr/funcWinArsipTeks.h"
#include "lyr/funcWinCitra.h"
#include "lyr/funcWinDataBarisTabel.h"
#include "lyr/funcWinDataGambar.h"
#include "lyr/funcWinDialogPilihHuruf.h"
#include "lyr/funcWinDialogPilihWarna.h"
#include "lyr/funcWinDialogPilihArsip.h"
#include "lyr/funcWinExpander.h"
#include "lyr/funcWinIsiMenu.h"
#include "lyr/funcWinIsiMenuCek.h"
#include "lyr/funcWinKertas.h"
#include "lyr/funcWinLabel.h"
#include "lyr/funcWinMasukan.h"
#include "lyr/funcWinNilaiStatusMenuCek.h"
#include "lyr/funcWinNilaiTombolPutar.h"
#include "lyr/funcWinPilihan.h"
#include "lyr/funcWinRadioBtn.h"
#include "lyr/funcWinRadioBtnGroup.h"
#include "lyr/funcWinStatusCek.h"
#include "lyr/funcWinTabel.h"
#include "lyr/funcWinTeksKertas.h"
#include "lyr/funcWinTeksLabel.h"
#include "lyr/funcWinTeksMasukan.h"
#include "lyr/funcWinTeksPilihan.h"
#include "lyr/funcWinTeksPosisi.h"
#include "lyr/funcWinTeksTerpilih.h"
#include "lyr/funcWinTombol.h"
#include "lyr/funcWinTombolCek.h"
#include "lyr/funcWinTombolPutar.h"
#include "lyr/funcWinTotalBarisTabel.h"

#include "lyr/funcWinIsiSimpulRanting.h"
#include "lyr/funcWinModelRanting.h"
#include "lyr/funcWinKolomRanting.h"
#include "lyr/funcWinTeksRanting.h"

#include "lyr/funcWinUTF.h"

extern char TANGGAL_TERPILIH[64];

extern int MOUSE_POS_X;
extern int MOUSE_POS_Y;
extern int MOUSE_TIME;
extern int MOUSE_BUTTON;

extern int EKSPOS_POS_X;
extern int EKSPOS_POS_Y;
extern int EKSPOS_WIDTH;
extern int EKSPOS_HEIGHT;

extern int KEYBOARD_VALUE;
extern int KEYBOARD_STATE;
extern char *KEYBOARD_STRING;

#include "lyr/funcCairoRuangTeks.h"
#include "lyr/funcCairoLebarRuangTeks.h"
#include "lyr/funcCairoTinggiRuangTeks.h"

#include "lyr/funcCairoBidangGambar.h"
#include "lyr/funcCairoLatarGambar.h"
#include "lyr/funcCairoPolaLinier.h"
#include "lyr/funcCairoPolaRadial.h"
#include "lyr/funcCairoAmbilPng.h"
#include "lyr/funcCairoLatarLayar.h"

#include "lyr/funcCairoBaikPixmap.h"
#include "lyr/funcWinAlokasiX.h"
#include "lyr/funcWinAlokasiY.h"
#include "lyr/funcWinAlokasiLebar.h"
#include "lyr/funcWinAlokasiTinggi.h"

#include "lyr/funcWinPrinting.h"

GtkPrintSettings *BAIK_PRINT_settings;

#include "lyr/funcWinTombolBerikon.h"
#endif


#ifdef USE_GTK3

#include <glib.h>
#include <glib/gprintf.h>

#include "lyr3/funcWinArsipTeks.h"
#include "lyr3/funcWinCitra.h"
#include "lyr3/funcWinDataBarisTabel.h"
#include "lyr3/funcWinDataGambar.h"

#include "lyr3/funcWinDialogPilihHuruf.h"
#include "lyr3/funcWinDialogPilihWarna.h"
#include "lyr3/funcWinDialogPilihArsip.h"

#include "lyr3/funcWinExpander.h"
#include "lyr3/funcWinIsiMenu.h"
#include "lyr3/funcWinIsiMenuCek.h"
#include "lyr3/funcWinKertas.h"
#include "lyr3/funcWinLabel.h"
#include "lyr3/funcWinMasukan.h"
#include "lyr3/funcWinNilaiStatusMenuCek.h"
#include "lyr3/funcWinNilaiTombolPutar.h"
#include "lyr3/funcWinPilihan.h"
#include "lyr3/funcWinRadioBtn.h"
#include "lyr3/funcWinRadioBtnGroup.h"
#include "lyr3/funcWinStatusCek.h"
#include "lyr3/funcWinTabel.h"
#include "lyr3/funcWinTeksKertas.h"
#include "lyr3/funcWinTeksLabel.h"
#include "lyr3/funcWinTeksMasukan.h"
#include "lyr3/funcWinTeksPilihan.h"
#include "lyr3/funcWinTeksPosisi.h"
#include "lyr3/funcWinTeksTerpilih.h"
#include "lyr3/funcWinTombol.h"
#include "lyr3/funcWinTombolCek.h"
#include "lyr3/funcWinTombolPutar.h"
#include "lyr3/funcWinTotalBarisTabel.h"

#include "lyr3/funcWinIsiSimpulRanting.h"
#include "lyr3/funcWinModelRanting.h"
#include "lyr3/funcWinKolomRanting.h"
#include "lyr3/funcWinTeksRanting.h"

#include "lyr3/funcWinUTF.h"

extern char TANGGAL_TERPILIH[64];

extern int MOUSE_POS_X;
extern int MOUSE_POS_Y;
extern int MOUSE_TIME;
extern int MOUSE_BUTTON;

extern int EKSPOS_POS_X;
extern int EKSPOS_POS_Y;
extern int EKSPOS_WIDTH;
extern int EKSPOS_HEIGHT;

extern int KEYBOARD_VALUE;
extern int KEYBOARD_STATE;
extern char *KEYBOARD_STRING;

#include "lyr3/funcCairoRuangTeks.h"
#include "lyr3/funcCairoLebarRuangTeks.h"
#include "lyr3/funcCairoTinggiRuangTeks.h"

#include "lyr3/funcCairoBidangGambar.h"
#include "lyr3/funcCairoLatarGambar.h"
#include "lyr3/funcCairoPolaLinier.h"
#include "lyr3/funcCairoPolaRadial.h"
#include "lyr3/funcCairoAmbilPng.h"
#include "lyr3/funcCairoLatarLayar.h"

#include "lyr3/funcCairoBaikPixmap.h"

//#include "lyr3/funcWinAlokasiX.h"
//#include "lyr3/funcWinAlokasiY.h"
//#include "lyr3/funcWinAlokasiLebar.h"
//#include "lyr3/funcWinAlokasiTinggi.h"

#include "lyr3/funcWinPrinting.h"

GtkPrintSettings *BAIK_PRINT_settings;

#include "lyr3/funcWinTombolBerikon.h"
#endif


#ifdef USE_PDF
#include "pdf/funcPDFHalaman.h"
#include "pdf/funcPDFLebar.h"
#include "pdf/funcPDFTinggi.h"
#include "pdf/funcPDFAmbilPng.h"
#include "pdf/funcPDFAmbilJpg.h"
#endif

#ifdef USE_SSL
#include "ssl/baik_sandi.h"
#include "ssl/funcSSLdes.h"
#include "ssl/funcSSL3des.h"
#include "ssl/funcSSLrc4.h"
#include "ssl/funcSSLaes128cbc.h"
#include "ssl/funcSSLaes128ecb.h"
#include "ssl/funcSSLblowfishcbc.h"
#include "ssl/funcSSLblowfishcfb.h"
#endif

#ifdef USE_CGI
#include "cgi/funcWebCgi.h"
#endif

VAL_LABEL FactorIdent( char Funcword[MAX_STRING_LEN])
{
  VAL_LABEL datx;

  char   tmp_str[MAX_STRING_LEN];
  char   dat_a[MAX_STRING_LEN];

  //printf("Enter Factor\n");

  memset(&datx, '\0', sizeof(datx));
  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&tmp_str, '\0', sizeof(tmp_str));

      /* ======================================================== */
      /* SAKLAR_STATUS    ======================================= */
      /* ======================================================== */
      if( !strcmp(Funcword, "SAKLAR_STATUS")   ||
		  !strcmp(Funcword, "saklar_status") ) {
          datx = funcSaklarStatus();


	  /* ======================================================== */
	  /* AIN              ======================================= */
	  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ANALOG_STATUS") ||
		  !strcmp(Funcword, "analog_status") ||
		  !strcmp(Funcword, "AIN_status") ||
		  !strcmp(Funcword, "ain_status")) {
		  datx = funcAnalogPortStatus();


      /* ======================================================== */
      /* AKAR             ======================================= */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "AKAR")   ||
		  !strcmp(Funcword, "akar") ) {
          datx = funcAkar();


      /* ======================================================== */
      /* ABSOLUT              =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "ABSOLUT") || 
                 !strcmp(Funcword, "absolut") ||
                 !strcmp(Funcword, "ABS") ||
                 !strcmp(Funcword, "abs") ) { 
          datx = funcAbs();

      /* ======================================================== */
      /* SINUS             ====================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "SINUS") ||
                 !strcmp(Funcword, "sinus") ||
                 !strcmp(Funcword, "SIN")   ||
                 !strcmp(Funcword, "sin") ) { 
         /* printf("SIN function\n"); */
         datx = funcSinus();

	  /* ======================================================== */
      /* COSINUS             ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "COSINUS") || 
                 !strcmp(Funcword, "cosinus") ||
                 !strcmp(Funcword, "COS")     ||
                 !strcmp(Funcword, "cos") ) { 
         /* printf("COS function\n"); */
         datx = funcCosinus();

      /* ======================================================== */
      /* FAKTORIAL            =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "FAKTORIAL") || 
                 !strcmp(Funcword, "faktorial") ) { 
         /* printf("FAKTORIAL function\n"); */
		 datx = funcFaktorial();

      /* ======================================================== */
      /* PERMUTASI           ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "PERMUTASI")  || 
                !strcmp(Funcword, "permutasi") ) { 
        /* printf("PERMUTASI function\n");  */
		 datx = funcPermutasi();

      /* ======================================================== */
      /* KOMBINASI           ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "KOMBINASI")  || 
                !strcmp(Funcword, "kombinasi") ) { 
        /* printf("KOMBINASI function\n");  */
		 datx = funcKombinasi();

      /* ======================================================== */
      /* GCD                 ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "GCD")  || 
                !strcmp(Funcword, "gcd") ||
                !strcmp(Funcword, "FAKTOR_TERBESAR") ||
                !strcmp(Funcword, "faktor_terbesar") ) { 
        /* printf("GCD function\n");  */
		 datx = funcGcd();

      /* ======================================================== */
      /* JUMLAH_UNTAIAN       =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "JUMLAH_UNTAIAN") || 
                 !strcmp(Funcword, "jumlah_untaian") ) { 
         /* printf("JUMLAH_UNTAIAN function\n"); */
		 datx = funcJumUntaian();

      /* ======================================================== */
      /* RATARATA_UNTAIAN     =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "RATARATA_UNTAIAN") || 
                 !strcmp(Funcword, "ratarata_untaian") ) { 
         /* printf("JUMLAH_UNTAIAN function\n"); */
		 datx = funcAveUntaian();

      /* ======================================================== */
      /* VARIAN_UNTAIAN       =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "VARIAN_UNTAIAN") || 
                 !strcmp(Funcword, "varian_untaian") ) { 
         /* printf("VARIAN_UNTAIAN function\n"); */
		 datx = funcVarUntaian();

      /* ======================================================== */
      /* STD_DEVIASI_UNTAIAN   ================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "STD_DEVIASI_UNTAIAN") || 
                 !strcmp(Funcword, "std_deviasi_untaian") ) { 
         /* printf("STD_DEVIASI function\n"); */
		 datx = funcStdDevUntaian();

      /* ======================================================== */
      /* APAKAH_ANGKA             =============================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "ANGKA_KAH") || 
                 !strcmp(Funcword, "angka_kah") ) { 
         /* printf("BIL function\n"); */
		 datx = funcANGKA_KAH();

      /* ======================================================== */
      /* APAKAH_HURUF             =============================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "HURUF_KAH") || 
                 !strcmp(Funcword, "huruf_kah") ) { 
         /* printf("HURUF function\n"); */
		 datx = funcHURUF_KAH();

      /* ======================================================== */
      /* KE_ANGKA             =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "KE_ANGKA") || 
                 !strcmp(Funcword, "ke_angka") ) { 
         /* printf("HURUF function\n"); */
		 datx = funcKE_ANGKA();

      /* ======================================================== */
      /* KE_HURUF             =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "KE_HURUF") || 
                 !strcmp(Funcword, "ke_huruf") ) { 
         /* printf("HURUF function\n"); */
		 datx = funcKE_HURUF();

      /* ======================================================== */
      /* HURUF_NO             =================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "HURUF_NO")  || 
                !strcmp(Funcword, "huruf_no") ) { 
        /* printf("HURUF_NO function\n"); */
		 datx = funcHURUF_NO();

	  /* ======================================================== */
      /* SAMBUNG             ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "SAMBUNG")  || !strcmp(Funcword, "Sambung") ||
                !strcmp(Funcword, "sambung") ) { 
        /* printf("SAMBUNG function\n");  */
		 datx = funcSambung();

      /* ======================================================== */
      /* GABUNG              ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "GABUNG")  || !strcmp(Funcword, "Gabung") ||
                !strcmp(Funcword, "gabung") ) { 
        /* printf("GABUNG function\n");  */
		 datx = funcGabung();

      /* ======================================================== */
      /* EKSPRESI                ================================ */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "EKSPRESI")  || 
                 !strcmp(Funcword, "ekspresi") ) { 
        /* printf("EKSPRESI function\n"); */
		 datx = funcEKSPRESI();


      /* ======================================================== */
      /* WAKTU                     ============================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "WAKTU") || 
                ! strcmp(Funcword, "waktu") ) { 
          /*  printf("WAKTU function\n"); */
          strcpy( datx.str, createTime2() );
          datx.datatype = 3;

      /* ======================================================== */
      /* HARI                      ============================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "HARI") || 
                ! strcmp(Funcword, "hari") ) { 
          /*  printf("WAKTU function\n"); */
          strcpy( datx.str, getDay2() );
          datx.datatype = 3;

      /* ======================================================== */
      /* RANDOM      0 <= rnd() < 1    ========================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "RANDOM") || 
                ! strcmp(Funcword, "random") ||
                ! strcmp(Funcword, "ACAK") ||
                ! strcmp(Funcword, "acak") ) { 
          /*  printf("RANDOM function\n"); */
          datx.floatdata = hhrnd();
          datx.datatype  = 1;

#ifndef S_SPLINT_S
      /* ======================================================== */
      /* PING                          ========================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "PING") || 
                ! strcmp(Funcword, "ping") ||
                ! strcmp(Funcword, "Ping") ||
                ! strcmp(Funcword, "tembak") ) { 
          /*  printf("PING  hostname, exectime, timeout \n"); */
		 datx = funcPing();

      /* ======================================================== */
      /* SOKET                     ============================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "SOKET") || 
                ! strcmp(Funcword, "soket") ) { 
          /*  printf("SOKET function\n"); */
          #ifdef WINDOWS
           datx.sock = initSocket("tcp");
          #else
           datx.sock = ux_initSocket("tcp");
          #endif
          datx.datatype = 4;

      /* ======================================================== */
      /* SOKET UDP                 ============================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "SOKET_UDP") || 
                ! strcmp(Funcword, "soket_udp") ) { 
          /*  printf("SOKET function\n"); */
          #ifdef WINDOWS
           datx.sock = initSocket("udp");
          #else
           datx.sock = ux_initSocket("udp");
          #endif
          datx.datatype = 5;

      /* ======================================================== */
      /* IKAT_SOKET             ================================= */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "IKAT_SOKET") || 
                !strcmp(Funcword, "ikat_soket") ) { 
        /* printf("ikat soket function\n"); */
		 datx = funcIKAT_SOKET();

      /* ======================================================== */
      /* TRIMA_SOKET             ================================ */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "TRIMA_SOKET") || 
                !strcmp(Funcword, "trima_soket") ) { 
         /* printf("trima soket function\n"); */
		 datx = funcTRIMA_SOKET();

      /* ======================================================== */
      /* BACA_SOKET              ================================ */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "BACA_SOKET") || 
                !strcmp(Funcword, "baca_soket") ) { 
         /* printf("baca soket function\n"); */
		 datx = funcBACA_SOKET();

      /* ======================================================== */
      /* TULIS_SOKET            ================================= */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "TULIS_SOKET") || 
                !strcmp(Funcword, "tulis_soket") ) { 
        /* printf("tulis soket function\n"); */
		 datx = funcTULIS_SOKET();

      /* ======================================================== */
      /* KONEK_SOKET            ================================= */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "KONEK_SOKET") || 
                !strcmp(Funcword, "konek_soket") ) {
		 datx = funcKONEK_SOKET();
#endif

      /* ======================================================== */
      /* LINGKUP              =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "LINGKUP") || 
                 !strcmp(Funcword, "lingkup") ) { 
         /* printf("LINGKUP function\n"); */
		 datx = funcLingkup();

      /* ======================================================== */
      /* KONFIGURASI            ================================ */
      /* ======================================================== */
      } else if( strncmp(Funcword, "KONFIGURASI", 11) == 0 || 
                strncmp(Funcword, "konfigurasi", 11) == 0) { 

		 datx = funcKONFIGURASI();

      /* ======================================================== */
      /* AMBIL_DIR             =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "AMBIL_DIR") || 
                 !strcmp(Funcword, "ambil_dir") ) { 
         /* printf("AMBIL_DIR function\n"); */
         datx = funcAMBIL_DIR();

      /* ======================================================== */
      /* BUAT_DIR             =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "BUAT_DIR") || 
                 !strcmp(Funcword, "buat_dir") ) { 
         /* printf("BUAT_DIR function\n"); */
		 datx = funcBUAT_DIR();

      /* ======================================================== */
      /* HAPUS_DIR            =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "HAPUS_DIR") || 
                 !strcmp(Funcword, "hapus_dir") ) { 
         /* printf("HAPUS_DIR function\n"); */
		 datx = funcHAPUS_DIR();

      /* ======================================================== */
      /* GANTI_DIR            =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "GANTI_DIR") || 
                 !strcmp(Funcword, "ganti_dir") ) { 
         /* printf("GANTI_DIR function\n"); */
		 datx = funcGANTI_DIR();

      /* ======================================================== */
      /* POSISI_DIR            =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "POSISI_DIR") || 
                 !strcmp(Funcword, "posisi_dir") ) { 
         /* printf("GANTI_DIR function\n"); */
		 datx = funcPOSISI_DIR();

	  // --------------------------GD -----------------------------

      #ifdef USE_GD
      /* ======================================================== */
      /* GD GAMBAR            =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "GAMBAR") || 
                 !strcmp(Funcword, "Gambar") ||
                 !strcmp(Funcword, "gambar") ) { 
        // printf("GAMBAR function\n");
        datx.datatype = 20; /* gdImagePtr */
        datx.gdimg = NULL;

      /* ======================================================== */
      /* GD LEBARGAMBAR       =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "LEBARGAMBAR") || 
                 !strcmp(Funcword, "lebargambar") ||
                 !strcmp(Funcword, "LebarGambar") ) { 
         /* printf("LEBARGAMBAR function\n"); */
		 datx = funcLebarGambar();

      /* ======================================================== */
      /* GD PANJANGGAMBAR       =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "PANJANGGAMBAR") || 
                 !strcmp(Funcword, "panjanggambar") ||
                 !strcmp(Funcword, "PanjangGambar") ) { 
         /* printf("PANJANGGAMBAR function\n"); */
		 datx = funcPanjangGambar();

      /* ======================================================== */
      /* GD TITIK            =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "TITIK") || 
                 !strcmp(Funcword, "titik") ) { 
         /* printf("TITIK function\n"); */
        datx.datatype = 21; /* gdPoint */
        datx.gdimg = NULL;

      /* ======================================================== */
      /* GD HURUFKECIL            =================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "HURUFKECIL")  || 
                !strcmp(Funcword, "hurufkecil")  ||
                !strcmp(Funcword, "Hurufkecil")  ||
                !strcmp(Funcword, "HurufKecil")  ) { 
        /* printf("HURUFKECIL function\n");  */
        datx.gdfont   = gdFontGetSmall();      /* small     */
        datx.datatype = 22;                    /* gdFontPtr */
        datx.gdimg    = NULL;

      /* ======================================================== */
      /* GD HURUFBESAR        =================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "HURUFBESAR")  || 
                !strcmp(Funcword, "hurufbesar")  ||
                !strcmp(Funcword, "Hurufbesar")  ||
                !strcmp(Funcword, "HurufBesar")  ) { 
        /* printf("HURUFBESAR function\n");  */
        datx.gdfont   = gdFontGetLarge();      /* large     */
        datx.datatype = 22;                    /* gdFontPtr */
        datx.gdimg    = NULL;

      /* ======================================================== */
      /* GD HURUFSEDANG       =================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "HURUFSEDANG")  || 
                !strcmp(Funcword, "hurufsedang")  ||
                !strcmp(Funcword, "Hurufsedang")  ||
                !strcmp(Funcword, "HurufSedang")  ) { 
        /* printf("HURUFKECIL function\n");  */
        datx.gdfont   = gdFontGetMediumBold(); /* medium bold  */
        datx.datatype = 22;                    /* gdFontPtr    */
        datx.gdimg    = NULL;

      /* ======================================================== */
      /* GD HURUFMINI            =================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "HURUFMINI")  || 
                !strcmp(Funcword, "hurufmini")  ||
                !strcmp(Funcword, "Hurufmini")  ||
                !strcmp(Funcword, "HurufMini")  ) { 
        /* printf("HURUFKECIL function\n");  */
        datx.gdfont   = gdFontGetTiny();       /* tiny     */
        datx.datatype = 22;                    /* gdFontPtr */
        datx.gdimg    = NULL;

      /* ======================================================== */
      /* GD LEBARHURUF        =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "LEBARHURUF") || 
                 !strcmp(Funcword, "lebarhuruf") ||
                 !strcmp(Funcword, "LebarHuruf") ) { 
         /* printf("LEBARHURUF function\n"); */
		 datx = funcLebarHuruf();

      /* ======================================================== */
      /* GD TINGGIHURUF        =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "TINGGIHURUF") || 
                 !strcmp(Funcword, "tinggihuruf") ||
                 !strcmp(Funcword, "TinggiHuruf") ) { 
         /* printf("TINGGIHURUF function\n"); */
		 datx = funcTinggiHuruf();

      /* ======================================================== */
      /* GD BUATGAMBAR       ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "BUATGAMBAR")  || 
                !strcmp(Funcword, "buatgambar")  ||
                !strcmp(Funcword, "Buatgambar")  ||
                !strcmp(Funcword, "BuatGambar")  ) { 
        /* printf("BUATGAMBAR function\n");  */
		 datx = funcBuatGambar();


      /* ======================================================== */
      /* GD WARNAGAMBAR       ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "WARNAGAMBAR")  || 
                !strcmp(Funcword, "warnagambar")  ||
                !strcmp(Funcword, "Warnagambar")  ||
                !strcmp(Funcword, "WarnaGambar")  ) { 
        /* printf("WARNAGAMBAR function\n");  */
		 datx = funcWarnaGambar();

      #endif
	  // --------------------------GD END---------------------------

      /* ======================================================== */
      /* ARSIP / FILE           ================================= */
      /* t - tulis              */
      /* b - baca               */
      /* s - sambung            */
      /* ======================================================== */
	  } else if(!strcmp(Funcword, "FILE") || !strcmp(Funcword, "file") ||
                !strcmp(Funcword, "ARSIP") || !strcmp(Funcword, "arsip") ) { 
        /* printf("FILE function\n"); */
		 datx = funcArsip();

      /* ======================================================== */
      /* BACA_ARSIP             ================================= */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "BACA_ARSIP") ||
                !strcmp(Funcword, "baca_arsip") ) { 
        /* printf("BACA_ARSIP function\n"); */
		 datx = funcBacaArsip();

      #ifdef USE_GTK2
      /* ======================================================== */
      /* BACA_TEKS             ================================= */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "BACA_TEKS") ||
                !strcmp(Funcword, "baca_teks") ) {
                datx = funcBacaTeks();
      #endif

      #ifdef USE_GTK3
				/* ======================================================== */
				/* BACA_TEKS             ================================= */
				/* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BACA_TEKS") ||
		  !strcmp(Funcword, "baca_teks")) {
		  datx = funcBacaTeks();
      #endif
      
      /* ======================================================== */
      /* APAKAH_ARSIP          =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "APAKAH_ARSIP") || 
                 !strcmp(Funcword, "apakah_arsip") ) { 
         /* printf("APAKAH_ARSIP function\n"); */
		 datx = funcApakahArsip();

      /* ======================================================== */
      /* BESAR_ARSIP          =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "BESAR_ARSIP") || 
                 !strcmp(Funcword, "besar_arsip") ) { 
         /* printf("BESAR_ARSIP function\n"); */
		 datx = funcBesarArsip();

      /* ======================================================== */
      /* WAKTU_AKSES_ARSIP    =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "WAKTU_AKSES_ARSIP") || 
                 !strcmp(Funcword, "waktu_akses_arsip") ) { 
         /* printf("WAKTU_AKSES_ARSIP function\n"); */
		 datx = funcWaktuAksesArsip();

      /* ======================================================== */
      /* WAKTU_RUBAH_ARSIP    =================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "WAKTU_RUBAH_ARSIP") || 
                 !strcmp(Funcword, "waktu_rubah_arsip") ) { 
         /* printf("WAKTU_RUBAH_ARSIP function\n"); */
		 datx = funcWaktuRubahArsip();

      /* ======================================================== */

      #ifdef USE_MYSQL

      /* ======================================================== */

      /* ======================================================== */
      /* MYSQL_KONEKSI       ==================================== */
      /* ======================================================== */	  
	  } else if(!strcmp(Funcword, "MYSQL_KONEKSI") ||
                !strcmp(Funcword, "mysql_koneksi") ||
                !strcmp(Funcword, "Mysql_koneksi") ||
                !strcmp(Funcword, "Mysql_Koneksi") ) { 
        /* printf("MYSQL_KONEKSI function\n"); */
		 datx = funcMYSQL_KONEKSI();

      /* ======================================================== */
      } else if(!strcmp(Funcword, "MYSQL_HASIL") ||
                !strcmp(Funcword, "mysql_hasil") ||
                !strcmp(Funcword, "Mysql_hasil") ||
                !strcmp(Funcword, "Mysql_Hasil") ) { 
        /* printf("MYSQL_HASIL function\n"); */
        datx = funcMYSQL_HASIL();
        
      /* ======================================================== */
      } else if(!strcmp(Funcword, "MYSQL_STATUS") ||
                !strcmp(Funcword, "mysql_status") ||
                !strcmp(Funcword, "Mysql_status") ||
                !strcmp(Funcword, "Mysql_Status") ) { 
        /* printf("MYSQL_STATUS function\n"); */
        datx = funcMYSQL_RESULT_STATUS();        

      /* ======================================================== */
      /* MYSQL_TOTAL         ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "MYSQL_TOTAL") || 
                 !strcmp(Funcword, "mysql_total") ||
                 !strcmp(Funcword, "Mysql_total")     ||
                 !strcmp(Funcword, "Mysql_Total") ) { 
         /* printf("MYSQL_TOTAL function\n"); */
		 datx = funcMYSQL_TOTAL();

      /* ======================================================== */
      /* MYSQL_NAMAKOLOM     ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "MYSQL_NAMAKOLOM") || 
                 !strcmp(Funcword, "mysql_namakolom") ||
                 !strcmp(Funcword, "Mysql_namakolom")     ||
                 !strcmp(Funcword, "Mysql_Namakolom") ) { 
         /* printf("MYSQL_NAMAKOLOM function\n"); */
		 datx = funcMYSQL_NAMAKOLOM();

      /* ======================================================== */
      /* MYSQL_ISIDATA       ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "MYSQL_ISIDATA") || 
                 !strcmp(Funcword, "mysql_isidata") ||
                 !strcmp(Funcword, "Mysql_isidata")     ||
                 !strcmp(Funcword, "Mysql_IsiData") ) { 
         /* printf("MYSQL_DATA function\n"); */
		 datx = funcMYSQL_ISIDATA();

      /* ======================================================== */

      #endif

      /* ======================================================== */

      #ifdef USE_PGSQL

      /* ======================================================== */

      /* ======================================================== */
      /* PGSQL_KONEKSI       ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "PGSQL_KONEKSI") ||
                !strcmp(Funcword, "pgsql_koneksi") ||
                !strcmp(Funcword, "Pgsql_koneksi") ||
                !strcmp(Funcword, "Pgsql_Koneksi") ) { 
        /* printf("PGSQL_KONEKSI function\n"); */
		 datx = funcPGSQL_KONEKSI();

      /* ======================================================== */
      } else if(!strcmp(Funcword, "PGSQL_HASIL") ||
                !strcmp(Funcword, "pgsql_hasil") ||
                !strcmp(Funcword, "Pgsql_hasil") ||
                !strcmp(Funcword, "Pgsql_Hasil") ) { 
        /* printf("MYSQL_HASIL function\n"); */
        datx = funcPGSQL_HASIL();

      /* ======================================================== */
      } else if(!strcmp(Funcword, "PGSQL_STATUS") ||
                !strcmp(Funcword, "pgsql_status") ||
                !strcmp(Funcword, "Pgsql_status") ||
                !strcmp(Funcword, "Pgsql_Status") ) { 
        /* printf("PGSQL_STATUS function\n"); */
        datx = funcPGSQL_RESULT_STATUS();        


      /* ======================================================== */
      /* PGSQL_TOTAL         ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "PGSQL_TOTAL") || 
                 !strcmp(Funcword, "pgsql_total") ||
                 !strcmp(Funcword, "Pgsql_total")     ||
                 !strcmp(Funcword, "Pgsql_Total") ) { 
         /* printf("MYSQL_TOTAL function\n"); */
		 datx = funcPGSQL_TOTAL();

      /* ======================================================== */
      /* PGSQL_NAMAKOLOM     ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "PGSQL_NAMAKOLOM") || 
                 !strcmp(Funcword, "pgsql_namakolom") ||
                 !strcmp(Funcword, "Pgsql_namakolom")     ||
                 !strcmp(Funcword, "Pgsql_Namakolom") ) { 
         /* printf("MYSQL_NAMAKOLOM function\n"); */
		 datx = funcPGSQL_NAMAKOLOM();

      /* ======================================================== */
      /* PGSQL_ISIDATA       ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "PGSQL_ISIDATA") || 
                 !strcmp(Funcword, "pgsql_isidata") ||
                 !strcmp(Funcword, "Pgsql_isidata")     ||
                 !strcmp(Funcword, "Pgsql_IsiData") ) { 
         /* printf("MYSQL_DATA function\n"); */
		 datx = funcPGSQL_ISIDATA();

      /* ======================================================== */

      #endif

      /* ======================================================== */

      /* ======================================================== */

      #ifdef USE_OCI

      /* ======================================================== */

      /* ======================================================== */
      /* ORADB_KONEKSI       ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "ORADB_KONEKSI") ||
                !strcmp(Funcword, "oradb_koneksi") ||
                !strcmp(Funcword, "Oradb_koneksi") ||
                !strcmp(Funcword, "Oradb_Koneksi") ) { 
          /* printf("PGSQL_KONEKSI function\n"); */
		  datx = funcORADB_KONEKSI();

      /* ======================================================== */
      /* ORADB_HASIL         ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "ORADB_HASIL") ||
                !strcmp(Funcword, "oradb_hasil") ||
                !strcmp(Funcword, "Oradb_hasil") ||
                !strcmp(Funcword, "Oradb_Hasil") ) { 
          /* printf("MYSQL_HASIL function\n"); */
          datx = funcORADB_HASIL();
          
          
      /* ======================================================== */
      /* ORADB_STATUS         ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "ORADB_STATUS") ||
                !strcmp(Funcword, "oradb_status") ||
                !strcmp(Funcword, "Oradb_status") ||
                !strcmp(Funcword, "Oradb_Status") ) { 
          /* printf("ORADB_STATUS function\n"); */
          datx = funcORADB_RESULT_STATUS();          


      /* ======================================================== */
      /* ORADB_TOTAL         ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "ORADB_TOTAL") || 
                 !strcmp(Funcword, "oradb_total") ||
                 !strcmp(Funcword, "Oradb_total")     ||
                 !strcmp(Funcword, "Oradb_Total") ) { 
          /* printf("ORADB_TOTAL function\n"); */
		  datx = funcORADB_TOTAL();

      /* ======================================================== */
      /* ORADB_NAMAKOLOM     ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "ORADB_NAMAKOLOM") || 
                 !strcmp(Funcword, "oradb_namakolom") ||
                 !strcmp(Funcword, "Oradb_namakolom")     ||
                 !strcmp(Funcword, "Oradb_Namakolom") ) { 
          /* printf("ORADB_NAMAKOLOM function\n"); */
		  datx = funcORADB_NAMAKOLOM();

      /* ======================================================== */
      /* ORADB_ISIDATA       ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "ORADB_ISIDATA") || 
                 !strcmp(Funcword, "oradb_isidata") ||
                 !strcmp(Funcword, "Oradb_isidata")     ||
                 !strcmp(Funcword, "Oradb_IsiData") ) { 
          /* printf("ORADB_DATA function\n"); */
		  datx = funcORADB_ISIDATA();

      /* ======================================================== */

      #endif

      /* ======================================================== */


      /* ======================================================== */

      #ifdef USE_SQLITE

      /* ======================================================== */

      /* ======================================================== */
      /* SQLITE_KONEKSI       ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "SQLITE_KONEKSI") ||
                !strcmp(Funcword, "sqlite_koneksi") ||
                !strcmp(Funcword, "Sqlite_koneksi") ||
                !strcmp(Funcword, "Sqlite_Koneksi") ) { 
          /* printf("SQLITE_KONEKSI function\n"); */
		  datx = funcSQLITE_KONEKSI();


      /* ======================================================== */
      } else if(!strcmp(Funcword, "SQLITE_HASIL") ||
                !strcmp(Funcword, "sqlite_hasil") ||
                !strcmp(Funcword, "Sqlite_hasil") ||
                !strcmp(Funcword, "Sqlite_Hasil") ) { 
          /* printf("SQLITE_HASIL function\n"); */
          datx = funcSQLITE_HASIL();
          
      /* ======================================================== */
      } else if(!strcmp(Funcword, "SQLITE_STATUS") ||
                !strcmp(Funcword, "sqlite_status") ||
                !strcmp(Funcword, "Sqlite_status") ||
                !strcmp(Funcword, "Sqlite_Status") ) { 
          /* printf("SQLITE_STATUS function\n"); */
          datx = funcSQLITE_RESULT_STATUS();          

      /* ======================================================== */
      /* SQLITE_TOTAL         ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "SQLITE_TOTAL") || 
                 !strcmp(Funcword, "sqlite_total") ||
                 !strcmp(Funcword, "Sqlite_total")     ||
                 !strcmp(Funcword, "Sqlite_Total") ) { 
          /* printf("SQLITE_TOTAL function\n"); */
		  datx = funcSQLITE_TOTAL();

	  /* ======================================================== */
      /* SQLITE_NAMAKOLOM     ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "SQLITE_NAMAKOLOM") || 
                 !strcmp(Funcword, "sqlite_namakolom") ||
                 !strcmp(Funcword, "Sqlite_namakolom")     ||
                 !strcmp(Funcword, "Sqlite_Namakolom") ) { 
          /* printf("SQLITE_NAMAKOLOM function\n"); */
		  datx = funcSQLITE_NAMAKOLOM();

      /* ======================================================== */
      /* SQLITE_ISIDATA       ==================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "SQLITE_ISIDATA") || 
                 !strcmp(Funcword, "sqlite_isidata") ||
                 !strcmp(Funcword, "Sqlite_isidata")     ||
                 !strcmp(Funcword, "Sqlite_IsiData") ) { 
          /* printf("SQLITE_ISIDATA function\n"); */
		  datx = funcSQLITE_ISIDATA();

      /* ======================================================== */
      #endif
      /* ======================================================== */

      /* ======================================================== */

 










#ifdef USE_GTK3

		  /* ======================================================== */

		  /* ======================================================== */
		  /* LAYAR                 ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LAYAR") ||
		  !strcmp(Funcword, "layar")) {
		  //printf("LAYAR function\n");
		  datx.widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 0;  // window
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* KANVAS                ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KANVAS") ||
		  !strcmp(Funcword, "kanvas")) {
		  //printf("KANVAS function - gtk_drawing_area_new\n");
		  datx.widget = gtk_drawing_area_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 20; // window drawing area
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* CITRA                 ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "CITRA") ||
		  !strcmp(Funcword, "citra") ||
		  !strcmp(Funcword, "Citra")) {
		  datx = funcWinCitra();

		  /* ======================================================== */
		  /* LAYAR_GULUNG          ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LAYAR_GULUNG") ||
		  !strcmp(Funcword, "layar_gulung")) {
		  // printf("LAYAR_GULUNG function\n");
		  datx.widget = gtk_scrolled_window_new(NULL, NULL);
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 21; // scrolled window
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* ALAS_TETAP            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ALAS_TETAP") ||
		  !strcmp(Funcword, "alas_tetap") ||
		  !strcmp(Funcword, "Alas_Tetap")) {
		  datx.widget = gtk_fixed_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 1;  // fixed container
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* ALAS_TEGAK            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ALAS_TEGAK") ||
		  !strcmp(Funcword, "alas_tegak") ||
		  !strcmp(Funcword, "Alas_Tegak")) {
		  datx.widget = gtk_vbox_new(FALSE, 0);
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 2;  // vbox container
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* MENU SEPARATOR        ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "MENU_PEMISAH") ||
		  !strcmp(Funcword, "menu_pemisah")) {
		  // printf("MENU SEPARATOR function\n");
		  datx.widget = gtk_separator_menu_item_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 9;  // Menu Separator
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* STATUSBAR             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PAPAN_STATUS") ||
		  !strcmp(Funcword, "papan_status")) {
		  // printf("papan_status function\n");
		  datx.widget = gtk_statusbar_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 19; // Statusbar
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* DialogPilihHuruf       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "DIALOG_HURUF") ||
		  !strcmp(Funcword, "Dialog_Huruf") ||
		  !strcmp(Funcword, "dialog_huruf")) {
		  datx = funcWinDialogPilihHuruf();

		  /* ======================================================== */
		  /* DialogPilihWarna       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "DIALOG_WARNA") ||
		  !strcmp(Funcword, "Dialog_Warna") ||
		  !strcmp(Funcword, "dialog_warna")) {
		  datx = funcWinDialogPilihWarna();

		  /* ======================================================== */
		  /* DialogPilihArsip       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "DIALOG_ARSIP") ||
		  !strcmp(Funcword, "Dialog_Arsip") ||
		  !strcmp(Funcword, "dialog_arsip")) {
		  datx = funcWinDialogPilihArsip();




		  /* ======================================================== */
		  /* TOMBOL                 ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL") ||
		  !strcmp(Funcword, "tombol")) {
		  datx = funcWinTombol();

		  /* ======================================================== */
		  /* LABEL                 ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LABEL") ||
		  !strcmp(Funcword, "label")) {
		  datx = funcWinLabel();

		  /* ======================================================== */
		  /* LABEL_BERIKON          ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_BERIKON") ||
		  !strcmp(Funcword, "tombol_berikon")) {
		  datx = funcWinTombolBerikon();

		  /* ======================================================== */
		  /* Perinci/Expander       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PERINCI") ||
		  !strcmp(Funcword, "perinci")) {
		  datx = funcWinExpander();

		  /* ======================================================== */
		  /* TOMBOL_PUTAR           ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_PUTAR") ||
		  !strcmp(Funcword, "tombol_putar") ||
		  !strcmp(Funcword, "Tombol_Putar") ||
		  !strcmp(Funcword, "Tombol_putar")
		  ) {
		  datx = funcWinTombolPutar();

		  /* ======================================================== */
		  /* TOMBOL_CEK             ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_CEK") ||
		  !strcmp(Funcword, "tombol_cek") ||
		  !strcmp(Funcword, "Tombol_Cek") ||
		  !strcmp(Funcword, "Tombol_cek")
		  ) {
		  datx = funcWinTombolCek();

		  /* ======================================================== */
		  /* STATUS_CEK             ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "STATUS_CEK") ||
		  !strcmp(Funcword, "status_cek") ||
		  !strcmp(Funcword, "Status_Cek") ||
		  !strcmp(Funcword, "Status_cek")
		  ) {
		  datx = funcWinStatusCek();

		  /* ======================================================== */
		  /* NILAI_TOMBOL_PUTAR     ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "NILAI_TOMBOL_PUTAR") ||
		  !strcmp(Funcword, "nilai_tombol_putar") ||
		  !strcmp(Funcword, "Nilai_Tombol_Putar")
		  ) {
		  datx = funcWinNilaiTombolPutar();

		  /* ======================================================== */
		  /* MASUKAN               ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "MASUKAN") ||
		  !strcmp(Funcword, "masukan")) {
		  datx = funcWinMasukan();

		  /* ======================================================== */
		  /* KERTAS/TEXT AREA       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KERTAS") ||
		  !strcmp(Funcword, "kertas")) {
		  datx = funcWinKertas();

		  /* ======================================================== */
		  /* TEKS_LABEL             ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_LABEL") ||
		  !strcmp(Funcword, "teks_label") ||
		  !strcmp(Funcword, "Teks_Label")
		  ) {
		  datx = funcWinTeksLabel();

		  /* ======================================================== */
		  /* TEKS_MASUKAN           ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_MASUKAN") ||
		  !strcmp(Funcword, "teks_masukan") ||
		  !strcmp(Funcword, "Teks_Masukan")
		  ) {
		  datx = funcWinTeksMasukan();




		  /* ======================================================== */
		  /* TEKS_PILIHAN           ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_PILIHAN") ||
		  !strcmp(Funcword, "teks_pilihan") ||
		  !strcmp(Funcword, "Teks_Pilihan")
		  ) {
		  datx = funcWinTeksPilihan();




		  /* ======================================================== */
		  /* TEKS_KERTAS            ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_KERTAS") ||
		  !strcmp(Funcword, "teks_kertas") ||
		  !strcmp(Funcword, "Teks_Kertas")
		  ) {
		  datx = funcWinTeksKertas();
		  // printf("funcWinTeksKertas() OK \n");

		  /* ======================================================== */
		  /* PILIHAN               ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PILIHAN") ||
		  !strcmp(Funcword, "pilihan")) {
		  datx = funcWinPilihan();



		  /* ======================================================== */
		  /* TOMBOL COBLOS/RADIO    ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_COBLOS") ||
		  !strcmp(Funcword, "tombol_coblos")) {
		  datx = funcWinRadioBtn();



		  /* ======================================================== */
		  /* GRUP TOMBOL RADIO      ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "GRUP_TOMBOL") ||
		  !strcmp(Funcword, "grup_tombol")) {
		  
		  datx = funcWinRadioBtnGroup();



		  /* ======================================================== */
		  /* PAPAN_MENU            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PAPAN_MENU") ||
		  !strcmp(Funcword, "papan_menu")) {
		  // printf("PAPAN_MENU function\n");
		  datx.widget = gtk_menu_bar_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 6;  // Menubar
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* MENU                  ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "MENU") ||
		  !strcmp(Funcword, "menu")) {
		  // printf("MENU function\n");
		  datx.widget = gtk_menu_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 7;  // Menu
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* ISI_MENU               ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ISI_MENU") ||
		  !strcmp(Funcword, "isi_menu")) {
		  datx = funcWinIsiMenu();

		  /* ======================================================== */
		  /* ISI_MENU_CEK           ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ISI_MENU_CEK") ||
		  !strcmp(Funcword, "isi_menu_cek")) {
		  datx = funcWinIsiMenuCek();

		  /* ======================================================== */
		  /* STATUS_MENU_CEK        ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "STATUS_MENU_CEK") ||
		  !strcmp(Funcword, "status_menu_cek") ||
		  !strcmp(Funcword, "Status_Menu_Cek")
		  ) {
		  datx = funcWinNilaiStatusMenuCek();


		  /* ======================================================== */
		  /* PENUNJUK_X            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PENUNJUK_X") ||
		  !strcmp(Funcword, "penunjuk_x")) {
		  datx.val = MOUSE_POS_X;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* PENUNJUK_Y            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PENUNJUK_Y") ||
		  !strcmp(Funcword, "penunjuk_y")) {
		  datx.val = MOUSE_POS_Y;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_PENUNJUK       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_PENUNJUK") ||
		  !strcmp(Funcword, "tombol_penunjuk")) {
		  datx.val = MOUSE_BUTTON;
		  if (MOUSE_BUTTON == 1) {
			  strcpy(datx.str, "kiri");
		  }
		  else if (MOUSE_BUTTON == 2) {
			  strcpy(datx.str, "tengah");
		  }
		  else if (MOUSE_BUTTON == 3) {
			  strcpy(datx.str, "kanan");
		  }
		  datx.datatype = 3; // string
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* KETIKAN_NILAI         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KETIKAN_NILAI") ||
		  !strcmp(Funcword, "ketikan_nilai")) {
		  datx.val = KEYBOARD_VALUE;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_PANAH_KANAN    ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PANAH_KANAN") ||
		  !strcmp(Funcword, "TOMBOL_PANAH_KANAN")) {
		  datx.val = GDK_KEY_Right;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_PANAH_KIRI     ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PANAH_KIRI") ||
		  !strcmp(Funcword, "TOMBOL_PANAH_KIRI")) {
		  datx.val = GDK_KEY_Left;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_PANAH_ATAS     ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PANAH_ATAS") ||
		  !strcmp(Funcword, "TOMBOL_PANAH_ATAS")) {
		  datx.val = GDK_KEY_Up;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_PANAH_BAWAH    ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PANAH_BAWAH") ||
		  !strcmp(Funcword, "TOMBOL_PANAH_BAWAH")) {
		  datx.val = GDK_KEY_Down;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_ENTER          ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_ENTER") ||
		  !strcmp(Funcword, "TOMBOL_RETURN")) {
		  datx.val = GDK_KEY_Return;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_TAB            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_TAB")) {
		  datx.val = GDK_KEY_Tab;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_ESCAPE         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_ESCAPE")) {
		  datx.val = GDK_KEY_Escape;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_HOME           ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_HOME")) {
		  datx.val = GDK_KEY_Home;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_INSERT         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_INSERT")) {
		  datx.val = GDK_KEY_Insert;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_DELETE         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_DELETE")) {
		  datx.val = GDK_KEY_Delete;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_END            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_END")) {
		  datx.val = GDK_KEY_End;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_BACKSPACE      ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_BACKSPACE")) {
		  datx.val = GDK_KEY_BackSpace;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_SHIFT_KIRI     ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_SHIFT_KIRI")) {
		  datx.val = GDK_KEY_Shift_L;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_SHIFT_KANAN    ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_SHIFT_KANAN")) {
		  datx.val = GDK_KEY_Shift_R;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_CTRL_KIRI      ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_CTRL_KIRI")) {
		  datx.val = GDK_KEY_Control_L;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_CTRL_KANAN     ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_CTRL_KANAN")) {
		  datx.val = GDK_KEY_Control_R;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_ALT_KIRI       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_ALT_KIRI")) {
		  datx.val = GDK_KEY_Alt_L;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_ALT_KANAN      ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_ALT_KANAN")) {
		  datx.val = GDK_KEY_Alt_R;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_SPACE          ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_SPACE")) {
		  datx.val = GDK_KEY_space;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F1             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F1")) {
		  datx.val = GDK_KEY_F1;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F2             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F2")) {
		  datx.val = GDK_KEY_F2;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F3             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F3")) {
		  datx.val = GDK_KEY_F3;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F4             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F4")) {
		  datx.val = GDK_KEY_F4;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F5             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F5")) {
		  datx.val = GDK_KEY_F5;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F6             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F6")) {
		  datx.val = GDK_KEY_F6;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F7             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F7")) {
		  datx.val = GDK_KEY_F7;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F8             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F8")) {
		  datx.val = GDK_KEY_F8;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F9             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F9")) {
		  datx.val = GDK_KEY_F9;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F10            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F10")) {
		  datx.val = GDK_KEY_F10;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F11            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F11")) {
		  datx.val = GDK_KEY_F11;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F12            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F12")) {
		  datx.val = GDK_KEY_F12;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* KETIKAN_STATUS        ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KETIKAN_STATUS") ||
		  !strcmp(Funcword, "ketikan_status")) {
		  datx.val = KEYBOARD_STATE;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* KETIKAN_ABJAD         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KETIKAN_ABJAD") ||
		  !strcmp(Funcword, "ketikan_abjad")) {
		  strcpy(datx.str, KEYBOARD_STRING);
		  datx.datatype = 2; // string
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TABEL                  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TABEL") ||
		  !strcmp(Funcword, "tabel")) {
		  datx = funcWinTabel();

		  /* ======================================================== */
		  /* TOTAL_BARIS_TABEL       ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOTAL_BARIS_TABEL") ||
		  !strcmp(Funcword, "total_baris_tabel")) {
		  datx = funcWinTotalBarisTabel();


		  /* ======================================================== */
		  /* DATA_BARIS_TABEL       ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BARIS_TERPILIH") ||
		  !strcmp(Funcword, "baris_terpilih")) {
		  datx = funcWinDataBarisTabel();

		  /* ======================================================== */
		  /* DATA_GAMBAR             ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "DATA_GAMBAR") ||
		  !strcmp(Funcword, "data_gambar")) {
		  datx = funcWinDataGambar();

		  /* ======================================================== */
		  /* MASUKAN_OTOMATIS        ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_RAMPUNG") ||
		  !strcmp(Funcword, "teks_rampung")) {
		  datx.completion = gtk_entry_completion_new();
		  datx.datatype = 48; // auto completion
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* TEKS_TERPILIH           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_TERPILIH") ||
		  !strcmp(Funcword, "teks_terpilih")) {
		  datx = funcWinTeksTerpilih();

		  /* ======================================================== */
		  /* POSISI_TEKS           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "POSISI_TEKS") ||
		  !strcmp(Funcword, "posisi_teks")) {
		  datx = funcWinTeksPosisi();

		  /* ======================================================== */
		  /* CLIPBOARD             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PAPAN_KLIP") ||
		  !strcmp(Funcword, "PAPANKLIP") ||
		  !strcmp(Funcword, "papan_klip") ||
		  !strcmp(Funcword, "papanklip")) {
		  // printf("papan_status function\n");
		  datx.clipboard = NULL;
		  datx.clipboard = gtk_clipboard_get(GDK_NONE);
		  datx.datatype = 51; // default clipboard
		  datx.isGUI = 1;  // GUI



		  /* ======================================================== */
		  /* TANGGAL_TERPILIH      ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TANGGAL_TERPILIH ") ||
		  !strcmp(Funcword, "tanggal_terpilih") ||
		  !strcmp(Funcword, "Tanggal_Terpilih")) {
          // printf("papan_status function\n");
		  strcpy(datx.str, TANGGAL_TERPILIH);
		  datx.datatype = 3; // string


		  /* ======================================================== */
		  /* PUNDI_TEKS              ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PUNDI_TEKS") ||
		  !strcmp(Funcword, "pundi_teks")) {
		  datx.liststore = gtk_list_store_new(1, G_TYPE_STRING);
		  datx.datatype = 47; // list_store STRING
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* PUNDI_ANGKA              ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PUNDI_ANGKA") ||
		  !strcmp(Funcword, "pundi_angka")) {
		  datx.liststore = gtk_list_store_new(1, G_TYPE_INT);
		  datx.datatype = 52; // list_store INT
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* PUNDI_GAMBAR            ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PUNDI_GAMBAR") ||
		  !strcmp(Funcword, "pundi_gambar")) {
		  datx.liststore = gtk_list_store_new(1, GDK_TYPE_PIXBUF);
		  datx.datatype = 53; // list_store PIXBUF
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* PUNDI_CAMPURAN          ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PUNDI_CAMPURAN") ||
		  !strcmp(Funcword, "pundi_campuran")) {
		  datx.liststore = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_INT, GDK_TYPE_PIXBUF);
		  datx.datatype = 54; // list_store STRING, INT, PIXBUF
		  datx.isGUI = 1;



		  /* ======================================================== */
		  /* MODEL_RANTING           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "MODEL_RANTING") ||
		  !strcmp(Funcword, "model_ranting")) {
		  datx = funcWinModelRanting();

		  /* ======================================================== */
		  /* KOLOM_RANTING           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KOLOM_RANTING") ||
		  !strcmp(Funcword, "kolom_ranting")) {
		  datx = funcWinKolomRanting();

		  /* ======================================================== */
		  /* ISI_RANTING_TEKS        ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ISI_SIMPUL") ||
		  !strcmp(Funcword, "isi_simpul")) {
		  datx.treeiter = funcIsiSimpulRanting();
		  datx.datatype = 55; // TreeIter
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* SEL_SIMPUL_TEKS - CellRenderer ====================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "SIMPUL_TEKS") ||
		  !strcmp(Funcword, "simpul_teks")) {
		  datx.renderer = gtk_cell_renderer_text_new();
		  datx.datatype = 57; // teks renderer
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* SEL_SIMPUL_GAMBAR - CellRenderer  ====================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "SIMPUL_GAMBAR") ||
		  !strcmp(Funcword, "simpul_gambar")) {
		  datx.renderer = gtk_cell_renderer_pixbuf_new();
		  datx.datatype = 57; // gambar renderer
		  datx.isGUI = 1;


		  /* ======================================================== */
		  /* RANTING_POHON           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "RANTING_POHON") ||
		  !strcmp(Funcword, "ranting_pohon")) {
		  datx.treestore = gtk_tree_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);
		  datx.datatype = 56; // tree_store STRING
		  datx.isGUI = 1;


		  /* ======================================================== */
		  /* SIMPUL_RANTING - TreeIter   ============================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "SIMPUL_RANTING") ||
		  !strcmp(Funcword, "simpul_ranting")) {
		  // printf("SIMPUL_RANTING function\n");
		  memset(&datx.treeiter, '\0', sizeof(datx.treeiter));
		  datx.datatype = 55; // TreeIter
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* PUNDI_RANTING - TreeStore   ============================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PUNDI_RANTING") ||
		  !strcmp(Funcword, "pundi_ranting")) {
		  // printf("PUNDI_RANTING function\n");
		  memset(&datx.treestore, '\0', sizeof(datx.treestore));
		  datx.datatype = 56; // TreeStore
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* TEKS_RANTING           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_RANTING") ||
		  !strcmp(Funcword, "teks_ranting")) {
		  datx = funcWinTeksRanting();


		  /* ======================================================== */
		  /* KE_UTF8                 ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KE_UTF8") ||
		  !strcmp(Funcword, "ke_utf8")) {
		  datx = funcKE_UTF8();

		  //  --- Cairo ---

		  /* ======================================================== */
		  /* BIDANG_GAMBAR (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BIDANG_GAMBAR") ||
		  !strcmp(Funcword, "bidang_gambar")) {
		  datx = funcCairoBidangGambar();

		  /* ======================================================== */
		  /* LATAR_GAMBAR (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LATAR_GAMBAR") ||
		  !strcmp(Funcword, "latar_gambar")) {
		  datx = funcCairoLatarGambar();

		  /* ======================================================== */
		  /* POLA_LINIER (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "POLA_LINIER") ||
		  !strcmp(Funcword, "pola_linier")) {
		  datx = funcCairoPolaLinier();

		  /* ======================================================== */
		  /* POLA_RADIAL (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "POLA_RADIAL") ||
		  !strcmp(Funcword, "pola_radial")) {
		  datx = funcCairoPolaRadial();

		  /* ======================================================== */
		  /* BIDANG_AMBILPNG (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BIDANG_AMBILPNG") ||
		  !strcmp(Funcword, "bidang_ambilpng")) {
		  datx = funcCairoAmbilPng();



		  /* ======================================================== */
		  /* LATAR_LAYAR (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LATAR_LAYAR") ||
		  !strcmp(Funcword, "latar_layar")) {
		  datx = funcCairoLatarLayar();



		  /* ======================================================== */
		  /* BIDANG_PIXMAP (GDK)    ================================= */
		  /* ======================================================== */
	 }
	  else if (!strcmp(Funcword, "BIDANG_PIXMAP") ||
		  !strcmp(Funcword, "bidang_pixmap")) {
		  datx = funcCairoBaikPixmap();




		  /* ======================================================== */
		  /* AKSI_AREA_X           ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "AREA_X") ||
		  !strcmp(Funcword, "area_x")) {
		  datx.val = EKSPOS_POS_X;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* AKSI_AREA_Y           ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "AREA_Y") ||
		  !strcmp(Funcword, "area_y")) {
		  datx.val = EKSPOS_POS_Y;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* AKSI_AREA_LEBAR       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "AREA_LEBAR") ||
		  !strcmp(Funcword, "area_lebar")) {
		  datx.val = EKSPOS_WIDTH;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* AKSI_AREA_TINGGI      ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "AREA_TINGGI") ||
		  !strcmp(Funcword, "area_tinggi")) {
		  datx.val = EKSPOS_HEIGHT;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;



		  /* ======================================================== */
		  /* ALOKASI_X (Gtk)       ================================= */
		  /* ======================================================== */
//	  }
//	  else if (!strcmp(Funcword, "ALOKASI_X") ||
//		  !strcmp(Funcword, "alokasi_x")) {
//		  datx = funcWinAlokasiX();

		  /* ======================================================== */
		  /* ALOKASI_Y (Gtk)       ================================= */
		  /* ======================================================== */
//	  }
//	  else if (!strcmp(Funcword, "ALOKASI_Y") ||
//		  !strcmp(Funcword, "alokasi_y")) {
//		  datx = funcWinAlokasiY();

		  /* ======================================================== */
		  /* ALOKASI_LEBAR (Gtk)    ================================= */
		  /* ======================================================== */
//	  }
//	  else if (!strcmp(Funcword, "ALOKASI_LEBAR") ||
//		  !strcmp(Funcword, "alokasi_lebar")) {
//		  datx = funcWinAlokasiLebar();

		  /* ======================================================== */
		  /* ALOKASI_TINGGI (Gtk)   ================================= */
		  /* ======================================================== */
//	  }
//	  else if (!strcmp(Funcword, "ALOKASI_TINGGI") ||
//		  !strcmp(Funcword, "alokasi_tinggi")) {
//		  datx = funcWinAlokasiTinggi();




		  /* ======================================================== */
		  /* RUANG_TEKS (Cairo)   ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "RUANG_TEKS") ||
		  !strcmp(Funcword, "ruang_teks")) {
		  datx = funcCairoRuangTeks();

		  /* ======================================================== */
		  /* LEBAR_RUANG_TEKS (Cairo)   ============================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LEBAR_RUANG_TEKS") ||
		  !strcmp(Funcword, "lebar_ruang_teks")) {
		  datx = funcCairoLebarRuangTeks();

		  /* ======================================================== */
		  /* TINGGI_RUANG_TEKS (Cairo)   ============================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TINGGI_RUANG_TEKS") ||
		  !strcmp(Funcword, "tinggi_ruang_teks")) {
		  datx = funcCairoTinggiRuangTeks();

		  /* ======================================================== */
		  /* NOTEBOOK              ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BUKU") ||
		  !strcmp(Funcword, "buku")) {
		  // printf("BUKU (Notebook) function\n");
		  datx.widget = gtk_notebook_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 23; // Notebook
		  datx.isGUI = 1;  // GUI


		  /* ======================================================== */
		  /* PRINT OPERATION       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "OPERASI_CETAK") ||
		  !strcmp(Funcword, "operasi_cetak")) {
		  datx.gtk_print_ope = gtk_print_operation_new();
		  datx.datatype = 90; // GTK print ope
		  datx.isGUI = 1;  // GUI

		  //printf("Operasi Cetak ..\n");

		  if (BAIK_PRINT_settings != NULL) {
			  gtk_print_operation_set_print_settings(datx.gtk_print_ope, BAIK_PRINT_settings);
		  }
		  else {
			  //printf("BAIK_PRINT_settings NULL.\n");
		  }
		  

		  /* ======================================================== */
		  /* SELURUH_ARSIP         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "SELURUH_ARSIP") ||
		  !strcmp(Funcword, "seluruh_arsip")) {
		  datx = funcWinSeluruhArsip();

		  /* ======================================================== */
		  /* PISAH_PER_BARIS       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PISAH_PER_BARIS") ||
		  !strcmp(Funcword, "pisah_per_baris")) {
		  datx = funcWinPisahBarisArsip();

		  /* ======================================================== */
		  /* TEKS_PER_BARIS       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_PER_BARIS") ||
		  !strcmp(Funcword, "teks_per_baris")) {
		  datx = funcWinTeksPerBaris();

		  /* ======================================================== */
		  /* JUMLAH_BARIS_ARSIP    ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "JUMLAH_BARIS_ARSIP") ||
		  !strcmp(Funcword, "jumlah_baris_arsip")) {
		  datx = funcWinJumlahBarisArsip();




		  /* ======================================================== */
		  /* TINGGI_CETAKAN       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TINGGI_CETAKAN") ||
		  !strcmp(Funcword, "tinggi_cetakan")) {
		  datx = funcWinTinggiCetakan();

		  /* ======================================================== */
		  /* LEBAR_CETAKAN         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LEBAR_CETAKAN") ||
		  !strcmp(Funcword, "lebar_cetakan")) {
		  if (BAIK_Print_Context != NULL) {
			  datx.floatdata = gtk_print_context_get_width(BAIK_Print_Context);
			  datx.datatype = 1; // double
		  }

		  
		  /* ======================================================== */
		  /* BARIS_PER_HALAMAN     ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BARIS_PER_HALAMAN") ||
		  !strcmp(Funcword, "baris_per_halaman")) {
		  datx = funcWinBarisPerHalaman();

		  /* ======================================================== */
		  /* KONTEKS_CETAKAN       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KONTEKS_CETAKAN") ||
		  !strcmp(Funcword, "konteks_cetakan")) {
		  if (BAIK_Print_Context != NULL) {
			  datx.cr_img = NULL;
			  datx.cr_img = gtk_print_context_get_cairo_context(BAIK_Print_Context);
			  datx.datatype = 80;
		  }

		  /* ======================================================== */
		  /* TATANAN_CETAKAN       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TATANAN_CETAKAN") ||
		  !strcmp(Funcword, "tatanan_cetakan")) {
		  if (BAIK_Print_Context != NULL) {
			  datx.pango_layout = gtk_print_context_create_pango_layout(BAIK_Print_Context);
			  datx.datatype = 91; // pango_layout
		  }

		  /* ======================================================== */
		  /* TINGGI_TEKS_CETAK       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TINGGI_TEKS_CETAK") ||
		  !strcmp(Funcword, "tinggi_teks_cetak")) {
		  datx = funcWinTinggiTeksCetak();

		  /* ======================================================== */
		  /* LEBAR_TEKS_CETAK       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LEBAR_TEKS_CETAK") ||
		  !strcmp(Funcword, "lebar_teks_cetak")) {
		  datx = funcWinLebarTeksCetak();

		  /* ======================================================== */
		  /* SET_ATRIBUT_CETAK       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "SET_ATRIBUT_CETAK") ||
		  !strcmp(Funcword, "set_atribut_cetak")) {
		  datx = funcWinSetAtributCetak();

		  /* ======================================================== */
		  /* HALAMAN_AKTUAL        ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "HALAMAN_AKTUAL") ||
		  !strcmp(Funcword, "halaman_aktual")) {

		  // printf("func HALAMAN AKTUAL %d \n", (BAIK_page_nr + 1));

		  datx.val = BAIK_page_nr + 1;
		  datx.datatype = 0;

		  /* ======================================================== */
#endif
		  /* ======================================================== */













	  /* ======================================================== */
      #ifdef USE_GTK2
	  /* ======================================================== */

	  /* ======================================================== */
	  /* LAYAR                 ================================== */
	  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LAYAR") ||
		  !strcmp(Funcword, "layar")) {
		  // printf("LAYAR function\n");
		  datx.widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 0;  // window
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* KANVAS                ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KANVAS") ||
		  !strcmp(Funcword, "kanvas")) {
		  // printf("KANVAS function\n");
		  datx.widget = gtk_drawing_area_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 20; // window drawing area
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* CITRA                 ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "CITRA") ||
		  !strcmp(Funcword, "citra") ||
		  !strcmp(Funcword, "Citra")) {
		  datx = funcWinCitra();

		  /* ======================================================== */
		  /* LAYAR_GULUNG          ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LAYAR_GULUNG") ||
		  !strcmp(Funcword, "layar_gulung")) {
		  // printf("LAYAR_GULUNG function\n");
		  datx.widget = gtk_scrolled_window_new(NULL, NULL);
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 21; // scrolled window
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* ALAS_TETAP            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ALAS_TETAP") ||
		  !strcmp(Funcword, "alas_tetap") ||
		  !strcmp(Funcword, "Alas_Tetap")) {
		  datx.widget = gtk_fixed_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 1;  // fixed container
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* ALAS_TEGAK            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ALAS_TEGAK") ||
		  !strcmp(Funcword, "alas_tegak") ||
		  !strcmp(Funcword, "Alas_Tegak")) {
		  datx.widget = gtk_vbox_new(FALSE, 0);
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 2;  // vbox container
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* MENU SEPARATOR        ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "MENU_PEMISAH") ||
		  !strcmp(Funcword, "menu_pemisah")) {
		  // printf("MENU SEPARATOR function\n");
		  datx.widget = gtk_separator_menu_item_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 9;  // Menu Separator
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* STATUSBAR             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PAPAN_STATUS") ||
		  !strcmp(Funcword, "papan_status")) {
		  // printf("papan_status function\n");
		  datx.widget = gtk_statusbar_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 19; // Statusbar
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* DialogPilihHuruf       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "DIALOG_HURUF") ||
		  !strcmp(Funcword, "Dialog_Huruf") ||
		  !strcmp(Funcword, "dialog_huruf")) {
		  datx = funcWinDialogPilihHuruf();

		  /* ======================================================== */
		  /* DialogPilihWarna       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "DIALOG_WARNA") ||
		  !strcmp(Funcword, "Dialog_Warna") ||
		  !strcmp(Funcword, "dialog_warna")) {
		  datx = funcWinDialogPilihWarna();

		  /* ======================================================== */
		  /* DialogPilihArsip       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "DIALOG_ARSIP") ||
		  !strcmp(Funcword, "Dialog_Arsip") ||
		  !strcmp(Funcword, "dialog_arsip")) {
		  datx = funcWinDialogPilihArsip();


		  /* ======================================================== */
		  /* TOMBOL                 ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL") ||
		  !strcmp(Funcword, "tombol")) {
		  datx = funcWinTombol();

		  /* ======================================================== */
		  /* LABEL                 ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LABEL") ||
		  !strcmp(Funcword, "label")) {
		  datx = funcWinLabel();

		  /* ======================================================== */
		  /* LABEL_BERIKON          ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_BERIKON") ||
		  !strcmp(Funcword, "tombol_berikon")) {
		  datx = funcWinTombolBerikon();

		  /* ======================================================== */
		  /* Perinci/Expander       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PERINCI") ||
		  !strcmp(Funcword, "perinci")) {
		  datx = funcWinExpander();

		  /* ======================================================== */
		  /* TOMBOL_PUTAR           ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_PUTAR") ||
		  !strcmp(Funcword, "tombol_putar") ||
		  !strcmp(Funcword, "Tombol_Putar") ||
		  !strcmp(Funcword, "Tombol_putar")
		  ) {
		  datx = funcWinTombolPutar();

		  /* ======================================================== */
		  /* TOMBOL_CEK             ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_CEK") ||
		  !strcmp(Funcword, "tombol_cek") ||
		  !strcmp(Funcword, "Tombol_Cek") ||
		  !strcmp(Funcword, "Tombol_cek")
		  ) {
		  datx = funcWinTombolCek();

		  /* ======================================================== */
		  /* STATUS_CEK             ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "STATUS_CEK") ||
		  !strcmp(Funcword, "status_cek") ||
		  !strcmp(Funcword, "Status_Cek") ||
		  !strcmp(Funcword, "Status_cek")
		  ) {
		  datx = funcWinStatusCek();

		  /* ======================================================== */
		  /* NILAI_TOMBOL_PUTAR     ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "NILAI_TOMBOL_PUTAR") ||
		  !strcmp(Funcword, "nilai_tombol_putar") ||
		  !strcmp(Funcword, "Nilai_Tombol_Putar")
		  ) {
		  datx = funcWinNilaiTombolPutar();

		  /* ======================================================== */
		  /* MASUKAN               ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "MASUKAN") ||
		  !strcmp(Funcword, "masukan")) {
		  datx = funcWinMasukan();

		  /* ======================================================== */
		  /* KERTAS/TEXT AREA       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KERTAS") ||
		  !strcmp(Funcword, "kertas")) {
		  datx = funcWinKertas();

		  /* ======================================================== */
		  /* TEKS_LABEL             ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_LABEL") ||
		  !strcmp(Funcword, "teks_label") ||
		  !strcmp(Funcword, "Teks_Label")
		  ) {
		  datx = funcWinTeksLabel();

		  /* ======================================================== */
		  /* TEKS_MASUKAN           ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_MASUKAN") ||
		  !strcmp(Funcword, "teks_masukan") ||
		  !strcmp(Funcword, "Teks_Masukan")
		  ) {
		  datx = funcWinTeksMasukan();

		  /* ======================================================== */
		  /* TEKS_PILIHAN           ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_PILIHAN") ||
		  !strcmp(Funcword, "teks_pilihan") ||
		  !strcmp(Funcword, "Teks_Pilihan")
		  ) {
		  datx = funcWinTeksPilihan();

		  /* ======================================================== */
		  /* TEKS_KERTAS            ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_KERTAS") ||
		  !strcmp(Funcword, "teks_kertas") ||
		  !strcmp(Funcword, "Teks_Kertas")
		  ) {
		  datx = funcWinTeksKertas();
		  // printf("funcWinTeksKertas() OK \n");

		  /* ======================================================== */
		  /* PILIHAN               ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PILIHAN") ||
		  !strcmp(Funcword, "pilihan")) {
		  datx = funcWinPilihan();

		  /* ======================================================== */
		  /* TOMBOL COBLOS/RADIO    ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_COBLOS") ||
		  !strcmp(Funcword, "tombol_coblos")) {
		  datx = funcWinRadioBtn();

		  /* ======================================================== */
		  /* GRUP TOMBOL RADIO      ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "GRUP_TOMBOL") ||
		  !strcmp(Funcword, "grup_tombol")) {

		  datx = funcWinRadioBtnGroup();

		  /* ======================================================== */
		  /* PAPAN_MENU            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PAPAN_MENU") ||
		  !strcmp(Funcword, "papan_menu")) {
		  // printf("PAPAN_MENU function\n");
		  datx.widget = gtk_menu_bar_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 6;  // Menubar
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* MENU                  ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "MENU") ||
		  !strcmp(Funcword, "menu")) {
		  // printf("MENU function\n");
		  datx.widget = gtk_menu_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 7;  // Menu
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* ISI_MENU               ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ISI_MENU") ||
		  !strcmp(Funcword, "isi_menu")) {
		  datx = funcWinIsiMenu();

		  /* ======================================================== */
		  /* ISI_MENU_CEK           ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ISI_MENU_CEK") ||
		  !strcmp(Funcword, "isi_menu_cek")) {
		  datx = funcWinIsiMenuCek();

		  /* ======================================================== */
		  /* STATUS_MENU_CEK        ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "STATUS_MENU_CEK") ||
		  !strcmp(Funcword, "status_menu_cek") ||
		  !strcmp(Funcword, "Status_Menu_Cek")
		  ) {
		  datx = funcWinNilaiStatusMenuCek();


		  /* ======================================================== */
		  /* PENUNJUK_X            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PENUNJUK_X") ||
		  !strcmp(Funcword, "penunjuk_x")) {
		  datx.val = MOUSE_POS_X;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* PENUNJUK_Y            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PENUNJUK_Y") ||
		  !strcmp(Funcword, "penunjuk_y")) {
		  datx.val = MOUSE_POS_Y;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_PENUNJUK       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_PENUNJUK") ||
		  !strcmp(Funcword, "tombol_penunjuk")) {
		  datx.val = MOUSE_BUTTON;
		  if (MOUSE_BUTTON == 1) {
			  strcpy(datx.str, "kiri");
		  }
		  else if (MOUSE_BUTTON == 2) {
			  strcpy(datx.str, "tengah");
		  }
		  else if (MOUSE_BUTTON == 3) {
			  strcpy(datx.str, "kanan");
		  }
		  datx.datatype = 3; // string
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* KETIKAN_NILAI         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KETIKAN_NILAI") ||
		  !strcmp(Funcword, "ketikan_nilai")) {
		  datx.val = KEYBOARD_VALUE;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_PANAH_KANAN    ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PANAH_KANAN") ||
		  !strcmp(Funcword, "TOMBOL_PANAH_KANAN")) {
		  datx.val = GDK_Right;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_PANAH_KIRI     ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PANAH_KIRI") ||
		  !strcmp(Funcword, "TOMBOL_PANAH_KIRI")) {
		  datx.val = GDK_Left;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_PANAH_ATAS     ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PANAH_ATAS") ||
		  !strcmp(Funcword, "TOMBOL_PANAH_ATAS")) {
		  datx.val = GDK_Up;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_PANAH_BAWAH    ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PANAH_BAWAH") ||
		  !strcmp(Funcword, "TOMBOL_PANAH_BAWAH")) {
		  datx.val = GDK_Down;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_ENTER          ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_ENTER") ||
		  !strcmp(Funcword, "TOMBOL_RETURN")) {
		  datx.val = GDK_Return;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_TAB            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_TAB")) {
		  datx.val = GDK_Tab;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_ESCAPE         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_ESCAPE")) {
		  datx.val = GDK_Escape;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_HOME           ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_HOME")) {
		  datx.val = GDK_Home;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_INSERT         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_INSERT")) {
		  datx.val = GDK_Insert;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_DELETE         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_DELETE")) {
		  datx.val = GDK_Delete;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_END            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_END")) {
		  datx.val = GDK_End;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_BACKSPACE      ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_BACKSPACE")) {
		  datx.val = GDK_BackSpace;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_SHIFT_KIRI     ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_SHIFT_KIRI")) {
		  datx.val = GDK_Shift_L;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_SHIFT_KANAN    ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_SHIFT_KANAN")) {
		  datx.val = GDK_Shift_R;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_CTRL_KIRI      ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_CTRL_KIRI")) {
		  datx.val = GDK_Control_L;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_CTRL_KANAN     ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_CTRL_KANAN")) {
		  datx.val = GDK_Control_R;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_ALT_KIRI       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_ALT_KIRI")) {
		  datx.val = GDK_Alt_L;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_ALT_KANAN      ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_ALT_KANAN")) {
		  datx.val = GDK_Alt_R;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_SPACE          ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_SPACE")) {
		  datx.val = GDK_space;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F1             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F1")) {
		  datx.val = GDK_F1;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F2             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F2")) {
		  datx.val = GDK_F2;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F3             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F3")) {
		  datx.val = GDK_F3;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F4             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F4")) {
		  datx.val = GDK_F4;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F5             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F5")) {
		  datx.val = GDK_F5;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F6             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F6")) {
		  datx.val = GDK_F6;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F7             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F7")) {
		  datx.val = GDK_F7;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F8             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F8")) {
		  datx.val = GDK_F8;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F9             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F9")) {
		  datx.val = GDK_F9;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F10            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F10")) {
		  datx.val = GDK_F10;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F11            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F11")) {
		  datx.val = GDK_F11;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TOMBOL_F12            ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOMBOL_F12")) {
		  datx.val = GDK_F12;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* KETIKAN_STATUS        ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KETIKAN_STATUS") ||
		  !strcmp(Funcword, "ketikan_status")) {
		  datx.val = KEYBOARD_STATE;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* KETIKAN_ABJAD         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KETIKAN_ABJAD") ||
		  !strcmp(Funcword, "ketikan_abjad")) {
		  strcpy(datx.str, KEYBOARD_STRING);
		  datx.datatype = 2; // string
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* TABEL                  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TABEL") ||
		  !strcmp(Funcword, "tabel")) {
		  datx = funcWinTabel();

		  /* ======================================================== */
		  /* TOTAL_BARIS_TABEL       ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TOTAL_BARIS_TABEL") ||
		  !strcmp(Funcword, "total_baris_tabel")) {
		  datx = funcWinTotalBarisTabel();


		  /* ======================================================== */
		  /* DATA_BARIS_TABEL       ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BARIS_TERPILIH") ||
		  !strcmp(Funcword, "baris_terpilih")) {
		  datx = funcWinDataBarisTabel();

		  /* ======================================================== */
		  /* DATA_GAMBAR             ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "DATA_GAMBAR") ||
		  !strcmp(Funcword, "data_gambar")) {
		  datx = funcWinDataGambar();

		  /* ======================================================== */
		  /* MASUKAN_OTOMATIS        ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_RAMPUNG") ||
		  !strcmp(Funcword, "teks_rampung")) {
		  datx.completion = gtk_entry_completion_new();
		  datx.datatype = 48; // auto completion
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* TEKS_TERPILIH           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_TERPILIH") ||
		  !strcmp(Funcword, "teks_terpilih")) {
		  datx = funcWinTeksTerpilih();

		  /* ======================================================== */
		  /* POSISI_TEKS           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "POSISI_TEKS") ||
		  !strcmp(Funcword, "posisi_teks")) {
		  datx = funcWinTeksPosisi();

		  /* ======================================================== */
		  /* CLIPBOARD             ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PAPAN_KLIP") ||
		  !strcmp(Funcword, "PAPANKLIP") ||
		  !strcmp(Funcword, "papan_klip") ||
		  !strcmp(Funcword, "papanklip")) {
		  // printf("papan_status function\n");
		  datx.clipboard = NULL;
		  datx.clipboard = gtk_clipboard_get(GDK_NONE);
		  datx.datatype = 51; // default clipboard
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* TANGGAL_TERPILIH      ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TANGGAL_TERPILIH ") ||
		  !strcmp(Funcword, "tanggal_terpilih") ||
		  !strcmp(Funcword, "Tanggal_Terpilih")) {
		  // printf("papan_status function\n");
		  strcpy(datx.str, TANGGAL_TERPILIH);
		  datx.datatype = 3; // string

		  /* ======================================================== */
		  /* PUNDI_TEKS              ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PUNDI_TEKS") ||
		  !strcmp(Funcword, "pundi_teks")) {
		  datx.liststore = gtk_list_store_new(1, G_TYPE_STRING);
		  datx.datatype = 47; // list_store STRING
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* PUNDI_ANGKA              ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PUNDI_ANGKA") ||
		  !strcmp(Funcword, "pundi_angka")) {
		  datx.liststore = gtk_list_store_new(1, G_TYPE_INT);
		  datx.datatype = 52; // list_store INT
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* PUNDI_GAMBAR            ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PUNDI_GAMBAR") ||
		  !strcmp(Funcword, "pundi_gambar")) {
		  datx.liststore = gtk_list_store_new(1, GDK_TYPE_PIXBUF);
		  datx.datatype = 53; // list_store PIXBUF
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* PUNDI_CAMPURAN          ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PUNDI_CAMPURAN") ||
		  !strcmp(Funcword, "pundi_campuran")) {
		  datx.liststore = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_INT, GDK_TYPE_PIXBUF);
		  datx.datatype = 54; // list_store STRING, INT, PIXBUF
		  datx.isGUI = 1;



		  /* ======================================================== */
		  /* MODEL_RANTING           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "MODEL_RANTING") ||
		  !strcmp(Funcword, "model_ranting")) {
		  datx = funcWinModelRanting();

		  /* ======================================================== */
		  /* KOLOM_RANTING           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KOLOM_RANTING") ||
		  !strcmp(Funcword, "kolom_ranting")) {
		  datx = funcWinKolomRanting();

		  /* ======================================================== */
		  /* ISI_RANTING_TEKS        ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ISI_SIMPUL") ||
		  !strcmp(Funcword, "isi_simpul")) {
		  datx.treeiter = funcIsiSimpulRanting();
		  datx.datatype = 55; // TreeIter
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* SEL_SIMPUL_TEKS - CellRenderer ====================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "SIMPUL_TEKS") ||
		  !strcmp(Funcword, "simpul_teks")) {
		  datx.renderer = gtk_cell_renderer_text_new();
		  datx.datatype = 57; // teks renderer
		  datx.isGUI = 1;

		  /* ======================================================== */
		  /* SEL_SIMPUL_GAMBAR - CellRenderer  ====================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "SIMPUL_GAMBAR") ||
		  !strcmp(Funcword, "simpul_gambar")) {
		  datx.renderer = gtk_cell_renderer_pixbuf_new();
		  datx.datatype = 57; // gambar renderer
		  datx.isGUI = 1;


		  /* ======================================================== */
		  /* RANTING_POHON           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "RANTING_POHON") ||
		  !strcmp(Funcword, "ranting_pohon")) {
		  datx.treestore = gtk_tree_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);
		  datx.datatype = 56; // tree_store STRING
		  datx.isGUI = 1;


		  /* ======================================================== */
		  /* SIMPUL_RANTING - TreeIter   ============================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "SIMPUL_RANTING") ||
		  !strcmp(Funcword, "simpul_ranting")) {
		  // printf("SIMPUL_RANTING function\n");
		  memset(&datx.treeiter, '\0', sizeof(datx.treeiter));
		  datx.datatype = 55; // TreeIter
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* PUNDI_RANTING - TreeStore   ============================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PUNDI_RANTING") ||
		  !strcmp(Funcword, "pundi_ranting")) {
		  // printf("PUNDI_RANTING function\n");
		  memset(&datx.treestore, '\0', sizeof(datx.treestore));
		  datx.datatype = 56; // TreeStore
		  datx.isGUI = 1;  // GUI

		  /* ======================================================== */
		  /* TEKS_RANTING           ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_RANTING") ||
		  !strcmp(Funcword, "teks_ranting")) {
		  datx = funcWinTeksRanting();


		  /* ======================================================== */
		  /* KE_UTF8                 ================================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KE_UTF8") ||
		  !strcmp(Funcword, "ke_utf8")) {
		  datx = funcKE_UTF8();

		  //  --- Cairo ---

		  /* ======================================================== */
		  /* BIDANG_GAMBAR (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BIDANG_GAMBAR") ||
		  !strcmp(Funcword, "bidang_gambar")) {
		  datx = funcCairoBidangGambar();

		  /* ======================================================== */
		  /* LATAR_GAMBAR (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LATAR_GAMBAR") ||
		  !strcmp(Funcword, "latar_gambar")) {
		  datx = funcCairoLatarGambar();

		  /* ======================================================== */
		  /* POLA_LINIER (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "POLA_LINIER") ||
		  !strcmp(Funcword, "pola_linier")) {
		  datx = funcCairoPolaLinier();

		  /* ======================================================== */
		  /* POLA_RADIAL (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "POLA_RADIAL") ||
		  !strcmp(Funcword, "pola_radial")) {
		  datx = funcCairoPolaRadial();

		  /* ======================================================== */
		  /* BIDANG_AMBILPNG (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BIDANG_AMBILPNG") ||
		  !strcmp(Funcword, "bidang_ambilpng")) {
		  datx = funcCairoAmbilPng();

		  /* ======================================================== */
		  /* LATAR_LAYAR (Cairo)  ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LATAR_LAYAR") ||
		  !strcmp(Funcword, "latar_layar")) {
		  datx = funcCairoLatarLayar();

		  /* ======================================================== */
		  /* BIDANG_PIXMAP (GDK)    ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BIDANG_PIXMAP") ||
		  !strcmp(Funcword, "bidang_pixmap")) {
		  datx = funcCairoBaikPixmap();

		  /* ======================================================== */
		  /* AKSI_AREA_X           ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "AREA_X") ||
		  !strcmp(Funcword, "area_x")) {
		  datx.val = EKSPOS_POS_X;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* AKSI_AREA_Y           ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "AREA_Y") ||
		  !strcmp(Funcword, "area_y")) {
		  datx.val = EKSPOS_POS_Y;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* AKSI_AREA_LEBAR       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "AREA_LEBAR") ||
		  !strcmp(Funcword, "area_lebar")) {
		  datx.val = EKSPOS_WIDTH;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* AKSI_AREA_TINGGI      ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "AREA_TINGGI") ||
		  !strcmp(Funcword, "area_tinggi")) {
		  datx.val = EKSPOS_HEIGHT;
		  datx.datatype = 0; // integer
		  datx.isGUI = 0;

		  /* ======================================================== */
		  /* ALOKASI_X (Gtk)       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ALOKASI_X") ||
		  !strcmp(Funcword, "alokasi_x")) {
		  datx = funcWinAlokasiX();

		  /* ======================================================== */
		  /* ALOKASI_Y (Gtk)       ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ALOKASI_Y") ||
		  !strcmp(Funcword, "alokasi_y")) {
		  datx = funcWinAlokasiY();

		  /* ======================================================== */
		  /* ALOKASI_LEBAR (Gtk)    ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ALOKASI_LEBAR") ||
		  !strcmp(Funcword, "alokasi_lebar")) {
		  datx = funcWinAlokasiLebar();

		  /* ======================================================== */
		  /* ALOKASI_TINGGI (Gtk)   ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "ALOKASI_TINGGI") ||
		  !strcmp(Funcword, "alokasi_tinggi")) {
		  datx = funcWinAlokasiTinggi();

		  /* ======================================================== */
		  /* RUANG_TEKS (Cairo)   ================================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "RUANG_TEKS") ||
		  !strcmp(Funcword, "ruang_teks")) {
		  datx = funcCairoRuangTeks();

		  /* ======================================================== */
		  /* LEBAR_RUANG_TEKS (Cairo)   ============================= */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LEBAR_RUANG_TEKS") ||
		  !strcmp(Funcword, "lebar_ruang_teks")) {
		  datx = funcCairoLebarRuangTeks();

		  /* ======================================================== */
		  /* TINGGI_RUANG_TEKS (Cairo)   ============================ */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TINGGI_RUANG_TEKS") ||
		  !strcmp(Funcword, "tinggi_ruang_teks")) {
		  datx = funcCairoTinggiRuangTeks();

		  /* ======================================================== */
		  /* NOTEBOOK              ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BUKU") ||
		  !strcmp(Funcword, "buku")) {
		  // printf("BUKU (Notebook) function\n");
		  datx.widget = gtk_notebook_new();
		  datx.datatype = 40; // GTK widget
		  datx.GUItype = 23; // Notebook
		  datx.isGUI = 1;  // GUI


		  /* ======================================================== */
		  /* PRINT OPERATION       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "OPERASI_CETAK") ||
		  !strcmp(Funcword, "operasi_cetak")) {
		  datx.gtk_print_ope = gtk_print_operation_new();
		  datx.datatype = 90; // GTK print ope
		  datx.isGUI = 1;  // GUI

		  if (BAIK_PRINT_settings != NULL)
			  gtk_print_operation_set_print_settings(datx.gtk_print_ope, BAIK_PRINT_settings);

		  /* ======================================================== */
		  /* SELURUH_ARSIP         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "SELURUH_ARSIP") ||
		  !strcmp(Funcword, "seluruh_arsip")) {
		  datx = funcWinSeluruhArsip();

		  /* ======================================================== */
		  /* PISAH_PER_BARIS       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "PISAH_PER_BARIS") ||
		  !strcmp(Funcword, "pisah_per_baris")) {
		  datx = funcWinPisahBarisArsip();

		  /* ======================================================== */
		  /* TEKS_PER_BARIS       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TEKS_PER_BARIS") ||
		  !strcmp(Funcword, "teks_per_baris")) {
		  datx = funcWinTeksPerBaris();

		  /* ======================================================== */
		  /* JUMLAH_BARIS_ARSIP    ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "JUMLAH_BARIS_ARSIP") ||
		  !strcmp(Funcword, "jumlah_baris_arsip")) {
		  datx = funcWinJumlahBarisArsip();

		  /* ======================================================== */
		  /* TINGGI_CETAKAN       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TINGGI_CETAKAN") ||
		  !strcmp(Funcword, "tinggi_cetakan")) {
		  datx = funcWinTinggiCetakan();

		  /* ======================================================== */
		  /* LEBAR_CETAKAN         ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LEBAR_CETAKAN") ||
		  !strcmp(Funcword, "lebar_cetakan")) {
		  if (BAIK_Print_Context != NULL) {
			  datx.floatdata = gtk_print_context_get_width(BAIK_Print_Context);
			  datx.datatype = 1; // double
		  }

		  /* ======================================================== */
		  /* BARIS_PER_HALAMAN     ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "BARIS_PER_HALAMAN") ||
		  !strcmp(Funcword, "baris_per_halaman")) {
		  datx = funcWinBarisPerHalaman();

		  /* ======================================================== */
		  /* KONTEKS_CETAKAN       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "KONTEKS_CETAKAN") ||
		  !strcmp(Funcword, "konteks_cetakan")) {
		  if (BAIK_Print_Context != NULL) {
			  datx.cr_img = NULL;
			  datx.cr_img = gtk_print_context_get_cairo_context(BAIK_Print_Context);
			  datx.datatype = 80;
		  }

		  /* ======================================================== */
		  /* TATANAN_CETAKAN       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TATANAN_CETAKAN") ||
		  !strcmp(Funcword, "tatanan_cetakan")) {
		  if (BAIK_Print_Context != NULL) {
			  datx.pango_layout = gtk_print_context_create_pango_layout(BAIK_Print_Context);
			  datx.datatype = 91; // pango_layout
		  }

		  /* ======================================================== */
		  /* TINGGI_TEKS_CETAK       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "TINGGI_TEKS_CETAK") ||
		  !strcmp(Funcword, "tinggi_teks_cetak")) {
		  datx = funcWinTinggiTeksCetak();

		  /* ======================================================== */
		  /* LEBAR_TEKS_CETAK       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "LEBAR_TEKS_CETAK") ||
		  !strcmp(Funcword, "lebar_teks_cetak")) {
		  datx = funcWinLebarTeksCetak();

		  /* ======================================================== */
		  /* SET_ATRIBUT_CETAK       ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "SET_ATRIBUT_CETAK") ||
		  !strcmp(Funcword, "set_atribut_cetak")) {
		  datx = funcWinSetAtributCetak();

		  /* ======================================================== */
		  /* HALAMAN_AKTUAL        ================================== */
		  /* ======================================================== */
	  }
	  else if (!strcmp(Funcword, "HALAMAN_AKTUAL") ||
		  !strcmp(Funcword, "halaman_aktual")) {

		  // printf("func HALAMAN AKTUAL %d \n", (BAIK_page_nr + 1));

		  datx.val = BAIK_page_nr + 1;
		  datx.datatype = 0;

	  /* ======================================================== */
      #endif
	  /* ======================================================== */

      /* ======================================================== */
      /* SQL Translasi      ==================================== */
      /* ======================================================== */
      } else if(!strcmp(Funcword, "TRANS_SQL") ||
                !strcmp(Funcword, "trans_sql") ||
                !strcmp(Funcword, "Trans_Sql") ||
                !strcmp(Funcword, "Trans_sql") ) { 
          /* printf("SQL Translasi function\n"); */
		  datx = funcSQLTranslasi();

      /* ======================================================== */


      #ifdef USE_PDF

      /* ======================================================== */
      /* PDF                 ================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "PDF") ||
         !strcmp(Funcword, "pdf") ) { 
         //printf("use PDF function\n");
		 datx.pdf = HPDF_New (NULL, NULL);
         if (!datx.pdf)
            Error ("salah: tidak bisa buat PdfDoc\n");
         if (datx.pdf == NULL)
            Error ("salah: PdfDoc NULL\n");
	     datx.datatype = 70; // PDF
 
      } else if( !strcmp(Funcword, "PDF_HALAMAN") ||
         !strcmp(Funcword, "pdf_halaman") ) { 
		  datx = funcPDFHalaman();
	     datx.datatype = 71; // PDF Page

      } else if( !strcmp(Funcword, "PDF_LEBAR") ||
         !strcmp(Funcword, "pdf_lebar") ) { 
		  datx = funcPDFLebar();

      } else if( !strcmp(Funcword, "PDF_TINGGI") ||
         !strcmp(Funcword, "pdf_tinggi") ) { 
		  datx = funcPDFTinggi();

      } else if( !strcmp(Funcword, "PDF_AMBILPNG") ||
         !strcmp(Funcword, "pdf_ambilpng") ) { 
		  datx = funcPDFAmbilPng();

      } else if( !strcmp(Funcword, "PDF_AMBILJPG") ||
         !strcmp(Funcword, "pdf_ambiljpg") ) { 
		  datx = funcPDFAmbilJpg();

	  /* ======================================================== */
      #endif
      /* ======================================================== */


      #ifdef USE_SSL

      /* ======================================================== */
      /* SSL                 ================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "ENKRIPSI_DES") ||
         !strcmp(Funcword, "enkripsi_des") ) { 
		  datx = funcSSL_des_encrypt();

      } else if( !strcmp(Funcword, "DEKRIPSI_DES") ||
         !strcmp(Funcword, "dekripsi_des") ) { 
		  datx = funcSSL_des_decrypt();

      } else if( !strcmp(Funcword, "ENKRIPSI_3DES") ||
         !strcmp(Funcword, "enkripsi_3des") ) { 
		  datx = funcSSL_3des_encrypt();

      } else if( !strcmp(Funcword, "DEKRIPSI_3DES") ||
         !strcmp(Funcword, "dekripsi_3des") ) { 
		  datx = funcSSL_3des_decrypt();

	  //} else if( !strcmp(Funcword, "ENKRIPSI_RC4") ||
      //   !strcmp(Funcword, "enkripsi_rc4") ) { 
	  //  datx = funcSSL_rc4_encrypt();

      //} else if( !strcmp(Funcword, "DEKRIPSI_RC4") ||
      //   !strcmp(Funcword, "dekripsi_rc4") ) { 
	  //  datx = funcSSL_rc4_decrypt();

      } else if( !strcmp(Funcword, "ENKRIPSI_AES128CBC") ||
         !strcmp(Funcword, "enkripsi_aes128cbc") ) { 
		  datx = funcSSL_des_encrypt();

      } else if( !strcmp(Funcword, "DEKRIPSI_AES128CBC") ||
         !strcmp(Funcword, "dekripsi_aes128cbc") ) { 
		  datx = funcSSL_des_decrypt();

      } else if( !strcmp(Funcword, "ENKRIPSI_AES128ECB") ||
         !strcmp(Funcword, "enkripsi_aes128ecb") ) { 
		  datx = funcSSL_des_encrypt();

      } else if( !strcmp(Funcword, "DEKRIPSI_AES128ECB") ||
         !strcmp(Funcword, "dekripsi_aes128ecb") ) { 
		  datx = funcSSL_des_decrypt();

      } else if( !strcmp(Funcword, "ENKRIPSI_BLOWFISHCBC") ||
         !strcmp(Funcword, "enkripsi_blowfishcbc") ) { 
		  datx = funcSSL_des_encrypt();

      } else if( !strcmp(Funcword, "DEKRIPSI_BLOWFISHCBC") ||
         !strcmp(Funcword, "dekripsi_blowfishcbc") ) { 
		  datx = funcSSL_des_decrypt();

      } else if( !strcmp(Funcword, "ENKRIPSI_BLOWFISHCFB") ||
         !strcmp(Funcword, "enkripsi_blowfishcfb") ) { 
		  datx = funcSSL_des_encrypt();

      } else if( !strcmp(Funcword, "DEKRIPSI_BLOWFISHCFB") ||
         !strcmp(Funcword, "dekripsi_blowfishcfb") ) { 
		  datx = funcSSL_des_decrypt();

	  /* ======================================================== */
      #endif
      /* ======================================================== */


      #ifdef USE_CGI

      /* ======================================================== */
      /* CGI                 ================================== */
      /* ======================================================== */

      } else if( !strcmp(Funcword, "BASIS64") ||
         !strcmp(Funcword, "basis64") ) { 
		  datx = funcBASIS64();

      } else if( !strcmp(Funcword, "BUKABASIS64") ||
         !strcmp(Funcword, "bukabasis64") ) { 
		  datx = funcBUKABASIS64();

      /* ======================================================== */
      /* POST_NAMA             ================================== */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "POST_NAMA") ||
         !strcmp(Funcword, "post_nama") ) { 
         /* printf("POST_NAMA function\n"); */
		 datx = funcPOST_NAMA();

      /* ======================================================== */
      /* POST_NILAI             ================================= */
      /* ======================================================== */
      } else if( !strcmp(Funcword, "POST_NILAI") ||
                 !strcmp(Funcword, "post_nilai") ) { 
         /* printf("POST_NAMA function\n"); */
		 datx = funcPOST_NILAI();

	  /* ======================================================== */
      #endif
      /* ======================================================== */

	  } else if( !strcmp(Funcword, "BENDABARU") || 
              !strcmp(Funcword, "bendabaru") ||
              !strcmp(Funcword, "BendaBaru") ) { 
         /* printf("BENDABARU function\n"); */
		 datx = funcBendaBaru();

	  } else if(!strcmp(Funcword, "PANJANG")   || 
              !strcmp(Funcword, "panjang")   ||
              !strcmp(Funcword, "Panjang") ) { 
         datx = funcOther();

      } else {
         // read real Ident ...
         memset(&dat_a, '\0', sizeof(dat_a));

         if(currentClass != NULL && strlen(currentClass) > 0) {
           // sprintf(dat_a, "%s->%s", currentClass, Funcword);
           #ifdef WIN32
             #ifndef S_SPLINT_S
             sprintf_s(dat_a, sizeof(dat_a),"%s->%s", currentClass, Funcword);
             #else
             snprintf(dat_a, sizeof(dat_a),"%s->%s", currentClass, Funcword);
             #endif
            #else
            snprintf(dat_a, sizeof(dat_a),"%s->%s", currentClass, Funcword);
            #endif

           //printf(" expression look for ident: %s\n", lex.detail.ident);
           strcpy(datx.ident, dat_a);
           //tmpdat.val = 0;
           datx = ValLabel( dat_a, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
	       //printf(" expression get type %d\n", tmpdat.datatype);

		 } else {

           //printf(" expression look for ident: %s\n", lex.detail.ident);
           strcpy(datx.ident, Funcword);
           //tmpdat.val = 0;
           datx = ValLabel( Funcword, sub_deep, datx, VAL_FLAG_SEARCH_R );
	       //printf(" expression get type %d\n", tmpdat.datatype);

		 }

         if(datx.datatype == 31)  // Copy Class Instance
         {
           datx.isClassInit = 0;  // set AWALAN not inited yet
         }
     }

     return datx;
}



