// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2012
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#include <math.h>

void keySetOperasiCetak ()
{
  int  tmp_a = 0;

  int  n=0, i=0, j=0;

  long idx=0;                           // array index

  VAL_LABEL valdat,valdat2,tmpdat, tmpdat2;
  VAL_LABEL aksidat;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];


  // printf("keySetOperasiCetak ------------------------------------- \n");

  memset(&aksidat, '\0', sizeof(aksidat));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  n = 0;

	do{

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_NUM:
              if(n == 1) {
                tmp_a = lex.detail.num;
              }
	      break;

	    case TYPE_DBL:
              if(n == 1) {
                tmp_a = floor(lex.detail.dblnum);
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

              if(aksidat.datatype == 90) { // Print Ope
                if(n == 0) {
				  // printf("get print_ope \n");
				  tmpdat2.gtk_print_ope   = aksidat.gtk_print_ope;
                  tmpdat2.datatype = 90;
				  tmpdat2.GUItype  = aksidat.GUItype;
				} 
			  } else if(aksidat.datatype == 0) {
				if(n == 1)
				  tmp_a = aksidat.val;
			  } else if(aksidat.datatype == 1) {
				if(n == 1)
				  tmp_a = floor(aksidat.floatdata);
			  } else {
                Error("bentuk perintah set_operasi_cetak salah");
			  }

	      break;


	    default:
	      Error("bentuk perintah set_operasi_cetak salah");
	    }

        n++;

	    getlex(); // pass comma

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	// printf("keySetOperasiCetak num param : %d , tmp_a %d \n", n , tmp_a);

    if(n != 2) {
      Error("parameter set_operasi_cetak tidak lengkap");
    } else {
	  if(tmp_a != 0) {
        // printf("set num page %d into operation \n", tmp_a);

        gtk_print_operation_set_n_pages (tmpdat2.gtk_print_ope, tmp_a);

		// apply operation into BaiK param
		BAIK_Print_Operation = tmpdat2.gtk_print_ope;

		// printf("set operasi cetak OK \n");
	  }
    }

	ungetlex();

}


