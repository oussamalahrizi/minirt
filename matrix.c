/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:08:18 by olahrizi          #+#    #+#             */
/*   Updated: 2023/07/28 02:36:02 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_matrix(t_matrix *m);

t_matrix *new_matrix(int r, int c)
{
	t_matrix *new;
	int x;

	new = malloc(sizeof(t_matrix));
	new->rows = r;
	new->cols = c;
	new->data = (double **)malloc(sizeof(double *) * new->rows);
	x = 0;
	while (x < new->rows)
	{
		new->data[x] = (double *)malloc(sizeof(double) * new->cols);
		x++;
	}
	return (new);
}

t_matrix *identity_matrix(int r)
{
	t_matrix *new;

	new = new_matrix(r, r);
	int y;
	int x;
	x = 0;
	while (x < new->cols)
	{
		y = 0;
		while (y < new->rows)
		{
			if (y == x)
				new->data[y][x] = 1.0;
			else
				new->data[y][x] = 0.0;
			y++;
		}
		x++;
	}
	return (new);
}

void free_matrix(t_matrix *m)
{
	int x = 0;
	while (x < m->rows)
	{
		free(m->data[x]);
		x++;
	}
	free(m->data);
	free(m);
}

void print_matrix(t_matrix *m)
{
	int r;
	int c;

	r = 0;
	while (r < m->rows)
	{
		c = 0;
		while (c < m->cols)
		{
			printf("%f\t", m->data[r][c]);
			c++;
		}
		printf("\n");
		r++;
	}
}

void	copy_clmn(double *clm1, double *clm2, int column, int size)
{
	int	j;
	int	fci;

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

t_matrix	*submatrix(t_matrix *mt, int row, int column)
{
	int			i;
	int			fri;
	t_matrix	*sub;

	if (mt->rows <= 1 || mt->cols <= 1)
		return (mt);
	sub = new_matrix(mt->rows - 1, mt->rows - 1);
	i = 0;
	fri = 0;
	while (i < mt->rows)
	{
		if (i == row)
		{
			i++;
			continue ;
		}
		copy_clmn(sub->data[fri], mt->data[i], column, mt->cols);
		fri++;
		i++;
	}
	return (sub);
}

double	minor(t_matrix *mt, int row, int column)
{
	t_matrix	*sub;
	double		m_determinant;

	sub = submatrix(mt, row, column);
	m_determinant = determinant(sub);
	free_matrix(sub);
	return (m_determinant);
}

double	cofactor(t_matrix *mt, int row, int column)
{
	int	sign;

	sign = 1;
	if ((row + column) % 2 != 0)
		sign = -1;
	return (sign * minor(mt, row, column));
}

double	determinant(t_matrix *mt)
{
	double	d;
	int		column_index;

	column_index = 0;
	d = 0;
	if (mt->cols != mt->rows)
		return (0);
	if (mt->cols == 2 || mt->rows == 2)
		d = (mt->data[0][0] * mt->data[1][1]) - (mt->data[0][1]
				* mt->data[1][0]);
	else
	{
		while (column_index < mt->cols)
		{
			d += mt->data[0][column_index] * cofactor(mt, 0, column_index);
			column_index++;
		}
	}
	return (d);
}

t_matrix	*inverse(t_matrix *mt)
{
	t_matrix	*m_inverse;
	int			row_index;
	int			col_index;
	double		c;
	double		dt;

	dt = determinant(mt);
	if (dt == 0)
		return (NULL);
	m_inverse = new_matrix(mt->rows, mt->cols);
	row_index = 0;
	while (row_index < mt->rows)
	{
		col_index = 0;
		while (col_index < mt->cols)
		{
			c = cofactor(mt, row_index, col_index);
			m_inverse->data[col_index][row_index] = (c / dt);
			col_index++;
		}
		row_index++;
	}
	return (m_inverse);
}

t_matrix *matrix_multiply(const t_matrix *a, const t_matrix *b)
{
    if (a->cols != b->rows)
	{
        fprintf(stderr, "Matrix dimensions are incompatible for multiplication.\n");
        return (NULL);
    }

    t_matrix *result = new_matrix(a->rows, b->cols);

	int i = 0;
	int j;
	int k ;
	while (i < a->rows)
	{
		j = 0;
		while (j < b->cols)
		{
			result->data[i][j] = 0.0;
			k = 0;
			while (k < a->cols)
			{
				result->data[i][j] += a->data[i][k] * b->data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
    return result;
}