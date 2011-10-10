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

const int SIZE = 256*400;

/* OpenAL */
static ALCdevice *device = NULL;
static ALCcontext *context = NULL;
static ALuint buffer = 0, source = 0;

/* output stopping flag */
static int da_stopping = 0;

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
  init_audiodev();
}

void sndout(int	leng, short *out)
{
  ALint state;
  //printf("sndout(%d)\n", leng);  fflush(stdout);
  alBufferData(buffer, AL_FORMAT_MONO16, 
	       out, sizeof(short) * leng, wave.rate);
  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, buffer);
  alSourcePlay(source);
  while (alGetSourcei(source, AL_SOURCE_STATE, &state), state != AL_STOPPED) {
    if (da_stopping) {
      alSourceStop(source);
      update_talked_da_msec();
      if (prop_Speak_len == AutoOutput)  inqSpeakLen();
      if (prop_Speak_utt == AutoOutput)  inqSpeakUtt();
      reset_audiodev();
      da_stopping = 0;
      return;
    }
    if (slot_Speak_syncinterval > 0) {
      usleep(slot_Speak_syncinterval * 1000);
      update_talked_da_msec();
      RepMsg("tell Speak.sync = %d\n", talked_DA_msec);
    } else {
      usleep(1000000);
      //printf("sndout sleeping 1\n");
    }
  }
}

void init_audiodev()
{
  /* OpenAL */
  device = alcOpenDevice(NULL);
  context = alcCreateContext(device, NULL);
  alcMakeContextCurrent(context);
  alGenBuffers(1, &buffer);
}

void close_audiodev()
{
  /* OpenAL */
  alSourceStop(source);
  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);
}

void reset_audiodev()
{
  close_audiodev();
}

static struct timeval tv;
static struct timezone tz;
static int start_DA_sec;
static int start_DA_usec;

void set_start_da_time()
{
  gettimeofday( &tv, &tz );
  start_DA_sec = (int)tv.tv_sec;
  start_DA_usec = (int)tv.tv_usec;
}

void update_talked_da_msec()
{
  gettimeofday( &tv, &tz );
  talked_DA_msec = (tv.tv_sec - start_DA_sec) * 1000 + (tv.tv_usec - start_DA_usec) / 1000.0;
}

static pthread_t thread;

void output_speaker_cleanup(void *dummy)
{
  reset_output();
  strcpy( slot_Speak_stat, "IDLE" );
  if( prop_Speak_stat == AutoOutput )  inqSpeakStat();
}

void output_speaker_thread(int *t)
{
  static int total;
  static int nout;
  //static int last_state, last_type;
  
  total = *t;
  //printf("output_speaker_thread(total %d)\n", total);  fflush(stdout);
  init_output();
  nout = 0;
  set_start_da_time();
  while (nout < total - SIZE) {
    sndout(SIZE,&wave.data[nout]);
    nout += SIZE;
  }
  sndout(total - nout, &wave.data[nout]);
  //printf("output_speaker_thread() done.\n");  fflush(stdout);
}

void do_output(char *fn)
{
  static int nsample;
  
  in_auto_play = 0;

  if (fn)  {
    do_output_file(fn);
    return;
  }
  
  nsample = wave.nsample;
  talked_DA_msec = -1;
  already_talked = 1;
  
  pthread_create(&thread,
		 NULL,
		 (void *) output_speaker_thread,
		 (void *) &nsample);
}

void abort_output()
{
  //printf("abort_output()\n");  fflush(stdout);
  da_stopping = 1;
}
