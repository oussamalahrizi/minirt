/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Simple_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 03:29:30 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 02:43:43 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_vec3	handle_diffuse(t_info *info, t_vars *vars)
{
	t_vec3	diff_color;

	if (info->e->has_texture == 1)
		diff_color = diffuse_color(vars, info,
				get_checker_color(info, info->e->checker_matrix));
	else if (info->e->has_texture == 2)
		diff_color = diffuse_color(vars, info,
				get_color_texture(info->e->image, info->uv.u, info->uv.v));
	else
		diff_color = diffuse_color(vars, info, info->e->base_color);
	return (diff_color);
}

t_vec3	compute_color(t_vars *vars, t_info *info,
	t_ray *camera_ray, int ref_count)
{
	t_vec3	mat_color;
	t_vec3	diff_color;
	t_vec3	spc_color;
	t_vec3	ref_color;
	t_vec3	helper;

	spc_color = new_vector(0, 0, 0);
	if (info->e->has_bump == 1)
		info->localnormal = bump_normal(info);
	diff_color = handle_diffuse(info, vars);
	mat_color = diff_color;
	if (info->e->has_material == 1)
	{
		if (info->e->reflectivity)
		{
			ref_color = reflection_color(vars, info, camera_ray, ref_count);
			ref_color = scale_vector(ref_color, info->e->reflectivity);
			helper = scale_vector(diff_color, 1.0 - info->e->reflectivity);
			mat_color = vec_add(ref_color, helper);
		}
		if (info->e->shininess)
			spc_color = specular_highlight(vars, info, camera_ray);
		mat_color = vec_add(mat_color, spc_color);
	}
	return (vec_add(mat_color, vars->parse.ambient_light.rgb));
}
