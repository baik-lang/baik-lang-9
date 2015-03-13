// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

#include <pthread.h>

typedef struct {
  char myfile[256];
  int  num;
} TH_BOX;

#ifdef WINDOWS
#include "hariswav.h"
#else

#ifdef USE_MIKMOD
#include <unistd.h>
#include <mikmod.h>
#include "mikmod_playwav.h"
#elif USE_ALSA
#include "alsa_play_sound.h"
#else
#include "ux_hariswav.h"
#endif

#endif

void keyMusikBGM ()
{
  char      tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat;

  pthread_t pt;

  TH_BOX    * arg_bgm=NULL;
  
  char   get_name[MAX_STRING_LEN];

  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];


  memset(&valdat, '\0', sizeof(valdat));
  memset(&get_name, '\0', sizeof(get_name));
  
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  arg_bgm = malloc(sizeof(TH_BOX));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              strcpy(arg_bgm->myfile, lex.detail.string);
              arg_bgm->num = 1;

              #ifdef WINDOWS
                pthread_create( &pt, NULL, &play_BGM, arg_bgm);
              #else
              
              #ifdef USE_MIKMOD
                pthread_create( &pt, NULL, &mikmod_play_BGM, arg_bgm); 
              #elif USE_ALSA
                pthread_create( &pt, NULL, &alsa_play_BGM, arg_bgm);                 
              #else
                // printf ("before: %s\n", arg_bgm->myfile);
                pthread_create( &pt, NULL, &ux_play_BGM, arg_bgm);
              #endif
              
              #endif

	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:
	    case TYPE_NUM:

              //printf("curr class : %s\n", currentClass);
              //printf("datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
              } else {
                valdat = ValLabel(lex.detail.string, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                strcpy(arg_bgm->myfile, valdat.str);
                arg_bgm->num = 1;              
              
                #ifdef WINDOWS
                pthread_create( &pt, NULL, &play_BGM, arg_bgm);                
                #else

                #ifdef USE_MIKMOD
                pthread_create( &pt, NULL, &mikmod_play_BGM, arg_bgm);                 
                #elif USE_ALSA
                pthread_create( &pt, NULL, &alsa_play_BGM, arg_bgm);                                 
                #else
                pthread_create( &pt, NULL, &ux_play_BGM, arg_bgm);                
                #endif
                
                #endif
              }
              break;

	    default:
	      Error("kode perintah MUSIK salah");
	    }
	  getlex();

	ungetlex();

}

/////////////////////////////////////////////////////////

void keyMusik ()
{
  char   tmpMsg[MAX_STRING_LEN * 2];
  VAL_LABEL valdat;
  
  char   get_name[MAX_STRING_LEN];


  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];


  memset(&valdat, '\0', sizeof(valdat));

  memset(&get_name, '\0', sizeof(get_name));
  
  memset(&tmpMsg, '\0', sizeof(tmpMsg));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));


	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:

              #ifdef WINDOWS
	          playWave( lex.detail.string );
	          
	      #else
	      
              #if USE_MIKMOD
                  printf("use mikmod\n");
                  mymikmod_play( lex.detail.string );
              #elif USE_ALSA
                  printf("use alsa\n");              
                  alsa_play_son( lex.detail.string );                  
	      #else
                  printf("use dsp\n");	      
                  ux_play_wave( lex.detail.string );
              #endif

              #endif
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:
	    case TYPE_NUM:

              //printf("curr class : %s\n", currentClass);
              //printf("datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
              } else {
                valdat = ValLabel(lex.detail.string, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                #ifdef WINDOWS
                playWave( valdat.str );
                
                #else
                
                #if USE_MIKMOD
                mymikmod_play( valdat.str );
                #elif USE_ALSA
                alsa_play_son( valdat.str );                
                #else
                ux_play_wave (valdat.str );
                #endif
                
                #endif
              }
              break;

	    default:
	      Error("kode perintah MUSIK salah");
	    }
	  getlex();

	ungetlex();

}


void keyJendela ()
{

  char tmpMsg[MAX_STRING_LEN * 2];

  int  n=0, i=0;

  char popupmsg[1024],
       poptitle[1024];


  VAL_LABEL valdat,tmpdat;
  
  int    idx=0;                           // array index

  int    isArrDummy=0;

  int    size = 0;
  char   get_name[MAX_STRING_LEN];


  // var list for class params
  struct  node_list tmpnode;
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&get_name, '\0', sizeof(get_name));

  memset(&tmpnode, '\0', sizeof(tmpnode));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  memset(popupmsg, '\0', sizeof(popupmsg));
  memset(poptitle, '\0', sizeof(poptitle));

  n = 0;

	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 0) {
                strcpy(popupmsg, lex.detail.string );
              } else if(n == 1) {
                strcpy(poptitle, lex.detail.string );
              } 

	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              //printf("curr class : %s\n", currentClass);
              //printf("datatype : %d\n", valdat.datatype);
              //printf("\nval : %d\n", valdat.val);
              //printf("str : %s\n", valdat.str);

              if(currentClass != NULL && strlen(currentClass) > 0) {
                sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.string);
                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, class_sub_deep, valdat, VAL_FLAG_SEARCH_R );
              } else {
                valdat = ValLabel(lex.detail.string, sub_deep, valdat, VAL_FLAG_SEARCH_R );
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.str != '\0' && strlen(valdat.str) > 0) {
                sprintf(tmpMsg, "%s" , valdat.str );

                if(n == 0) {
                  strcpy(popupmsg, tmpMsg );
                } else if(n == 1) {
                  strcpy(poptitle, tmpMsg );
                } 

              }

	      break;

	    default:
	      Error("bentuk perintah JENDELA salah");
	    }

          n++;

	  getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


        if(n != 2) {
          Error("parameter JENDELA tidak lengkap");
        } else {

         #ifdef WINDOWS
         showDialog(popupmsg, poptitle);
         #else

         #endif

        }

	ungetlex();

}

