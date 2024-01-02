#include "../header.h"


static int cast_ray(t_ray *lightray, t_vars *vars, float lighdist, t_info *info)
{
	int i;
	int validint;
	float dist;
	t_info test;

	i = 0;
	validint = 0;
	while (i < vars->obj_count)
	{
		if (info->e == &vars->objects[i])
		{
			i++;
			continue;
		}
		test.e = &vars->objects[i];
		validint = vars->objects[i].intersect(lightray, &test);
		if (validint)
		{
			dist = length(vec_sub(test.hitpoint, info->hitpoint));
			if (dist > lighdist)
				validint = 0;
		}
		if (validint)
			break;
		i++;
	}
	return (validint);
}

int compute_illimunation(t_light *light, t_info *info, t_vars *vars, float *intensity)
{
	t_vec3 lighdir;
	t_ray lightray;
	float lighdist;
	int validint;

	lighdir = normalized(vec_sub(light->position, info->hitpoint));
	lighdist = length(vec_sub(light->position, info->hitpoint));
	lightray = new_ray(info->hitpoint, vec_add(info->hitpoint, lighdir));
	validint = cast_ray(&lightray, vars, lighdist, info);
	if (!validint)
	{
		*intensity = light->intensity * fmax(dot_product(lighdir, info->localnormal), 0.0);
		return (1);
	}
	else
	{
		*intensity = 0.0f;
		return (0);
	}
	return (0);
}

t_vec3 diffuse_color(t_vars *vars, t_info *info, t_vec3 base_color)
{
	int i;
	float red;
	float green;
	float blue;
	int validillum;
	int illumfound;
	// t_vec3 ambient;
	t_vec3 diff_color;
	float intensity;

	illumfound = 0;
	red = 0.0;
	green = 0.0;
	blue = 0.0;
	diff_color = new_vector(red, green, blue);
	
	i = 0;
	intensity = 0;
	while (i < 1)
	{
		validillum = compute_illimunation(&vars->lights[i], info, vars, &intensity);
		if (validillum)
		{
			illumfound = 1;
			red += vars->lights[i].color.x * intensity;
			green += vars->lights[i].color.y * intensity;
			blue += vars->lights[i].color.z * intensity;
		}
		i++;
	}
	if (illumfound)
	{
		diff_color = new_vector(red * base_color.x,
								green * base_color.y,
			 					blue * base_color.z);
	}
	return (diff_color);
}
