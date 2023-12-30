/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 03:17:41 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/25 10:10:59 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_vec3	helper(t_matrix *m, t_matrix *other)
{
	t_matrix	*temp;
	t_matrix	*new;
	t_vec3		newnormal;
	t_vec3		tempdata;

	temp = m;
	m = inverse(m);
	delete_matrix(temp);
	temp = m;
	m = transpose(m);
	delete_matrix(temp);
	new = safe_matrix_multy(m, other);
	tempdata = new_vector(new->matrix[0][0],
			new->matrix[1][0], new->matrix[2][0]);
	newnormal = normalized(tempdata);
	delete_matrix(new);
	return (newnormal);
}

t_vec3	fixed_normal(t_matrix *forward, t_vec3 *hitpoint)
{
	int			i;
	int			j;
	t_matrix	*new;
	float		*values;
	t_matrix	*m;

	new = create_matrix(3, 1);
	values = (float []){hitpoint->x, hitpoint->y, hitpoint->z};
	fill_mt(new, values);
	m = create_matrix(3, 3);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			m->matrix[i][j] = forward->matrix[i][j];
			j++;
		}
		i++;
	}
	return (helper(m, new));
}
