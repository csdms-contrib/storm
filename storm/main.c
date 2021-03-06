/* 
   An example of calling `storm`. 
*/
#include <stdio.h>

#include "storm.h"

int
main(int argc, char *argv[]) 
{
  StormModel *m = NULL;
  char wdir_file[MAX_LEN];
  char wspd_file[MAX_LEN];
  char windx_file[MAX_LEN];
  char windy_file[MAX_LEN];

  if (argc == 1) {
    m = storm_from_default ();
  } else {
    m = storm_from_input_file (argv[1]);
  }

  printf ("*** storm ***\n");
  printf ("Input file: %s\n", m->filename);

  while (m->t < m->t_end) {
    storm_advance_time (m);
    printf ("Timestep: %d\n", (int) m->t);

    sprintf (wdir_file, "wdir_%03d.out", (int) m->t);
    sprintf (wspd_file, "wspd_%03d.out", (int) m->t);
    sprintf (windx_file, "windx_%03d.out", (int) m->t);
    sprintf (windy_file, "windy_%03d.out", (int) m->t);

    storm_write_output (wdir_file, m->wdir, m->shape);
    storm_write_output (wspd_file, m->wspd, m->shape);
    storm_write_output (windx_file, m->windx, m->shape);
    storm_write_output (windy_file, m->windy, m->shape);
  }
  printf ("Done!\n");

  return 0;
}
