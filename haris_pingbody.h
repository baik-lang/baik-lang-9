// ////////////////////////////////////////////////////
// Copyright(c) Haris Hasanudin 2005
// ////////////////////////////////////////////////////

// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


#include <time.h>
#include "haris_ping.h"

int Ping_win(LPCSTR pstrHost, int num_exec, int mytimeout);
void ReportError(LPCSTR pstrFrom);
int  WaitForEchoReply(SOCKET s, int mytimeout);
u_short in_cksum(u_short *addr, int len);

int	SendEchoRequest(SOCKET, LPSOCKADDR_IN);
DWORD	RecvEchoReply(SOCKET, LPSOCKADDR_IN, u_char *);


int Ping_win(LPCSTR pstrHost, int num_exec, int mytimeout)
{
    WSADATA   wsaData;

	SOCKET	  rawSocket;
	LPHOSTENT lpHost;
	struct    sockaddr_in saDest;
	struct    sockaddr_in saSrc;
	DWORD	  dwTimeSent;
	DWORD	  dwElapsed;
	u_char    cTTL;
	int       nLoop;
	int       nRet;

	char      logMsg[1024];
    int       failed = 0;

    nRet = WSAStartup(MAKEWORD(1, 1), &wsaData);
    if (nRet != 0) {
      ReportError("Gagal buat Windows Soket(WSA)\n");
	  return 0;
    }
	
	rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	if (rawSocket == INVALID_SOCKET) 
	{
        WSACleanup();
		ReportError("tidak bisa buat socket()");
	    return 0;
	}
	// printf("rawSocket OK\n");
	
	lpHost = gethostbyname(pstrHost);
	if (lpHost == NULL)
	{
        fprintf(stderr,"\nHost not found: %s\n", pstrHost);
	    return 0;
	}
	// printf("gethostbyname OK\n");	

	saDest.sin_addr.s_addr = *((u_long FAR *) (lpHost->h_addr));
	saDest.sin_family = AF_INET;
	saDest.sin_port = 0;

    #ifdef VISUALC
	sprintf_s(logMsg, sizeof(logMsg), "Pinging %s [%s] with %d bytes of data",
				pstrHost,
				inet_ntoa(saDest.sin_addr),
				REQ_DATASIZE);
    #else
 	sprintf(logMsg, "Pinging %s [%s] with %d bytes of data",
				pstrHost,
				inet_ntoa(saDest.sin_addr),
				REQ_DATASIZE);
    #endif


	printf("\nPing %s [%s] dengan %d bytes data:\n",
				pstrHost,
				inet_ntoa(saDest.sin_addr),
				REQ_DATASIZE);

	for (nLoop = 0; nLoop < num_exec; nLoop++)
	{
		SendEchoRequest(rawSocket, &saDest);

		nRet = WaitForEchoReply(rawSocket, mytimeout);

		if (nRet == SOCKET_ERROR)
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

		dwElapsed = GetTickCount() - dwTimeSent;

        #ifdef VISUALC
        sprintf_s(logMsg, sizeof(logMsg), "Respon dari: %s: bytes=%d time=%ldms TTL=%d", 
               inet_ntoa(saSrc.sin_addr), 
			   REQ_DATASIZE,
               dwElapsed,
               cTTL);
        #else
        sprintf(logMsg, "Reply from: %s: bytes=%d time=%ldms TTL=%d", 
               inet_ntoa(saSrc.sin_addr), 
			   REQ_DATASIZE,
               dwElapsed,
               cTTL);
        #endif

		printf("\nRespon dari: %s: bytes=%d time=%ldms TTL=%d", 
               inet_ntoa(saSrc.sin_addr), 
			   REQ_DATASIZE,
               dwElapsed,
               cTTL);
	}
	printf("\n");
	nRet = closesocket(rawSocket);

    WSACleanup();

	if (nRet == SOCKET_ERROR) {
           ReportError("closesocket()");
           return 0;
    } else {
          if(failed == 1)
            return 0;
          else 
            return 1;
    }

}

int SendEchoRequest(SOCKET s,LPSOCKADDR_IN lpstToAddr) 
{
	static ECHOREQUEST echoReq;
	static nId = 1;
	static nSeq = 1;
	int nRet;

	echoReq.icmpHdr.Type		= ICMP_ECHOREQ;
	echoReq.icmpHdr.Code		= 0;
	echoReq.icmpHdr.Checksum	= 0;
	echoReq.icmpHdr.ID			= nId++;
	echoReq.icmpHdr.Seq			= nSeq++;

	for (nRet = 0; nRet < REQ_DATASIZE; nRet++)
		echoReq.cData[nRet] = ' '+nRet;

	echoReq.dwTime				= GetTickCount();

	echoReq.icmpHdr.Checksum = in_cksum((u_short *)&echoReq, sizeof(ECHOREQUEST));

	nRet = sendto(s,
				 (LPSTR)&echoReq,
				 sizeof(ECHOREQUEST),
				 0,
				 (LPSOCKADDR)lpstToAddr,
				 sizeof(SOCKADDR_IN));

	if (nRet == SOCKET_ERROR) 
		ReportError("sendto()");
	return (nRet);
}

DWORD RecvEchoReply(SOCKET s, LPSOCKADDR_IN lpsaFrom, u_char *pTTL) 
{
	ECHOREPLY echoReply;
	int nRet;
	int nAddrLen = sizeof(struct sockaddr_in);

	nRet = recvfrom(s,
					(LPSTR)&echoReply,
					sizeof(ECHOREPLY),
					0,
					(LPSOCKADDR)lpsaFrom,
					&nAddrLen);

	if (nRet == SOCKET_ERROR) 
		ReportError("recvfrom()");

	*pTTL = echoReply.ipHdr.TTL;
	return(echoReply.echoRequest.dwTime);   		
}

void ReportError(LPCSTR mymsg)
{
    char *logMsg = "";

	//fprintf(stderr, "\n%s ping error: %d\n",  WSAGetLastError());
	//sprintf(logMsg, "%s ping error : %d",  WSAGetLastError());

	fprintf(stderr, "\n%s : %d\n",  mymsg, WSAGetLastError());
	sprintf(logMsg, "%s : %d",  mymsg, WSAGetLastError());
}


int WaitForEchoReply(SOCKET s, int mytimeout)
{
    struct timeval Timeout;
    fd_set readfds;

    readfds.fd_count = 1;
    readfds.fd_array[0] = s;

    Timeout.tv_sec  = mytimeout;  // 5 secs
    Timeout.tv_usec = 0;          // mili sec

    return(select(1, &readfds, NULL, NULL, &Timeout));
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

