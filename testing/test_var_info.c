#include <stdio.h>
#include <stdlib.h>

#include "bmi_storm.h"
#include "bmilib.h"
#include "storm.h"


void print_var_info (BMI_Model *model, const char *var);

int
main (void)
{
  BMI_Model *model = (BMI_Model*)malloc (sizeof(BMI_Model));

  Construct_storm_bmi(model);

  BMI_Initialize (model, NULL);

  {
    char name[BMI_MAX_COMPONENT_NAME];
    BMI_Get_component_name (model, name);
    fprintf (stdout, "%s\n", name);
  }

  { /* Input items */
    int n_names;
    char **names = NULL;
    int i;

    BMI_Get_input_var_name_count(model, &n_names);

    names = (char**) malloc (sizeof(char*) * n_names);
    for (i = 0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof (char) * BMI_MAX_VAR_NAME);

    BMI_Get_input_var_names (model, names);
    fprintf (stdout, "\n");
    fprintf (stdout, "Input Variables\n");
    fprintf (stdout, "===============\n");
    fprintf(stdout, "Number of variables: %d\n", n_names); fflush(stdout);
    for (i = 0; i<n_names; i++)
      print_var_info (model, names[i]);

    for (i = 0; i<n_names; i++)
      free (names[i]);
    free (names);
  }

  { /* Output items */
    int n_names;
    char **names = NULL;
    int i;

    BMI_Get_output_var_name_count(model, &n_names);

    names = (char**) malloc (sizeof(char*) * n_names);
    for (i = 0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof (char) * BMI_MAX_VAR_NAME);

    BMI_Get_output_var_names (model, names);
    fprintf (stdout, "\n");
    fprintf (stdout, "Output Variables\n");
    fprintf (stdout, "================\n");
    fprintf(stdout, "Number of variables: %d\n", n_names); fflush(stdout);
    for (i = 0; i<n_names; i++)
      print_var_info (model, names[i]);

    for (i = 0; i<n_names; i++)
      free (names[i]);
    free (names);
  }

  BMI_Finalize (model);

  free (model);

  return EXIT_SUCCESS;
}

void
print_var_info (BMI_Model *model, const char *var)
{
  char type[BMI_MAX_TYPE_NAME];
  char units[BMI_MAX_UNITS_NAME];
  int n_dims = 0;
  int size = 0;
  int n_bytes = 0;

  BMI_Get_var_type (model, var, type);
  BMI_Get_var_units (model, var, units);
  BMI_Get_var_rank (model, var, &n_dims);
  BMI_Get_var_size (model, var, &size);
  BMI_Get_var_nbytes (model, var, &n_bytes);

  fprintf (stdout, "\n");
  fprintf (stdout, "Name: %s\n", var);
  fprintf (stdout, "Type: %s\n", type);
  fprintf (stdout, "Units: %s\n", units);
  fprintf (stdout, "Rank: %d\n", n_dims);
  fprintf (stdout, "Size: %d\n", size);
  fprintf (stdout, "Bytes: %d\n", n_bytes);

  return;
}
