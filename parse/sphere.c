/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:16:07 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/29 14:12:52 by idelfag          ###   ########.fr       */
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

void	sphere_position(char **line, t_parse *parse, int *index, int *i)
{
	int	j;

	j = 0;
	parse->obj[*index].type = SPHERE;
	parse->obj[*index].translation.x = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "sphere");
	parse->obj[*index].translation.y = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "sphere");
	parse->obj[*index].translation.z = parse_number(line[*i], &j);
	if (line[*i][j])
		message_exit("Error while parcing sphere infos\n", 1);
	(*i)++;
}

void	sphere_color_radius(char **line, t_parse *parse, int *index, int *i)
{
	int	j;

	j = 0;
	parse->obj[*index].radius = (parse_number(line[*i], &j) / 2.0f);
	if (line[*i][j])
		message_exit("Error while parcing sphere infos\n", 1);
	(*i)++;
	j = 0;
	parse->obj[*index].base_color.x = (parse_number(line[*i], &j) / 255.f);
	skip_char(line[*i], ',', &j, "sphere");
	parse->obj[*index].base_color.y = (parse_number(line[*i], &j) / 255.f);
	skip_char(line[*i], ',', &j, "sphere");
	parse->obj[*index].base_color.z = (parse_number(line[*i], &j) / 255.f);
	if (line[*i][j])
		message_exit("Error while parcing sphere infos\n", 1);
}

void	parse_sphere(char **line, t_parse *parse, int *index)
{
	int	i;

	i = 1;
	if (ft_tablen(line) != 4)
		message_exit("Error while parcing sphere infos\n", 1);
	sphere_position(line, parse, index, &i);
	sphere_color_radius(line, parse, index, &i);
	if (!check_sphere(&(parse->obj[*index])))
		message_exit("Error while parcing sphere infos\n", 1);
	(*index)++;
}
