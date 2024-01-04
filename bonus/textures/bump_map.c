/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:14:38 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 06:28:38 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norm_text.h"

int	min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

static void	helper(t_bump *local)
{
	local->tempdata = create_matrix(3, 1);
	local->values = (float []){local->bump_normal.x, local->bump_normal.y,
		local->bump_normal.z};
	fill_mt(local->tempdata, local->values);
	local->result = safe_matrix_multy(local->tbn, local->tempdata);
	local->output = normalized(new_vector(local->result->matrix[0][0],
				local->result->matrix[1][0], local->result->matrix[2][0]));
	delete_matrix(local->result);
}

t_vec3	bump_normal(t_info *info)
{
	t_bump	local;

	local.u = info->uv.u;
	local.v = info->uv.v;
	if (info->e->type == PLANE)
	{
		local.u *= 0.5;
		local.v *= 0.5;
	}
	local.h = get_color_texture(info->e->imgnormal, local.u, local.v).z;
	local.hr = get_color_texture(info->e->imgnormal, local.u
			+ 1.0f / info->e->imgnormal.width, local.v).z;
	local.hu = get_color_texture(info->e->imgnormal,
			local.u, local.v + 1.0f / info->e->imgnormal.height).z;
	info->tangent = normalized(info->tangent);
	local.bitangent = normalized(cross(info->localnormal, info->tangent));
	local.bump_normal = normalized(cross((t_vec3){1, 0, (local.hr - local.h)
				* 10}, (t_vec3){0, 1, (local.hu - local.h) * 10}));
	local.tbn = create_matrix(3, 3);
	local.values = (float [])
	{info->tangent.x, local.bitangent.x, info->localnormal.x,
		info->tangent.y, local.bitangent.y, info->localnormal.y,
		info->tangent.z, local.bitangent.z, info->localnormal.z};
	(fill_mt(local.tbn, local.values), helper(&local));
	return (local.output);
}

t_vec3	get_color_texture(t_data image, float u, float v)
{
	t_text	local;

	local.width = image.width;
	local.height = image.height;
	u -= floorf(u);
	v -= floorf(v);
	local.x = min((u * local.width), local.width - 1);
	local.y = min((1 - v) * local.height, local.height - 1);
	local.pixel_index = local.y * image.line_length
		+ local.x * (image.bits_per_pixel / 8);
	local.dst = image.addr + local.pixel_index;
	local.final = *((unsigned int *) local.dst);
	local.color = new_vector((local.final >> 16 & 255) / 255.0f,
			(local.final >> 8 & 255) / 255.0f, (local.final & 255) / 255.0f);
	return (local.color);
}
