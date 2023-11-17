/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:21:31 by aaitouna          #+#    #+#             */
/*   Updated: 2023/11/15 04:01:44 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"



t_matrix	*matrix(int rows, int cols, double *values)
{
	t_matrix	*mt;

	mt = create_matrix(rows, cols);
	fill_mt(mt, values);
	return (mt);
}

void	fill_mt(t_matrix *mt, double *values)
{
	int	k;
	int	i;
	int	j;

	k = 0;
	i = 0;
	while (i < mt->rows)
	{
		j = 0;
		while (j < mt->cols)
		{
			mt->matrix[i][j] = values[k++];
			j++;
		}
		i++;
	}
}

double	*create_cols(int c)
{
	int		i;
	double	*new_col;

	i = 0;
	new_col = malloc(c * sizeof(double));
	while (i < c)
		new_col[i++] = .0;
	return (new_col);
}

t_matrix	*create_matrix(int rows, int cols)
{
	t_matrix	*new_mt;
	int			i;
	double		**mt;

	if (rows <= 0 || cols <= 0)
		return (NULL);
	new_mt = malloc(sizeof(t_matrix));
	i = 0;
	new_mt->rows = rows;
	new_mt->cols = cols;
	mt = malloc(sizeof(double *) * rows);
	while (i < rows)
		mt[i++] = create_cols(cols);
	new_mt->matrix = mt;
	return (new_mt);
}
