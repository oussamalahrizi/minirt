/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:16:07 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/31 01:44:50 by idelfag          ###   ########.fr       */
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
}

void	parse_sphere(char **line, t_vars *vars, int *index)
{
	int	i;

	i = 1;
	if (ft_tablen(line) != 4)
		msg_exit_free("parcing sphere infos\n", 1, vars);
	sphere_position(line, vars, index, &i);
	sphere_color_radius(line, vars, index, &i);
	if (!check_sphere(&(vars->parse.obj[*index])))
		msg_exit_free("parcing sphere infos\n", 1, vars);
	(*index)++;
}
