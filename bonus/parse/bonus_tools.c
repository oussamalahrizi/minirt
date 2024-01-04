/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:25:50 by idelfag           #+#    #+#             */
/*   Updated: 2024/01/03 18:36:02 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_shininess(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	if (!line[*i])
		msg_exit_free("bad config file\n", 1, vars);
	vars->parse.obj[*index].shininess = parse_number(line[*i], &j, vars);
	if (line[*i][j] || !(vars->parse.obj[*index].shininess >= 0
		&& vars->parse.obj[*index].shininess <= 50))
		msg_exit_free("bad config file\n", 1, vars);
	vars->parse.obj[*index].has_material = 1;
}

void	parse_reflectivity(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	if (!line[*i])
		msg_exit_free("bad config file\n", 1, vars);
	vars->parse.obj[*index].reflectivity = parse_number(line[*i], &j, vars);
	if (line[*i][j] || !(vars->parse.obj[*index].reflectivity >= 0
		&& vars->parse.obj[*index].reflectivity <= 1))
		msg_exit_free("bad config file\n", 1, vars);
	vars->parse.obj[*index].has_material = 1;
}

void	parse_texture(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	if (!line[*i])
		msg_exit_free("bad config file\n", 1, vars);
	if (!ft_strcmp(line[*i], "CHECKERBOARD"))
	{
		(*i)++;
		if (!line[*i])
			msg_exit_free("bad config file\n", 1, vars);
		vars->parse.obj[*index].has_texture = 1;
		vars->parse.obj[*index].c_scale.u = parse_number(line[*i], &j, vars);
		skip_char(line[*i], ',', &j, vars);
		vars->parse.obj[*index].c_scale.v = parse_number(line[*i], &j, vars);
		if (line[*i][j])
			msg_exit_free("bad config file\n", 1, vars);
	}
	else if (!ft_strcmp(line[*i], "NO_TEXTURE"))
		vars->parse.obj[*index].has_texture = 0;
	else
	{
		vars->parse.obj[*index].has_texture = 2;
		vars->parse.obj[*index].texture_path = ft_strdup(line[*i]);
	}
}

void	parse_bump(char **line, t_vars *vars, int *index, int *i)
{
	(*i)++;
	if (!line[*i])
		msg_exit_free("bump path path is not found\n", 1, vars);
	vars->parse.obj[*index].has_bump = 1;
	vars->parse.obj[*index].bump_path = ft_strdup(line[*i]);
}

void	parse_bonus(char **line, t_vars *vars, int *index, int i)
{
	vars->parse.shin = 0;
	vars->parse.ref = 0;
	while (line[i])
	{
		if (line[i][0] == 'r')
		{
			parse_reflectivity(line, vars, index, &i);
			(vars->parse.ref)++;
		}
		else if (line[i][0] == 's')
		{
			parse_shininess(line, vars, index, &i);
			(vars->parse.shin)++;
		}
		else if (line[i][0] == 't')
			parse_texture(line, vars, index, &i);
		else if (line[i][0] == 'b')
			parse_bump(line, vars, index, &i);
		else
			msg_exit_free("bad config file\n", 1, vars);
		i++;
	}
	if (vars->parse.shin != 1 || vars->parse.ref != 1)
		if (!(vars->parse.shin == 0 && vars->parse.ref == 0))
			msg_exit_free("parsing object infos\n", 1, vars);
}
