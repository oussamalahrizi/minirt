#include "minirt.h"

int rgb_to_int(double red, double green, double blue, double max)
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    int result;

    r = (red / max) * 255;
    g = (green / max) * 255;
    b = (blue / max) * 255;
    result = (r << 16) + (g << 8) + b;

    return (result);
}

double max_in_channel(double **channel)
{
    int x;
    int y;
    double max;
    double value;

    max = -1;
    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            value = channel[y][x];
            if (value > max)
                max = value;
            y++;
        }
        x++;
    }
    return (max);
}

double max_overall(t_image *image)
{
    double max;
    double value;

    max = max_in_channel(image->red);
    value = max_in_channel(image->green);
    if (value > max)
        max = value;
    value = max_in_channel(image->blue);
    if (value > max)
        max = value;
    return (max);
}

void my_mlx_put_pixel(t_data *img, int x, int y, int color)
{
    char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}