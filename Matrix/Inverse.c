/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:16:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/11/15 04:01:50 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/**
 * 1: |a b|
 * 2: |c d|
 * det = ad - bc;
 */
double	determinant(t_matrix *mt)
{
	double	d;
	int		column_index;

	column_index = 0;
	d = 0;
	if (mt->cols != mt->rows)
		return (0);
	if (mt->cols == 2 || mt->rows == 2)
		d = (mt->matrix[0][0] * mt->matrix[1][1]) - (mt->matrix[0][1]
				* mt->matrix[1][0]);
	else
	{
		while (column_index < mt->cols)
		{
			d += mt->matrix[0][column_index] * cofactor(mt, 0, column_index);
			column_index++;
		}
	}
	return (d);
}

double	cofactor(t_matrix *mt, int row, int column)
{
	int	sign;

	sign = 1;
	if ((row + column) % 2 != 0)
		sign = -1;
	return (sign * minor(mt, row, column));
}

t_matrix	*inverse(t_matrix *mt)
{
	t_matrix	*m_invers;
	int			row_index;
	int			col_index;
	double		c;
	double		dt;

	dt = determinant(mt);
	if (dt == 0)
		return (NULL);
	m_invers = create_matrix(mt->rows, mt->cols);
	row_index = 0;
	while (row_index < mt->rows)
	{
		col_index = 0;
		while (col_index < mt->cols)
		{
			c = cofactor(mt, row_index, col_index);
			m_invers->matrix[col_index][row_index] = (c / dt);
			col_index++;
		}
		row_index++;
	}
	return (m_invers);
}
