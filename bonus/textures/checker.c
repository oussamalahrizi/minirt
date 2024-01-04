/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 06:29:31 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 06:32:23 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_matrix	*get_rotation(double angle)
{
	t_matrix	*rotation;

	rotation = create_matrix(3, 3);
	set_to_indentity(rotation);
	rotation->matrix[0][0] = cos(angle);
	rotation->matrix[0][1] = sin(angle);
	rotation->matrix[1][0] = -sin(angle);
	rotation->matrix[1][1] = cos(angle);
	return (rotation);
}

t_matrix	*get_scale(t_vec2 *scale)
{
	t_matrix	*scale_matrix;

	scale_matrix = create_matrix(3, 3);
	set_to_indentity(scale_matrix);
	scale_matrix->matrix[0][0] = scale->u;
	scale_matrix->matrix[1][1] = scale->v;
	return (scale_matrix);
}

t_matrix	*get_translation(void)
{
	t_matrix	*translation;

	translation = create_matrix(3, 3);
	set_to_indentity(translation);
	translation->matrix[0][2] = 0.0;
	translation->matrix[1][2] = 0.0;
	return (translation);
}

t_matrix	*set_transform_checker(t_vec2 *scale)
{
	t_matrix	*final;
	t_matrix	*translation;
	t_matrix	*scale_matrix;
	t_matrix	*rotation;

	translation = get_translation();
	scale_matrix = get_scale(scale);
	rotation = get_rotation(0);
	final = safe_matrix_multy(translation, rotation);
	final = safe_matrix_multy(final, scale_matrix);
	return (final);
}
