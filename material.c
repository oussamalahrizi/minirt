#include "minirt.h"

t_vec3 *diffuse_color(t_object *objects, t_light *lights, t_int_info *object_info)
{
    t_vec3 *diff_color = new_vector3(0, 0, 0);
    double intensity;
    t_vec3 *color = new_vector3(0, 0, 0);
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    int validillum = 0;
    int illumfound = 0;
    int j = 0;
    while (j < 3)
    {
        validillum = compute_illumination(&lights[j], objects, object_info->closest_object,
            object_info->intpoint, object_info->localnormal, color, &intensity);
        if (validillum)
        {
            illumfound = 1;
            red += color->x * intensity;
            green += color->y * intensity;
            blue += color->z * intensity;
        }
        j++;
    }
    if (illumfound)
    {
        diff_color->x = (red * object_info->closest_object->base_color->x);
        diff_color->y = (green * object_info->closest_object->base_color->y);
        diff_color->z = (blue * object_info->closest_object->base_color->z);
    }
    return (diff_color);
}

t_vec3 *compute_specular(t_object *objects, t_int_info *current, t_light *lights, t_vec3 *intpoint,
                t_vec3 *localnormal, t_ray *camera_ray)
{
    t_vec3 *spc_color = new_vector3(0, 0, 0);
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    int j = 0;
    while (j < 3)
    {
        double intensity = 0;
        t_vec3 *lightdir = vec3_sub(lights[j].position, intpoint);
        lightdir = normalized(lightdir);
        t_vec3 *start_poi = vec3_add(intpoint, multiply_vec3_number(lightdir, 0.001));
        t_vec3 *po2 = vec3_add(start_poi, lightdir);
        t_ray *light_ray = new_ray(start_poi, po2);
        // print_vector(light_ray->direction);
        t_int_info *test = malloc(sizeof(t_int_info));
    
        test->localnormal = new_vector3(0, 0, 0);
        test->intpoint = new_vector3(0, 0, 0);
        test->localcolor = new_vector3(0, 0, 0);
        int  i = 0;
        int validint = 0;
        while (i < 4)
        {
            if (objects[i].type == SPHERE)
            {
                validint = intersect_sphere(light_ray, objects[i].gtfm, test->intpoint, test->localnormal);
            }
            else if (objects[i].type == PLANE)
            {
                validint = test_intersect_plane(light_ray, objects[i].gtfm, test->intpoint, test->localnormal);
            }
            if (validint)
                break;
            i++;
        }
        if (!validint)
        {
            // r = d - (2 * dot(d, localnormal) * localnormal)
            t_vec3 *d = copy_vector(light_ray->direction);
            double temp = dot_product(d, localnormal);
            t_vec3 *r = new_vector3(0,0,0);
            r->x = d->x - (2 * temp * localnormal->x);
            r->y = d->y - (2 * temp * localnormal->y);
            r->z = d->z - (2 * temp * localnormal->z);
            normalize(r);
            t_vec3 *v = copy_vector(camera_ray->direction);
            normalize(v);
            double prod = dot_product(r, v);
            if (prod > 0)
            {
                printf("prod positive \n");
                intensity = current->closest_object->reflectivity * pow(prod, current->closest_object->shininess);
            }
        }
        red += lights[j].color->x * intensity;
        green += lights[j].color->y * intensity;
        blue += lights[j].color->z * intensity;
        j++;
    }
    spc_color->x = red;
    spc_color->y = green;
    spc_color->z = blue;
    return (spc_color);
}

t_vec3 *compute_color(t_object *objects, t_light *lights, t_int_info *object_info, t_ray *camera_ray)
{
    t_vec3 *mat_color = new_vector3(0, 0, 0);
    t_vec3 *diff_color;
    t_vec3 *spc_color = new_vector3(0, 0, 0);

    diff_color = diffuse_color(objects, lights, object_info);

    if (object_info->closest_object->shininess > 0)
        spc_color = compute_specular(objects, object_info, lights, object_info->intpoint,
            object_info->localnormal, camera_ray);
    mat_color = vec3_add(diff_color, spc_color);

    return (mat_color);
}

