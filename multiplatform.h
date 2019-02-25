// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// LAST 2015-07-11 win_checkweb (iot)

char* newString(const char* str)
{
	char* p = (char*)malloc(strlen(str) + 1);

	if (p == NULL) {
		printf("malloc error : can not make newString");
		return NULL;
	}

	strcpy(p, str);
	return p;
}

char* addString(char** form, const char* latt)
{
	*form = (char*)realloc(*form, strlen(*form) + strlen(latt) + 1);

	if (*form == NULL) {
		printf("realloc error : can not make addString");
		return NULL;
	}
	strcat(*form, latt);

	return *form;
}




/* ************************************************* */
#ifndef WINDOWS
/* ************************************************* */
int ux_initSocket(const char *transport) {
   struct hostent    *myhost=NULL;
   struct sockaddr_in me;
   int s_waiting = 0;
   int type = 0;

  /* use protocol to choose a socket type */
  if(strcmp(transport, "udp") == 0 || strcmp(transport, "UDP") == 0)
    type =  SOCK_DGRAM;
  else
    type = SOCK_STREAM;

   if((s_waiting = socket(AF_INET, type, 0)) < 0) {
     fprintf(stderr, "Gagal buat soket %s\n", transport);
     exit(1);
   }

   /* printf("ux init socket ok\n"); */

  return s_waiting;
}

int ux_closeSocket(int s) {
    int ret=0;

    ret = close(s);
    /* printf("s ret %d\n", ret); */

    return ret;
}

int ux_connectSocket(int s, char *szServer, const char *portservice) {

    char szBuf[1024];
    struct sockaddr_in saddr;

    int ret=0;

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family      = AF_INET;

    
    saddr.sin_addr.s_addr = inet_addr(szServer);

    
    if((saddr.sin_port = htons((u_short)atoi(portservice))) == 0)
      Error("tidak bisa ambil %s service entry\n", portservice);

    if (connect(s, (struct sockaddr *)&saddr, sizeof(saddr)) != 0) {
        fprintf(stderr, "Tidak bisa sambung soket ke %s\n", szServer);
        close(s);
        return -1;
    }

    return 0;


}


