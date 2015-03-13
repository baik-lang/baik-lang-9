// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

/* ----------------------------------------------------------- */
/* GD Graphic Handle                                             */
/* ----------------------------------------------------------- */
void SimpanGambarPng(gdImagePtr im, char filename[1024]);
void SimpanGambarJpg(gdImagePtr im, char filename[1024]);

void keyGAMBAR_GARIS ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0, dat_num5=0;

  gdImagePtr dat_img=NULL;

  long    idx=0;                           // array index

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
      // printf(" DEBUG: GAMBAR_GARIS lex.type %d\n", lex.type);

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
                   idx = atol (valdat.array_idx);
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

                  if(n == 1)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 4)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);
                  if(n == 5)                           /* int color   */
                    dat_num5 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:

                if(n == 1)                           /* ord x start */
                  dat_num = lex.detail.num;
                if(n == 2)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = lex.detail.num;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = lex.detail.num;
                if(n == 5)                           /* int color   */
                  dat_num5 = lex.detail.num;

	      break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                // printf("GAMBARGARIS class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {
                valdat = ValLabel(lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              //printf("\n datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.datatype == 0) {
                if(n == 1)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 2)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = valdat.val;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = valdat.val;
                if(n == 5)                           /* int color   */
                  dat_num5 = valdat.val;
              } else if(valdat.datatype == 20) {    /* gd img      */
                if(n == 0)
                  dat_img = valdat.gdimg;
              } else {
                 Error("kode perintah GAMBARGARIS salah");
              }

	      break;

	    default:
	      Error("kode perintah GAMBARGARIS salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 6) {
           Error("parameter kode perintah GAMBARGARIS salah");
        } else {
           /*
           printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           printf("color: %d\n", dat_num5);
           */

           gdImageLine(dat_img, dat_num, dat_num2, dat_num3, dat_num4, dat_num5); 

        }

	ungetlex();

}

void keyGAMBAR_GARIS_PUTUS ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0, dat_num5=0;

  gdImagePtr dat_img=NULL;

  long    idx=0;                           // array index

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
          // if(isDEBUG == 1) printf(" DEBUG: GAMBAR_GARIS_PUTUS lex.type %d\n", lex.type);

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
                   idx = atol (valdat.array_idx);
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

                  if(n == 1)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 4)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);
                  if(n == 5)                           /* int color   */
                    dat_num5 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:

                if(n == 1)                           /* ord x start */
                  dat_num = lex.detail.num;
                if(n == 2)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = lex.detail.num;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = lex.detail.num;
                if(n == 5)                           /* int color   */
                  dat_num5 = lex.detail.num;

	      break;


	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {
                valdat = ValLabel( lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              //printf("\n datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.datatype == 0) {
                if(n == 1)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 2)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = valdat.val;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = valdat.val;
                if(n == 5)                           /* int color   */
                  dat_num5 = valdat.val;
              } else if(valdat.datatype == 20) {    /* gd img      */
                if(n == 0)
                  dat_img = valdat.gdimg;
              } else {
                 Error("kode perintah GAMBARGARISPUTUS salah");
              }

	      break;

	    default:
	      Error("kode perintah GAMBARGARISPUTUS salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 6) {
           Error("parameter kode perintah GAMBARGARISPUTUS salah");
        } else {
           /* printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           printf("color: %d\n", dat_num5); */

           gdImageDashedLine(dat_img, dat_num, dat_num2, dat_num3, dat_num4, dat_num5); 

        }

	ungetlex();

}

