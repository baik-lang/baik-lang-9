// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

int power_on(char *myport);
int power_off(char *myport);

void keySAKLAR_HIDUP ()
{

  char ident[MAX_IDENT_LEN];

  VAL_LABEL valdat;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&ident, '\0', sizeof(ident));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


     getlex();
     // printf(" DEBUG: SAKLAR_HIDUP lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    case TYPE_STR:
	      power_on( lex.detail.string );
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                power_on(valdat.str);
              }

              break;

	    default:
	      Error("kode perintah SAKLAR_HIDUP salah");
	    }
	    
        getlex();

	fflush( stdout );

	ungetlex();
}


void keySAKLAR_MATI ()
{

  char ident[MAX_IDENT_LEN];

  VAL_LABEL valdat;

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&ident, '\0', sizeof(ident));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));


     getlex();
     // printf(" DEBUG: SAKLAR_HIDUP lex.type %d\n", lex.type);

	  switch( lex.type )
	    {
	    case TYPE_STR:
	      power_off( lex.detail.string );
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                power_off(valdat.str);
              }

              break;

	    default:
	      Error("kode perintah SAKLAR_MATI salah");
	    }
	    
        getlex();

	fflush( stdout );

	ungetlex();
}






int power_on(char *myport) {
    FILE *fp=NULL;

    // create a variable to store whether we are sending a '1' or a '0'
    char set_value[4];
    // Integer to keep track of whether we want on or off
    int toggle = 0;
    // path for GPIO file
    char mypath[128];
    
    // Initialize memory    
    memset(&set_value, '\0', sizeof(set_value));
    memset(&mypath, '\0', sizeof(mypath));

    // Check GPIO
    if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL)
    {
       printf("Tidak bisa buka GPIO export file.\n");
       exit(1);
    }

    //Set pointer to begining of the file
    rewind(fp);
    //Write our value of "myport" to the file
    strcpy(set_value, myport);
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);

    // ///////////////////////////////////////////
    // SET DIRECTION
    // ///////////////////////////////////////////
  
    sprintf(mypath, "/sys/class/gpio/gpio%s/direction", set_value);
    // printf("path : %s \n", mypath);      
        
    if ((fp = fopen(mypath, "rb+")) == NULL)
    {
       printf("Tidak bisa buka direction file.\n");
       exit(1);
    }
    //Set pointer to begining of the file
    rewind(fp);
    //Write our value of "out" to the file
    strcpy(set_value,"out");
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);
    // printf("...direction set to output\n");

    // /////////////////////////////////////////////
    //SET VALUE
    // /////////////////////////////////////////////
    memset(&mypath, '\0', sizeof(mypath));
    strcpy(set_value, myport);    
    sprintf(mypath, "/sys/class/gpio/gpio%s/value", set_value);
    // printf("path : %s \n", mypath);      

    if ((fp = fopen(mypath, "rb+")) == NULL)
    {
        printf("Cannot open value file.\n");
        exit(1);
    }
    
    //Set pointer to begining of the file
    rewind(fp);
    //Write our value of "1" to the file
    strcpy(set_value,"1");
    fwrite(&set_value, sizeof(char), 1, fp);
    fclose(fp);
    // printf("...Power On...\n");

    return 0;
}

int power_off(char *myport) {
    FILE *fp=NULL;

    // create a variable to store whether we are sending a '1' or a '0'
    char set_value[4];
    // Integer to keep track of whether we want on or off
    int toggle = 0;
    // path for GPIO file
    char mypath[128];
    
    // Initialize memory    
    memset(&set_value, '\0', sizeof(set_value));
    memset(&mypath, '\0', sizeof(mypath));

    // Check GPIO
    if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL)
    {
       printf("Tidak bisa buka GPIO export file.\n");
       exit(1);
    }

    //Set pointer to begining of the file
    rewind(fp);
    //Write our value of "myport" to the file
    strcpy(set_value, myport);
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);

    // ///////////////////////////////////////////
    // SET DIRECTION
    // ///////////////////////////////////////////
  
    sprintf(mypath, "/sys/class/gpio/gpio%s/direction", set_value);
    // printf("path : %s \n", mypath);      
        
    if ((fp = fopen(mypath, "rb+")) == NULL)
    {
       printf("Tidak bisa buka direction file.\n");
       exit(1);
    }
    //Set pointer to begining of the file
    rewind(fp);
    //Write our value of "out" to the file
    strcpy(set_value,"out");
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);
    // printf("...direction set to output\n");

    // /////////////////////////////////////////////
    //SET VALUE
    // /////////////////////////////////////////////
    memset(&mypath, '\0', sizeof(mypath));
    strcpy(set_value, myport);        
    sprintf(mypath, "/sys/class/gpio/gpio%s/value", set_value);

    if ((fp = fopen(mypath, "rb+")) == NULL)
    {
        printf("Cannot open value file.\n");
        exit(1);
    }
    
    //Set pointer to begining of the file
    rewind(fp);
    //Write our value of "1" to the file
    strcpy(set_value,"0");
    fwrite(&set_value, sizeof(char), 1, fp);
    fclose(fp);
    // printf("...Power Off...\n");

    return 0;
} 


