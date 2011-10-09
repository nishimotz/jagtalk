/*
 * do_output_openal.c
 * by Takuya Nishimoto (nishimotz.com)
 * since 2011-10-09 
 */

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

/* extern WAVE wave; in synthesis.h */

static ALCdevice *device = NULL;
static ALCcontext *context = NULL;
static ALuint buffer = 0, source = 0;

void set_da_signal() 
{
}

void do_output_da()
{
  int i;
  device = alcOpenDevice(NULL);
  context = alcCreateContext(device, NULL);
  alcMakeContextCurrent(context);
  alGenBuffers(1, &buffer);
  alBufferData(buffer, AL_FORMAT_MONO16, 
	       wave.data, wave.nsample * sizeof(short), wave.rate);
  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, buffer);
  alSourcePlay(source);
  sleep(10);

  alSourceStop(source);
  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);
}

void do_output(char *fn)
{
  if (fn == NULL) {
    do_output_da();
  } else {
    do_output_file( fn );
  }
}

void abort_output()
{
  //
}

void abort_demanded_output() 
{
  //
}

void do_auto_output()
{
  //
}

void abort_auto_output() 
{
  //
}

