// Playing Wav using Alsa Sound Library
// Copyright Haris Hasanudin 2015

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
 
#include <alsa/asoundlib.h>

typedef  struct
{
u_int32_t  dwSize ;
u_int16_t  wFormatTag ;
u_int16_t  wChannels ;
u_int32_t  dwSamplesPerSec ;
u_int32_t  dwAvgBytesPerSec ;
u_int16_t  wBlockAlign ;
u_int16_t  wBitsPerSample ;
} WAVEFORMAT ;


#if WORDS_BIGENDIAN
#define SwapLE16(x) ((((u_int16_t)x)<<8)|(((u_int16_t)x)>>8))
#define SwapLE32(x) ((((u_int32_t)x)<<24)|((((u_int32_t)x)<<8)&0x00FF0000) \
                     |((((u_int32_t)x)>>8)&0x0000FF00)|(((u_int32_t)x)>>24))
#else
#define SwapLE16(x) (x)
#define SwapLE32(x) (x)
#endif



#define BUFF_SIZE_SND_ALSA 1024

int alsa_play_son(const char * nom_fic_a_jouer);

void * alsa_play_BGM( void * arg )
{
   TH_BOX * arg_bgm = (TH_BOX * ) arg;
   char   *fname=NULL;

   fname = arg_bgm->myfile;

   // printf("inside: %s\n", arg_bgm->myfile);

   pthread_detach ( pthread_self() );
   
   alsa_play_son( arg_bgm->myfile );

   //printf( "\nselesai.\n" );
   
   if(arg_bgm != NULL)
     free (arg_bgm);
   
  return 0;
}


char * alsa_find_chunk(char* pstart,const char* fourcc, size_t n)
{
char *pend ;
int k,test;

pend=pstart + n ;
while (pstart < pend)
  {
  if (*pstart == *fourcc)       /* found match for first char*/
    {
    test = TRUE ;
    for (k = 1 ; fourcc [k] != 0 ; k++)
       test = (test ? ( pstart [k] == fourcc [k] ) : FALSE) ;
    if (test)
      return  pstart ;
    } ; /* if*/
  pstart ++ ;
  } ; /* while lpstart*/
return  NULL ;
}





int alsa_init_son(FILE * fic_son,const char * nom_fic_a_jouer,
              snd_pcm_t ** adr_handle,snd_pcm_uframes_t * adr_buffer_size,
              size_t * adr_bits_per_frame,u_long * adr_datastart)
{
char buffer[BUFF_SIZE_SND_ALSA];
//size_t chunk_bytes;
char *device ;                        /* playback device */
//snd_pcm_uframes_t chunk_size;
size_t bits_per_sample;
WAVEFORMAT waveformat ;
u_long samples;
char * ptr;
u_long databytes;
snd_pcm_format_t format;
snd_pcm_hw_params_t * params;
int err;


// a partager
snd_pcm_t *handle;
snd_pcm_uframes_t buffer_size;
size_t bits_per_frame;
u_long datastart;

//device = strdup("plughw:0,0");      /* playback device */
device=strdup("default");           /* playback device */



if ( fseek(fic_son,0,SEEK_SET) != 0 )
  {
  printf("Salah, Rewinding WAV file %s\n",nom_fic_a_jouer);
  return 101;           /* Wav file must be seekable device */
  }
fread(buffer,BUFF_SIZE_SND_ALSA,1,fic_son) ;

if (alsa_find_chunk(buffer,"RIFF",BUFF_SIZE_SND_ALSA) != buffer)
  {
  fprintf(stdout,"Salah format: tidak ditemukan RIFF file marker\n");   // wwg Report error
  return  102;
  }
if (! alsa_find_chunk(buffer,"WAVE",BUFF_SIZE_SND_ALSA))
  {
  fprintf(stdout,"Salah format: tidak ditemukan WAVE file marker\n");
  return 103;
  }
ptr=alsa_find_chunk(buffer, "fmt ",BUFF_SIZE_SND_ALSA) ;
if (! ptr)
  {
  fprintf(stdout,"Salah format: tidak ditemukan 'fmt' file marker\n");  /* wwg:report error */
  return 104;
  }

ptr+=4 ;      /* Move past "fmt ".*/
memcpy (&waveformat, ptr, sizeof (WAVEFORMAT)) ;
waveformat.dwSize = SwapLE32(waveformat.dwSize);
waveformat.wFormatTag = SwapLE16(waveformat.wFormatTag) ;
waveformat.wChannels = SwapLE16(waveformat.wChannels) ;
waveformat.dwSamplesPerSec = SwapLE32(waveformat.dwSamplesPerSec) ;
waveformat.dwAvgBytesPerSec = SwapLE32(waveformat.dwAvgBytesPerSec) ;
waveformat.wBlockAlign = SwapLE16(waveformat.wBlockAlign) ;
waveformat.wBitsPerSample = SwapLE16(waveformat.wBitsPerSample) ;


ptr=alsa_find_chunk(buffer,"data",BUFF_SIZE_SND_ALSA) ;
if (! ptr)
  {
  fprintf(stdout,"Salah format: tidak ditemukan 'data' file marker\n");      /* wwg:report error */
  return 105;
  }

ptr+=4 ;      /* Move past "data".*/
memcpy(&databytes, ptr, sizeof (u_long)) ;

samples    = databytes / waveformat.wBlockAlign ;
datastart  = ((u_long) (ptr + 4)) - ((u_long) (&(buffer[0]))) ;

switch (waveformat.wBitsPerSample)
  {
  case 8:
    format=SND_PCM_FORMAT_U8 ;
    break;
  case 16:
    format=SND_PCM_FORMAT_S16_LE ;
    break;
  case 32 :
    format=SND_PCM_FORMAT_S32_LE;
    break;
  default :
    fprintf(stdout,"Salah format: %i bits perseconds\n",waveformat.wBitsPerSample ); // wwg: report error
    return 106;
    break;
  }


snd_pcm_hw_params_alloca(&params);
if ((err=snd_pcm_open (&handle, device,SND_PCM_STREAM_PLAYBACK,SND_PCM_ASYNC)) < 0)
  {
  fprintf(stdout, "tidak bisa buka audio device %s (%s)\n",device,snd_strerror (err));
  return 107;
  }
if ((err=snd_pcm_nonblock(handle, 1))< 0)
{
fprintf(stdout,"nonblock setting error: %s", snd_strerror(err));
return 108;
}
    /* Init hwparams with full configuration space */
if (snd_pcm_hw_params_any(handle, params)<0)
  {
  fprintf(stdout, "tidak bisa konfigurasi PCM device.\n");
  return 109;
  }
err=snd_pcm_hw_params_set_access(handle,params,SND_PCM_ACCESS_RW_INTERLEAVED);
if (err<0)
  {
  fprintf(stdout,"tidak tersedia Access type");
  return 110;
  }
err=snd_pcm_hw_params_set_format(handle, params, format);
if (err < 0)
  {
  fprintf(stdout,"tidak tersedia Sample format");
  return 111;
  }
err=snd_pcm_hw_params_set_channels(handle,params,waveformat.wChannels);
if (err < 0)
  {
  fprintf(stdout,"tidak tersedia Channels count");
  return 112;
  }
err=snd_pcm_hw_params_set_rate_near(handle,params,&waveformat.dwSamplesPerSec, 0);
if (err < 0)
  {
  fprintf(stdout,"Unable to set rate : %d",waveformat.dwSamplesPerSec);
  return 113;
  }
assert(err >= 0);
err=snd_pcm_hw_params(handle,params);
if (err < 0)
  {
  fprintf(stdout,"tidak bisa instal hw params:");
  return 114;
  }
//chunk_size = 0;
buffer_size=0;
snd_pcm_hw_params_get_buffer_size(params,&buffer_size);
//snd_pcm_hw_params_get_period_size(params,&chunk_size,0);
bits_per_sample=snd_pcm_format_physical_width(format);

bits_per_frame=bits_per_sample*waveformat.wChannels;
//chunk_bytes=chunk_size*bits_per_frame/8;
*adr_handle=handle;
*adr_buffer_size=buffer_size;
*adr_bits_per_frame=bits_per_frame;
*adr_datastart=datastart;
return 0;
}






