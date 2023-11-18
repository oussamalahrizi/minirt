
#include "minirt.h"

unsigned int rgbToInteger(t_vec3 *color)
{
	int red = color->x;
	int green = color->y;
	int blue = color->z;
	unsigned int result = (red << 16) | (green << 8) | blue;
	return result;
}


int mouse_hook(void **param)
{
	mlx_destroy_window(param[0], param[1]);
	exit(1);
}

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;
	t_data img;
	// t_scene	scene;
	t_camera *camera;
	t_image *image = new_image();

	camera = malloc(sizeof(t_camera));
	initialize_camera(camera);
	update_camera(camera);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Raytracing goes prrrr");
	img.img = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	t_light *light_list = init_light();
	t_object *objects = init_objects();
	
	double xFact = 1.0 / ((double)(WIDTH) / 2.0);
	double yFact = 1.0 / ((double)(HEIGHT) / 2.0);
	int x;
	t_int_info *info = NULL;
	int y = 0;
	while (y < HEIGHT)
	{
		// printf("line : %d", y + 1);
		// printf("\r");
		// fflush(stdout);
		x = 0;
		while (x < WIDTH)
		{
			double normX = ((double)(x)* xFact) - 1.0;
			double normY = ((double)(y)* yFact) - 1.0;
			t_ray *ray = generate_ray(normX, normY, camera);
			if (info)
			{
				free(info);
				info = NULL;
			}
			info = calloc(1, sizeof(t_int_info));
			int intfound = test_intersection(ray, objects, info);
			if (intfound)
			{
				if (info->closest_object->has_material == 1)
				{
					t_vec3 *color;
					color = compute_color(objects, light_list, info, ray, 0);
					set_pixel(image, color, x, y);
					free(color);
				}
				else
				{
					t_vec3 *color;
					color = diffuse_color(objects, light_list, info, info->closest_object->base_color);
					set_pixel(image, color, x, y);
					free(color);
				}
			}
			x++;
		}
		y++;
	}
	render(image, mlx_ptr, win_ptr);
	void **param = (void *[]) {mlx_ptr, win_ptr};
	mlx_hook(win_ptr, 17, 0, mouse_hook, param);
	mlx_loop(mlx_ptr);
	return (0);
}

// vectors: corss dot normileze normilized operatios : */ -+ with other vectors and numbers | lenght = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))

// x = a2 + b2.t

// r^2 = x^2 + y^y + z^2
// => r^2 = (a2.x + b2.x*t) +  (a2.y + b2.y*t) + (a2.z + b2.z*t);
