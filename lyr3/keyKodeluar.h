// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyKodeluar ( int progType , char currentClass[MAX_STRING_LEN])
{
  int  n=0, i=0, j=0;

  VAL_LABEL valdat, valdat2, tmpdat, valdat0;
  
  int    idx=0, idx2=0;                           // array index

  int    isArrDummy=0;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&valdat2, '\0', sizeof(valdat2));
  memset(&valdat0, '\0', sizeof(valdat0));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

	  getlex();
	  switch( lex.type )
	    {
	    case TYPE_STR:

              strcpy(inc_file, lex.detail.string);
              // printf("Code luar %s\n", inc_file);

              if( stat( inc_file, &inc_st ) != 0 ){
                fprintf( stderr, "Kode Luar tidak ditemukan: %s\n",  inc_file);
                exit( -1 );
              }

              if( ( inc_fp = fopen(inc_file, "r") ) == NULL ) {
                fprintf( stderr, "tidak bisa buka Kode Luar %s\n", inc_file );
                exit( -1 );
              }

              inc_source = (char *)calloc(inc_st.st_size + 9, sizeof(char));
              if( inc_source == NULL ){
                fprintf( stderr, "calloc error\n" );
                exit( -1 );
              }

              fread( inc_source, 1, inc_st.st_size, inc_fp );

              fclose( inc_fp );

              // and implicit code for reading termination of include file
              i=0; j=0;
              while(inc_source[i] != '\0') {

                if((inc_source[i] == 'R' || inc_source[i] == 'r') &&
                   (inc_source[i-1] == 'A' || inc_source[i-1] == 'a') &&
                   (inc_source[i-2] == 'U' || inc_source[i-2] == 'u') &&
                   (inc_source[i-3] == 'L' || inc_source[i-3] == 'l' ) &&
                   inc_source[i-4] == '_' &&
                   (inc_source[i-5] == 'E' || inc_source[i-5] == 'e' ) &&
                   (inc_source[i-6] == 'D' || inc_source[i-6] == 'd' ) &&
                   (inc_source[i-7] == 'O' || inc_source[i-7] == 'o' ) &&
                   (inc_source[i-8] == 'K' || inc_source[i-8] == 'k' ) &&
                   inc_source[i-9] == '_'
                  ) {

                  j = i+2;
                }

                i++;
              }

              inc_source[j+1] = ' ';  // 
              inc_source[j++] = 'E';  // E
              inc_source[j++] = 'N';  // N
              inc_source[j++] = 'D';  // D
              inc_source[j++] = '_';  // _
              inc_source[j++] = 'K';  // K
              inc_source[j++] = 'O';  // O
              inc_source[j++] = 'D';  // D
              inc_source[j++] = 'E';  // E
              inc_source[j++] = '\0';  // NULL
              
              //i=0;
              //while(inc_source[i] != '\0') {
                // printf("%d %c\n", i,inc_source[i]);
                ///i++;
              //}
              

              // keep current source into temp
              inc_tmp_source = NULL;

              inc_pt = pg.pt;
              inc_back_pt = pg.back_pt;
              inc_tmp_source = pg.source;

              // set source to included file source
              pg.source = inc_source;
              pg.pt = 0;
              pg.back_pt = 0;

              // interprete included file source
              SourceCodeReader(1, inc_file);

              // clear filename
              memset(&inc_file, '\0', sizeof(inc_file));

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

                ungetlex();
                valdat = expression("",0);
              }

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {

                strcpy(inc_file, lex.detail.string);
                // printf("Code luar %s\n", inc_file);

                if( stat( inc_file, &inc_st ) != 0 ){
                  fprintf( stderr, "Kode Luar tidak ditemukan: %s\n",  inc_file);
                  exit( -1 );
                }

                if( ( inc_fp = fopen(inc_file, "r") ) == NULL ) {
                  fprintf( stderr, "tidak bisa buka Kode Luar %s\n", inc_file );
                  exit( -1 );
                }

                inc_source = (char *)calloc(inc_st.st_size + 9, sizeof(char));
                if( inc_source == NULL ){
                  fprintf( stderr, "calloc error\n" );
                  exit( -1 );
                }

                fread( inc_source, 1, inc_st.st_size, inc_fp );

                fclose( inc_fp );

                // and implicit code for reading termination of include file
                i=0; j=0;
                while(inc_source[i] != '\0') {

                  if((inc_source[i] == 'R' || inc_source[i] == 'r') &&
                     (inc_source[i-1] == 'A' || inc_source[i-1] == 'a') &&
                     (inc_source[i-2] == 'U' || inc_source[i-2] == 'u') &&
                     (inc_source[i-3] == 'L' || inc_source[i-3] == 'l' ) &&
                     inc_source[i-4] == '_' &&
                     (inc_source[i-5] == 'E' || inc_source[i-5] == 'e' ) &&
                     (inc_source[i-6] == 'D' || inc_source[i-6] == 'd' ) &&
                     (inc_source[i-7] == 'O' || inc_source[i-7] == 'o' ) &&
                     (inc_source[i-8] == 'K' || inc_source[i-8] == 'k' ) &&
                     inc_source[i-9] == '_'
                    ) {

                    j = i+2;
                  }

                  i++;
                }

                inc_source[j+1] = ' ';  // 
                inc_source[j++] = 'E';  // E
                inc_source[j++] = 'N';  // N
                inc_source[j++] = 'D';  // D
                inc_source[j++] = '_';  // _
                inc_source[j++] = 'K';  // K
                inc_source[j++] = 'O';  // O
                inc_source[j++] = 'D';  // D
                inc_source[j++] = 'E';  // E
                inc_source[j++] = '\0';  // NULL
              
                //i=0;
                //while(inc_source[i] != '\0') {
                  // printf("%d %c\n", i,inc_source[i]);
                  ///i++;
                //}
              

                // keep current source into temp
                inc_tmp_source = NULL;

                inc_pt = pg.pt;
                inc_back_pt = pg.back_pt;
                inc_tmp_source = pg.source;

                // set source to included file source
                pg.source = inc_source;
                pg.pt = 0;
                pg.back_pt = 0;

                // interprete included file source
                SourceCodeReader(1, inc_file);

                // clear filename
                memset(&inc_file, '\0', sizeof(inc_file));

              }

              break;

	    default:
	      Error("kode perintah KODE_LUAR salah");
	    }

	  getlex();
	  fflush( stdout );
	  ungetlex();

}


void keyEndKodeluar ( int progType , char currentClass[MAX_STRING_LEN])
{

          // return source from temp to current
          pg.pt      = inc_pt;
          pg.back_pt = inc_back_pt;
          pg.source  = inc_tmp_source;

          // printf("balik ke main %s\n", lex.detail.string);

          // clear temporary source and file
          memset(&inc_tmp_source, '\0', sizeof(inc_tmp_source));

          // clear temporary include source and file
          memset(&inc_source, '\0', sizeof(inc_source));
          memset(&inc_file, '\0', sizeof(inc_file));

          inc_tmp_source = NULL;
          inc_source = NULL;

}


