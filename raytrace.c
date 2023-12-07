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
	mindist = 100e6;
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

void raytrace(t_image *image, t_light *lights, t_object *objects, t_camera *cam)
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

	y = 0;
	xfact = 1.0f / ((float)(WIDTH) / 2.0f);
	yfact = 1.0f / ((float)(HEIGHT) / 2.0f);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			normx =  ((float)(x)* xfact ) - 1.0f;
			normy =  ((float)(y)* yfact ) - 1.0f;
			ray = generate_ray(normx, normy, cam);
			intfound = test_intersection(objects, &ray, &info);
			if (intfound)
			{
				color = diffuse_color(objects, &info, lights, &info.e->base_color);
				set_pixel(x, y, &color, image);
			}
			x++;
		}
		y++;
	}
}