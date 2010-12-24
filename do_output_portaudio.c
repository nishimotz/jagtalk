/* 2010-11-15 by Takuya Nishimoto */
/* TODO: -DAUTO_DA=1 must be supported */

#include <portaudio.h>

// static int in_auto_play;

static  PaStreamParameters outputParameters;
static  PaStream *stream;
static  PaError err;

void set_da_signal() 
{
}

void do_output_da()
{
  err = Pa_Initialize();
  outputParameters.device = Pa_GetDefaultOutputDevice();
  outputParameters.channelCount = 1;
  outputParameters.sampleFormat = paInt16;
  outputParameters.suggestedLatency 
    = Pa_GetDeviceInfo( outputParameters.device )->defaultHighOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;
  err = Pa_OpenStream(
		      &stream,
		      NULL, // input
		      &outputParameters,
		      16000,
		      1024, // FRAMES_PER_BUFFER,
		      paClipOff,
		      NULL,
		      NULL );
  if ( err != paNoError ) 
    exit(-1);
  err = Pa_StartStream( stream );
  if ( err != paNoError ) 
    exit(-1);
}

void do_output(char *fn)
{
  in_auto_play = 0;
  if (fn == NULL) {
    do_output_da();
  } else {
    do_output_file( fn );
  }
}

void abort_output()
{
}

void abort_demanded_output() 
{
}

void do_auto_output()
{
    in_auto_play = 1;
    do_output_da();
}

void abort_auto_output() 
{
    abort_demanded_output();
}

