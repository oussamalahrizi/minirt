/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:04:10 by olahrizi          #+#    #+#             */
/*   Updated: 2023/11/17 00:46:26 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double length2(t_vec3 *vector)
{
	return ((vector->x * vector->x) + (vector->y * vector->y) + (vector->z * vector->z));
}

double length(t_vec3 *vector)
{
	return (sqrtf(length2(vector)));
}

double normalize(t_vec3 *vector)
{
	double l;

	l = length(vector);
	if (l != 0)
	{
		vector->x /= l;
		vector->y /= l;
		vector->z /= l;
	}
	return (l);
}

t_vec3 *normalized(t_vec3 *vector)
{
	t_vec3 *new_v;

	new_v = malloc(sizeof(t_vec3));
	new_v->x = vector->x;
	new_v->y = vector->y;
	new_v->z = vector->z;
	normalize(new_v);
	return (new_v);
}

t_vec3 *cross(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3 *new_v;

	new_v = malloc(sizeof(t_vec3));
	new_v->x = (v1->y * v2->z) - (v1->z * v2->y);
	new_v->y = (v1->z * v2->x) - (v1->x * v2->z);
	new_v->z = (v1->x * v2->y) - (v1->y * v2->x);
	return (new_v);
}

// x, y, z a , b c == xa + yb + zc == cos theta
double dot_product(t_vec3 *v1, t_vec3 *v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

t_vec3 *new_vector3(double x, double y, double z)
{
	t_vec3 *new;

	new = malloc(sizeof(t_vec3));
	new->x = x;
	new->y = y;
	new->z = z;
	return new;
}

t_vec3 *vec3_sub(t_vec3 *vec1, t_vec3 *vec2)
{
	t_vec3 *result;

	result = malloc(sizeof(t_vec3));
	result->x = vec1->x - vec2->x;
	result->y = vec1->y - vec2->y;
	result->z = vec1->z - vec2->z;
	return (result);
}

t_vec3 *vec3_add(t_vec3 *vec1, t_vec3 *vec2)
{
	t_vec3 *result;

	result = malloc(sizeof(t_vec3));
	result->x = vec1->x + vec2->x;
	result->y = vec1->y + vec2->y;
	result->z = vec1->z + vec2->z;
	return (result);
}

t_vec3 *vec3_multiply(t_vec3 *vec1, t_vec3 *vec2)
{
	t_vec3 *result;

	result = malloc(sizeof(t_vec3));
	result->x = vec1->x * vec2->x;
	result->y = vec1->y * vec2->y;
	result->z = vec1->z * vec2->z;
	return (result);
}

t_vec3 *vec3_div_number(t_vec3 *vec1, int n)
{
	t_vec3 *result;

	result = malloc(sizeof(t_vec3));
	result->x = vec1->x / n;
	result->y = vec1->y / n;
	result->z = vec1->z / n;
	return (result);
}

t_vec3 *negative_vec3(t_vec3 *vector)
{
	t_vec3 *neg;

	neg = malloc(sizeof(t_vec3));
	neg->x = -vector->x;
	neg->y = -vector->y;
	neg->z = -vector->z;
	return (neg);
}

double max(double v1, double v2)
{
	if (v1 > v2)
		return (v1);
	return (v2);
}

t_vec3 *multiply_vec3_number(t_vec3 *vector, double number)
{
	t_vec3 *new;

	new = malloc(sizeof(t_vec3));
	new->x = vector->x *number;
	new->y = vector->y *number;
	new->z = vector->z *number;
	return (new);
}

void print_vector(t_vec3 *vec)
{
	printf("x : %f\t", vec->x);
	printf("y : %f\t", vec->y);
	printf("z : %f\n", vec->z);
}

t_vec3 *copy_vector(t_vec3 *vec)
{
	return (new_vector3(vec->x, vec->y, vec->z));
}

void copy_vector_values(t_vec3 *vec1, t_vec3 *vec2)
{
	vec1->x = vec2->x;
	vec1->y = vec2->y;
	vec1->z = vec2->z;
}

t_vec3 *reflect(t_vec3 *d, t_vec3 *normal)
{
	return normalized(vec3_sub(d, multiply_vec3_number(normal, 2.0f * dot_product(d, normal))));
}