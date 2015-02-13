#ifndef STORM_H_INCLUDED
#define STORM_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif


typedef struct {
  int t;              // current time step
  int t_end;          // last time step
  int shape[2];       // grid dimensions 
  double spacing[2];  // grid spacing [m]
} StormModel;


#if defined(__cplusplus)
}
#endif

#endif
