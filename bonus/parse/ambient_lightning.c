/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:54:49 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/31 01:32:01 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_ambient_error(t_ambient *ambient)
{
	if ((ambient->rgb.x < 0.0f) || (ambient->rgb.x > 1.0f))
		return (0);
	if ((ambient->rgb.y < 0.0f) || (ambient->rgb.y > 1.0f))
		return (0);
	if ((ambient->rgb.z < 0.0f) || (ambient->rgb.z > 1.0f))
		return (0);
	if (ambient->ambient_ratio < 0.0f || ambient->ambient_ratio > 1.0f)
		return (0);
	return (1);
}

void	parse_ambient(char **line, t_vars *vars)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ft_tablen(line) != 3)
		msg_exit_free("parsing ambient lightning infos\n", 1, vars);
	vars->parse.ambient_light.ambient_ratio = parse_number(line[i], &j, vars);
	if (line[i][j])
		msg_exit_free("parsing ambient light infos\n", 1, vars);
	i++;
	j = 0;
	vars->parse.ambient_light.rgb.x = (parse_number(line[i], &j, vars) / 255.f);
	skip_char(line[i], ',', &j, vars);
	vars->parse.ambient_light.rgb.y = (parse_number(line[i], &j, vars) / 255.f);
	skip_char(line[i], ',', &j, vars);
	vars->parse.ambient_light.rgb.z = (parse_number(line[i], &j, vars) / 255.f);
	if (line[i][j])
		msg_exit_free("parsing ambient light infos\n", 1, vars);
	if (!check_ambient_error(&(vars->parse.ambient_light)))
		msg_exit_free("parsing ambient lightning infos\n", 1, vars);
}
