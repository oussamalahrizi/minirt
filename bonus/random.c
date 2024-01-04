/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 11:53:36 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/04 06:49:02 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

unsigned int	rand_pcg(unsigned int *rng_state)
{
	unsigned int	seed;

	seed = (unsigned int)(*rng_state ^ (61)) ^ (*rng_state >> (16));
	seed *= (9);
	seed = seed ^ (seed >> 4);
	seed *= (0x27d4eb2d);
	seed = seed ^ (seed >> 15);
	*rng_state = seed;
	return (seed);
}

float	random_float(unsigned int *rng_state, float min, float max)
{
	return (min + (rand_pcg(rng_state) * (1.0 / UINT_MAX)
		) * (max - min));
}
