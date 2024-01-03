/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 06:29:31 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/23 02:15:09 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"


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

t_matrix *get_scale(t_vec2 *scale)
{
	t_matrix *scale_matrix = create_matrix(3,3);

	set_to_indentity(scale_matrix);

	scale_matrix->matrix[0][0] = scale->u;
	scale_matrix->matrix[1][1] = scale->v;

	return (scale_matrix);
}

t_matrix *get_translation()
{
	t_matrix *translation = create_matrix(3,3);

	set_to_indentity(translation);

	translation->matrix[0][2] = 0.0;
	translation->matrix[1][2] = 0.0;

	return (translation);
}

t_matrix *set_transform_checker(t_vec2 *scale)
{
	t_matrix *final;

	t_matrix *translation = get_translation();
	t_matrix *scale_matrix = get_scale(scale);
	t_matrix *rotation = get_rotation(0);
	final = safe_matrix_multy(translation, rotation);
	final = safe_matrix_multy(final, scale_matrix);
	return (final);
}

t_vec2 apply_transform_checker(t_matrix *transform, t_vec2 *input)
{
	t_vec2 result;
	t_matrix *m;
	t_matrix *final;
	float *values;
	
	m = create_matrix(3, 1);
	values = (float []) {input->u, input->v, 1};
	fill_mt(m, values);
	final = mt_multiplication(transform, m);
	result = (t_vec2) {final->matrix[0][0], final->matrix[1][0]};
	delete_matrix(final);
	delete_matrix(m);
	return(result);
}

t_vec3 get_checker_color(t_info *info, t_matrix *checker_matrix)
{
	t_vec2 inputvec;
	t_vec2 new_location;

	inputvec.u = (info->uv.u * 2) - 1;
	inputvec.v = (info->uv.v * 2) - 1;
	
	new_location = apply_transform_checker(checker_matrix, &inputvec);
	
	float newU = new_location.u;
	float newV = new_location.v;

	int check = (int)(floorf(newU)) + (int)(floorf(newV));
	if (check % 2)
		return (new_vector(1,1,1));
	return (new_vector(0.0, 0.0, 0.0));
}