void keyGAMBAR_KOTAK ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0, dat_num5=0;

  gdImagePtr dat_img=NULL;

  long    idx=0;                           // array index

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
          // if(isDEBUG == 1) printf(" DEBUG: GAMBAR_KOTAK lex.type %d\n", lex.type);

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
                   idx = atol (valdat.array_idx);
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

                  if(n == 1)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 4)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);
                  if(n == 5)                           /* int color   */
                    dat_num5 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:

                if(n == 1)                           /* ord x start */
                  dat_num = lex.detail.num;
                if(n == 2)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = lex.detail.num;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = lex.detail.num;
                if(n == 5)                           /* int color   */
                  dat_num5 = lex.detail.num;

	      break;


	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                valdat = ValLabel(lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              }

              //printf("\n datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.datatype == 0) {
                if(n == 1)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 2)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = valdat.val;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = valdat.val;
                if(n == 5)                           /* int color   */
                  dat_num5 = valdat.val;
              } else if(valdat.datatype == 20) {    /* gd img      */
                if(n == 0)
                  dat_img = valdat.gdimg;
              } else {
                 Error("kode perintah GAMBARKOTAK salah");
              }

	      break;

	    default:
	      Error("kode perintah GAMBARKOTAK salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 6) {
           Error("parameter kode perintah GAMBARKOTAK salah");
        } else {
           /* printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           printf("color: %d\n", dat_num5); */

           gdImageRectangle(dat_img, dat_num, dat_num2, dat_num3, dat_num4, dat_num5); 

        }

	ungetlex();

}

void keyGAMBAR_KOTAK_ISI ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0, dat_num5=0;

  gdImagePtr dat_img=NULL;

  long    idx=0;                           // array index

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
          // if(isDEBUG == 1) printf(" DEBUG: GAMBAR_KOTAK_ISI lex.type %d\n", lex.type);

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
                   idx = atol (valdat.array_idx);
                } else {
                   /* printf("show NOT digit\n"); */
                   /* Read index param */
                   tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

                /* データ読み込み */
	        valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

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
                  if(n == 3)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 4)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);
                  if(n == 5)                           /* int color   */
                    dat_num5 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:

                if(n == 1)                           /* ord x start */
                  dat_num = lex.detail.num;
                if(n == 2)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = lex.detail.num;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = lex.detail.num;
                if(n == 5)                           /* int color   */
                  dat_num5 = lex.detail.num;

	      break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {
                valdat = ValLabel( lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              //printf("\n datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.datatype == 0) {
                if(n == 1)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 2)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = valdat.val;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = valdat.val;
                if(n == 5)                           /* int color   */
                  dat_num5 = valdat.val;
              } else if(valdat.datatype == 20) {    /* gd img      */
                if(n == 0)
                  dat_img = valdat.gdimg;
              } else {
                 Error("kode perintah GAMBARKOTAKISI salah");
              }

	      break;

	    default:
	      Error("kode perintah GAMBARKOTAKISI salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 6) {
           Error("parameter kode perintah GAMBARKOTAKISI salah");
        } else {
           /*
           printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           printf("color: %d\n", dat_num5);
           */

           gdImageFilledRectangle(dat_img, dat_num, dat_num2, dat_num3, dat_num4, dat_num5); 

        }

	ungetlex();

}


