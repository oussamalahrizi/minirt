/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:29:57 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 06:34:36 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_vec2	apply_transform_checker(t_matrix *transform, t_vec2 *input)
{
	t_vec2		result;
	t_matrix	*m;
	t_matrix	*final;
	float		*values;

	m = create_matrix(3, 1);
	values = (float []){input->u, input->v, 1};
	fill_mt(m, values);
	final = mt_multiplication(transform, m);
	result = (t_vec2){final->matrix[0][0], final->matrix[1][0]};
	delete_matrix(final);
	delete_matrix(m);
	return (result);
}

t_vec3	get_checker_color(t_info *info, t_matrix *checker_matrix)
{
	t_vec2	inputvec;
	t_vec2	new_location;
	float	new_u;
	float	new_v;
	int		check;

	inputvec.u = (info->uv.u * 2) - 1;
	inputvec.v = (info->uv.v * 2) - 1;
	new_location = apply_transform_checker(checker_matrix, &inputvec);
	new_u = new_location.u;
	new_v = new_location.v;
	check = (int)(floorf(new_u)) + (int)(floorf(new_v));
	if (check % 2)
		return (new_vector(1, 1, 1));
	return (new_vector(0.0, 0.0, 0.0));
}
