/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:39:40 by olahrizi          #+#    #+#             */
/*   Updated: 2023/12/25 12:41:15 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_data	new_mlx_image(void *mlx_ptr)
{
	t_data	image;

	image.img = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	return (image);
}

void	my_mlx_put_pixel(t_data *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	set_pixel(int x, int y, t_vec3 *color, t_image *image)
{
	image->red[y][x] = color->x;
	image->green[y][x] = color->y;
	image->blue[y][x] = color->z;
}

void	render(t_image *image, void *mlx_ptr, void *win_ptr)
{
	t_data			mlx_image;
	float			max;
	unsigned int	color;
	int				x;
	int				y;

	mlx_image = new_mlx_image(mlx_ptr);
	max = max_overall(image);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = rgb_to_int(image->red[y][x],
					image->green[y][x], image->blue[y][x], max);
			my_mlx_put_pixel(&mlx_image, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, mlx_image.img, 0, 0);
	mlx_destroy_image(mlx_ptr, mlx_image.img);
}
