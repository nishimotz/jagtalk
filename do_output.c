#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "synthesis.h"
#include "defaults.h"
#include "confpara.h"
#include "da.h"
#include "slot.h"

int talked_DA_msec;
int already_talked;
int in_auto_play;

int ErrMsg(char *,...);
int TmpMsg(char *,...);
void RepMsg( char *, ... );
void restart(int);
void inqSpeakLen();
void inqSpeakUtt();
void inqSpeakStat();
void do_output_file(char *);
void abort_auto_output();

#ifdef USE_SPLIB
#include "do_output_sp.c"
#else
# ifdef USE_PORTAUDIO
#  include "do_output_portaudio.c"
# else
#  include "do_output_oss.c"
# endif
#endif /* !USE_SPLIB */
