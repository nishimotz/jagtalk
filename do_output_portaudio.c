/* 2010-11-15 by Takuya Nishimoto */
/* TODO: -DAUTO_DA=1 must be supported */

#include "portaudio.h"

int in_auto_play;

void set_da_signal() 
{
}

void do_output_da()
{
  PaStreamParameters outputParameters;
  PaStream *stream;
  PaError err;
  // paTestData data;
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

void abort_auto_output() {
    abort_demanded_output();
}

