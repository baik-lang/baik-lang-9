// //////////////////////////////////////////
// Playing Wav in Linux
// Copyright Haris Hasanudin 2010
// //////////////////////////////////////////

#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/soundcard.h>

typedef struct {
	FILE* fp;
	short is_pcm;
	short channel;
	int   rate; 
	short bits;
	long  offset;
	int   len; 
} HHWAVE;

static int  wave_read_file( char* fname, HHWAVE* wave );
static int  wave_setup_dsp( int* fd, HHWAVE* wave );
static void wave_progress( int* processed, int current, HHWAVE* wave );
static int  ux_play_wave( char* fname );

void * ux_play_BGM( void * fname );

#define WAVBUFSIZE 64000

void * ux_play_BGM( void * arg )
{
        TH_BOX * arg_bgm = (TH_BOX * ) arg;
        char   *fname=NULL;
	HHWAVE wave;
	char buf[ WAVBUFSIZE ];
	int  dsp;
	int  len;
	int  processed = 0;

        fname = arg_bgm->myfile;

        // printf("inside: %s\n", arg_bgm->myfile);
        
        pthread_detach ( pthread_self() );
        
	if ( wave_read_file( fname, &wave ) != 0 ) {
		fprintf( stderr, "Gagal baca WAVE file"
			 ": %s\n", fname );
	        exit(1);
	}

	//printf( "\n" );
	//printf( "format HHWAVE :\n" );
	//printf( " kecepatan    = %d\n",  wave.rate );
	//printf( " canel   = %d\n",  wave.channel );
	//printf( " bits    = %d\n",  wave.bits );
	//printf( " offsets = %ld\n", wave.offset );
	//printf( " panjang = %d\n",  wave.len );
	//printf( "\n" );

	if ( wave_setup_dsp( &dsp, &wave ) != 0 ) {
		fprintf( stderr, "Salah Setup /dev/dsp.\n" );
		fclose( wave.fp );
	        exit(1);		
	}

	//printf( "Main music wave file %s ...\n", fname );
	fflush( stdout );

	fseek( wave.fp, wave.offset, SEEK_SET );
	wave_progress( &processed, 0, &wave );

	while ( 1 ) {
		len = fread( buf, 1, WAVBUFSIZE, wave.fp );

		if ( len < WAVBUFSIZE ) {
			if ( feof( wave.fp ) ) {
				if ( write( dsp, buf, len ) == -1 ) {
					perror( "kesalahan internal : write()" );
				}
				else {
					wave_progress( &processed, len, &wave );
				}
			}
			else {
				perror( "kesalahan internal : fread()" );
			}

			break;
		}

		if ( write( dsp, buf, len ) == -1 ) {
			perror( "kesalahan internal : write()" );
			break;
		}

		wave_progress( &processed, len, &wave );
	}

	fclose( wave.fp );
	close( dsp );

        if(arg_bgm != NULL)
          free (arg_bgm);

	//printf( "\nselesai.\n" );
	return 0;
}

// ////////////////////////////////////////////////////////////

static int  ux_play_wave( char* fname )
{
	HHWAVE wave;
	char buf[ WAVBUFSIZE ];
	int  dsp;
	int  len;
	int  processed = 0;

	if ( wave_read_file( fname, &wave ) != 0 ) {
		fprintf( stderr, "Gagal baca WAVE file"
			 ": %s\n", fname );
		return 1;
	}

	//printf( "\n" );
	//printf( "format HHWAVE :\n" );
	//printf( " kecepatan    = %d\n",  wave.rate );
	//printf( " canel   = %d\n",  wave.channel );
	//printf( " bits    = %d\n",  wave.bits );
	//printf( " offsets = %ld\n", wave.offset );
	//printf( " panjang = %d\n",  wave.len );
	//printf( "\n" );

	if ( wave_setup_dsp( &dsp, &wave ) != 0 ) {
		fprintf( stderr, "Salah Setup /dev/dsp.\n" );
		fclose( wave.fp );
		return 1;
	}

	//printf( "Main music wave file %s ...\n", fname );
	fflush( stdout );

	fseek( wave.fp, wave.offset, SEEK_SET );
	wave_progress( &processed, 0, &wave );

	while ( 1 ) {
		len = fread( buf, 1, WAVBUFSIZE, wave.fp );

		if ( len < WAVBUFSIZE ) {
			if ( feof( wave.fp ) ) {
				if ( write( dsp, buf, len ) == -1 ) {
					perror( "kesalahan internal : write()" );
				}
				else {
					wave_progress( &processed, len, &wave );
				}
			}
			else {
				perror( "kesalahan internal : fread()" );
			}

			break;
		}

		if ( write( dsp, buf, len ) == -1 ) {
			perror( "kesalahan internal : write()" );
			break;
		}

		wave_progress( &processed, len, &wave );
	}

	fclose( wave.fp );
	close( dsp );

	//printf( "\nselesai.\n" );
	return 0;
}


