/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:09:37 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/31 01:45:52 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_plane(t_object *obj)
{
	if ((obj->d_normal.x < -1.0f) || (obj->d_normal.x > 1.0f))
		return (0);
	if ((obj->d_normal.y < -1.0f) || (obj->d_normal.y > 1.0f))
		return (0);
	if (obj->d_normal.z < -1 || obj->d_normal.z > 1)
		return (0);
	if ((obj->base_color.x < 0.0f) || (obj->base_color.x > 1.0f))
		return (0);
	if ((obj->base_color.y < 0.0f) || (obj->base_color.y > 1.0f))
		return (0);
	if ((obj->base_color.z < 0.0f) || (obj->base_color.z > 1.0f))
		return (0);
	return (1);
}

void	plane_position(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	vars->parse.obj[*index].type = PLANE;
	vars->parse.obj[*index].translation.x = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].translation.y = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].translation.z = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("Error\nparsing plane infos\n", 1, vars);
	(*i)++;
}

void	plane_dnormal(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	vars->parse.obj[*index].d_normal.x = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].d_normal.y = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].d_normal.z = parse_number(line[*i], &j, vars);
	vars->parse.obj->d_normal = vars->parse.obj->d_normal;
	if (line[*i][j])
		msg_exit_free("Error\nparsing plane infos\n", 1, vars);
	(*i)++;
}

void	plane_basecolor(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

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
		msg_exit_free("Error\nparsing plane infos\n", 1, vars);
}

void	parse_plane(char **line, t_vars *vars, int *index)
{
	int	i;

	i = 1;
	if (ft_tablen(line) != 4)
		msg_exit_free("Error\nparsing plane infos\n", 1, vars);
	plane_position(line, vars, index, &i);
	plane_dnormal(line, vars, index, &i);
	plane_basecolor(line, vars, index, &i);
	if (!check_plane(&(vars->parse.obj[*index])))
		msg_exit_free("Error\nparsing plane infos\n", 1, vars);
	(*index)++;
}
