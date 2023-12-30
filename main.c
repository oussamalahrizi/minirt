/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:06:24 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/30 22:05:41 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	handle_exit(t_vars *vars)
{
	free_objects(vars);
	free_image(vars->image);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->buffer);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEYCODE_ESC)
		handle_exit(vars);
	return (0);
}

int	loop(t_vars *vars)
{
	if (vars->frames == 120)
		return (0);
	raytrace(vars);
	render(vars->image, vars->mlx_ptr, vars->win_ptr);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	parse(ac, av, &vars);
	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr,
			WIDTH, HEIGHT, "miniRT");
	vars.parse.ambient_light.rgb = scale_vector(vars.parse.ambient_light.rgb,
			vars.parse.ambient_light.ambient_ratio);
	prepare_objects(&vars);
	init_camera(&vars.cam);
	vars.image = new_image();
	vars.buffer = ft_calloc(HEIGHT * WIDTH, sizeof(t_vec3));
	vars.frames = 0;
	vars.rng_state = 0;
	mlx_loop_hook(vars.mlx_ptr, loop, &vars);
	mlx_hook(vars.win_ptr, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win_ptr, 17, 0, handle_exit, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
