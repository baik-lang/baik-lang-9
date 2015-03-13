// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyHTMLJS_GAMBARSTYLE ()
{

  char ident[MAX_IDENT_LEN];

  char logMsg[MAX_STRING_LEN * 2],
       tmpMsg[MAX_STRING_LEN * 2];

  int  n=0, i=0, j=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  

  int    idx=0, idx2=0;                           // array index

  char keep_string[MAX_STRING_LEN];

  char tmpstr[MAX_STRING_LEN];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  memset(&tmp_str, '\0', sizeof(tmp_str));
  
  memset(&ident, '\0', sizeof(ident));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));
  memset(&logMsg, '\0', sizeof(logMsg));

  memset(&keep_string, '\0', sizeof(keep_string));
  memset(&tmpstr, '\0', sizeof(tmpstr));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

	  getlex();
	  switch( lex.type )
	    {
	    case TYPE_STR:
              printf("</head> \n");
              printf("<script type=\"text/javascript\" src=\"%s/wz_jsgraphics.js\"> </script> \n", lex.detail.string);
              printf("<body> \n");
              fflush( stdout );

	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.datatype == 0 || strlen(valdat.str) > 0) {
                printf("</head> \n");
                printf("<script type=\"text/javascript\" src=\"%s/wz_jsgraphics.js\"> </script> \n", valdat.str);
                printf("<body> \n");
                fflush( stdout );
              }

              break;

	    default:
	      Error("kode perintah HTMLJS_GAMBARSTYLE salah");
	    }

	  getlex();
	  fflush( stdout );
	  ungetlex();


}

void keyHTMLJS_WARNA ()
{

  int  n=0, i=0, j=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, tmpdat;
  
  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));

  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

	  getlex();
	  switch( lex.type )
	    {
	    case TYPE_STR:
             if(!strcmp(lex.detail.string, "biru") || !strcmp(lex.detail.string, "BIRU"))
               strcpy(dat_a, "blue");
             else if(!strcmp(lex.detail.string, "biru muda") || !strcmp(lex.detail.string, "BIRU MUDA"))
               strcpy(dat_a, "lightblue");
             else if(!strcmp(lex.detail.string, "hijau") || !strcmp(lex.detail.string, "HIJAU"))
               strcpy(dat_a, "green");
             else if(!strcmp(lex.detail.string, "hijau muda") || !strcmp(lex.detail.string, "HIJAU MUDA"))
               strcpy(dat_a, "lightgreen");
             else if(!strcmp(lex.detail.string, "merah") || !strcmp(lex.detail.string, "MERAH"))
               strcpy(dat_a, "red");
             else if(!strcmp(lex.detail.string, "merah muda") || !strcmp(lex.detail.string, "MERAH MUDA"))
               strcpy(dat_a, "pink");
             else if(!strcmp(lex.detail.string, "kuning") || !strcmp(lex.detail.string, "KUNING"))
               strcpy(dat_a, "yellow");
             else if(!strcmp(lex.detail.string, "jingga") || !strcmp(lex.detail.string, "JINGGA"))
               strcpy(dat_a, "orange");
             else if(!strcmp(lex.detail.string, "kuning emas") || !strcmp(lex.detail.string, "KUNING EMAS"))
               strcpy(dat_a, "gold");
             else if(!strcmp(lex.detail.string, "merah jambu") || !strcmp(lex.detail.string, "MERAH JAMBU"))
               strcpy(dat_a, "pink");
             else if(!strcmp(lex.detail.string, "ungu") || !strcmp(lex.detail.string, "UNGU"))
               strcpy(dat_a, "purple");
             else if(!strcmp(lex.detail.string, "kelabu") || !strcmp(lex.detail.string, "KELABU"))
               strcpy(dat_a, "gray");
             else {
               strcpy(dat_a, lex.detail.string);
             }

              printf(" jg_doc.setColor('%s');  \n", dat_a);
              fflush( stdout );

	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.datatype == 0 || strlen(valdat.str) > 0) {
                if(!strcmp(valdat.str, "biru") || !strcmp(valdat.str, "BIRU"))
                  strcpy(dat_a, "blue");
                else if(!strcmp(valdat.str, "biru muda") || !strcmp(valdat.str, "BIRU MUDA"))
                  strcpy(dat_a, "lightblue");
                else if(!strcmp(valdat.str, "hijau") || !strcmp(valdat.str, "HIJAU"))
                  strcpy(dat_a, "green");
                else if(!strcmp(valdat.str, "hijau muda") || !strcmp(valdat.str, "HIJAU MUDA"))
                  strcpy(dat_a, "lightgreen");
                else if(!strcmp(valdat.str, "merah") || !strcmp(valdat.str, "MERAH"))
                  strcpy(dat_a, "red");
                else if(!strcmp(valdat.str, "merah muda") || !strcmp(valdat.str, "MERAH MUDA"))
                  strcpy(dat_a, "pink");
                else if(!strcmp(valdat.str, "kuning") || !strcmp(valdat.str, "KUNING"))
                  strcpy(dat_a, "yellow");
                else if(!strcmp(valdat.str, "jingga") || !strcmp(valdat.str, "JINGGA"))
                  strcpy(dat_a, "orange");
                else if(!strcmp(valdat.str, "kuning emas") || !strcmp(valdat.str, "KUNING EMAS"))
                  strcpy(dat_a, "gold");
                else if(!strcmp(valdat.str, "merah jambu") || !strcmp(valdat.str, "MERAH JAMBU"))
                  strcpy(dat_a, "pink");
                else if(!strcmp(valdat.str, "ungu") || !strcmp(valdat.str, "UNGU"))
                  strcpy(dat_a, "purple");
                else if(!strcmp(valdat.str, "kelabu") || !strcmp(valdat.str, "KELABU"))
                  strcpy(dat_a, "gray");
                else {
                  strcpy(dat_a, valdat.str);
                }

                printf(" jg_doc.setColor('%s');  \n", dat_a);
                fflush( stdout );
              }

              break;

	    default:
	      Error("kode perintah HTMLJS_WARNA salah");
	    }

	  getlex();
	  fflush( stdout );
	  ungetlex();

}


