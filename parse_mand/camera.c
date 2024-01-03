/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:36:15 by idelfag           #+#    #+#             */
/*   Updated: 2024/01/01 15:13:30 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_cam_error(t_camera *cam)
{
	if (cam->fov < 0 || cam->fov >= 180)
		return (0);
	if (cam->lookat.x < -1.0f || cam->lookat.x > 1.0f)
		return (0);
	if (cam->lookat.y < -1.0f || cam->lookat.y > 1.0f)
		return (0);
	if (cam->lookat.z < -1.0f || cam->lookat.z > 1.0f)
		return (0);
	return (1);
}

void	camera_position(char **line, t_vars *vars, int *i)
{
	int	j;

	j = 0;
	vars->parse.cam.origin.x = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.cam.origin.y = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.cam.origin.z = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("parsing camera infos\n", 1, vars);
	(*i)++;
}

void	camera_lookat_fov(char **line, t_vars *vars, int *i)
{
	int		j;
	float	tmp;

	j = 0;
	vars->parse.cam.lookat.x = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.cam.lookat.y = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.cam.lookat.z = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("parsing camera infos\n", 1, vars);
	(*i)++;
	j = 0;
	vars->parse.cam.fov = ft_atoi(line[*i]);
	tmp = parse_number(line[*i], &j, vars);
	(void)tmp;
	if (line[*i][j])
		msg_exit_free("parsing camera infos\n", 1, vars);
}

void	parse_camera(char **line, t_vars *vars)
{
	int	i;

	i = 1;
	if (ft_tablen(line) != 4)
		msg_exit_free("parsing camera infos\n", 1, vars);
	camera_position(line, vars, &i);
	camera_lookat_fov(line, vars, &i);
	if (!check_cam_error(&(vars->parse.cam)))
		msg_exit_free("parsing camera infos\n", 1, vars);
}
