#include "minirt.h"

double **make_channel()
{
    double **new;

    int i;

    new = malloc(sizeof(double *) * HEIGHT);
    i = 0;
    while (i < HEIGHT)
    {
        new[i] = malloc(sizeof(double) * WIDTH);
        i++;
    }
    return (new);
}

t_image *new_image()
{
    t_image *image;

    image = malloc(sizeof(t_image));

    image->red = make_channel();
    image->green = make_channel();
    image->blue = make_channel();

    return (image);
}

void set_pixel(t_image *image, t_vec3 *color, int x, int y)
{
    image->red[y][x] = color->x,
    image->green[y][x] = color->y,
    image->blue[y][x] = color->z;
}

void render(t_image *image, void *mlx, void *win)
{
    int x;
    int y;
    t_data img_data;
    double max;
    int temp;

    max = max_overall(image);
    img_data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
    img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bits_per_pixel, &img_data.line_length,
                                        &img_data.endian);
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            temp = rgb_to_int(image->red[y][x], image->green[y][x], image->blue[y][x], max);
            my_mlx_put_pixel(&img_data, x, y, temp);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(mlx, win, img_data.img, 0, 0);
    mlx_destroy_image(mlx, img_data.img);
}