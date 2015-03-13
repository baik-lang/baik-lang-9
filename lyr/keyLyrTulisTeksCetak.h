// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2012
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyTulisTeksCetak ()
{
  int  point = 0;
  int  n=0, i=0, j=0;

  long idx=0;                           // array index

  VAL_LABEL valdat,valdat2,tmpdat, tmpdat2;
  VAL_LABEL aksidat;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  double posx = 0.0;
  double posy = 0.0;
  char   tmpMsg[MAX_STRING_LEN];

  memset(&aksidat, '\0', sizeof(aksidat));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  // printf("tulis teks cetak...\n");

  n = 0;

	do{

      getlex();

	  // printf("getlex type : %d\n", lex.type);

	  switch( lex.type )
	    {
	    case TYPE_NUM:
              if(n == 2) {
				posx = (double)lex.detail.num;
              } else
              if(n == 3) {
				posy = (double)lex.detail.num;
              } 
	      break;

	    case TYPE_DBL:
              if(n == 2) {
				posx = (double)lex.detail.dblnum;
              } else
              if(n == 3) {
				posy = (double)lex.detail.dblnum;
              } 
	      break;
   
	    case TYPE_STR:
              if(n == 4) {
				strcpy(tmpMsg, lex.detail.string);
              } 
	      break;

	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

			  if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                aksidat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                aksidat = expression();
              }

              // printf("n %d , aksidat type %d\n", n, aksidat.datatype);

              if(aksidat.datatype == 80) { // print konteks
                if(n == 0) {
				  // printf("get print context \n");
				  tmpdat.cr_img   = aksidat.cr_img;
                  tmpdat.datatype = 80;
				  tmpdat.isGUI    = 1;
				} 
			  } else if(aksidat.datatype == 91) { // print layout
                if(n == 1) {
				  // printf("get print_layout \n");
			      tmpdat2.pango_layout  = aksidat.pango_layout;
                  tmpdat2.datatype = 91;
				  tmpdat2.isGUI     = 1;
				} 
			  } else if(aksidat.datatype == 0) {
                if(n == 2) {
				  posx = (double)aksidat.val;
                } else
                if(n == 3) {
				  posy = (double)aksidat.val;
                } 
			  } else if(aksidat.datatype == 1) {
                if(n == 2) {
				  posx = (double)aksidat.floatdata;
                } else
                if(n == 3) {
				  posy = (double)aksidat.floatdata;
                } 
			  } else if(aksidat.datatype == 3) {
                if(n == 4) {
				  strcpy(tmpMsg, aksidat.str);
                } 
			  } else {
                Error("bentuk perintah tulis_teks_cetak salah");
			  }

	      break;


	    default:
	      Error("bentuk perintah tulis_teks_cetak salah");
	    }

        n++;

	    getlex(); // pass comma

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 5) {
      Error("parameter tulis_teks_cetak tidak lengkap");
    } else {
		if(tmpdat.cr_img == NULL)
			Error("salah konteks_cetakan");

		if(tmpdat2.pango_layout == NULL)
			Error("salah tatanan_cetakan");

        if(tmpdat.datatype == 80 && tmpdat2.datatype == 91) {

          pango_layout_set_text(tmpdat2.pango_layout, tmpMsg, -1);
          pango_layout_set_width(tmpdat2.pango_layout, -1);
          pango_layout_set_alignment(tmpdat2.pango_layout, PANGO_ALIGN_LEFT);

          cairo_move_to(tmpdat.cr_img, posx, posy);
          pango_cairo_show_layout(tmpdat.cr_img, tmpdat2.pango_layout);

		} else {
          Error("parameter pada kode perintah tulis_teks_cetak salah 0");
		}

    }

	ungetlex();

}


