/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 21:39:40 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/30 21:48:33 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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

static void	loop(t_diff *diff, t_info *info, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 1)
	{
		diff->validillum = compute_illimunation(&vars->lights[i],
				info, vars, &diff->intensity);
		if (diff->validillum)
		{
			diff->illumfound = 1;
			diff->red += vars->lights[i].color.x * diff->intensity;
			diff->green += vars->lights[i].color.y * diff->intensity;
			diff->blue += vars->lights[i].color.z * diff->intensity;
		}
		i++;
	}
}

t_vec3	diffuse_color(t_info *info, t_vars *vars, t_vec3 *base_color)
{
	t_diff	diff;

	diff.illumfound = 0;
	diff.red = 0.0;
	diff.green = 0.0;
	diff.blue = 0.0;
	diff.diff_color = new_vector(diff.red, diff.green, diff.blue);
	diff.intensity = 0;
	loop(&diff, info, vars);
	if (diff.illumfound)
	{
		diff.diff_color = new_vector(diff.red * base_color->x,
				diff.green * base_color->y, diff.blue * base_color->z);
	}
	return (diff.diff_color);
}
