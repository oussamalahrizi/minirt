/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 03:36:31 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/11 11:31:26 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int cast_ray(t_ray *ray, t_object *objects, t_info *test, t_object *skip)
{
	int i;
	int validint;
	int intfound;
	float mindist;
	float dist;
	t_info other;

	i = 0;
	intfound = 0;
	mindist = 10e6;
	while (i < OBJ_COUNT)
	{
		if (skip == &objects[i])
		{
			i++;
			continue;
		}
		other.e = &objects[i];
		validint = objects[i].intersect(ray, &other);
		if (validint)
		{
			intfound = 1;
			dist = length(vec_sub(other.hitpoint, ray->point1));
			if (dist < mindist)
			{
				mindist = dist;
				test->e = other.e;
				test->hitpoint = other.hitpoint;
				test->localnormal = other.localnormal;
				test->tangent = other.tangent;
				test->uv = other.uv;
			}
		}
		i++;
	}
	return (intfound);
}

t_vec3 reflection_color(t_vars *vars, t_info *info, t_ray *incident_ray, int ref_count)
{
	t_vec3 ref_color;
	t_vec3 ref_v;
	int validint;
	t_ray ray;
	t_info test;
	
	ref_color = new_vector(0, 0, 0);
	ref_v = reflect(normalized(incident_ray->dir), normalized(info->localnormal));
	ray = new_ray(info->hitpoint, vec_add(info->hitpoint, ref_v));
	validint = cast_ray(&ray, vars->objects, &test, info->e);
	if (validint && ref_count < MAX_REF)
	{
		ref_count++;
		ref_color = compute_color(vars, &test, &ray, ref_count);
	}
	return (ref_color);
}