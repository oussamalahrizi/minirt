#include "minirt.h"

t_matrix *get_rotation(double angle)
{
	t_matrix *rotation = create_matrix(3,3);

	set_to_indentity(rotation);

	rotation->matrix[0][0] = cos(angle);
	rotation->matrix[0][1] = sin(angle);
	rotation->matrix[1][0] = -sin(angle);
	rotation->matrix[1][1] = cos(angle);

	return (rotation);
}

t_matrix *get_scale(t_vec3 *scale)
{
	t_matrix *scale_matrix = create_matrix(3,3);

	set_to_indentity(scal_matrix);

	scale_matrix->matrix[0][0] = scale->x;
	scale_matrix->matrix[1][1] = scale->y;

	return (scale_matrix);
}

t_matrix *get_translation(t_vec3 *trans)
{
	t_matrix *translation = create_matrix (3,3);

	set_to_indentity(translation);

	translation->matrix[0][2] = trans->x;
	translation->matrix[1][2] = trans->y;

	return (translation);
}

t_matrix *set_transform_checker(t_vec3 *trans, t_vec3 *scale, double angle)
{
	t_matrix *final;

	t_matrix *translation = get_translation(trans);
	t_matrix *scale_matrix = get_scale(scale);
	t_matrix *rotation = get_rotation(angle);
	final = safe_matrix_multy(translation, rotation);
	final = safe_matrix_multy(final, scale_matrix);

	return (final);
}

t_vec2 *apply_transform_checker(t_matrix *transform, t_vec3 *input)
{
	t_matrix *m = create_matrix(3, 1);

	double *values = (double []) {input->x, input->y, 1};

	fill_mt(m, values);

	t_matrix *final = safe_matrix_multy(transform, m);
	t_vec2 *result = malloc(sizeof(t_vec2));
	result->x = final->matrix[0][0];
	result->y = final->matrix[1][0];
	return(result);
}