// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// sewing a new history ...
// my coding, my way, my inspiration ...
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


enum
{
/* ********************   Language Word    ***************************  */
/*           lex.type     padanan                                       */
  _TULIS,       /* 0      PRINT                                         */
  _MASUK,       /* 1      INPUT                                         */
  _KALAU,       /* 2      IF                                            */
  _MAKA,        /* 3      THEN                                          */
  _LAINNYA,     /* 4      ELSE                                          */
  _STOPKALAU,   /* 5      ENDIF                                         */
  _LONCATLABEL, /* 6      LONCATLABEL --- changed since ver 5           */
  _LONCAT,      /* 7      GOTO                                          */
  _END,         /* 8      END                                           */
  _DAN,         /* 9      AND                                           */
  _ATAU,        /* 10     OR                                            */
  _NOT,         /* 11     NOT                                           */
  _TULISLOG,    /* 12     writeLog                                      */
  _PERINTAH,    /* 13     EXEC                                          */
  _TUNGGU,      /* 14     SLEEP                                         */
  _SUB,         /* 15     SUBROUTINE                                    */
  _RETURN,      /* 16     RETURN                                        */
  _SURAT,       /* 17     Send Mail                                     */
  _SELAGI,      /* 18     WHILE                                         */
  _LAKUKAN,     /* 19     DO                                            */
  _BALIKLAGI,   /* 20     ENDWHILE                                      */
  _UNTUK,       /* 21     FOR                                           */
  _ULANG,       /* 22     FOR DO                                        */
  _LAGI,        /* 23     NEXT                                          */
  _MUSIK,       /* 24     Play Wave file                                */
  _JENDELA,     /* 25     Popup Window                                  */
  _KONEKSI,     /* 26     CONNECT                                       */
  _TUTUP,       /* 27     CLOSE                                         */
  _EOF,         /* 28     End of file                                   */
  _UNTAI,       /* 29     ARRAY define                                  */
  _HAPUS,       /* 30     ARRAY memory clear                            */
  _TULIS_ARSIP, /* 31     FPRINTF                                       */
  _PILIH,        /* 32     SWITCH                                       */
  _SAMA,         /* 33     CASE                                         */
  _AKHIRPILIH,   /* 34     ENDCASE                                      */
  _KELUARSELAGI, /* 35     BREAK WHILE                                  */
  _KELUARUNTUK,  /* 36     BREAK FOR                                    */
  _LANJUT,       /* 37     CONTINUE                                     */
  _LAINKALAU,    /* 38     ELSEIF                                       */

/* *******************************************************************  */
  _BENDA,        /* 39     OBJ / CLASS                                  */
  _DEF_BENDA,    /* 40     OBJ / CLASS DEFINITION                       */
/* *******************************************************************  */
  _LOKAL,        /* 41     VAR SCOPE LOCAL                              */
/* *******************************************************************  */

/* CGI Handle                                           */
  _POST_CGI,              /* 42     CGI handling        */

/* GD Graphic Handle                                    */
  _GAMBAR_GARIS,          /* 43 gdImageLine             */
  _GAMBAR_GARIS_PUTUS,    /* 44 gdImageDashedLine       */
  _GAMBAR_POLIGON,        /* 45 gdImagePolygon          */
  _GAMBAR_POLIGON_ISI,    /* 46 gdImageFilledPolygon    */
  _GAMBAR_KOTAK,          /* 47 gdImageRectangle        */
  _GAMBAR_KOTAK_ISI,      /* 48 gdImageFilledRectangle  */
  _GAMBAR_LINGKARAN,      /* 49 gdImageArc              */
  _GAMBAR_LINGKARAN_ISI,  /* 50 gdImageFilledArc        */
  _SIMPAN_GAMBAR_PNG,     /* 51 gdImagePngPtr           */
  _SIMPAN_GAMBAR_JPG,     /* 52 gdImageJpgPtr           */
  _HAPUS_GAMBAR,          /* 53 gdImageDestroy          */
  _GAMBAR_HURUF,          /* 54 gdImageString           */

/* Html Style Handle                                    */
  _SEDIA_WEBSTYLE,        /* 55 Prepare Html style file */
  _HTML_AWAL,             /* 56 Html start              */
  _HTML_STYLE,            /* 57 Html style              */
  _HTML_MENU_AWAL,        /* 58 Html menu start         */
  _HTML_MENU_AKHIR,       /* 59 Html menu end           */
  _HTML_MENU,             /* 60 Html menu               */
  _HTML_HAKCIPTA,         /* 61 Html copyright          */
  _ISIWEB_TITEL,          /* 62 Header of Html menu     */
  _ISIWEB_AWAL,           /* 63 main menu start         */
  _ISIWEB_AKHIR,          /* 64 main menu end           */
  _HTML_AKHIR,            /* 65 Html end                */

