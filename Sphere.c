#include "minirt.h"


int intersect(t_ray *ray, t_vec3 *int_point, t_vec3 *local_normal, t_color *color)
{
	t_vec3 *ray_dir_normal = normalized(ray->direction);
	// a is always 1 for some fkn reason
	double a = 1;
	double b = 2 * dot_product(ray->origin, ray_dir_normal);
	double c = dot_product(ray->origin, ray->origin) - 1;
	// 1 is the radius , I think he assumed the position of the camera is the same as the position of the sphere both 0, 0, 0
	double delta = (b * b) - (4 * a * c);
	if (delta >= 0)
		return (1);
	else
		return (0);
}