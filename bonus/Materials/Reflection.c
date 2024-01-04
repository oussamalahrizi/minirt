/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 03:36:31 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 05:58:27 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norm_mat.h"

static void	fill_info(t_cast *local, t_info *test, t_ray *ray)
{
	local->intfound = 1;
	local->dist = length(vec_sub(local->other.hitpoint, ray->point1));
	if (local->dist < local->mindist)
	{
		local->mindist = local->dist;
		test->e = local->other.e;
		test->hitpoint = local->other.hitpoint;
		test->localnormal = local->other.localnormal;
		test->tangent = local->other.tangent;
		test->uv = local->other.uv;
	}
}

static int	cast_ray(t_ray *ray, t_vars *vars, t_info *test, t_object *skip)
{
	int		i;
	t_cast	local;

	i = 0;
	local.intfound = 0;
	local.mindist = 10e6;
	local.validint = 0;
	while (i < vars->obj_count)
	{
		if (skip != &vars->objects[i])
		{
			local.other.e = &vars->objects[i];
			local.validint = vars->objects[i].intersect(ray, &local.other);
			if (local.validint)
				fill_info(&local, test, ray);
		}
		i++;
	}
	return (local.intfound);
}

t_vec3	reflection_color(t_vars *vars, t_info *info,
	t_ray *incident_ray, int ref_count)
{
	t_vec3	ref_color;
	t_vec3	ref_v;
	int		validint;
	t_ray	ray;
	t_info	test;

	ref_color = new_vector(0, 0, 0);
	ref_v = reflect(normalized(incident_ray->dir),
			normalized(info->localnormal));
	ray = new_ray(info->hitpoint, vec_add(info->hitpoint, ref_v));
	validint = cast_ray(&ray, vars, &test, info->e);
	if (validint && ref_count < MAX_REF)
	{
		ref_count++;
		ref_color = compute_color(vars, &test, &ray, ref_count);
	}
	return (ref_color);
}
