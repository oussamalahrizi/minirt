
#include "minirt.h"

unsigned int rgbToInteger(t_vec3 *color)
{
	int red = color->x;
	int green = color->y;
	int blue = color->z;
    unsigned int result = (red << 16) | (green << 8) | blue;
    return result;
}



int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;
	// t_scene	scene;
	t_camera *camera;
	t_image *image = new_image();
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Raytracer");
	img.img = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	camera = malloc(sizeof(t_camera));
	initialize_camera(camera);
	update_camera(camera);
	t_light *light_list = init_light();
	t_object *objects = init_objects();
	t_int_info *info = malloc(sizeof(t_int_info));
	int y = 0;
	int x;
	t_vec3 coord;
	while (y < HEIGHT)
	{
		x = 0;
		printf("Processing line : %d", y + 1);
		printf("\r");
		fflush(stdout);
		while (x < WIDTH)
		{
			coord.x = ((double)x / (double) WIDTH ) * 2 - 1;
			coord.y = ((double)y / (double) HEIGHT ) * 2 - 1;
			t_ray *ray = generate_ray(coord.x, coord.y, camera);
			int intfound = test_intersection(ray, objects, info);
			if (intfound)
			{
				// set_pixel(image, info->closest_object->base_color, x, y);
				double intensity;
				t_vec3 *color = new_vector3(0.0, 0.0, 0.0);
				int validillum = 0;
				int illumfound = 0;
				double red = 0;
				double green = 0;
				double blue = 0;
				int j = 0;
				while (j < 3)
				{
					validillum = compute_illumination(&light_list[j], objects, info->closest_object,
						info->intpoint,info->localnormal, color, &intensity);
					if (validillum)
					{
						illumfound = 1;
						red += color->x * intensity;
						green += color->y * intensity;
						blue += color->z * intensity;
					}
					j++;
				}
				if (illumfound)
				{
					red *= info->closest_object->base_color->x;
					green *= info->closest_object->base_color->y;
					blue *= info->closest_object->base_color->z;
					color->x = red;
					color->y = green;
					color->z = blue;
					set_pixel(image, color, x, y);
				}
			}
			x++;
		}
		y++;
	}
	render(image, mlx_ptr, win_ptr);
	printf("\nDone\n");
	mlx_loop(mlx_ptr);
	return (0);
}


// vectors: corss dot normileze normilized operatios : */ -+ with other vectors and numbers | lenght = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))

// x = a2 + b2.t 

// r^2 = x^2 + y^y + z^2
// => r^2 = (a2.x + b2.x*t) +  (a2.y + b2.y*t) + (a2.z + b2.z*t);
