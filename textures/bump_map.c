/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:14:38 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/11 06:16:47 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

t_vec3 bump_normal(t_info *info)
{
	float h;
	float hr;
	float hu;
	t_vec3 bump_normal;
	t_vec3 bitangent;
	float u, v;

	u = info->uv.u;
	v = info->uv.v;
	if (info->e->type == PLANE)
	{
		u *= 0.5;
		v *= 0.5;
	}
	h = get_color_texture(info->e->imgnormal, u, v).z;
	hr = get_color_texture(info->e->imgnormal, u + 1.0f / info->e->imgnormal.width, v).z;
	hu = get_color_texture(info->e->imgnormal, u, v + 1.0f / info->e->imgnormal.height).z;
	info->tangent = normalized(info->tangent);
	bitangent = normalized(cross(info->localnormal, info->tangent));
	bump_normal = normalized(cross(
		(t_vec3) {1, 0, (hr - h ) * 10},
		(t_vec3) {0, 1, (hu - h) * 10}
	));
	t_matrix *tbn = create_matrix(3, 3);
	float *values = (float []) {info->tangent.x, bitangent.x, info->localnormal.x,
								info->tangent.y, bitangent.y, info->localnormal.y,
								info->tangent.z, bitangent.z, info->localnormal.z};
	fill_mt(tbn, values);
	t_matrix *tempdata = create_matrix(3, 1);
	values = (float []) {bump_normal.x, bump_normal.y, bump_normal.z};
	fill_mt(tempdata, values);
	t_matrix *result = safe_matrix_multy(tbn, tempdata);
	t_vec3 output = normalized(new_vector(result->matrix[0][0], result->matrix[1][0], result->matrix[2][0]));
	delete_matrix(result);
	return(output);
}

t_vec3 get_color_texture(t_data image, float u, float v)
{
	int width;
	int height;
	int x;
	int y;
	int pixel_index;
	char *dst;
	t_vec3 color;
	unsigned int final;

	width = image.width;
	height = image.height;
	u -= floorf(u);
	v -= floorf(v);
	x = min((u * width), width - 1);
	y = min((1 - v) * height, height - 1);
	pixel_index = y * image.line_length + x * (image.bits_per_pixel / 8);
	dst = image.addr + pixel_index;
	final = *((unsigned int *) dst);
	color = new_vector((final >> 16 & 255)  / 255.0f, (final >> 8 & 255) / 255.0f, (final & 255) / 255.0f);
	return (color);	
}