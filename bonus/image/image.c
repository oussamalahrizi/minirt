/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 23:34:30 by olahrizi          #+#    #+#             */
/*   Updated: 2024/01/03 23:37:17 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

float	**make_channel(void)
{
	float	**new;
	int		i;
	int		j;

	i = 0;
	new = malloc(sizeof(float *) * HEIGHT);
	while (i < HEIGHT)
	{
		new[i] = malloc(sizeof(float) * WIDTH);
		j = 0;
		while (j < WIDTH)
			new[i][j++] = 0.0f;
		i++;
	}
	return (new);
}

t_image	*new_image(void)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	image->red = make_channel();
	image->green = make_channel();
	image->blue = make_channel();
	return (image);
}

unsigned int	rgb_to_int(float red, float green, float blue)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	value;

	if (red > 1)
		red = 1;
	if (green > 1)
		green = 1;
	if (blue > 1)
		blue = 1;
	r = (red) * 255.0;
	g = (green) * 255.0;
	b = (blue) * 255.0;
	value = (r << 16) | (g << 8) | b;
	return (value);
}
