#include "minirt.h"

int close_enough(double value)
{
    return (fabs(value) < EPSILON);
}

double	norm(double v)
{
	if (fabs(v) <= 1)
		return (v);
	while (v > 1)
		v -= 1.f;
	while (v < -1)
		v += 1.f;
	return (v);
}

// int test_intersect_plane(t_ray *ray, t_matrix **gtfm, t_vec3 *hitposition, t_vec3 *localnormal, t_vec2 *uv)
// {
//     t_ray *back_ray = apply_transform(ray, gtfm, BACKWARD);
//     t_vec3 *ray_dir = normalized(back_ray->direction);
//     if (close_enough(ray_dir->z))
//         return (0);

//     double t = back_ray->point1->z / -ray_dir->z;
//     // if t is negative then the intersection is behind the camera
//     if (t < 0.0)
//         return (0);

//     /* ax + tbx =   u;
//         double u = bckRay.m_point1.GetElement(0) + (k.GetElement(0) * t);
//         double v = bckRay.m_point1.GetElement(1) + (k.GetElement(1) * t);
//     */
//     /*
//      p = p1 * u + p2 * v + p0 = Rorg + at;
//      Rorg_x + a_x t = u;
//      Rorg_y + a_y t = v;
//      Rorg_z + a_z t = 0;
//      t = -Rorgz / a_z;
//      */
    
//     double u = back_ray->point1->x + (ray_dir->x * t);
//     double v = back_ray->point1->y + (ray_dir->y * t);
//     /* If the magnitude of both u and v is less than or equal to one
//     then we must be in the plane. */

//     // point of intersection
//     t_vec3 *intpoint = vec3_add(back_ray->point1, scale_vector(ray_dir, t));
//     // transform back the vector to original world
//     t_vec3 *temp = apply_transform_vector(intpoint, FORWARD, gtfm);
//     copy_vector_values(hitposition, temp);
//     free(temp);
//     // Compute the local normal.
//     // t_vec3 *localorigin = new_vector3(0.0, 0.0, 0.0);
//     t_vec3 *normalvector = new_vector3(0.0, 0.0, -1.0);
//     // t_vec3 *globalorigin = apply_transform_vector(localorigin, FORWARD, gtfm);
//     temp = fixed_normal(gtfm[0], normalvector);
//     copy_vector_values(localnormal, temp);
//     free(temp);

//     // t_vec3 *xaxis = normalized(cross(new_vector3(1, 0, 0), normalvector));
//     // t_vec3 *yaxis = normalized(cross(normalvector, xaxis));


//     uv->x = norm(u);
//     uv->y = norm(v);
    
//     return (1);
// }

int test_intersect_plane(t_ray *ray, t_matrix **gtfm, t_vec3 *hitposition, t_vec3 *localnormal, t_vec2 *uv)
{
	(void) gtfm;
    t_vec3 *origin = new_vector3(0,0,0);

	t_vec3 *axis = new_vector3(0, 0, -1);
	t_vec3 *vhat = normalized(ray->direction);
	double d = dot_product(origin, axis);

	double denom = dot_product(axis, vhat);
	if (fabs(denom) < EPSILON)
		return (0);
	double t = (-d - dot_product(axis, ray->point1)) / denom;
	if (t < EPSILON)
		return (0);
	t_vec3 *intpoint = vec3_add(ray->point1, scale_vector(vhat, t));
	t_vec3 *normal = copy_vector(axis);
	if (dot_product(normal, vhat) > 0)
		normal = scale_vector(normal, -1);
	t_vec3 *xaxis = normalized(cross(new_vector3(1, 0, 0), axis));
	t_vec3 *yaxis = normalized(cross(axis, xaxis));

	uv->x = -dot_product(intpoint, xaxis);
	uv->y = dot_product(intpoint, yaxis);
	uv->x = uv->x - floor(uv->x);
	uv->y = uv->y - floor(uv->y);
	uv->x = 2 * uv->x - 1;
	uv->y = 2 * uv->y - 1;
	copy_vector_values(hitposition, intpoint);
	copy_vector_values(localnormal, normal);
	return (1);
}