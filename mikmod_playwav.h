// /////////////////////////////////////////////////////////////////
// Copyright Haris Hasanudin 2010
// /////////////////////////////////////////////////////////////////
// libMikmod sample
//  `libmikmod-config --cflags` `libmikmod-config --libs` 
// /////////////////////////////////////////////////////////////////


#include <unistd.h>
#include <mikmod.h>
#include <stdio.h>
#include <stdlib.h>

void  mymikmod_play(char fname[256]);

void * mikmod_play_BGM( void * fname );

void * mikmod_play_BGM( void * arg )
{
   TH_BOX * arg_bgm = (TH_BOX * ) arg;
   char   *fname=NULL;

   fname = arg_bgm->myfile;

   // printf("inside: %s\n", arg_bgm->myfile);

   pthread_detach ( pthread_self() );
   
   mymikmod_play( arg_bgm->myfile );

   //printf( "\nselesai.\n" );
   
   if(arg_bgm != NULL)
     free (arg_bgm);
   
  return 0;
}


void  mymikmod_play(char fname[256])
{
    int i;
    /* sound effects */
    SAMPLE *sfx1=NULL;
    /* voices */
    int v1;

    // printf("mikmod read %s\n", fname);

    /* register all the drivers */
    MikMod_RegisterAllDrivers();

    //printf("register ok\n");

    /* initialize the library */
    md_mode |= DMODE_SOFT_SNDFX;
    if (MikMod_Init("")) {
        fprintf(stderr, "Could not initialize sound, reason: %s\n",
                MikMod_strerror(MikMod_errno));
        return;
    }

    /* load samples */
    sfx1 = Sample_Load( fname );
    if (!sfx1) {
        MikMod_Exit();
        fprintf(stderr, "Could not load the first sound, reason: %s\n",
                MikMod_strerror(MikMod_errno));
        return;
    }

    // printf("load sample ok\n");

    /* reserve voices for sound effects */
    MikMod_SetNumVoices(-1, 1);

    /* get ready to play */
    MikMod_EnableOutput();

    /* play first sample */
    v1 = Sample_Play(sfx1, 0, 0);
    
    //printf("\n");
    
    do {
        MikMod_Update();
        Voice_SetVolume(v1, 180);
        usleep(100000);
    } while (!Voice_Stopped(v1));


    MikMod_DisableOutput();

    Sample_Free(sfx1);

    MikMod_Exit();
}



