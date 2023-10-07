#ifndef MINRT_H

# define MINRT_H

#include <stdlib.h>
#include <math.h>
#include "mlx_linux/mlx.h"
#include <math.h>
#include <stdio.h>

# define WIDTH 1280
# define HEIGHT 720
# define FOV 15
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

typedef struct s_matrix
{
	int rows;
	int cols;
	double **data;
}	t_matrix;

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
int intersect_sphere(t_ray *ray, t_vec3 *hitposition, t_vec3 *localnormal, t_vec3 *localcolor);
int compute_illumination(t_light *light, t_vec3 *hitpoint, t_vec3 *color, double *intensity);
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
#endif