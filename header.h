/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:04:06 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/30 21:58:35 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <mlx.h>
# include "parse/parse.h"
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <stdint.h>
# include <limits.h>

# define WIDTH 800
# define HEIGHT 600
# define M_PI 3.14159265358979323846
# define HALFPI 1.5708
# define FLT_MAX 3.40282346638528859811704183484516925e+38F
# define FORWARD 1
# define BACKWARD 0
# define KEYCODE_ESC 65307
# define EPSILON 1e-21f
# define MAX_REF 1

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_diff
{
	float	red;
	float	green;
	float	blue;
	int		validillum;
	int		illumfound;
	t_vec3	diff_color;
	float	intensity;
}	t_diff;

// for norminette
typedef struct s_int
{
	int		i;
	float	dist;
	float	mindist;
	int		validint;
	int		intfound;
	t_info	test;
}	t_int;

typedef struct s_rt
{
	int		x;
	int		y;
	int		intfound;
	t_ray	ray;
	float	xfact;
	float	yfact;
	float	normx;
	float	normy;
	t_info	info;
	t_vec3	color;
}	t_rt;

// vectors
float			square(float x);
float			length(t_vec3 a);
t_vec3			normalized(t_vec3 a);
float			dot_product(t_vec3 a, t_vec3 b);
t_vec3			cross(t_vec3 a, t_vec3 b);
t_vec3			scale_vector(t_vec3 a, float t);
t_vec3			vec_sub(t_vec3 a, t_vec3 b);
t_vec3			vec_add(t_vec3 a, t_vec3 b);
t_vec3			new_vector(float x, float y, float z);
void			copy_vec_values(t_vec3 *a, t_vec3 *b);
t_vec3			reflect(t_vec3 d, t_vec3 normal);
t_vec3			get_rotation_vector(t_vec3 normal);
t_vec3			get_up_vector(t_vec3 forward);
void			print_vector(t_vec3 a);
// random	
float			random_float(unsigned int *rng_state, float min, float max);
// matrices	
void			fill_mt(t_matrix *mt, float *values);
float			*create_cols(int c);
t_matrix		*create_matrix(int rows, int cols);
float			determinant(t_matrix *mt);
float			cofactor(t_matrix *mt, int row, int column);
t_matrix		*inverse(t_matrix *mt);
void			set_to_indentity(t_matrix *mt);
void			print_matrix(t_matrix *matrix);
t_matrix		*transpose(t_matrix *mt);
void			delete_matrix(t_matrix *this);
void			copy_clmn(float *clm1, float *clm2, int column, int size);
t_matrix		*submatrix(t_matrix *mt, int row, int column);
float			minor(t_matrix *mt, int row, int column);
t_matrix		*mt_multiplication(t_matrix *mt1, t_matrix *mt2);
t_matrix		*safe_matrix_multy(t_matrix *mt1, t_matrix *mt2);
void			init_camera(t_camera *cam);
t_ray			new_ray(t_vec3 point1, t_vec3 point2);
t_ray			generate_ray(float x, float y, t_camera *cam);
// gtfm	
t_matrix		*rotation_matrix_y(double angle);
t_matrix		*rotation_matrix_x(double angle);
t_matrix		*rotation_matrix_z(double angle);
t_matrix		*translation_matrix(t_vec3 *translation);
t_matrix		*scal_matrix(t_vec3 *scal);
t_matrix		**set_transform(t_vec3 *translation,
					t_vec3 *rotation, t_vec3 *scal);
t_vec3			apply_transform_vector(t_vec3 inputVector,
					int dirFlag, t_matrix **gtfm);
t_ray			apply_transform(t_ray *input_ray, t_matrix **gtfm, int dirFlag);
// fixed nor	mal
t_vec3			fixed_normal(t_matrix *forward, t_vec3 *hitpoint);
// test_int	
int				test_sphere(t_ray *ray, t_info *info);
int				test_plane(t_ray *ray, t_info *info);
//image	
t_image			*new_image(void);
unsigned int	rgb_to_int(float red, float green, float blue, float max);
float			max_overall(t_image *image);
void			render(t_image *image, void *mlx_ptr, void *win_ptr);
void			set_pixel(int x, int y, t_vec3 *color, t_image *image);
void			raytrace(t_vars *vars);
void			prepare_objects(t_vars *vars);
t_vec3			diffuse_color(t_info *info, t_vars *vars, t_vec3 *base_color);
int				calculate_props(int min_index, t_vec3 *poi,
					t_info *info, t_vec3 *vhat);
int				test_cylinder(t_ray *ray, t_info *info);
float			get_min(float *t, int *min_index);
// other utils
void			*ft_calloc(size_t nelem, size_t elsize);
void			free_objects(t_vars *vars);
void			free_image(t_image *image);
#endif
