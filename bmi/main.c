/* 
   An example of calling `storm`. 
*/
#include <stdio.h>

#include "storm.h"

int
main(void) {
  int i;
  StormModel *m = storm_from_default ();

  fprintf (stdout, "dx: %f\n", m->spacing[0]);
  fprintf (stdout, "dy: %f\n", m->spacing[1]);
  fprintf (stdout, "sspd: %f\n", m->sspd);
  fprintf (stdout, "sdir: %f\n", m->sdir);

  for (i=0; i<10; i++) {
    storm_advance_in_time (m);
    fprintf (stdout, "Time: %d\n", m->t);
  }

  return 0;
}
