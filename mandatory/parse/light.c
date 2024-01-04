/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:46:03 by idelfag           #+#    #+#             */
/*   Updated: 2024/01/01 14:32:51 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	light_error_check(t_light *light)
{
	if ((light->color.x < 0.0f) || (light->color.x > 1.0f))
		return (0);
	if ((light->color.y < 0.0f) || (light->color.y > 1.0f))
		return (0);
	if ((light->color.z < 0.0f) || (light->color.z > 1.0f))
		return (0);
	if (light->intensity < 0.0f || light->intensity > 1.0f)
		return (0);
	return (1);
}

void	light_position(char **line, t_vars *vars, int *i)
{
	int	j;

	j = 0;
	vars->parse.light.position.x = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.light.position.y = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.light.position.z = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("parsing light infos\n", 1, vars);
	(*i)++;
}

void	light_intensity_color(char **line, t_vars *vars, int *i)
{
	int	j;

	j = 0;
	vars->parse.light.intensity = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("parsing light infos\n", 1, vars);
	vars->parse.light.color.x = 1.0f;
	vars->parse.light.color.y = 1.0f;
	vars->parse.light.color.z = 1.0f;
}

void	parse_light(char **line, t_vars *vars)
{
	int	i;

	i = 1;
	if (ft_tablen(line) != 3)
		msg_exit_free("parsing light infos\n", 1, vars);
	light_position(line, vars, &i);
	light_intensity_color(line, vars, &i);
	if (!light_error_check(&(vars->parse.light)))
		msg_exit_free("parsing light infos\n", 1, vars);
}
