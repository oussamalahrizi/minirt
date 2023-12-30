/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:22:52 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/25 12:31:37 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	calculate_props(int min_index, t_vec3 *poi, t_info *info, t_vec3 *vhat)
{
	t_vec3	orgnormal;

	if (min_index < 2)
	{
		info->hitpoint = apply_transform_vector(*poi, FORWARD, info->e->gtfm);
		orgnormal = new_vector(poi->x, poi->y, 0);
		info->localnormal = fixed_normal(info->e->gtfm[0], &orgnormal);
		return (1);
	}
	else
	{
		if (fabs(vhat->z) < EPSILON)
			return (0);
		if (sqrtf(square(poi->x) + square(poi->y)) < 1.0)
		{
			info->hitpoint = apply_transform_vector(*poi,
					FORWARD, info->e->gtfm);
			orgnormal = new_vector(0, 0, poi->z);
			info->localnormal = fixed_normal(info->e->gtfm[0], &orgnormal);
			return (1);
		}
		return (0);
	}
	return (0);
}

float	get_min(float *t, int *min_index)
{
	float	min;
	int		i;

	i = 0;
	if (t[0] == 100e6 && t[1] == 100e6
		&& t[2] == 100e6 && t[3] == 100e6)
		return (-1);
	min = 10e6;
	while (i < 4)
	{
		if (t[i] < min)
		{
			min = t[i];
			*min_index = i;
		}
		i++;
	}
	return (min);
}