int ux_ikatSocket(int s, const char *portservice) {
  struct sockaddr_in sin;

  int                qlen = 10;
  int                nRtn = 0;

  struct sockaddr_in fsin;
  int alen = 0;

  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;

  /* map to local address */
  sin.sin_addr.s_addr = htonl(INADDR_ANY); /* any incoming interface */

  /* map service name to port num */
  if((sin.sin_port = htons((u_short)atoi(portservice))) == 0)
    printf("tidak bisa ambil %s service entry\n", portservice);

  /* bind the socket */
  if(bind(s, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
    fprintf(stderr, "tidak bisa bind ke port: %s\n", portservice);
    exit(1);
  }

  if(listen(s, qlen) == -1) {
    fprintf(stderr, "tidak bisa listen pada port: %s\n", portservice);
    exit(1);
  }

  /* printf("ikatSoket OK\n"); */ 

  return s;
}

int ux_terimaSocket(int s) {
  struct sockaddr_in fsin;
  int alen=0;
  int sock=0;

  memset(&fsin, '\0', sizeof(fsin));
  sock = accept(s, (struct sockaddr *)&fsin, &alen);
  /* printf("sock accept\n"); */

  if(sock == -1) {
    fprintf(stderr, "salah: soket accept \n");
    exit(1);
  }

  return sock;
}


char *ux_bacaSocket( int sock )
{
   char buf[512];
   char *ret=NULL;
   int n=0;

   memset(&buf, '\0', sizeof(buf));

    if((n =recv(sock, buf, 512, 0)) > 0) {
      write(buf, (const void *)strlen(buf), n);
    } else {
      strcpy(buf, "");
    }

    /* printf("buf %s", buf); */
    ret = buf;

    return ret;
}

int ux_tulisSocket( int sock, char data[MAX_STRING_LEN] )
{
   int ret;

   ret = send(sock, data, (int)strlen(data), 0);

   return ret;
}

/* ****************************************************** */
/* Unix : CheckWeb handle                                  */
/* ****************************************************** */

char* ux_checkweb(int argc, char argv[512]) {
    int BUF_LEN=512;
    char      *r = NULL;

    int  len=0;
    char ch[2];
    char *myline=NULL;
    
    int s=0;                             // Socket Descriptor in Unix/Linux 
    struct hostent *servhost=NULL;       // Hostname and IP Address Structure
    struct sockaddr_in server;           // Socket Structure in Unix
    struct servent *service=NULL;        // Service (http) handling Structure

    char send_buf[BUF_LEN];              // Buffer for HTTP Protocol sending to Server
    char host[BUF_LEN];                  // Connected Hostname
    char path[BUF_LEN];                  // Request Path
    char host_path[BUF_LEN];
    unsigned short port = 80;            // Connected Port Number

    char buf[BUF_LEN];
    char match_buf[BUF_LEN];

    int read_size = 0;

    char match_str1[BUF_LEN];              // String to match Web Content
    char match_str2[BUF_LEN];              // String to match Web Content
    char match_str3[BUF_LEN];              // String to match Web Content

    memset(&match_str1, '\0', sizeof(match_str1));
    memset(&match_str2, '\0', sizeof(match_str2));
    memset(&match_str3, '\0', sizeof(match_str3));

    memset(&send_buf, '\0', sizeof(send_buf));

    memset(&buf, '\0', sizeof(buf));
    memset(&match_buf, '\0', sizeof(match_buf));

    memset(&host, '\0', sizeof(host));
    memset(&path, '\0', sizeof(path));
    memset(&host_path, '\0', sizeof(host_path));    

    strcpy(host,"localhost");
    strcpy(path, "/");

    //printf("inside ux_checkweb.\n");

    if ( argc > 1 ){                     // if URL defined as Argument
		// printf("check strlen \n");
        if ( strlen(argv) > BUF_LEN) {
            fprintf(stderr, "URL is too long\n");
            return "";
        }
		// printf("strlen OK \n");

        /* string statement with http:// */
        /* successful to sscanf */
        /* there is other string after http://  */
 
       if ( strstr(argv, "http://") &&
             sscanf(argv, "http://%s", host_path) &&
             strcmp(argv, "http://" ) ){
             char *p='\0';

            p = strchr(host_path, '/');  /* Check separator "/" between Host and Path */
            if ( p != NULL ){
                strcpy(path, p);        /* string after "/" will be copied into path */
                *p = '\0';
                strcpy(host, host_path); /* string before "/" will be copied into host */
            } else {                     /* if no separator "/", the form will be http://host  */
                strcpy(host, host_path); /* and all string will be copied into host */
            }

            p = strchr(host, ':');       /* if there is ":" inside Hostname */
            if ( p != NULL ){
                port = atoi(p+1);        /* Get port number  */
                if ( port <= 0 ){        /* if not number (failed for atoi) or 0 */
                    port = 80;           /* set port number to be 80 */
                }
                *p = '\0';
            }
        } else {
            fprintf(stderr, "Please set URL to be http://host/path \n");
            return "";
        }
    }

    //printf("Getting ... http://%s%s \n\n", host, path);

    /* Getting Host Information (IP and others) */
    servhost = gethostbyname(host);
    if ( servhost == NULL ){
        fprintf(stderr, "Failed to get IP Address from [%s] \n", host);
        return "";
    }

    bzero(&server, sizeof(server));            /* Clear Structure */

    server.sin_family = AF_INET;

    /* Copy IP Addrress Structure */
    bcopy(servhost->h_addr, &server.sin_addr, servhost->h_length);

    if ( port != 0 ){                          /* If port number is defined inside Argument */
        server.sin_port = htons(port);
    } else {                                   /* If not defined, get port number by getservbyname */
        service = getservbyname("http", "tcp");
        if ( service != NULL ){                /* Copy port number if successful */
            server.sin_port = service->s_port;
        } else {                               /* Set port number to be 80 if filed */
            server.sin_port = htons(80);
        }
    }

    /* Create Unix Socket */
    if ( ( s = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ){
        fprintf(stderr, "Failed to create socket ! \n");
        return "";
    }

    //printf("create socket OK\n");

    /* Connect to server */
    if ( connect(s, (struct sockaddr *)&server, sizeof(server)) == -1 ){
        fprintf(stderr, "Failed to connect to server ! \n");
        return "";
    }
    
    //printf("connect socket OK\n");    

    /* Create HTTP Protocol and send to server */
    sprintf(send_buf, "GET %s HTTP/1.0\r\n", path);
    write(s, send_buf, strlen(send_buf));

    sprintf(send_buf, "Host: %s:%d\r\n", host, port);
    write(s, send_buf, strlen(send_buf));

    sprintf(send_buf, "\r\n");
    write(s, send_buf, strlen(send_buf));

    // Set Match Pattern 1
    strcpy(match_str1, "suhu =");        
    // Set Match Pattern 1
    strcpy(match_str2, "cahaya =");        
    // Set Match Pattern 1
    strcpy(match_str3, "stat");        

    memset(&match_buf, '\0', sizeof(match_buf));

   /* Wait for receiving message from server */
    while (1){
        memset(&buf, '\0', sizeof(buf));

        // read_size = read(s, buf, BUF_LEN);

        len = recv(s, ch, 1, 0);
	myline = newString(ch);

	while (strncmp(ch, "\n", 1) != 0) {
		len = recv(s, ch, 1, 0);
		if (len == 1) {
		  myline = addString(&myline, ch);
        	}
		else {
			break;
		}
	}
	chop(myline);
	strcpy(buf, myline);
	myline = NULL;

        
        //if ( read_size > 0 ){

	if (strlen(buf) > 0){

           //printf("buf: %s\n",buf);
           //printf("pattern: %s\n", match_str);

           if(unixRegexBuf(buf, match_str1) == 1) {
              strcpy(match_buf, buf);
              //printf("---> Match 1\n");
              break;
           } else
           if(unixRegexBuf(buf, match_str2) == 1) {
              strcpy(match_buf, buf);
              //printf("---> Match 2\n");
              break;
           } else
           if(unixRegexBuf(buf, match_str3) == 1) {
              strcpy(match_buf, buf);
              //printf("---> Match\n");
              break;
           } 
           else {
              //printf("---> NOT Match\n");
           }

        } 
        memset(&buf, '\0', sizeof(buf));
    }

    // Close Socket
    close(s);

    r = match_buf;


    return r;
}


/* ****************************************************** */
/* Unix : SendMail handle                                  */
/* ****************************************************** */

int ux_sendMail(char szServer[64], char szPort[8],
    char mailfrom[128], char mailto[1024], char subject[256], char body[4096])
{
    char szBuf[1024],                            /* message from svr */
         send_mesg[4096];                        /* message to svr */
    u_int port = 0;

    int nRtn = 0;
    int s = 0;                                   /* socket */

    struct sockaddr_in saddr;
    unsigned int addr;

    port = (u_int)atoi(szPort);
    // if(isDEBUG == 1) printf("port : %d\n", port);

    if(s = socket(AF_INET, SOCK_STREAM, 0) < 0) {
        printf("Gagal buat Soket\n");
        return -2;
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;

    saddr.sin_port = htons(port);                  /* Server Port       */
    saddr.sin_addr.s_addr = inet_addr(szServer);   /* Server IP address */

    // printf("s %s p %d \n", szServer, port);

    if (connect(s, (struct sockaddr *)&saddr, sizeof(saddr)) != 0) {
        printf("Tidak bisa sambung ke mail server\n");
        close(s);
        return -4;
    }

    memset(szBuf, '\0', sizeof(szBuf));
    memset(send_mesg, '\0', sizeof(send_mesg));

    // if(isDEBUG == 1) printf("start mail ...\n");
                /* get welcome response */
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);

    // printf("svr: %s\n", szBuf);

    if (strstr(szBuf, "220") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    strcpy(send_mesg, "HELO SERVER\n");
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);

    // printf("svr: %s\n", szBuf);

    if (strstr(szBuf, "250") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    memset(send_mesg, '\0', sizeof(send_mesg));
    sprintf(send_mesg,"MAIL FROM: %s\r\n", mailfrom);
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);
    if (strstr(szBuf, "250") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    memset(send_mesg, '\0', sizeof(send_mesg));
    sprintf(send_mesg,"RCPT TO: %s\r\n", mailto);
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);
    if (strstr(szBuf, "250") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    memset(send_mesg, '\0', sizeof(send_mesg));
    strcpy(send_mesg, "DATA\n");
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);
    if (strstr(szBuf, "354") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    memset(send_mesg, '\0', sizeof(send_mesg));
    sprintf(send_mesg,"To: %s\r\n", mailto);
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(send_mesg, '\0', sizeof(send_mesg));
    sprintf(send_mesg,"Subject: %s\r\n\n", subject);  // need \n\n
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(send_mesg, '\0', sizeof(send_mesg));
    sprintf(send_mesg,"%s\r\n", body);
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(send_mesg, '\0', sizeof(send_mesg));
    strcpy(send_mesg, "\r\n.\n");
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);
    if (strstr(szBuf, "250") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    strcpy(szBuf, "QUIT\r\n");
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);

    close(s);

    return 0;
}

int ux_sendMail2(char szServer[64], char szPort[8], char pass[1024],
	char mailfrom[128], char mailto[1024], char subject[256], char body[4096])
{
	char szBuf[1024],                            /* message from svr */
		send_mesg[4096];                        /* message to svr */
	u_int port = 0;

	int nRtn = 0;
	int s = 0;                                   /* socket */

	struct sockaddr_in saddr;
	unsigned int addr;

	port = (u_int)atoi(szPort);
	// if(isDEBUG == 1) printf("port : %d\n", port);

	if(s = socket(AF_INET, SOCK_STREAM, 0) < 0) {
		printf("Gagal buat Soket\n");
		return -2;
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;

	saddr.sin_port = htons(port);                  /* Server Port       */
	saddr.sin_addr.s_addr = inet_addr(szServer);   /* Server IP address */

	// printf("s %s p %d \n", szServer, port);

	if (connect(s, (struct sockaddr *)&saddr, sizeof(saddr)) != 0) {
		printf("Tidak bisa sambung ke mail server\n");
		close(s);
		return -4;
	}

	memset(szBuf, '\0', sizeof(szBuf));
	memset(send_mesg, '\0', sizeof(send_mesg));

	// if(isDEBUG == 1) printf("start mail ...\n");
	/* get welcome response */
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);

	// printf("svr: %s\n", szBuf);

	if (strstr(szBuf, "220") != szBuf) {              // OK 220
		perror("Mail server tidak merespon OK\n");
	}

	strcpy(send_mesg, "EHLO MAIL.SERVER.COM\n\n");
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);

	// printf("svr: %s\n", szBuf);

	if (strstr(szBuf, "250") != szBuf) {              // OK 220
		perror("(EHLO) Mail server tidak merespon OK\n");
	}

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "AUTH PLAIN %s\r\n", pass);
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);
	if (strstr(szBuf, "235") != szBuf) {              // OK 220
		printf("(AUTH PLAIN) Mail server tidak merespon OK\n");
	}


	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "MAIL FROM: %s\r\n", mailfrom);
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);
	if (strstr(szBuf, "250") != szBuf) {              // OK 220
		perror("Mail server tidak merespon OK\n");
	}

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "RCPT TO: %s\r\n", mailto);
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);
	if (strstr(szBuf, "250") != szBuf) {              // OK 220
		perror("Mail server tidak merespon OK\n");
	}

	memset(send_mesg, '\0', sizeof(send_mesg));
	strcpy(send_mesg, "DATA\n");
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);
	if (strstr(szBuf, "354") != szBuf) {              // OK 220
		perror("Mail server tidak merespon OK\n");
	}

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "To: %s\r\n", mailto);
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "Subject: %s\r\n\n", subject);  // need \n\n
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "%s\r\n", body);
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(send_mesg, '\0', sizeof(send_mesg));
	strcpy(send_mesg, "\r\n.\r\r\n");
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);
	if (strstr(szBuf, "250") != szBuf) {              // OK 220
		perror("Mail server tidak merespon OK\n");
	}

	strcpy(szBuf, "QUIT\r\n");
	send(s, szBuf, (int)strlen(szBuf), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);

	close(s);

	return 0;
}


