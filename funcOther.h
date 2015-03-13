// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

int power_stat(char *myport);
int analog_stat(char *myport);

VAL_LABEL funcSaklarStatus() {
   VAL_LABEL datx;
   VAL_LABEL valdat, tmpdat;   
   char      class_tmpvar[MAX_STRING_LEN];
   int       pwr = -1;

 
   memset(&datx, '\0', sizeof(datx));   
   memset(&valdat, '\0', sizeof(valdat));
   memset(&tmpdat, '\0', sizeof(tmpdat));

   memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

   //printf("saklar inside...\n");

   getlex();

   if(lex.type == TYPE_STR) {
     datx.val = power_stat(lex.detail.string);
     datx.datatype = 0;

   } else if(lex.type == TYPE_IDENT) {
      /* read data */
      // printf("get panjang array ident\n");

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
             tmpdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
      } else {
             tmpdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
      }

      // printf("read panjang array ident, type : \n", tmpdat.datatype);

      if(tmpdat.datatype == 3) {
         datx.val = power_stat(tmpdat.str);
         datx.datatype = 0;
      }   

   }
   
   return datx;
}

VAL_LABEL funcAnalogPortStatus() {
   VAL_LABEL datx;
   VAL_LABEL valdat, tmpdat;   
   char      class_tmpvar[MAX_STRING_LEN];
   int       pwr = -1;

 
   memset(&datx, '\0', sizeof(datx));   
   memset(&valdat, '\0', sizeof(valdat));
   memset(&tmpdat, '\0', sizeof(tmpdat));

   memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

   // printf("AIN inside...\n");

   getlex();

   if(lex.type == TYPE_STR) {
     datx.val = analog_stat(lex.detail.string);
     datx.datatype = 0;

   } else if(lex.type == TYPE_IDENT) {
      /* read data */
      // printf("get panjang array ident\n");

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
             tmpdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
      } else {
             tmpdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
      }

      // printf("read panjang array ident, type : \n", tmpdat.datatype);

      if(tmpdat.datatype == 3) {
         datx.val = analog_stat(tmpdat.str);
         datx.datatype = 0;
      }   

   }
   
   return datx;
}

VAL_LABEL funcOther() {
  VAL_LABEL datx;



  VAL_LABEL valdat, tmpdat;

  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&datx, '\0', sizeof(datx));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));



      /* ======================================================== */
      /* OTHER            ======================================= */
      /* ======================================================== */
      if( !strcmp(lex.detail.string, "xxxxxxxxxxxxxxxxxxxxxxxxxxx") ||
         !strcmp(lex.detail.string, "xxxxxxxxxxxxxxxxxxxxxxxxx") ) { 


      /* ======================================================== */
      /* PANJANG              =================================== */
      /* ======================================================== */
      } else if( !strcmp(lex.detail.string, "PANJANG") || 
                 !strcmp(lex.detail.string, "panjang") ||
                 !strcmp(lex.detail.string, "Panjang") ) { 
         /* printf("PANJANG function\n"); */
         memset(&tmpdat, '\0', sizeof(tmpdat));
         memset(&valdat, '\0', sizeof(valdat));

         getlex();
         // printf("panjang get ident : %s\n", lex.detail.ident);
         // printf("panjang get type : %d\n", lex.type);

         if(lex.type == TYPE_ARRAY) {
            if(strlen(lex.detail.array_str) > 0) {
              strcpy(valdat.array_str, lex.detail.array_str);
              getArrayName(lex.detail.array_str, (char *)&valdat.array_name);
              getArrayIdx(lex.detail.array_str, (char *)&valdat.array_idx);

              if(currentClass != NULL && strlen(currentClass) > 0) {

                #ifdef WIN32
                 #ifndef S_SPLINT_S
                 sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                 #else
                 snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                 #endif
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_name);
                #endif

                //printf("construct class var: %s\n", class_tmpvar);
                memset(&valdat.array_name[0], '\0', sizeof(valdat.array_name));
                strcpy(valdat.array_name, class_tmpvar);

                if(!isdigit(valdat.array_idx[0])) {
                  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

                  #ifdef WIN32
                   #ifndef S_SPLINT_S
                   sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                   #else
                   snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                   #endif
                  #else
                  snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, valdat.array_idx);
                  #endif


                  //printf("construct class var: %s\n", class_tmpvar);
                  memset(&valdat.array_idx[0], '\0', sizeof(valdat.array_idx));
                  strcpy(valdat.array_idx, class_tmpvar);
                }
              }

              /* read data */
              valdat = ValLabel( valdat.array_name, sub_deep, valdat, VAL_FLAG_SEARCH_R );

              /* printf("panjang array %d", valdat.array_max);  */
              datx.val = tmpdat.array_max;
              datx.datatype = 0;
           }

         } else if(lex.type == TYPE_STR) {
           datx.val = (long)strlen(lex.detail.string);
           datx.datatype = 0;

         } else if(lex.type == TYPE_IDENT) {
           /* read data */
           // printf("get panjang array ident\n");

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
             tmpdat = ValLabel( class_tmpvar, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           } else {
             tmpdat = ValLabel( lex.detail.ident, sub_deep, valdat, VAL_FLAG_SEARCH_R );
           }

		   // printf("read panjang array ident, type : \n", tmpdat.datatype);

           if(tmpdat.datatype == 3) {
             datx.val = (long)strlen(tmpdat.str);
             datx.datatype = 0;

           }
           else if(tmpdat.datatype >= 6 && tmpdat.datatype <=8) {
             /*
             printf("array type = %d\n", tmpdat.datatype); 
             printf("panjang array ident = %d\n", tmpdat.array_max); 
             */
             datx.val = tmpdat.array_max;
             datx.datatype = 0;

             /*
             printf("ident type = %d\n", datx.datatype); 
             printf("ident val = %d\n", datx.val); 
             */
           }
           else
           if(tmpdat.datatype == 10) {
             /*
             printf("array type = %d\n", tmpdat.datatype); 
             printf("panjang array ident = %d\n", tmpdat.array_max); 
             */
             datx.val = tmpdat.array_max;
             datx.datatype = 0;

             /*
             printf("ident type = %d\n", datx.datatype); 
             printf("ident val = %d\n", datx.val); 
             */
           }
           else
           {
		     // including not valued yet array
             datx.val = tmpdat.array_max;
             datx.datatype = 0;
           }


         } else {
           /* not array, so there is no length */
           datx.val = 0;
           datx.datatype = 0;
         }
	  
	  }


  if(valdat.left != NULL)
    free(valdat.left);
  if(valdat.right != NULL)
    free(valdat.right);
  if(valdat.pnext != NULL)
    free(valdat.pnext);

  if(tmpdat.left != NULL)
    free(tmpdat.left);
  if(tmpdat.right != NULL)
    free(tmpdat.right);
  if(tmpdat.pnext != NULL)
    free(tmpdat.pnext);

	
   return datx;
}





