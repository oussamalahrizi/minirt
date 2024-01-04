/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 23:50:16 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/03 23:53:52 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	get_others(t_info *info, t_vec3 axis)
{
	t_vec3	xaxis;
	t_vec3	yaxis;

	xaxis = normalized(cross(get_up_vector(axis), axis));
	yaxis = normalized(cross(axis, xaxis));
	info->uv.u = -dot_product(info->hitpoint, xaxis);
	info->uv.v = dot_product(info->hitpoint, yaxis);
	info->tangent = scale_vector(xaxis, -1);
}

int	test_plane(t_ray *ray, t_info *info)
{
	t_vec3	axis;
	t_vec3	vhat;
	t_vec3	origin;
	float	denom;
	float	t;

	origin = info->e->translation;
	vhat = ray->dir;
	axis = normalized(info->e->d_normal);
	denom = dot_product(axis, vhat);
	if (fabs(denom) < EPSILON)
		return (0);
	t = (dot_product(origin, axis) - dot_product(ray->point1, axis)) / denom;
	if (t < EPSILON)
		return (0);
	info->localnormal = axis;
	if (dot_product(info->localnormal, vhat) > 0)
		info->localnormal = scale_vector(info->localnormal, -1);
	info->hitpoint = scale_vector(vhat, t);
	info->hitpoint = vec_add(ray->point1, info->hitpoint);
	get_others(info, axis);
	return (1);
}
