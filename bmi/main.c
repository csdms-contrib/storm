/* 
   An example of calling `storm`. 
*/
#include <stdio.h>

#include "storm.h"

int
main(int argc, char *argv[]) {
  int j;
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

  printf("windx[0,*] =\n");
  for (j = 0; j < m->shape[1]; j++) {
    printf("%f ", m->windx[0][j]);
  }
  printf("\n");
  printf("windy[0,*] =\n");
  for (j = 0; j < m->shape[1]; j++) {
    printf("%f ", m->windy[0][j]);
  }
  printf("\n");
  printf("wspd[0,*] =\n");
  for (j = 0; j < m->shape[1]; j++) {
    printf("%f ", m->wspd[0][j]);
  }
  printf("\n");
  printf("wdir[0,*] =\n");
  for (j = 0; j < m->shape[1]; j++) {
    printf("%f ", m->wdir[0][j]);
  }
  printf("\n");

  return 0;
}