void keyGAMBAR_LINGKARAN ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0, dat_num5=0;
  int    dat_num6=0, dat_num7=0;

  gdImagePtr dat_img=NULL;

  long    idx=0;                           // array index

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
          // if(isDEBUG == 1) printf(" DEBUG: GAMBAR_LINGKARAN lex.type %d\n", lex.type);

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
                   idx = atol (valdat.array_idx);
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

                  if(n == 1)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 4)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);
                  if(n == 5)                           /* degree start 0 */
                    dat_num5 = get_int_array(valdat2, idx);
                  if(n == 6)                           /* degree end   360 */
                    dat_num6 = get_int_array(valdat2, idx);
                  if(n == 7)                           /* int color   */
                    dat_num7 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:
                if(n == 1)                           /* ord x start */
                  dat_num  = lex.detail.num;
                if(n == 2)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = lex.detail.num;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = lex.detail.num;
                if(n == 5)                           /* deg start   */
                  dat_num5 = lex.detail.num;
                if(n == 6)                           /* deg end   */
                  dat_num6 = lex.detail.num;
                if(n == 7)                           /* int color   */
                  dat_num7 = lex.detail.num;
	      break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                valdat = ValLabel( lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              }

              //printf("\n datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.datatype == 0) {
                if(n == 1)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 2)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = valdat.val;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = valdat.val;
                if(n == 5)                           /* deg start   */
                  dat_num5 = valdat.val;
                if(n == 6)                           /* deg end   */
                  dat_num6 = valdat.val;
                if(n == 7)                           /* int color   */
                  dat_num7 = valdat.val;
              } else if(valdat.datatype == 20) {    /* gd img      */
                if(n == 0)
                  dat_img = valdat.gdimg;
              } else {
                 Error("kode perintah GAMBARLINGKARAN salah");
              }

	      break;

	    default:
	      Error("kode perintah GAMBARLINGKARAN salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 8) {
           Error("parameter kode perintah GAMBARLINGKARAN salah");
        } else {
           /* printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           printf("e: %d\n", dat_num5); */

           if(dat_num6 > 360)
             dat_num6 = dat_num6 % 360;

           gdImageArc(dat_img, dat_num, dat_num2, dat_num3, dat_num4, 
                      dat_num5, dat_num6,
                      dat_num7); 

        }

	ungetlex();

}

void keyGAMBAR_LINGKARAN_ISI ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0, dat_num5=0;
  int    dat_num6=0, dat_num7=0;

  gdImagePtr dat_img=NULL;

  long    idx=0;                           // array index

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
          // if(isDEBUG == 1) printf(" DEBUG: GAMBAR_LINGKARAN_ISI lex.type %d\n", lex.type);

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
                   idx = atol (valdat.array_idx);
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

                  if(n == 1)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 2)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord x end   */
                    dat_num3 = get_int_array(valdat2, idx);
                  if(n == 4)                           /* ord y end   */
                    dat_num4 = get_int_array(valdat2, idx);
                  if(n == 5)                           /* degree start 0 */
                    dat_num5 = get_int_array(valdat2, idx);
                  if(n == 6)                           /* degree end   360 */
                    dat_num6 = get_int_array(valdat2, idx);
                  if(n == 7)                           /* int color   */
                    dat_num7 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_NUM:
                if(n == 1)                           /* ord x start */
                  dat_num  = lex.detail.num;
                if(n == 2)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = lex.detail.num;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = lex.detail.num;
                if(n == 5)                           /* deg start   */
                  dat_num5 = lex.detail.num;
                if(n == 6)                           /* deg end   */
                  dat_num6 = lex.detail.num;
                if(n == 7)                           /* int color   */
                  dat_num7 = lex.detail.num;
	      break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {
                valdat = ValLabel( lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              //printf("\n datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.datatype == 0) {
                if(n == 1)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 2)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 3)                           /* ord x end   */
                  dat_num3 = valdat.val;
                if(n == 4)                           /* ord y end   */
                  dat_num4 = valdat.val;
                if(n == 5)                           /* deg start   */
                  dat_num5 = valdat.val;
                if(n == 6)                           /* deg end   */
                  dat_num6 = valdat.val;
                if(n == 7)                           /* int color   */
                  dat_num7 = valdat.val;
              } else if(valdat.datatype == 20) {    /* gd img      */
                if(n == 0)
                  dat_img = valdat.gdimg;
              } else {
                 Error("kode perintah GAMBARLINGKARANISI salah");
              }

	      break;

	    default:
	      Error("kode perintah GAMBARLINGKARANISI salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 8) {
           Error("parameter kode perintah GAMBARLINGKARANISI salah");
        } else {
           /* printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("c: %d\n", dat_num3);
           printf("d: %d\n", dat_num4);
           printf("e: %d\n", dat_num5); */

           if(dat_num6 > 360)
             dat_num6 = dat_num6 % 360;

           gdImageFilledArc(dat_img, dat_num, dat_num2, dat_num3, dat_num4, 
                      dat_num5, dat_num6,
                      dat_num7,
                      gdArc); 

        }

	ungetlex();

}

