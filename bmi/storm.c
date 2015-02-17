#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heat.h"

int initialize_arrays (StormModel *self);

StormModel *
storm_from_default (void)
{
  StormModel * self = (StormModel*) malloc (sizeof(StormModel));

  if (self) {
    self->t_end = 1;
    self->t_next = 2;
    self->shape[0] = 50;
    self->shape[1] = 25;
    self->spacing[0] = 5000.0;
    self->spacing[1] = 10000.0;
    self->center[0] = 24;
    self->center[1] = 12;
  }
  else
    return NULL;

  initialize_arrays (self);

  return self;
}


int
initialize_arrays (StormModel *self)
{
  if (self) {
    const int n_rows = self->shape[0];
    const int n_cols = self->shape[1];
    const int n_elements = n_rows * n_cols;

    /* Allocate memory */
    self->wdir = (double **)malloc (sizeof (double*) * n_elements);
    self->wspd = (double **)malloc (sizeof (double*) * n_elements);

    if (!self->wdir || !self->wspd)
      return 1;
  }
  else
    return 1;

  return 0;
}


int
storm_free (StormModel *self)
{
  if (self) {
    free (self->wdir);
    free (self->wspd);
    free (self);
  }
  return 0;
}
