/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_mat.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:42:54 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/03 23:24:36 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORM_MAT_H
# define NORM_MAT_H

# include "../header.h"

typedef struct s_diff
{
	float	red;
	float	green;
	float	blue;
	int		validillum;
	int		illumfound;
	t_vec3	diff_color;
	float	intensity;
}	t_diff;

typedef struct s_spc
{
	t_vec3	spc_color;
	float	red;	
	float	green;	
	float	blue;
	t_vec3	lighdir;
	t_vec3	start;
	t_vec3	point2;
	t_ray	lightray;
	float	intensity;
	int		validint;
}	t_spc;

typedef struct s_cast
{
	int		validint;
	int		intfound;
	float	mindist;
	float	dist;
	t_info	other;
}	t_cast;

#endif