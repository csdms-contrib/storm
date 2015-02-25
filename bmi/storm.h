#ifndef STORM_H_INCLUDED
#define STORM_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

#define ACOR 0.0
#define RHOA 1.22
#define F 0.000061618

typedef struct {
  int t;              /* current time step */
  int dt;             /* time increment */
  int t_end;          /* last time step */
  int shape[2];       /* grid dimensions */
  double spacing[2];  /* grid spacing [m] */
  int center[2];      /* grid cell of storm center */
  double sspd;        /* storm speed [m/s] */
  double sdir;        /* storm direction [deg CCW from east] */
  double pcent;       /* pressure at storm center [Pa] */
  double pedge;       /* pressure at storm edge [Pa] */
  double rmaxw;       /* radius of maximum winds [m] */
  double srad;        /* storm radius [m] */
  double defcon;
  double **wdir;      /* wind direction */
  double **wspd;      /* wind speed */
  double **windx;     /* x-component of wind */
  double **windy;     /* y-component of wind */
} StormModel;

extern StormModel * storm_from_default (void);
extern StormModel * storm_from_input_file (const char *filename);
extern int storm_free (StormModel *self);
extern int storm_advance_time (StormModel *self);
extern int storm_compute_wind (double **wdir, double **wspd,
			       double **windx, double **windy,
			       int shape[2], double spacing[2],
			       int center[2], double sspd, double sdir,
			       double pcent, double pedge, double rmaxw,
			       double srad, double defcon);
extern int storm_write_output (const char *filename, double **, int shape[2]);

#if defined(__cplusplus)
}
#endif

#endif
