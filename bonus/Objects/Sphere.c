/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 23:47:08 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 01:28:57 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static t_vec2	get_uvcoords(t_vec3 intpoint)
{
	float	x;
	float	y;
	float	z;
	float	u;
	float	v;

	x = intpoint.x;
	y = intpoint.y;
	z = intpoint.z;
	u = atan2(y, x) / M_PI;
	v = 2.0 * (atan2(sqrtf(powf(x, 2) + powf(y, 2)), z) / M_PI) - 1.0;
	u = (u + 1) / 2.0;
	v = (v + 1) / 2.0;
	return ((t_vec2){u, v});
}

float	get_dist(t_vec3 ray_org, t_vec3 vhat)
{
	float	b;
	float	c;
	float	delta;
	float	t1;
	float	t2;

	b = 2.0 * dot_product(ray_org, vhat);
	c = dot_product(ray_org, ray_org) - 1.0f;
	delta = square(b) - (4.0 * c);
	if (delta > 0)
	{
		delta = sqrtf(delta);
		t1 = (-b - delta) / 2.0;
		t2 = (-b + delta) / 2.0;
		if (t1 < 0.0 || t2 < 0.0)
			return (FLT_MAX);
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	return (FLT_MAX);
}

int	test_sphere(t_ray *ray, t_info *info)
{
	t_matrix	**gtfm;
	t_ray		back_ray;
	t_vec3		vhat;
	t_vec3		localpoi;
	float		t;

	gtfm = info->e->gtfm;
	back_ray = apply_transform(ray, gtfm, BACKWARD);
	vhat = normalized(back_ray.dir);
	t = get_dist(back_ray.point1, vhat);
	if (t == FLT_MAX)
		return (0);
	localpoi = vec_add(back_ray.point1, scale_vector(vhat, t));
	info->hitpoint = apply_transform_vector(&localpoi, FORWARD, gtfm);
	info->localnormal = fixed_normal(gtfm[0], &localpoi);
	info->uv = get_uvcoords(localpoi);
	info->tangent = cross(get_up_vector(info->localnormal), info->localnormal);
	return (1);
}
