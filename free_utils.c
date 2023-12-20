/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:01:21 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/20 23:25:23 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*result;
	size_t i;
	if (nelem && elsize > SIZE_MAX / nelem)
		return (0);
	result = malloc(nelem * elsize);
	if (!result)
		return (0);
	i = 0;
	while (i < nelem * elsize)
		((unsigned char *)result)[i++] = 0;
	return (result);
}

void free_objects(t_object *objects)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (objects[i].type == SPHERE || objects[i].type == CYLINDER)
		{
			delete_matrix(objects[i].gtfm[0]);
			delete_matrix(objects[i].gtfm[1]);
			free(objects[i].gtfm);
		}
		i++;
	}
	free(objects);
}

void free_image(t_image *image)
{
	int i;

	i = 0;
	while (i < HEIGHT)
	{
		free(image->red[i]);
		free(image->green[i]);
		free(image->blue[i]);
		i++;
	}
	free(image->red);
	free(image->green);
	free(image->blue);
	free(image);
}