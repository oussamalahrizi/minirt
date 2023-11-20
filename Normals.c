#include "minirt.h"

t_vec3 *fixed_normal(t_matrix *forward, t_vec3 *hitpoint) /// not necessary hitpoint on all objects
{
	t_vec3 *newnormal;
	

	t_matrix *new;
	new = create_matrix(3, 1);
	double *values = (double []){hitpoint->x, hitpoint->y, hitpoint->z};
	fill_mt(new, values);

	t_matrix *m = create_matrix(3, 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m->matrix[i][j] = forward->matrix[i][j];
	t_matrix *temp;
	temp = m;
	m = inverse(m);
	delete_matrix(temp);
	temp = m;
	m = transpose(m);
	delete_matrix(temp);
	new = mt_multiplication(m, new);
	t_vec3 *tempdata;
	tempdata = new_vector3(new->matrix[0][0], new->matrix[1][0], new->matrix[2][0]);
	newnormal = normalized(tempdata);
	free(tempdata);
	delete_matrix(m);
	delete_matrix(new);
	return (newnormal);
}