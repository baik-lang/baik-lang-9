// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyPdfPng ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0, mysize=0;

  double x1=0.0, y1=0.0;
 
  HPDF_Doc  pdf=NULL;
  HPDF_Page ppage=NULL;
  HPDF_Image image=NULL;

  VAL_LABEL valdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

    //printf("keyPdfPng\n");
	do{

	  getlex();

	  switch( lex.type )
	    {

	    case TYPE_NUM:
			if(n == 2)
			  x1 = (double) lex.detail.num;
			if(n == 3)
			  y1 = (double) lex.detail.num;

	      break;  

	    case TYPE_DBL:
			if(n == 2)
			  x1 = (double) lex.detail.dblnum;
			if(n == 3)
			  y1 = (double) lex.detail.dblnum;

	      break;   

	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

			  if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
              } else {
                valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }


              if(valdat.datatype == 71) {           // get pdf page
                if(n == 0) {
				  pdf = valdat.pdf;
				  ppage = valdat.pdf_page;
				  if(ppage == NULL) {
				    printf("pdf page NULL !\n");
				  }
				}

			  } else if(valdat.datatype == 73) {    // get pdf image
                if(n == 1) {
				  image = valdat.pdf_image;
				  if(image == NULL) {
				    printf("pdf image NULL !\n");
				  }
				}

			  } else if(valdat.datatype == 0) {
				if(n == 2)
				  x1 = (double) valdat.val;
				if(n == 3)
				  y1 = (double) valdat.val;

			  } else if(valdat.datatype == 1) {
				if(n == 2)
				  x1 = valdat.floatdata;
				if(n == 3)
				  y1 = valdat.floatdata;


			  } else {
                Error("bentuk perintah pdf_png salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah pdf_png salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	if(n!=4) {
      Error("bentuk perintah pdf_png salah");
	} else {
	  //printf("draw png image ...\n");

      HPDF_Page_DrawImage (ppage, image, x1, y1, HPDF_Image_GetWidth (image),
                    HPDF_Image_GetHeight (image));

	  //printf("draw png image ok\n");
	}

	ungetlex();

}

