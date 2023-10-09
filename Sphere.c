#include "minirt.h"


int intersect_sphere(t_ray *ray, t_matrix **gtfm, t_vec3 *hitposition, t_vec3 *localnormal, t_vec3 *localcolor)
{
	t_ray *back_ray = apply_to_ray(ray, BACKWARD, gtfm);
	t_vec3 *ray_dir_normal = normalized(back_ray->direction);
	// Apply               To Transfer the ray from Original Cordinat System to the sphere's Local Cordinats System
	// GTFM Geometric Transform
	t_vec3 *intpoint;
	double s1;
	double s2;
	//double a = 1;
	double b = 2 * dot_product(back_ray->point1, ray_dir_normal);
	double c = dot_product(back_ray->point1, back_ray->point1) - 1.0;
	// 1 is the radius , I think he assumed the position of the camera is the same as the position of the sphere both 0, 0, 0
	double delta = (b * b) - (4 * c);
	if (delta >= 0)
	{
		s1 = (-b - sqrt(delta)) / 2.0;
		s2 = (-b + sqrt(delta)) / 2.0;
		if (s2 < s1)
			intpoint = vec3_add(back_ray->point1 , multiply_vec3_number(back_ray->direction, s2));
		else
			intpoint = vec3_add(back_ray->point1 , multiply_vec3_number(back_ray->direction, s1));
		t_vec3 *temp = apply_to_vector(intpoint, FORWARD, gtfm);
		copy_vector_values(hitposition, temp);
		free(temp);		
		// compute local normal
		t_vec3 *obj_origin = new_vector3(0.0, 0.0, 0.0);
		t_vec3 *new_origin = apply_to_vector(obj_origin, FORWARD, gtfm);
		temp = vec3_sub(hitposition, new_origin);
		temp = normalized(temp);
		copy_vector_values(localnormal, temp);
		free(temp);
		(void) localcolor;
		return (1);
	}
	return (0);
}
