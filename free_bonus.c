#include "header.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*result;
	size_t	i;

	if (nelem && elsize > SIZE_MAX / nelem)
		return (0);
	result = malloc(nelem * elsize);
	if (!result)
		return (0);
	i = 0;
	while (i < nelem * elsize)
		((unsigned char *)result)[i++] = 0;
	return (result);
}

void	free_objects(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->obj_count)
	{
		if (vars->objects[i].type == SPHERE
			|| vars->objects[i].type == CYLINDER
            || vars->objects[i].type == CONE)
		{
			delete_matrix(vars->objects[i].gtfm[0]);
			delete_matrix(vars->objects[i].gtfm[1]);
			free(vars->objects[i].gtfm);
		}
        if (vars->objects[i].has_texture == 2)
        {
            free(vars->objects[i].texture_path);
            mlx_destroy_image(vars->mlx_ptr, vars->objects[i].image.img);
        }
        else if (vars->objects[i].has_texture == 1)
            delete_matrix(vars->objects[i].checker_matrix);
        if (vars->objects[i].has_bump == 1)
        {
            free(vars->objects[i].bump_path);
            mlx_destroy_image(vars->mlx_ptr, vars->objects[i].imgnormal.img);
        }
        i++;
	}
	free(vars->objects);
}

void	free_image(t_image *image)
{
	int	i;

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
