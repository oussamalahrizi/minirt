/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_text.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:01:56 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 06:20:07 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORM_TEXT_H
# define NORM_TEXT_H

# include "../header.h"

typedef struct s_text
{
	int				width;
	int				height;
	int				x;
	int				y;
	int				pixel_index;
	char			*dst;
	t_vec3			color;
	unsigned int	final;
}	t_text;

typedef struct s_bump
{
	float		h;
	float		hr;
	float		hu;
	t_vec3		bump_normal;
	t_vec3		bitangent;
	float		u;
	float		v;
	t_matrix	*tbn;
	float		*values;
	t_matrix	*tempdata;
	t_matrix	*result;
	t_vec3		output;
}	t_bump;

#endif