void keyHTMLJS_GARIS ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0;

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;

	do{

	  getlex();
      //printf(" DEBUG: HTMLJS_GARIS lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    
            case TYPE_ARRAY:
              /* printf("write array\n"); */

              if(strlen(lex.detail.array_str) > 0) {
                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atoi (valdat.array_idx);
                } else {
                   /* printf("show NOT digit\n"); */
                   /* Read index param */
                   tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

	        valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                sprintf(valdat2.array_idx, "%d", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  if(n == 0)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 1)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:

                if(n == 0)                           /* ord x start */
                  dat_num = lex.detail.num;
                if(n == 1)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 2)                           /* ord x end   */
                  dat_num3 = lex.detail.num;
                if(n == 3)                           /* ord y end   */
                  dat_num4 = lex.detail.num;

	      break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                // printf("HTMLJS_GARIS class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.datatype == 0) {
                if(n == 0)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 1)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 2)                           /* ord x end   */
                  dat_num3 = valdat.val;
                if(n == 3)                           /* ord y end   */
                  dat_num4 = valdat.val;

              } else {
                 Error("kode perintah HTMLJS_GARIS salah");
              }

	      break;

	    default:
	      Error("kode perintah HTMLJS_GARIS salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 4) {
           Error("parameter kode perintah HTMLJS_GARIS salah");
        } else {
           /*
           printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           */

           printf(" jg_doc.drawLine(%d,%d,%d,%d); \n", dat_num, dat_num2, dat_num3, dat_num4);
           printf(" jg_doc.paint(); \n"); // flush paint
           fflush( stdout );

        }

	ungetlex();

}


