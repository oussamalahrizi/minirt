
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

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Raytracer");
	img.img = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	camera = malloc(sizeof(t_camera));
	initialize_camera(camera);
	update_camera(camera);
	printf("camera screen center :\n");
	print_vector(camera->screen_center);
	printf("camera U vector:\n");
	print_vector(camera->u);
	printf("camera V vector :\n");
	print_vector(camera->v);
	t_light *light = malloc(sizeof(t_light));
	light->position = new_vector3(5, -10, -5);
	light->color = new_vector3(255, 255, 255);
	light->intensity = 1;
	t_vec3 *hitposition = new_vector3(0,0,0);
	t_vec3 *localnormal = new_vector3(0,0,0);
	t_vec3 *localcolor = new_vector3(0,0,0);
	int y = 0;
	int x;
	t_vec3 coord;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			coord.x = ((double)x / (double) WIDTH ) * 2 - 1;
			coord.y = ((double)y / (double) HEIGHT ) * 2 - 1;
			t_ray *ray = generate_ray(coord.x, coord.y, camera);
			if (intersect_sphere(ray, hitposition, localnormal, localcolor))
			{
				//compute the intensity
				double intensity;
				t_vec3 color;
				int validillum;
				validillum = compute_illumination(light, hitposition, &color, &intensity);
				if (validillum)
				{
					t_vec3 *sphere = new_vector3(10, 0, 255);
					sphere->x = intensity * sphere->x;
					sphere->y = intensity * sphere->y;
					sphere->z = intensity * sphere->z;
					my_mlx_pixel_put(&img, x, y, sphere);
				}
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}


// vectors: corss dot normileze normilized operatios : */ -+ with other vectors and numbers | lenght = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))

// x = a2 + b2.t 

// r^2 = x^2 + y^y + z^2
// => r^2 = (a2.x + b2.x*t) +  (a2.y + b2.y*t) + (a2.z + b2.z*t);
