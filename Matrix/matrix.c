/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/11/15 04:01:53 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minirt.h"

void	set_to_indentity(t_matrix *mt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mt->rows)
	{
		j = 0;
		while (j < mt->cols)
		{
			if (i == j)
				mt->matrix[i][j] = 1;
			j++;
		}
		i++;
	}
}

void	print_matrix(t_matrix *matrix)
{
	int	i;
	int	j;

	if (!matrix)
		return ;
	i = 0;
	printf("[ \n");
	while (i < matrix->rows)
	{
		j = 0;
		printf("\t[ ");
		while (j < matrix->cols)
		{
			printf(" %f  %c", matrix->matrix[i][j], ' ');
			j++;
		}
		printf("],\n");
		i++;
	}
	printf("]\n");
}

t_matrix	*from_t_vectoro_matrix(t_vec3 vt)
{
	t_matrix	*new_mt;

	new_mt = create_matrix(1, 3);
	new_mt->matrix[0][0] = vt.x;
	new_mt->matrix[0][1] = vt.y;
	new_mt->matrix[0][2] = vt.z;
	return (new_mt);
}

t_matrix	*transpose(t_matrix *mt)
{
	t_matrix	*new_mt;
	int			r_i;
	int			c_i;

	if (!mt)
		return (NULL);
	new_mt = create_matrix(mt->cols, mt->rows);
	r_i = 0;
	while (r_i < mt->rows)
	{
		c_i = 0;
		while (c_i < mt->cols)
		{
			new_mt->matrix[c_i][r_i] = mt->matrix[r_i][c_i];
			c_i++;
		}
		r_i++;
	}
	return (new_mt);
}

void	delete_matrix(t_matrix *this)
{
	int	row_index;

	row_index = 0;
	if (this)
	{
		if (this->matrix)
		{
			while (row_index < this->rows)
			{
				if (this->matrix[row_index])
					free(this->matrix[row_index]);
				row_index++;
			}
			free(this->matrix);
		}
		free(this);
	}
}
