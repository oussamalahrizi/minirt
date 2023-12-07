#include "../header.h"



int test_plane(t_ray *ray, t_info *info)
{
	float d;
	t_vec3 axis;
	t_vec3 vhat;
	t_vec3 origin;
	float denom;
	float t;

	origin = info->e->translation;
	axis = normalized(info->e->d_normal);
	vhat = normalized(ray->dir);
	d = -dot_product(&origin, &axis);
	denom = dot_product(&axis, &vhat);
	if (fabs(denom) < EPSILON)
		return (0);
	t = (-d - dot_product(&ray->point1, &axis)) / denom;
	if (t < EPSILON)
		return (0);
	info->localnormal = axis;
	if (dot_product(&info->localnormal, &vhat) > 0)
		info->localnormal = scale_vector(&info->localnormal, -1);
	info->hitpoint = scale_vector(&vhat, t);
	info->hitpoint = vec_add(&ray->point1, &info->hitpoint);
	return (1);
}