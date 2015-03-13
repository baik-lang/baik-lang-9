// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


//char* hhstring_add(int last, char *orig, const char *addstr)
char* hhstring_add(char orig[], char addstr[])
{
   char *result = NULL; 
   int i=0,j=0;
   int  newlen=0;

   //printf("new haris_string\n");

   if (orig == NULL || addstr==NULL) {
     return NULL;
   }

   newlen = (int)strlen(orig) + (int)strlen(addstr);

   result = (char *)malloc(newlen+ 1);
   if(result == NULL) {
	   printf("can not allocate memory\n");
	   exit(1);
   }
   for(i=0; i<(int)strlen(orig); i++) 
     result[i] = orig[i];
   
   for(j=0; j<(int)strlen(addstr); j++) {
      result[i] = addstr[j];
      i++;
   }
   result[i]='\0';   

   //printf("new haris_string ok\n");
   
   return result;
}
