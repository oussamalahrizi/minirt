/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:11 by aaitouna          #+#    #+#             */
/*   Updated: 2023/11/15 22:24:20 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_matrix	**set_transform(t_vec3 *translation, t_vec3 *rotation,
		t_vec3 *scal)
{
	t_matrix	**result = malloc(sizeof(t_matrix *) * 2);
	t_matrix *forward;

	if (!translation || !rotation || !scal)
	{
		printf("some thing null in set_transform \n");
		return (NULL);
	}
	forward = NULL;
	forward = safe_matrix_multy(translation_matrix(translation),
			rotation_matrix_x(rotation->x));
	forward = safe_matrix_multy(forward, rotation_matrix_y(rotation->y));
	forward = safe_matrix_multy(forward, rotation_matrix_z(rotation->z));
	forward = safe_matrix_multy(forward, scal_matrix(scal));
	result[0] = forward;
	result[1] = inverse(forward);
	return (result);
}

t_vec3	*apply_transform_vector(t_vec3 *inputVector, int dirFlag,
		t_matrix **gtfm);

t_ray	*apply_transform(t_ray *input_ray, t_matrix **gtfm, int dirFlag)
{
	t_ray	*output;

	output = malloc(sizeof(t_ray));
	output->point1 = apply_transform_vector(input_ray->point1, dirFlag, gtfm);
	output->point2 = apply_transform_vector(input_ray->point2, dirFlag, gtfm);
	output->direction = vec3_sub(output->point2, output->point1);
	return (output);
}

t_vec3	*apply_transform_vector(t_vec3 *inputVector, int dirFlag,
		t_matrix **gtfm)
{
	t_matrix	*tmp;
	double		*values;
	t_matrix	*resultmt;
	t_vec3	*result;

	resultmt = NULL;
	values = (double []){inputVector->x, inputVector->y, inputVector->z, 1.0f};
	tmp = create_matrix(4, 1);
	fill_mt(tmp, values);
	if (dirFlag)
		resultmt = mt_multiplication(gtfm[0], tmp);
	else
		resultmt = mt_multiplication(gtfm[1], tmp);
	if (!resultmt)
	{
		delete_matrix(tmp);
		return (new_vector3(0.0, 0.0, 0.0));
	}
	result = new_vector3(resultmt->matrix[0][0], resultmt->matrix[1][0],
			resultmt->matrix[2][0]);
	delete_matrix(resultmt);
	delete_matrix(tmp);
	return (result);
}

// void	set_lineartfm(t_object *this)
// {
// 	t_matrix	*tmp;
// 	t_matrix	*inverse_tmp;
// 	int			i;
// 	int			j;

// 	this->lineartfm = NULL;
// 	tmp = create_matrix(3, 3);
// 	i = 0;
// 	while (i < 3)
// 	{
// 		j = 0;
// 		while (j < 3)
// 		{
// 			tmp->matrix[i][j] = this->fwd_tfm->matrix[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	inverse_tmp = inverse(tmp);
// 	this->lineartfm = transpose(inverse_tmp);
// 	delete_matrix(tmp);
// 	delete_matrix(inverse_tmp);
// }

// t_vec3	*get_norm(t_object *this, t_vec3 *input_vec3)
// {
// 	t_matrix	*tmp;
// 	t_matrix	*resultmt;
// 	t_vec3	*result;

// 	resultmt = NULL;
// 	tmp = matrix(3, 1, (double []){input_vec3->x, input_vec3->y,
// 			input_vec3->z});
// 	resultmt = mt_multiplication(this->lineartfm, tmp);
// 	result = vector(resultmt->matrix[0][0], resultmt->matrix[1][0],
// 			resultmt->matrix[2][0]);
// 	delete_matrix(resultmt);
// 	delete_matrix(tmp);
// 	normalize(result);
// 	return (result);
// }
