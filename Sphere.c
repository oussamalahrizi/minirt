#include "minirt.h"


int intersect_sphere(t_ray *ray, t_vec3 *hitposition, t_vec3 *localnormal, t_vec3 *localcolor)
{
	t_vec3 *ray_dir_normal = normalized(ray->direction);
	// Apply               To Transfer the ray from Original Cordinat System to the sphere's Local Cordinats System
	// GTFM Geometric Transform
	t_vec3 *intpoint;
	double s1;
	double s2;
	//double a = 1;
	double b = 2 * dot_product(ray->point1, ray_dir_normal);
	double c = dot_product(ray->point1, ray->point1) - 1.0;
	// 1 is the radius , I think he assumed the position of the camera is the same as the position of the sphere both 0, 0, 0
	double delta = (b * b) - (4 * c);
	if (delta >= 0)
	{
		s1 = (-b - sqrt(delta)) / 2.0;
		s2 = (-b + sqrt(delta)) / 2.0;
		if (s2 < s1)
			intpoint = vec3_add(ray->point1 , multiply_vec3_number(ray->direction, s2));
		else
			intpoint = vec3_add(ray->point1 , multiply_vec3_number(ray->direction, s1));
		copy_vector_values(hitposition, intpoint);
		(void) localcolor;
		(void) localnormal;
		return (1);
	}
	else
		return (0);
}
