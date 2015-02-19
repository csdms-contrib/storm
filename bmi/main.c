/* 
   An example of calling `storm`. 
*/
#include <stdio.h>

#include "storm.h"

int
main(void) {
  int i, j;
  StormModel *m = storm_from_default ();

  fprintf (stdout, "dx: %f\n", m->spacing[0]);
  fprintf (stdout, "dy: %f\n", m->spacing[1]);
  fprintf (stdout, "sspd: %f\n", m->sspd);
  fprintf (stdout, "sdir: %f\n", m->sdir);

  storm_advance_time (m);
  printf("wspd =\n");
  for (i = 0; i < m->shape[0]; i++) {
    for (j = 0; j < m->shape[1]; j++) {
      printf("%f ", m->wspd[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return 0;
}
