#include "../header.h"


float get_dist(t_vec3 *ray_org, t_vec3 *vhat)
{
	float b;
	float c;
	float delta;
	float t1;
	float t2;

	b = 2.0 * dot_product(ray_org, vhat);
	c = dot_product(ray_org, ray_org) - 1.0f;
	delta = square(b) - (4.0 * c);
	if (delta > 0)
	{
		delta  = sqrtf(delta);
		t1 = (-b - delta) / 2.0;
		t2 = (-b + delta) / 2.0;
		if (t1 < 0.0 || t2 < 0.0)
			return (-1);
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	return (-1);
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
	float b = 2 * dot_product(&back_ray.point1, &vhat);
	float c = dot_product(&back_ray.point1, &back_ray.point1) - 1.0;
	float delta  = square(b) - 4 * c;
	if (delta > 0)
	{
		float t1 = (-b - delta ) / 2.0;
		float t2 = (-b + delta ) / 2.0;
		if (t1 < 0 || t2 < 0)
			return (0);
		if (t1 < t2)
		{
			t_vec3 temp = scale_vector(&vhat, t1);
			localpoi = vec_add(&back_ray.point1, &temp);
		}
		else
		{
			t_vec3 temp = scale_vector(&vhat, t2);
			localpoi = vec_add(&back_ray.point1, &temp);
		}
		info->hitpoint = apply_transform_vector(&localpoi, FORWARD, gtfm);
		info->localnormal = fixed_normal(gtfm[0], &localpoi);
		return (1);
	}
	return (0);
}