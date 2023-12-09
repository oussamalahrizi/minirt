#include "header.h"


int test_intersection(t_object *objects, t_ray *ray, t_info *info)
{
	int i;
	float dist;
	float mindist;
	int validint;
	int intfound;
	t_info test;
	t_vec3 t;

	i = 0;
	mindist = 1e6;
	intfound = 0;
	validint = 0;
	while (i < 3)
	{
		test.e = &objects[i];
		validint = objects[i].intersect(ray, &test);
		if (validint)
		{
			intfound = 1;
			t = vec_sub(&test.hitpoint, &ray->point1);
			dist = normalize(&t);
			if (dist < mindist)
			{
				mindist = dist;
				info->e = test.e;
				info->hitpoint = test.hitpoint;
				info->localnormal = test.localnormal;
			}
		}
		i++;
	}
	return (intfound);
}

unsigned int	rand_pcg(unsigned int *rng_state)
{
	unsigned int		state;
	unsigned int		word;

	state = *rng_state;
	*rng_state = state * 747796405u + 2891336453u;
	word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return ((word >> 22u) ^ word);
}

float	random_float(unsigned int *rng_state, float min, float max)
{
	return (min + (rand_pcg(rng_state) * (1.0 / UINT_MAX)
		) * (max - min));
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
	static int frame;
	static unsigned int rng_state;
	rng_state += frame >> 16;
	frame++;
	y = 0;
	xfact = 1.0 / ((float)(WIDTH) / 2.0);
	yfact = 1.0 / ((float)(HEIGHT) / 2.0);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			float xOffset = random_float(&rng_state, -0.5, 0.5);
			float yOffset = random_float(&rng_state, -0.5, 0.5);
			normx = ((float)(x + xOffset)* xfact) - 1.0;
			normy = ((float)(y + yOffset)* yfact) - 1.0;
			ray = generate_ray(normx, normy, &vars->cam);
			intfound = test_intersection(vars->objects, &ray, &info);
			if (intfound)
			{
				color = diffuse_color(vars->objects, &info, vars->lights, &info.e->base_color);
				vars->buffer[y * WIDTH + x] = vec_add(&vars->buffer[y * WIDTH + x], &color);
				color = scale_vector(&vars->buffer[y * WIDTH + x], 1.0 / frame);
				set_pixel(x, y, &color, vars->image);
			}
			x++;
		}
		y++;
	}
	printf("frame : %d\n", frame);
}