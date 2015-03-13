// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyTunggu ()
{
  VAL_LABEL valdat;
 
  memset(&valdat, '\0', sizeof(valdat));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_NUM:
            #ifdef WINDOWS
              #ifndef S_SPLINT_S
	      Sleep( lex.detail.num );
              #endif
            #else
	        sleep( lex.detail.num );
            #endif
	      break;	  
	    case TYPE_IDENT:
	      ungetlex();
          valdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
          if(valdat.datatype == 0) {
            #ifdef WINDOWS
              #ifndef S_SPLINT_S
              Sleep( valdat.val );
              #endif
            #else
	      sleep( valdat.val );
            #endif
	  } else {
	            Error("variabel harus dengan bilangan desimal");
          }
	      break;
	    default:
	      Error("kode perintah TUNGGU salah");
	    }
	  getlex();

	fflush( stdout );

	ungetlex();

  if(valdat.filename != NULL)
    free(valdat.filename);
  if(valdat.folder != NULL)
    free(valdat.folder);
  if(valdat.filedata != NULL)
    free(valdat.filedata);
  if(valdat.long_str != NULL)
    free(valdat.long_str);

  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

}

