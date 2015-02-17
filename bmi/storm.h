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
  int t_end;          /* last time step */
  int t_next;         /* next time step for which data are read */
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
} StormModel;

extern StormModel * storm_from_default (void);
extern int storm_free (StormModel *self);

#if defined(__cplusplus)
}
#endif

#endif