int unixRegexBuf(const char *string, char *pattern) {
 
  int status = 0;
 
  regex_t re;
 
 
  if(regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
     return 0; 
  }
 
  status = regexec(&re, string, (size_t)0, NULL, 0);
 
  regfree(&re);
 
  if(status != 0) {
 
    return 0; 
  }
 
  return 1; 
} 

/* ************************************************* */
#else
/* ************************************************* */
int winRegexBuf(char sbuf[MAX_STRING_LEN*4], char *regex)
{
  int st=0;

  REGE_NFA *nfa=NULL;
  REGE_REFER *rf=NULL;
  char regbuf[256];
  char *p=NULL;
  int rc=0;
  int i=0;


    st = 0;
    nfa = rege_compile(regex);

    p = NULL;
    p = sbuf;

    rc = reg_match(nfa, p, &rf, FALSE);
    if(rc > 0){
	for(i = 0; i < rc; i++){
		if(rf[i].st == NULL || rf[i].en == NULL){
			break;
		}
		lstrcpyn(regbuf, rf[i].st, rf[i].en - rf[i].st + 1);
		if(i == 0){
                        st = 1;
                        /* printf("match OK %d\n", st); */
		}else{
			/* do nothing */
		}
	}
    }else{
       /* printf("no match\n"); */
    }
    free_refer(rf);
    free_nfa(nfa);
    rf = NULL;
    nfa = NULL;

  /* printf("stat %d\n", st); */

  return st;
}

