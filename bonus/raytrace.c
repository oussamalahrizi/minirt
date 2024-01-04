/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 05:45:37 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 05:46:33 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	fill_info(t_int *local, t_info *info, t_ray *ray)
{
	local->intfound = 1;
	local->dist = length(vec_sub(local->test.hitpoint, ray->point1));
	if (local->dist < local->mindist)
	{
		local->mindist = local->dist;
		info->e = local->test.e;
		info->hitpoint = local->test.hitpoint;
		info->localnormal = local->test.localnormal;
		info->tangent = local->test.tangent;
		info->uv = local->test.uv;
	}
}

int	test_intersection(t_object *objects, t_ray *ray, t_info *info, int count)
{
	t_int	local;
	int		i;

	i = 0;
	local.mindist = 1e6;
	local.intfound = 0;
	local.validint = 0;
	while (i < count)
	{
		local.test.e = &objects[i];
		local.validint = objects[i].intersect(ray, &local.test);
		if (local.validint)
			fill_info(&local, info, ray);
		i++;
	}
	return (local.intfound);
}

static void	raytrace_helper(t_vars *vars, t_rt *local)
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
		local->color = compute_color(vars, &local->info, &local->ray, 0);
		vars->buffer[local->y * WIDTH + local->x] = vec_add(
				vars->buffer[local->y * WIDTH + local->x], local->color);
		local->color = scale_vector(
				vars->buffer[local->y * WIDTH + local->x], 1.0 / vars->frames);
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
			raytrace_helper(vars, &local);
			local.x++;
		}
		local.y++;
	}
	printf("frame : %d\n", vars->frames);
}