void keyHTMLJS_KOTAK ()
{

  int  n=0, i=0, j=0;


  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0;

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;

	do{

	  getlex();
      //printf(" DEBUG: HTMLJS_KOTAK lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    
            case TYPE_ARRAY:
              /* printf("write array\n"); */

              if(strlen(lex.detail.array_str) > 0) {
                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atoi (valdat.array_idx);
                } else {
                   /* printf("show NOT digit\n"); */
                   /* Read index param */
                   tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

	        valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                //itoa(idx, valdat2.array_idx, 10);
                sprintf(valdat2.array_idx, "%d", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  if(n == 0)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 1)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:

                if(n == 0)                           /* ord x start */
                  dat_num = lex.detail.num;
                if(n == 1)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 2)                           /* ord x end   */
                  dat_num3 = lex.detail.num;
                if(n == 3)                           /* ord y end   */
                  dat_num4 = lex.detail.num;

	      break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                // printf("HTMLJS_KOTAK class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.datatype == 0) {
                if(n == 0)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 1)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 2)                           /* ord x end   */
                  dat_num3 = valdat.val;
                if(n == 3)                           /* ord y end   */
                  dat_num4 = valdat.val;

              } else {
                 Error("kode perintah HTMLJS_KOTAK salah");
              }

	      break;

	    default:
	      Error("kode perintah HTMLJS_KOTAK salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 4) {
           Error("parameter kode perintah HTMLJS_KOTAK salah");
        } else {
           /*
           printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           */

           printf(" jg_doc.drawRect(%d,%d,%d,%d); \n", dat_num, dat_num2, dat_num3, dat_num4);
           printf(" jg_doc.paint(); \n"); // flush paint
           fflush( stdout );

        }

	ungetlex();
}


void keyHTMLJS_KOTAKISI ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0;

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;
	do{

	  getlex();
      //  printf(" DEBUG: HTMLJS_KOTAKISI lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    
            case TYPE_ARRAY:
              /* printf("write array\n"); */

              if(strlen(lex.detail.array_str) > 0) {
                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atoi (valdat.array_idx);
                } else {
                   /* printf("show NOT digit\n"); */
                   /* Read index param */
                   tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

	        valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                sprintf(valdat2.array_idx, "%d", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  if(n == 0)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 1)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:

                if(n == 0)                           /* ord x start */
                  dat_num = lex.detail.num;
                if(n == 1)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 2)                           /* ord x end   */
                  dat_num3 = lex.detail.num;
                if(n == 3)                           /* ord y end   */
                  dat_num4 = lex.detail.num;

	      break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                // printf("HTMLJS_KOTAKISI class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.datatype == 0) {
                if(n == 0)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 1)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 2)                           /* ord x end   */
                  dat_num3 = valdat.val;
                if(n == 3)                           /* ord y end   */
                  dat_num4 = valdat.val;

              } else {
                 Error("kode perintah HTMLJS_KOTAKISI salah");
              }

	      break;

	    default:
	      Error("kode perintah HTMLJS_KOTAKISI salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 4) {
           Error("parameter kode perintah HTMLJS_KOTAKISI salah");
        } else {
           /*
           printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           */

           printf(" jg_doc.fillRect(%d,%d,%d,%d); \n", dat_num, dat_num2, dat_num3, dat_num4);
           printf(" jg_doc.paint(); \n"); // flush paint
           fflush( stdout );

        }

	ungetlex();

}

void keyHTMLJS_LINGKARAN ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0;

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;
	do{

	  getlex();
      // printf(" DEBUG: HTMLJS_LINGKARAN lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    
            case TYPE_ARRAY:
              /* printf("write array\n"); */

              if(strlen(lex.detail.array_str) > 0) {
                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atoi (valdat.array_idx);
                } else {
                   /* printf("show NOT digit\n"); */
                   /* Read index param */
                   tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

	        valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                sprintf(valdat2.array_idx, "%d", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  if(n == 0)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 1)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:

                if(n == 0)                           /* ord x start */
                  dat_num = lex.detail.num;
                if(n == 1)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 2)                           /* r1 - x   */
                  dat_num3 = lex.detail.num;
                if(n == 3)                           /* r2 - y   */
                  dat_num4 = lex.detail.num;

	      break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                // printf("HTMLJS_LINGKARAN class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.datatype == 0) {
                if(n == 0)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 1)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 2)                           /* r1 x   */
                  dat_num3 = valdat.val;
                if(n == 3)                           /* r2 y   */
                  dat_num4 = valdat.val;

              } else {
                 Error("kode perintah HTMLJS_LINGKARAN salah");
              }

	      break;

	    default:
	      Error("kode perintah HTMLJS_LINGKARAN salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 4) {
           Error("parameter kode perintah HTMLJS_LINGKARAN salah");
        } else {
           /*
           printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           */

           printf(" jg_doc.drawEllipse(%d,%d,%d,%d); \n", dat_num, dat_num2, dat_num3, dat_num4);
           printf(" jg_doc.paint(); \n"); // flush paint
           fflush( stdout );

        }

	ungetlex();

}


