/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:15:30 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/30 19:00:22 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_cylender(t_object *obj)
{
	if ((obj->d_normal.x < -1.0f) || (obj->d_normal.x > 1.0f))
		return (0);
	if ((obj->d_normal.y < -1.0f) || (obj->d_normal.y > 1.0f))
		return (0);
	if ((obj->d_normal.z < -1.0f) || (obj->d_normal.z > 1.0f))
		return (0);
	if ((obj->base_color.x < 0.0f) || (obj->base_color.x > 1.0f))
		return (0);
	if ((obj->base_color.y < 0.0f) || (obj->base_color.y > 1.0f))
		return (0);
	if ((obj->base_color.z < 0.0f) || (obj->base_color.z > 1.0f))
		return (0);
	return (1);
}

void	cylender_position(char **line, t_parse *parse, int *index, int *i)
{
	int	j;

	j = 0;
	parse->obj[*index].type = CYLINDER;
	parse->obj[*index].translation.x = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "cylender");
	parse->obj[*index].translation.y = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "cylender");
	parse->obj[*index].translation.z = parse_number(line[*i], &j);
	if (line[*i][j])
		message_exit("Error while parcing cylender infos\n", 1);
	(*i)++;
}

void	cylender_dnormal(char **line, t_parse *parse, int *index, int *i)
{
	int	j;

	j = 0;
	parse->obj[*index].d_normal.x = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "cylender");
	parse->obj[*index].d_normal.y = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "cylender");
	parse->obj[*index].d_normal.z = parse_number(line[*i], &j);
	if (line[*i][j])
		message_exit("Error while parcing cylender infos\n", 1);
	(*i)++;
}

void	cylender_scale_color(char **line, t_parse *parse, int *index, int *i)
{
	int	j;

	j = 0;
	parse->obj[*index].scale.x = (parse_number(line[*i], &j) / 2.f);
	j = 0;
	parse->obj[*index].scale.y = (parse_number(line[*i], &j) / 2.f);
	(*i)++;
	j = 0;
	parse->obj[*index].scale.z = parse_number(line[*i], &j);
	if (line[*i][j])
		message_exit("Error while parcing cylender infos\n", 1);
	(*i)++;
	j = 0;
	parse->obj[*index].base_color.x = (parse_number(line[*i], &j) / 255.f);
	skip_char(line[*i], ',', &j, "cylender");
	parse->obj[*index].base_color.y = (parse_number(line[*i], &j) / 255.f);
	skip_char(line[*i], ',', &j, "cylender");
	parse->obj[*index].base_color.z = (parse_number(line[*i], &j) / 255.f);
	if (line[*i][j])
		message_exit("Error while parcing cylender infos\n", 1);
}

void	parse_cylender(char **line, t_parse *parse, int *index)
{
	int	i;

	i = 1;
	if (ft_tablen(line) != 6)
		message_exit("Error while parcing cylender infos\n", 1);
	cylender_position(line, parse, index, &i);
	cylender_dnormal(line, parse, index, &i);
	cylender_scale_color(line, parse, index, &i);
	if (!check_cylender(&(parse->obj[*index])))
		message_exit("Error while parcing cylender infos\n", 1);
	(*index)++;
}
