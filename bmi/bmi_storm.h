#ifndef BMI_STORM_H_INCLUDED
#define BMI_STORM_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

#define BMI_SUCCESS (0)
#define BMI_FAILURE (1)

#define BMI_MAX_UNITS_NAME (2048)
#define BMI_MAX_COMPONENT_NAME (2048)
#define BMI_MAX_VAR_NAME (2048)


/* Model Control functions */
int BMI_STORM_Initialize (const char *, void**);
int BMI_STORM_Update (void *);
int BMI_STORM_Update_until (void *, double);
int BMI_STORM_Update_frac (void *, double);
int BMI_STORM_Finalize (void *);
int BMI_STORM_Run_model (void *);

/* Model information functions */
int BMI_STORM_Get_component_name (void *, char *);
int BMI_STORM_Get_input_var_name_count (void *, int *);
int BMI_STORM_Get_output_var_name_count (void *, int *);
int BMI_STORM_Get_input_var_names (void *, char **);
int BMI_STORM_Get_output_var_names (void *, char **);

/* Variable information functions */
int BMI_STORM_Get_var_type (void *, const char *, char *);
int BMI_STORM_Get_var_units (void *, const char *, char *);
int BMI_STORM_Get_var_rank (void *, const char *, int *);
int BMI_STORM_Get_var_size (void *, const char *, int *);
int BMI_STORM_Get_var_nbytes (void *, const char *, int *);
int BMI_STORM_Get_current_time (void *, double *);
int BMI_STORM_Get_start_time (void *, double *);
int BMI_STORM_Get_end_time (void *, double *);
int BMI_STORM_Get_time_units (void *, char *);
int BMI_STORM_Get_time_step (void *, double *);

/* Variable getter and setter functions */
int BMI_STORM_Get_value (void *, const char *, void *);
int BMI_STORM_Get_value_ptr (void *, const char *, void **);
int BMI_STORM_Get_value_at_indices (void *, const char *, void *, int *, int);

int BMI_STORM_Set_value (void *, const char *, void *);
int BMI_STORM_Set_value_ptr (void *, const char *, void **);
int BMI_STORM_Set_value_at_indices (void *, const char *, int *, int, void *);

/* Grid information functions */
int BMI_STORM_Get_grid_type (void *, const char *, char *);
int BMI_STORM_Get_grid_shape (void *, const char *, int *);
int BMI_STORM_Get_grid_spacing (void *, const char *, double *);
int BMI_STORM_Get_grid_origin (void *, const char *, double *);

int BMI_STORM_Get_grid_x (void *, const char *, double *);
int BMI_STORM_Get_grid_y (void *, const char *, double *);
int BMI_STORM_Get_grid_z (void *, const char *, double *);

int BMI_STORM_Get_grid_cell_count (void *, const char *, int *);
int BMI_STORM_Get_grid_point_count (void *, const char *, int *);
int BMI_STORM_Get_grid_vertex_count (void *, const char *, int *);

int BMI_STORM_Get_grid_connectivity (void *, const char *, int *);
int BMI_STORM_Get_grid_offset (void *, const char *, int *);

#if defined(__cplusplus)
}
#endif

#endif
