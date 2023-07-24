#include "minirt.h"

int compute_illumination(t_light *light, t_vec3 *hitpoint, t_color *color, double *intensity)
{
	// lightdir is the vector pointing from the intersection to the light position
	t_vec3 *lightdir = vec3_sub(light->position, hitpoint);
	lightdir = normalized(lightdir);

	// compute the angle between the normal of the sphere and the light ray
	t_vec3 *hitpoint_normal = normalized(hitpoint);
	double angle = acos(dot_product(hitpoint_normal, lightdir));
	// if the normal is pointing away from the light then we have no illumination

	if (angle > HALFPI)
	{
		color = &(light->color);
		*intensity = 0;
		return (0);
	}
	// in case we have illumination
	color = &(light->color);
	*intensity = light->intensity * (1 - (double)(angle / (double)HALFPI));
	return (1);
}