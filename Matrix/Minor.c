/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:42:23 by aaitouna          #+#    #+#             */
/*   Updated: 2023/11/15 04:01:56 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minirt.h"

void copy_clmn(double *clm1, double *clm2, int column, int size)
{
	int j;
	int fci;

	j = 0;
	fci = 0;
	while (j < size)
	{
		if (j != column)
		{
			clm1[fci] = clm2[j];
			fci++;
		}
		j++;
	}
}

t_matrix *submatrix(t_matrix *mt, int row, int column)
{
	int i;
	int fri;
	t_matrix *new_matrix;

	if (mt->rows <= 1 || mt->cols <= 1)
		return (mt);
	new_matrix = create_matrix(mt->rows - 1, mt->rows - 1);
	i = 0;
	fri = 0;
	while (i < mt->rows)
	{
		if (i == row)
		{
			i++;
			continue;
		}
		copy_clmn(new_matrix->matrix[fri], mt->matrix[i], column, mt->cols);
		fri++;
		i++;
	}
	return (new_matrix);
}

double minor(t_matrix *mt, int row, int column)
{
	t_matrix *sub;
	double m_determinant;

	sub = submatrix(mt, row, column);
	m_determinant = determinant(sub);
	delete_matrix(sub);
	return (m_determinant);
}
