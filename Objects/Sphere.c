/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:22:15 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/25 12:23:17 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
	vhat = back_ray.dir;
	t = get_dist(back_ray.point1, vhat);
	if (t == FLT_MAX)
		return (0);
	localpoi = vec_add(back_ray.point1, scale_vector(vhat, t));
	info->hitpoint = apply_transform_vector(localpoi, FORWARD, gtfm);
	info->localnormal = fixed_normal(gtfm[0], &localpoi);
	return (1);
}
