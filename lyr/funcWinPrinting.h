// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2012
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


VAL_LABEL funcWinTinggiCetakan ()
{

  int  n=0;
  double  tmp_a = 0.0;
  double  tmp_b = 0.0;  

  VAL_LABEL datx,valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  n = 0;

	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_NUM:
              if(n == 0) {
                tmp_a = lex.detail.num;
              } else
              if(n == 1) {
                tmp_b = lex.detail.num;
              } 
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

	      if(currentClass != NULL && strlen(currentClass) > 0) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #endif
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

				valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 0) {
                if(n == 0) {
                  tmp_a = valdat.val;
                } else
                if(n == 1) {
                  tmp_b = valdat.val;
                } 
			  } else if(valdat.datatype == 1) {
                if(n == 0) {
                  tmp_a = valdat.floatdata;
                } else
                if(n == 1) {
                  tmp_b = valdat.floatdata;
                } 
			  } else {
                Error("bentuk perintah TINGGI_CETAKAN salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah TINGGI_CETAKAN salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' && lex.detail.symbol != '\n');

	ungetlex();

    if(n == 2) {
	 datx.floatdata = gtk_print_context_get_height (BAIK_Print_Context) - tmp_a - tmp_b;
	 datx.datatype = 1;   // double

	 return datx;

    } else {
      Error("parameter TINGGI_CETAKAN tidak lengkap");
	  return datx;

	}

}


VAL_LABEL funcWinBarisPerHalaman ()
{

  int  n=0;
  double  tmp_a = 0.0;
  double  tmp_b = 0.0;  
  double  tmp_c = 0.0; 

  VAL_LABEL datx,valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  n = 0;

	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_NUM:
              if(n == 0) {
                tmp_a = lex.detail.num;
              } else
              if(n == 1) {
                tmp_b = lex.detail.num;
              } else
              if(n == 2) {
                tmp_c = lex.detail.num;
              } 
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

	      if(currentClass != NULL && strlen(currentClass) > 0) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #endif
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

				valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 0) {
                if(n == 0) {
                  tmp_a = valdat.val;
                } else
                if(n == 1) {
                  tmp_b = valdat.val;
                } else
                if(n == 2) {
                  tmp_c = valdat.val;
                } 
			  } else if(valdat.datatype == 1) {
                if(n == 0) {
                  tmp_a = valdat.floatdata;
                } else
                if(n == 1) {
                  tmp_b = valdat.floatdata;
                } else
                if(n == 2) {
                  tmp_c = valdat.floatdata;
                } 
			  } else {
                Error("bentuk perintah BARIS_PER_HALAMAN salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah BARIS_PER_HALAMAN salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' && lex.detail.symbol != '\n');

	ungetlex();

    if(n == 3) {
	  if((tmp_b + tmp_b*2 + tmp_c) != 0.0) {
	    // printf("get param %f %f %f \n", tmp_a, tmp_b, tmp_c);
	    datx.floatdata = floor (tmp_a / (tmp_b + tmp_b*2 + tmp_c));
	  } else {
        datx.floatdata = 0.0;
	  }

	  datx.datatype = 1;   // double

	  return datx;

    } else {
      Error("parameter BARIS_PER_HALAMAN tidak lengkap");
	  return datx;

	}

}


VAL_LABEL funcWinSetAtributCetak ()
{

  int  n=0;

  int  font_size=0;
  char name[MAX_STRING_LEN];

  VAL_LABEL datx,valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&name, '\0', sizeof(name));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  n = 0;

	do{

	  getlex();

	  // printf("got type %d \n", lex.type);

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 1) {
				strcpy(name, lex.detail.string);
              } 
	      break;

	    case TYPE_NUM:
              if(n == 2) {
                font_size = lex.detail.num;
              } 
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

	      if(currentClass != NULL && strlen(currentClass) > 0) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #endif
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

				valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 91) {
                if(n == 0) {
			      // printf("get pango_layout \n");
			      tmpdat.pango_layout  = valdat.pango_layout;
                  tmpdat.datatype = 91;
				}
			  } else if(valdat.datatype == 0) {
                if(n == 2) {
                  font_size = valdat.val;
                } 
			  } else if(valdat.datatype == 1) {
                if(n == 2) {
                  font_size = abs(valdat.floatdata);
                } 
			  } else if(valdat.datatype == 3) {
                if(n == 1) {
                  strcpy(name, valdat.str);
                } 
			  } else {
                Error("bentuk perintah SET_ATRIBUT_CETAK salah 0");
			  }

	      break;

	    default:
	      Error("bentuk perintah SET_ATRIBUT_CETAK salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' && lex.detail.symbol != '\n');

	ungetlex();

    if(n == 3) {

     datx.font_desc   = pango_font_description_from_string("Arial");
	 pango_font_description_set_size(datx.font_desc, font_size * PANGO_SCALE);
	 pango_layout_set_font_description(tmpdat.pango_layout, datx.font_desc);

	 datx.datatype = 42;   // font_desc

	 return datx;

    } else {
      Error("parameter SET_ATRIBUT_CETAK tidak lengkap");
	  return datx;

	}

}


VAL_LABEL funcWinTinggiTeksCetak ()
{
  int layout_height = 0;
  VAL_LABEL datx,valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

	  getlex();

	  switch( lex.type )
	    {
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

	      if(currentClass != NULL && strlen(currentClass) > 0) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #endif
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

				valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 91) {
			    // printf("get pango_layout \n");
			    tmpdat.pango_layout  = valdat.pango_layout;
                tmpdat.datatype = 91;
			  } else {
                Error("bentuk perintah TINGGI_TEKS_CETAK salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah TINGGI_TEKS_CETAK salah");
	    }

	 if(tmpdat.pango_layout != NULL) {
       pango_layout_get_size(tmpdat.pango_layout, NULL, &layout_height);
	   datx.floatdata = (double) (layout_height / PANGO_SCALE);
	 }
	 datx.datatype = 1;   // double

	 return datx;

}

VAL_LABEL funcWinLebarTeksCetak ()
{
  int n = 0;
  int text_width = 0;
  VAL_LABEL datx,valdat,tmpdat;

  char tmpMsg[MAX_STRING_LEN];
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  n = 0;

	do{

	  getlex();

	  switch( lex.type )
	    {

	    case TYPE_STR:
              if(n == 1) {
				strcpy(tmpMsg, lex.detail.string);
              } 
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

	      if(currentClass != NULL && strlen(currentClass) > 0) {
                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #endif
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

				valdat = ValLabel( lex.detail.ident, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 91) {
				if(n == 0) {
			      // printf("get pango_layout \n");
			      tmpdat.pango_layout  = valdat.pango_layout;
                  tmpdat.datatype = 91;
				}
			  } else if(valdat.datatype == 3) {
				if(n == 1) {
			      strcpy(tmpMsg , valdat.str);
				}
			  } else {
                Error("bentuk perintah LEBAR_TEKS_CETAK salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah LEBAR_TEKS_CETAK salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' && lex.detail.symbol != '\n');

	ungetlex();

	if(n == 2) {

	 if(tmpdat.pango_layout != NULL) {
       pango_layout_set_text(tmpdat.pango_layout, tmpMsg, -1);
       pango_layout_get_size(tmpdat.pango_layout, &text_width, NULL);
	   text_width = (int) (text_width / PANGO_SCALE);
	   datx.val = text_width;
	 }
	 datx.datatype = 0;   // int

	} else {
      Error("parameter LEBAR_TEKS_CETAK tidak lengkap");
	}

	return datx;

}
