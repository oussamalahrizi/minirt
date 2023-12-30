/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 10:07:48 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/25 10:10:31 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_vec3	reflect(t_vec3 d, t_vec3 normal)
{
	return (normalized(vec_sub(d,
				scale_vector(normal, 2.0f * dot_product(d, normal)))));
}

t_vec3	get_rotation_vector(t_vec3 normal)
{
	float	x;
	float	y;
	float	z;

	x = atan2(normal.y, -normal.z);
	y = atan2(-normal.x, sqrtf(square(normal.y) + square(normal.z)));
	z = atan2(normal.x, normal.y);
	return (new_vector(x, y, z));
}

t_vec3	get_up_vector(t_vec3 forward)
{
	t_vec3	up;
	float	d;

	up = new_vector(0, 1, 0);
	d = dot_product(up, forward);
	if (d > 0.9)
		up = new_vector(0, 0, 1);
	else if (d < -0.9)
		up = new_vector(0, 0, -1);
	return (up);
}

void	print_vector(t_vec3 a)
{
	printf("%f %f %f\n", a.x, a.y, a.z);
}