/* ****************************************************** */
/* Socket handle */
/* ****************************************************** */

SOCKET initSocket(const char *transport) {
  WSADATA            wsaData;
  struct protoent    *ppe=NULL;

  SOCKET             s;
  int                type=0;
  int                nRtn=0;

  nRtn = WSAStartup(MAKEWORD(2, 0), &wsaData); // winSock 2.0
  if (nRtn != 0) {
     Error("Gagal buat Windows Soket(WSA)\n");
  }

  /* map protocol name to protocol num */
  if((ppe = getprotobyname(transport)) == 0)
    Error("Gagal ambil %s protocol entry\n", transport);

  /* use protocol to choose a socket type */
  if(strcmp(transport, "udp") == 0 || strcmp(transport, "UDP") == 0)
    type =  SOCK_DGRAM;
  else
    type = SOCK_STREAM;

  /* allocate a socket */
  s = socket(AF_INET, type, ppe->p_proto);
  if(s == INVALID_SOCKET) {
    Error("Gagal buat soket %s %d\n", transport, GetLastError());
    WSACleanup();
  }

  // printf("init Socket OK\n");

  return s;
}

int closeSocket(SOCKET s) {
    int ret=0;

	// printf("closeSocket\n");
    ret = closesocket(s);

    /* printf("s ret %d\n", ret); */

    WSACleanup();

	// printf("closeSocket OK\n");

    return ret;
}

int connectSocket(SOCKET s, char szServer[MAX_STRING_LEN], const char *portservice) {
    char szBuf[1024];
    SOCKADDR_IN saddr;
    HOSTENT *lpHost=NULL;
    unsigned int addr;

    memset(&szBuf, '\0', sizeof(szBuf));
    memset(&saddr, '\0', sizeof(saddr));

    lpHost = gethostbyname(szServer);
    if (lpHost == NULL) {
        addr = inet_addr(szServer);
        lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
        wsprintf(szBuf, "Salah: %s tidak teridentifikasi\n", szServer);
        perror(szBuf);

        return -1;
    }

    memset(&saddr, 0, sizeof(SOCKADDR_IN));
	// printf("connectSocket\n");

    saddr.sin_family = AF_INET;
    saddr.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);

    /* map service name to port num */
    if((saddr.sin_port = htons((u_short)atoi(portservice))) == 0)
      Error("tidak bisa ambil %s service entry\n", portservice);

    if (connect(s, (PSOCKADDR)&saddr, sizeof(saddr)) != 0) {
        Error("Tidak bisa sambung soket ke %s\n", szServer);
        closesocket(s);
        WSACleanup();
        return -1;
    }

	// printf("connectSocket OK\n");

    return 0;
}

