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

	new = malloc(sizeof(t_matrix));
	new->rows = r;
	new->cols = r;
	new->data = malloc(sizeof(double *) * new->cols);
	int x = 0;
	while (x < new->cols)
	{
		new->data[x] = malloc(sizeof(double) * new->rows);
		x++;
	}
	int y;

	x = 0;
	while (x < new->cols)
	{
		y = 0;
		while (y < new->rows)
		{
			if (y == x)
				new->data[y][x] = 1;
			else
				new->data[y][x] = 0;
			y++;
		}
		x++;
	}
	return (new);
}

t_matrix *submatrix(t_matrix *m1, int ex_r, int ex_c)
{
	int r;
	int c;
	int r_sub;
	int c_sub;
	t_matrix *new;

	new = new_matrix(m1->rows - 1, m1->cols - 1);
	r_sub = 0;
	r = 0;
	while (r < m1->rows)
	{
		if (r == ex_r)
		{
			r++;
			continue;
		}
		c = 0;
		c_sub = 0;
		while (c < m1->cols)
		{
			if (c == ex_c)
			{
				c++;
				continue;
			}
			new->data[r_sub][c_sub] = m1->data[r][c];
			c++;
			c_sub++;
		}
		r++;
		r_sub++;
	}
	return (new);
}

double determinant(t_matrix *m1)
{
	int r;
	int c;
	int sign;
	double det;
	t_matrix *sub;

	if (m1->rows == 1)
		return (m1->data[0][0]);
	sign = 1;
	det = 0.0;
	c = 0;
	while (c < m1->cols)
	{
		sub = submatrix(m1, 0, c);
		det += sign * m1->data[0][c] * determinant(sub);
		sign *= -1;
		free(sub);
		c++;
	}
	return (det);
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

t_matrix *transpose_matrix(t_matrix *m1)
{
	t_matrix *new;
	int r;
	int c;

	new = new_matrix(m1->cols, m1->rows);
	r = 0;
	while (r < m1->rows)
	{
		c = 0;
		while (c < m1->cols)
		{
			new->data[c][r] = m1->data[r][c];
			c++;
		}
		r++;
	}
	return (new);
}

t_matrix *inverse_matrix(t_matrix *m1)
{
	double det;
	int r;
	int c;

	if (m1->rows != m1->cols)
		return (NULL);
	det = determinant(m1);
	if (!det)
		return (NULL);
	r = 0;
	while (r < m1->rows)
	{
		c = 0;
		
	}
	
}

int main()
{
	t_matrix *m1 = new_matrix(2, 2);
	m1->data[0][0] = 1;
	m1->data[0][1] = 2;
	m1->data[1][0] = 3;
	m1->data[1][1] = 4;
	print_matrix(m1);
	printf("transpose\n");
	print_matrix(transpose_matrix(m1));
}