void keySIMPAN_GAMBAR_PNG ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0, dat_num5=0;

  char   dat_a[MAX_STRING_LEN];

  gdImagePtr dat_img=NULL;  // GD

  #ifdef USE_GTK2
  GdkPixbuf  *dat_pix=NULL; // GTK
  #endif

  int pic_type = 0;    // 0 -> GD , 1 -> GTK

  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;
	do{

	  getlex();
          // if(isDEBUG == 1) printf(" DEBUG: SIMPAN_GAMBAR_PNG lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    
	    case TYPE_STR:
              if(n == 1) {                        /* png filename */
                if(lex.detail.string  != '\0' && strlen(lex.detail.string) > 0) {
                  sprintf(dat_a, "%s", lex.detail.string );
                } else {
                  Error("kode perintah SIMPANGAMBARPNG salah : nama File");
                }
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
                   idx = atol (valdat.array_idx);
                } else {
                   /* printf("show NOT digit\n"); */
                   /* Read index param */
                   tmpdat = ValLabel( valdat.array_idx, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

                   if(tmpdat.datatype==0)
                     idx = tmpdat.val;
                   else
                      Error("Untaian salah masukan");
                }

                /* データ読み込み */
	        valdat2 = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

                sprintf(valdat2.array_idx, "%d", idx);

                if(idx < 0 || idx > (valdat2.array_max-1))
                  Error("ukuran Untaian tidak sesuai kapasitas");

                if(valdat2.datatype == 8  && valdat2.array_s != '\0') {
                  if(valdat2.array_s == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				  memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				  strcpy(TmpStrBox.var.array_name, valdat2.array_name);
                  renban = valdat2.array_s;

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

					}

				  }

				  if(n == 1) {                       /* png filename */
                    sprintf(dat_a, "%s" , TmpStrBox.str.mystring );

				  }

                } else if (valdat2.datatype == 10) {
                  if(n == 1)                        /* png filename */
                    sprintf(dat_a, "%s", valdat2.long_str[idx]);
                }

              }

              break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

               valdat = ValLabel( lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

			  }

              //printf("\n datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.datatype == 3) {
                if(n == 1) {                        /* png filename */
                  if(strlen(valdat.str) > 0) {
                    sprintf(dat_a, "%s", valdat.str);
                  } else {
                    Error("kode perintah SIMPANGAMBARPNG salah : nama File");
                  }
                }
              } else if(valdat.datatype == 20) {    /* gd img      */
				  if(n == 0) {
                    dat_img  = valdat.gdimg;
					pic_type = 0;
				  }
              #ifdef USE_GTK2
              } else if(valdat.datatype == 46) {    /* gtk pixbuf img      */
				  if(n == 0) {
				    dat_pix = valdat.pixbuf[0];
					pic_type = 1;
				  }
              #endif
              } else {
                 Error("kode perintah SIMPANGAMBARPNG salah");
              }

	      break;

	    default:
	      Error("kode perintah SIMPANGAMBARPNG salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 2) {
           Error("parameter kode perintah SIMPANGAMBARPNG salah");
        } else {
           /* printf("png file: %s\n", dat_a); */
              if(pic_type == 0) {
	        if(dat_img != NULL) {
                  SimpanGambarPng(dat_img, dat_a);
                }
	      } else if(pic_type == 1) {
                #ifdef USE_GTK2
                gdk_pixbuf_save(dat_pix, dat_a, "png", NULL, NULL);
                #endif
              }
        }

	ungetlex();

}


