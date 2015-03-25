#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <bmi_storm.h>
#include <bmilib.h>


int
main (void)
{
  int status = BMI_SUCCESS;
  BMI_Model *model = (BMI_Model *)malloc (sizeof(BMI_Model));

  register_bmi_storm (model);

  {
    fprintf (stdout, "Initializing... ");
    fflush (stdout);

    status = BMI_Initialize (model, NULL);
    if (status == BMI_FAILURE)
      return EXIT_FAILURE;

    fprintf (stdout, "PASS\n");
  }

  {
    char name[BMI_MAX_COMPONENT_NAME];

    status = BMI_Get_component_name (model, name);
    if (status == BMI_FAILURE)
      return EXIT_FAILURE;

    fprintf (stdout, "%s\n", name);
  }

  {
    int i;
    const int n_steps = 10;
    const double t_until = 100.5;
    double time;
    double dt;

    status = BMI_Get_time_step(model, &dt);
    if (status == BMI_FAILURE)
      return EXIT_FAILURE;

    for (i = 0; i < n_steps; i++)
    {
      fprintf (stdout, "Running until t = %d... ", i+1);

      status = BMI_Update (model);
      if (status == BMI_FAILURE)
        return EXIT_FAILURE;
      
      status = BMI_Get_current_time (model, &time);
      if (status == BMI_FAILURE)
        return EXIT_FAILURE;

      if (fabs (time / dt - (i + 1)) < 1e-6)
        fprintf (stdout, "PASS\n");
      else
        return EXIT_FAILURE;
    }

    fprintf (stdout, "Running until t = %f... ", t_until);

    status = BMI_Update_until (model, t_until);
    if (status == BMI_FAILURE)
      return EXIT_FAILURE;

    status = BMI_Get_current_time (model, &time);
    if (status == BMI_FAILURE)
      return EXIT_FAILURE;

    if (fabs (time - t_until) < 1e-6)
      fprintf (stdout, "PASS\n");
    else {
      fprintf (stdout, "%f\n", time);
      return EXIT_FAILURE;
    }
  }

  fprintf (stdout, "Finalizing... ");

  status = BMI_Finalize (model);
  if (status == BMI_FAILURE)
    return EXIT_FAILURE;

  fprintf (stdout, "PASS\n");

  free (model);

  return EXIT_SUCCESS;
}
