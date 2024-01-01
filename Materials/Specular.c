/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 06:21:34 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/26 12:49:49 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int cast_ray(t_object *objects, t_ray cast_ray)
{
	t_info test;
	int i;
	int validint;
	i = 0;
	while (i < OBJ_COUNT)
	{
		test.e = &objects[i];
		validint = objects[i].intersect(&cast_ray, &test);
		if (validint)
			return (1);
		i++;
	}
	return (0);
}

float get_intensity(t_vec3 light_ray_dir, t_vec3 normal, t_vec3 cam_dir, t_object *e)
{
	t_vec3 v;
	t_vec3 ref_v;
	float prod;

	v = normalized(cam_dir);
	ref_v = reflect(normalized(light_ray_dir), normal);
	prod = dot_product(ref_v, v);
	if (prod > 0.0)
		return (e->reflectivity * powf(prod, e->shininess));
	return (0);
}

t_vec3 specular_highlight(t_object *objects, t_info *info, t_light *lights, t_ray *camera_ray)
{
	t_vec3 spc_color;
	float red;	
	float green;	
	float blue;
	int j;
	t_vec3 lighdir;
	t_vec3 start;
	t_vec3 point2;
	t_ray lightray;
	float intensity;
	int validint;

	red = .0f;	
	green = .0f;	
	blue = .0f;
	j = 0;
	intensity = 0.0f;
	while (j < 1)
	{
		lighdir = normalized(vec_sub(lights[j].position, info->hitpoint));
		start = vec_add(info->hitpoint, scale_vector(lighdir, 0.0001f));
		point2 = vec_add(start, lighdir);
		lightray = new_ray(start, point2);
		validint = cast_ray(objects, lightray);
		if (!validint)
			intensity = get_intensity(lightray.dir, info->localnormal, camera_ray->dir, info->e);
		red += lights[j].color.x * intensity * lights[j].intensity;
		green += lights[j].color.y * intensity * lights[j].intensity;
		blue += lights[j].color.z * intensity * lights[j].intensity;
		j++;
	};
	spc_color = new_vector(red, green, blue);
	return (spc_color);
}