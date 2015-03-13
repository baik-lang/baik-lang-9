// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

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

    printf("s %s p %d \n", szServer, port);

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

    printf("svr: %s\n", szBuf);

    if (strstr(szBuf, "220") != szBuf) {              // OK 220
        perror("Mail server tidak merespon OK\n");
    }

    strcpy(send_mesg, "HELO SERVER\n");
    send(s, send_mesg, (int)strlen(send_mesg), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    // if(isDEBUG == 1) printf(szBuf);

    printf("svr: %s\n", szBuf);

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

/* ************************************************* */
#endif
/* ************************************************* */

