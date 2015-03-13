// //////////////////////////////////////////
// Playing Wav in Windows with PThread
// Copyright Haris Hasanudin 2010
// //////////////////////////////////////////

#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void * play_BGM( void * fname );

void * play_BGM( void * arg )
{
        TH_BOX * arg_bgm = (TH_BOX * ) arg;
        char   *fname=NULL;

        fname = arg_bgm->myfile;

        // printf("inside: %s\n", arg_bgm->myfile);
        
        pthread_detach ( pthread_self() );
        
        playWave( arg_bgm->myfile );

	//printf( "\nselesai.\n" );
	
	if(arg_bgm != NULL)
	  free (arg_bgm);
	
	return 0;
}

