/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:54:49 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/30 17:51:28 by olahrizi         ###   ########.fr       */
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

void	parse_ambient(char **line, t_parse *parse)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ft_tablen(line) != 3)
		message_exit("Error while parcing ambient lightning infos\n", 1);
	parse->ambient_light.ambient_ratio = parse_number(line[i], &j);
	if (line[i][j])
		message_exit("Error while parcing ambient light infos\n", 1);
	i++;
	j = 0;
	parse->ambient_light.rgb.x = (parse_number(line[i], &j) / 255.f);
	skip_char(line[i], ',', &j, "ambient");
	parse->ambient_light.rgb.y = (parse_number(line[i], &j) / 255.f);
	skip_char(line[i], ',', &j, "ambient");
	parse->ambient_light.rgb.z = (parse_number(line[i], &j) / 255.f);
	if (line[i][j])
		message_exit("Error while parcing ambient light infos\n", 1);
	if (!check_ambient_error(&(parse->ambient_light)))
		message_exit("Error while parcing ambient lightning infos\n", 1);
}