  _KODE_LUAR,             /* 66 Include Source Code     */
  _END_KODE_LUAR,         /* 67 EOF Include File        */

  _TULIS_RINCI,           /* 68 PRINT DETAIL            */

  _HTMLJS_GAMBARSTYLE,    /* 69 Html Style for Drawing  */
  _HTMLJS_AWALGAMBAR,     /* 70 Html Style for Drawing  */
  _HTMLJS_AKHIRGAMBAR,    /* 71 Html Style for Drawing  */
  _HTMLJS_WARNA,          /* 72 Html Style for Drawing  */
  _HTMLJS_GARIS,          /* 73 Html Style for Drawing  */
  _HTMLJS_TEBALGARIS,     /* 74 Html Style for Drawing  */
  _HTMLJS_KOTAK,          /* 75 Html Style for Drawing  */
  _HTMLJS_KOTAKISI,       /* 76 Html Style for Drawing  */
  _HTMLJS_LINGKARAN,      /* 77 Html Style for Drawing  */
  _HTMLJS_LINGKARANISI,   /* 78 Html Style for Drawing  */
  _HTMLJS_HURUFBESAR,     /* 79 Html Style for Drawing  */
  _HTMLJS_HURUFSEDANG,       /* 80 Html Style for Drawing  */
  _HTMLJS_HURUFSEDANGTEBAL,  /* 81 Html Style for Drawing  */
  _HTMLJS_HURUFSEDANGMIRING, /* 82 Html Style for Drawing  */
  _HTMLJS_HURUFKECIL,        /* 83 Html Style for Drawing  */
  _HTMLJS_TULIS,             /* 84 Html Style for Drawing  */

/* GTK GUI Layar Handle                                    */
  _PAKAI_LAYAR,           // 85

  _TAMPIL_LAYAR,          // 86
  _TITEL_LAYAR,           // 87
  _LUAS_LAYAR,            // 88
  _LOGO_LAYAR,            // 89

  _HIAS_LAYAR,            // 90
  _HIAS_ALAS,             // 91

  _SUBMENU,               // 92
  _TAMBAH_MENU,           // 93
  _AKHIR_MENU,            // 94
  _SUSUN_MENU,            // 95
  _SUSUN_PAPAN_STATUS,    // 96

  _AKSI_TUTUP_LAYAR,      // 97
  _AKSI_FUNGSI,           // 98

  _AKSI_RAMBU_INFO,       // 99
  _AKSI_RAMBU_SALAH,      // 100
  _AKSI_RAMBU_AWAS,       // 101

  _RAMBU_INFO,            // 102
  _RAMBU_SALAH,           // 103
  _RAMBU_TANYA,           // 104
  _RAMBU_AWAS,            // 105

  _SET_WARNAHURUF,        // 106
  _SET_WARNADASAR,        // 107
  _SET_JENISHURUF,        // 108
  _SET_PILIHAN,           // 109

  _KIBAR_LAYAR,           // 110
  _SET_LABEL,             // 111
  _SET_MASUKAN,           // 112
  _SET_TIPS,              // 113 ToolTip
  _SET_KERTAS,            // 114

