#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "storm.h"

int initialize_arrays (StormModel *self);
int read_timestep (StormModel *self);


StormModel *
storm_from_default (void)
{
  StormModel *self = (StormModel*) malloc (sizeof(StormModel));

  if (self) {
    self->t = 0;
    self->dt = 1;
    self->t_end = 1;
    self->shape[0] = 8;
    self->shape[1] = 6;
    self->spacing[0] = 25000.0;
    self->spacing[1] = 20000.0;
    self->center[0] = 4;
    self->center[1] = 3;
    self->sspd = 5.0;
    self->sdir = 210.0 * PI / 180.0;
    self->pcent = 99000.0;
    self->pedge = 101200.0;
    self->rmaxw = 40000.0;
    self->srad = 100000.0;
  }
  else
    return NULL;

  initialize_arrays (self);

  return self;
}


StormModel *
storm_from_input_file (const char *filename)
{
  StormModel *self = NULL;
  FILE *fp = NULL;
  char line[MAX_LEN];
  int t_end, xsize, ysize;
  double dx, dy;

  fp = fopen (filename, "r");
  if (!fp) {
    return NULL;
  } else {
    self = (StormModel *) malloc (sizeof (StormModel));
    strcpy(self->filename, filename);
  }

  fscanf(fp, "%d %d %d %lf %lf", &t_end, &xsize, &ysize, &dx, &dy);
  fgets(line, MAX_LEN, fp);
  fclose(fp);

  self->t = 0;
  self->dt = 1;
  self->t_end = t_end;
  self->shape[0] = xsize;
  self->shape[1] = ysize;
  self->spacing[0] = dx;
  self->spacing[1] = dy;

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
    read_timestep (self);
    compute_wind (self->wdir, self->wspd,
		  self->windx, self->windy,
		  self->shape, self->spacing, self->center,
		  self->sspd, self->sdir,
		  self->pcent, self->pedge,
		  self->rmaxw, self->srad);
    self->t += self->dt;
  }
  else
    return 1;

  return 0;
}


int
read_timestep (StormModel *self)
{
  FILE *fp = NULL;
  char line[MAX_LEN];
  int i, xc, yc;
  double sspd, sdir, pcent, pedge, rmaxw, srad;

  fp = fopen (self->filename, "r");
  if (!fp) {
    return 1;
  }

  /* Skip to timestep in file */
  fgets(line, MAX_LEN, fp);
  for (i = 0; i < 4*self->t; i++) {
    fgets(line, MAX_LEN, fp);
  }

  fscanf(fp, "%d %d", &xc, &yc);
  fgets(line, MAX_LEN, fp);
  fscanf(fp, "%lf %lf %lf %lf", &sspd, &sdir, &pcent, &pedge);
  fgets(line, MAX_LEN, fp);
  fscanf(fp, "%lf %lf", &rmaxw, &srad);
  fgets(line, MAX_LEN, fp);

  fclose(fp);

  self->center[0] = xc;
  self->center[1] = yc;
  self->sspd = sspd;
  self->sdir = (sdir + ACOR) * PI / 180.0;
  self->pcent = pcent;
  self->pedge = pedge;
  self->rmaxw = rmaxw;
  self->srad = srad;

  return 0;
}
