#ifndef MINRT_H

# define MINRT_H

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>

# define WIDTH 1280
# define HEIGHT 720
# define FOV 70
# define HALFPI 1.5708
typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_vec2
{
	double	x;
	double	y;
}				t_vec2;

typedef struct	s_ray
{
	t_vec3	*origin;
	t_vec3	*direction;
}				t_ray;

typedef struct	s_color
{
	int		red;
	int		green;
	int		blue;
}				t_color;

typedef struct	s_sphere
{
	t_vec3	*center;
	double	radius;
	t_color	*color;
}				t_sphere;

typedef struct	s_scene
{
	t_sphere	*sphere;
}				t_scene;

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
	t_color color;
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
int intersect_sphere(t_ray *ray, t_vec3 **hitposition);
int compute_illumination(t_light *light, t_vec3 *hitpoint, t_color *color, double *intensity);
#endif