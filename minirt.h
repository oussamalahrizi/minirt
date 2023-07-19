#ifndef MINRT_H

# define MINRT_H

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 800

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
	t_vec3	center;
	double	radius;
	t_color	color;
}				t_sphere;

typedef struct	s_scene
{
	t_sphere	sphere;
}				t_scene;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

t_vec3 *new_vector3(double x, double y, double z);
double dot_product(t_vec3 *v1, t_vec3 *v2);
t_vec3 *cross(t_vec3 *v1, t_vec3 *v2);
t_vec3 *normalized(t_vec3 *vector);
double normalize(t_vec3 *vector);
double length(t_vec3 *vector);
double length2(t_vec3 *vector);
t_vec3	*vec3_div_number(t_vec3 *vec1, int n);
t_vec3	*vec3_sub(t_vec3 *vec1, t_vec3 *vec2);
t_vec3 *negative_vec3(t_vec3 *vector);
double max(double v1, double v2);
t_vec3 *multiply_vec3_number(t_vec3 *vector, double number);

#endif