void keyHTMLJS_LINGKARANISI ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0;

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;
	do{

	  getlex();
      // printf(" DEBUG: HTMLJS_LINGKARANISI lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    
            case TYPE_ARRAY:
              /* printf("write array\n"); */

              if(strlen(lex.detail.array_str) > 0) {
                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atoi (valdat.array_idx);
                } else {
                   /* printf("show NOT digit\n"); */
                   /* Read index param */
                   tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

	        valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                sprintf(valdat2.array_idx, "%d", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  if(n == 0)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 1)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:

                if(n == 0)                           /* ord x start */
                  dat_num = lex.detail.num;
                if(n == 1)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 2)                           /* r1 - x   */
                  dat_num3 = lex.detail.num;
                if(n == 3)                           /* r2 - y   */
                  dat_num4 = lex.detail.num;

	      break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                // printf("HTMLJS_LINGKARANISI class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.datatype == 0) {
                if(n == 0)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 1)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 2)                           /* r1 x   */
                  dat_num3 = valdat.val;
                if(n == 3)                           /* r2 y   */
                  dat_num4 = valdat.val;

              } else {
                 Error("kode perintah HTMLJS_LINGKARANISI salah");
              }

	      break;

	    default:
	      Error("kode perintah HTMLJS_LINGKARANISI salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 4) {
           Error("parameter kode perintah HTMLJS_LINGKARANISI salah");
        } else {
           /*
           printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           */

           printf(" jg_doc.fillEllipse(%d,%d,%d,%d); \n", dat_num, dat_num2, dat_num3, dat_num4);
           printf(" jg_doc.paint(); \n"); // flush paint
           fflush( stdout );

        }

	ungetlex();

}


