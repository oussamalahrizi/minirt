/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 06:21:34 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 04:59:13 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norm_mat.h"

static int	cast_ray(t_object *objects, t_ray cast_ray, int count)
{
	t_info	test;
	int		i;
	int		validint;

	i = 0;
	while (i < count)
	{
		test.e = &objects[i];
		validint = objects[i].intersect(&cast_ray, &test);
		if (validint)
			return (1);
		i++;
	}
	return (0);
}

float	get_intensity(t_vec3 light_ray_dir, t_vec3 normal,
	t_vec3 cam_dir, t_object *e)
{
	t_vec3	v;
	t_vec3	ref_v;
	float	prod;

	v = normalized(cam_dir);
	ref_v = reflect(normalized(light_ray_dir), normal);
	prod = dot_product(ref_v, v);
	if (prod > 0.0)
		return (e->reflectivity * powf(prod, e->shininess));
	return (0);
}

static void	loop(t_spc *local, t_vars *vars, t_info *info, t_ray *camera_ray)
{
	int	i;

	i = 0;
	while (i < vars->l_count)
	{
		local->lighdir = normalized(
				vec_sub(vars->lights[i].position, info->hitpoint));
		local->start = vec_add(info->hitpoint,
				scale_vector(local->lighdir, 0.0001f));
		local->point2 = vec_add(local->start, local->lighdir);
		local->lightray = new_ray(local->start, local->point2);
		local->validint = cast_ray(vars->objects,
				local->lightray, vars->obj_count);
		if (!local->validint)
			local->intensity = get_intensity(local->lightray.dir,
					info->localnormal, camera_ray->dir, info->e);
		local->red += vars->lights[i].color.x * local->intensity
			* vars->lights[i].intensity;
		local->green += vars->lights[i].color.y * local->intensity
			* vars->lights[i].intensity;
		local->blue += vars->lights[i].color.z * local->intensity
			* vars->lights[i].intensity;
		i++;
	}
}

t_vec3	specular_highlight(t_vars *vars, t_info *info, t_ray *camera_ray)
{
	t_spc	local;

	local.red = .0f;
	local.green = .0f;
	local.blue = .0f;
	local.intensity = 0.0f;
	loop(&local, vars, info, camera_ray);
	local.spc_color = new_vector(local.red, local.green, local.blue);
	return (local.spc_color);
}
