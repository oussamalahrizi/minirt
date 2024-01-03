/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:21:05 by idelfag           #+#    #+#             */
/*   Updated: 2024/01/02 23:18:54 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

float	length2(t_vec3 a)
{
	return (pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

float	length(t_vec3 a)
{
	return (sqrtf(length2(a)));
}

t_vec3	scale_vector(t_vec3 a, float t)
{
	return ((t_vec3){a.x * t, a.y * t, a.z * t});
}

t_vec3	normalized(t_vec3 a)
{
	t_vec3	new;
	float	l;

	new = a;
	l = length(new);
	if (l != 0)
		new = scale_vector(new, 1.0f / l);
	return (new);
}

int	check_if_valid(char **lines, char c, int min, int max)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] && ft_isspace(lines[i][j]))
			j++;
		if (lines[i][j] == c)
			count++;
		i++;
	}
	if (max != -1 && count >= min && count <= max)
		return (1);
	else if (count >= min)
		return (1);
	return (0);
}
