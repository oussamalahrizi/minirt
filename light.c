#include "minirt.h"

int compute_illumination(t_light *light, t_object *object_list, t_object *current_object, t_vec3 *hitpoint,
	t_vec3 *localnormal, t_vec3 *color, double *intensity)
{
	// lightdir is the vector pointing from the intersection to the light position
	t_vec3 *lightdir = vec3_sub(light->position, hitpoint);
	lightdir = normalized(lightdir);
	t_ray *ray = new_ray(hitpoint, vec3_add(hitpoint, lightdir));

	int i = 0;
	t_vec3 *intpoint = new_vector3(0,0,0);
	t_vec3 *poinormal = new_vector3(0,0,0);
	int validint = 0;
	while (i < 4)
	{
		if (current_object->id != object_list[i].id)
		{
			if (object_list[i].type == SPHERE && 
				intersect_sphere(ray, object_list[i].gtfm, intpoint, poinormal))
				validint = 1;
			else if (object_list[i].type == PLANE &&
				test_intersect_plane(ray, object_list[i].gtfm, intpoint, poinormal))
				validint = 1;
		}
		if (validint)
			break;
		i++;
	}
	if (!validint)
	{
		double angle = acos(dot_product(localnormal, lightdir));
		if (angle > HALFPI)
		{
			copy_vector_values(color, light->color);
			*intensity = 0;
			return (0);
		}
		else
		{
			copy_vector_values(color, light->color);
			*intensity = light->intensity * (1 - (double)(angle / (double)HALFPI));
			return (1);
		}
	}
	else // shadow
	{
		copy_vector_values(color, light->color);
		*intensity = 0;
		return (0);
	}
	return (1);
}