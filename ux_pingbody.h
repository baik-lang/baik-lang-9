
// ////////////////////////////////////////////////////
// ICMP
// Copyright(c) Haris Hasanudin 2005
// ////////////////////////////////////////////////////

// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2010
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


#include <time.h>
#include "haris_ping.h"

int Ping_ux(char pstrHost[256], int num_exec, int mytimeout);
void ReportError(char *pstrFrom);
int  WaitForEchoReply(int s, int mytimeout);
u_short in_cksum(u_short *addr, int len);

int SendEchoRequest(int, struct sockaddr_in);
int RecvEchoReply(int, struct sockaddr_in *, u_char *);


// Ping()
// SendEchoRequest()
int Ping_ux(char pstrHost[256], int num_exec, int mytimeout)
{
	int	  rawSocket;
	struct    hostent   *lpHost;
	struct    sockaddr_in saDest;
	struct    sockaddr_in saSrc;
	char      *from;
	int	  dwTimeSent;
	int	  dwElapsed;
	u_char    cTTL;
	int       nLoop;
	int       nRet;

	char      logMsg[1024];
	time_t    present;
    char      repHost[256];
    int       failed=0;

	rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (rawSocket < 0) 
	{
		ReportError("tidak bisa buat socket()");
		return 0;
	}
	
	lpHost = gethostbyname(pstrHost);
	if (lpHost == NULL)
	{
        fprintf(stderr,"\nHost tidak ditemukan: %s\n", pstrHost);
	    return 0;
	}
	
	saDest.sin_addr.s_addr = inet_addr(pstrHost);
	saDest.sin_family = AF_INET;
	saDest.sin_port = 0;

 	sprintf(logMsg, "Ping %s [%s] dengan %d bytes data",
				pstrHost,
				inet_ntoa(saDest.sin_addr),
				REQ_DATASIZE);

	printf("\nPing %s [%s] dengan %d bytes data:\n",
				pstrHost,
				inet_ntoa(saDest.sin_addr),
				REQ_DATASIZE);

	for (nLoop = 0; nLoop < num_exec; nLoop++)
	{
		SendEchoRequest(rawSocket, saDest);
		
		nRet = WaitForEchoReply(rawSocket, mytimeout);
               
		if (nRet < 0)
		{
			ReportError("socket error\n");
                        failed = 1;
			continue;
		}
		if (!nRet)
		{
			fprintf(stderr,"%s TimeOut\n", pstrHost);
                        failed = 1;
			continue;
		}

		dwTimeSent = RecvEchoReply(rawSocket, &saSrc, &cTTL);
                
                present = time(NULL);
		dwElapsed = (present) - dwTimeSent;

                memset(&repHost[0],'\0',sizeof(repHost));
                sprintf(repHost, "%s", inet_ntoa(saSrc.sin_addr));
                // printf("from: %s\n", repHost); 

            if(!strcmp(repHost, pstrHost)) {
              sprintf(logMsg, "Respon dari: %s: bytes=%d time=%dms TTL=%d", 
                 inet_ntoa(saSrc.sin_addr), 
                 REQ_DATASIZE,
                 dwElapsed,
                 cTTL);

               printf("\nRespon dari: %s: bytes=%d time=%dms TTL=%d", 
                     inet_ntoa(saSrc.sin_addr), 
                     REQ_DATASIZE,
                     dwElapsed,
                     cTTL);
            } else {
              printf("Dari %s Tujuan Host %s tidak bisa dijangkau\n", repHost,pstrHost);
              failed = 1;
            }

	}
	printf("\n");

    nRet = close(rawSocket);
    if (nRet < 0) {
        ReportError("closesocket()");
        return 0;
    } else {
        if(failed == 1)
          return 0;
        else 
          return 1;
    }
}

int SendEchoRequest(int s, struct sockaddr_in lpstToAddr) 
{
	static ECHOREQUEST echoReq;
	static nId = 1;
	static nSeq = 1;
	int nRet=0;
	time_t present;

	echoReq.icmpHdr.Type		= ICMP_ECHOREQ;
	echoReq.icmpHdr.Code		= 0;
	echoReq.icmpHdr.Checksum	= 0;
	echoReq.icmpHdr.ID			= nId++;
	echoReq.icmpHdr.Seq			= nSeq++;

	for (nRet = 0; nRet < REQ_DATASIZE; nRet++)
		echoReq.cData[nRet] = ' '+nRet;

        present = time(NULL);
	echoReq.dwTime	= present;

	echoReq.icmpHdr.Checksum = in_cksum((u_short *)&echoReq, sizeof(ECHOREQUEST));
	
	nRet = sendto(s, &echoReq, 
               sizeof(ECHOREQUEST), 0,
               (struct sockaddr *)&lpstToAddr, sizeof(struct sockaddr_in));

	if (nRet < 0) 
		ReportError("sendto()");
	return (nRet);
}


// RecvEchoReply()
int RecvEchoReply(int s, struct sockaddr_in *fr, u_char *pTTL) 
{
	ECHOREPLY echoReply;
	int nRet=0;
	char *from=NULL;
        struct sockaddr_in lpsaFrom;
	int nAddrLen = sizeof(lpsaFrom);

	nRet = recvfrom(s,
			&echoReply,
			sizeof(ECHOREPLY),
			0,
			(struct sockaddr *)&lpsaFrom,
			&nAddrLen);

	if (nRet < 0) 
		ReportError("recvfrom()");

        from = inet_ntoa(lpsaFrom.sin_addr);
        // printf("from : %s\n", from);

        *fr = lpsaFrom;
	*pTTL = echoReply.ipHdr.TTL;
	return (echoReply.echoRequest.dwTime);   		
}

void ReportError(char *pWhere)
{
    char *logMsg = "";

    fprintf(stderr, "\n%s ping error\n", pWhere);

    sprintf(logMsg, "%s ping error ", pWhere);
}


// WaitForEchoReply()
int WaitForEchoReply(int s, int mytimeout)
{
    struct timeval Timeout;
    fd_set readfds;
    fd_set fds;

    FD_ZERO(&readfds);
    FD_SET(s, &readfds);

    memcpy(&fds, &readfds, sizeof(readfds));

    Timeout.tv_sec  = mytimeout;
    Timeout.tv_usec = 0; 

    return(select(FD_SETSIZE, &fds, NULL, NULL, &Timeout));
}


//
// Mike Muuss' in_cksum() function
// and his comments from the original
// ping program
//
// * Author -
// *	Mike Muuss
// *	U. S. Army Ballistic Research Laboratory
// *	December, 1983

/*
 *			I N _ C K S U M
 *
 * Checksum routine for Internet Protocol family headers (C Version)
 *
 */
u_short in_cksum(u_short *addr, int len)
{
	register int nleft = len;
	register u_short *w = addr;
	register u_short answer;
	register int sum = 0;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
	 */
	while( nleft > 1 )  {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if( nleft == 1 ) {
		u_short	u = 0;

		*(u_char *)(&u) = *(u_char *)w ;
		sum += u;
	}

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}

