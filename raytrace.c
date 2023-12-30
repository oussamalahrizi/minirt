/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 11:50:49 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/30 21:54:08 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	test_helper(t_info *info, t_int *vars, t_ray *ray)
{
	if (vars->validint)
	{
		vars->intfound = 1;
		vars->dist = length(vec_sub(vars->test.hitpoint, ray->point1));
		if (vars->dist < vars->mindist)
		{
			vars->mindist = vars->dist;
			info->e = vars->test.e;
			info->hitpoint = vars->test.hitpoint;
			info->localnormal = vars->test.localnormal;
		}
	}
}

int	test_intersection(t_object *objects, t_ray *ray, t_info *info, int count)
{
	t_int	vars;

	vars.i = 0;
	vars.mindist = 1e6;
	vars.intfound = 0;
	vars.validint = 0;
	while (vars.i < count)
	{
		vars.test.e = &objects[vars.i];
		vars.validint = objects[vars.i].intersect(ray, &(vars.test));
		test_helper(info, &vars, ray);
		vars.i++;
	}
	return (vars.intfound);
}

void	raytrace_helper(t_rt *local, t_vars *vars)
{
	float	x_offset;
	float	y_offset;

	x_offset = random_float(&vars->rng_state, -0.5, 0.5);
	y_offset = random_float(&vars->rng_state, -0.5, 0.5);
	local->normx = ((float)(local->x + x_offset) * local->xfact) - 1.0;
	local->normy = ((float)(local->y + y_offset) * local->yfact) - 1.0;
	local->ray = generate_ray(local->normx, local->normy, &vars->cam);
	local->intfound = test_intersection(vars->objects,
			&local->ray, &local->info, vars->obj_count);
	if (local->intfound)
	{
		local->color = diffuse_color(&local->info, vars,
				&local->info.e->base_color);
		local->color = vec_add(local->color, vars->parse.ambient_light.rgb);
		vars->buffer[local->y * WIDTH + local->x] = vec_add(
				vars->buffer[local->y * WIDTH + local->x], local->color);
		local->color = scale_vector(vars->buffer[local->y * WIDTH + local->x],
				(float)1.0 / (float)vars->frames);
		set_pixel(local->x, local->y, &local->color, vars->image);
	}
}

void	raytrace(t_vars *vars)
{
	t_rt	local;

	vars->frames++;
	vars->rng_state = vars->frames;
	local.y = 0;
	local.xfact = 1.0 / ((float)(WIDTH) / 2.0);
	local.yfact = 1.0 / ((float)(HEIGHT) / 2.0);
	while (local.y < HEIGHT)
	{
		local.x = 0;
		while (local.x < WIDTH)
		{
			raytrace_helper(&local, vars);
			local.x++;
		}
		local.y++;
	}
	printf("frame : %d\n", vars->frames);
}
