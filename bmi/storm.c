#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "storm.h"

int initialize_arrays (StormModel *self);

StormModel *
storm_from_default (void)
{
  StormModel *self = (StormModel*) malloc (sizeof(StormModel));

  if (self) {
    self->t = 0;
    self->dt = 1;
    self->t_end = 1;
    self->t_next = 2;
    self->shape[0] = 50;
    self->shape[1] = 25;
    self->spacing[0] = 5000.0;
    self->spacing[1] = 10000.0;
    self->center[0] = 24;
    self->center[1] = 12;
    self->sspd = 5.0;
    self->sdir = 210.0 * M_PI / 180.0;
    self->pcent = 99000.0;
    self->pedge = 101500.0;
    self->rmaxw = 65000.0;
    self->srad = 3000000.0;
    self->defcon = 0.0;
  }
  else
    return NULL;

  initialize_arrays (self);

  return self;
}


int
initialize_arrays (StormModel *self)
{
  int i;

  if (self) {
    const int n_rows = self->shape[0];
    const int n_cols = self->shape[1];
    const int n_elements = n_rows * n_cols;

    self->wdir = (double **) malloc (sizeof (double *) * n_rows);
    self->wspd = (double **) malloc (sizeof (double *) * n_rows);
    self->windx = (double **) malloc (sizeof (double *) * n_rows);
    self->windy = (double **) malloc (sizeof (double *) * n_rows);
    if (!self->wdir || !self->wspd || !self->windx || !self->windy)
      return 1;

    self->wdir[0] = (double *) malloc (sizeof (double) * n_elements);
    self->wspd[0] = (double *) malloc (sizeof (double) * n_elements);
    self->windx[0] = (double *) malloc (sizeof (double) * n_elements);
    self->windy[0] = (double *) malloc (sizeof (double) * n_elements);
    if (!self->wdir[0] || !self->wspd[0] || !self->windx[0] || !self->windy[0])
      return 1;

    for (i = 1; i < n_rows; i++) {
      self->wdir[i] = self->wdir[i-1] + n_cols;
      self->wspd[i] = self->wspd[i-1] + n_cols;
      self->windx[i] = self->windx[i-1] + n_cols;
      self->windy[i] = self->windy[i-1] + n_cols;
    }

  }
  else
    return 1;

  return 0;
}


int
storm_free (StormModel *self)
{
  if (self) {
    free (self->wdir[0]);
    free (self->wdir);
    free (self->wspd[0]);
    free (self->wspd);
    free (self->windx[0]);
    free (self->windx);
    free (self->windy[0]);
    free (self->windy);
    free (self);
  }
  return 0;
}


int
storm_advance_time (StormModel *self)
{
  if (self) {
    storm_compute_wind (self->wdir, self->wspd,
			self->windx, self->windy,
			self->shape, self->spacing, self->center,
			self->sspd, self->sdir,
			self->pcent, self->pedge,
			self->rmaxw, self->srad, self->defcon);
    self->t += self->dt;
  }
  else
    return 1;

  return 0;
}
