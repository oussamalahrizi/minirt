#include "minirt.h"

t_vec3 *diffuse_color(t_object *objects, t_light *lights, t_int_info *object_info, t_vec3 *base_color)
{
    t_vec3 *diff_color = new_vector3(0.0, 0.0, 0.0);
    double intensity;
    t_vec3 *color = new_vector3(0.0, 0.0, 0.0);
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
            red += (lights[j].color->x * intensity);
            green += (lights[j].color->y * intensity);
            blue += (lights[j].color->z * intensity);
        }
        j++;
    }
    if (illumfound)
    {

        diff_color->x = (red * base_color->x);
        diff_color->y = (green * base_color->y);
        diff_color->z = (blue * base_color->z);
    }

    t_vec3 *ambient = scale_vector(new_vector3(0.8, 0.8, 0.8), 0.2);
    diff_color = vec3_add(diff_color, ambient);
    return (diff_color);
}

t_vec3 *compute_specular(t_object *objects, t_int_info *current, t_light *lights, t_vec3 *intpoint,
                         t_vec3 *localnormal, t_ray *camera_ray)
{
    t_vec3 *spc_color = NULL;
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    int j = 0;
    while (j < 3)
    {
        double intensity = 0;
        t_vec3 *lightdir = normalized(vec3_sub(lights[j].position, intpoint));
        t_vec3 *start_poi = vec3_add(intpoint, scale_vector(lightdir, 0.001));
        t_vec3 *po2 = vec3_add(start_poi, lightdir);
        t_ray *light_ray = new_ray(start_poi, po2);
        t_vec3 *temp = copy_vector(light_ray->direction);
        // print_vector(light_ray->direction);
        t_int_info test;

        test.localnormal = new_vector3(0, 0, 0);
        test.intpoint = new_vector3(0, 0, 0);
        test.localcolor = new_vector3(0, 0, 0);
        test.uv = malloc(sizeof(t_vec2));

        int i = 0;
        int validint = 0;

        while (i < 4)
        {
            if (objects[i].type == SPHERE)
            {
                validint = intersect_sphere(light_ray, objects[i].gtfm, test.intpoint, test.localnormal, test.uv);
            }
            else if (objects[i].type == PLANE)
            {
                validint = test_intersect_plane(light_ray, objects[i].gtfm, test.intpoint, test.localnormal, test.uv);
            }
            else if (objects[i].type == CYLINDER)
                validint = test_cylinder(light_ray, objects[i].gtfm, test.intpoint, test.localnormal, test.uv);
            else if (objects[i].type == CONE)
                validint = test_cone(light_ray, objects[i].gtfm, test.intpoint, test.localnormal, test.uv);
            if (validint)
                break;
            i++;
        }

        if (!validint)
        {
            // r = d - (2 * dot(d, localnormal) * localnormal)
            t_vec3 *d = copy_vector(temp);
            t_vec3 *r = reflect(d, localnormal);
            t_vec3 *v = normalized(camera_ray->direction);

            double prod = dot_product(r, v);

            if (prod > 0.0)
            {
                intensity = current->closest_object->reflectivity * pow(prod, current->closest_object->shininess);
            }
        }
        red += lights[j].color->x * intensity;
        green += lights[j].color->y * intensity;
        blue += lights[j].color->z * intensity;
        j++;
    }
    spc_color = new_vector3(red, green, blue);
    return (spc_color);
}

int test_cast_ray(t_ray *cast_ray, t_object *objects, t_object *current, t_int_info *info)
{
    double dist;
    double min_dist = 1e6;
    t_vec3 *intpoint = new_vector3(0, 0, 0);
    t_vec3 *localnormal = new_vector3(0, 0, 0);
    t_vec2 *uv = malloc(sizeof(t_vec2));
    int intfound = 0;
    int validint = 0;

    int i = 0;
    while (i < 4)
    {
        if (&objects[i] != current)
        {
            if (objects[i].type == SPHERE)
                validint = intersect_sphere(cast_ray, objects[i].gtfm, intpoint, localnormal, uv);
            else if (objects[i].type == PLANE)
                validint = test_intersect_plane(cast_ray, objects[i].gtfm, intpoint, localnormal, uv);
            else if (objects[i].type == CYLINDER)
                validint = test_cylinder(cast_ray, objects[i].gtfm, intpoint, localnormal, uv);
            else if (objects[i].type == CONE)
                validint = test_cone(cast_ray, objects[i].gtfm, intpoint, localnormal, uv);
            if (validint)
            {
                intfound = 1;
                dist = normalize(vec3_sub(intpoint, cast_ray->point1));
                if (dist < min_dist)
                {
                    min_dist = dist;
                    info->closest_object = &objects[i];
                    copy_vector_values(info->intpoint, intpoint);
                    copy_vector_values(info->localnormal, localnormal);
                    info->uv->x = uv->x;
                    info->uv->y = uv->y;
                }
            }
        }
        i++;
    }
    return (intfound);
}

double randomBetween()
{
    double min = -0.125;
    double max = 0.125;
    double scale = rand() / (double)RAND_MAX; // [0, 1.0]
    return min + scale * (max - min);
}

