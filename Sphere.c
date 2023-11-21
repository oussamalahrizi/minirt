#include "minirt.h"


static t_vec2 get_uvcoord(t_vec3 *intpoint)
{
	double x = intpoint->x;
	double y = intpoint->y;
	double z = intpoint->z;

	double u = atan2(sqrtf(pow(x, 2) + pow(y, 2)) , z);
	double v = atan2(y , x);
	if (v < 0)
		v += M_PI;
	u /= M_PI;
	v /= M_PI;
	return ((t_vec2) {u, v});
}

int intersect_sphere(t_ray *ray, t_matrix **gtfm, t_vec3 *hitposition, t_vec3 *localnormal, t_vec2 *uv)
{
	t_ray *back_ray = apply_transform(ray, gtfm, BACKWARD);
	t_vec3 *vhat = normalized(back_ray->direction);
	// Apply               To Transfer the ray from Original Cordinat System to the sphere's Local Cordinats System
	// GTFM Geometric Transform
	t_vec3 *intpoint;
	double s1;
	double s2;
	// double a = 1;
	double b = 2 * dot_product(back_ray->point1, vhat);
	double c = dot_product(back_ray->point1, back_ray->point1) - 1.0f;
	double delta = (b * b) - 4.0 * c;
	if (delta > 0)
	{
		delta = sqrtf(delta);
		s1 = (-b - delta) / 2.0;
		s2 = (-b + delta) / 2.0;
		if (s1 < 0.0 || s2 < 0.0)
			return (0);
		if (s2 < s1)
			intpoint = vec3_add(back_ray->point1, multiply_vec3_number(vhat, s2));
		else
			intpoint = vec3_add(back_ray->point1, multiply_vec3_number(vhat, s1));
		t_vec3 *temp = apply_transform_vector(intpoint, FORWARD, gtfm);
		copy_vector_values(hitposition, temp);
		free(temp);
		// compute local normal
		temp = fixed_normal(gtfm[0], intpoint);
		copy_vector_values(localnormal, temp);
		free(temp);

		t_vec2 get_uv = get_uvcoord(intpoint);
		uv->x = get_uv.x;
		uv->y = get_uv.y;
		return (1);
	}
	return (0);
}
