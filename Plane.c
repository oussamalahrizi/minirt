#include "minirt.h"


int close_enough(double value)
{
    return (fabs(value) < EPSILON);
}

int test_intersect_plane(t_ray *ray, t_matrix **gtfm, t_vec3 *hitposition, t_vec3 *localnormal, t_vec2 *uv)
{
    t_ray *back_ray = apply_transform(ray,  gtfm, BACKWARD);
    t_vec3 *ray_dir = normalized(back_ray->direction);
    if (!close_enough(ray_dir->z))
    {
        double t = back_ray->point1->z / -ray_dir->z;
        // if t is negative then the intersection is behind the camera
        if (t > 0.0)
        {
            /*
                double u = bckRay.m_point1.GetElement(0) + (k.GetElement(0) * t);
                double v = bckRay.m_point1.GetElement(1) + (k.GetElement(1) * t);
            */
            double u = back_ray->point1->x + (ray_dir->x * t);
            double v = back_ray->point1->y + (ray_dir->y * t);
            /* If the magnitude of both u and v is less than or equal to one
            then we must be in the plane. */

            if ((fabs(u) < 1.0) && (fabs(v) < 1.0))
            {
                // point of intersection
                t_vec3 *intpoint = vec3_add(back_ray->point1, multiply_vec3_number(ray_dir, t));
                // transform back the vector to original world
                t_vec3 *temp = apply_transform_vector(intpoint, FORWARD, gtfm);
                copy_vector_values(hitposition, temp);
                free(temp);
                // Compute the local normal.
                // t_vec3 *localorigin = new_vector3(0.0, 0.0, 0.0);
                t_vec3 *normalvector = new_vector3(0.0, 0.0, -1.0);
                // t_vec3 *globalorigin = apply_transform_vector(localorigin, FORWARD, gtfm);
                temp = fixed_normal(gtfm[0], normalvector);
                copy_vector_values(localnormal, temp);
                free(temp);
                uv->x = u;
                uv->y = v;
                if (u < -1 || u > 1 || v < -1 || u > 1)
                {
                    printf("stop\n");
                    while(1);
                }
                return (1);
            }
            return (0);
        }
        return (0);
    }
    return (0);
}