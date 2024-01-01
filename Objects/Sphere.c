#include "../header.h"


static t_vec2 get_uvcoords(t_vec3 intpoint)
{
	float x = intpoint.x;
	float y = intpoint.y;
	float z = intpoint.z;

	float u = atan2(y, x) / M_PI;
	float v = 2.0 * (atan2(sqrtf(powf(x, 2) + powf(y, 2)), z) / M_PI) - 1.0;

	u = (u + 1) / 2.0;
	v = (v + 1) / 2.0;
	return ((t_vec2) {u, v});
}


int test_sphere(t_ray *ray, t_info *info)
{
	t_matrix **gtfm;
	t_ray back_ray;
	t_vec3 vhat;
	t_vec3 localpoi;

	gtfm = info->e->gtfm;
	back_ray = apply_transform(ray, gtfm, BACKWARD);
	vhat = normalized(back_ray.dir);
	float b = 2 * dot_product(back_ray.point1, vhat);
	float c = dot_product(back_ray.point1, back_ray.point1) - 1.0;
	float delta  = square(b) - (4 * c);
	if (delta > 0)
	{
		delta = sqrtf(delta);
		float t1 = (-b - delta ) / 2.0;
		float t2 = (-b + delta ) / 2.0;
		if (t1 < 0 || t2 < 0)
			return (0);
		if (t1 < t2)
			localpoi = vec_add(back_ray.point1, scale_vector(vhat, t1));
		else
			localpoi = vec_add(back_ray.point1, scale_vector(vhat, t2));
		info->hitpoint = apply_transform_vector(&localpoi, FORWARD, gtfm);
		info->localnormal = fixed_normal(gtfm[0], &localpoi);
		info->uv = get_uvcoords(localpoi);
		info->tangent = cross(get_up_vector(info->localnormal), info->localnormal);
		return (1);
	}
	return (0);
}