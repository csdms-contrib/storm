#ifndef STORM_H_INCLUDED
#define STORM_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

#define ACOR 0.0
#define RHOA 1.22         /* air density [kg/m3] */
#define F 0.000061618     /* Coriolis parameter [rad/s] */
#define MAX_LEN 1024
#define PI 3.14159265358979323846264338327

typedef struct {
  char filename[MAX_LEN]; /* input file */
  double t;               /* current time step */
  double dt;              /* time increment */
  double t_end;           /* last time step */
  int shape[2];           /* grid dimensions */
  double spacing[2];      /* grid spacing [m] */
  int center[2];          /* grid cell of storm center */
  double sspd;            /* storm speed [m/s] */
  double sdir;            /* storm direction [deg CCW from east] */
  double pcent;           /* pressure at storm center [Pa] */
  double pedge;           /* pressure at storm edge [Pa] */
  double rmaxw;           /* radius of maximum winds [m] */
  double srad;            /* storm radius [m] */
  double **wdir;          /* wind direction */
  double **wspd;          /* wind speed */
  double **windx;         /* x-component of wind */
  double **windy;         /* y-component of wind */
} StormModel;

extern StormModel * storm_from_default (void);
extern StormModel * storm_from_input_file (const char *filename);
extern int storm_free (StormModel *self);
extern int storm_advance_time (StormModel *self);
extern int compute_wind (double **wdir, double **wspd, double **windx,
			 double **windy, int shape[2], double spacing[2],
			 int center[2], double sspd, double sdir, double pcent,
			 double pedge, double rmaxw, double srad);
extern int storm_write_output (const char *filename, double **, int shape[2]);

#if defined(__cplusplus)
}
#endif

#endif