  _AKSI_JATIDIRI,         // 115

  _TAMPIL_ELEMEN,         // 116
  _SEMBUNYI_ELEMEN,       // 117

  _AKSI_TEKAN_KETIK,       // 118
  _AKSI_LEPAS_KETIK,       // 119
  _AKSI_TEKAN_MOUSE,       // 120
  _AKSI_LEPAS_MOUSE,       // 121
  _AKSI_MOUSE_BERGERAK,    // 122

  _HIAS_LAYAR_GULUNG,      // 123
  _SET_STATUS,             // 124
  _HAPUS_STATUS,           // 125

  _ISI_ALAS_TEGAK,         // 126

  _TAMBAH_AKSELERASI,      // 127
  _SET_SENSITIF,           // 128
  _TAMPIL_POPUP,           // 129

  _TABEL_ATRIBUT,          // 130
  _TABEL_DATA,             // 131
  _HAPUS_SEL_TABEL,        // 132
  _TULIS_TABEL,            // 133
  _TULIS_SEL_TABEL,        // 134

  _ISI_PUNDI_TEKS,         // 135
  _ISI_TEKS_RAMPUNG,       // 136
  _SET_TEKS_RAMPUNG,       // 137

  _HAPUS_TEKS_TERPILIH,    // 138
  _SALIN_TEKS_PAPANKLIP,   // 139
  _POTONG_TEKS_PAPANKLIP,  // 140
  _UNDUH_TEKS_PAPANKLIP,   // 141

  _TANGGALAN,              // 142
  _AKSI_TUTUP_PROGRAM,     // 143

  _SIMPAN_TEKS,            // 144

  _PDF_SETHURUF,           // 145
  _PDF_AWALTEKS,           // 146
  _PDF_AKHIRTEKS,          // 147
  _PDF_TEKS,               // 148

  _PDF_PNG,                // 149
  _PDF_JPG,                // 150

  _PDF_SIMPANPDF,          // 151
  _PDF_HAPUS,              // 152

  _PDF_LUKIS,              // 153  STROKE
  _PDF_TEBALGARIS,         // 154  
  _PDF_WARNAGARIS,         // 155  
  _PDF_KOTAK,              // 156  RECT
  _PDF_POS,                // 157  MOVETO
  _PDF_GARIS,              // 158  LINETO

  _PDF_WARNAHURUF,         // 159  
  _PDF_JARAKHURUF,         // 160
  _PDF_JARAKKATA,          // 161

/* Cairo Graphic Handle                                      */
  _LUKIS_GARIS,          /* 162 cairo_move_to cairo_lineto    */
  _LUKIS_TEKS,           /* 163 cairo_move_to cairo_show_text */
  _LUKIS_KOTAK,          /* 164 cairo_rectangle cairo_stroke  */
  _LUKIS_KOTAK_ISI,      /* 165 cairo_rectangle cairo_fill    */

  _LUKIS_LINGKARAN,      /* 166 cairo_arc cairo_stroke        */
  _LUKIS_LINGKARAN_ISI,  /* 167 cairo_arc cairo_fill          */

  _SIMPAN_LUKISAN,       /* 168 cairo_surface_write_to_png    */
  _HAPUS_LATAR,          /* 169 cairo_destroy                 */
  _HAPUS_BIDANG,         /* 170 cairo_surface_destroy         */
  _HAPUS_POLA,           /* 171 cairo_pattern_destroy         */

  _WARNA_PENA,           /* 171 cairo_set_source_rgb          */
  _WARNA_TRANSPARAN,     /* 172 cairo_set_source_rgba         */
  _PUDAR_PENA,           /* 173 cairo_paint_with_alpha        */
  _PINDAH_PENA,          /* 174 cairo_move_to                 */
  _GESER_PENA,           /* 175 cairo_line_to                 */

