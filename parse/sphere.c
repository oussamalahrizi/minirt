/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:16:07 by idelfag           #+#    #+#             */
/*   Updated: 2024/01/01 23:11:59 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_sphere(t_object *obj)
{
	if ((obj->base_color.x < 0.0f) || (obj->base_color.x > 1.0f))
		return (0);
	if ((obj->base_color.y < 0.0f) || (obj->base_color.y > 1.0f))
		return (0);
	if ((obj->base_color.z < 0.0f) || (obj->base_color.z > 1.0f))
		return (0);
	return (1);
}

void	sphere_position(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	vars->parse.obj[*index].type = SPHERE;
	vars->parse.obj[*index].translation.x = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].translation.y = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].translation.z = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("parcing sphere infos\n", 1, vars);
	(*i)++;
}

void	sphere_color_radius(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	vars->parse.obj[*index].radius = (parse_number(line[*i], &j, vars) / 2.0f);
	if (line[*i][j])
		msg_exit_free("parcing sphere infos\n", 1, vars);
	(*i)++;
	j = 0;
	vars->parse.obj[*index].base_color.x = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].base_color.y = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].base_color.z = parse_number(line[*i], &j, vars);
	vars->parse.obj[*index].base_color.x /= 255.f;
	vars->parse.obj[*index].base_color.y /= 255.f;
	vars->parse.obj[*index].base_color.z /= 255.f;
	if (line[*i][j])
		msg_exit_free("parcing sphere infos\n", 1, vars);
	(*i)++;
}

void	reflectivity(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	vars->parse.obj[*index].reflectivity = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("bad config file\n", 1, vars);
	(*i)++;
	j = 0;
	if (line[*i][j] == 's')
	{
		(*i)++;
		vars->parse.obj[*index].shininess = parse_number(line[*i], &j, vars);
		if (line[*i][j])
			msg_exit_free("bad config file\n", 1, vars);
	}
	else
		msg_exit_free("bad config file\n", 1, vars);
	vars->parse.obj[*index].has_material = 1;
  // printf("%d %d\n", vars->parse.obj[*index].has_material, *index);
}

void	shininess(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	vars->parse.obj[*index].shininess = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("bad config file\n", 1, vars);
	(*i)++;
	j = 0;
	if (line[*i][j] == 'r')
	{
		(*i)++;
		vars->parse.obj[*index].reflectivity = parse_number(line[*i], &j, vars);
		if (line[*i][j])
			msg_exit_free("bad config file\n", 1, vars);
	}
	else
		msg_exit_free("bad config file\n", 1, vars);
	vars->parse.obj[*index].has_material = 1;
}

void	parse_reflectivity(char **line, t_vars *vars, int *index, int *i)
{
	if (line[*i][0] == 'r')
		reflectivity(line, vars, index, i);
	else if (line[*i][0] == 's')
		shininess(line, vars, index, i);	
	else
		vars->parse.obj[*index].has_material = 0;
}

void	parse_texture(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
  (*i)++;
	if (!ft_strcmp(line[*i], "CHECKERBOARD"))
	{
		(*i)++;
		vars->parse.obj[*index].has_texture = 1;
		vars->parse.obj[*index].c_scale.u = parse_number(line[*i], &j, vars);
		skip_char(line[*i], ',', &j, vars);
		vars->parse.obj[*index].c_scale.v = parse_number(line[*i], &j, vars);
		if (line[*i][j])
			msg_exit_free("bad config file\n", 1, vars);
	}
	else if (!ft_strcmp(line[*i], "NO_TEXTURE"))
	{
		(*i)++;
		vars->parse.obj[*index].has_texture = 0;
	}
	else
	{
		vars->parse.obj[*index].has_texture = 2;
		vars->parse.obj[*index].texture_path = ft_strdup(line[*i]);
	}
}

void	parse_bump(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	
	(*i)++;
	if (!line[*i][j])
		msg_exit_free("bump path path is not found\n", 1, vars);
	vars->parse.obj[*index].has_bump = 1;
	vars->parse.obj[*index].bump_path = ft_strdup(line[*i]);
}

void	parse_sphere(char **line, t_vars *vars, int *index)
{
	int	i;

	i = 1;
	if (!(ft_tablen(line) >= 4 && ft_tablen(line) <= 13))
		msg_exit_free("parcing sphere infos\n", 1, vars);
	sphere_position(line, vars, index, &i);
	sphere_color_radius(line, vars, index, &i);
	while(line[i])
	{
		if (line[i][0] == 'r' || line[i][0] == 's')
			parse_reflectivity(line, vars, index, &i);
		else if (line[i][0] == 't')
			parse_texture(line, vars, index, &i);
		else if (line[i][0] == 'b')
			parse_bump(line, vars, index, &i);
	  else
    {
      printf("%c\n", line[i][0]);
			msg_exit_free("Unknown key\n", 1, vars);
    }
		i++;
	}
	if (!check_sphere(&(vars->parse.obj[*index])))
		msg_exit_free("parcing sphere infos\n", 1, vars);
	(*index)++;
}
