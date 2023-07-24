#include "minirt.h"


int intersect_sphere(t_ray *ray, t_vec3 **hitposition)
{
	t_vec3 *ray_dir_normal = normalized(ray->direction);
	// Apply               To Transfer the ray from Original Cordinat System to the sphere's Local Cordinats System
	// GTFM Geometric Transform
	// a is always 1 for some fkn reason
	double s1;
	double s2;
	double radius = 1;
	double a = 1;
	double b = 2 * dot_product(ray->origin, ray_dir_normal);
	double c = dot_product(ray->origin, ray->origin) - (radius * radius);
	// 1 is the radius , I think he assumed the position of the camera is the same as the position of the sphere both 0, 0, 0
	double delta = (b * b) - (4 * a * c);
	if (delta >= 0)
	{
		s1 = (-b - sqrt(delta)) / (2 * a);
		s2 = (-b + sqrt(delta)) / (2 * a);
		if (s2 < s1)
			*hitposition = vec3_add(ray->origin , multiply_vec3_number(ray->direction, s2));
		else
			*hitposition = vec3_add(ray->origin , multiply_vec3_number(ray->direction, s1));
		return (1);
	}
	else
		return (0);
}
