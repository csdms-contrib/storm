/* 
   An example of calling `storm`. 
*/
#include <stdio.h>
#include "storm.h"

int
main(void) {

  StormModel * m = storm_from_default ();

  fprintf (stdout, "dx: %f\n", m->spacing[0]);
  fprintf (stdout, "dy: %f\n", m->spacing[1]);
  fprintf (stdout, "sspd: %f\n", m->sspd);
  fprintf (stdout, "sdir: %f\n", m->sdir);
  return 0;
}
