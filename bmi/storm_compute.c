#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "storm.h"

double gridcell_wdir (int i, int j, int xc, int yc, double dxc, double dyc,
		      double r, double rmaxw, double defcon);
double gridcell_wspd (double r, double pcent, double pedge, double rmaxw);
double xdistance_from_center (int i, double dx, int xc);
double ydistance_from_center (int j, double dy, int yc);
double euclidian_norm (double x, double y);
double * speed_correction (double sspd, double sdir, double r, double rmaxw);

int
compute_wind (double **wdir, double **wspd, double **windx, double **windy, 
	      int shape[2], double spacing[2], int center[2], double sspd, 
	      double sdir, double pcent, double pedge, double rmaxw, 
	      double srad, double defcon)
{
  int i, j;
  const int nx = shape[0];
  const int ny = shape[1];
  const double dx = spacing[0];
  const double dy = spacing[1];
  const int xc = center[0];
  const int yc = center[1];
  double dxc, dyc, r, wdir_ij, wspd_ij;
  double *sspd_corr;

  for (i = 0; i < nx; i++) {
    for (j = 0; j < ny; j++) {
      if (i == xc && j == yc) {
	wspd_ij = sspd;
	wdir_ij = sdir;
      } else {
	dxc = xdistance_from_center (i, dx, xc);
	dyc = ydistance_from_center (j, dy, yc);
	r = euclidian_norm (dxc, dyc);
	wdir_ij = gridcell_wdir (i, j, xc, yc, dxc, dyc, r, rmaxw, defcon);
	wspd_ij = gridcell_wspd (r, pcent, pedge, rmaxw);
      }
      sspd_corr = speed_correction (sspd, sdir, r, rmaxw);
      windx[i][j] = (wspd_ij * cos (wdir_ij)) + sspd_corr[0];
      windy[i][j] = (wspd_ij * sin (wdir_ij)) + sspd_corr[1];
      wdir[i][j] = (wdir_ij * 180.0 / M_PI) - ACOR;
      wspd[i][j] = euclidian_norm (windx[i][j], windy[i][j]);
    }
  }

  return 0;
}

double
gridcell_wdir (int i, int j, int xc, int yc, double dxc, double dyc,
	       double r, double rmaxw, double defcon)
{
  double _wdir;

  if (j > yc) {
    if (i > xc) {
      _wdir = atan (dyc / dxc) + (M_PI / 2.0);
    } else if (i < xc) {
      _wdir = atan (dxc / dyc) + M_PI;
    } else {
      _wdir = M_PI;
    }
  } else if (j < yc) {
    if (i > xc) {
      _wdir = atan (dxc / dyc);
    } else if (i < xc) {
      _wdir = atan (dyc / dxc) + (1.5 * M_PI);
    } else {
      _wdir = 0.0;
    }
  } else {
    if (i < xc) {
      _wdir = 1.5 * M_PI;
    } else {
      _wdir = M_PI / 2.0;
    }
  }

  _wdir += defcon * (r / rmaxw) * (M_PI / 180.0);

  return _wdir;
}


double
gridcell_wspd (double r, double pcent, double pedge, double rmaxw)
{
  double cc;

  cc = -((pedge - pcent) / RHOA) * (rmaxw / (r*r)) * exp (-rmaxw / r);
  return (sqrt(F*F - 4.0/r*cc) - F)/(2.0/r);
}


double
xdistance_from_center (int i, double dx, int xc)
{
  return fabs ((i - xc) * dx);
}


double
ydistance_from_center (int j, double dy, int yc)
{
  return fabs ((j - yc) * dy);
}


double
euclidian_norm (double x, double y)
{
  return sqrt (x*x + y*y);
}


double *
speed_correction (double sspd, double sdir, double r, double rmaxw)
{
  double magnitude;
  static double correction[2];

  magnitude = sspd * (rmaxw * r / (r*r + rmaxw*rmaxw));
  correction[0] = magnitude * cos (sdir);
  correction[1] = magnitude * sin (sdir);

  return correction;
}
