#ifndef MINRT_H

# define MINRT_H

#include <stdlib.h>
#include <math.h>
#include "mlx_linux/mlx.h"
#include <math.h>
#include <stdio.h>

# define WIDTH 1280
# define HEIGHT 720
# define FOV 20
# define M_PI 3.14159265358979323846
# define HALFPI 1.5708
# define FORWARD 1
# define BACKWARD 0

typedef struct s_image
{
	double **red;
	double **green;
	double **blue;
}	t_image;


typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_vec4
{
	double	a;
	double	b;
	double	c;
	double	d;
}				t_vec4;

typedef struct	s_vec2
{
	double	x;
	double	y;
}				t_vec2;

typedef struct s_ray
{
	t_vec3 *point1;
	t_vec3 *point2;
	t_vec3 *direction;
}	t_ray;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_camera
{
	t_vec3 *position;
	t_vec3 *look_at;
	t_vec3 *camera_up;
	double camera_length;
	double horizontal_size;
	double aspectRatio;
	t_vec3 *alignement_vec;
	t_vec3 *u;
	t_vec3 *v;
	t_vec3 *screen_center;
} t_camera;

typedef struct s_light
{
	t_vec3 *color;
	double intensity;
	t_vec3 *position;
}	t_light;

typedef struct s_matrix
{
	int				rows;
	int				cols;
	double			**matrix;
}	t_matrix;

typedef struct s_object
{
	int id;
	int type;
	int has_material;
	t_vec3 *base_color;
	t_vec3 *mat_color;
	t_vec3 *translation;
	t_vec3 *rotation;
	t_vec3 *scale;
	t_matrix **gtfm;
	double shininess;
	double reflectivity;
	t_matrix *linear;
	
}	t_object;

typedef struct s_int_info
{
	t_object *closest_object;
	t_vec3 *intpoint;
	t_vec3 *localnormal;
	t_vec3 *localcolor;
}	t_int_info;

enum
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
};

# define EPSILON 1e-21f
# define MAX_REF 3


t_vec3 *new_vector3(double x, double y, double z);
double dot_product(t_vec3 *v1, t_vec3 *v2);
t_vec3 *cross(t_vec3 *v1, t_vec3 *v2);
t_vec3 *normalized(t_vec3 *vector);
double normalize(t_vec3 *vector);
double length(t_vec3 *vector);
double length2(t_vec3 *vector);
t_vec3	*vec3_div_number(t_vec3 *vec1, int n);
t_vec3	*vec3_sub(t_vec3 *vec1, t_vec3 *vec2);
t_vec3	*vec3_add(t_vec3 *vec1, t_vec3 *vec2);
t_vec3 *negative_vec3(t_vec3 *vector);
double max(double v1, double v2);
t_vec3 *multiply_vec3_number(t_vec3 *vector, double number);
void initialize_camera(t_camera *camera);
t_ray *generate_ray(double x, double y, t_camera *camera);
void update_camera(t_camera *camera);
void print_vector(t_vec3 *vec);
int intersect_sphere(t_ray *ray, t_matrix **gtfm, t_vec3 *hitposition, t_vec3 *localnormal);
int compute_illumination(t_light *light, t_object *object_list, t_object *current_object, t_vec3 *hitpoint, t_vec3 *localnormal, t_vec3 *color, double *intensity);
t_vec3 *copy_vector(t_vec3 *vec);
t_ray *new_ray(t_vec3 *point1, t_vec3 *point2);
void copy_vector_values(t_vec3 *vec1, t_vec3 *vec2);
t_matrix	*inverse(t_matrix *mt);
double	determinant(t_matrix *mt);
double	cofactor(t_matrix *mt, int row, int column);
double	minor(t_matrix *mt, int row, int column);
void free_matrix(t_matrix *m);
t_matrix *identity_matrix(int r);
t_matrix *new_matrix(int r, int c);
t_matrix *matrix_multiply(const t_matrix *a, const t_matrix *b);
double max_overall(t_image *image);
void my_mlx_put_pixel(t_data *img, int x, int y, int color);
int rgb_to_int(double red, double green, double blue, double max);
void render(t_image *image, void *mlx, void *win);
t_ray *apply_to_ray(t_ray *input_ray, int dirflag, t_matrix **matrices);
t_vec3 *apply_to_vector(t_vec3 *input_vec, int dirflag, t_matrix **matrices);
t_object* init_objects();
t_light *init_light();
int test_intersect_plane(t_ray *ray, t_matrix **gtfm, t_vec3 *hitposition, t_vec3 *localnormal);
int close_enough(double value);
void set_pixel(t_image *image, t_vec3 *color, int x, int y);
t_image *new_image();
void copy_matrix(t_matrix *m1, t_matrix *m2);
int test_intersection(t_ray *ray, t_object *objects, t_int_info *info);
t_vec3 *compute_color(t_object *objects, t_light *lights, t_int_info *object_info, t_ray *camera_ray, int ref_count);
t_vec3 *diffuse_color(t_object *objects, t_light *lights, t_int_info *object_info, t_vec3 *base_color);



//test
void print_matrix(t_matrix *m);
t_vec3 *reflect(t_vec3 *d, t_vec3 *normal);

// matrix aitouna


t_matrix	*matrix(int rows, int cols, double *values);
void	fill_mt(t_matrix *mt, double *values);
double	*create_cols(int c);
t_matrix	*create_matrix(int rows, int cols);
double	determinant(t_matrix *mt);
double	cofactor(t_matrix *mt, int row, int column);
t_matrix	*inverse(t_matrix *mt);
void	set_to_indentity(t_matrix *mt);
void	print_matrix(t_matrix *matrix);
t_matrix	*from_t_vectoro_matrix(t_vec3 vt);
t_matrix	*transpose(t_matrix *mt);
void	delete_matrix(t_matrix *this);
void copy_clmn(double *clm1, double *clm2, int column, int size);
t_matrix *submatrix(t_matrix *mt, int row, int column);
double minor(t_matrix *mt, int row, int column);
t_matrix	*mt_multiplication(t_matrix *mt1, t_matrix *mt2);
t_matrix	*safe_matrix_multy(t_matrix *mt1, t_matrix *mt2);

t_matrix	*rotation_matrix_y(double angle);
t_matrix	*rotation_matrix_x(double angle);
t_matrix	*rotation_matrix_z(double angle);
t_matrix	*translation_matrix(t_vec3 *translation);
t_matrix	*scal_matrix(t_vec3 *scal);
t_matrix	**set_transform(t_vec3 *translation, t_vec3 *rotation, t_vec3 *scal);
t_ray	*apply_transform(t_ray *input_ray, t_matrix **gtfm, int dirFlag);
t_vec3	*apply_transform_vector(t_vec3 *inputVector, int dirFlag, t_matrix **gtfm);


//cylinder test intersection
int test_cylinder(t_ray *ray, t_matrix **gtfm, t_vec3 *hitpoint, t_vec3 *localnormal);

// cone intersection
int test_cone(t_ray *ray, t_matrix **gtfm, t_vec3 *hitpoint, t_vec3 *localnormal);
t_vec3 *fixed_normal(t_matrix *forward, t_vec3 *hitpoint);
#endif