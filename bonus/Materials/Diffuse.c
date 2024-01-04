/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:34:44 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/03 22:42:46 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norm_mat.h"

static int	cast_ray(t_ray *lightray, t_vars *vars,
	float lighdist, t_info *info)
{
	int		i;
	int		validint;
	float	dist;
	t_info	test;

	i = 0;
	validint = 0;
	while (i < vars->obj_count)
	{
		if (info->e != &vars->objects[i])
		{
			test.e = &vars->objects[i];
			validint = vars->objects[i].intersect(lightray, &test);
			if (validint)
			{
				dist = length(vec_sub(test.hitpoint, info->hitpoint));
				if (dist > lighdist)
					validint = 0;
			}
			if (validint)
				break ;
		}
		i++;
	}
	return (validint);
}

int	compute_illimunation(t_light *light, t_info *info,
	t_vars *vars, float *intensity)
{
	t_vec3	lighdir;
	t_ray	lightray;
	float	lighdist;
	int		validint;

	lighdir = normalized(vec_sub(light->position, info->hitpoint));
	lighdist = length(vec_sub(light->position, info->hitpoint));
	lightray = new_ray(info->hitpoint, vec_add(info->hitpoint, lighdir));
	validint = cast_ray(&lightray, vars, lighdist, info);
	if (!validint)
	{
		*intensity = light->intensity * fmax(dot_product(lighdir,
					info->localnormal), 0.0);
		return (1);
	}
	else
	{
		*intensity = 0.0f;
		return (0);
	}
	return (0);
}

static void	loop(t_diff *local, t_vars *vars, t_info *info)
{
	int	i;

	i = 0;
	while (i < vars->l_count)
	{
		local->validillum = compute_illimunation(&vars->lights[i],
				info, vars, &local->intensity);
		if (local->validillum)
		{
			local->illumfound = 1;
			local->red += vars->lights[i].color.x * local->intensity;
			local->green += vars->lights[i].color.y * local->intensity;
			local->blue += vars->lights[i].color.z * local->intensity;
		}
		i++;
	}
}

t_vec3	diffuse_color(t_vars *vars, t_info *info, t_vec3 base_color)
{
	t_diff	local;

	local.illumfound = 0;
	local.red = 0.0;
	local.green = 0.0;
	local.blue = 0.0;
	local.diff_color = new_vector(local.red, local.green, local.blue);
	local.intensity = 0;
	loop(&local, vars, info);
	if (local.illumfound)
		local.diff_color = new_vector(local.red * base_color.x,
				local.green * base_color.y, local.blue * base_color.z);
	return (local.diff_color);
}
