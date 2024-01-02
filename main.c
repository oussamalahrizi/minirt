#include "header.h"




void free_objects(t_object *objects, t_vars *vars)
{
	int i;

	i = 0;
	while (i < OBJ_COUNT)
	{
		if (objects[i].type == SPHERE || objects[i].type == CYLINDER
        || objects[i].type == CONE)
		{
			delete_matrix(objects[i].gtfm[0]);
			delete_matrix(objects[i].gtfm[1]);
			free(objects[i].gtfm);
		}
    if (objects[i].has_texture == 2)
    {
      mlx_destroy_image(vars->mlx_ptr, objects[i].image.img);
      free(objects[i].texture_path);
    }
    if (objects[i].has_bump == 1)
    {
      free(objects[i].bump_path);
      mlx_destroy_image(vars->mlx_ptr, objects[i].imgnormal.img);
    }
    if (objects[i].has_texture == 1)
    {
      free(objects[i].checker_matrix);
    }
		i++;
	}
	free(objects);
}

void free_image(t_image *image)
{
	int i;

	i = 0;
	while (i < HEIGHT)
	{
		free(image->red[i]);
		free(image->green[i]);
		free(image->blue[i]);
		i++;
	}
	free(image->red);
	free(image->green);
	free(image->blue);
	free(image);
}

int handle_exit(t_vars *vars)
{
	free_objects(vars->objects, vars);
	free(vars->lights);
	free_image(vars->image);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->buffer);
	exit(0);
	return (0);
}

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEYCODE_ESC)
		handle_exit(vars);
	return (0);
}

int loop(t_vars *vars)
{
	if (vars->frames == 120)
		return (0);
 	raytrace(vars);
	render(vars->image, vars->mlx_ptr, vars->win_ptr);
	return (0);
}

int main(int ac, char **av)
{
	t_vars vars;

  parse(ac, av, &vars);
	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "Raytracing goes prr");
	init_camera(&vars.cam);
  prepare_objects(&vars);
	vars.image = new_image();
	vars.buffer = calloc(HEIGHT * WIDTH, sizeof(t_vec3));
	vars.frames = 0;
	vars.rng_state = 0;
	mlx_loop_hook(vars.mlx_ptr, loop, &vars);
	// raytrace(&vars);
	// render(vars.image, vars.mlx_ptr, vars.win_ptr);
	mlx_hook(vars.win_ptr, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win_ptr, 17, 0, handle_exit, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
