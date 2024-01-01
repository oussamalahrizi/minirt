#include "../header.h"



int test_plane(t_ray *ray, t_info *info)
{
	float d;
	t_vec3 axis;
	t_vec3 vhat;
	t_vec3 origin;
	float denom;
	float t;
	t_vec3 xaxis;
	t_vec3 yaxis;

	origin = info->e->translation;
	axis = normalized(info->e->d_normal);
	vhat = normalized(ray->dir);
	d = -dot_product(origin, axis);
	denom = dot_product(axis, vhat);
	if (fabs(denom) < EPSILON)
		return (0);
	t = (-d - dot_product(ray->point1, axis)) / denom;
	if (t < EPSILON)
		return (0);
	info->localnormal = axis;
	if (dot_product(info->localnormal, vhat) > 0)
		info->localnormal = scale_vector(info->localnormal, -1);
	info->hitpoint = vec_add(ray->point1, scale_vector(vhat, t));
	xaxis = normalized(cross(get_up_vector(axis), axis));
	yaxis = normalized(cross(axis, xaxis));
	info->uv.u = -dot_product(info->hitpoint, xaxis);
	info->uv.v = dot_product(info->hitpoint, yaxis);
	info->tangent = scale_vector(xaxis, -1);
	return (1);
}