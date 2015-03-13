// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


/* ****************************************************** */
/* WWW handle */
/* ****************************************************** */

int parse_webform(char* s_in,long maxl,char* name[],char* value[],int *p_nfld)
{
        int i,cur_field;
        *p_nfld=0;
        i=0;
        cur_field=0;
        if(s_in[0]=='\0') return(-1);
        name[0]=s_in;
        while((s_in[++i]!='\0')&&(i<maxl)){
                if(s_in[i]=='='){
                        s_in[i]='\0';
                        value[cur_field]=s_in+i+1;
                }
                else if(s_in[i]=='&'){
                        s_in[i]='\0';
                        cur_field++;
                        name[cur_field]=s_in+i+1;
                }
        }
        *p_nfld=cur_field+1;
        return(0);
}

       
int decode_webform(char* s,long len)
{
        int i,j;
        char buf,*s1;
        
		if(len==0)return(-1);

        s1=(char*)malloc(len);

        for(i=0,j=0;i<len;i++,j++)
        {
                if(s[i]=='+'){s1[j]=' ';continue;}
                if(s[i]!='%') {s1[j]=s[i];continue;}
                buf=((s[++i]>='A') ? s[i]-'A'+10 : s[i]-'0');
                buf*=16;
                buf+=((s[++i]>='A') ? s[i]-'A'+10 : s[i]-'0');
                s1[j]=buf;
        }
        for(i=0;i<j;i++) s[i]=s1[i];
        s[i]='\0';

		if(s1 != NULL) {
          free(s1);
		}

        return(0);
}

void getPostCgi(void) {
    web_cLength = (char*)getenv("CONTENT_LENGTH");
    if(web_cLength == '\0') {
       fprintf( stderr,"POST CGI salah: tidak ada parameter CONTENT_LENGTH");
       exit(-1);
    }
    web_length  = atol(web_cLength);
    if(web_length>WEBMAXLEN) {
       printf("CONTENT_LENGTH > WEBMAXLEN\n");
       exit(0);
    }

    web_inputstring=(char*)malloc(web_length+1);

    scanf("%s",web_inputstring);
    /*
    printf("%s","Content-type: text/html\n\n\0");
    printf("%s","<HTML><HEAD></HEAD><BODY>\n\0");
    */
    parse_webform(web_inputstring, WEBMAXLEN, web_name, web_value, &web_nfield);
    for(web_i=0; web_i<web_nfield; web_i++){
       /*
       decode_webform(web_name[web_i],strlen(web_name[web_i]));
       */
       decode_webform(web_value[web_i],strlen(web_value[web_i]));
       
       /* printf("%s ---> %s<BR>\n", web_name[web_i],web_value[web_i]); */
    }
    /* printf("%s","\n</BODY></HTML>\n\0"); */

	//if(web_inputstring != NULL ) {
      // free(web_inputstring);       // DONT free here ! use garbage collection.
	//}
}

char *getPostName(int i) {
  char *ret;
  if(web_name[i] != '\0' && strlen(web_name[i]) > 0) {
    ret = web_name[i];
    return ret;
  }

  return "";
}

char *getPostVal(int i) {
  char *ret;
  if(web_value[i] != '\0' && strlen(web_value[i]) > 0) {
    ret = web_value[i];
    return ret;
  }

  return "";
}

/* ****************************************************** */
/* Base 64 Encode - Decode */
/* ****************************************************** */

int base64(char *data,int size,char *into)
{
char  now[3];
char  c='\0';
int	  i,h,n;
char  *ptr=NULL;


    memset(&now, '\0', sizeof(now));
	ptr=into;

	n=0;
	for(i=0;i<size;i+=3){
		if(i+2<size){
			now[0]=data[i];
			now[1]=data[i+1];
			now[2]=data[i+2];
			c=(now[0]>>2)&0x3F;
			outchar(&n,&ptr,c);
			c=((now[0]<<4)&0x30)+((now[1]>>4)&0x0F);
			c&=0x3F;
			outchar(&n,&ptr,c);
			c=((now[1]<<2)&0x3C)+((now[2]>>6)&0x03);
			c&=0x3F;
			outchar(&n,&ptr,c);
			c=now[2]&0x3F;
			c&=0x3F;
			outchar(&n,&ptr,c);
		}
		else if(i+1<size){
			now[0]=data[i];
			now[1]=data[i+1];
			c=(now[0]>>2)&0x3F;
			outchar(&n,&ptr,c);
			c=((now[0]<<4)&0x30)+((now[1]>>4)&0x0F);
			c&=0x3F;
			outchar(&n,&ptr,c);
			c=((now[1]<<2)&0x3C);
			c&=0x3F;
			outchar(&n,&ptr,c);
		}
		else{
			now[0]=data[i];
			c=(now[0]>>2)&0x3F;
			outchar(&n,&ptr,c);
			c=((now[0]<<4)&0x30);
			c&=0x3F;
			outchar(&n,&ptr,c);
		}
	}

	h=4-(n%4);
	if(h!=4){
		for(i=0;i<h;i++){
			*ptr='=';ptr++;
		}
	}

	*ptr='\0';

	return(0);
}


int outchar(int *n,char **ptr,char c)
{
	if(c<=25){
		**ptr=c+'A';
	}
	else if(c<=51){
		**ptr=c-26+'a';
	}
	else if(c<=61){
		**ptr=c-52+'0';
	}
	else if(c==62){
		**ptr='+';
	}
	else if(c==63){
		**ptr='/';
	}
	(*ptr)++;
	(*n)++;

        //if((*n)%60==0){              // 60-th byte not be line feeded
        //      **ptr='\n';
	//      (*ptr)++;
        //}

	return(0);
}

char b64_charconv(char c)
{
    char str[256];

    memset(&str, '\0', sizeof(str));

    if (c >= 'A' && c <= 'Z')
        return (c - 'A');
    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 0x1a);
    if (c >= '0' && c <= '9')
        return (c - '0' + 0x34);
    if (c == '+')
        return 0x3e;
    if (c == '/')
        return 0x3f;
    if (c == '=')
        return '\0';
    sprintf(str, "!Tidak bisa dibaca %c \n", c);
    return '\0';
}


void b64_decode(char *lpszStr, char *lpszResult)
{
    int len, i, iR;
    char a1, a2, a3, a4;

    len = strlen(lpszStr);
    i = 0;
    iR = 0;
    while (1) {
        if (i >= len)
            break;
        a1 = b64_charconv(lpszStr[i]);
        a2 = b64_charconv(lpszStr[i+1]);
        a3 = b64_charconv(lpszStr[i+2]);
        a4 = b64_charconv(lpszStr[i+3]);
        lpszResult[iR] = (a1 << 2) + (a2 >>4);
        lpszResult[iR + 1] = (a2 << 4) + (a3 >>2);
        lpszResult[iR + 2] = (a3 << 6) + a4;
        i += 4;
        iR += 3;
    }
    return;
}


