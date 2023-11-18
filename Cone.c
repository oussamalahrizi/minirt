#include "minirt.h"

int test_cone(t_ray *ray, t_matrix **gtfm, t_vec3 *hitpoint, t_vec3 *localnormal)
{
	t_ray *back_ray = apply_transform(ray, gtfm, BACKWARD);
	t_vec3 *vhat = normalized(back_ray->direction);

	t_vec3 *p = back_ray->point1;

	double a = pow(vhat->x, 2) + pow(vhat->y, 2) - pow(vhat->z, 2);
	double b = 2 * (p->x * vhat->x + p->y * vhat->y - p->z * vhat->z);
	double c = pow(p->x, 2) + pow(p->y, 2) - pow(p->z, 2);

	double delta = sqrtf(pow(b, 2) - (4 * a * c));

	t_vec3 *poi[3] = {NULL, NULL, NULL};
	double t[3];
	int t1valid, t2valid, t3valid;
	t1valid = 0;
	t2valid = 0;
	t3valid = 0;

	if (delta > 0.0)
	{
		t[0] = (-b + delta) / (2 * a);
		t[1] = (-b - delta) / (2 * a);
	
		poi[0] = vec3_add(back_ray->point1, multiply_vec3_number(vhat, t[0]));
		poi[1] = vec3_add(back_ray->point1, multiply_vec3_number(vhat, t[1]));

		if (t[0] > 0 && poi[0]->z > 0.0 && poi[0]->z < 1.0 )
			t1valid = 1;
		else
		{
			t1valid = 0;
			t[0] = 100e6;
		}

		if (t[1] > 0 && poi[1]->z > 0.0 && poi[1]->z < 1.0)
			t2valid = 1;
		else
		{
			t2valid = 0;
			t[1] = 100e6;
		}
	}
	else
	{
		t1valid = 0;
		t2valid = 0;
		t[0] = 100e6;
		t[1] = 100e6;
	}

	// test for end cap
	if (close_enough(vhat->z))
	{
		t3valid = 0;
		t[2] = 100e6;
	}
	else
	{
		t[2] = (back_ray->point1->z - 1) / -vhat->z;
		poi[2] = vec3_add(back_ray->point1, multiply_vec3_number(vhat, t[2]));

		if (t[2] > 0 && sqrtf( pow(poi[2]->x, 2) + pow(poi[2]->y, 2) ) < 1.0)
			t3valid = 1;
		else
		{
			t3valid = 0;
			t[2] = 100e6;
		}
	}
	if (!t1valid && !t2valid && !t3valid)
		return (0);


	int minindex = 0;
	double minvalue = 10e6;
	int i = 0;
	while (i < 3)
	{
		if (t[i] < minvalue)
		{
			minvalue = t[i];
			minindex = i;
		}
		i++;
	}

	t_vec3 *validpoi = poi[minindex];

	if (minindex < 2)
	{
		t_vec3 *temp = apply_transform_vector(validpoi, FORWARD, gtfm);
		copy_vector_values(hitpoint, temp);
		free(temp);
	
		t_vec3 *orgnormal = new_vector3(0,0,0);
		t_vec3 *newnormal;
		// t_vec3 *localorigin = new_vector3 (0,0,0);
		// t_vec3 *globalorigin = apply_transform_vector(localorigin, FORWARD, gtfm);
		orgnormal->x = validpoi->x;
		orgnormal->y = validpoi->y;
		orgnormal->z = validpoi->z;

		orgnormal = cross(orgnormal, cross(orgnormal, new_vector3(0, 0, 1)));
		orgnormal = normalized(orgnormal);

		double *values = (double []){orgnormal->x, orgnormal->y, orgnormal->z};
		t_matrix *new = create_matrix(3, 1);
		fill_mt(new, values);

		t_matrix *m = create_matrix(3, 3);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m->matrix[i][j] = gtfm[1]->matrix[j][i];
		

		new = mt_multiplication(m, new);
		newnormal = normalized(new_vector3(new->matrix[0][0], new->matrix[1][0], new->matrix[2][0]));

		// newnormal = normalized(vec3_sub(apply_transform_vector(orgnormal, FORWARD, gtfm), globalorigin));
		copy_vector_values(localnormal, newnormal);
		free(newnormal);
		return (1);
	}
	else
	{
		if (!close_enough(vhat->z))
		{
			if (sqrtf( pow(validpoi->y, 2) + pow(validpoi->x, 2) ) < 1.0)
			{
				t_vec3 *temp = apply_transform_vector(validpoi, FORWARD, gtfm);
				copy_vector_values(hitpoint, temp);
				free(temp);


				t_vec3 *localorigin = new_vector3 (0,0,0);
				t_vec3 *globalorigin = apply_transform_vector(localorigin, FORWARD, gtfm);
				t_vec3 *normalvector = new_vector3 (0,0, 1);
				temp = normalized(vec3_sub(apply_transform_vector(normalvector, FORWARD, gtfm), globalorigin));
				copy_vector_values(localnormal, temp);
				return (1);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	return (0);
}