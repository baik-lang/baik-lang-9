// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// ..............................................................



/* ************************************************* */
#ifndef WINDOWS
/* ************************************************* */

char* ux_checkweb(int argc, char argv[512]);

int ux_initSocket(const char *transport);
int ux_closeSocket(int s);
int ux_connectSocket(int s, char *szServer, const char *portservice);
int ux_ikatSocket(int s, const char *portservice);
int ux_terimaSocket(int s);
char *ux_bacaSocket( int sock );
int ux_tulisSocket( int sock, char data[MAX_STRING_LEN] );

int ux_sendMail(char szServer[64], char szPort[8],
    char mailfrom[128], char mailto[1024], char subject[256], char body[4096]);

int ux_sendMail2(char szServer[64], char szPort[8], char pass[1024],
	char mailfrom[128], char mailto[1024], char subject[256], char body[4096]);

int unixRegexBuf(const char *string, char *pattern);

/* ************************************************* */
#else
/* ************************************************* */
int winRegexBuf(char sbuf[MAX_STRING_LEN*4], char *regex);

char* win_checkweb(int argc, char argv[512]);

SOCKET initSocket(const char *transport);
int closeSocket(SOCKET s);
int connectSocket(SOCKET s, char szServer[MAX_STRING_LEN], const char *portservice);
SOCKET ikatSocket(SOCKET s, const char *portservice);
SOCKET terimaSocket(SOCKET s);
char *bacaSocket( SOCKET sock );
int tulisSocket( SOCKET sock, char data[MAX_STRING_LEN] );

int playWave(char filename[MAX_STRING_LEN]);
int showDialog(char msg[MAX_STRING_LEN], char title[MAX_STRING_LEN]);

void win_openCD();
void win_closeCD();

void win_playCDaudio();
void win_stopCDaudio();
void win_pauseCDaudio();
void win_resumeCDaudio();

void win_playAVIMidi(char filename[256]);
void win_stopAVIMidi(char filename[256]);
void win_pauseAVIMidi(char filename[256]);
void win_resumeAVIMidi(char filename[256]);

void InitSer(DCB dcb, HANDLE* hComm, int baud, char COM[8]);
int writeSerialCom(char COM[8], char input[1024], int baudrate);
char *readSerialCom(char COM[8], int baudrate);

int win_sendMail(char szServer[64], char szPort[8],
    char mailfrom[128], char mailto[1024], char subject[256], char body[4096]);

int win_sendMail2(char szServer[64], char szPort[8], char pass[1024],
	char mailfrom[128], char mailto[1024], char subject[256], char body[4096]);

/* ************************************************* */
#endif
/* ************************************************* */

