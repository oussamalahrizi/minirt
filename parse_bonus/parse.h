/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:05:53 by idelfag           #+#    #+#             */
/*   Updated: 2024/01/03 00:00:34 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include <math.h>
# include <fcntl.h>

enum
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
};

enum
{
	CHECKERBOARD,
	TEXTURE,
	NO_TEXTURE
};

typedef struct s_vec2
{
	float	u;
	float	v;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct s_light
{
	t_vec3	position;
	t_vec3	color;
	float	intensity;
}			t_light;

typedef struct s_matrix
{
	int		rows;
	int		cols;
	float	**matrix;
}	t_matrix;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data;

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	lookat;
	t_vec3	up_vector;
	t_vec3	cam_w;
	t_vec3	cam_u;
	t_vec3	cam_v;
	t_vec3	screen_center;
	t_vec3	screen_u;
	t_vec3	screen_v;
	float	aspect_ratio;
	float	focal_length;
	float	hor_size;
	int		fov;
}				t_camera;

typedef struct s_info
{
	struct s_object	*e;
	t_vec3			hitpoint;
	t_vec3			localnormal;
	t_vec2			uv;
	t_vec3			tangent;
}				t_info;

typedef struct s_ray
{
	t_vec3	point1;
	t_vec3	point2;
	t_vec3	dir;
}	t_ray;

typedef struct s_object
{
	int			type;
	t_vec3		base_color;
	t_vec3		translation;
	t_vec3		rotation;
	t_vec3		scale;
	t_vec3		d_normal;
	t_matrix	**gtfm;
	float		radius;
	float		shininess;
	float		reflectivity;
	int			has_texture;
	int			has_material;
	t_matrix	*checker_matrix;
	t_vec2		c_scale;
	t_data		image;
	t_data		imgnormal;
	int			(*intersect)(t_ray*, struct s_info *);
	int			texture_type;
	char		*texture_path;
	char		*bump_path;
	int			has_bump;
}	t_object;

typedef struct s_ambient
{
	float	ambient_ratio;
	t_vec3	rgb;
}				t_ambient;

typedef struct s_parse
{
	t_camera	cam;
	t_light		light;
	t_ambient	ambient_light;
	t_object	*obj;
	int			shin;
	int			ref;
}				t_parse;

typedef struct s_image
{
	float	**red;
	float	**green;
	float	**blue;
}	t_image;

typedef struct s_vars
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_image			*image;
	t_light			*lights;
	t_object		*objects;
	t_camera		cam;
	t_vec3			*buffer;
	unsigned int	rng_state;
	int				frames;
	char			**lines;
	t_parse			parse;
	int				obj_count;
	char			**line;
    int             l_count;
}	t_vars;

void	free_tab(char **tab);
int		ft_tablen(char **tab);
int		ft_isspace(int c);
void	message_exit(char *msg, int n);
char	**ft_split_two(char *str, char *charset);
float	parse_number(char *str, int *index, t_vars *vars);
void	skip_char(char *line, char c, int *index, t_vars *vars);
void	get_content(t_vars *vars);
void	parse_camera(char **line, t_vars *vars);
void	parse_ambient(char **line, t_vars *vars);
void	parse_light(char **line, t_vars *vars, int index);
void	parse_sphere(char **line, t_vars *vars, int *index);
void	parse_plane(char **line, t_vars *vars, int *index);
void	parse_cylender(char **line, t_vars *vars, int *index);
void	parse_cone(char **line, t_vars *vars, int *index);
t_vec3	normalized(t_vec3 a);
int		ft_strcmp(char *s1, char *s2);
void	parse(int ac, char **av, t_vars *vars);
void	msg_exit_free(char *msg, int n, t_vars *vars);
void	parse_reflectivity(char **line, t_vars *vars, int *index, int *i);
void	parse_shininess(char **line, t_vars *vars, int *index, int *i);
void	parse_texture(char **line, t_vars *vars, int *index, int *i);
void	parse_bump(char **line, t_vars *vars, int *index, int *i);
void	parse_bonus(char **line, t_vars *vars, int *index, int i);
void	parse(int ac, char **av, t_vars *vars);
int		check_if_valid(char **lines, char c, int min, int max);
int		count_lights(char **line);
int		count_objs(char **line);

#endif
