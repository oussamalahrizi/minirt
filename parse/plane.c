/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:09:37 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/30 18:59:55 by olahrizi         ###   ########.fr       */
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

void	plane_position(char **line, t_parse *parse, int *index, int *i)
{
	int	j;

	j = 0;
	parse->obj[*index].type = PLANE;
	parse->obj[*index].translation.x = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "plane");
	parse->obj[*index].translation.y = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "plane");
	parse->obj[*index].translation.z = parse_number(line[*i], &j);
	if (line[*i][j])
		message_exit("Error while parcing plane infos\n", 1);
	(*i)++;
}

void	plane_dnormal(char **line, t_parse *parse, int *index, int *i)
{
	int	j;

	j = 0;
	parse->obj[*index].d_normal.x = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "plane");
	parse->obj[*index].d_normal.y = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "plane");
	parse->obj[*index].d_normal.z = parse_number(line[*i], &j);
	parse->obj->d_normal = parse->obj->d_normal;
	if (line[*i][j])
		message_exit("Error while parcing plane infos\n", 1);
	(*i)++;
}

void	plane_basecolor(char **line, t_parse *parse, int *index, int *i)
{
	int	j;

	j = 0;
	parse->obj[*index].base_color.x = (parse_number(line[*i], &j) / 255.f);
	skip_char(line[*i], ',', &j, "plane");
	parse->obj[*index].base_color.y = (parse_number(line[*i], &j) / 255.f);
	skip_char(line[*i], ',', &j, "plane");
	parse->obj[*index].base_color.z = (parse_number(line[*i], &j) / 255.f);
	if (line[*i][j])
		message_exit("Error while parcing plane infos\n", 1);
}

void	parse_plane(char **line, t_parse *parse, int *index)
{
	int	i;

	i = 1;
	if (ft_tablen(line) != 4)
		message_exit("Error while parcing plane infos\n", 1);
	plane_position(line, parse, index, &i);
	plane_dnormal(line, parse, index, &i);
	plane_basecolor(line, parse, index, &i);
	if (!check_plane(&(parse->obj[*index])))
		message_exit("Error while parcing plane infos\n", 1);
	(*index)++;
}