void keySIMPAN_GAMBAR_JPG ()
{

  int  n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0, dat_num5=0;

  char   dat_a[MAX_STRING_LEN];
  gdImagePtr dat_img = NULL;

  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;
	do{

	  getlex();
          // if(isDEBUG == 1) printf(" DEBUG: SIMPAN_GAMBAR_JPG lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    
	    case TYPE_STR:
              if(n == 1) {                        /* png filename */
                if(lex.detail.string  != '\0' && strlen(lex.detail.string) > 0) {
                  sprintf(dat_a, "%s", lex.detail.string );
                } else {
                  Error("kode perintah SIMPANGAMBARJPG salah : nama File");
                }
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
                   idx = atol (valdat.array_idx);
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

                if(valdat2.datatype == 8  && valdat2.array_s != '\0') {
                  if(valdat2.array_s == '\0')
                    Error("ukuran Untaian belum terdefinisi: int");

                  memset(&TmpStrBox.var.array_name, '\0', sizeof(TmpStrBox.var.array_name));
				  memset(&TmpStrBox.str.mystring, '\0', sizeof(TmpStrBox.str.mystring));

				  strcpy(TmpStrBox.var.array_name, valdat2.array_name);
                  renban = valdat2.array_s;

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

					}

				  }

				  if(n == 1) {                       /* png filename */
                    sprintf(dat_a, "%s" , TmpStrBox.str.mystring );

				  }

                } else if (valdat2.datatype == 10) {
                  if(n == 1)                        /* png filename */
                    sprintf(dat_a, "%s", valdat2.long_str[idx]);
                }

              }

              break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {
                valdat = ValLabel( lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
              }

              //printf("\n datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.datatype == 3) {
                if(n == 1) {                        /* png filename */
                  if(strlen(valdat.str) > 0) {
                    sprintf(dat_a, "%s", valdat.str);
                  } else {
                    Error("kode perintah SIMPANGAMBARJPG salah : nama File");
                  }
                }
              } else if(valdat.datatype == 20) {    /* gd img      */
                if(n == 0)
                  dat_img = valdat.gdimg;
              } else {
                 Error("kode perintah SIMPANGAMBARJPG salah");
              }

	      break;

	    default:
	      Error("kode perintah SIMPANGAMBARJPG salah");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 2) {
           Error("parameter kode perintah SIMPANGAMBARJPG salah");
        } else {
           /* printf("png file: %s\n", dat_a); */

           SimpanGambarJpg(dat_img, dat_a);
        }

	ungetlex();

}

void keyGAMBAR_HURUF ()
{
  char   tmpMsg[MAX_STRING_LEN * 2];
  int    n=0, i=0, j=0;

  char   tmp_str[MAX_STRING_LEN];
  VAL_LABEL valdat, valdat2, tmpdat;
  
  int    dat_num=0, dat_num2=0, dat_num3=0, dat_num4=0, dat_num5=0;

  char   dat_a[MAX_STRING_LEN];
  gdImagePtr dat_img=NULL;
  gdFontPtr  dat_font=NULL;

  long    idx=0;                           // array index

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&dat_a, '\0', sizeof(dat_a));
  memset(&tmp_str, '\0', sizeof(tmp_str));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

    n = 0;
	do{

	  getlex();
          // if(isDEBUG == 1) printf(" DEBUG: GAMBAR_HURUF lex.type %d\n", lex.type);

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
                   idx = atol (valdat.array_idx);
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

                  if(n == 2)                           /* ord x start */
                    dat_num = get_int_array(valdat2, idx);
                  if(n == 3)                           /* ord y start */
                    dat_num2 = get_int_array(valdat2, idx);
                  if(n == 5)                           /* color   */
                    dat_num3 = get_int_array(valdat2, idx);

                } 

              }

              break;

	    case TYPE_STR:
              strcpy(tmpMsg, lex.detail.string);

              break;

	    case TYPE_NUM:
                if(n == 2)                           /* ord x start */
                  dat_num  = lex.detail.num;
                if(n == 3)                           /* ord y start */
                  dat_num2 = lex.detail.num;
                if(n == 5)                           /* int color   */
                  dat_num3 = lex.detail.num;

              break;

	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                valdat = ValLabel(lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              }

              //printf("\n datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(valdat.datatype == 0) {
                if(n == 2)                           /* ord x start */
                  dat_num = valdat.val;
                if(n == 3)                           /* ord y start */
                  dat_num2 = valdat.val;
                if(n == 5)                           /* int color   */
                  dat_num3 = valdat.val;
              } else if(valdat.datatype == 3) {      /* string      */
                if(n == 4)
                  strcpy(tmpMsg, valdat.str);
              } else if(valdat.datatype == 20) {     /* gd img      */
                if(n == 0)
                  dat_img = valdat.gdimg;
              } else if(valdat.datatype == 22) {     /* gd font      */
                if(n == 1)
                  dat_font = valdat.gdfont;
              } else {
                 Error("kode perintah GAMBARHURUF salah 0");
              }

	      break;

	    default:
	      Error("kode perintah GAMBARHURUF salah 1");
	    }

          n++;
	  getlex();
	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',' );

        if(n != 6) {
           Error("parameter kode perintah GAMBARHURUF salah");
        } else {
           /* printf("a: %d\n", dat_num);
           printf("b: %d\n", dat_num2);
           printf("msg: %s\n", tmpMsg);
           printf("c: %d\n", dat_num3); */

           gdImageString(dat_img, dat_font, dat_num, dat_num2, tmpMsg, dat_num3); 

        }

	ungetlex();

}

