// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2012
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyMulaiCetak ()
{
  int  type_func = 0; // 0: general function , 1: object function
  int  point = 0;
  int  n=0, i=0, j=0;

  long idx=0;                           // array index
  int  tmp_deep=0;

  VAL_LABEL valdat,valdat2,tmpdat, tmpdat2;
  VAL_LABEL aksidat;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  char   logMsg[MAX_STRING_LEN];
  char   tmpMsg[MAX_STRING_LEN];


  AksiPrintData *dat=NULL;
  GtkPrintOperationResult res;

  memset(&aksidat, '\0', sizeof(aksidat));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&tmpdat2, '\0', sizeof(tmpdat2));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&logMsg, '\0', sizeof(logMsg));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  // printf("Mulai cetak...\n");

  n = 0;

	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  // printf("getlex type : %d\n", lex.type);

	  switch( lex.type )
	    {
   
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

              if(aksidat.datatype == 40) { // Widget
                if(n == 0) {
				  // printf("get widget \n");
				  tmpdat.widget   = valdat.widget;
                  tmpdat.datatype = 40;
				  tmpdat.GUItype  = valdat.GUItype;
				} 
			  } else if(aksidat.datatype == 90) { // Print Ope
                if(n == 1) {
				  // printf("get print_ope \n");
				  tmpdat2.gtk_print_ope   = aksidat.gtk_print_ope;
                  tmpdat2.datatype = 90;
				  tmpdat2.GUItype  = aksidat.GUItype;
				} 
			  } else {
                Error("bentuk perintah mulai_cetak salah");
			  }

	      break;


	    default:
	      Error("bentuk perintah mulai_cetak salah");
	    }

        n++;

	    getlex(); // pass comma

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');

	// printf("num param : %d , deep : %d \n", n, sub_deep);

    if(n != 2) {
      Error("parameter mulai_cetak tidak lengkap");
    } else {

        if(tmpdat.datatype == 40 && tmpdat2.datatype == 90) {
		  // printf("Mulai Cetak .......\n");

		  // run print
          res = gtk_print_operation_run (tmpdat2.gtk_print_ope, GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG,
                                         GTK_WINDOW (tmpdat.widget), NULL);

          if (res == GTK_PRINT_OPERATION_RESULT_APPLY)
          {
            if (BAIK_PRINT_settings != NULL)
              g_object_unref (BAIK_PRINT_settings);
            BAIK_PRINT_settings = g_object_ref (gtk_print_operation_get_print_settings (tmpdat2.gtk_print_ope));
          }

          g_object_unref (tmpdat2.gtk_print_ope);

		} else {
          Error("parameter pada kode perintah mulai_cetak salah 0");
		}

    }

	ungetlex();

}


