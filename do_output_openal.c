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

void init_audiodev()
{
  /* OpenAL */
  device = alcOpenDevice(NULL);
  context = alcCreateContext(device, NULL);
  alcMakeContextCurrent(context);
  alGenBuffers(1, &buffer);
}

void init_output()
{
  init_audiodev();
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

void reset_output()
{
  reset_audiodev();
}

/* timer */
static struct timeval tv;
// static struct timezone tz;
static time_t start_DA_sec = 0;
static suseconds_t start_DA_usec = 0;

void set_start_da_time()
{
  gettimeofday( &tv, NULL );
  start_DA_sec = tv.tv_sec;
  start_DA_usec = tv.tv_usec;
}

void update_talked_da_msec()
{
  gettimeofday( &tv, NULL );
  talked_DA_msec = (tv.tv_sec - start_DA_sec) * 1000 + (tv.tv_usec - start_DA_usec) / 1000;
}

/* output stopping flag */
static int da_stopping = 0;

/* functions */
void set_da_signal() 
{
}

void sndout(int	leng, short *out)
{
  ALint state;
  int prev_msec, next_sync_msec;
  //printf("sndout(%d)\n", leng);  fflush(stdout);
  alBufferData(buffer, AL_FORMAT_MONO16, 
	       out, sizeof(short) * leng, wave.rate);
  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, buffer);
  alSourcePlay(source);
  update_talked_da_msec();
  prev_msec = talked_DA_msec;
  if (slot_Speak_syncinterval > 0) {
    next_sync_msec = slot_Speak_syncinterval;
  }
  while (alGetSourcei(source, AL_SOURCE_STATE, &state), state != AL_STOPPED) {
    usleep(1000); // 1msec
    update_talked_da_msec();
    if (da_stopping == 1) {
      alSourceStop(source);
      //if (prop_Speak_len == AutoOutput)  inqSpeakLen();
      //if (prop_Speak_utt == AutoOutput)  inqSpeakUtt();
      //reset_audiodev();
      return;
    }
    if (slot_Speak_syncinterval > 0) {
      if (next_sync_msec < talked_DA_msec) {
	RepMsg("tell Speak.sync = %d\n", talked_DA_msec);
	next_sync_msec += slot_Speak_syncinterval;
      }
    }
  }
}

static pthread_t thread;

void output_speaker_cleanup(void *dummy)
{
  update_talked_da_msec();
  if (prop_Speak_len == AutoOutput)  inqSpeakLen();
  strcpy(slot_Speak_stat, "IDLE");
  if (prop_Speak_stat == AutoOutput)  inqSpeakStat();
  // talked_DA_msec = -1;
  already_talked = 0;
  reset_output();
}

void output_speaker_thread(int *t)
{
#if 0
  static int total;
  static int nout;
  
  total = *t;
  //printf("output_speaker_thread(total %d)\n", total);  fflush(stdout);
  init_output();
  nout = 0;
  set_start_da_time();
  while (nout < total - SIZE) {
    sndout(SIZE,&wave.data[nout]);
    if (da_stopping == 1) {
      da_stopping = 0;
      output_speaker_cleanup(NULL);
      return;
    }
    nout += SIZE;
  }
  sndout(total - nout, &wave.data[nout]);
#else
  static int total;
  
  total = *t;
  init_output();
  set_start_da_time();
  sndout(total, wave.data);
  if (da_stopping == 1) {
    da_stopping = 0;
  }
#endif
  output_speaker_cleanup(NULL);
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
  if (already_talked == 1) {
    da_stopping = 1;
  }
}