/*
 * Read HHWAVE file
 */
static int 
wave_read_file( char* fname, HHWAVE* wave )
{
	char   buf[32];
	int    len;

	if ( ( wave->fp = fopen( fname, "r" ) ) == NULL ) {
		fprintf( stderr, "Gagal buka file %s\n", fname );
		return -1;
	}

	fread( buf, 8, 1, wave->fp );

	if ( strncmp( buf, "RIFF", 4 ) != 0 ) {
		fprintf( stderr, "Salah, bukan jenis file RIFF.\n" );
		fclose( wave->fp );
		return -1;
	}


	fread( buf, 4, 1, wave->fp );

	if ( strncmp( buf, "WAVE", 4 ) != 0 ) {
		fprintf( stderr, "Salah, bukan jenis file WAVE.\n" );
		fclose( wave->fp );
		return -1;
	}

	while ( 1 ) {
		fread( buf, 8, 1, wave->fp );
		len = *( int* )( &buf[4] );

		if ( strncmp( buf, "fmt ", 4 ) != 0 ) {
			if ( fseek( wave->fp, len, SEEK_CUR ) == -1 ) {
				fprintf( stderr, "kesalahan internal : gagal pencarian fmt chunk.\n" );
				fclose( wave->fp );
				return -1;
			}
		}
		else {
			break;
		}
	}


	fread( buf, len, 1, wave->fp );

	wave->is_pcm  = *( ( short* )( &buf[0]  ) );
	wave->channel = *( ( short* )( &buf[2]  ) );
	wave->rate    = *( ( int*   )( &buf[4]  ) );
	wave->bits    = *( ( short* )( &buf[14] ) );

	if ( wave->is_pcm != 1 ) {
		wave->is_pcm = 0;
	}

	while ( 1 ) {
		fread( buf, 8, 1, wave->fp );
		len = *( int* )( &buf[4] );

		if ( strncmp( buf, "data", 4 ) != 0 ) {
			if ( fseek( wave->fp, len, SEEK_CUR ) == -1 ) {
				fprintf( stderr, "kesalahan internal : gagal pencarian data chunk.\n" );
				fclose( wave->fp );
				return -1;
			}
		}
		else {
			break;
		}
	}

	wave->len = len;

	if ( ( wave->offset = ftell( wave->fp ) ) == -1 ) {
		fprintf( stderr, "kesalahan internal : gagal pencarian offset PCM data.\n" );
		fclose( wave->fp );
		return -1;
	}

	return 0;
}


static int 
wave_setup_dsp( int* dsp, HHWAVE* wave )
{
	int format;
	int rate;
	int channel;


	if ( ! wave->is_pcm ) {
		fprintf( stderr, "file sound data bukan dalam PCM format.\n" );
		fclose( wave->fp );
		return -1;
	}


	if ( wave->bits == 8 ) {
		format = AFMT_U8;
	}
	else if ( wave->bits == 16 ) {
		format = AFMT_S16_LE;
	}
	else {
		fprintf( stderr, "Data suara dalam file %d bits,"
			 "bukan 8 maupun 16 bits.\n", wave->bits );
		fclose( wave->fp );
		return -1;
	}

	rate    = ( int )wave->rate;
	channel = ( int )wave->channel;


	if ( ( *dsp = open( "/dev/dsp", O_WRONLY ) ) == -1 ) {
          if ( ( *dsp = open( "/dev/snd", O_WRONLY ) ) == -1 ) {	
		perror( "salah buka" );
		return -1;
	  }
	}

	if ( ioctl( *dsp, SNDCTL_DSP_SETFMT, &format ) == -1 ) {
		perror( "ioctl( SOUND_PCM_SETFMT )" );
		close( *dsp );
		return -1;
	}

	if ( ioctl( *dsp, SOUND_PCM_WRITE_RATE, &rate ) == -1 ) {
		perror( "ioctl( SOUND_PCM_WRITE_RATE )" );
		close( *dsp );
		return -1;
	}

	if ( ioctl( *dsp, SOUND_PCM_WRITE_CHANNELS, &channel ) == -1 ) {
		perror( "ioctl( SOUND_PCM_WRITE_CHANNELS )" );
		close( *dsp );
		return -1;
	}

	return 0;
}


static void 
wave_progress( int* processed, int current, HHWAVE* wave )
{
	int progress;

	*processed += current;
	progress = (int)( ( ( double )*processed / ( double )wave->len ) * 100 );
	//printf( "\r%3d%% dimainkan.", progress );
	fflush( stdout );
}


/* End of haris_wav.c */


