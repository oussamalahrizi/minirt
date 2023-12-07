#include "../header.h"


float get_dist(t_vec3 *ray_org, t_vec3 *vhat)
{
	float b;
	float c;
	float delta;
	float t1;
	float t2;

	b = 2.0f * dot_product(ray_org, vhat);
	c = dot_product(ray_org, ray_org) - 1.0f;
	delta = (b * b) - (4.0f * c);
	if (delta < 0)
		return (-1);
	delta  = sqrtf(delta);
	t1 = (-b - delta) / 2.0f;
	t2 = (-b + delta) / 2.0f;
	if (t1 < 0.0f || t2 < 0.0f)
		return (-1);
	if (t1 < t2)
		return (t1);
	return (t2);
}

int test_sphere(t_ray *ray, t_info *info)
{
	t_matrix **gtfm;
	t_ray back_ray;
	t_vec3 vhat;
	float t;
	t_vec3 localpoi;

	gtfm = info->e->gtfm;
	back_ray = apply_transform(ray, gtfm, BACKWARD);
	vhat = normalized(back_ray.dir);
	t = get_dist(&back_ray.point1, &vhat);
	if (t == -1)
		return (0);
	vhat = scale_vector(&vhat, t);
	localpoi = vec_add(&back_ray.point1, &vhat);
	info->hitpoint = apply_transform_vector(&localpoi, FORWARD, gtfm);
	info->localnormal = fixed_normal(gtfm[0], &localpoi);
	return (1);
}