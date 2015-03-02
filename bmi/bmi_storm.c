#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bmi/bmi.h>

#include "bmi_storm.h"
#include "storm.h"


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


static int
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


static int
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


static int
Finalize (void *self)
{
  if (self)
    storm_free (self);

  return BMI_SUCCESS;
}


BMI_Model *
Construct_storm_bmi(BMI_Model *model)
{
  if (model) {
    model->self = NULL;

    model->initialize = Initialize;
    model->update = Update;
    model->update_until = Update_until;
    model->update_frac = Update_frac;
    model->finalize = Finalize;
    model->run_model = NULL;

    /* model->get_component_name = Get_component_name; */
    /* model->get_input_var_name_count = Get_input_var_name_count; */
    /* model->get_output_var_name_count = Get_output_var_name_count; */
    /* model->get_input_var_names = Get_input_var_names; */
    /* model->get_output_var_names = Get_output_var_names; */

    /* model->get_var_type = Get_var_type; */
    /* model->get_var_units = Get_var_units; */
    /* model->get_var_rank = Get_var_rank; */
    /* model->get_var_size = Get_var_size; */
    /* model->get_var_nbytes = Get_var_nbytes; */
    model->get_current_time = Get_current_time;
    model->get_start_time = Get_start_time;
    model->get_end_time = Get_end_time;
    model->get_time_units = Get_time_units;
    model->get_time_step = Get_time_step;

    /* model->get_value = Get_value; */
    /* model->get_value_ptr = Get_value_ptr; */
    /* model->get_value_at_indices = Get_value_at_indices; */

    /* model->set_value = Set_value; */
    /* model->set_value_ptr = NULL; */
    /* model->set_value_at_indices = Set_value_at_indices; */

    /* model->get_grid_type = Get_grid_type; */
    /* model->get_grid_shape = Get_grid_shape; */
    /* model->get_grid_spacing = Get_grid_spacing; */
    /* model->get_grid_origin = Get_grid_origin; */

    /* model->get_grid_x = NULL; */
    /* model->get_grid_y = NULL; */
    /* model->get_grid_z = NULL; */
  }

  return model;
}