int alsa_play_son(const char * nom_fic_a_jouer)
{
int err;
FILE * fic_son;


snd_pcm_sframes_t nb_frames_envoyes;
int octects_lus,nb_frames_de_envoi,frames_rest_a_envoyer;
char *buffer2;
char * pos_buffer;
int err_init,nb_octets_par_frame;

// a partager
snd_pcm_t *handle;
snd_pcm_uframes_t buffer_size;
size_t bits_per_frame;
u_long datastart;


fic_son=fopen(nom_fic_a_jouer,"rb");
if (!fic_son)
  {
  fprintf(stdout,"Gagal buka file WAV %s\n",nom_fic_a_jouer);
  return 10;
  }
err_init=alsa_init_son(fic_son,nom_fic_a_jouer,&handle,&buffer_size,&bits_per_frame,&datastart);
if (err_init)
  {
  fclose(fic_son);
  return err_init;
  }
err=fseek(fic_son,datastart,SEEK_SET);

if (buffer_size>1024*64)
  buffer_size=1024*64;

buffer2=(char *)malloc(buffer_size);
if (buffer2==0)
  {
  fprintf(stdout,"Salah Malloc in function : play_le_son\n");
  return 11;
  }

nb_octets_par_frame=bits_per_frame/8;
if (nb_octets_par_frame<1)
  nb_octets_par_frame=1;

while ((octects_lus=fread(buffer2,1,buffer_size,fic_son)))
  {
  pos_buffer=buffer2;
  nb_frames_de_envoi=octects_lus/nb_octets_par_frame;
  frames_rest_a_envoyer=nb_frames_de_envoi;

  nb_frames_envoyes=snd_pcm_writei(handle,pos_buffer,frames_rest_a_envoyer);
  if (nb_frames_envoyes>0)
    {
    frames_rest_a_envoyer-=nb_frames_envoyes;
    pos_buffer+=nb_octets_par_frame*nb_frames_envoyes;
    }
  while (frames_rest_a_envoyer>0)
    {

    nb_frames_envoyes=snd_pcm_writei(handle,pos_buffer,frames_rest_a_envoyer);
    if (nb_frames_envoyes>0)
      {
      frames_rest_a_envoyer-=nb_frames_envoyes;
      pos_buffer+=nb_octets_par_frame*nb_frames_envoyes;
      }
    if (nb_frames_envoyes==-EPIPE)  // une erreur est survenue
       frames_rest_a_envoyer=0;
    }
  }
free(buffer2);
fclose(fic_son);
snd_pcm_drain(handle);
return 0;
}



