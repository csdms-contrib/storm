#ifndef STORM_H_INCLUDED
#define STORM_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct {
  int t;              /* current time step */
  int t_end;          /* last time step */
  int t_next;         /* next time step for which data are read */
  int shape[2];       /* grid dimensions */
  double spacing[2];  /* grid spacing [m] */
  int center[2];      /* grid cell of storm center */
  double **wdir;      /* wind direction */
  double **wspd;      /* wind speed */
} StormModel;

extern StormModel * storm_from_default (void);
extern int storm_free (StormModel *self);

#if defined(__cplusplus)
}
#endif

#endif
