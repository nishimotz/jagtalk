/*
 * do_output_openal.c
 * by Takuya Nishimoto (nishimotz.com)
 * since 2011-10-09 
 */

#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

/* extern WAVE wave; in synthesis.h */

/* from oss version */
int     current_pos;
int     prev_tell_pos_ms;

const int SIZE = 256*400;

/* OpenAL */
static ALCdevice *device = NULL;
static ALCcontext *context = NULL;
static ALuint buffer = 0, source = 0;

/* prototypes */
void reset_audiodev();
void init_audiodev();

/* functions */
void set_da_signal() 
{
}

void reset_output()
{
  reset_audiodev();
}

void init_output()
{
  int	dtype;
  dtype = DTYPE;
  init_audiodev(dtype);
}

void sndout(int	leng, short *out)
{
  int i, pos, pos_ms, interval_ms, samp_rate;

  //samp_rate = data_type[DTYPE].sample;
  samp_rate = wave.rate;
  for( i=0; i<leng; ++i ) {
    /* OpenAL */
    alBufferData(buffer, AL_FORMAT_MONO16, 
		 &(out[i]), sizeof(short), samp_rate);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);

    if(current_pos % 128 == 0) {
      pos = current_pos;
      pos_ms = (1000 * pos) / samp_rate;
      interval_ms = pos_ms - prev_tell_pos_ms;
      if( slot_Speak_syncinterval > 0 && interval_ms >= slot_Speak_syncinterval ) {
	RepMsg("tell Speak.sync = %d\n", pos_ms);
	/*prev_tell_pos_ms = pos_ms;*/
	while( prev_tell_pos_ms + slot_Speak_syncinterval <= pos_ms ) {
	  prev_tell_pos_ms += slot_Speak_syncinterval;
	}
      }
    }
    ++current_pos;
  }
}

void init_audiodev(int dtype)
{
  /* OpenAL */
  device = alcOpenDevice(NULL);
  context = alcCreateContext(device, NULL);
  alcMakeContextCurrent(context);
  alGenBuffers(1, &buffer);
  // 
  current_pos = 0;
  prev_tell_pos_ms = 0;
}

void reset_audiodev()
{
  /* OpenAL */
  alSourceStop(source);
  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);
  //
  current_pos = 0;
  prev_tell_pos_ms = 0;
}

struct timeval tv;
struct timezone tz;
static int start_DA_sec;
static int start_DA_usec;

pthread_t thread;

void output_speaker_cleanup(void *dummy)
{
  reset_output();
  strcpy( slot_Speak_stat, "IDLE" );
  if( prop_Speak_stat == AutoOutput )  inqSpeakStat();
}

void output_speaker_thread(int *t)
{
  int total = *t;
  int nout;
  int last_state, last_type;

  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &last_type);
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &last_state);
  pthread_cleanup_push((void *)output_speaker_cleanup, NULL);
  
  init_output();
  nout = 0;
  while ( nout < total - SIZE)  {
    sndout(SIZE,&wave.data[nout]);
    nout += SIZE;
    pthread_testcancel();
  }
  sndout(total - nout, &wave.data[nout]);
  // TODO: flush output

  pthread_cleanup_pop(1);
}

void abort_demanded_output()
{
  void *statusp;

  gettimeofday( &tv, &tz );
  talked_DA_msec = (tv.tv_sec-start_DA_sec)*1000 + 
                   (tv.tv_usec-start_DA_usec)/1000.;

  pthread_cancel(thread);
  pthread_join(thread, &statusp);

  if( prop_Speak_len == AutoOutput )  inqSpeakLen();
  if( prop_Speak_utt == AutoOutput )  inqSpeakUtt();
}

void do_output(char *fn)
{
  static int nsample;
  
  in_auto_play = 0;

  if( fn )  {
    do_output_file( fn );
    return;
  }
  
  nsample = wave.nsample;
  
  gettimeofday( &tv, &tz );
  start_DA_sec = (int)tv.tv_sec;
  start_DA_usec = (int)tv.tv_usec;
  talked_DA_msec = -1;
  already_talked = 1;
  
#if 0
  pthread_create(&thread,
		 NULL,
		 (void *) output_speaker_thread,
		 (void *) &nsample);
#else
  device = alcOpenDevice(NULL);
  context = alcCreateContext(device, NULL);
  alcMakeContextCurrent(context);
  alGenBuffers(1, &buffer);

  alBufferData(buffer, AL_FORMAT_MONO16, 
	       wave.data, 
	       nsample * sizeof(short), 
	       wave.rate /* data_type[DTYPE].sample */);

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
#endif
}

void abort_output()
{
#if 0
  abort_demanded_output();
#endif
}