  _KLIP_PENA ,           /* 176 cairo_clip                    */
  _KLIP_LINGKARAN,       /* 177 cairo_arc cairo_clip          */
  _KLIP_KOTAK,           /* 178 cairo_rectangle cairo_clip    */

  _GORES_PENA,           /* 179 cairo_stroke                  */
  _GORES_PENA_JAGA,      /* 180 cairo_stroke_preserve         */

  _LUKIS_PENA,           /* 181 cairo_paint                   */
  _ISI_PENA,             /* 182 cairo_fill                    */
  _ISI_PENA_JAGA,        /* 183 cairo_fill_preserve           */

  _TEBAL_GARIS,          /* 184 cairo_line_width              */
  _PUCUK_GARIS,          /* 185 cairo_line_cap                */
  _BENTUK_SAMBUNGAN,     /* 186 cairo_line_join               */
  _GARIS_PUTUS,          /* 187 cairo_set_dash                */
  _ATRIBUT_TEKS,         /* 188 cairo_select_font_face size   */

  _LEKUKAN_TEKS,         /* 190 cairo_move_to cairo_text_path */
  _LEKUKAN_BARU,         /* 191 cairo_new_path                */

  _TUTUP_KURVA,          /* 192 cairo_close_path              */

  _POLA_WARNA,           /* 193 cairo_pattern_add_color_stop_rgb  */
  _SET_ASAL,             /* 194 cairo_set_source                  */
  _SET_ASALBIDANG,       /* 195 cairo_set_source_surface          */

  _AKSI_EKSPOS,          // 196 drawing_area expose_event
  _AKSI_ATUR,            // 197 drawing_area configure_event

  _EKSPOS_KANVAS,        // 198  gtk_widget_draw(drawing_area, NULL) ?

  _GESER_LATAR,          // 199 cairo_translate
  _SKALA_LATAR,          // 200 cairo_scale
  _PUTAR_LATAR,          // 201 cairo_rotate

  _GLOBAL,               // 202 Global Param
  _DETAK_WAKTU,          // 203 g_timeout_add
  _STOP_DETAK,           // 204 stop detak

  _HAPUS_PIXMAP,         // 205 draw_pixmap
  _LUKIS_PIXMAP,         // 206 draw_pixmap

  _MUSIK_BGM,            // 207 threaded musik

  _CEK_MEMORI,           // 208 debug : print var memori alloc

  _LEMBAR_BUKU,          // 209
  _TAB_BUKU,             // 210

  _TAMBAH_RANTING,       // 211
  _WARNADASAR_SEL,       // 212
  _WARNAHURUF_SEL,       // 213
  _JENISHURUF_SEL,       // 214

  _SET_TOMBOL,           // 215
  _AKSI_SIAP_CETAK,      // 216
  _AKSI_CETAK_TEKS,      // 217
  _MULAI_CETAK,          // 218
  _SET_OPERASI_CETAK,    // 219
  _TULIS_TEKS_CETAK,     // 220

  _SAKLAR_HIDUP,         // 221
  _SAKLAR_MATI,          // 222

  _RUPA,                 // 223

/* Other Data Word                                      */
  TYPE_NUM,           /* 224 number                     */
  TYPE_IDENT,         /* 225 variable or label name     */
  TYPE_STR,           /* 226 string                     */
  TYPE_DBL,           /* 227  double number              */
  TYPE_SYM,           /* 228 symbol char                */
  TYPE_ARRAY,         /* 229 array var                  */
  TYPE_OBJECT,        /* 230 object var                 */
  TYPE_OBJECT_FUNC,   /* 231 object func                */

/* ValLabel : Keep variable inside memory               */
  VAL_FLAG_START,      /* make tree searching           */
  VAL_FLAG_SEARCH_R,   /* search data from tree         */
  VAL_FLAG_SEARCH_W,   /* write data into tree          */

  VAL_FLAG_SEARCH_D,   /* delete data from tree         */
  VAL_FLAG_END,        /* delete all data from tree     */
  VAL_FLAG_PRINT       /* delete all data from tree     */
};