void keyHTMLJS_TULIS ()
{

  char ident[MAX_IDENT_LEN];

  char logMsg[MAX_STRING_LEN * 2],
       tmpMsg[MAX_STRING_LEN * 2];

  int  n=0, i=0, j=0;
  int  dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  

  int    idx=0, idx2=0;                           // array index

  char keep_string[MAX_STRING_LEN];

  char tmpstr[MAX_STRING_LEN];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  memset(&tmp_str, '\0', sizeof(tmp_str));
  
  memset(&ident, '\0', sizeof(ident));
  memset(&tmpMsg, '\0', sizeof(tmpMsg));
  memset(&logMsg, '\0', sizeof(logMsg));

  memset(&keep_string, '\0', sizeof(keep_string));
  memset(&tmpstr, '\0', sizeof(tmpstr));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;
	do{

	  getlex();
      //printf(" DEBUG: HTMLJS_TULIS lex.type %d\n", lex.type);

	  switch( lex.type )
	    {

	    case TYPE_STR:
             if(n == 0) {
               strcpy(dat_a, lex.detail.string);
             }
              break;
	    
            case TYPE_ARRAY:
              /* printf("write array\n"); */

              if(strlen(lex.detail.array_str) > 0) {
                strcpy(valdat.array_str, lex.detail.array_str);
                getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
                getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

                if(isdigit(valdat.array_idx[0])) {
                   /* printf("show digit\n"); */
                   idx = atoi (valdat.array_idx);
                } else {
                   /* printf("show NOT digit\n"); */
                   /* Read index param */
                   tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

	        valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                //itoa(idx, valdat2.array_idx, 10);
                sprintf(valdat2.array_idx, "%d", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(valdat2.datatype == 6) {
                  if(valdat2.array_i == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  if(n == 1)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);

                } else if (valdat2.datatype == 8) {
                  if(valdat2.array_s == '\0')
                    Error("ukuran Untaian belum terdefinisi: kata");
                  if(n == 0) {
                    if(valdat2.array_s != '\0') {

			        memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				    memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				    strcpy(TmpStrBox.var.array_name, valdat2.array_name);
                    renban = valdat2.array_s;

				    // printf("TULIS get stackid: %d, idx: %d\n", renban, idx);

				    if(renban < 0) {
                      printf("variabel untaian tidak ditemukan\n");
				    } else {
                      TmpStrBox.str.stackid = renban;
                      TmpStrBox.str.idx = idx;

					  strarryPos = string_findData(TmpStrBox.str);
					  if(strarryPos < 0) {
    					// printf("\n! nilai untaian kata tidak ditemukan");
					  } else {
                        TmpStrBox.str = string_getElement(strarryPos);
                        strcpy(dat_a, TmpStrBox.str.mystring);
					  }

				    }


					}
                  }
                } else if (valdat2.datatype == 10) {
                  if(n == 0) {
                    if(valdat2.long_str != NULL) {
                      strcpy(dat_a, valdat2.long_str[idx]);
                    }
                  }
                }

              }

              break;

	    case TYPE_NUM:

                if(n == 1)                           /* ord x start */
                  dat_num = lex.detail.num;
                if(n == 2)                           /* ord y start */
                  dat_num2 = lex.detail.num;

	      break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                // printf("HTMLJS_GARIS class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.datatype == 0) {
                if(n == 1)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 2)                           /* ord y start */
                  dat_num2 = valdat.val;

              } else if(valdat.datatype == 3 || strlen(valdat.str) > 0) {
                if(n == 0) {
                  strcpy(dat_a, valdat.str);
                }

              } else {
                 Error("kode perintah HTMLJS_TULIS salah");
              }

	      break;

	    default:
	      Error("kode perintah HTMLJS_TULIS salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 3) {
           Error("parameter kode perintah HTMLJS_TULIS salah");
        } else {
           /*
           printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           */

           printf(" jg_doc.drawString(\"%s\",%d,%d); \n", dat_a, dat_num, dat_num2);
           printf(" jg_doc.paint(); \n"); // flush paint
           fflush( stdout );

        }

	ungetlex();

}



void keySEDIA_WEBSTYLE ()
{
  char tmpMsg[MAX_STRING_LEN];

  int  n=0, i=0, j=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  memset(&tmp_str, '\0', sizeof(tmp_str));
  
  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;
	do{

          memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 0) {
                strcpy(dat_a, lex.detail.string );
              } else if(n == 1) {
                strcpy(dat_b, lex.detail.string );
              } 

	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 0 || strlen(valdat.str) > 0) {
                sprintf(tmpMsg, "%s" , valdat.str );

                if(n == 0) {
                  strcpy(dat_a, tmpMsg );
                } else if(n == 1) {
                  strcpy(dat_b, tmpMsg );
                } 

              }

	      break;

	    default:
	      Error("bentuk perintah SEDIA_WEBSTYLE salah");
	    }

          n++;

	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


        if(n != 2) {
          Error("parameter SEDIA_WEBSTYLE tidak lengkap");
        } else {

          createWebStyle(dat_a, dat_b);

        }

        fflush( stdout );
        ungetlex();

}

void keyHTML_AWAL ()
{
  VAL_LABEL valdat, valdat2, tmpdat;
  

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  
  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

	  getlex();
	  switch( lex.type )
	    {
	    case TYPE_STR:
              printf("Content-type: text/html\n\n");
              printf("<html> \n");
              printf("<head> \n");
	      printf("<title>%s</title> \n", lex.detail.string );
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                printf("Content-type: text/html\n\n");
                printf("<html> \n");
                printf("<head> \n");
                printf("<title>%s</title> \n", valdat.str );
              }

              break;

	    default:
	      Error("kode perintah HTML_AWAL salah");
	    }

	  getlex();
	  fflush( stdout );
	  ungetlex();

}


