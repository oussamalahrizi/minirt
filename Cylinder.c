#include "minirt.h"


static t_vec2 get_uvcoords(t_vec3 *intpoint, int cap)
{
	if (cap)
		return ((t_vec2) {intpoint->x, intpoint->y});
	double x = intpoint->x;
	double y = intpoint->y;
	double z = intpoint->z;
	double u = atan2(y , x) / M_PI;
	double v = z;
	return ((t_vec2) {u, v});
}

int test_cylinder(t_ray *ray, t_matrix **gtfm, t_vec3 *hitpoint, t_vec3 *localnormal, t_vec2 *uv)
{
	t_ray *back_ray = apply_transform(ray, gtfm, BACKWARD);
	t_vec3 *vhat = normalized(back_ray->direction);

	t_vec3 *p = back_ray->point1;

	double a = pow(vhat->x, 2.0) + pow(vhat->y, 2.0);
	double b = 2.0 * (p->x * vhat->x + p->y * vhat->y);
	double c = pow(p->x, 2.0) + pow(p->y, 2.0) - 1.0;

	double delta = sqrtf(pow(b, 2.0) - (4 * a * c));

	//test intersections
	t_vec3 *poi[4];
	double t[4];
	int t1valid, t2valid, t3valid, t4valid;
	t1valid = 0;
	t2valid = 0;
	t3valid = 0;
	t4valid = 0;
	if (delta > 0.0)
	{
		t[0] = (-b + delta) / (2.0 * a);
		t[1] = (-b - delta) / (2.0 * a);

		poi[0] = vec3_add (back_ray->point1, multiply_vec3_number(vhat, t[0]));
		poi[1] = vec3_add (back_ray->point1, multiply_vec3_number(vhat, t[1]));


		// check if these values are valid
		if (t[0] > 0.0 && fabs(poi[0]->z) < 1.0)
			t1valid = 1;
		else
		{
			t1valid = 0;
			t[0] = 100e6;
		}
		if (t[1] > 0.0 && fabs(poi[1]->z) < 1)
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
	// test the end caps
	if (close_enough(vhat->z))
	{
		t3valid = 0;
		t4valid = 0;
		t[2] = 100e6;
		t[3] = 100e6;
	}
	else
	{
		// compute the values of t;
		t[2] = (back_ray->point1->z - 1) / -vhat->z;
		t[3] = (back_ray->point1->z + 1) / -vhat->z;
		// compute the points of intersections
		poi[2] = vec3_add (back_ray->point1, multiply_vec3_number(vhat, t[2]));

		poi[3] = vec3_add (back_ray->point1, multiply_vec3_number(vhat, t[3]));
		// check if this is valid

		if (t[2] > 0.0 && sqrtf(pow(poi[2]->x, 2))
			+ pow(poi[2]->y, 2) < 1)
			t3valid = 1;
		else
		{
			t3valid = 0;
			t[2] = 100e6;
		}
		if (t[3] > 0.0 && sqrtf(pow(poi[3]->x, 2)
			+ pow(poi[3]->y, 2)) < 1.0)
				t4valid = 1;
		else
		{
			t4valid = 0;
			t[3] = 100e6;
		}
	}
	if (!t1valid && !t2valid && !t3valid && !t4valid)
		return (0);
	int minindex = 0;
	double minvalue = 10e6;
	int i = 0;
	while (i < 4)
	{
		if (t[i] < minvalue)
		{
			minvalue = t[i];
			minindex = i;
		}
		i++;
	}
	t_vec3 *validpoi = poi[minindex];
	// if minindex  is 0 or 1 then we have intersection with the cylinder itself
	if (minindex < 2)
	{
		// transform the point of intersection back to the original world
		t_vec3 *temp = apply_transform_vector(validpoi, FORWARD, gtfm);
		copy_vector_values(hitpoint, temp);
		free(temp);
		// compute the localnormal
		t_vec3 *orgnormal = new_vector3(0,0,0);
		t_vec3 *new_normal;
		// t_vec3 *localorigin = new_vector3(0,0,0);
		// t_vec3 *globalorigin = apply_transform_vector(localorigin, FORWARD, gtfm);
		orgnormal->x = validpoi->x;
		orgnormal->y = validpoi->y;
		// orgnormal->z = 0.0; no need for this cuz it's alreay 0
		new_normal = fixed_normal(gtfm[0], orgnormal);
		copy_vector_values(localnormal, new_normal);
		free(new_normal);
		// compute the uv for checker
		t_vec2 get_uv = get_uvcoords(validpoi, 0);
		uv->x = get_uv.x;
		uv->y = get_uv.y;
		return (1);
	}
	else
	{
		// point of intersection must be in the caps
		if (!close_enough(vhat->z))
		{
			// check if we are inside the disk
			if (sqrtf(pow(validpoi->x, 2) + pow(validpoi->y, 2)) < 1)
			{
				// transform the poi back to original world
				t_vec3 *temp = apply_transform_vector(validpoi, FORWARD, gtfm);
				copy_vector_values(hitpoint, temp);
				free(temp);
				// compute the localnormal
				// t_vec3 *localorigin = new_vector3(0,0,0);
				t_vec3 *normalvector = new_vector3(0, 0, 0 + validpoi->z);
				// t_vec3 *globalorigin = apply_transform_vector(localorigin, FORWARD, gtfm);
				// temp = normalized(vec3_sub(apply_transform_vector(normalvector, FORWARD, gtfm), globalorigin));
				temp = fixed_normal(gtfm[0], normalvector);
				copy_vector_values(localnormal, temp);
				free(temp);
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