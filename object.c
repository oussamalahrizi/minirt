#include "minirt.h"


// void copy_object(t_object *origin, t_object *copy)
// {
//     copy->id = origin->id;
//     copy->type = origin->type;
//     copy->has_material = origin->has_material;
//     copy->shininess = origin->shininess;
//     copy->reflectivity = origin->reflectivity;
//     copy->base_color = copy_vector(origin->base_color);
//     copy->mat_color = copy_vector(origin->mat_color);
//     copy->translation = copy_vector(origin->translation);
//     copy->rotation = copy_vector(origin->rotation);
//     copy->scale = copy_vector(origin->scale);
//     copy->gtfm = malloc(sizeof(t_matrix **) * 2);
//     copy->gtfm[0] = new_matrix(origin->gtfm[0]->rows,origin->gtfm[0]->cols);
//     copy->gtfm[1] = new_matrix(origin->gtfm[1]->rows,origin->gtfm[1]->cols);
//     copy_matrix(copy->gtfm[0], origin->gtfm[0]);
//     copy_matrix(copy->gtfm[1], origin->gtfm[1]);
// }

int test_intersection(t_ray *ray, t_object *objects, t_int_info *info)
{
    int i;
    int validint;
    int intfound = 0;
    double mindist;
    double dist;
    t_vec3 *intpoint;
    t_vec3 *localnormal;
    info->closest_object = NULL;
    info->intpoint = new_vector3(0,0,0);
    info->localnormal = new_vector3(0,0,0);
    info->localcolor = new_vector3(0,0,0);
    intpoint = new_vector3(0,0,0);
    localnormal = new_vector3(0,0,0);
    i = 0;
    validint = 0;
    mindist = 1e6;
    while (i < 4)
    {
        if (objects[i].type == SPHERE)
            validint = intersect_sphere(ray, objects[i].gtfm, intpoint, localnormal);
        else if (objects[i].type == PLANE)
            validint = test_intersect_plane(ray, objects[i].gtfm, intpoint, localnormal);
        else if (objects[i].type == CYLINDER)
            validint = test_cylinder(ray, objects[i].gtfm, intpoint, localnormal);
        else if (objects[i].type == CONE)
            validint = test_cone(ray, objects[i].gtfm, intpoint, localnormal);
        if (validint)
        {
            intfound = 1;
            dist = normalize(vec3_sub(intpoint, ray->point1));
            if (dist < mindist)
            {
                mindist = dist;
                info->closest_object = &objects[i];
                copy_vector_values(info->intpoint, intpoint);
                copy_vector_values(info->localnormal, localnormal);
            }
        }
        i++;
    }
    return (intfound);
}