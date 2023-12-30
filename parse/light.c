/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:46:03 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/29 14:11:21 by idelfag          ###   ########.fr       */
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

void	light_position(char **line, t_parse *parse, int *i)
{
	int	j;

	j = 0;
	parse->light.position.x = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "light");
	parse->light.position.y = parse_number(line[*i], &j);
	skip_char(line[*i], ',', &j, "light");
	parse->light.position.z = parse_number(line[*i], &j);
	if (line[*i][j])
		message_exit("Error while parcing light infos\n", 1);
	(*i)++;
}

void	light_intensity_color(char **line, t_parse *parse, int *i)
{
	int	j;

	j = 0;
	parse->light.intensity = parse_number(line[*i], &j);
	if (line[*i][j])
		message_exit("Error while parcing light infos\n", 1);
	(*i)++;
	j = 0;
	parse->light.color.x = (parse_number(line[*i], &j) / 255.f);
	skip_char(line[*i], ',', &j, "light");
	parse->light.color.y = (parse_number(line[*i], &j) / 255.f);
	skip_char(line[*i], ',', &j, "light");
	parse->light.color.z = (parse_number(line[*i], &j) / 255.f);
	if (line[*i][j])
		message_exit("Error while parcing light infos\n", 1);
}

void	parse_light(char **line, t_parse *parse)
{
	int	i;

	i = 1;
	if (ft_tablen(line) != 4)
		message_exit("Error while parcing light infos\n", 1);
	light_position(line, parse, &i);
	light_intensity_color(line, parse, &i);
	if (!light_error_check(&(parse->light)))
		message_exit("Error while parcing light infos\n", 1);
}
