#include <stdio.h>
#include <stdlib.h>

#include "bmi_storm.h"
#include "bmilib.h"


void print_var_values (void *model, const char *var_name);

int
main (void)
{
  double *new_vals = NULL;
  int err = 0;
  BMI_Model * model = (BMI_Model*)malloc (sizeof(BMI_Model));

  register_bmi_storm (model);

  err = BMI_Initialize (model, NULL);
  if (err)
    return EXIT_FAILURE;

  {
    char name[BMI_MAX_COMPONENT_NAME];
    BMI_Get_component_name (model, name);
  
    fprintf (stdout, "%s\n", name);
  }

  { /* Get grid information */
    int n_dims;
    int *shape;
    int len = 0;
    int i;

    BMI_Get_var_rank (model, 
		      "atmosphere_air_flow__east_component_of_velocity", 
		      &n_dims);
    shape = (int*) malloc (sizeof (int)*n_dims);

    BMI_Get_grid_shape (model, 
			"atmosphere_air_flow__east_component_of_velocity", 
			shape);
    for (i = 0, len = 1; i < n_dims; i++)
      len *= shape[i];

    new_vals = (double *)malloc (sizeof (double) * len);
    for (i = 0; i < len; i++)
      new_vals[i] = -1;

    free (shape);
  }

  fprintf (stdout, "Values before set\n");
  fprintf (stdout, "=================\n");
  print_var_values (model, "atmosphere_air_flow__east_component_of_velocity");

  BMI_Set_value (model, 
		 "atmosphere_air_flow__east_component_of_velocity", 
		 new_vals);

  fprintf (stdout, "Values after set\n");
  fprintf (stdout, "================\n");
  print_var_values (model, "atmosphere_air_flow__east_component_of_velocity");

  {
    int inds[5] = {1, 2, 4, 8, 16};
    double vals[5] = {11, 22, 44, 88, 1616};
    double *p;
    int i;

    BMI_Set_value_at_indices (model, 
			      "atmosphere_air_flow__east_component_of_velocity",
			      inds, 5, vals);
    print_var_values (model, "atmosphere_air_flow__east_component_of_velocity");

    BMI_Get_value_ptr (model, 
		       "atmosphere_air_flow__east_component_of_velocity", 
		       (void**)(&p));
    for (i=0; i<5; i++) {
      fprintf (stdout, "Checking %d...", inds[i]);
      if (p[inds[i]] == vals[i])
        fprintf (stdout, "PASS\n");
    }
  }

  free (new_vals);

  BMI_Finalize (model);

  free (model);

  return EXIT_SUCCESS;
}

void
print_var_values (void *model, const char *var_name)
{
  double *var = NULL;
  int n_dims = 0;
  int *shape = NULL;

  BMI_Get_var_rank (model, var_name, &n_dims);
  shape = (int*) malloc (sizeof (int)*n_dims);

  BMI_Get_grid_shape (model, 
		      "atmosphere_air_flow__east_component_of_velocity", 
		      shape);
  BMI_Get_value_ptr (model, var_name, (void**)(&var));

  fprintf (stdout, "Variable: %s\n", var_name);
  fprintf (stdout, "Number of dimensions: %d\n", n_dims);
  fprintf (stdout, "Shape: %d x %d\n", shape[0], shape[1]);
  fprintf (stdout, "================\n");

  {
    int i, j;
    for (i = 0; i < shape[0]; i++) {
      for (j = 0; j < shape[1]; j++)
        fprintf (stdout, "%f ", var[i*shape[1]+j]);
      fprintf (stdout, "\n");
    }
  }

  return;
}