SOCKET ikatSocket(SOCKET s, const char *portservice) {
  struct sockaddr_in sin;
  struct sockaddr_in fsin;
  int  qlen = 10;

  memset(&sin, 0, sizeof(sin));
  memset(&fsin, 0, sizeof(fsin));

  sin.sin_family = AF_INET;

  /* map service name to port num */
  if((sin.sin_port = htons((u_short)atoi(portservice))) == 0)
    printf("tidak bisa ambil %s service entry\n", portservice);

  /* bind the socket */
  if(bind(s, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) {
    Error("tidak bisa bind ke %s port: %d\n", portservice, GetLastError());
    WSACleanup();
  }

  // printf(" ikatSocket: bind OK\n");

  //  if(type == SOCK_STREAM && listen(s, qlen) == SOCKET_ERROR) {
  if(listen(s, qlen) == SOCKET_ERROR) {
    Error("tidak bisa listen pada %s port: %d\n", portservice, GetLastError());
    WSACleanup();
  }

  // printf(" ikatSoket listen OK\n");

  return s;
}

SOCKET terimaSocket(SOCKET s) {
  struct sockaddr_in fsin;
  int alen = sizeof(fsin);

  fflush(stdout);
  memset(&fsin, 0, sizeof(fsin));
  s = accept(s, (struct sockaddr *)&fsin, &alen);
  
  fflush(stdout);

  // printf("terimaSocket: accept OK\n"); 

  if(s == INVALID_SOCKET) {
    Error("salah: soket accept : %d\n", GetLastError());
    WSACleanup();
    exit(1);
  }


  // printf("return sock accept\n");

  return s;
}


char *bacaSocket( SOCKET sock )
{
   char buf[512];
   char *ret;
   int n=0;
   int i=0;

   ret = NULL;
   memset(&buf, '\0', sizeof(buf));
   // printf("bacaSocket\n");

    i=0;
    if((n =recv(sock, buf, sizeof(buf), 0)) > 0) {
	  // printf("recv n : %d, buf %s\n", n, buf);

      // write(buf, sizeof(buf), n); // VC not need ??
	  // printf("buf pos %d\n",i);
	  i++;
    } else {
      strcpy(buf, "");
    }

    // printf("bacaSocket buf %s \n", buf);
	// ret = (char *)malloc(sizeof(buf));

	ret = buf;

    return ret;
}

int tulisSocket( SOCKET sock, char data[MAX_STRING_LEN] )
{
   int ret=0;

   // printf("tulisSocket\n");

   ret = send(sock, data, (int)strlen(data), 0);

   return ret;
}

/* ****************************************************** */
/* Win : CheckWeb handle                                  */
/* ****************************************************** */

char* win_checkweb(int argc, char argv[512]) {
  WSADATA            wsaData;
  struct protoent    *ppe=NULL;

  SOCKET    s;
  int       type=0;
  int       nRtn=0;
  int       ret=0;
  int       len = 0;
  unsigned   int   BUF_LEN = 512;

  const char *transport="tcp";
  char      *r = NULL;

  char ch[2];
  char *myline=NULL;

  char buf[512];
  char match_buf[512];

  SOCKADDR_IN server;
  HOSTENT *servhost = NULL;
  struct servent *service = NULL;

  char send_buf[512];              // Buffer for HTTP Protocol sending to Server
  char host[512] = "localhost";    // Connected Hostname
  char path[512] = "/";            // Request Path
  unsigned short port = 80;        // Connected Port Number
  char host_path[512] = "";

  char match_str1[512];
  char match_str2[512];
  char match_str3[512];

  memset(&ch, '\0', sizeof(ch));

  memset(&buf, '\0', sizeof(buf));
  memset(&match_buf, '\0', sizeof(match_buf));

  memset(&match_str1, '\0', sizeof(match_str1));
  memset(&match_str2, '\0', sizeof(match_str2));
  memset(&match_str3, '\0', sizeof(match_str3));

  // printf("call win_checkweb \n");

    if ( argc > 1 ){                     // if URL defined as Argument
		// printf("check strlen \n");
        if ( strlen(argv) > BUF_LEN) {
			strcpy(match_buf, "URL too long!");
			strcpy(buf, match_buf);
			WSACleanup();
			r = match_buf;
			return r;
        }
		// printf("strlen OK \n");

        /* string statement with http:// */
        /* successful to sscanf */
        /* there is other string after http://  */
 
       if ( strstr(argv, "http://") &&
             sscanf(argv, "http://%s", host_path) &&
             strcmp(argv, "http://" ) ){
             char *p='\0';

            p = strchr(host_path, '/');  /* Check separator "/" between Host and Path */
            if ( p != NULL ){
                strcpy(path, p);        /* string after "/" will be copied into path */
                *p = '\0';
                strcpy(host, host_path); /* string before "/" will be copied into host */
            } else {                     /* if no separator "/", the form will be http://host  */
                strcpy(host, host_path); /* and all string will be copied into host */
            }

            p = strchr(host, ':');       /* if there is ":" inside Hostname */
            if ( p != NULL ){
                port = atoi(p+1);        /* Get port number  */
                if ( port <= 0 ){        /* if not number (failed for atoi) or 0 */
                    port = 80;           /* set port number to be 80 */
                }
                *p = '\0';
            }
        } else {
            fprintf(stderr, "Silahkan set URL http://host/path \n");
            return "";
        }
    }

  // printf("start winsock, port %d \n", port);

  nRtn = WSAStartup(MAKEWORD(2, 0), &wsaData); // winSock 2.0
  if (nRtn != 0) {
     Error("Gagal buat Windows Soket(WSA)\n");
  }

  /* map protocol name to protocol num */
  if((ppe = getprotobyname(transport)) == 0)
    Error("Gagal ambil %s protocol entry\n", transport);

  /* use protocol to choose a socket type */
  if(strcmp(transport, "udp") == 0 || strcmp(transport, "UDP") == 0)
    type =  SOCK_DGRAM;
  else
    type = SOCK_STREAM;

  /* allocate a socket */
  s = socket(AF_INET, type, ppe->p_proto);
  if(s == INVALID_SOCKET) {
	strcpy(match_buf, "Socket Error!");
	strcpy(buf, match_buf);
	WSACleanup();
	r = match_buf;
	return r;
  }

  // printf("create socket OK \n");

    /* Getting Host Information (IP and others) */
    servhost = gethostbyname(host);
    if ( servhost == NULL ){
        fprintf(stderr, "Gagal dapat IP Address dari [%s] \n", host);
        return "";
    }

	memset(&server, 0, sizeof(SOCKADDR_IN));            /* Clear Structure */

    server.sin_family = AF_INET;
	server.sin_addr = *((LPIN_ADDR)*servhost->h_addr_list);
    /* Copy IP Addrress Structure */

	if ( port != 0 ){                          /* If port number is defined inside Argument */
        server.sin_port = htons(port);
    } else {                                   /* If not defined, get port number by getservbyname */
        service = getservbyname("http", "tcp");
        if ( service != NULL ){                /* Copy port number if successful */
            server.sin_port = service->s_port;
        } else {                               /* Set port number to be 80 if filed */
            server.sin_port = htons(80);
        }
    }

    /* Connect to server */
    if (connect(s, (PSOCKADDR)&server, sizeof(server)) != 0) {
		strcpy(match_buf, "No Connection!");
		strcpy(buf, match_buf);
		closesocket(s);
		r = match_buf;
		return r;
    }

	//printf("socket connected\n");

    /* Create HTTP Protocol and send to server */
    sprintf(send_buf, "GET %s HTTP/1.0\r\n", path);
    //write(s, send_buf, strlen(send_buf));
    ret = send(s, send_buf, (int)strlen(send_buf), 0);

    sprintf(send_buf, "Host: %s:%d\r\n", host, port);
    //write(s, send_buf, strlen(send_buf));
    ret = send(s, send_buf, (int)strlen(send_buf), 0);

    sprintf(send_buf, "\r\n");
    //write(s, send_buf, strlen(send_buf));
    ret = send(s, send_buf, (int)strlen(send_buf), 0);

    // Set Match Pattern 1
    strcpy(match_str1, "suhu");        
    // Set Match Pattern 2
    strcpy(match_str2, "cahaya");        
    // Set Match Pattern 3
    strcpy(match_str3, "stat");        

	memset(&match_buf, '\0', sizeof(match_buf));

   /* Wait for receiving message from server */
	strcpy(ch, "\n");
	while (strncmp(ch, "\0", 1) != 0){
        memset(&buf, '\0', sizeof(buf));
		memset(&ch, '\0', sizeof(ch));

		//printf("start recv ...\n", buf);

		len = recv(s, ch, 1, 0);
		myline = newString(ch);

		while (strncmp(ch, "\n", 1) != 0) {
			len = recv(s, ch, 1, 0);
			if (len == 1) {
			  myline = addString(&myline, ch);
			}
			else {
				break;
			}
		}
		chop(myline);
		strcpy(buf, myline);
		myline = NULL;

		//printf("buf: %s\n", buf);

		if (strlen(buf) > 0){

           //printf("buf: %s\n",buf);
           //printf("pattern: %s\n", match_str);

           if(winRegexBuf(buf, match_str1) == 1) {
              strcpy(match_buf, buf);
              //printf("---> Match\n");
			  break;
           } else
           if(winRegexBuf(buf, match_str2) == 1) {
              strcpy(match_buf, buf);
			  //printf("match_buf: %s\n", match_buf);
              //printf("---> Match cahaya\n");
			  break;
           } else
           if(winRegexBuf(buf, match_str3) == 1) {
              strcpy(match_buf, buf);
              //printf("---> Match switch\n");
			  break;
           } 
           else {
              //printf("---> NOT Match\n");
           }

        } 
        memset(&buf, '\0', sizeof(buf));
    }

	//printf("match_buf: %s\n", match_buf);
	flushall();

    // Close Socket
	// printf("close socket\n");
	strcpy(buf, match_buf);
    closesocket(s);

	r = match_buf;

    return r;
}


/* ****************************************************** */
/* Win: Alarm Sound & Popup handle                        */
/* ****************************************************** */
/* Kupersembahkan untuk istriku tercinta Masako,          */
/* anakku tersayang Takumi                                */
/* serta seluruh putra putri Indonesia                    */
/* ****************************************************** */

int playWave(char filename[MAX_STRING_LEN]) {
    PlaySound(filename, NULL, SND_FILENAME | SND_SYNC);

    return 0;
}

int showDialog(char msg[MAX_STRING_LEN], char title[MAX_STRING_LEN]) {

   MessageBox(NULL, msg, title, 0);

   return 0;
}

void win_openCD() {
  mciSendString( "set cdaudio door open", NULL, 0, NULL );
}

void win_closeCD() {
  mciSendString( "set cdaudio door close", NULL, 0, NULL );
}

void win_playCDaudio() {
  mciSendString( "open cdaudio", NULL, 0, NULL );
  mciSendString( "play cdaudio", NULL, 0, NULL );
}

void win_stopCDaudio() {
  mciSendString( "stop cdaudio", NULL, 0, NULL );
}

void win_pauseCDaudio() {
  mciSendString( "pause cdaudio", NULL, 0, NULL );

}

void win_resumeCDaudio() {
  mciSendString( "resume cdaudio", NULL, 0, NULL );
}

void win_playAVIMidi(char filename[256]) {
  char msg1[1024];
  char msg2[1024];

  memset(&msg1, '\0', sizeof(msg1));
  memset(&msg2, '\0', sizeof(msg2));

  sprintf(msg1, "open %s", filename);
  sprintf(msg1, "play %s", filename);

  mciSendString( msg1, NULL, 0, NULL );
  mciSendString( msg2, NULL, 0, NULL );
}

void win_stopAVIMidi(char filename[256]) {
  char msg1[1024];

  memset(&msg1, '\0', sizeof(msg1));
  sprintf(msg1, "stop %s", filename);

  mciSendString( msg1, NULL, 0, NULL );
}

void win_pauseAVIMidi(char filename[256]) {
  char msg1[1024];

  memset(&msg1, '\0', sizeof(msg1));
  sprintf(msg1, "pause %s", filename);

  mciSendString( msg1, NULL, 0, NULL );
}

void win_resumeAVIMidi(char filename[256]) {
  char msg1[1024];

  memset(&msg1, '\0', sizeof(msg1));
  sprintf(msg1, "resume %s", filename);

  mciSendString( msg1, NULL, 0, NULL );
}

/* ****************************************************** */
/* Serial RS232 handle */
/* ****************************************************** */
void InitSer(DCB dcb, HANDLE* hComm, int baud, char COM[8])
{

    if(hComm == NULL)
		return;

    *hComm = CreateFile(
        COM,                          /* COM serial port */
        GENERIC_READ | GENERIC_WRITE, /* access mode     */
        0,                            /* share mode      */
        NULL,                         /* security attrib */
        OPEN_EXISTING,                /* create flag     */
        FILE_ATTRIBUTE_NORMAL,        /* attribute       */
        NULL                          /* template handle */
    ); 
  
    GetCommState(*hComm, &dcb);       /* get DCB         */
    dcb.BaudRate = baud;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    SetCommState(*hComm, &dcb);       /* set DCB         */

}

/* Write a line to COM */
int writeSerialCom(char COM[8], char input[1024], int baudrate)
{
    DCB dcb;                          /* comm param         */
    HANDLE hComm;                     /* serial port handle */
    DWORD writesize;                  /* byte size to write */

	memset(&dcb, '\0', sizeof(dcb));
    InitSer(dcb, &hComm, baudrate, COM);
    
    chop(input);

    /* Write to Serial Port */ 
    WriteFile(hComm, input, strlen(input), &writesize, NULL); 

    CloseHandle(hComm);

    return(0);
}

/* Read a line from COM */
char *readSerialCom(char COM[8], int baudrate)
{
  DCB    dcb;
  HANDLE hComm;

  DWORD   dwCommEvent;
  DWORD   dwRead;
  TCHAR   chRead;                     /* international char */
  DWORD   dwStoredFlags;
  COMSTAT comStat;
  DWORD   dwErrors;

  int     n = 0;
  char    str[MAX_STRING_LEN];
  char    *ret;

  ret = NULL;
  memset(&str,'\0',sizeof(str));
  memset(&dcb, '\0', sizeof(dcb));
  InitSer(dcb, &hComm, baudrate, COM);

  if( hComm == INVALID_HANDLE_VALUE ) exit( 1 );

  dwStoredFlags = EV_BREAK | EV_CTS | EV_DSR | EV_ERR | EV_RING |\
                  EV_RLSD | EV_RXCHAR | EV_RXFLAG | EV_TXEMPTY ;
  if (!SetCommMask(hComm, dwStoredFlags)) {
     // Error setting communications event mask.
     printf("Serial Comm salah  : Set Event Mask\n");
     return NULL;
  }

  // Get and clear current errors on the port.
  if (!ClearCommError(hComm, &dwErrors, &comStat)) {
     // Report error in ClearCommError.
     printf("Serial Comm salah : Clear comm err\n");
     return NULL;
  }


   if (WaitCommEvent(hComm, &dwCommEvent, NULL)) {
     n = 0;
     do {
       if (ReadFile(hComm, &chRead, 1, &dwRead, NULL)) {
         printf("%c", chRead);
         str[n] = chRead;
         n++;
       } else {
         // An error occurred in the ReadFile call.
         printf("Serial Comm salah : ReadFile call\n");
         break;
       }
     } while(dwRead && chRead != '\n');
     str[n] = '\0';
   }  else {
      // Error in WaitCommEvent.
      printf("Serial Comm salah : WaitCommEvent\n");
   }

  CloseHandle(hComm);

  ret = (char *)malloc(sizeof(str));
  ret = str;

  return ret;
}


/* ****************************************************** */
/* Win : SendMail handle                                  */
/* ****************************************************** */

int win_sendMail(char szServer[64], char szPort[8],
    char mailfrom[128], char mailto[1024], char subject[256], char body[4096])
{
    char szBuf[1024],                            /* message from svr */
         send_mesg[4096];                        /* message to svr */
    u_int port;
    WSADATA wsaData;
    int nRtn=0;
    SOCKET s;
    SOCKADDR_IN saddr;
    HOSTENT *lpHost=NULL;
    unsigned int addr;

    memset(szBuf, '\0', sizeof(szBuf));
	memset(send_mesg, '\0', sizeof(send_mesg));

    port = (u_int)atoi(szPort);
    // if(isDEBUG == 1) printf("port : %d\n", port);

    nRtn = WSAStartup(MAKEWORD(1, 1), &wsaData);
    if (nRtn != 0) {
       perror("Gagal buat Windows Soket(WSA)\n");
       return -1;
    }

    s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        perror("Gagal buat Soket\n");
        WSACleanup();
        return -2;
    }

    lpHost = gethostbyname(szServer);
    if (lpHost == NULL) {
        addr = inet_addr(szServer);
        lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
        wsprintf(szBuf, "%s tidak teridentifikasi\n", szServer);
        perror(szBuf);
        return -3;
    }
    memset(&saddr, 0, sizeof(SOCKADDR_IN));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);

    if (connect(s, (PSOCKADDR)&saddr, sizeof(saddr)) != 0) {
        perror("Tidak bisa sambung ke mail server\n");
        closesocket(s);
        WSACleanup();
        return -4;
    }

    memset(szBuf, '\0', sizeof(szBuf));
    memset(send_mesg, '\0', sizeof(send_mesg));

    // if(isDEBUG == 1) printf("start mail ...\n");
                /* get welcome response */
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);

    if (strstr(szBuf, "220") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    strcpy(send_mesg, "HELO SERVER\n");
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);
    if (strstr(szBuf, "250") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    memset(send_mesg, '\0', sizeof(send_mesg));
    sprintf(send_mesg,"MAIL FROM: %s\r\n", mailfrom);
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);
    if (strstr(szBuf, "250") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    memset(send_mesg, '\0', sizeof(send_mesg));
    sprintf(send_mesg,"RCPT TO: %s\r\n", mailto);
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);
    if (strstr(szBuf, "250") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    memset(send_mesg, '\0', sizeof(send_mesg));
    strcpy(send_mesg, "DATA\n");
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);
    if (strstr(szBuf, "354") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    memset(send_mesg, '\0', sizeof(send_mesg));
    sprintf(send_mesg,"To: %s\r\n", mailto);
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(send_mesg, '\0', sizeof(send_mesg));
    sprintf(send_mesg,"Subject: %s\r\n\n", subject);  // need \n\n
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(send_mesg, '\0', sizeof(send_mesg));
    sprintf(send_mesg,"%s\r\n", body);
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(send_mesg, '\0', sizeof(send_mesg));
    strcpy(send_mesg, "\r\n.\n");
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);
    if (strstr(szBuf, "250") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    strcpy(szBuf, "QUIT\r\n");
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);

    closesocket(s);
    WSACleanup();

    return 0;
}

