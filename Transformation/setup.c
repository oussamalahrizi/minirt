/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:36:29 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/25 12:36:44 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_matrix	*rotation_matrix_y(double angle)
{
	t_matrix	*rotationmatrix;

	rotationmatrix = create_matrix(4, 4);
	set_to_indentity(rotationmatrix);
	rotationmatrix->matrix[0][0] = cosf(angle);
	rotationmatrix->matrix[0][2] = sinf(angle);
	rotationmatrix->matrix[2][0] = -sinf(angle);
	rotationmatrix->matrix[2][2] = cosf(angle);
	return (rotationmatrix);
}

t_matrix	*rotation_matrix_x(double angle)
{
	t_matrix	*rotationmatrix;

	rotationmatrix = create_matrix(4, 4);
	set_to_indentity(rotationmatrix);
	rotationmatrix->matrix[1][1] = cosf(angle);
	rotationmatrix->matrix[1][2] = -sinf(angle);
	rotationmatrix->matrix[2][1] = sinf(angle);
	rotationmatrix->matrix[2][2] = cosf(angle);
	return (rotationmatrix);
}

t_matrix	*rotation_matrix_z(double angle)
{
	t_matrix	*rotationmatrix;

	rotationmatrix = create_matrix(4, 4);
	set_to_indentity(rotationmatrix);
	rotationmatrix->matrix[0][0] = cosf(angle);
	rotationmatrix->matrix[0][1] = -sinf(angle);
	rotationmatrix->matrix[1][0] = sinf(angle);
	rotationmatrix->matrix[1][1] = cosf(angle);
	return (rotationmatrix);
}

t_matrix	*translation_matrix(t_vec3 *translation)
{
	t_matrix	*translationmatrix;

	translationmatrix = create_matrix(4, 4);
	set_to_indentity(translationmatrix);
	translationmatrix->matrix[0][3] = translation->x;
	translationmatrix->matrix[1][3] = translation->y;
	translationmatrix->matrix[2][3] = translation->z;
	return (translationmatrix);
}

t_matrix	*scal_matrix(t_vec3 *scal)
{
	t_matrix	*scalmatrix;

	scalmatrix = create_matrix(4, 4);
	set_to_indentity(scalmatrix);
	scalmatrix->matrix[0][0] = scal->x;
	scalmatrix->matrix[1][1] = scal->y;
	scalmatrix->matrix[2][2] = scal->z;
	return (scalmatrix);
}
