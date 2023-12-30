/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:36:15 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/29 14:10:23 by idelfag          ###   ########.fr       */
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

void	camera_position(char **line, t_parse *parse, int *i)
{
	int	j;

	j = 0;
	parse->cam.origin.x = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "camera");
	parse->cam.origin.y = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "camera");
	parse->cam.origin.z = parse_number(line[*i], &j);
	if (line[*i][j])
		message_exit("Error while parcing camera infos\n", 1);
	(*i)++;
}

void	camera_lookat_fov(char **line, t_parse *parse, int *i)
{
	int		j;
	float	tmp;

	j = 0;
	parse->cam.lookat.x = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "camera");
	parse->cam.lookat.y = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "camera");
	parse->cam.lookat.z = parse_number(line[*i], &j);
	if (line[*i][j])
		message_exit("Error while parcing camera infos\n", 1);
	(*i)++;
	j = 0;
	parse->cam.fov = ft_atoi(line[*i]);
	tmp = parse_number(line[*i], &j);
	(void)tmp;
	if (line[*i][j])
		message_exit("Error while parcing camera infos\n", 1);
}

void	parse_camera(char **line, t_parse *parse)
{
	int	i;

	i = 1;
	if (ft_tablen(line) != 4)
		message_exit("Error while parcing camera infos\n", 1);
	camera_position(line, parse, &i);
	camera_lookat_fov(line, parse, &i);
	if (!check_cam_error(&(parse->cam)))
		message_exit("Error while parcing camera infos\n", 1);
}
