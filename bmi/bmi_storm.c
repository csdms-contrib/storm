#include <stdio.h>
#include <stdlib.h>

#include "bmi_storm.h"
#include "storm.h"


int
Initialize (const char *file, void **handle)
{
  StormModel *self = NULL;

  if (!handle)
    return BMI_FAILURE;

  if (file)
    self = storm_from_input_file (file);
  else
    self = storm_from_default ();

  *handle = (void *) self;

  return BMI_SUCCESS;
}


int
Update (void *self)
{
  storm_advance_time ((StormModel *) self);

  return BMI_SUCCESS;
}


static int
Update_frac (void *self, double f)
{
  if (f>0) {
    double dt;

    Get_time_step (self, &dt);

    ((StormModel *)self)->dt = f * dt;

    Update (self);

    ((StormModel *)self)->dt = dt;
  }

  return BMI_SUCCESS;
}


static int
Update_until (void *self, double t)
{
  {
    double dt;
    double now;

    Get_time_step (self, &dt);
    Get_current_time (self, &now);

    {
      int n;
      const double n_steps = (t - now) / dt;
      for (n=0; n<(int)n_steps; n++) {
        Update (self);
      }

      Update_frac (self, n_steps - (int)n_steps);
    }
  }

  return BMI_SUCCESS;
}


int
Finalize (void *self)
{
  if (self)
    storm_free (self);

  return BMI_SUCCESS;
}


static int
Get_start_time (void *self, double * time)
{
  if (time) {
    *time = 0.;
    return BMI_SUCCESS;
  }
  else {
    return BMI_FAILURE;
  }
}


static int
Get_end_time (void *self, double * time)
{
  *time = ((StormModel *)self)->t_end;
  return BMI_SUCCESS;
}


static int
Get_time_step (void *self, double * dt)
{
  *dt = ((StormModel *)self)->dt;
  return BMI_SUCCESS;
}


static int
Get_time_units (void *self, char * units)
{
  strncpy (units, "-", BMI_MAX_UNITS_NAME);
  return BMI_SUCCESS;
}


static int
Get_current_time (void *self, double * time)
{
  *time = ((StormModel *)self)->t;
  return BMI_SUCCESS;
}
