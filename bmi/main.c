/* 
   An example of calling `storm`. 
*/
#include <stdio.h>

#include "storm.h"

#define FNAME_LENGTH 20

int
main(int argc, char *argv[]) 
{
  StormModel *m = NULL;
  char wdir_file[FNAME_LENGTH];
  char wspd_file[FNAME_LENGTH];
  char windx_file[FNAME_LENGTH];
  char windy_file[FNAME_LENGTH];

  if (argc == 1) {
    m = storm_from_default ();
  } else {
    m = storm_from_input_file (argv[1]);
  }

  printf ("file: %s\n", m->filename);
  printf ("dx: %f\n", m->spacing[0]);
  printf ("dy: %f\n", m->spacing[1]);
  printf ("sspd: %f\n", m->sspd);
  printf ("sdir: %f\n", m->sdir);

  while (m->t < m->t_end) {
    storm_advance_time (m);

    sprintf (wdir_file, "wdir_%03d.out", m->t);
    sprintf (wspd_file, "wspd_%03d.out", m->t);
    sprintf (windx_file, "windx_%03d.out", m->t);
    sprintf (windy_file, "windy_%03d.out", m->t);

    storm_write_output (wdir_file, m->wdir, m->shape);
    storm_write_output (wspd_file, m->wspd, m->shape);
    storm_write_output (windx_file, m->windx, m->shape);
    storm_write_output (windy_file, m->windy, m->shape);
  }


  return 0;
}