void keyHAPUS_GAMBAR ()
{
  char   tmpMsg[MAX_STRING_LEN * 2];

  VAL_LABEL valdat, tmpdat;

  // var list for class params

  char    class_tmpvar[MAX_STRING_LEN];

  // printf("init valdats ...\n");
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));

  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  	getlex();
    strcpy(tmpMsg, lex.detail.ident);

	if( lex.type == TYPE_IDENT ){
           if(currentClass != NULL && strlen(currentClass) > 0) {
             sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
             //printf("construct class var: %s\n", class_tmpvar);
             valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
           } else {
             valdat = ValLabel( lex.detail.string, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );
           }

           if(valdat.datatype == 20) {    /* gd img      */
             // printf("hapus img\n");
             gdImageDestroy(valdat.gdimg);

             memset(&tmpdat,'\0',sizeof(tmpdat));
             ValLabel( tmpMsg , sub_deep, tmpdat, VAL_FLAG_SEARCH_W );
           } else {
             Error("kode perintah HAPUSGAMBAR salah");
           }
	}

	else
	  Error("kode perintah HAPUSGAMBAR salah");

}


/* ****************************************************** */
/* GD Graphic handle */
/* ****************************************************** */

void SimpanGambarPng(gdImagePtr im, char filename[1024] ) {
  FILE *out=NULL;
  int size=0;
  char *data=NULL;

  out = fopen(filename, "wb");
  if(out == NULL) {
    Error("Salah: Tidak bisa buka File");
  }

  data = (char *)gdImagePngPtr(im, &size);

  if (data) {
    if (fwrite(data, 1, size, out) != size) {
      Error("Salah: Tidak bisa simpan ke File");
    }
  }

  if(out != NULL) {
    fclose(out);
  }

  if(data != NULL) {
    gdFree(data);
  }

}

void SimpanGambarJpg(gdImagePtr im, char filename[1024] ) {
  FILE *out=NULL;
  int size=0;
  char *data=NULL;

  out = fopen(filename, "wb");
  if(out == NULL) {
    Error("Salah: Tidak bisa buka File");
  }

  data = (char *)gdImageJpegPtr(im, &size, -1);

  if (data) {
    if (fwrite(data, 1, size, out) != size) {
      Error("Salah: Tidak bisa simpan ke File");
    }
  }

  if(out != NULL) {
    fclose(out);
  }

  if(data != NULL) {
    gdFree(data);
  }
}



