/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 08:51:10 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/10 08:52:08 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static t_vec2 get_uvcoords(t_vec3 intpoint, int cap)
{
	float x = intpoint.x;
	float y = intpoint.y;
	float z = intpoint.z;
	float u;
	float v;
	if (cap)
	{
		u = x;
		v = y;
	}
	else
	{	
		u = atan2(y,x) / M_PI;
		v = (z * 2.0) + 1.0;
	}
	u = (u + 1) / 2.0;
	v = (v + 1) / 2.0;
	return ((t_vec2) {u, v});
}

int calculate_cone_props(int min_index, t_vec3 *poi, t_info *info, t_vec3 *vhat)
{
	if (min_index < 2)
	{
		info->hitpoint = apply_transform_vector(*poi, FORWARD, info->e->gtfm);
		poi->z = -sqrtf(square(poi->x) + square(poi->y));
		info->localnormal = fixed_normal(info->e->gtfm[0], poi);
		info->uv = get_uvcoords(*poi, 0);
		info->tangent = cross(get_up_vector(info->localnormal), info->localnormal);
		return (1);
	}
	else
	{
		if (fabs(vhat->z) < EPSILON)
			return (0);
		if (sqrtf( square(poi->y) + square(poi->x) ) < 1.0)
		{
			info->hitpoint= apply_transform_vector(*poi, FORWARD, info->e->gtfm);
			t_vec3 normal = new_vector(0, 0, 1);
			info->localnormal = fixed_normal(info->e->gtfm[0], &normal);
			info->uv = get_uvcoords(*poi, 1);
			info->tangent = cross(get_up_vector(info->localnormal), info->localnormal);
			return (1);
		}
		return (0);
	}
	return (0);
}