t_vec3 *reflection_color(t_object *objects, t_light *lights, t_int_info *object_info, t_ray *incident_ray, int ref_count)
{
    t_vec3 *reflect_color = new_vector3(0, 0, 0);

    t_vec3 *d = copy_vector(incident_ray->direction);

    t_vec3 *reflect_vector = reflect(d, object_info->localnormal);
    t_ray *cast_ray = new_ray(object_info->intpoint, vec3_add(object_info->intpoint, reflect_vector));

    t_int_info test;
    test.intpoint = new_vector3(0, 0, 0);
    test.localnormal = new_vector3(0, 0, 0);
    test.uv = malloc(sizeof(t_vec2));
    int valid_int = test_cast_ray(cast_ray, objects, object_info->closest_object, &test);
    if (valid_int && ref_count < MAX_REF)
    {
        ref_count++;
        if (test.closest_object->has_material == 1)
        {
            reflect_color = compute_color(objects, lights, &test, cast_ray, ref_count);
        }
        else
        {
            reflect_color = diffuse_color(objects, lights, &test, test.closest_object->base_color);
        }
    }
    return (reflect_color);
}

t_vec3 *get_up_vector(t_vec3 *forward)
{
    t_vec3 *up;
    double d;

    up = new_vector3(0, 1, 0);
    d = dot_product(up, forward);
    if (d > 0.9)
    {
        free(up);
        up = new_vector3(0, 0, 1);
    }
    else if (d < -0.9)
    {
        free(up);
        up = new_vector3(0, 0, -1);
    }
    return (up);
}

t_vec3 *get_bump_normal(t_int_info *info)
{
    t_vec3 *tangent = normalized(cross(get_up_vector(info->localnormal), info->localnormal));
    t_vec3 *bitangent = normalized(cross(info->localnormal, tangent));

    t_vec2 uv = *(info->uv);
    double h = get_color_texture(&uv, info->closest_object->imgnormal)->x;
    double t1 = 1.0 / info->closest_object->imgnormal->width;
    double t2 = 1.0 / info->closest_object->imgnormal->height;
    uv.x += t1;
    double hr = get_color_texture(&uv, info->closest_object->imgnormal)->x;
    uv.x -= t1;
    uv.y += t2;
    double hu = get_color_texture(&uv, info->closest_object->imgnormal)->x;

    t_vec3 *part1 = new_vector3(1, 0, (hr - h) * 10);
    t_vec3 *part2 = new_vector3(0, 1, (hu - h) * 10);
    t_vec3 *bumpnormal = normalized(cross(part1, part2));

    t_matrix *tbn = create_matrix(3, 3);
    double *values = (double[]){tangent->x, bitangent->x, info->localnormal->x,
                                tangent->y, bitangent->y, info->localnormal->y,
                                tangent->z, bitangent->z, info->localnormal->z};
    fill_mt(tbn, values);

    t_matrix *bmpmatrix = create_matrix(3, 1);
    values = (double[]){bumpnormal->x, bumpnormal->y, bumpnormal->z};
    fill_mt(bmpmatrix, values);
    t_matrix *result = mt_multiplication(tbn, bmpmatrix);
    t_vec3 *outputvec = normalized(new_vector3(result->matrix[0][0],
                                               result->matrix[1][0],
                                               result->matrix[2][0]));
    return (outputvec);
}

t_vec3 *compute_color(t_object *objects, t_light *lights, t_int_info *object_info, t_ray *camera_ray, int ref_count)
{

    t_vec3 *mat_color = NULL;
    t_vec3 *diff_color = NULL;
    t_vec3 *reflect_color = NULL;
    t_vec3 *spc_color = NULL;

    // calculate the diffuse color (along with ambient ofc)
    if (object_info->closest_object->has_texture)
    {
        if (object_info->closest_object->has_texture == 2)
        {
            // calculate the new normal
            // object_info->localnormal = get_bump_normal(object_info);

            // t_vec3 *color = get_color_texture(object_info->uv, object_info->closest_object->image);
            // if (object_info->closest_object->type == PLANE)
            //     color = object_info->closest_object->base_color;
            diff_color = diffuse_color(objects, lights, object_info,
                get_color_texture(object_info->uv, object_info->closest_object->image));
        }
        else
        diff_color = diffuse_color(objects, lights, object_info,
                                   get_color_checker(object_info->uv, object_info->closest_object->checker_matrix));
    }
    else
        diff_color = diffuse_color(objects, lights, object_info, object_info->closest_object->base_color);

    mat_color = diff_color;
    // if the material has reflectivity compute the reflection color
    if (object_info->closest_object->reflectivity > 0.0f)
    {
        reflect_color = reflection_color(objects, lights, object_info, camera_ray, ref_count);
        t_vec3 *part1 = scale_vector(reflect_color, object_info->closest_object->reflectivity);
        t_vec3 *part2 = scale_vector(diff_color, 1.0 - object_info->closest_object->reflectivity);
        mat_color = vec3_add(part1, part2);
    }

    // compute specular color if the object has shininess
    if (object_info->closest_object->shininess > 0.0f)
        spc_color = compute_specular(objects, object_info, lights, object_info->intpoint, object_info->localnormal, camera_ray);

    mat_color = vec3_add(mat_color, spc_color);
    // mat_color = copy_vector(spc_color);
    // (void)diff_color;
    return (mat_color);
}
