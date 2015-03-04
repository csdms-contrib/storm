#ifndef BMILIB_H_INCLUDED
#define BMILIB_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

#include "bmi.h"


int BMI_Initialize(BMI_Model*, const char *);
int BMI_Update(BMI_Model*);
int BMI_Update_until(BMI_Model *, double);
int BMI_Update_frac(BMI_Model *, double);
int BMI_Finalize(BMI_Model *);
int BMI_Run_model(BMI_Model *);

int BMI_Get_component_name(BMI_Model*, char *);
int BMI_Get_input_var_name_count(BMI_Model *, int *);
int BMI_Get_output_var_name_count(BMI_Model *, int *);
int BMI_Get_input_var_names(BMI_Model *, char **);
int BMI_Get_output_var_names(BMI_Model *, char **);

int BMI_Get_time_units(BMI_Model*, char *);
int BMI_Get_time_step(BMI_Model*, double *);
int BMI_Get_current_time(BMI_Model*, double *);
int BMI_Get_start_time(BMI_Model*, double *);
int BMI_Get_end_time(BMI_Model*, double *);

int BMI_Get_var_type(BMI_Model * model, const char * name, char * type);
int BMI_Get_var_units(BMI_Model * model, const char * name, char * units);
int BMI_Get_var_rank(BMI_Model * model, const char * name, int * rank);
int BMI_Get_var_size(BMI_Model * model, const char * name, int * rank);
int BMI_Get_var_nbytes(BMI_Model * model, const char * name, int * nbytes);

int BMI_Get_value(BMI_Model *, const char *, void *);
int BMI_Get_value_ptr(BMI_Model *, const char *, void **);
int BMI_Get_value_at_indices(BMI_Model *, const char *, void *, int *, int);

int BMI_Set_value(BMI_Model *, const char *, void *);
int BMI_Set_value_ptr(BMI_Model *, const char *, void **);
int BMI_Set_value_at_indices(BMI_Model *, const char *, int *, int, void *);

int BMI_Get_grid_type(BMI_Model * model, const char * name, char * type);
int BMI_Get_grid_shape(BMI_Model * model, const char * name, int * shape);
int BMI_Get_grid_spacing(BMI_Model * model, const char * name, double * spacing);
int BMI_Get_grid_origin(BMI_Model * model, const char * name, double * origin);

int BMI_Get_grid_x(BMI_Model * model, const char * name, double * x);
int BMI_Get_grid_y(BMI_Model * model, const char * name, double * y);
int BMI_Get_grid_z(BMI_Model * model, const char * name, double * z);

int BMI_Get_grid_cell_count(BMI_Model * model, const char * name, int * n_cells);
int BMI_Get_grid_point_count(BMI_Model * model, const char * name, int * n_points);
int BMI_Get_grid_vertex_count(BMI_Model * model, const char * name, int * n_verts);

int BMI_Get_grid_connectivity(BMI_Model * model, const char * name, int * connectivity);
int BMI_Get_grid_offset(BMI_Model * model, const char * name, int * offset);


#if defined(__cplusplus)
}
#endif

#endif
