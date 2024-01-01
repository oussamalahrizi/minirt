/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 06:22:50 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/10 08:39:58 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


static int get_t2(t_vec3 *ray_org, t_vec3 *vhat, float *t, t_vec3 *poi)
{
	float a;
	float b;
	float c;
	float delta;

	a = square(vhat->x) + square(vhat->y) - square(vhat->z);
	b = 2 * (ray_org->x * vhat->x + ray_org->y * vhat->y - ray_org->z * vhat->z);
	c =  square(ray_org->x) + square(ray_org->y) - square(ray_org->z);
	delta = sqrtf(square(b) - (4 * a * c));
	if (delta > 0)
	{
		t[0] = (-b + delta) / (2 * a);
		t[1] = (-b - delta) / (2 * a);
		poi[0] = vec_add(*ray_org, scale_vector(*vhat, t[0]));
		poi[1] = vec_add(*ray_org, scale_vector(*vhat, t[1]));
		return (1);
	}
	return (0);
}

static float get_distance(t_ray *back_ray, t_vec3 *vhat, float *t, t_vec3 *poi)
{
	int t2;

	t2 = get_t2(&back_ray->point1, vhat, t, poi);
	if (!t2)
		return (FLT_MAX);
	if (!(t[0] > 0 && poi[0].z > 0.0 && poi[0].z < 1.0 ))
		t[0] = 100e6;
	if (!(t[1] > 0 && poi[1].z > 0.0 && poi[1].z < 1.0))
		t[1] = 100e6;
	return (t2);
}

static void get_distance2(t_ray *back_ray, t_vec3 *vhat, float *t, t_vec3 *poi)
{
	float t2;

	t2 = get_distance(back_ray, vhat, t, poi);
	if (t2 == FLT_MAX)
	{
		t[0] = 100e6;
		t[1] = 100e6;
	}
	if (fabs(vhat->z) < EPSILON)
		t[2] = 100e6;
	else
	{
		t[2] = (back_ray->point1.z - 1) / -vhat->z;
		poi[2] = vec_add(back_ray->point1, scale_vector(*vhat, t[2]));
		if (!(t[2] > 0 && sqrtf( square(poi[2].x) + square(poi[2].y) ) < 1.0))
			t[2] = 100e6;
	}
}

static int get_min(float *t, int *min_index)
{
	int i;
	float min;

	i = 0;
	min = 10e6;
	while (i < 3)
	{
		if (t[i] < min)
		{
			min = t[i];
			*min_index = i;
		}
		i++;
	}
	if (min == 10e6)
		return (-1);
	return (min);
}


int test_cone(t_ray *ray, t_info *info)
{
	float t[3];
	t_vec3 poi[3];
	t_ray back_ray;
	t_vec3 vhat;
	t_vec3 validpoi;
	int min_index;

	back_ray = apply_transform(ray, info->e->gtfm, BACKWARD);
	vhat = normalized(back_ray.dir);
	get_distance2(&back_ray, &vhat, t, poi);
	min_index = 0;
	if (get_min(t, &min_index) == -1)
		return (0);
	validpoi = poi[min_index];
	return (calculate_cone_props(min_index, &validpoi, info, &vhat));
}