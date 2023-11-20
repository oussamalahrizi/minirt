#include "minirt.h"

static t_vec2 get_uvcoords(t_vec3 *intpoint, int cap)
{
	if (cap)
		return ((t_vec2) {intpoint->x, intpoint->y});
	double x = intpoint->x;
	double y = intpoint->y;
	double z = intpoint->z;
	double u = atan2(y, x) / M_PI;
	double v = (z * 2) + 1;

	return ((t_vec2) {u, v});
}

int test_cone(t_ray *ray, t_matrix **gtfm, t_vec3 *hitpoint, t_vec3 *localnormal, t_vec2 *uv)
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
	
		t_vec3 *newnormal;
		newnormal = fixed_normal(gtfm[0], validpoi);
		copy_vector_values(localnormal, newnormal);
		free(newnormal);
		t_vec2 get_uv = get_uvcoords(validpoi, 0);
		uv->x = get_uv.x;
		uv->y = get_uv.y;
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
				t_vec3 *newnormal = normalized(vec3_sub(apply_transform_vector(normalvector, FORWARD, gtfm), globalorigin));
				newnormal = fixed_normal(gtfm[0], hitpoint);
				copy_vector_values(localnormal, newnormal);
				free(newnormal);
				t_vec2 get_uv = get_uvcoords(validpoi, 1);
				uv->x = get_uv.x;
				uv->y = get_uv.y;
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