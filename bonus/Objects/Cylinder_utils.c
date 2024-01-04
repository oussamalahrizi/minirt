/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:22:52 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 02:05:00 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static t_vec2	get_uvcoords(t_vec3 intpoint, int cap)
{
	float	x;
	float	y;
	float	z;
	float	u;
	float	v;

	x = intpoint.x;
	y = intpoint.y;
	z = intpoint.z;
	if (cap)
		return ((t_vec2){x / 5, y / 5});
	u = atan2(y, x) / M_PI;
	v = -z;
	u = (u + 1) / 2.0;
	v = (v + 1) / 2.0;
	return ((t_vec2){u, v});
}

static void	handle_caps(t_info *info, t_vec3 *poi)
{
	t_vec3	orgnormal;

	info->hitpoint = apply_transform_vector(poi,
			FORWARD, info->e->gtfm);
	orgnormal = new_vector(0, 0, poi->z);
	info->localnormal = fixed_normal(info->e->gtfm[0], &orgnormal);
	info->uv = get_uvcoords(*poi, 1);
	info->tangent = cross(get_up_vector(info->localnormal), info->localnormal);
}

int	calculate_props(int min_index, t_vec3 *poi, t_info *info, t_vec3 *vhat)
{
	t_vec3	orgnormal;

	if (min_index < 2)
	{
		info->hitpoint = apply_transform_vector(poi, FORWARD, info->e->gtfm);
		orgnormal = new_vector(poi->x, poi->y, 0);
		info->localnormal = fixed_normal(info->e->gtfm[0], &orgnormal);
		info->uv = get_uvcoords(*poi, 0);
		info->tangent = cross(get_up_vector(info->localnormal),
				info->localnormal);
		return (1);
	}
	else
	{
		if (fabs(vhat->z) < EPSILON)
			return (0);
		if (sqrtf(square(poi->x) + square(poi->y)) < 1.0)
		{
			handle_caps(info, poi);
			return (1);
		}
		return (0);
	}
	return (0);
}

float	get_min(float *t, int *min_index, int size)
{
	float	min;
	int		i;

	i = 0;
	if (size == 4 && t[0] == 100e6
		&& t[1] == 100e6 && t[2] == 100e6
		&& t[3] == 100e6)
		return (FLT_MAX);
	if (size == 3 && t[0] == 100e6
		&& t[1] == 100e6 && t[2] == 100e6)
		return (FLT_MAX);
	min = 10e6;
	while (i < size)
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
