#include "header.h"


int test_intersection(t_object *objects, t_ray *ray, t_info *info, int count)
{
	int i;
	float dist;
	float mindist;
	int validint;
	int intfound;
	t_info test;

	i = 0;
	mindist = 1e6;
	intfound = 0;
	validint = 0;
	while (i < count)
	{
		test.e = &objects[i];
		validint = objects[i].intersect(ray, &test);
		if (validint)
		{
			intfound = 1;
			dist = length(vec_sub(test.hitpoint, ray->point1));
			if (dist < mindist)
			{
				mindist = dist;
				info->e = test.e;
				info->hitpoint = test.hitpoint;
				info->localnormal = test.localnormal;
				info->tangent = test.tangent;
				info->uv = test.uv;
			}
		}
		i++;
	}
	return (intfound);
}

unsigned int	rand_pcg(unsigned int *rng_state)
{
	unsigned int seed;
	seed = (unsigned int)(*rng_state ^ (61)) ^ (*rng_state >> (16));
    seed *= (9);
    seed = seed ^ (seed >> 4);
    seed *= (0x27d4eb2d);
    seed = seed ^ (seed >> 15);
	*rng_state = seed;
	return (seed);
}

float	random_float(unsigned int *rng_state, float min, float max)
{
	return (min + (rand_pcg(rng_state) * (1.0 / UINT_MAX)
		) * (max - min));
}

float rand_float(unsigned int *rng_state)
{
	return (rand_pcg(rng_state) / 4294967295.0);
}


void raytrace(t_vars *vars)
{
	int x;
	int y;
	int intfound;
	t_ray ray;
	float xfact;
	float yfact;
	float normx;
	float normy;
	t_info info;
	t_vec3 color;
	vars->frames++;
	vars->rng_state = vars->frames;
	y = 0;
	xfact = 1.0 / ((float)(WIDTH) / 2.0);
	yfact = 1.0 / ((float)(HEIGHT) / 2.0);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			float xOffset = random_float(&vars->rng_state, -0.5, 0.5);
			float yOffset = random_float(&vars->rng_state, -0.5, 0.5);
			
			normx = ((float)(x + xOffset )* xfact) - 1.0;
			normy = ((float)(y + yOffset )* yfact) - 1.0;
			ray = generate_ray(normx, normy, &vars->cam);
			intfound = test_intersection(vars->objects, &ray, &info, vars->obj_count);
			if (intfound)
			{
				color = compute_color(vars, &info, &ray, 0);
				vars->buffer[y * WIDTH + x] = vec_add(vars->buffer[y * WIDTH + x], color);
				color = scale_vector(vars->buffer[y * WIDTH + x], 1.0 / vars->frames);
				set_pixel(x, y, &color, vars->image);
			}
			
			x++;
		}
		y++;
	}
	printf("frame : %d\n", vars->frames);
}
