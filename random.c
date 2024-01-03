/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 11:53:36 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/25 12:21:06 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

unsigned int	rand_pcg(unsigned int *rng_state)
{
	unsigned int		state;
	unsigned int		word;

	state = *rng_state;
	*rng_state = state * 747796405u + 2891336453u;
	word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return ((word >> 22u) ^ word);
}

float	random_float(unsigned int *rng_state, float min, float max)
{
	return (min + (rand_pcg(rng_state) * (1.0 / UINT_MAX)
		) * (max - min));
}