int power_stat(char *myport) {
    FILE *fp=NULL;

    // create a variable to store whether we are sending a '1' or a '0'
    char set_value[4];
    // Integer to keep track of whether we want on or off
    int toggle = 0;
    // path for GPIO file
    char mypath[128];

    int  get_value = -1;
    
    // Initialize memory    
    memset(&set_value, '\0', sizeof(set_value));
    memset(&mypath, '\0', sizeof(mypath));

    //printf("power stat ...\n");

    // Check GPIO
    if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL)
    {
       printf("Cannot open GPIO export file.\n");
       exit(1);
    }

    //Set pointer to begining of the file
    rewind(fp);
    //Write our value of "myport" to the file
    strcpy(set_value, myport);
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);

    // /////////////////////////////////////////////
    //GET VALUE
    // /////////////////////////////////////////////
    memset(&mypath, '\0', sizeof(mypath));
    strcpy(set_value, myport);    
    sprintf(mypath, "/sys/class/gpio/gpio%s/value", set_value);
    //printf("get value , path : %s \n", mypath);      

    if ((fp = fopen(mypath, "r")) == NULL)
    {
        printf("Cannot open value file.\n");
        exit(1);
    }

    memset(&set_value, '\0', sizeof(set_value));    
    fread(set_value, sizeof(int), 1, fp);
    fclose(fp);

    get_value = atoi (set_value);
    //printf("get val : %s \n", set_value);    

    return get_value;
}

int analog_stat(char *myport) {
    FILE *fp=NULL;

    // create a variable to store AIN name
    char set_value[6];
    // Integer to keep track of whether we want on or off
    int toggle = 0;
    // path for GPIO file
    char mypath[128];

    int  get_value = -1;
    
    // Initialize memory    
    memset(&set_value, '\0', sizeof(set_value));
    memset(&mypath, '\0', sizeof(mypath));

    // printf("analog stat ...\n");

    // Check AIN folder
    if ((fp = fopen("/sys/devices/ocp.2/helper.14", "r")) == NULL)
    {
       printf("Tidak ada AIN port.\nCek aktivasi AIN port.\n");
       exit(1);
    }

    //Set pointer to begining of the file
    rewind(fp);
    //Write our value of "myport" to the file
    strcpy(set_value, myport);
    fwrite(&set_value, sizeof(char), 3, fp);
    fclose(fp);

    // /////////////////////////////////////////////
    //GET VALUE
    // /////////////////////////////////////////////
    memset(&mypath, '\0', sizeof(mypath));
    strcpy(set_value, myport);    
    sprintf(mypath, "/sys/devices/ocp.2/helper.14/%s", set_value);
    // printf("get path : %s \n", mypath);      

    if ((fp = fopen(mypath, "r")) == NULL)
    {
        printf("Tidak bisa buka file analog input AIN.\n");
        exit(1);
    }

    memset(&set_value, '\0', sizeof(set_value));    
    fread(set_value, sizeof(int), 1, fp);
    fclose(fp);

    get_value = atoi (set_value);
    // printf("get val : %s \n", set_value);    

    return get_value;
}



