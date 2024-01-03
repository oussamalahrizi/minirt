/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:05:59 by idelfag           #+#    #+#             */
/*   Updated: 2024/01/03 00:22:27 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_line(t_vars *vars, int *index)
{
	if (!ft_strcmp(vars->line[0], "C"))
		parse_camera(vars->line, vars);
	else if (!ft_strcmp(vars->line[0], "A"))
		parse_ambient(vars->line, vars);
	else if (!ft_strcmp(vars->line[0], "sp"))
		parse_sphere(vars->line, vars, index);
	else if (!ft_strcmp(vars->line[0], "pl"))
		parse_plane(vars->line, vars, index);
	else if (!ft_strcmp(vars->line[0], "cy"))
		parse_cylender(vars->line, vars, index);
	else if (!ft_strcmp(vars->line[0], "co"))
		parse_cone(vars->line, vars, index);
	else if (!ft_strcmp(vars->line[0], "L"))
	{
		free_tab(vars->line);
		return ;
	}
	else
		msg_exit_free("bad configuration file\n", 1, vars);
	free_tab(vars->line);
}

void	set_default(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->obj_count)
	{
		vars->parse.obj[i].has_bump = 0;
		vars->parse.obj[i].has_material = 0;
		vars->parse.obj[i].has_texture = 0;
		vars->parse.obj[i].bump_path = NULL;
		vars->parse.obj[i].texture_path = NULL;
		i++;
	}
}

void	fill_lights(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (vars->lines[i])
	{
		vars->line = ft_split_two(vars->lines[i], "\t\n\v\f\r ");
		if (!ft_strcmp(vars->line[0], "L"))
		{
			parse_light(vars->line, vars, j);
			j++;
		}
		free_tab(vars->line);
		i++;
	}
}

void	pre_init(t_vars *vars)
{
	if (!check_if_valid(vars->lines, 'C', 1, 1)
		|| !check_if_valid(vars->lines, 'L', 1, -1)
		|| !check_if_valid(vars->lines, 'A', 0, 1))
	{
		free_tab(vars->lines);
		message_exit("bad config file\n", 1);
	}
    vars->l_count = count_lights(vars->lines);
	vars->lights = malloc(sizeof(t_light) * (vars->l_count));
	vars->obj_count = count_objs(vars->lines);
	vars->parse.obj = malloc(sizeof(t_object) * (vars->obj_count + 1));
	set_default(vars);
	fill_lights(vars);
}

void	get_content(t_vars *vars)
{
	int		i;
	int		index;
	int		flag;

	i = 0;
	flag = 0;
	index = 0;
	pre_init(vars);
	while (vars->lines[i])
	{
		vars->line = ft_split_two(vars->lines[i], "\t\n\v\f\r ");
		if (vars->line && vars->line[0])
			parse_line(vars, &index);
		i++;
	}
	free_tab(vars->lines);
}
