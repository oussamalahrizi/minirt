/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:10:02 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/30 21:52:13 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	handle_cy(t_object *obj)
{
	obj->d_normal = normalized(obj->d_normal);
	obj->rotation = get_rotation_vector(obj->d_normal);
	obj->gtfm = set_transform(&obj->translation, &obj->rotation, &obj->scale);
	obj->intersect = test_cylinder;
}

void	prepare_objects(t_vars *vars)
{
	int			i;
	t_object	*obj;

	i = 0;
	obj = vars->objects;
	while (i < vars->obj_count)
	{
		if (obj[i].type == SPHERE)
		{
			obj[i].rotation = (t_vec3){0, 0, 0};
			obj[i].scale = (t_vec3){obj[i].radius,
				obj[i].radius, obj[i].radius};
			obj[i].gtfm = set_transform(&obj[i].translation,
					&obj[i].rotation, &obj[i].scale);
			obj[i].intersect = test_sphere;
		}
		else if (obj[i].type == CYLINDER)
			handle_cy(&obj[i]);
		else if (obj[i].type == PLANE)
		{
			obj[i].d_normal = normalized(obj[i].d_normal);
			obj[i].intersect = test_plane;
		}
		i++;
	}
}
