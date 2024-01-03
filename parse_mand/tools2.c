/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:21:05 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/29 14:21:37 by idelfag          ###   ########.fr       */
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
