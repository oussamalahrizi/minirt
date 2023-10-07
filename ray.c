#include "minirt.h"

t_ray *new_ray(t_vec3 *point1, t_vec3 *point2)
{
    t_ray *ray = malloc(sizeof(t_ray));

    ray->point1 = copy_vector(point1);
    ray->point2 = copy_vector(point2);
    ray->direction = vec3_sub(point2, point1);
    return (ray);
}