// For WebMail 2015
int win_sendMail2(char szServer[64], char szPort[8], char pass[1024],
	char mailfrom[128], char mailto[1024], char subject[256], char body[4096])
{
	char szBuf[1024],                            /* message from svr */
		send_mesg[4096];                         /* message to svr */
	u_int port;
	WSADATA wsaData;
	int nRtn = 0;
	SOCKET s;
	SOCKADDR_IN saddr;
	HOSTENT *lpHost = NULL;
	unsigned int addr;

	memset(szBuf, '\0', sizeof(szBuf));
	memset(send_mesg, '\0', sizeof(send_mesg));

	port = (u_int)atoi(szPort);
	// printf("port : %d\n", port);

	// printf("WebMail capable ...\n");

	nRtn = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if (nRtn != 0) {
		perror("Gagal buat Windows Soket(WSA)\n");
		return -1;
	}

	s = socket(PF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		perror("Gagal buat Soket\n");
		WSACleanup();
		return -2;
	}

	lpHost = gethostbyname(szServer);
	if (lpHost == NULL) {
		addr = inet_addr(szServer);
		lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
		wsprintf(szBuf, "%s tidak teridentifikasi\n", szServer);
		perror(szBuf);
		return -3;
	}
	memset(&saddr, 0, sizeof(SOCKADDR_IN));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);

	if (connect(s, (PSOCKADDR)&saddr, sizeof(saddr)) != 0) {
		perror("Tidak bisa sambung ke mail server\n");
		closesocket(s);
		WSACleanup();
		return -4;
	}

	memset(szBuf, '\0', sizeof(szBuf));
	memset(send_mesg, '\0', sizeof(send_mesg));

	// if(isDEBUG == 1) printf("start mail ...\n");
	/* get welcome response */
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);

	if (strstr(szBuf, "220") != szBuf) {              // OK 220
		perror("Mail server tidak merespon OK\n");
	}

	strcpy(send_mesg, "EHLO MAIL.SERVER.COM\n");
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);
	if (strstr(szBuf, "250") != szBuf) {              // OK 220
		perror("(EHLO) Mail server tidak merespon OK\n");
	}

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "AUTH PLAIN %s\r\n", pass);
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// printf(szBuf);
	if (strstr(szBuf, "235") != szBuf) {              // OK 235
		printf("(AUTH PLAIN) Auth Salah. Mail server tidak merespon OK\n");
	}

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "MAIL FROM: %s\r\n", mailfrom);
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);
	if (strstr(szBuf, "250") != szBuf) {              // OK 220
		perror("(MAIL FROM) Mail server tidak merespon OK\n");
	}

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "RCPT TO: %s\r\n", mailto);
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);
	if (strstr(szBuf, "250") != szBuf) {              // OK 220
		perror("(RCPT TO) Mail server tidak merespon OK\n");
	}

	memset(send_mesg, '\0', sizeof(send_mesg));
	strcpy(send_mesg, "DATA\n");
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// printf(szBuf);
	if (strstr(szBuf, "354") != szBuf) {              // OK 220
		perror("(DATA )Mail server tidak merespon OK\n");
	}

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "To: %s\r\n", mailto);
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "Subject: %s\r\n\n", subject);  // need \n\n
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(send_mesg, '\0', sizeof(send_mesg));
	sprintf(send_mesg, "%s\r\n", body);
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(send_mesg, '\0', sizeof(send_mesg));
	strcpy(send_mesg, "\r\n.\r\r\n\0");
	send(s, send_mesg, (int)strlen(send_mesg), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// printf(szBuf);
	if (strstr(szBuf, "250") != szBuf) {              // OK 220
		perror("Mail server tidak merespon OK\n");
	}

	strcpy(szBuf, "QUIT\r\n");
	send(s, szBuf, (int)strlen(szBuf), 0);

	memset(szBuf, '\0', sizeof(szBuf));
	recv(s, szBuf, (int)sizeof(szBuf)-1, 0);
	// if(isDEBUG == 1) printf(szBuf);

	closesocket(s);
	WSACleanup();

	return 0;
}

/* ************************************************* */
#endif
/* ************************************************* */

