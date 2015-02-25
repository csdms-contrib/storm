/*
  A faithful translation of `storm` from Fortran 77 to C.
  
  Mark Piper (mark.piper@colorado.edu
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Names of input and output files.
#define FILE_WIND_IN "wind.in"
#define FILE_WDIR_OUT "wdir.data"
#define FILE_WINDX_OUT "windx.data"
#define FILE_WINDY_OUT "windy.data"

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

#define ACOR 0.0
#define RHOA 1.22     // air density [kg/m3]
#define F 0.000061618 // Coriolis parameter [rad/s]

int main(void) {

  int lmax;          // maximum number of timesteps over which winds computed
  int mcent, ncent;  // initial (i,j) position of storm center in grid
  int im, jm;        // grid dimensions [m]
  int i, j, l;       // loop counters
  int i3, i4;        // loop counter limits
  int lsc;           // the next timestep for which data are to be read

  int li = 25, lj = 25, lt = 10;
  double taux[lt][lj][li], tauy[lt][lj][li];   // component shear stresses
  double windx[lt][lj][li], windy[lt][lj][li]; // component winds
  double wdir[lt][lj][li];                     // wind direction

  double dx, dy;        // grid cell size [m]
  double svel, sdir;    // storm speed [m/s] and direction [deg CCW from east]
  double pcent, pedge;  // pressure [Pa] at eye and edge
  double rmaxw;         // radius of max storm winds [m]
  double srad;          // storm radius [m]
  double a, r, cc, phi; // temp variables for calculations
  double defcon, defx, dxt, dyt, wspd;
  double usm, usmx, usmy, wspdx, wspdy, w;
  double cd;            // drag coefficient
  double stress;        // wind shear stress

  FILE *fp_wind_in, *fp_windx, *fp_windy, *fp_wdir; // file pointers
  char *line = NULL;
  size_t len = 0;

  // Open input file for reading.
  fp_wind_in = fopen(FILE_WIND_IN, "r");

  // Read max timesteps, grid dimensions, grid cell size.
  fscanf(fp_wind_in, "%d %d %d %lf %lf", &lmax, &im, &jm, &dx, &dy);
  getline(&line, &len, fp_wind_in);

  // The main computation loop.
  for (l = 0; l < lmax; l++) {

    // Read the location of the storm center and other variables for
    // selected timesteps.
    if (l == 0 || l == lsc) {
      fscanf(fp_wind_in, "%d %d %d", &mcent, &ncent, &lsc);
      getline(&line, &len, fp_wind_in);
      fscanf(fp_wind_in, "%lf %lf %lf %lf %lf %lf %lf",			\
	     &svel, &sdir, &pcent, &pedge, &rmaxw, &srad, &defcon);
      sdir += ACOR;
      sdir = M_PI * sdir / 180.f;

      // Decrement location of center node in translation from Fortran
      // to C.
      mcent--;
      ncent--;
    }

    // Solve the quadratic equation for wind speed at each grid
    // cell. Only northern hemisphere cases are considered.
    for (i = 0; i < im; i++) {
      for (j = 0; j < jm; j++) {
	if (i == mcent && j == ncent) {
	  wspd = svel;
	  phi = sdir;
	} else {
	  dxt = fabs((i - mcent)*dx);
	  dyt = fabs((j - ncent)*dy);
	  r = sqrt(dxt*dxt + dyt*dyt);
	  a = 1.f / r;
	  cc = -((pedge - pcent)/RHOA)*(rmaxw*(a*a))*exp(-rmaxw*a);
	  wspd = (sqrt(F*F - 4.f*a*cc) - F)/(2.f*a);

	  // Each node is analyzed for the angle of the wind at that
	  // position. The value of phi found here will be used in
	  // finding the shear stress at the surface.  
	  if (j > ncent) {
	    // Nodes north of the storm center.
	    if (i == mcent) phi = M_PI;
	    if (i < mcent) phi = atan(dxt/dyt) + M_PI;
	    if (i > mcent) phi = atan(dyt/dxt) + (M_PI / 2.f);
	  } else if (j == ncent) {
	    // Nodes at the same latitude as the storm center.
	    if (i < mcent) phi = 1.5f * M_PI;
	    if (i > mcent) phi = M_PI / 2.f;
	  } else if (j < ncent) {
	    // Nodes south of the storm center.
	    if (i == mcent) phi = 0.f;
	    if (i < mcent) phi = atan(dyt/dxt) + (1.5f * M_PI);
	    if (i > mcent) phi = atan(dxt/dyt);
	  }
	  phi += defcon * defx * r / rmaxw * M_PI / 180.f;
	}
	
	// For a moving storm a correction factor allows for increased
	// winds.
	usm = rmaxw * r / (rmaxw*rmaxw + r*r) * svel;
	usmy = usm * cos(sdir);
	usmx = usm * sin(sdir);

	// Calculate wind speed and direction.
	wspdx = (wspd * cos(phi)) + usmx;
	wspdy = (wspd * sin(phi)) + usmy;
	wspd = sqrt(wspdx*wspdx + wspdy*wspdy);
	windx[l][j][i] = wspdx;
	windy[l][j][i] = wspdy;
	wdir[l][j][i] = (phi * 180.f / M_PI) - ACOR;

	// Calculate drag coefficient and wind shear stress.
	w = wspd * 0.1f;
	if (w <= 6.f) {
	  cd = 0.0011f;
	} else if (w > 6.f && w <= 22.f) {
	  cd = 0.001f * (0.61f + 0.63f*w);
	} else if (w > 22.f) {
	  cd = 0.001f * (1.f + 0.07f*w);
	}
	stress = cd * RHOA * (wspd*wspd);
	taux[l][j][i] = stress*cos(phi);
	tauy[l][j][i] = stress*sin(phi);
      }
    }
  } // end main computation loop

  // Close input file.
  fclose(fp_wind_in);

  // Write output files. Note that index limits are decremented in
  // translation from Fortan to C.
  fp_windx = fopen(FILE_WINDX_OUT, "w");
  fp_windy = fopen(FILE_WINDY_OUT, "w");
  fp_wdir = fopen(FILE_WDIR_OUT, "w");
  for (l = 0; l < lmax; l++) {
    i3 = 0;
    i4 = 6;
    while (i3 < im) {
      i4 = MIN((im - 1), i4);
      fprintf(fp_windx, "%6d\n", l + 1);
      fprintf(fp_windy, "%6d\n", l + 1);
      for (j = 0; j < jm; j++) {
	for (i = i3; i <= i4; i++) {
	  fprintf(fp_wdir, "%10.2e", wdir[l][j][i]);
	  fprintf(fp_windx, "%10.2e", windx[l][j][i]);
	  fprintf(fp_windy, "%10.2e", windy[l][j][i]);
	}
	fprintf(fp_wdir, "\n");
	fprintf(fp_windx, "\n");
	fprintf(fp_windy, "\n");
      }
      i3 = i4 + 1;
      i4 = i4 + 7;
    }
  }
  fclose(fp_windx);
  fclose(fp_windy);
  fclose(fp_wdir);

  return 0;
}
