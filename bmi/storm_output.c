#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "storm.h"


int
storm_write_output (const char *filename, double **output, int shape[2])
{
  int i, j;
  const int nx = shape[0];
  const int ny = shape[1];
  FILE *fp = NULL;

  fp = fopen (filename, "w");
  if (!fp)
    return 1;

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      fprintf(fp, "%10.2e", output[i][j]);
    }
    fprintf(fp, "\n");
  }

  fclose(fp);

  return 0;
}
