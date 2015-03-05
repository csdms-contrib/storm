#include <stdio.h>
#include <stdlib.h>

#include "bmi_storm.h"
#include "bmilib.h"

void print_var_names (void *model);

int
main (void)
{
  BMI_Model * model = (BMI_Model *)malloc (sizeof(BMI_Model));

  Construct_storm_bmi (model);

  if (BMI_Initialize (model, NULL)!=0 || !model)
    return EXIT_FAILURE;

  {
    char name[BMI_MAX_COMPONENT_NAME];
    BMI_Get_component_name (model, name);
    fprintf (stdout, "%s\n\n", name);
  }

  print_var_names (model);

  if (BMI_Finalize (model) != 0)
    return EXIT_FAILURE;

  free (model);

  return EXIT_SUCCESS;
}

void
print_var_names (void *model)
{
  { /* Print the input var names */
    int n_names;
    char **names = NULL;
    int i;

    BMI_Get_input_var_name_count(model, &n_names);

    names = (char**) malloc (sizeof(char *) * n_names);
    for (i=0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);

    BMI_Get_input_var_names (model, names);

    fprintf (stdout, "Input var names\n");
    fprintf (stdout, "===============\n");
    for (i = 0; i<n_names; i++)
      fprintf (stdout, "%s\n", names[i]);

    for (i=0; i<n_names; i++)
      free (names[i]);
    free (names);

  }

  fprintf (stdout, "\n");

  { /* Print the output var names */
    int n_names;
    char **names = NULL;
    int i;

    BMI_Get_output_var_name_count(model, &n_names);

    names = (char**) malloc (sizeof(char *) * n_names);
    for (i=0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);

    BMI_Get_output_var_names (model, names);

    fprintf (stdout, "Output var names\n");
    fprintf (stdout, "===============\n");
    for (i = 0; i<n_names; i++)
      fprintf (stdout, "%s\n", names[i]);

    for (i=0; i<n_names; i++)
      free (names[i]);
    free (names);

  }
}