void keyHTML_STYLE ()
{
  VAL_LABEL valdat, valdat2, tmpdat;
  

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  
  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

	  getlex();
	  switch( lex.type )
	    {
	    case TYPE_STR:
              printf("<link rel='stylesheet' type='text/css' href='%s/baikstyle.css'> \n", lex.detail.string);
              printf("<style type='text/css'> \n");
              printf("</style> \n");
              printf("</head> \n");
              printf("<body> \n");
              fflush( stdout );

	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.datatype == 0 || strlen(valdat.str) > 0) {
                printf("<link rel='stylesheet' type='text/css' href='%s/baikstyle.css'> \n", valdat.str);
                printf("<style type='text/css'> \n");
                printf("</style> \n");
                printf("</head> \n");
                printf("<body> \n");
                fflush( stdout );
              }

              break;

	    default:
	      Error("kode perintah HTML_STYLE salah");
	    }

	  getlex();
	  fflush( stdout );
	  ungetlex();

}


void keyHTML_MENU ()
{
  char tmpMsg[MAX_STRING_LEN];

  int  n=0, i=0, j=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];
  char   dat_c[MAX_STRING_LEN];

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  memset(&dat_c, '\0', sizeof(dat_c));
  memset(&tmp_str, '\0', sizeof(tmp_str));
  
  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;

	do{

          memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 0) {
                strcpy(dat_a, lex.detail.string );
              } else if(n == 1) {
                strcpy(dat_b, lex.detail.string );
              } else if(n == 2) {
                strcpy(dat_c, lex.detail.string );
              } 

	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                sprintf(tmpMsg, "%s" , valdat.str );

                if(n == 0) {
                  strcpy(dat_a, tmpMsg );
                } else if(n == 1) {
                  strcpy(dat_b, tmpMsg );
                } else if(n == 2) {
                  strcpy(dat_c, tmpMsg );
                } 

              }

	      break;

	    default:
	      Error("bentuk perintah HTML_MENU salah");
	    }

          n++;

	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


        if(n != 3) {
          Error("parameter HTML_MENU tidak lengkap");
        } else {

          printf("<div class='en' lang='en'> \n");
          printf("<a href=%s>%s</a> \n",dat_c, dat_a );
          printf("</div> \n");
          printf("<div class='jp'>%s</div> \n", dat_b);

        }

        fflush( stdout );
        ungetlex();

}

void keyHTML_HAKCIPTA ()
{
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  
  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

	  getlex();
	  switch( lex.type )
	    {
	    case TYPE_STR:
	      printf("<div class='sub'>%s </div> <BR>\n", lex.detail.string );
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                printf("<div class='sub'>%s </div> <BR>\n", valdat.str );
              }

              break;

	    default:
	      Error("kode perintah HTML_HAKCIPTA salah");
	    }

	  getlex();
	  fflush( stdout );
	  ungetlex();

}

void keyISIWEB_TITEL ()
{
  char tmpMsg[MAX_STRING_LEN];

  int  n=0, i=0, j=0;

  char   dat_a[MAX_STRING_LEN];
  char   dat_b[MAX_STRING_LEN];
  char   dat_c[MAX_STRING_LEN];

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;

  int    idx=0, idx2=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&dat_b, '\0', sizeof(dat_b));
  memset(&dat_c, '\0', sizeof(dat_c));
  memset(&tmp_str, '\0', sizeof(tmp_str));
  
  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;
	do{

          memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 0) {
                strcpy(dat_a, lex.detail.string );
              } else if(n == 1) {
                strcpy(dat_b, lex.detail.string );
              } else if(n == 2) {
                strcpy(dat_c, lex.detail.string );
              } 

	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                sprintf(tmpMsg, "%s" , valdat.str );

                if(n == 0) {
                  strcpy(dat_a, tmpMsg );
                } else if(n == 1) {
                  strcpy(dat_b, tmpMsg );
                } else if(n == 2) {
                  strcpy(dat_c, tmpMsg );
                } 

              }

	      break;

	    default:
	      Error("bentuk perintah ISIWEB_TITEL salah");
	    }

          n++;

	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


        if(n != 3) {
          Error("parameter ISIWEB_TITEL tidak lengkap");
        } else {

          printf("<div class='title'> \n");
          printf("<h1 lang='en'>%s</h1> \n", dat_a );
          printf("<div>%s</div> \n", dat_b);
          printf("<p>%s</p> \n", dat_c);
          printf("</div> \n");
          printf("<BR> \n");
          printf("<!-- contents --> \n");
          printf("<div class='con'> \n");

        }

        fflush( stdout );
        ungetlex();

}


