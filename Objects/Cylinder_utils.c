/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:22:52 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/07 21:53:51 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int calculate_props(int min_index, t_vec3 *poi, t_info *info, t_vec3 *vhat)
{
	t_vec3 orgnormal;

	if (min_index < 2)
	{
		info->hitpoint = apply_transform_vector(poi, FORWARD, info->e->gtfm);
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
			info->hitpoint = apply_transform_vector(poi, FORWARD, info->e->gtfm);
			orgnormal = new_vector(0, 0, poi->z);
			info->localnormal = fixed_normal(info->e->gtfm[0], &orgnormal);
			return (1);
		}
		return (0);
	}
	return (0);
}