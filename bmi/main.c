/* 
   An example of calling `storm`. 
*/
#include <stdio.h>

#include "storm.h"

int
main(int argc, char *argv[]) 
{
  StormModel *m = NULL;

  if (argc == 1) {
    m = storm_from_default ();
  } else {
    m = storm_from_input_file (argv[1]);
  }

  fprintf (stdout, "dx: %f\n", m->spacing[0]);
  fprintf (stdout, "dy: %f\n", m->spacing[1]);
  fprintf (stdout, "sspd: %f\n", m->sspd);
  fprintf (stdout, "sdir: %f\n", m->sdir);

  storm_advance_time (m);

  storm_write_output ("wdir.out", m->wdir, m->shape);
  storm_write_output ("wspd.out", m->wspd, m->shape);
  storm_write_output ("windx.out", m->windx, m->shape);
  storm_write_output ("windy.out", m->windy, m->shape);

  return 0;
}
