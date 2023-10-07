#include "minirt.h"

t_matrix *get_translation(t_vec3 *tr)
{
    t_matrix *trans = identity_matrix(4);

    trans->data[0][3] = tr->x; 
    trans->data[1][3] = tr->y; 
    trans->data[2][3] = tr->z;

    return (trans);
}

t_matrix *get_rotation_z(t_vec3 *rotation)
{
    t_matrix *rotation_z = identity_matrix(4);

    rotation_z->data[0][0] = cos(rotation->z);
    rotation_z->data[0][1] = -sin(rotation->z);
    rotation_z->data[1][0] = sin(rotation->z);
    rotation_z->data[1][1] = cos(rotation->z);

    return (rotation_z);
}

t_matrix *get_rotation_y(t_vec3 *rotation)
{
    t_matrix *rotation_y = identity_matrix(4);

    rotation_y->data[0][0] = cos(rotation->y);
    rotation_y->data[0][2] = sin(rotation->y);
    rotation_y->data[2][0] = -sin(rotation->y);
    rotation_y->data[2][2] = cos(rotation->y);
    
    return (rotation_y);
}

t_matrix *get_rotation_x(t_vec3 *rotation)
{
    t_matrix *rotation_x = identity_matrix(4);

    rotation_x->data[1][1] = cos(rotation->x);
    rotation_x->data[1][2] = -sin(rotation->x);
    rotation_x->data[2][1] = sin(rotation->x);
    rotation_x->data[2][2] = cos(rotation->x);

    return (rotation_x);
}

t_matrix *get_scale(t_vec3 *scale)
{
    t_matrix *scale_matrix = identity_matrix(4);

    scale_matrix->data[0][0] = scale->x;
    scale_matrix->data[1][1] = scale->y;
    scale_matrix->data[2][2] = scale->z;

    return (scale_matrix);
}

t_matrix **set_transform(t_vec3 *trans, t_vec3 *rotation, t_vec3 *scale)
{
    t_matrix *translation = get_translation(trans);
    t_matrix *rotation_x = get_rotation_x(rotation);
    t_matrix *rotation_y = get_rotation_y(rotation);
    t_matrix *rotation_z = get_rotation_z(rotation);
    t_matrix *scale_matrix = get_scale(scale);

    t_matrix *forward;
    t_matrix *backward;
    t_matrix *temp;

    forward = matrix_multiply(translation, scale_matrix);
    temp = forward;
    forward = matrix_multiply(forward, rotation_x);
    free_matrix(temp);
    temp = forward;
    forward = matrix_multiply(forward, rotation_y);
    free_matrix(temp);
    temp = forward;
    forward = matrix_multiply(forward, rotation_z);
    free_matrix(temp);
    backward = inverse(forward);
    t_matrix **gtform = malloc(sizeof(t_matrix *) * 2);

    free_matrix(translation);
    free_matrix(rotation_x);
    free_matrix(rotation_y);
    free_matrix(rotation_z);
    free_matrix(scale_matrix);

    gtform[0] = forward;
    gtform[1] = backward;

    return (gtform);
}

t_vec3 *apply_to_vector(t_vec3 *input_vec, int dirflag, t_matrix **matrices)
{
    t_matrix *tempdata = new_matrix(4, 1);
    t_matrix *result_matrix;

    tempdata->data[0][0] = input_vec->x;
    tempdata->data[1][0] = input_vec->y;
    tempdata->data[2][0] = input_vec->z;
    tempdata->data[3][0] = 1.0;

    if (dirflag)
        result_matrix = matrix_multiply(matrices[0], tempdata);
    else
        result_matrix = matrix_multiply(matrices[1], tempdata);

    t_vec3 *output_vec = new_vector3(result_matrix->data[0][0], result_matrix->data[1][0],
        result_matrix->data[2][0]);
    free_matrix(tempdata);
    free_matrix(result_matrix);
    return (output_vec);
}

t_vec3 *apply_to_ray(t_ray *input_ray, int dirflag, t_matrix **matrices)
{
    t_ray *output_ray = malloc(sizeof(t_ray));

    output_ray->point1 = apply_to_vector(input_ray->point1, dirflag, matrices);
    output_ray->point2 = apply_to_vector(input_ray->point2, dirflag, matrices);
    output_ray->direction = vec3_sub(output_ray->point2, output_ray->point1);
    return (output_ray);
}
