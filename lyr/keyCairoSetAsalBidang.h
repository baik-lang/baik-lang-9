// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyCairoSetAsalBidang ()
{
  double x=0.0;
  double y=0.0;
  int  n=0, mysize=0;

  cairo_t *cr=NULL;
  cairo_surface_t *image=NULL;

  VAL_LABEL valdat, valdat2, tmpdat;
  int idx=0;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  n = 0;

  // printf("keyCairoSetAsal\n");

	do{

	  getlex();

	  switch( lex.type )
	    {

	    case TYPE_DBL:
			if(n == 2) {
			  x =  lex.detail.dblnum;
			} else
			if(n == 3) {
			  y =  lex.detail.dblnum;
			} 
	      break; 

	    case TYPE_NUM:
			if(n == 2) {
			  x =  (double)lex.detail.num;
			} else
			if(n == 3) {
			  y =  (double)lex.detail.num;
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
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
              } else {
                valdat = ValLabel( lex.detail.string, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }

              if(valdat.datatype == 80) { // cairo img
                if(n == 0) {
				  cr = valdat.cr_img;
				  if(cr == NULL)
					  printf("latar Nil!\n");
				}
			  } else if(valdat.datatype == 81) { // cairo surface image
				if(n == 1) {
			      image = valdat.cr_surface;
				  if(image == NULL)
					  printf("image Nil!\n");
				} 
			  } else if(valdat.datatype == 1) {
				if(n == 2) {
					x = valdat.floatdata;
				} else
				if(n == 3) {
					y = valdat.floatdata;
				} 
			  } else if(valdat.datatype == 0) {
				if(n == 2) {
					x = (double)valdat.val;
				} else
				if(n == 3) {
					y = (double)valdat.val;
				} 
			  } else {
                Error("bentuk perintah set_asalbidang / set_pola salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah set_asalbidang / set_pola salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	ungetlex();

	if(n!=4) {
      Error("bentuk perintah set_asalbidang / set_pola salah");
	} else {
	  // printf("set source surface...\n");
	  cairo_set_source_surface (cr, image, x, y);
	}

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));

}



